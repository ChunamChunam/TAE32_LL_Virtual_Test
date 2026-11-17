using System.Text.RegularExpressions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Generates editable test cases from real LL signatures and real SDK macros.
/// Prefers write→read / clear→verify paired scenarios when companion functions exist in the same header.
/// </summary>
public sealed class LlTestCaseGenerator
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;

    public LlTestCaseGenerator(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task<IReadOnlyList<LlTestCaseEditModel>> GenerateAsync(
        Guid llFunctionId, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var fn = await db.LlFunctions.AsNoTracking()
            .Include(x => x.ParseParameters)
            .FirstOrDefaultAsync(x => x.Id == llFunctionId, cancellationToken)
            ?? throw new KeyNotFoundException("LL 函数不存在");

        return await GenerateForFunctionAsync(db, fn, cancellationToken);
    }

    public async Task<IReadOnlyList<LlTestCaseEditModel>> GenerateForPeripheralAsync(
        Guid sdkProjectId,
        string peripheralName,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var functions = await db.LlFunctions.AsNoTracking()
            .Include(x => x.ParseParameters)
            .Where(x => x.SdkProjectId == sdkProjectId
                        && x.PeripheralName == peripheralName
                        && (x.Form == null || x.Form.Contains("inline")))
            .OrderBy(x => x.FunctionName)
            .ToListAsync(cancellationToken);

        var all = new List<LlTestCaseEditModel>();
        foreach (var fn in functions)
        {
            cancellationToken.ThrowIfCancellationRequested();
            all.AddRange(await GenerateForFunctionAsync(db, fn, cancellationToken));
        }

        return all;
    }

    private async Task<IReadOnlyList<LlTestCaseEditModel>> GenerateForFunctionAsync(
        AppDbContext db, LlFunction fn, CancellationToken cancellationToken)
    {
        if (!SdkLlSourceFilter.IsInlineAvailableInSdk(fn.FilePath, fn.FunctionName))
            return Array.Empty<LlTestCaseEditModel>();

        var pinMacros = ExtractNamedMacros(fn.FilePath, "LL_GPIO_PIN_")
            .Where(x => !x.Name.EndsWith("_ALL", StringComparison.Ordinal))
            .Take(2)
            .ToList();

        var instances = await db.PeripheralInstances.AsNoTracking()
            .Where(x => x.SdkProjectId == fn.SdkProjectId
                        && (x.ModuleName == fn.PeripheralName
                            || (fn.PeripheralName != null && x.Name.StartsWith(fn.PeripheralName))))
            .OrderBy(x => x.Name)
            .Select(x => x.Name)
            .Take(2)
            .ToListAsync(cancellationToken);

        var parameters = fn.ParseParameters.OrderBy(p => p.Position).ToList();
        if (parameters.Count == 0)
        {
            var fromSig = TestHarnessGenerator.ParseParametersFromSignature(
                fn.Signature ?? $"{fn.ReturnType} {fn.FunctionName}({fn.Parameters})");
            if (fromSig.Count == 0)
                return new[] { DraftShell(fn, $"{fn.FunctionName}/draft-no-params") };
            parameters = fromSig.Select((p, i) => new LlFunctionParameter
            {
                Name = p.Name,
                Type = p.Type,
                Position = i
            }).ToList();
        }

        var isGpio = string.Equals(fn.PeripheralName, "GPIO", StringComparison.OrdinalIgnoreCase)
                     || fn.FunctionName.StartsWith("LL_GPIO_", StringComparison.Ordinal);
        var isRcu = string.Equals(fn.PeripheralName, "RCU", StringComparison.OrdinalIgnoreCase)
                    || fn.FunctionName.StartsWith("LL_RCU_", StringComparison.Ordinal);

        if (isGpio)
        {
            var gpioCases = BuildGpioCases(fn, parameters, instances, pinMacros);
            foreach (var model in gpioCases)
                ApplyHostPolicy(model, fn);
            return gpioCases;
        }

        // RCU also uses SET_BIT/CLEAR_BIT on concrete masks (HSE/HSI/PLL) — same bit-op path.
        IReadOnlyList<LlTestCaseEditModel> cases;
        {
            var inst = instances.FirstOrDefault()
                       ?? InferDefaultInstance(fn.PeripheralName, fn.FunctionName)
                       ?? (isRcu ? "RCU" : null)
                       ?? "UNK";
            if (isRcu && instances.Count == 0)
                instances = new List<string> { "RCU" };
            var allowClearCheck = await InstanceHasRegisterMemberAsync(
                db, fn.SdkProjectId, inst, "ISR", cancellationToken);
            cases = await BuildGenericCasesAsync(db, fn, parameters, instances, allowClearCheck, cancellationToken);
        }

        foreach (var model in cases)
            ApplyHostPolicy(model, fn);
        return cases;
    }

    private static IReadOnlyList<LlTestCaseEditModel> BuildGpioCases(
        LlFunction fn,
        List<LlFunctionParameter> parameters,
        List<string> instances,
        List<(string Name, string ValueExpr)> pinMacros)
    {
        if (instances.Count == 0)
            return new[] { DraftShell(fn, $"{fn.FunctionName}/draft-no-gpio-instance") };

        var cases = new List<LlTestCaseEditModel>();
        var pins = pinMacros.Count > 0 ? pinMacros : new List<(string, string)> { ("PIN_LITERAL", "0x1") };
        if (pinMacros.Count == 0)
        {
            // Do not invent pin macros — only use literal if user must edit; mark Draft.
        }

        var usePins = pinMacros.Count > 0
            ? pinMacros
            : new List<(string Name, string ValueExpr)>();

        foreach (var inst in instances)
        {
            if (usePins.Count == 0)
            {
                var model = BaseModel(fn);
                model.Name = $"{fn.FunctionName}/{inst}/no-pin-macro";
                model.Status = "Draft";
                model.IsAutoGenerated = true;
                model.Parameters = BuildParams(parameters, inst, null);
                model.Notes = "头文件中未解析到 LL_GPIO_PIN_* 宏，请人工填写 Pin。";
                cases.Add(model);
                continue;
            }

            foreach (var pin in usePins)
            {
                // 1) Write-only: register assertion after write
                if (IsWriteLike(fn.FunctionName))
                {
                    var write = BaseModel(fn);
                    write.Name = $"{fn.FunctionName}/{inst}/{pin.Name}/write-check";
                    write.Status = "Ready";
                    write.IsAutoGenerated = true;
                    write.Parameters = BuildParams(parameters, inst, pin.ValueExpr);
                    write.InitialRegisters =
                    [
                        new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = "0x0" },
                        new LlTestInitialRegister { InstanceName = inst, MemberName = "BSR", ValueHex = "0x0" }
                    ];
                    write.Assertions = BuildGpioWriteAssertions(fn.FunctionName, inst, pin.ValueExpr);
                    write.Notes = $"写后查寄存器（虚拟 GPIO）。宏 {pin.Name}={pin.ValueExpr}。非真实硬件。";
                    cases.Add(write);

                    // 2) Write → Read pair when companion read exists in same header
                    var readName = SuggestGpioReadCompanion(fn.FunctionName);
                    if (readName is not null && HeaderDeclares(fn.FilePath, readName))
                    {
                        var pair = BaseModel(fn);
                        pair.Name = $"{fn.FunctionName}→{readName}/{inst}/{pin.Name}";
                        pair.FunctionName = readName; // main = read (return value)
                        pair.FunctionSignature = $"uint32_t {readName}(const GPIO_TypeDef *GPIOx)";
                        pair.Status = "Ready";
                        pair.IsAutoGenerated = true;
                        pair.PreludeCalls =
                        [
                            new LlTestCallStep
                            {
                                FunctionName = fn.FunctionName,
                                Parameters = BuildParams(parameters, inst, pin.ValueExpr)
                            }
                        ];
                        pair.Parameters = BuildParamsForRead(readName, inst, pin.ValueExpr);
                        pair.InitialRegisters =
                        [
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = "0x0" }
                        ];
                        if (TryBuildGpioGetterAssertionsAfterSet(fn.FunctionName, readName, inst, pin.ValueExpr,
                                out var getterAssertions))
                        {
                            pair.Assertions = getterAssertions;
                        }
                        else if (readName.Contains("ReadOutputPort", StringComparison.OrdinalIgnoreCase))
                        {
                            var expected = ExpectedPortAfterWrite(fn.FunctionName, pin.ValueExpr);
                            pair.Assertions =
                            [
                                ReturnValueAssertion($"0x{expected:X}",
                                    "写后 ReadOutputPort 返回值应与写入端口值一致"),
                                ..DefaultTimeoutAssertions()
                            ];
                        }
                        else
                        {
                            var expected = ExpectedPortAfterWrite(fn.FunctionName, pin.ValueExpr);
                            var dorMask = fn.FunctionName.Contains("WriteOutputPort", StringComparison.OrdinalIgnoreCase)
                                ? 0xFFFFu
                                : (expected == 0 ? 0xFFFFu : expected);
                            pair.Assertions =
                            [
                                new LlTestAssertionSpec
                                {
                                    Kind = LlAssertionKind.RegisterValue,
                                    InstanceName = inst,
                                    MemberName = "DOR",
                                    ExpectedHex = $"0x{expected:X}",
                                    ExpectedMask = dorMask,
                                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                                    RuleSourceDetail = "写后 DOR 应与写入一致（虚拟；同步后校验，非宿主 RAM 返回值）"
                                },
                                ..DefaultTimeoutAssertions()
                            ];
                        }
                        pair.Notes = "读写成对：同一 harness 先写后读。虚拟环境结果，非真实硬件。";
                        cases.Add(pair);
                    }
                }
                else if (IsReadLike(fn.FunctionName))
                {
                    var read = BaseModel(fn);
                    read.Name = $"{fn.FunctionName}/{inst}/{pin.Name}/read-prepared";
                    read.Status = "Ready";
                    read.IsAutoGenerated = true;
                    read.Parameters = BuildParams(parameters, inst, pin.ValueExpr);
                    if (TryBuildGpioGetterPreparedCase(fn.FunctionName, inst, pin.ValueExpr,
                            out var initRegs, out var getterAsserts))
                    {
                        read.InitialRegisters = initRegs;
                        read.Assertions = getterAsserts;
                    }
                    else if (read.FunctionName.Contains("ReadOutputPort", StringComparison.OrdinalIgnoreCase))
                    {
                        var pinVal = TestHarnessGenerator.ParseUIntExpression(pin.ValueExpr);
                        read.InitialRegisters =
                        [
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = $"0x{pinVal:X}" }
                        ];
                        read.Assertions =
                        [
                            ReturnValueAssertion($"0x{pinVal:X}", "预置 DOR 后 ReadOutputPort 应返回端口值"),
                            ..DefaultTimeoutAssertions()
                        ];
                    }
                    else
                    {
                        var pinVal = TestHarnessGenerator.ParseUIntExpression(pin.ValueExpr);
                        read.InitialRegisters =
                        [
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = $"0x{pinVal:X}" }
                        ];
                        read.Assertions =
                        [
                            new LlTestAssertionSpec
                            {
                                Kind = LlAssertionKind.RegisterValue,
                                InstanceName = inst,
                                MemberName = "DOR",
                                ExpectedHex = $"0x{pinVal:X}",
                                ExpectedMask = pinVal,
                                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                                RuleSourceDetail = "预置 DOR 后读回；同步后校验 DOR"
                            },
                            ..DefaultTimeoutAssertions()
                        ];
                    }
                    read.Notes = "读用例：先预置寄存器再调用读函数。虚拟环境。";
                    cases.Add(read);
                }
                else if (IsClearLike(fn.FunctionName))
                {
                    var pinVal = TestHarnessGenerator.ParseUIntExpression(pin.ValueExpr);
                    var clear = BaseModel(fn);
                    clear.Name = $"{fn.FunctionName}/{inst}/{pin.Name}/clear-check";
                    clear.Status = "Draft";
                    clear.IsAutoGenerated = true;
                    clear.Parameters = BuildParams(parameters, inst, pin.ValueExpr);
                    clear.InitialRegisters =
                    [
                        new LlTestInitialRegister { InstanceName = inst, MemberName = "ISR", ValueHex = $"0x{pinVal:X}" }
                    ];
                    clear.Assertions =
                    [
                        new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.RegisterValue,
                            InstanceName = inst,
                            MemberName = "ISR",
                            ExpectedHex = "0x0",
                            ExpectedMask = pinVal == 0 ? 0xFFFFu : pinVal,
                            RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                            RuleSourceDetail = "清标志后对应位应为 0（虚拟；需对照真实清零语义）"
                        },
                        ..DefaultTimeoutAssertions()
                    ];
                    clear.Notes = "清空/清标志：预置标志位后调用 Clear，断言位清除。请核对真实寄存器名。";
                    cases.Add(clear);
                }
                else
                {
                    var model = BaseModel(fn);
                    model.Name = $"{fn.FunctionName}/{inst}/{pin.Name}";
                    model.Status = "Draft";
                    model.IsAutoGenerated = true;
                    model.Parameters = BuildParams(parameters, inst, pin.ValueExpr);
                    model.Assertions = DefaultTimeoutAssertions();
                    model.Notes = $"自动草稿：宏 {pin.Name}={pin.ValueExpr}。请补断言。";
                    cases.Add(model);
                }
            }
        }

        return cases;
    }

    private static async Task<IReadOnlyList<LlTestCaseEditModel>> BuildGenericCasesAsync(
        AppDbContext db,
        LlFunction fn,
        List<LlFunctionParameter> parameters,
        List<string> instances,
        bool allowClearCheck,
        CancellationToken cancellationToken)
    {
        var inst = instances.FirstOrDefault()
                   ?? InferDefaultInstance(fn.PeripheralName, fn.FunctionName);
        var cases = new List<LlTestCaseEditModel>();

        var draftParams = BuildParams(
            parameters.Count > 0 ? parameters : FakeParamsFromSig(fn),
            inst,
            null,
            fn.FunctionName);

        var builtSpecial = false;

        // Get/Is/Read: preload + expected return derived from the SAME initial value.
        if (IsLikelyGetter(fn.FunctionName))
        {
            var readChecks = await TryBuildReadPreparedCasesAsync(db, fn, inst, draftParams, cancellationToken);
            if (readChecks.Count > 0)
            {
                cases.AddRange(readChecks);
                builtSpecial = true;
            }
        }

        // Set/Write: MODIFY_REG write-check (chip Mask/Pos + CMSIS RMW formula).
        var modifyChecks = await TryBuildModifyRegWriteCasesAsync(db, fn, inst, draftParams, cancellationToken);
        if (modifyChecks.Count > 0)
        {
            cases.AddRange(modifyChecks);
            builtSpecial = true;

            // Set → Get pair from the first (representative) write-check.
            if (await TryBuildSetThenGetPairAsync(db, fn, inst, modifyChecks[0], cancellationToken) is { } pair)
                cases.Add(pair);
        }

        // SET_BIT / CLEAR_BIT / WRITE_REG write-check — covers Enable/Disable across all modules.
        // Skip SET/CLEAR on the same member when MODIFY_REG case already exists (e.g. UART SetParity:
        // CLEAR+MODIFY in one call — running a CLEAR-only expectation against the full fn is wrong).
        var bitOpChecks = await TryBuildBitOpWriteCasesAsync(db, fn, inst, draftParams, cancellationToken);
        if (bitOpChecks.Count > 0)
        {
            var modifyMembers = cases
                .Where(c => c.Name.Contains("/write-check", StringComparison.OrdinalIgnoreCase)
                            && (c.Notes?.Contains("MODIFY", StringComparison.OrdinalIgnoreCase) == true
                                || c.Assertions.Any(a =>
                                    (a.RuleSourceDetail ?? "").Contains("MODIFY_REG", StringComparison.Ordinal))))
                .SelectMany(c => c.Assertions
                    .Where(a => a.Kind == LlAssertionKind.RegisterValue)
                    .Select(a => a.MemberName))
                .Where(m => !string.IsNullOrEmpty(m))
                .ToHashSet(StringComparer.OrdinalIgnoreCase);

            foreach (var bitOpCheck in bitOpChecks)
            {
                var dup = cases.Any(c =>
                    string.Equals(c.Name, bitOpCheck.Name, StringComparison.OrdinalIgnoreCase));
                var bitMembers = bitOpCheck.Assertions
                    .Where(a => a.Kind == LlAssertionKind.RegisterValue)
                    .Select(a => a.MemberName)
                    .Where(m => !string.IsNullOrEmpty(m))
                    .ToList();
                var overlapsModify = modifyMembers.Count > 0
                                     && bitMembers.Any(m => modifyMembers.Contains(m!))
                                     && (bitOpCheck.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)
                                         || bitOpCheck.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase)
                                         || bitOpCheck.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase)
                                         || bitOpCheck.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase));
                if (!dup && !overlapsModify)
                {
                    cases.Add(bitOpCheck);
                    builtSpecial = true;
                }
            }
        }

        if (!builtSpecial)
        {
            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/{inst}/draft";
            model.Status = nameof(LlTestCaseStatus.Draft);
            model.IsAutoGenerated = true;
            model.Parameters = draftParams;
            model.Assertions = DefaultTimeoutAssertions();
            model.Notes = "自动草稿：仅超时断言。未能从 SET_BIT/CLEAR_BIT/WRITE_REG/MODIFY_REG/READ + 寄存器位域生成校验；请手工补断言。";
            cases.Add(model);
        }

        // Legacy fallback only when WRITE_REG/bit-op did not already emit Ready clear/disable-check.
        // Never expect the whole status register to become 0 — only the target flag bits.
        var hostCanRun = LlNativeEligibility.DescribeSkip(fn.FunctionName, fn.FilePath, draftParams) is null;
        var alreadyHasClearCheck = cases.Any(c =>
            c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase));
        if (allowClearCheck && hostCanRun && !alreadyHasClearCheck && IsClearLike(fn.FunctionName)
            && LlClearStatusRegisterResolver.TryResolve(fn.FunctionName, fn.PeripheralName, out var clrMem, out var clrMask))
        {
            if (clrMask == 0) clrMask = 1u;
            const uint widthOnes = 0xFFFFFFFFu;
            var initialBits = widthOnes;
            var preserveBits = widthOnes & ~clrMask;
            var clear = BaseModel(fn);
            clear.Name = $"{fn.FunctionName}/{inst}/{clrMem}/clear-check";
            clear.Status = nameof(LlTestCaseStatus.Draft);
            clear.IsAutoGenerated = true;
            clear.Parameters = draftParams.Select(p => new LlTestParameterValue
            {
                Name = p.Name,
                Type = p.Type,
                ValueExpression = p.ValueExpression,
                RuleSource = p.RuleSource
            }).ToList();
            clear.InitialRegisters =
            [
                new LlTestInitialRegister { InstanceName = inst, MemberName = clrMem, ValueHex = $"0x{initialBits:X}" }
            ];
            clear.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = inst,
                    MemberName = clrMem,
                    ExpectedHex = "0x0",
                    ExpectedMask = clrMask,
                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                    RuleSourceDetail = $"目标位清零：(actual & 0x{clrMask:X}) == 0（虚拟 W1C；{clrMem}）"
                },
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = inst,
                    MemberName = clrMem,
                    ExpectedHex = $"0x{preserveBits:X}",
                    ExpectedMask = preserveBits,
                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                    RuleSourceDetail =
                        $"非目标位保持：(actual & ~0x{clrMask:X}) == 0x{preserveBits:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            clear.Notes = "清空类回退：预置全 1 后 Clear，断言目标位 W1C 清零且其它位保持。虚拟环境。";
            cases.Add(clear);
        }

        // Combo macros: annotate every generated case with any ->MEM ↔ mask mismatches in the body.
        var liveBody = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        var mismatchNotes = CollectBodyMaskMemberMismatchNotes(liveBody);
        if (mismatchNotes.Count > 0)
        {
            var suffix = " | 体宏成员校验: " + string.Join("; ", mismatchNotes.Distinct());
            foreach (var c in cases)
                c.Notes = string.IsNullOrWhiteSpace(c.Notes) ? suffix.TrimStart(' ', '|') : c.Notes + suffix;
        }

        return cases;
    }

    // Flat or nested: Inst->MEM / Inst->Master.MCR0 / Inst->PWM[(Pwmx)%N].REG.PWMCR0
    private static readonly Regex ModifyRegPattern = new(
        @"MODIFY_REG\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*,",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>Full MODIFY_REG including RHS (field-value << Pos vs pre-shifted Mask).</summary>
    private static readonly Regex ModifyRegFullPattern = new(
        @"MODIFY_REG\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*,\s*(?<rhs>[^;]+?)\)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>SET_BIT / CLEAR_BIT(reg-> path, MASK_Msk|_MSK).</summary>
    private static readonly Regex SetClearBitPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>WRITE_REG(reg->path, VALUE) — VALUE may be literal or named mask macro.</summary>
    private static readonly Regex WriteRegPattern = new(
        @"\bWRITE_REG\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<path>[^,]+?)\s*,\s*(?<val>[^;]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    private static readonly Regex ChipFieldMskToken = new(
        @"\b(?<tok>[A-Za-z0-9]+_[A-Za-z0-9]+_[A-Za-z0-9]+_Msk)\b",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    private static readonly Regex ReadBitShiftPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*,\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>Channel flag: READ_BIT_SHIFT(ADCx->DISR, BIT(((Ch)%N)), ((Ch)%M)).</summary>
    private static readonly Regex ReadBitShiftChannelBitPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*BIT\s*\(",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Field getter written as (READ_BIT(reg->MEM, Xxx_Msk) >> Xxx_Pos) — common in WWDG/IWDG/UART/etc.
    /// Equivalent to READ_BIT_SHIFT for expected-value generation.
    /// </summary>
    private static readonly Regex ReadBitThenShiftPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*\)\s*>>\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    // Boolean-style: (READ_BIT(..._Msk) ? 1UL : 0UL) — exclude READ_BIT_SHIFT.
    private static readonly Regex ReadBitBoolPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    private static readonly Regex ReadRegPattern = new(
        @"READ_REG\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// SET_BIT / CLEAR_BIT / WRITE_REG → write monitoring for all modules (incl. Enable/Disable).
    /// Expected bits prefer a name-correlated LL_*_MSK #define (independent of a possibly-wrong
    /// SET_BIT argument). Body detects op + member/path; array paths expand channels like MODIFY.
    /// </summary>
    private static async Task<List<LlTestCaseEditModel>> TryBuildBitOpWriteCasesAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        CancellationToken ct)
    {
        var results = new List<LlTestCaseEditModel>();

        // Prefer live body (DB Expression may be stale after SDK edits); then DB parse evidence.
        var liveBody = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        var dbExprs = await db.LlRegisterAccesses.AsNoTracking()
            .Where(a => a.LlFunctionId == fn.Id
                        && (a.MacroName == "SET_BIT"
                            || a.MacroName == "CLEAR_BIT"
                            || a.MacroName == "WRITE_REG"
                            || (a.Expression != null && (
                                a.Expression.Contains("SET_BIT")
                                || a.Expression.Contains("CLEAR_BIT")
                                || a.Expression.Contains("WRITE_REG")))))
            .Select(a => a.Expression)
            .ToListAsync(ct);

        var candidates = new List<string>();
        if (!string.IsNullOrWhiteSpace(liveBody))
            candidates.Add(liveBody);
        candidates.AddRange(dbExprs.Where(e => !string.IsNullOrWhiteSpace(e))!);

        foreach (var text in candidates)
        {
            var setClear = SetClearBitPattern.Match(text);
            if (setClear.Success)
            {
                var op = setClear.Groups["op"].Value.ToUpperInvariant();
                var pathText = setClear.Groups["path"].Success
                    ? setClear.Groups["path"].Value
                    : setClear.Groups["mem"].Value;
                _ = TryParseRegAccessPath(pathText, out var accessPath);
                var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
                    ? PathLeaf(setClear)
                    : accessPath.LeafMember;
                var bodyMskMacro = setClear.Groups["msk"].Value;

                // DAC0_CR_OEN_Msk embeds CR — must match DACx->CR. Mismatch (e.g. ->SR + CR_OEN)
                // asserts on the mask's register so the wrong write is caught.
                var member = ResolveMemberAlignedToMask(
                    bodyMember, bodyMskMacro, out _, out var pairNote);

                // Trusted expected from function-name ↔ header #define / chip RegisterFields
                // (NOT from SET_BIT/CLEAR_BIT argument in the body).
                var trusted = await TryResolveTrustedMaskAsync(db, fn, member, ct);
                string mskMacro;
                uint maskBits;
                bool usedTrusted;
                if (trusted is { Bits: > 0 })
                {
                    mskMacro = trusted.Label;
                    maskBits = trusted.Bits;
                    usedTrusted = true;
                    member = ResolveMemberAlignedToMask(
                        member, mskMacro, out var trustedMismatch, out var trustedPair);
                    if (trustedMismatch)
                        pairNote = trustedPair;
                }
                else
                {
                    mskMacro = bodyMskMacro;
                    maskBits = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
                    usedTrusted = false;
                }

                if (maskBits == 0)
                    continue;

                var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
                var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
                var fieldLabel = usedTrusted
                    ? StripMaskSuffix(mskMacro)
                    : TryFieldNameFromMskMacro(mskMacro, member, out var singleField)
                        ? singleField
                        : mskMacro;

                var arrayBound = ResolveArrayBound(accessPath.ArrayIndexExpr, fn.FilePath);
                IReadOnlyList<uint> channelSamples = accessPath.ArrayIndexExpr is not null
                    ? new uint[] { 0, 1, 2, arrayBound > 0 ? arrayBound - 1 : 0, arrayBound, arrayBound + 1 }
                    : new uint[] { 0 };

                foreach (var channelRaw in channelSamples.Distinct())
                {
                    var channelIndex = accessPath.ArrayIndexExpr is not null
                        ? channelRaw % Math.Max(1u, arrayBound)
                        : 0u;
                    var targetInstance = ResolveNestedInstance(
                        instance, accessPath, channelIndex, bodyMskMacro);

                    // RMW: preload unrelated bits so SET/CLEAR must read-modify-write.
                    var preserveBits = PickUnrelatedPreserveBits(maskBits);
                    var initialBits = isClear ? (preserveBits | maskBits) : preserveBits;
                    var expectedBits = isClear ? preserveBits : (preserveBits | maskBits);
                    var assertMask = preserveBits | maskBits;
                    if (assertMask == 0) assertMask = maskBits;

                    var parameters = CloneParams(baseParams);
                    ApplyBitOpChannelParameters(
                        parameters, fn, instance, targetInstance, accessPath, channelRaw);

                    var channelTag = accessPath.ArrayIndexExpr is not null
                        ? $"ch{channelRaw}->{channelIndex}"
                        : (accessPath.NestedPrefix ?? "flat");

                    var model = BaseModel(fn);
                    model.Name =
                        $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/{channelTag}/{checkSuffix}";
                    model.Status = nameof(LlTestCaseStatus.Ready);
                    model.IsAutoGenerated = true;
                    model.Parameters = parameters;
                    model.InitialRegisters =
                    [
                        new LlTestInitialRegister
                        {
                            InstanceName = targetInstance,
                            MemberName = member,
                            ValueHex = $"0x{initialBits:X}"
                        }
                    ];

                    var trustNote = usedTrusted
                        ? $"期望掩码来自函数名关联的可信源 {mskMacro}（非函数体内位操作实参；可检出错误掩码，即使重新生成）"
                        : $"期望掩码来自体/解析证据 {mskMacro}（未找到函数名关联的 #define/位域；弱可信）";
                    var rmwNote = preserveBits != 0
                        ? $"RMW：预置其它位 0x{preserveBits:X}，写后应保留并{(isClear ? "清除" : "置位")}目标位"
                        : "目标掩码已覆盖全宽，无法另测保留位";
                    var ruleSource = usedTrusted
                        ? LlAssertionRuleSource.AutoGeneratedFromSdkMacro
                        : LlAssertionRuleSource.FromParseEvidence;

                    var assertions = new List<LlTestAssertionSpec>
                    {
                        new()
                        {
                            Kind = LlAssertionKind.RegisterWrite,
                            InstanceName = targetInstance,
                            MemberName = member,
                            RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                            RuleSourceDetail =
                                $"必须写入 {targetInstance}.{member}（{(isClear ? "Disable/CLEAR" : "Enable/SET")}；轨迹校验）"
                        },
                        new()
                        {
                            Kind = LlAssertionKind.RegisterValue,
                            InstanceName = targetInstance,
                            MemberName = member,
                            ExpectedHex = $"0x{expectedBits:X}",
                            ExpectedMask = assertMask,
                            RuleSource = ruleSource,
                            RuleSourceDetail =
                                $"{(isClear ? "CLEAR_BIT" : "SET_BIT")} 写后校验 {member} & 0x{assertMask:X}=0x{expectedBits:X}；{pairNote}；{rmwNote}；{trustNote}"
                        },
                        new()
                        {
                            Kind = LlAssertionKind.RegisterValue,
                            InstanceName = targetInstance,
                            MemberName = member,
                            ExpectedHex = isClear ? "0x0" : $"0x{maskBits:X}",
                            ExpectedMask = maskBits,
                            RuleSource = ruleSource,
                            RuleSourceDetail = isClear
                                ? $"目标位清零：(actual & 0x{maskBits:X}) == 0"
                                : $"目标位置位：(actual & 0x{maskBits:X}) == 0x{maskBits:X}"
                        }
                    };

                    if (preserveBits != 0)
                    {
                        assertions.Add(new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.PreserveBits,
                            InstanceName = targetInstance,
                            MemberName = member,
                            ExpectedHex = $"0x{preserveBits:X}",
                            ExpectedMask = preserveBits,
                            RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                            RuleSourceDetail =
                                $"保留位：(actual & ~0x{maskBits:X}) == (initial & ~0x{maskBits:X}) = 0x{preserveBits:X}"
                        });
                    }

                    // BitField: use resolved maskBits (chip/#define), not DB field.Mask.
                    if (!isClear && TryFieldNameFromMskMacro(mskMacro, member, out var bfName) && maskBits != 0)
                    {
                        var bitPos = PosFromMask(maskBits);
                        var bfExpected = maskBits >> bitPos;
                        assertions.Add(new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.BitField,
                            InstanceName = targetInstance,
                            MemberName = member,
                            BitFieldName = bfName,
                            ExpectedHex = $"0x{bfExpected:X}",
                            ExpectedMask = maskBits,
                            RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                            RuleSourceDetail =
                                $"BitField {bfName} after {op}: Expected=(mask>>pos)；" +
                                $"SetMask=0x{maskBits:X} FieldMask=0x{maskBits:X} Pos={bitPos} " +
                                $"Width={BitWidthFromMask(maskBits)} BitFieldExpected=0x{bfExpected:X}"
                        });
                    }

                    if (accessPath.ArrayIndexExpr is not null)
                    {
                        assertions.Add(new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.ArrayIndex,
                            InstanceName = targetInstance,
                            MemberName = member,
                            ExpectedHex = channelIndex.ToString(),
                            ExpectedExpression =
                                $"{accessPath.ArrayIndexExpr} → {channelRaw}%{arrayBound}={channelIndex}",
                            RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                            RuleSourceDetail =
                                $"数组索引：raw={channelRaw} → index={channelIndex} → {targetInstance}"
                        });
                    }

                    assertions.Add(new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.NoUnexpectedWrite,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedAccessOrder = new[] { $"{targetInstance}.{member}", member },
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail = "禁止意外修改其他寄存器（LL 归因写入）"
                    });

                    assertions.AddRange(DefaultTimeoutAssertions());
                    model.Assertions = assertions;
                    model.Notes = isClear
                        ? $"自动 Disable/CLEAR RMW 监控：path={accessPath.RawPath} Target={targetInstance}.{member} " +
                          $"Initial=0x{initialBits:X} Mask=0x{maskBits:X} Expected=0x{expectedBits:X}。{trustNote}。"
                        : $"自动 Enable/SET RMW 监控：path={accessPath.RawPath} Target={targetInstance}.{member} " +
                          $"Initial=0x{initialBits:X} Mask=0x{maskBits:X} Expected=0x{expectedBits:X}。{trustNote}。";
                    results.Add(model);
                }

                return results;
            }

            var write = WriteRegPattern.Match(text);
            if (!write.Success)
                continue;

            var writePathText = write.Groups["path"].Success
                ? write.Groups["path"].Value
                : "";
            _ = TryParseRegAccessPath(writePathText, out var writePath);
            var writeMember = string.IsNullOrEmpty(writePath.LeafMember)
                ? PathLeaf(write)
                : writePath.LeafMember;
            var writeInstance = ResolveNestedInstance(instance, writePath, 0, null);
            var builtWrite = await TryBuildWriteRegCaseAsync(
                db, fn, writeInstance, baseParams, writeMember, write.Groups["val"].Value.Trim(), ct);
            if (builtWrite is not null)
            {
                EnrichWriteRegMonitoringAssertions(builtWrite, writeInstance, writeMember);
                results.Add(builtWrite);
                return results;
            }
        }

        return results;
    }

    /// <summary>Enable→enable-check, Disable→disable-check; otherwise set/clear-check.</summary>
    private static string ResolveBitOpCheckSuffix(string? functionName, bool isClear)
    {
        var name = functionName ?? "";
        if (!isClear
            && name.Contains("Enable", StringComparison.OrdinalIgnoreCase)
            && !name.Contains("Disable", StringComparison.OrdinalIgnoreCase))
            return "enable-check";
        if (isClear && name.Contains("Disable", StringComparison.OrdinalIgnoreCase))
            return "disable-check";
        return isClear ? "clear-check" : "set-check";
    }

    private static void ApplyBitOpChannelParameters(
        List<LlTestParameterValue> parameters,
        LlFunction fn,
        string fallbackInstance,
        string targetInstance,
        RegAccessPath accessPath,
        uint channelRaw)
    {
        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
        {
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, fallbackInstance, targetInstance, p.ValueExpression);
        }

        if (accessPath.ArrayIndexExpr is null)
            return;

        var idxNames = Regex.Matches(accessPath.ArrayIndexExpr, @"\b([A-Za-z_][A-Za-z0-9_]*)\b")
            .Select(m => m.Groups[1].Value)
            .Where(id => !id.StartsWith("LL_", StringComparison.Ordinal)
                         && !id.Equals("U", StringComparison.OrdinalIgnoreCase)
                         && !id.Equals("UL", StringComparison.OrdinalIgnoreCase))
            .ToHashSet(StringComparer.OrdinalIgnoreCase);
        var chParam = parameters.FirstOrDefault(p =>
            !p.Type.Contains('*', StringComparison.Ordinal)
            && idxNames.Contains(p.Name));
        chParam ??= parameters.FirstOrDefault(p =>
            !p.Type.Contains('*', StringComparison.Ordinal)
            && (p.Name.Contains("Pwm", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Ch", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Idx", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Index", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Unit", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Tim", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)));

        if (chParam is not null
            && !chParam.Name.Contains("Mode", StringComparison.OrdinalIgnoreCase)
            && !chParam.Name.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
            && !chParam.Name.Contains("Value", StringComparison.OrdinalIgnoreCase))
        {
            chParam.ValueExpression = channelRaw.ToString();
            chParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }
    }

    /// <summary>Add RegisterWrite / NoUnexpectedWrite parity to WRITE_REG cases.</summary>
    private static void EnrichWriteRegMonitoringAssertions(
        LlTestCaseEditModel model, string instance, string member)
    {
        if (model.Assertions.All(a => a.Kind != LlAssertionKind.RegisterWrite))
        {
            model.Assertions.Insert(0, new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterWrite,
                InstanceName = instance,
                MemberName = member,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail = $"必须写入 {instance}.{member}（WRITE_REG；轨迹校验）"
            });
        }

        if (model.Assertions.All(a => a.Kind != LlAssertionKind.NoUnexpectedWrite))
        {
            var insertAt = model.Assertions.FindLastIndex(a => a.Kind != LlAssertionKind.Timeout) + 1;
            if (insertAt < 0) insertAt = 0;
            model.Assertions.Insert(insertAt, new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.NoUnexpectedWrite,
                InstanceName = instance,
                MemberName = member,
                ExpectedAccessOrder = new[] { $"{instance}.{member}", member },
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail = "禁止意外修改其他寄存器（LL 归因写入）"
            });
        }
    }

    private static async Task<LlTestCaseEditModel?> TryBuildWriteRegCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        string wMember,
        string valExpr,
        CancellationToken ct)
    {
        uint expected;
        uint mask;
        string detail;
        var writeTrusted = false;
        string mskLabel;
        var writePairNote = $"断言寄存器 {wMember}";

        var mskTok = Regex.Match(valExpr, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\b",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (mskTok.Success)
        {
            var bodyMsk = mskTok.Groups["msk"].Value;
            // WRITE_REG(ADCx->ISR, ADC0_IER_xxx) style mismatch → assert on mask's register.
            wMember = ResolveMemberAlignedToMask(wMember, bodyMsk, out _, out writePairNote);
            var trusted = await TryResolveTrustedMaskAsync(db, fn, wMember, ct);
            if (trusted is { Bits: > 0 })
            {
                mask = trusted.Bits;
                mskLabel = trusted.Label;
                writeTrusted = true;
            }
            else
            {
                mask = await ResolveClearMaskAsync(db, fn, wMember, bodyMsk, ct);
                mskLabel = bodyMsk;
            }

            if (mask == 0) return null;

            if (IsClearLike(fn.FunctionName))
            {
                // W1C clear-flag: do NOT expect whole register == 0.
                // Preload all-ones (flag + keepable); after WRITE_REG(mask):
                //   (actual & flagMask) == 0
                //   (actual & ~flagMask) == (initial & ~flagMask)
                const uint widthOnes = 0xFFFFFFFFu;
                var initialBits = widthOnes; // e.g. 0xFFFF… → after EWIF W1C becomes ~mask
                var preserveBits = widthOnes & ~mask;
                var trust = writeTrusted
                    ? $"期望掩码来自函数名关联的可信源 {mskLabel}"
                    : $"掩码来自体 {mskLabel}（弱可信）";
                detail =
                    $"WRITE_REG W1C 清标志：目标位 (reg&0x{mask:X})==0，可保持位 (reg&0x{preserveBits:X})==0x{preserveBits:X}；{writePairNote}；{trust}";
                var clearModel = BaseModel(fn);
                clearModel.Name = $"{fn.FunctionName}/{instance}/{wMember}.{StripMaskSuffix(mskLabel)}/clear-check";
                clearModel.Status = nameof(LlTestCaseStatus.Ready);
                clearModel.IsAutoGenerated = true;
                clearModel.Parameters = CloneParams(baseParams);
                clearModel.InitialRegisters =
                [
                    new LlTestInitialRegister
                    {
                        InstanceName = instance, MemberName = wMember, ValueHex = $"0x{initialBits:X}"
                    }
                ];
                clearModel.Assertions =
                [
                    new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = instance,
                        MemberName = wMember,
                        ExpectedHex = "0x0",
                        ExpectedMask = mask,
                        RuleSource = writeTrusted
                            ? LlAssertionRuleSource.AutoGeneratedFromSdkMacro
                            : LlAssertionRuleSource.FromParseEvidence,
                        RuleSourceDetail =
                            $"目标位清零：(actual & 0x{mask:X}) == 0（W1C / {mskLabel}；{writePairNote}）"
                    },
                    new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = instance,
                        MemberName = wMember,
                        ExpectedHex = $"0x{preserveBits:X}",
                        ExpectedMask = preserveBits,
                        RuleSource = writeTrusted
                            ? LlAssertionRuleSource.AutoGeneratedFromSdkMacro
                            : LlAssertionRuleSource.FromParseEvidence,
                        RuleSourceDetail =
                            $"非目标位保持：(actual & ~0x{mask:X}) == (initial & ~0x{mask:X}) = 0x{preserveBits:X}"
                    },
                    ..DefaultTimeoutAssertions()
                ];
                clearModel.Notes = $"{detail}。虚拟环境。";
                return clearModel;
            }

            expected = mask;
            detail = writeTrusted
                ? $"WRITE_REG 写后校验 {wMember}；{writePairNote}；期望掩码来自函数名关联的可信源 {mskLabel}"
                : $"WRITE_REG 写后校验 {wMember}；{writePairNote}（值/掩码来自 {mskLabel} 宏展开+芯片位域）";
        }
        else
        {
            if (!Regex.IsMatch(valExpr, @"^(0x[0-9A-Fa-f]+|[0-9]+)(u|U|ul|UL|ull|ULL)?$"))
                return null;
            expected = TestHarnessGenerator.ParseUIntExpression(valExpr);
            mask = 0xFFFFFFFFu;
            detail = $"WRITE_REG 写后校验 {wMember} == 0x{expected:X}；{writePairNote}";
        }

        // Full WRITE_REG overwrites the register: preload unrelated bits; they must be gone after write.
        var writePreserve = mask == 0xFFFFFFFFu
            ? PickUnrelatedPreserveBits(expected == 0 ? 0u : expected)
            : PickUnrelatedPreserveBits(mask);
        var writeInitial = writePreserve;
        var writeAssertMask = writePreserve | (mask == 0xFFFFFFFFu ? expected : mask);
        if (writeAssertMask == 0) writeAssertMask = mask == 0 ? 0xFFFFFFFFu : mask;

        var wModel = BaseModel(fn);
        wModel.Name = $"{fn.FunctionName}/{instance}/{wMember}/write-check";
        wModel.Status = nameof(LlTestCaseStatus.Ready);
        wModel.IsAutoGenerated = true;
        wModel.Parameters = CloneParams(baseParams);
        wModel.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance,
                MemberName = wMember,
                ValueHex = $"0x{writeInitial:X}"
            }
        ];
        wModel.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = wMember,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = writeAssertMask,
                RuleSource = writeTrusted
                    ? LlAssertionRuleSource.AutoGeneratedFromSdkMacro
                    : LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail = writePreserve != 0
                    ? $"{detail}；整写覆盖：预置其它位 0x{writePreserve:X} 写后应被覆盖；期望已固化，不以运行时被测体为准"
                    : detail + "；期望已固化，不以运行时被测体为准"
            },
            ..DefaultTimeoutAssertions()
        ];
        wModel.Notes =
            $"自动整写校验：预置 0x{writeInitial:X}，WRITE_REG 后断言 {wMember} & 0x{writeAssertMask:X}=0x{expected:X}。虚拟环境。";
        return wModel;
    }

    private static List<LlTestParameterValue> CloneParams(List<LlTestParameterValue> baseParams)
        => baseParams.Select(p => new LlTestParameterValue
        {
            Name = p.Name,
            Type = p.Type,
            ValueExpression = p.ValueExpression,
            RuleSource = p.RuleSource
        }).ToList();

    private static string StripMaskSuffix(string mskMacro)
    {
        if (mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return mskMacro[..^4];
        if (mskMacro.EndsWith("_Msk", StringComparison.Ordinal))
            return mskMacro[..^4];
        return mskMacro;
    }

    private sealed record TrustedMask(uint Bits, string Label, string Source);

    /// <summary>
    /// Bits outside <paramref name="excludeBits"/> used to verify RMW / read-only preserve.
    /// </summary>
    private static uint PickUnrelatedPreserveBits(uint excludeBits)
    {
        const uint p1 = 0xA5A55A5Au;
        const uint p2 = 0x5A5AA5A5u;
        var a = p1 & ~excludeBits;
        if (a != 0) return a;
        return p2 & ~excludeBits;
    }

    /// <summary>
    /// Trusted mask bits for SET/CLEAR expectations — never from the body argument.
    /// Order: header LL #define / alias → chip RegisterFields name match.
    /// </summary>
    private static async Task<TrustedMask?> TryResolveTrustedMaskAsync(
        AppDbContext db, LlFunction fn, string member, CancellationToken ct)
    {
        // AWD ClearFlag/IsActiveFlag numbering quirk must win over naive AWD1 token→AWD1 field.
        var awdMapped = await TryMapAwdFlagToHardwareFieldAsync(db, fn, member, ct);
        if (awdMapped is not null)
            return awdMapped;

        var macro = TryFindTrustedMaskMacroByFunctionName(fn.FilePath, fn.FunctionName, member);
        if (macro is not null)
        {
            var bits = await ResolveClearMaskAsync(db, fn, member, macro, ct);
            if (bits != 0)
                return new TrustedMask(bits, macro, "HeaderDefine");
        }

        var fromField = await TryFindTrustedMaskFromRegisterFieldsAsync(db, fn, member, ct);
        if (fromField is not null)
            return fromField;

        return null;
    }

    private static async Task<TrustedMask?> TryMapAwdFlagToHardwareFieldAsync(
        AppDbContext db, LlFunction fn, string member, CancellationToken ct)
    {
        var awdFlag = Regex.Match(fn.FunctionName ?? "",
            @"(?:ClearFlag|IsActiveFlag)_AWD(\d+)$", RegexOptions.CultureInvariant);
        if (!awdFlag.Success || !int.TryParse(awdFlag.Groups[1].Value, out var awdN) || awdN < 1)
            return null;

        var hw = $"AWD{awdN - 1}";
        var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, hw, ct);
        if (field?.Mask is not uint mm || mm == 0) return null;
        var label = !string.IsNullOrWhiteSpace(field.MskMacroName)
            ? field.MskMacroName!
            : $"{member}_{field.Name}_Msk";
        return new TrustedMask(mm, label, "RegisterFieldAwdMap:" + field.Name);
    }

    /// <summary>
    /// Match function-name tokens to RegisterFields on the same member
    /// (e.g. EnableBias → CFGR1.BIASEN; DisableIT_AWDG2 → IER.AWD2IE).
    /// </summary>
    private static async Task<TrustedMask?> TryFindTrustedMaskFromRegisterFieldsAsync(
        AppDbContext db, LlFunction fn, string member, CancellationToken ct)
    {
        var fields = await db.RegisterFields.AsNoTracking()
            .Include(f => f.RegisterDefinition)
            .Where(f => f.RegisterDefinition != null
                        && f.RegisterDefinition.SdkProjectId == fn.SdkProjectId
                        && f.RegisterDefinition.MemberName == member
                        && f.Mask != null && f.Mask != 0)
            .ToListAsync(ct);
        if (fields.Count == 0) return null;

        // Prefer ADC_TypeDef over ADC0_Type duplicates.
        fields = fields
            .GroupBy(f => f.Name, StringComparer.OrdinalIgnoreCase)
            .Select(g => g.OrderBy(f =>
            {
                var s = f.RegisterDefinition!.StructName;
                if (s.EndsWith("_TypeDef", StringComparison.Ordinal)) return 0;
                return 1;
            }).First())
            .ToList();

        var tokens = BuildFunctionMaskSearchTokens(fn.FunctionName ?? "");
        // RCU naming: HSE→XEN, HSI→HEN on XOSCCR; PLL* enable → EN.
        foreach (var alias in BuildFieldAliasTokens(fn.FunctionName ?? "", member))
            tokens.Add(alias);
        foreach (var acr in BuildCamelAcronymTokens(fn.FunctionName ?? ""))
            tokens.Add(acr);
        if (tokens.Count == 0) return null;

        var scored = new List<(RegisterField Field, int Score)>();
        foreach (var f in fields)
        {
            var score = 0;
            foreach (var t in tokens)
            {
                if (f.Name.Equals(t, StringComparison.OrdinalIgnoreCase))
                    score = Math.Max(score, 100 + t.Length);
                else if (f.Name.StartsWith(t, StringComparison.OrdinalIgnoreCase) && t.Length >= 3)
                    score = Math.Max(score, 60 + t.Length);
                else if (t.StartsWith(f.Name, StringComparison.OrdinalIgnoreCase) && f.Name.Length >= 3)
                    score = Math.Max(score, 50 + f.Name.Length);
                else if (f.Name.Contains(t, StringComparison.OrdinalIgnoreCase) && t.Length >= 4)
                    score = Math.Max(score, 40 + t.Length);
                // Timeout → *TOE on CTOP/ETOP/RTOP/STOP members.
                else if (t.Equals("TOE", StringComparison.OrdinalIgnoreCase)
                         && f.Name.EndsWith("TOE", StringComparison.OrdinalIgnoreCase))
                    score = Math.Max(score, 65);
                // Acronym PED → field PEDT (unique prefix extension on this member).
                else if (t.Length >= 3 && f.Name.Length > t.Length
                         && f.Name.StartsWith(t, StringComparison.OrdinalIgnoreCase)
                         && f.Name.Length <= t.Length + 2)
                    score = Math.Max(score, 70 + t.Length);
            }

            if (score > 0) scored.Add((f, score));
        }

        if (scored.Count == 0) return null;

        var bestScore = scored.Max(x => x.Score);
        var best = scored.Where(x => x.Score == bestScore).ToList();
        // Ambiguous (e.g. AWD matching AWD0/AWD1/AWD2) → refuse rather than guess.
        if (best.Count != 1) return null;

        var field = best[0].Field;
        var label2 = !string.IsNullOrWhiteSpace(field.MskMacroName)
            ? field.MskMacroName!
            : $"{member}_{field.Name}_Msk";
        return new TrustedMask(field.Mask!.Value, label2, "RegisterField:" + field.Name);
    }

    /// <summary>
    /// Resolve trusted mask macro from function name + independent header #defines
    /// (NOT from the SET_BIT/CLEAR_BIT argument in the body).
    /// Examples:
    ///   LL_ADC_AssertPreparingStart → LL_ADC_CFGR1_PREPARING_START_MSK
    ///   LL_ADC_DisableIT_AWDG2 → LL_ADC_IER_AWD2IE (→ ADC0_IER_AWD2IE_Msk)
    /// </summary>
    private static string? TryFindTrustedMaskMacroByFunctionName(
        string? filePath, string functionName, string memberName)
    {
        var tokens = BuildFunctionMaskSearchTokens(functionName);
        if (tokens.Count == 0) return null;

        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);

            // 1) LL_*_MSK composite masks
            // 2) LL_* field aliases: #define LL_ADC_IER_AWD2IE (ADC0_IER_AWD2IE_Msk)
            // 3) Chip *_Msk tokens referenced by those defines
            var llMsk = Regex.Matches(text,
                    @"#define\s+(?<n>LL_[A-Za-z0-9_]+_(?:Msk|MSK))\b",
                    RegexOptions.CultureInvariant)
                .Select(m => m.Groups["n"].Value);
            var llAlias = Regex.Matches(text,
                    @"#define\s+(?<n>LL_[A-Za-z0-9_]+)\s+\(\s*(?<chip>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
                    RegexOptions.CultureInvariant)
                .Select(m => (Name: m.Groups["n"].Value, Chip: m.Groups["chip"].Value))
                .ToList();

            var scored = new List<(string Macro, int Score)>();

            foreach (var n in llMsk.Distinct(StringComparer.OrdinalIgnoreCase))
            {
                var score = ScoreMacroAgainstTokens(n, tokens, memberName);
                if (score > 0) scored.Add((n, score));
            }

            foreach (var a in llAlias)
            {
                // Prefer returning the chip mask when alias matches — ResolveClearMaskAsync handles both.
                var score = Math.Max(
                    ScoreMacroAgainstTokens(a.Name, tokens, memberName),
                    ScoreMacroAgainstTokens(a.Chip, tokens, memberName));
                if (score > 0)
                {
                    // Alias name LL_ADC_IER_AWD2IE scores member IER; return chip for direct field resolve.
                    scored.Add((a.Chip, score + 1));
                    scored.Add((a.Name, score));
                }
            }

            if (scored.Count == 0) return null;
            return scored
                .OrderByDescending(x => x.Score)
                .ThenBy(x => x.Macro.Length)
                .Select(x => x.Macro)
                .First();
        }
        catch
        {
            return null;
        }
    }

    /// <summary>
    /// LL_ADC_DisableIT_AWDG2 → {AWDG2, AWD2, AWD2IE, IT_AWDG2, …}
    /// LL_ADC_AssertPreparingStart → {PREPARING_START, PREPARINGSTART, …}
    /// LL_ADC_ClearFlag_AWD1 (comment AWDG0) → prefer AWD0 over AWD1
    /// </summary>
    private static List<string> BuildFunctionMaskSearchTokens(string functionName)
    {
        var tokens = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        var name = functionName ?? "";

        // SDK quirk: ClearFlag_AWD1/IsActiveFlag_AWD1 comments say AWDG0 and use AWD0_Msk.
        var awdFlag = Regex.Match(name, @"(?:ClearFlag|IsActiveFlag)_AWD(\d+)$", RegexOptions.CultureInvariant);
        if (awdFlag.Success && int.TryParse(awdFlag.Groups[1].Value, out var awdN) && awdN >= 1)
            tokens.Add($"AWD{awdN - 1}");

        name = Regex.Replace(name, @"^LL_", "", RegexOptions.CultureInvariant);
        name = Regex.Replace(name, @"^[A-Z0-9]+_", "", RegexOptions.CultureInvariant);

        foreach (var verb in new[]
                 {
                     "Assert", "Release", "Enable", "Disable", "Set", "Clear", "Get", "Is",
                     "Write", "Read", "Config", "Start", "Stop", "Force", "Trigger", "Trig"
                 })
        {
            if (name.StartsWith(verb, StringComparison.OrdinalIgnoreCase)
                && name.Length > verb.Length
                && (char.IsUpper(name[verb.Length]) || name[verb.Length] == '_'))
            {
                name = name[verb.Length..].TrimStart('_');
                break;
            }
        }

        // Trailing verb leftovers: ProtocolExceptionDetectDisable → ProtocolExceptionDetect
        foreach (var verb in new[] { "Enable", "Disable", "Start", "Stop", "Clear", "Set" })
        {
            if (name.Length > verb.Length
                && name.EndsWith(verb, StringComparison.OrdinalIgnoreCase)
                && char.IsUpper(name[^verb.Length]))
            {
                name = name[..^verb.Length];
                break;
            }
        }

        // Also drop IT_ / Flag_ role prefixes: IT_AWDG2 → AWDG2
        foreach (var role in new[] { "IT_", "Flag_", "FLAG_" })
        {
            if (name.StartsWith(role, StringComparison.OrdinalIgnoreCase))
            {
                tokens.Add(name); // keep IT_AWDG2
                name = name[role.Length..];
                break;
            }
        }

        if (string.IsNullOrWhiteSpace(name)) return tokens.ToList();

        tokens.Add(name);
        tokens.Add(ToSnakeUpper(name));

        if (name.Contains("AllInterrupt", StringComparison.OrdinalIgnoreCase))
        {
            tokens.Add("IT_EN");
            tokens.Add("ALL");
        }

        // Timeout helpers often end with *TOE on the same member.
        if (name.Contains("Timeout", StringComparison.OrdinalIgnoreCase))
            tokens.Add("TOE");

        // Trailing discriminator after underscore: AWDG2
        var us = name.LastIndexOf('_');
        if (us >= 0 && us < name.Length - 1)
            tokens.Add(name[(us + 1)..]);

        // AWDG2 → AWD2 (SDK: function uses AWDGn, masks use AWDnIE)
        foreach (var t in tokens.ToList())
        {
            var compact = Regex.Replace(t, @"AWDG(\d)", "AWD$1", RegexOptions.IgnoreCase);
            if (!string.Equals(compact, t, StringComparison.OrdinalIgnoreCase))
            {
                tokens.Add(compact);
                tokens.Add(compact + "IE");
                tokens.Add(compact + "_IE");
            }

            // EOSMP → EOSMPIE; OVR → OVRIE when looking at IER
            if (t.Length >= 3 && !t.EndsWith("IE", StringComparison.OrdinalIgnoreCase))
                tokens.Add(t + "IE");
        }

        return tokens
            .Where(t => t.Length >= 3)
            .OrderByDescending(t => t.Length)
            .ToList();
    }

    /// <summary>Known SDK name↔field aliases that CamelCase tokens alone miss.</summary>
    private static IEnumerable<string> BuildFieldAliasTokens(string functionName, string member)
    {
        if (functionName.Contains("HSE", StringComparison.OrdinalIgnoreCase)
            && member.Contains("XOSC", StringComparison.OrdinalIgnoreCase))
            yield return "XEN";
        if (functionName.Contains("HSI", StringComparison.OrdinalIgnoreCase)
            && member.Contains("XOSC", StringComparison.OrdinalIgnoreCase))
            yield return "HEN";
        if (Regex.IsMatch(functionName, @"PLL\d", RegexOptions.IgnoreCase)
            && (functionName.Contains("Enable", StringComparison.OrdinalIgnoreCase)
                || functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)))
            yield return "EN";
        if (functionName.Contains("ClearCaptureDirectionError", StringComparison.OrdinalIgnoreCase))
            yield return "CDE";
        if (functionName.Contains("ClearCaptureOverflowError", StringComparison.OrdinalIgnoreCase))
            yield return "COE";
        if (functionName.Contains("ClearSWTrigB", StringComparison.OrdinalIgnoreCase))
            yield return "DONB";
        else if (functionName.Contains("ClearSWTrig", StringComparison.OrdinalIgnoreCase))
            yield return "DON";

        // ADC enable/disable helpers: Channel→CHEN, Reference→REFEN, AnalogWDn→AWD/JAWD.
        if (functionName.Contains("Channel", StringComparison.OrdinalIgnoreCase)
            && !functionName.Contains("Analog", StringComparison.OrdinalIgnoreCase))
            yield return "CHEN";
        if (functionName.Contains("Reference", StringComparison.OrdinalIgnoreCase))
            yield return "REFEN";
        if (Regex.IsMatch(functionName, @"^LL_ADC_Enable$") || Regex.IsMatch(functionName, @"^LL_ADC_Disable$"))
        {
            yield return functionName.Contains("Enable", StringComparison.OrdinalIgnoreCase) ? "ADEN" : "ADDIS";
        }

        var awdMon = Regex.Match(functionName,
            @"AnalogWD(?<n>\d)Monitor(?<kind>Injected|Regular)",
            RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);
        if (awdMon.Success)
        {
            var n = awdMon.Groups["n"].Value;
            yield return awdMon.Groups["kind"].Value.StartsWith("Inj", StringComparison.OrdinalIgnoreCase)
                ? $"JAWD{n}EN"
                : $"AWD{n}EN";
        }

        if (functionName.Contains("StartCalibration", StringComparison.OrdinalIgnoreCase)
            && !functionName.Contains("Mode", StringComparison.OrdinalIgnoreCase))
            yield return "ADCAL";
        if (functionName.Contains("CalibrationMode", StringComparison.OrdinalIgnoreCase))
            yield return "ADCALDIF";
        if (functionName.Contains("OverSamplingRightShift", StringComparison.OrdinalIgnoreCase))
            yield return "OVSS";
        if (functionName.Contains("LoopBackModeExternal", StringComparison.OrdinalIgnoreCase))
            yield return "LBME";
        if (functionName.Contains("LoopBackModeInternal", StringComparison.OrdinalIgnoreCase))
            yield return "LBMI";
        if (functionName.Contains("StandardRemoteFrameReject", StringComparison.OrdinalIgnoreCase))
            yield return "SRFR";
        if (functionName.Contains("ContinuousCountTimeout", StringComparison.OrdinalIgnoreCase))
            yield return "CTOE";
        if (functionName.Contains("AcceptanceFilterMaskIDE", StringComparison.OrdinalIgnoreCase)
            && !functionName.Contains("Extended", StringComparison.OrdinalIgnoreCase)
            && !functionName.Contains("Standard", StringComparison.OrdinalIgnoreCase))
            yield return "AIDEE";
        if (functionName.Contains("ProtocolExceptionDetect", StringComparison.OrdinalIgnoreCase))
            yield return "PEDT";
        if (functionName.Contains("SingleShotMode", StringComparison.OrdinalIgnoreCase))
        {
            if (functionName.Contains("PTB", StringComparison.OrdinalIgnoreCase))
                yield return "TPSS";
            if (functionName.Contains("STB", StringComparison.OrdinalIgnoreCase))
                yield return "TSSS";
        }
        if (functionName.Contains("ETB_", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("Timeout", StringComparison.OrdinalIgnoreCase))
            yield return "ETOE";
        if (functionName.Contains("PRB_", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("Timeout", StringComparison.OrdinalIgnoreCase))
            yield return "RTOE";
        if (functionName.Contains("SRB_", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("Timeout", StringComparison.OrdinalIgnoreCase))
            yield return "STOE";
        if (functionName.Contains("ReleaseBuffer", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("WaitBufferRelease", StringComparison.OrdinalIgnoreCase))
        {
            if (functionName.Contains("ETB_", StringComparison.OrdinalIgnoreCase)) yield return "EREL";
            if (functionName.Contains("PRB_", StringComparison.OrdinalIgnoreCase)) yield return "RREL";
            if (functionName.Contains("SRB_", StringComparison.OrdinalIgnoreCase)) yield return "SREL";
        }
        if (functionName.Contains("OutputInvert", StringComparison.OrdinalIgnoreCase))
            yield return "OPOL";
        if (functionName.Contains("OutputSync", StringComparison.OrdinalIgnoreCase))
            yield return "ODEB";
        if (functionName.Contains("SwBlanking", StringComparison.OrdinalIgnoreCase))
            yield return "CBLK";
        if (functionName.Contains("BypassBufferOutput", StringComparison.OrdinalIgnoreCase))
            yield return "BEN";
        if (functionName.Contains("BufferOutput", StringComparison.OrdinalIgnoreCase)
            && !functionName.Contains("Bypass", StringComparison.OrdinalIgnoreCase))
            yield return "OEN";
        if (functionName.Contains("WaveSawtooth", StringComparison.OrdinalIgnoreCase))
            yield return functionName.Contains("Trig", StringComparison.OrdinalIgnoreCase) ? "SWT" : "STE";
        if (functionName.Contains("WaveTriangle", StringComparison.OrdinalIgnoreCase))
            yield return functionName.Contains("Trig", StringComparison.OrdinalIgnoreCase) ? "SWT" : "TGE";
        if (functionName.Contains("DBusPrefetch", StringComparison.OrdinalIgnoreCase))
            yield return "DPE";
        if (functionName.Contains("IBusPrefetch", StringComparison.OrdinalIgnoreCase))
            yield return "IPE";
        if (functionName.Contains("OverSamplingRatio", StringComparison.OrdinalIgnoreCase))
            yield return "OVSR";
        if (functionName.Contains("OverSamplingScope", StringComparison.OrdinalIgnoreCase))
            yield return "OVERSAMPLING_MODE";
        if (functionName.Contains("OverSamplingDiscont", StringComparison.OrdinalIgnoreCase))
            yield return "TROVS";
        if (functionName.Contains("OverSampling", StringComparison.OrdinalIgnoreCase)
            && (functionName.Contains("Cal", StringComparison.OrdinalIgnoreCase)
                || functionName.Contains("Scale", StringComparison.OrdinalIgnoreCase)))
            yield return "OVSCAL";
        if (functionName.Contains("OverSampling", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("_INJ_", StringComparison.OrdinalIgnoreCase))
            yield return "JOVSE";
        if (functionName.Contains("OverSampling", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("_REG_", StringComparison.OrdinalIgnoreCase))
            yield return "ROVSE";
        if (functionName.Contains("Continuous", StringComparison.OrdinalIgnoreCase)
            && (functionName.Contains("Set", StringComparison.OrdinalIgnoreCase)
                || functionName.Contains("Get", StringComparison.OrdinalIgnoreCase)))
            yield return "CONT";
        if (functionName.Contains("Overrun", StringComparison.OrdinalIgnoreCase))
            yield return "OVRMOD";
        if (functionName.Contains("DiscNum", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("DiscontNum", StringComparison.OrdinalIgnoreCase))
            yield return "DISCNUM";
        if (functionName.Contains("Current", StringComparison.OrdinalIgnoreCase)
            && functionName.Contains("Select", StringComparison.OrdinalIgnoreCase))
            yield return "ISEL";
        if (functionName.Contains("SequencerDiscont", StringComparison.OrdinalIgnoreCase))
            yield return functionName.Contains("_INJ_", StringComparison.OrdinalIgnoreCase) ? "JDISCEN" : "DISCEN";
        if (functionName.Contains("TrigAuto", StringComparison.OrdinalIgnoreCase))
            yield return "JAUTO";
        if (functionName.Contains("StartConversion", StringComparison.OrdinalIgnoreCase))
            yield return functionName.Contains("_INJ_", StringComparison.OrdinalIgnoreCase) ? "JADSTART" : "ADSTART";
        if (functionName.Contains("StopConversion", StringComparison.OrdinalIgnoreCase))
            yield return functionName.Contains("_INJ_", StringComparison.OrdinalIgnoreCase) ? "JADSTP" : "ADSTP";
        // IsEnabled / IsActiveADC-style getters on CR.ADEN (not IT_* / Flag_*).
        if (Regex.IsMatch(functionName, @"LL_ADC_IsEnabled$")
            || Regex.IsMatch(functionName, @"LL_ADC_IsActive$"))
            yield return "ADEN";

        // CAN mode bits often abbreviated: ListenOnly→LOM, FD→FD_EN / FD.
        if (functionName.Contains("ListenOnly", StringComparison.OrdinalIgnoreCase))
            yield return "LOM";
        if (functionName.Contains("EnableFD", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("DisableFD", StringComparison.OrdinalIgnoreCase))
        {
            yield return "FD_EN";
            yield return "FD";
        }
        if (functionName.Contains("ExtendedRemoteFrameReject", StringComparison.OrdinalIgnoreCase))
            yield return "ERFR";
    }

    private static string ToSnakeUpper(string name)
    {
        var sb = new System.Text.StringBuilder();
        for (var i = 0; i < name.Length; i++)
        {
            var c = name[i];
            if (c == '_')
            {
                sb.Append('_');
                continue;
            }

            if (i > 0 && char.IsUpper(c)
                && (char.IsLower(name[i - 1]) || (i + 1 < name.Length && char.IsLower(name[i + 1]))))
                sb.Append('_');
            sb.Append(char.ToUpperInvariant(c));
        }

        return sb.ToString();
    }

    /// <summary>
    /// CamelCase remainder → acronym tokens (LoopBackModeExternal → LBME).
    /// </summary>
    private static IEnumerable<string> BuildCamelAcronymTokens(string functionName)
    {
        var tokens = BuildFunctionMaskSearchTokens(functionName);
        // Prefer the longest CamelCase-looking token without underscores.
        foreach (var t in tokens.Where(x => x.Length >= 4 && !x.Contains('_')).Take(3))
        {
            var parts = SplitCamelCaseWords(t);
            if (parts.Count < 2) continue;
            var acr = string.Concat(parts.Select(p => char.ToUpperInvariant(p[0])));
            if (acr.Length >= 2)
                yield return acr;
            // Drop short buffer prefix: ETB_ReleaseBuffer handled via aliases; here
            // ProtocolExceptionDetect → PED.
            if (parts.Count >= 3 && parts[0].Length <= 3)
            {
                var acr2 = string.Concat(parts.Skip(1).Select(p => char.ToUpperInvariant(p[0])));
                if (acr2.Length >= 2)
                    yield return acr2;
            }
        }
    }

    private static List<string> SplitCamelCaseWords(string name)
    {
        var parts = new List<string>();
        if (string.IsNullOrEmpty(name)) return parts;
        var start = 0;
        for (var i = 1; i < name.Length; i++)
        {
            if (!char.IsUpper(name[i])) continue;
            // USBHost → USB, Host ; AWDG2 → keep with digits on previous
            if (char.IsUpper(name[i - 1])
                && (i + 1 >= name.Length || char.IsUpper(name[i + 1])))
                continue;
            parts.Add(name[start..i]);
            start = i;
        }

        parts.Add(name[start..]);
        return parts.Where(p => p.Length > 0).ToList();
    }

    private static int ScoreMacroAgainstTokens(string macro, List<string> tokens, string memberName)
    {
        var score = 0;
        foreach (var t in tokens)
        {
            if (macro.Contains(t, StringComparison.OrdinalIgnoreCase))
                score = Math.Max(score, 10 + t.Length);
        }

        if (score == 0) return 0;

        if (!string.IsNullOrEmpty(memberName)
            && (macro.Contains($"_{memberName}_", StringComparison.OrdinalIgnoreCase)
                || macro.Contains($"_{memberName}", StringComparison.OrdinalIgnoreCase)
                || macro.StartsWith($"{memberName}_", StringComparison.OrdinalIgnoreCase)))
            score += 20;

        // Prefer precise field masks over huge composite OR masks.
        if (macro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase)
            && macro.Contains("_IT_", StringComparison.OrdinalIgnoreCase)
            && macro.Contains("ALL", StringComparison.OrdinalIgnoreCase))
            score -= 50;

        return score;
    }

    private static string PathLeaf(Match m)
    {
        if (m.Groups["path"].Success && TryParseRegAccessPath(m.Groups["path"].Value, out var parsed))
            return parsed.LeafMember;
        if (m.Groups["mem"].Success)
            return m.Groups["mem"].Value;
        return "";
    }

    /// <summary>
    /// MODIFY_REG cases using CMSIS semantics:
    /// <c>expected = (initial &amp; ~clearMask) | setMask</c>.
    /// Supports flat <c>reg-&gt;MEM</c>, nested <c>Master.MCR0</c>, and array
    /// <c>PWM[(Idx)%N].REG.MEM</c> for any peripheral (instance from chip mask peri prefix).
    /// </summary>
    private static async Task<List<LlTestCaseEditModel>> TryBuildModifyRegWriteCasesAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        CancellationToken ct)
    {
        var results = new List<LlTestCaseEditModel>();
        if (!IsLikelyRegisterSetter(fn.FunctionName))
            return results;

        var liveBody = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        if (string.IsNullOrWhiteSpace(liveBody))
            return results;

        var liveFull = ModifyRegFullPattern.Match(liveBody);
        Match? simple = null;
        if (!liveFull.Success)
        {
            simple = ModifyRegPattern.Match(liveBody);
            if (!simple.Success)
                return results;
        }

        var pathText = liveFull.Success ? liveFull.Groups["path"].Value : simple!.Groups["path"].Value;
        if (!TryParseRegAccessPath(pathText, out var accessPath))
            return results;

        var bodyMember = accessPath.LeafMember;
        var bodyMskMacro = liveFull.Success ? liveFull.Groups["msk"].Value : simple!.Groups["msk"].Value;
        var rhs = liveFull.Success ? liveFull.Groups["rhs"].Value : "";
        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var modifyPairNote);

        if (!TryFieldNameFromMskMacro(bodyMskMacro, member, out var fieldName)
            && !TryParseChipMaskRegAndField(bodyMskMacro, out _, out fieldName))
            fieldName = bodyMskMacro;

        var fieldDef = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
        var posMacroFromRhs = Regex.Match(rhs, @"\b(?<pos>[A-Za-z0-9_]+_Pos)\b");
        var posMacro = posMacroFromRhs.Success ? posMacroFromRhs.Groups["pos"].Value : null;
        if (!TryResolveFieldMaskPos(fn.FilePath, fieldDef, bodyMskMacro, posMacro, out var clearMask, out var pos)
            || clearMask == 0)
        {
            clearMask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
            if (clearMask == 0)
                return results;
            pos = fieldDef?.BitPosition ?? PosFromMask(clearMask);
        }

        var isFieldValueStyle = rhs.Contains("<<", StringComparison.Ordinal)
            && (rhs.Contains("_Val", StringComparison.OrdinalIgnoreCase)
                || rhs.Contains("_Pos", StringComparison.OrdinalIgnoreCase)
                || Regex.IsMatch(rhs, @"\(\s*\(?\s*[A-Za-z_][A-Za-z0-9_]*\s*\)?\s*<<"));

        uint? valClamp = null;
        var valTok = Regex.Match(rhs, @"&\s*(?<val>[A-Za-z0-9_]+_Val)\b");
        if (valTok.Success)
        {
            foreach (var path in CandidateDefineFiles(fn.FilePath, fieldDef))
            {
                if (TryParseUintDefineFromFile(path, valTok.Groups["val"].Value, out var vv) && vv != 0)
                {
                    valClamp = vv;
                    break;
                }
            }

            // CONT_Val = Msk>>Pos often not a literal — derive from clearMask.
            if (valClamp is null or 0)
                valClamp = clearMask >> pos;
        }

        var maxField = clearMask >> pos;
        if (maxField == 0 && isFieldValueStyle)
            return results;

        IEnumerable<(string Tag, uint Param, bool Interference)> samples;
        if (isFieldValueStyle)
        {
            samples = EnumerateFieldReadSamples(maxField)
                .Select(s => (s.Tag, s.FieldValue, s.Interference));
        }
        else
        {
            samples = EnumerateModifyMaskArgSamples(clearMask);
        }

        // Array expansion: Idx % NUMS (any module — not HRPWM-only).
        var arrayBound = ResolveArrayBound(accessPath.ArrayIndexExpr, fn.FilePath);
        IReadOnlyList<uint> channelSamples = accessPath.ArrayIndexExpr is not null
            ? new uint[] { 0, 1, 2, arrayBound > 0 ? arrayBound - 1 : 0, arrayBound, arrayBound + 1 }
            : new uint[] { 0 };

        foreach (var channelRaw in channelSamples.Distinct())
        {
            var channelIndex = accessPath.ArrayIndexExpr is not null
                ? channelRaw % Math.Max(1u, arrayBound)
                : 0u;
            var targetInstance = ResolveNestedInstance(instance, accessPath, channelIndex, bodyMskMacro);

            foreach (var (tag, paramRaw, withInterference) in samples)
            {
                uint paramBits;
                uint setMask;
                if (isFieldValueStyle)
                {
                    paramBits = valClamp is uint vc ? paramRaw & vc : paramRaw;
                    setMask = (paramBits << pos) & clearMask;
                }
                else
                {
                    paramBits = paramRaw & clearMask;
                    setMask = paramBits;
                }

                var preserveBits = withInterference ? PickUnrelatedPreserveBits(clearMask) : 0u;
                var oldFieldBits = (~setMask) & clearMask;
                if (oldFieldBits == 0 && clearMask != 0 && setMask != clearMask)
                    oldFieldBits = clearMask;
                var initial = preserveBits | oldFieldBits;
                var expected = ComputeModifyRegExpected(initial, clearMask, setMask);
                EnsureModifyExpectationConsistent($"{targetInstance}.{member}", initial, clearMask, setMask, expected);

                var parameters = baseParams.Select(p => new LlTestParameterValue
                {
                    Name = p.Name,
                    Type = p.Type,
                    ValueExpression = p.ValueExpression,
                    RuleSource = p.RuleSource
                }).ToList();

                // Host peri pointer: multi-bank TypeDef modules use module cast (HRPWM), else default instance.
                foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
                {
                    p.ValueExpression = ResolveHostPeriPointer(
                        fn.PeripheralName, instance, targetInstance, p.ValueExpression);
                }

                // Index param: prefer name appearing in the C index expression.
                if (accessPath.ArrayIndexExpr is not null)
                {
                    var idxNames = Regex.Matches(accessPath.ArrayIndexExpr, @"\b([A-Za-z_][A-Za-z0-9_]*)\b")
                        .Select(m => m.Groups[1].Value)
                        .Where(id => !id.StartsWith("LL_", StringComparison.Ordinal)
                                     && !id.Equals("U", StringComparison.OrdinalIgnoreCase)
                                     && !id.Equals("UL", StringComparison.OrdinalIgnoreCase))
                        .ToHashSet(StringComparer.OrdinalIgnoreCase);
                    var chParam = parameters.FirstOrDefault(p =>
                        !p.Type.Contains('*', StringComparison.Ordinal)
                        && idxNames.Contains(p.Name));
                    chParam ??= parameters.FirstOrDefault(p =>
                        !p.Type.Contains('*', StringComparison.Ordinal)
                        && (p.Name.Contains("Pwm", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Contains("Ch", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Contains("Idx", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Contains("Index", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Contains("Unit", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Contains("Tim", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)));

                    if (chParam is not null
                        && !chParam.Name.Contains("Mode", StringComparison.OrdinalIgnoreCase)
                        && !chParam.Name.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
                        && !chParam.Name.Contains("Value", StringComparison.OrdinalIgnoreCase))
                    {
                        chParam.ValueExpression = channelRaw.ToString();
                        chParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                    }
                }

                var indexParamNames = accessPath.ArrayIndexExpr is null
                    ? new HashSet<string>(StringComparer.OrdinalIgnoreCase)
                    : Regex.Matches(accessPath.ArrayIndexExpr, @"\b([A-Za-z_][A-Za-z0-9_]*)\b")
                        .Select(m => m.Groups[1].Value)
                        .ToHashSet(StringComparer.OrdinalIgnoreCase);

                var modeParam = parameters.LastOrDefault(p =>
                    !p.Type.Contains('*', StringComparison.Ordinal)
                    && !indexParamNames.Contains(p.Name)
                    && (p.Name.Contains("Mode", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Contains("Value", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Contains("Div", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Contains("Data", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Contains("Cfg", StringComparison.OrdinalIgnoreCase)));
                if (modeParam is null)
                {
                    modeParam = parameters.LastOrDefault(p =>
                        !p.Type.Contains('*', StringComparison.Ordinal)
                        && !indexParamNames.Contains(p.Name));
                }

                if (modeParam is not null)
                {
                    modeParam.ValueExpression = $"0x{paramBits:X}";
                    modeParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }

                var channelTag = accessPath.ArrayIndexExpr is not null
                    ? $"ch{channelRaw}->SLV{channelIndex}"
                    : (accessPath.NestedPrefix ?? "flat");
                var fieldLabel = fieldName;
                var model = BaseModel(fn);
                model.Name =
                    $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/{channelTag}/{tag}/write-check";
                model.Status = nameof(LlTestCaseStatus.Ready);
                model.IsAutoGenerated = true;
                model.Parameters = parameters;
                model.InitialRegisters =
                [
                    new LlTestInitialRegister
                    {
                        InstanceName = targetInstance,
                        MemberName = member,
                        ValueHex = $"0x{initial:X}"
                    }
                ];

                var assertions = new List<LlTestAssertionSpec>
                {
                    new()
                    {
                        Kind = LlAssertionKind.RegisterWrite,
                        InstanceName = targetInstance,
                        MemberName = member,
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail = $"必须写入 {targetInstance}.{member}（无 Get；轨迹校验）"
                    },
                    new()
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedHex = $"0x{expected:X}",
                        ExpectedMask = 0xFFFFFFFFu,
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail =
                            $"MODIFY_REG：(initial=0x{initial:X} & ~0x{clearMask:X}) | 0x{setMask:X} = 0x{expected:X}；" +
                            $"Param=0x{paramBits:X}；path={accessPath.RawPath}；{modifyPairNote}；体宏 {bodyMskMacro} pos={pos}"
                    },
                    new()
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedHex = $"0x{setMask:X}",
                        ExpectedMask = clearMask,
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail = $"目标位域：(actual & 0x{clearMask:X}) == 0x{setMask:X}"
                    }
                };

                if (preserveBits != 0)
                {
                    assertions.Add(new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.PreserveBits,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedHex = $"0x{preserveBits:X}",
                        ExpectedMask = preserveBits,
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail =
                            $"保留位：(actual & ~0x{clearMask:X}) == (initial & ~0x{clearMask:X}) = 0x{preserveBits:X}"
                    });
                }

                if (!string.IsNullOrWhiteSpace(fieldName)
                    && !fieldName.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
                    && clearMask != 0)
                {
                    var bfExpected = (setMask & clearMask) >> pos;
                    var fieldWidth = BitWidthFromMask(clearMask);
                    assertions.Add(new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.BitField,
                        InstanceName = targetInstance,
                        MemberName = member,
                        BitFieldName = fieldName,
                        ExpectedHex = $"0x{bfExpected:X}",
                        ExpectedMask = clearMask,
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail =
                            $"BitField {fieldName}: Expected=(SetMask&FieldMask)>>Pos；" +
                            $"ParamRaw=0x{paramBits:X} SetMask=0x{setMask:X} FieldMask=0x{clearMask:X} " +
                            $"Pos={pos} Width={fieldWidth} BitFieldExpected=0x{bfExpected:X}" +
                            (fieldDef?.Mask is uint dbm && dbm != clearMask
                                ? $"；已忽略 DB.Mask=0x{dbm:X}"
                                : "")
                    });
                }

                if (accessPath.ArrayIndexExpr is not null)
                {
                    assertions.Add(new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.ArrayIndex,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedHex = channelIndex.ToString(),
                        ExpectedExpression = $"{accessPath.ArrayIndexExpr} → {channelRaw}%{arrayBound}={channelIndex}",
                        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                        RuleSourceDetail =
                            $"数组索引：raw={channelRaw} → index={channelIndex} → {targetInstance}"
                    });
                }

                assertions.Add(new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.NoUnexpectedWrite,
                    InstanceName = targetInstance,
                    MemberName = member,
                    ExpectedAccessOrder = new[] { $"{targetInstance}.{member}", member },
                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                    RuleSourceDetail = "禁止意外修改其他寄存器（LL 归因写入）"
                });

                assertions.AddRange(DefaultTimeoutAssertions());
                model.Assertions = assertions;
                model.Notes =
                    $"自动 MODIFY[{tag}/{channelTag}]：path={accessPath.RawPath} " +
                    $"Target={targetInstance}.{member} Initial=0x{initial:X} Param=0x{paramBits:X} " +
                    $"ClearMask=0x{clearMask:X} SetMask=0x{setMask:X} Expected=0x{expected:X} " +
                    $"（无 Get；虚拟寄存器最终态 + 轨迹）。";
                results.Add(model);

                // Keep case volume bounded for array paths: one mode sample per channel is enough for edges.
                if (accessPath.ArrayIndexExpr is not null)
                    break;
            }
        }

        return results;
    }

    /// <summary>CMSIS MODIFY_REG: (REG &amp; ~CLEARMASK) | SETMASK</summary>
    private static uint ComputeModifyRegExpected(uint initial, uint clearMask, uint setMask)
        => (initial & ~clearMask) | (setMask & clearMask);

    private static void EnsureModifyExpectationConsistent(
        string registerName, uint initial, uint clearMask, uint setMask, uint expected)
    {
        var derived = ComputeModifyRegExpected(initial, clearMask, setMask);
        if (derived != expected)
        {
            throw new InvalidOperationException(
                $"MODIFY 用例生成不一致，禁止执行：{registerName} " +
                $"initial=0x{initial:X} clear=0x{clearMask:X} set=0x{setMask:X} " +
                $"expected=0x{expected:X} but CMSIS=0x{derived:X}");
        }
    }

    private static IEnumerable<(string Tag, uint Param, bool Interference)> EnumerateModifyMaskArgSamples(uint clearMask)
    {
        yield return ("zero", 0u, true);
        yield return ("one", 1u & clearMask, true);
        if (clearMask > 2)
            yield return ("mid", (clearMask >> 1) & clearMask, true);
        yield return ("max", clearMask, true);
        yield return ("one-clean", 1u & clearMask, false);
    }

    private static bool TryTrustedFieldName(TrustedMask trusted, string member, out string fieldName)
    {
        // RegisterField:ADCALDIF / RegisterFieldAwdMap:AWD0
        var src = trusted.Source;
        var colon = src.IndexOf(':');
        if (colon > 0
            && (src.StartsWith("RegisterField", StringComparison.OrdinalIgnoreCase)
                || src.StartsWith("RegisterFieldAwdMap", StringComparison.OrdinalIgnoreCase)))
        {
            fieldName = src[(colon + 1)..];
            return !string.IsNullOrWhiteSpace(fieldName);
        }

        return TryFieldNameFromMskMacro(trusted.Label, member, out fieldName);
    }

    /// <summary>
    /// Resolve trusted register member for READ_REG from function name
    /// (e.g. GetConfigEx → CFGR1; GetRegularSequence → SQR0).
    /// </summary>
    private static async Task<string?> TryResolveTrustedMemberAsync(
        AppDbContext db, LlFunction fn, CancellationToken ct)
    {
        var alias = TryTrustedMemberAlias(fn.FunctionName ?? "");
        if (alias is not null)
            return alias;

        var members = await db.RegisterDefinitions.AsNoTracking()
            .Where(r => r.SdkProjectId == fn.SdkProjectId
                        && r.MemberName != null && r.MemberName != "")
            .Select(r => r.MemberName!)
            .Distinct()
            .ToListAsync(ct);
        if (members.Count == 0) return null;

        var tokens = BuildFunctionMaskSearchTokens(fn.FunctionName ?? "");
        if (tokens.Count == 0) return null;

        var scored = new List<(string Member, int Score)>();
        foreach (var mem in members)
        {
            var score = 0;
            foreach (var t in tokens)
            {
                if (mem.Equals(t, StringComparison.OrdinalIgnoreCase))
                    score = Math.Max(score, 100 + t.Length);
                else if (mem.StartsWith(t, StringComparison.OrdinalIgnoreCase) && t.Length >= 3)
                    score = Math.Max(score, 60 + t.Length);
                else if (t.StartsWith(mem, StringComparison.OrdinalIgnoreCase) && mem.Length >= 3)
                    score = Math.Max(score, 50 + mem.Length);
                else if (mem.Contains(t, StringComparison.OrdinalIgnoreCase) && t.Length >= 4)
                    score = Math.Max(score, 40 + t.Length);
            }

            if (score > 0) scored.Add((mem, score));
        }

        if (scored.Count == 0) return null;
        var bestScore = scored.Max(x => x.Score);
        var best = scored.Where(x => x.Score == bestScore).ToList();
        return best.Count == 1 ? best[0].Member : null;
    }

    private static string? TryTrustedMemberAlias(string functionName)
    {
        if (functionName.Contains("ConfigEx", StringComparison.OrdinalIgnoreCase))
            return "CFGR1";
        if (functionName.Contains("GetConfig", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("SetConfig", StringComparison.OrdinalIgnoreCase))
            return "CFGR0";
        if (functionName.Contains("RegularSequence", StringComparison.OrdinalIgnoreCase))
            return "SQR0";
        if (functionName.Contains("DifferEnd", StringComparison.OrdinalIgnoreCase))
            return "SIGSEL";
        if (functionName.Contains("AllCpltEnabledIT", StringComparison.OrdinalIgnoreCase))
            return "FIER";
        if (functionName.Contains("AllCpltITPending", StringComparison.OrdinalIgnoreCase))
            return "FISR";
        if (functionName.Contains("AllHalfCpltEnabledIT", StringComparison.OrdinalIgnoreCase))
            return "HIER";
        if (functionName.Contains("AllHalfCpltITPending", StringComparison.OrdinalIgnoreCase))
            return "HISR";
        if (functionName.Contains("AllSampleEnabledIT", StringComparison.OrdinalIgnoreCase))
            return "DIER";
        if (functionName.Contains("AllSampleITPending", StringComparison.OrdinalIgnoreCase))
            return "DISR";
        if (functionName.Contains("NormalChannelsITPending", StringComparison.OrdinalIgnoreCase))
            return "ISR";
        if (functionName.Contains("NormAllInterruptEnable", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("GetNormAllInterruptEnable", StringComparison.OrdinalIgnoreCase))
            return "IER";
        return null;
    }

    /// <summary>
    /// Get/Is/Read cases: expected return is ALWAYS derived from the same InitialRegisterValue
    /// via <c>(initial &amp; mask) &gt;&gt; pos</c>. Never invent expected independently of preload.
    /// </summary>
    private static async Task<List<LlTestCaseEditModel>> TryBuildReadPreparedCasesAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        CancellationToken ct)
    {
        var results = new List<LlTestCaseEditModel>();
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        if (string.IsNullOrWhiteSpace(body))
            return results;

        List<LlTestParameterValue> CloneParams() => baseParams.Select(p => new LlTestParameterValue
        {
            Name = p.Name,
            Type = p.Type,
            ValueExpression = p.ValueExpression,
            RuleSource = p.RuleSource
        }).ToList();

        // Channel-indexed BIT(Ch) flag.
        var chBit = ReadBitShiftChannelBitPattern.Match(body);
        if (chBit.Success)
        {
            var member = chBit.Groups["mem"].Value;
            const uint ch = 3;
            var bitMask = 1u << (int)ch;
            var preserve = PickUnrelatedPreserveBits(bitMask);
            var preloadFull = bitMask | preserve;
            var expected = (preloadFull & bitMask) >> (int)ch;
            EnsureReadExpectationConsistent($"{instance}.{member}", preloadFull, bitMask, (int)ch, expected);

            var parameters = CloneParams();
            var chParam = parameters.FirstOrDefault(p =>
                !p.Type.Contains('*', StringComparison.Ordinal)
                && (p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Channel", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Pin", StringComparison.OrdinalIgnoreCase)));
            chParam ??= parameters.FirstOrDefault(p => !p.Type.Contains('*', StringComparison.Ordinal));
            if (chParam is not null)
            {
                chParam.ValueExpression = ch.ToString();
                chParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }

            results.Add(BuildReadCheckModel(
                fn, instance, parameters, member, preloadFull, expected,
                nameSuffix: $"{member}.BIT{ch}/read-check",
                detail:
                $"Ch={ch}；Initial=0x{preloadFull:X} Mask=0x{bitMask:X} Pos={ch} Expected=0x{expected:X}",
                notes:
                $"自动读校验：Ch={ch}，InitialRegisterValue=0x{preloadFull:X}，ExpectedReturn=(initial&mask)>>pos=0x{expected:X}。虚拟环境。"));
            return results;
        }

        // READ_BIT_SHIFT / (READ_BIT >> Pos) field-value getters.
        // Prefer BODY mask/pos (what the compiled LL actually uses).
        var shift = ReadBitShiftPattern.Match(body);
        if (!shift.Success)
            shift = ReadBitThenShiftPattern.Match(body);
        if (shift.Success)
        {
            var bodyMember = shift.Groups["mem"].Value;
            var bodyMskMacro = shift.Groups["msk"].Value;
            var bodyPosMacro = shift.Groups["pos"].Success ? shift.Groups["pos"].Value : null;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var readPairNote);

            if (!TryFieldNameFromMskMacro(bodyMskMacro, member, out var fieldName))
                return results;

            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (!TryResolveFieldMaskPos(fn.FilePath, field, bodyMskMacro, bodyPosMacro, out var mask, out var pos))
                return results;

            var maxVal = mask >> pos;
            if (maxVal == 0) return results;

            var fieldSource = $"体宏 {bodyMskMacro}/{bodyPosMacro ?? $"pos={pos}"}";
            foreach (var (tag, fieldValue, withInterference) in EnumerateFieldReadSamples(maxVal))
            {
                var initial = BuildFieldReadInitial(fieldValue, mask, pos, withInterference);
                var expected = DeriveFieldReadExpected(initial, mask, pos);
                EnsureReadExpectationConsistent($"{instance}.{member}.{fieldName}", initial, mask, pos, expected);
                if (expected != fieldValue)
                {
                    // Interference must never bleed into the field — generator bug.
                    throw new InvalidOperationException(
                        $"读用例字段干扰位泄漏：{member}.{fieldName} fieldValue=0x{fieldValue:X} " +
                        $"initial=0x{initial:X} → derived=0x{expected:X}");
                }

                results.Add(BuildReadCheckModel(
                    fn, instance, CloneParams(), member, initial, expected,
                    nameSuffix: $"{member}.{fieldName}/{tag}/read-check",
                    detail:
                    $"Register={instance}.{member} Field={fieldName} Initial=0x{initial:X} " +
                    $"Mask=0x{mask:X} Pos={pos} ExpectedReturn=0x{expected:X}（{fieldSource}；{readPairNote}）",
                    notes:
                    $"自动读校验[{tag}]：InitialRegisterValue=0x{initial:X}；" +
                    $"ExpectedReturn=(initial&0x{mask:X})>>{pos}=0x{expected:X}；读后寄存器不变。虚拟环境。"));
            }

            return results;
        }

        // Boolean READ_BIT(..._Msk) ? 1 : 0
        var bitBool = ReadBitBoolPattern.Match(body);
        if (bitBool.Success && body.Contains("? 1UL", StringComparison.Ordinal))
        {
            var bodyMember = bitBool.Groups["mem"].Value;
            var bodyMskMacro = bitBool.Groups["msk"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var boolPairNote);
            if (!TryFieldNameFromMskMacro(bodyMskMacro, member, out var fieldName))
                return results;

            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (!TryResolveFieldMaskPos(fn.FilePath, field, bodyMskMacro, posMacro: null, out var mask, out _))
                return results;

            var invert = body.Contains("(!READ_BIT", StringComparison.Ordinal)
                         || body.Contains("(! READ_BIT", StringComparison.Ordinal);
            var preserve = PickUnrelatedPreserveBits(mask);
            // true-case and false-case
            foreach (var (tag, setFlag) in new[] { ("true", !invert), ("false", invert) })
            {
                var initial = setFlag ? (mask | preserve) : preserve;
                var expected = invert
                    ? ((initial & mask) == 0 ? 1u : 0u)
                    : ((initial & mask) != 0 ? 1u : 0u);
                results.Add(BuildReadCheckModel(
                    fn, instance, CloneParams(), member, initial, expected,
                    nameSuffix: $"{member}.{fieldName}/{tag}/read-check",
                    detail:
                    $"布尔读：Initial=0x{initial:X} Mask=0x{mask:X} Expected=0x{expected:X}（{boolPairNote}）",
                    notes:
                    $"自动读校验（布尔/{tag}）：Initial=0x{initial:X} Expected=0x{expected:X}；读后不变。虚拟环境。"));
            }

            return results;
        }

        // Full register READ_REG
        var readReg = ReadRegPattern.Match(body);
        if (readReg.Success && !body.Contains("LL_ADC_REG_OFFSET", StringComparison.Ordinal)
            && !body.Contains("OFFSET", StringComparison.Ordinal))
        {
            var bodyMember = readReg.Groups["mem"].Value;
            var trustedMember = await TryResolveTrustedMemberAsync(db, fn, ct);
            var member = !string.IsNullOrWhiteSpace(trustedMember) ? trustedMember! : bodyMember;
            foreach (var (tag, preload) in new[]
                     {
                         ("zero", 0u),
                         ("pattern", 0xA5A55A5Au),
                         ("ones", 0xFFFFFFFFu)
                     })
            {
                var expected = preload; // READ_REG returns full value
                results.Add(BuildReadCheckModel(
                    fn, instance, CloneParams(), member, preload, expected,
                    nameSuffix: $"{member}/{tag}/read-check",
                    detail: $"READ_REG：Initial=0x{preload:X} Expected=0x{expected:X}",
                    notes: $"自动读校验[READ_REG/{tag}]：Initial=Expected=0x{preload:X}；读后不变。虚拟环境。"));
            }
        }

        return results;
    }

    private static LlTestCaseEditModel BuildReadCheckModel(
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> parameters,
        string member,
        uint initial,
        uint expectedReturn,
        string nameSuffix,
        string detail,
        string notes)
    {
        var model = BaseModel(fn);
        model.Name = $"{fn.FunctionName}/{instance}/{nameSuffix}";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance,
                MemberName = member,
                ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            ReturnValueAssertion($"0x{expectedReturn:X}", detail),
            RegisterUnchangedAfterReadAssertion(instance, member, initial),
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = notes;
        return model;
    }

    /// <summary>expected = (initial &amp; mask) &gt;&gt; pos</summary>
    private static uint DeriveFieldReadExpected(uint initial, uint mask, int pos)
        => pos is >= 0 and < 32 ? (initial & mask) >> pos : initial & mask;

    private static void EnsureReadExpectationConsistent(
        string registerName, uint initial, uint mask, int pos, uint expected)
    {
        var derived = DeriveFieldReadExpected(initial, mask, pos);
        if (derived != expected)
        {
            throw new InvalidOperationException(
                $"读用例生成不一致，禁止执行：{registerName} " +
                $"InitialRegisterValue=0x{initial:X} FieldMask=0x{mask:X} FieldPosition={pos} " +
                $"ExpectedReturnValue=0x{expected:X} 但 (initial&mask)>>pos=0x{derived:X}");
        }
    }

    private static uint BuildFieldReadInitial(uint fieldValue, uint mask, int pos, bool withInterference)
    {
        var fieldBits = (fieldValue << pos) & mask;
        if (!withInterference) return fieldBits;
        return fieldBits | PickUnrelatedPreserveBits(mask);
    }

    private static IEnumerable<(string Tag, uint FieldValue, bool Interference)> EnumerateFieldReadSamples(uint maxVal)
    {
        yield return ("min", 0u, true);
        if (maxVal >= 1)
            yield return ("one", 1u, true);
        if (maxVal > 2)
            yield return ("mid", maxVal / 2u, true);
        yield return ("max", maxVal, true);
        // Boundary: max-1 when distinct
        if (maxVal > 1)
            yield return ("nearmax", maxVal - 1u, true);
        // Clean (no interference) non-zero
        if (maxVal >= 1)
            yield return ("one-clean", 1u, false);
    }

    private static int PosFromMask(uint mask)
    {
        if (mask == 0) return 0;
        var pos = 0;
        while ((mask & 1u) == 0 && pos < 31)
        {
            mask >>= 1;
            pos++;
        }
        return pos;
    }

    private static int BitWidthFromMask(uint mask)
    {
        if (mask == 0) return 0;
        var shifted = mask >> PosFromMask(mask);
        var width = 0;
        while (shifted != 0 && width < 32)
        {
            shifted >>= 1;
            width++;
        }
        return width;
    }

    /// <summary>
    /// Resolve mask/pos from SDK #define literals when possible; fall back to DB RegisterField.
    /// </summary>
    private static bool TryResolveFieldMaskPos(
        string? llFilePath,
        RegisterField? field,
        string mskMacro,
        string? posMacro,
        out uint mask,
        out int pos)
    {
        mask = 0;
        pos = 0;
        posMacro ??= Regex.Replace(mskMacro, "_Msk$", "_Pos", RegexOptions.IgnoreCase);

        foreach (var path in CandidateDefineFiles(llFilePath, field))
        {
            if (!TryParseUintDefineFromFile(path, mskMacro, out var m) || m == 0)
                continue;
            mask = m;
            if (TryParseUintDefineFromFile(path, posMacro, out var p))
                pos = (int)p;
            else
                pos = PosFromMask(mask);
            return true;
        }

        if (field?.Mask is uint fm && fm != 0)
        {
            mask = fm;
            pos = field.BitPosition ?? PosFromMask(mask);
            return true;
        }

        return false;
    }

    private static IEnumerable<string> CandidateDefineFiles(string? llFilePath, RegisterField? field)
    {
        var seen = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        if (!string.IsNullOrWhiteSpace(field?.DefinitionFile))
        {
            var f = field!.DefinitionFile!;
            if (File.Exists(f) && seen.Add(Path.GetFullPath(f)))
                yield return Path.GetFullPath(f);
        }

        var ll = ResolveLlHeaderPath(llFilePath);
        if (ll is not null && seen.Add(ll))
            yield return ll;

        if (ll is not null)
        {
            // Walk up to SDK Drivers and probe Device/Inc chip headers.
            var dir = new DirectoryInfo(Path.GetDirectoryName(ll)!);
            for (var i = 0; i < 6 && dir is not null; i++, dir = dir.Parent)
            {
                foreach (var name in new[]
                         {
                             "tae32g58xx_chip.h", "tae32g58xx_chip_struct.h", "tae32g58xx.h"
                         })
                {
                    var probes = new[]
                    {
                        Path.Combine(dir.FullName, name),
                        Path.Combine(dir.FullName, "Inc", name),
                        Path.Combine(dir.FullName, "TAE32G58xx_Device", "Inc", name),
                        Path.Combine(dir.FullName, "Drivers", "TAE32G58xx_Device", "Inc", name),
                    };
                    foreach (var p in probes)
                    {
                        if (File.Exists(p))
                        {
                            var full = Path.GetFullPath(p);
                            if (seen.Add(full))
                                yield return full;
                        }
                    }
                }
            }
        }
    }

    private static bool TryParseUintDefineFromFile(string filePath, string macroName, out uint value)
    {
        value = 0;
        try
        {
            var text = File.ReadAllText(filePath);
            var m = Regex.Match(text,
                $@"#define\s+{Regex.Escape(macroName)}\s+(?<body>(?:.*\\\r?\n)*.*)",
                RegexOptions.CultureInvariant);
            if (!m.Success) return false;
            var body = m.Groups["body"].Value.Replace("\\", "", StringComparison.Ordinal);
            var lit = Regex.Match(body, @"0x[0-9A-Fa-f]+|\d+");
            if (!lit.Success) return false;
            value = TestHarnessGenerator.ParseUIntExpression(lit.Value);
            return true;
        }
        catch
        {
            return false;
        }
    }

    private static LlTestAssertionSpec RegisterUnchangedAfterReadAssertion(
        string instance, string member, uint preload) => new()
    {
        Kind = LlAssertionKind.RegisterValue,
        InstanceName = instance,
        MemberName = member,
        ExpectedHex = $"0x{preload:X}",
        ExpectedMask = 0xFFFFFFFFu,
        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
        RuleSourceDetail =
            $"只读校验：调用后 {member} 应仍为预置 0x{preload:X}（读不得改写寄存器）"
    };

    /// <summary>
    /// After a Set write-check: if LL_*_Get* companion exists, emit Set→Get with return assert.
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildSetThenGetPairAsync(
        AppDbContext db,
        LlFunction setFn,
        string instance,
        LlTestCaseEditModel writeCheck,
        CancellationToken ct)
    {
        var getName = SuggestGenericGetCompanion(setFn.FunctionName);
        if (getName is null || !HeaderDeclares(setFn.FilePath, getName))
            return null;

        var getBody = TryReadFunctionBodyFromSource(setFn.FilePath, getName);
        if (string.IsNullOrWhiteSpace(getBody))
            return null;

        // Determine expected Get return from write-check payload + Get body shape.
        uint? expectedReturn = null;
        string? detail = null;

        var shift = ReadBitShiftPattern.Match(getBody);
        if (shift.Success)
        {
            var bodyMember = shift.Groups["mem"].Value;
            var bodyMskMacro = shift.Groups["msk"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out _);
            // Prefer Get function-name trusted field over possibly-wrong Get body mask.
            var getProbe = new LlFunction
            {
                SdkProjectId = setFn.SdkProjectId,
                FunctionName = getName,
                FilePath = setFn.FilePath
            };
            var trusted = await TryResolveTrustedMaskAsync(db, getProbe, member, ct);
            string? fieldName = null;
            if (trusted is { Bits: > 0 } && TryTrustedFieldName(trusted, member, out var tf))
                fieldName = tf;
            else if (TryFieldNameFromMskMacro(bodyMskMacro, member, out var bfName))
                fieldName = bfName;

            if (fieldName is not null)
            {
                var field = await FindRegisterFieldAsync(db, setFn.SdkProjectId, member, fieldName, ct);
                if (field?.Mask is uint mask && mask != 0 && field.BitPosition is int pos)
                {
                    var bf = writeCheck.Assertions.FirstOrDefault(a =>
                        a.Kind == LlAssertionKind.BitField
                        && string.Equals(a.BitFieldName, fieldName, StringComparison.OrdinalIgnoreCase));
                    if (bf is not null)
                    {
                        expectedReturn = TestHarnessGenerator.ParseUIntExpression(bf.ExpectedHex ?? "0");
                        detail = $"Set 后 Get 应返回位域 {fieldName}=0x{expectedReturn:X}";
                    }
                    else
                    {
                        var reg = writeCheck.Assertions.FirstOrDefault(a =>
                            a.Kind == LlAssertionKind.RegisterValue
                            && string.Equals(a.MemberName, member, StringComparison.OrdinalIgnoreCase));
                        if (reg is not null)
                        {
                            var bits = TestHarnessGenerator.ParseUIntExpression(reg.ExpectedHex ?? "0");
                            expectedReturn = (bits & mask) >> pos;
                            detail = $"Set 后 Get 应返回 ({member}&0x{mask:X})>>{pos} = 0x{expectedReturn:X}";
                        }
                    }
                }
            }
        }
        else if (ReadRegPattern.Match(getBody) is { Success: true } rr
                 && !getBody.Contains("OFFSET", StringComparison.Ordinal))
        {
            var member = rr.Groups["mem"].Value;
            var reg = writeCheck.Assertions.FirstOrDefault(a =>
                a.Kind == LlAssertionKind.RegisterValue
                && string.Equals(a.MemberName, member, StringComparison.OrdinalIgnoreCase));
            if (reg is not null)
            {
                expectedReturn = TestHarnessGenerator.ParseUIntExpression(reg.ExpectedHex ?? "0");
                detail = $"Set 后 Get/READ_REG 应返回 0x{expectedReturn:X}";
            }
        }

        if (expectedReturn is null || string.IsNullOrEmpty(detail))
            return null;

        // Get typically only needs the peripheral pointer.
        var getParams = writeCheck.Parameters
            .Where(p => p.Type.Contains('*', StringComparison.Ordinal))
            .Select(p =>
            {
                var t = p.Type.Trim();
                if (!t.Contains("const", StringComparison.OrdinalIgnoreCase))
                    t = "const " + t;
                return new LlTestParameterValue
                {
                    Name = p.Name,
                    Type = t,
                    ValueExpression = p.ValueExpression,
                    RuleSource = p.RuleSource
                };
            })
            .ToList();
        if (getParams.Count == 0)
        {
            getParams =
            [
                new LlTestParameterValue
                {
                    Name = "Instance",
                    Type = "const void*",
                    ValueExpression = instance,
                    RuleSource = nameof(LlAssertionRuleSource.AutoGeneratedFromSdkMacro)
                }
            ];
        }

        var pair = BaseModel(setFn);
        pair.Name = $"{setFn.FunctionName}→{getName}/{instance}/set-get";
        pair.FunctionName = getName;
        pair.FunctionSignature = $"uint32_t {getName}(...)";
        pair.Status = nameof(LlTestCaseStatus.Ready);
        pair.IsAutoGenerated = true;
        pair.PreludeCalls =
        [
            new LlTestCallStep
            {
                FunctionName = setFn.FunctionName,
                Parameters = writeCheck.Parameters.Select(p => new LlTestParameterValue
                {
                    Name = p.Name,
                    Type = p.Type,
                    ValueExpression = p.ValueExpression,
                    RuleSource = p.RuleSource
                }).ToList()
            }
        ];
        pair.Parameters = getParams;
        pair.InitialRegisters = writeCheck.InitialRegisters.Select(r => new LlTestInitialRegister
        {
            InstanceName = r.InstanceName,
            MemberName = r.MemberName,
            ValueHex = r.ValueHex
        }).ToList();
        pair.Assertions =
        [
            ReturnValueAssertion($"0x{expectedReturn.Value:X}", detail),
            ..DefaultTimeoutAssertions()
        ];
        pair.Notes =
            $"读写成对：同一 harness 先 {setFn.FunctionName} 再 {getName}，断言返回值。可检出写/读地址或 Pos 不一致。虚拟环境，非真实硬件。";
        return pair;
    }

    private static string? SuggestGenericGetCompanion(string setName)
    {
        // LL_ADC_SetX → LL_ADC_GetX ; LL_ADC_REG_SetY → LL_ADC_REG_GetY
        var idx = setName.LastIndexOf("Set", StringComparison.Ordinal);
        if (idx < 0) return null;
        return setName[..idx] + "Get" + setName[(idx + 3)..];
    }

    private static bool IsLikelyGetter(string name)
        => name.Contains("Get", StringComparison.OrdinalIgnoreCase)
           || name.Contains("Read", StringComparison.OrdinalIgnoreCase)
           || Regex.IsMatch(name, @"_Is[A-Z]");

    private static string? TryReadFunctionBodyFromSource(string? filePath, string functionName)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);
            var fnIdx = text.IndexOf(functionName + "(", StringComparison.Ordinal);
            if (fnIdx < 0) return null;
            var brace = text.IndexOf('{', fnIdx);
            if (brace < 0) return null;
            var depth = 0;
            for (var i = brace; i < text.Length; i++)
            {
                if (text[i] == '{') depth++;
                else if (text[i] == '}')
                {
                    depth--;
                    if (depth == 0)
                        return text.Substring(brace, i - brace + 1);
                }
            }
        }
        catch
        {
            /* ignore */
        }

        return null;
    }

    private static async Task<uint> ResolveClearMaskAsync(
        AppDbContext db, LlFunction fn, string member, string mskMacro, CancellationToken ct)
    {
        if (TryFieldNameFromMskMacro(mskMacro, member, out var fieldName))
        {
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (field?.Mask is uint m && m != 0)
                return m;
        }

        // Composite LL mask: expand #define and OR chip *_Msk tokens.
        var expanded = ExpandDefineBody(fn.FilePath, mskMacro);
        if (string.IsNullOrWhiteSpace(expanded))
            return 0;

        uint combined = 0;
        foreach (Match tok in ChipFieldMskToken.Matches(expanded))
        {
            var chipMsk = tok.Groups["tok"].Value;
            if (!TryFieldNameFromMskMacro(chipMsk, member, out var fnName))
                continue;
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fnName, ct);
            if (field?.Mask is uint m)
                combined |= m;
        }

        return combined;
    }

    private static async Task<RegisterField?> FindRegisterFieldAsync(
        AppDbContext db, Guid sdkProjectId, string member, string fieldName, CancellationToken ct)
    {
        var rows = await db.RegisterFields.AsNoTracking()
            .Include(f => f.RegisterDefinition)
            .Where(f => f.Name == fieldName
                        && f.RegisterDefinition != null
                        && f.RegisterDefinition.SdkProjectId == sdkProjectId
                        && f.RegisterDefinition.MemberName == member
                        && f.Mask != null)
            .ToListAsync(ct);
        return rows
            .OrderBy(f =>
            {
                var s = f.RegisterDefinition!.StructName;
                if (s.EndsWith("_TypeDef", StringComparison.Ordinal)) return 0;
                if (s.StartsWith("ADC", StringComparison.OrdinalIgnoreCase)) return 1;
                return 2;
            })
            .FirstOrDefault();
    }

    private static string? ResolveLlHeaderPath(string? filePath)
    {
        if (string.IsNullOrWhiteSpace(filePath)) return null;
        if (File.Exists(filePath)) return Path.GetFullPath(filePath);

        var normalized = filePath.Replace('/', Path.DirectorySeparatorChar);
        // DB often stores repo-relative paths (SDKContent/...).
        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 10; i++)
        {
            var cand = Path.GetFullPath(Path.Combine(dir, normalized));
            if (File.Exists(cand)) return cand;

            // Stale pack folder name in DB (G580x vs G58xx): search by LL file name under SDKContent.
            var sdkContent = Path.Combine(dir, "SDKContent");
            if (Directory.Exists(sdkContent))
            {
                var name = Path.GetFileName(normalized);
                try
                {
                    var hit = Directory.EnumerateFiles(sdkContent, name, SearchOption.AllDirectories)
                        .FirstOrDefault(p => p.Contains($"{Path.DirectorySeparatorChar}LL{Path.DirectorySeparatorChar}",
                            StringComparison.OrdinalIgnoreCase));
                    if (hit is not null) return hit;
                }
                catch
                {
                    /* ignore IO */
                }
            }

            var parent = Path.GetDirectoryName(dir);
            if (string.IsNullOrEmpty(parent) || parent == dir) break;
            dir = parent;
        }

        return null;
    }

    private static string? TryReadModifyRegFromSource(string? filePath, string functionName)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);
            var fnIdx = text.IndexOf(functionName + "(", StringComparison.Ordinal);
            if (fnIdx < 0) return null;
            var brace = text.IndexOf('{', fnIdx);
            if (brace < 0) return null;
            var depth = 0;
            for (var i = brace; i < text.Length; i++)
            {
                if (text[i] == '{') depth++;
                else if (text[i] == '}')
                {
                    depth--;
                    if (depth == 0)
                    {
                        var body = text.Substring(brace, i - brace + 1);
                        var m = ModifyRegPattern.Match(body);
                        return m.Success ? m.Value + "…)" : null;
                    }
                }
            }
        }
        catch { /* ignore */ }
        return null;
    }

    private static string? ExpandDefineBody(string? filePath, string macroName)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);
            // Multi-line #define NAME ( a | b | \ ... )
            var m = Regex.Match(text,
                $@"#define\s+{Regex.Escape(macroName)}\s+(?<body>(?:.*\\\r?\n)*.*)",
                RegexOptions.CultureInvariant);
            if (!m.Success) return null;
            return m.Groups["body"].Value.Replace("\\", "", StringComparison.Ordinal);
        }
        catch
        {
            return null;
        }
    }

    /// <summary>Pick an LL_*SAMP*MODE* macro name (clang resolves it in harness).</summary>
    private static string? TryPickSampleMaskMacroName(string? filePath)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);
            var matches = Regex.Matches(text,
                @"#define\s+(?<n>LL_[A-Z0-9_]*SAMP[A-Z0-9_]*MODE[A-Z0-9_]*)\b",
                RegexOptions.CultureInvariant);
            // Prefer a multi-bit resumed mode over DISABLE / single-bit.
            foreach (var prefer in new[]
                     {
                         "LL_ADC_SAMP_MODE_REG_RESUMED",
                         "LL_ADC_SAMP_MODE_INJ_REG_RESUMED",
                         "LL_ADC_SAMP_MODE_TRIGGERED_REG_RESUMED",
                         "LL_ADC_SAMP_MODE_REG_CONTINUED"
                     })
            {
                if (matches.Any(m => m.Groups["n"].Value == prefer))
                    return prefer;
            }

            return matches.Cast<Match>()
                .Select(m => m.Groups["n"].Value)
                .FirstOrDefault(n => !n.Contains("DISABLE", StringComparison.OrdinalIgnoreCase));
        }
        catch
        {
            return null;
        }
    }

    private static async Task<uint> ResolveHeaderMaskMacroBitsAsync(
        AppDbContext db, LlFunction fn, string member, string macroName, CancellationToken ct)
    {
        var body = ExpandDefineBody(fn.FilePath, macroName);
        if (string.IsNullOrWhiteSpace(body)) return 0;
        uint acc = 0;
        foreach (Match tok in ChipFieldMskToken.Matches(body))
        {
            if (!TryFieldNameFromMskMacro(tok.Groups["tok"].Value, member, out var fieldName))
                continue;
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (field?.Mask is uint m)
                acc |= m;
        }

        return acc;
    }

    private static bool IsLikelyRegisterSetter(string functionName)
        => functionName.Contains("Set", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Write", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Config", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Enable", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Assert", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Release", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Start", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Stop", StringComparison.OrdinalIgnoreCase);

    /// <summary>ADC0_CFGR0_ROVSM_Msk + member CFGR0 → ROVSM</summary>
    private static bool TryFieldNameFromMskMacro(string mskMacro, string memberName, out string fieldName)
    {
        fieldName = "";
        if (!mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase))
            return false;
        var body = mskMacro[..^4]; // strip _Msk/_MSK
        var token = $"_{memberName}_";
        var idx = body.IndexOf(token, StringComparison.OrdinalIgnoreCase);
        if (idx < 0) return false;
        fieldName = body[(idx + token.Length)..];
        // Composite LL masks like OVERSAMPLING_MODE are not single chip fields.
        if (fieldName.Contains('_', StringComparison.Ordinal) && fieldName.Contains("MODE", StringComparison.OrdinalIgnoreCase))
            return false;
        return fieldName.Length > 0
               && !fieldName.Contains("OVERSAMPLING", StringComparison.OrdinalIgnoreCase);
    }

    /// <summary>
    /// Parse chip mask → register member + field.
    /// Supports <c>DAC0_CR_OEN_Msk</c> (3 seg) and <c>HRPWM_SLV0_PWMCR0_CONT_Msk</c> / <c>HRPWM_MST_MCR0_CONT_Msk</c> (4+ seg).
    /// Rejects multi-word composites like <c>LL_ADC_CFGR1_PREPARING_START_MSK</c>.
    /// </summary>
    private static bool TryParseChipMaskRegAndField(string mskMacro, out string regMember, out string fieldName)
    {
        regMember = "";
        fieldName = "";
        if (string.IsNullOrWhiteSpace(mskMacro)) return false;
        if (!mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
            && !mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return false;

        var core = mskMacro[..^4];
        var parts = core.Split('_', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length < 3) return false;
        // Last = field, second-last = register member; field must be a single token (no further _).
        fieldName = parts[^1];
        regMember = parts[^2];
        if (fieldName.Length == 0 || regMember.Length == 0) return false;
        // Reject long composite LL masks: field often looks like START / MODE with many peri tokens
        // and contains ALL / PREPARING style — keep simple alphanumeric field only.
        if (!Regex.IsMatch(fieldName, @"^[A-Za-z][A-Za-z0-9]*$")) return false;
        if (!Regex.IsMatch(regMember, @"^[A-Za-z][A-Za-z0-9]*$")) return false;
        if (parts.Length >= 5
            && parts[0].Equals("LL", StringComparison.OrdinalIgnoreCase))
            return false;
        return true;
    }

    /// <summary>Parsed <c>Inst-&gt;path</c> leaf register access (flat / nested / array).</summary>
    private sealed record RegAccessPath(
        string LeafMember,
        string RawPath,
        string? ArrayIndexExpr,
        string? NestedPrefix);

    private static bool TryParseRegAccessPath(string? path, out RegAccessPath parsed)
    {
        parsed = new RegAccessPath("", "", null, null);
        if (string.IsNullOrWhiteSpace(path)) return false;
        var p = path.Trim();
        // PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0
        var arr = Regex.Match(p,
            @"^(?<arr>[A-Za-z_][A-Za-z0-9_]*)\s*\[\s*(?<idx>.+?)\s*\]\s*(?:\.\s*(?:REG\s*\.)?\s*)?(?<leaf>[A-Za-z_][A-Za-z0-9_]*)\s*$",
            RegexOptions.CultureInvariant | RegexOptions.Singleline);
        if (arr.Success)
        {
            parsed = new RegAccessPath(
                arr.Groups["leaf"].Value,
                p,
                arr.Groups["idx"].Value.Trim(),
                arr.Groups["arr"].Value);
            return true;
        }

        // Master.MCR0 / Common.XXX
        var nest = Regex.Match(p,
            @"^(?<pref>[A-Za-z_][A-Za-z0-9_]*)\s*\.\s*(?<leaf>[A-Za-z_][A-Za-z0-9_]*)\s*$",
            RegexOptions.CultureInvariant);
        if (nest.Success)
        {
            parsed = new RegAccessPath(
                nest.Groups["leaf"].Value,
                p,
                null,
                nest.Groups["pref"].Value);
            return true;
        }

        // Flat MEM
        var flat = Regex.Match(p, @"^(?<leaf>[A-Za-z_][A-Za-z0-9_]*)\s*$", RegexOptions.CultureInvariant);
        if (flat.Success)
        {
            parsed = new RegAccessPath(flat.Groups["leaf"].Value, p, null, null);
            return true;
        }

        // Fallback: last identifier after . or ]
        var last = Regex.Matches(p, @"[A-Za-z_][A-Za-z0-9_]*");
        if (last.Count == 0) return false;
        parsed = new RegAccessPath(last[^1].Value, p, null, null);
        return true;
    }

    /// <summary>
    /// Bound for <c>idx % LL_*_NUMS</c> (any peripheral). Falls back to literal after % or 8.
    /// </summary>
    private static uint ResolveArrayBound(string? indexExpr, string? sourceFile)
    {
        const uint fallback = 8u;
        if (!string.IsNullOrWhiteSpace(indexExpr))
        {
            var numsMacro = Regex.Match(indexExpr, @"\b(LL_[A-Za-z0-9_]+_NUMS)\b");
            if (numsMacro.Success && !string.IsNullOrWhiteSpace(sourceFile))
            {
                foreach (var path in CandidateDefineFiles(sourceFile, null))
                {
                    if (TryParseUintDefineFromFile(path, numsMacro.Groups[1].Value, out var n) && n > 0)
                        return n;
                }
            }

            var lit = Regex.Match(indexExpr, @"%\s*(?<n>\d+)");
            if (lit.Success && uint.TryParse(lit.Groups["n"].Value, out var ln) && ln > 0)
                return ln;
        }

        if (!string.IsNullOrWhiteSpace(sourceFile))
        {
            foreach (var path in CandidateDefineFiles(sourceFile, null))
            {
                // Prefer any LL_*_NUMS define in the same header family.
                try
                {
                    var text = File.ReadAllText(path);
                    var m = Regex.Match(text, @"#define\s+(LL_[A-Za-z0-9_]+_NUMS)\s+\(?\s*(?<n>\d+)");
                    if (m.Success && uint.TryParse(m.Groups["n"].Value, out var n) && n > 0)
                        return n;
                }
                catch { /* ignore */ }
            }
        }

        return fallback;
    }

    /// <summary>Chip mask peri prefix: <c>ADC0_CFGR0_X_Msk</c>→ADC0, <c>HRPWM_SLV0_PWMCR0_X_Msk</c>→HRPWM_SLV0.</summary>
    private static bool TryPeriPrefixFromMask(string? mskMacro, out string peri)
    {
        peri = "";
        if (string.IsNullOrWhiteSpace(mskMacro)) return false;
        if (!mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
            && !mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return false;
        if (!TryParseChipMaskRegAndField(mskMacro, out _, out _))
            return false;
        var core = mskMacro[..^4];
        var parts = core.Split('_', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length < 3) return false;
        peri = string.Join('_', parts.Take(parts.Length - 2));
        return peri.Length > 0;
    }

    /// <summary>
    /// Map nested/array access to virtual MCU instance for any module.
    /// Array banks: replace trailing digits on mask peri (SLV0/CH0/…) with computed index.
    /// Nested Master/Common: prefer *_MST / *_COM family from mask peri.
    /// </summary>
    private static string ResolveNestedInstance(
        string fallbackInstance,
        RegAccessPath path,
        uint channelIndex,
        string? mskMacro)
    {
        TryPeriPrefixFromMask(mskMacro, out var periFromMask);

        if (path.ArrayIndexExpr is not null)
        {
            if (!string.IsNullOrWhiteSpace(periFromMask))
            {
                var bank = Regex.Replace(periFromMask, @"\d+$", channelIndex.ToString());
                if (!bank.Equals(periFromMask, StringComparison.Ordinal)
                    || Regex.IsMatch(periFromMask, @"\d+$"))
                    return bank;
                // Peri has no trailing digits (rare): Module + index
                return periFromMask + channelIndex;
            }

            // No mask peri: Module_ArrayPrefixIndex e.g. fallback HRPWM + PWM → keep fallback if already banked
            if (Regex.IsMatch(fallbackInstance, @"\d+$"))
                return Regex.Replace(fallbackInstance, @"\d+$", channelIndex.ToString());
            return $"{fallbackInstance}_{path.NestedPrefix}{channelIndex}";
        }

        if (!string.IsNullOrWhiteSpace(path.NestedPrefix))
        {
            var pref = path.NestedPrefix!;
            if (!string.IsNullOrWhiteSpace(periFromMask))
            {
                // Master / Common / shared block: swap bank token
                if (pref.Equals("Master", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("MST", StringComparison.OrdinalIgnoreCase))
                {
                    var mst = Regex.Replace(periFromMask, @"_(SLV|CH|UNIT|TIM)\d+$", "_MST",
                        RegexOptions.IgnoreCase);
                    if (mst.Equals(periFromMask, StringComparison.OrdinalIgnoreCase)
                        && !periFromMask.Contains("_MST", StringComparison.OrdinalIgnoreCase))
                    {
                        var root = Regex.Match(periFromMask, @"^[A-Za-z]+");
                        mst = root.Success ? $"{root.Value}_MST" : periFromMask;
                    }
                    return mst;
                }

                if (pref.Equals("Common", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("COM", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("Shared", StringComparison.OrdinalIgnoreCase))
                {
                    var com = Regex.Replace(periFromMask, @"_(SLV|CH|UNIT|TIM|MST)\d*$", "_COM",
                        RegexOptions.IgnoreCase);
                    if (com.Equals(periFromMask, StringComparison.OrdinalIgnoreCase)
                        && !periFromMask.Contains("_COM", StringComparison.OrdinalIgnoreCase))
                    {
                        var root = Regex.Match(periFromMask, @"^[A-Za-z]+");
                        com = root.Success ? $"{root.Value}_COM" : periFromMask;
                    }
                    return com;
                }

                // Other nested: use mask peri as-is (e.g. still SLV0 template)
                return periFromMask;
            }

            if (pref.Equals("Master", StringComparison.OrdinalIgnoreCase))
                return Regex.Replace(fallbackInstance, @"_(SLV|CH)\d+$", "_MST", RegexOptions.IgnoreCase);
            if (pref.Equals("Common", StringComparison.OrdinalIgnoreCase))
                return Regex.Replace(fallbackInstance, @"_(SLV|CH|MST)\d*$", "_COM", RegexOptions.IgnoreCase);
        }

        if (!string.IsNullOrWhiteSpace(periFromMask))
            return periFromMask;
        return fallbackInstance;
    }

    /// <summary>Host TypeDef cast name for multi-bank aggregates (single image); else numbered instance.</summary>
    private static string ResolveHostPeriPointer(
        string? peripheralName,
        string fallbackInstance,
        string targetInstance,
        string? current)
    {
        if (IsHostAggregateModule(peripheralName) || IsHostAggregateInstance(targetInstance))
            return string.IsNullOrWhiteSpace(peripheralName) ? "HRPWM" : peripheralName!;

        if (!string.IsNullOrWhiteSpace(current)
            && !current.Equals("0", StringComparison.Ordinal)
            && !IsHostAggregateInstance(current))
            return current;

        return string.IsNullOrWhiteSpace(fallbackInstance)
            ? (peripheralName ?? "PERI")
            : fallbackInstance;
    }

    private static bool IsHostAggregateModule(string? module)
        => string.Equals(module, "HRPWM", StringComparison.OrdinalIgnoreCase);

    private static bool IsHostAggregateInstance(string? instance)
        => !string.IsNullOrWhiteSpace(instance)
           && (instance.StartsWith("HRPWM_SLV", StringComparison.OrdinalIgnoreCase)
               || instance.StartsWith("HRPWM_MST", StringComparison.OrdinalIgnoreCase)
               || instance.StartsWith("HRPWM_COM", StringComparison.OrdinalIgnoreCase)
               || string.Equals(instance, "HRPWM", StringComparison.OrdinalIgnoreCase));

    /// <summary>
    /// Chip mask embeds the register (<c>DAC0_CR_OEN_Msk</c> → CR). If body uses a different
    /// <c>->Member</c>, assert on the mask's register so the mismatch fails the test.
    /// </summary>
    private static string ResolveMemberAlignedToMask(
        string bodyMember,
        string? mskMacro,
        out bool memberMaskMismatch,
        out string pairNote)
    {
        memberMaskMismatch = false;
        if (!string.IsNullOrWhiteSpace(mskMacro)
            && TryParseChipMaskRegAndField(mskMacro, out var maskReg, out _))
        {
            if (!maskReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase))
            {
                memberMaskMismatch = true;
                pairNote =
                    $"成员/掩码不一致：体为 ->{bodyMember} 但掩码声明寄存器 {maskReg}，断言落在 {maskReg}";
                return maskReg;
            }

            pairNote = $"断言寄存器 {maskReg}（与芯片掩码内嵌成员一致）";
            return maskReg;
        }

        // Composite LL_*_MSK: require _{bodyMember}_ token when present.
        if (!string.IsNullOrWhiteSpace(mskMacro)
            && mskMacro.Contains($"_{bodyMember}_", StringComparison.OrdinalIgnoreCase))
        {
            pairNote = $"断言寄存器 {bodyMember}（复合掩码含 _{bodyMember}_）";
            return bodyMember;
        }

        if (!string.IsNullOrWhiteSpace(mskMacro)
            && (mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
                || mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            && !mskMacro.Contains($"_{bodyMember}_", StringComparison.OrdinalIgnoreCase))
        {
            // Body member not named in composite mask — still assert on body member but flag distrust.
            pairNote =
                $"成员/掩码弱对应：体为 ->{bodyMember}，掩码 {mskMacro} 未含 _{bodyMember}_（复合掩码，按体成员断言）";
            return bodyMember;
        }

        pairNote = string.IsNullOrWhiteSpace(mskMacro)
            ? $"断言寄存器 {bodyMember}"
            : $"断言寄存器 {bodyMember}（掩码未解析到内嵌成员，按体成员）";
        return bodyMember;
    }

    /// <summary>
    /// Scan body for every SET/CLEAR/MODIFY/READ_* mask pair; used to annotate combo cases.
    /// </summary>
    private static List<string> CollectBodyMaskMemberMismatchNotes(string? body)
    {
        var notes = new List<string>();
        if (string.IsNullOrWhiteSpace(body)) return notes;

        void Check(string op, string mem, string msk)
        {
            _ = ResolveMemberAlignedToMask(mem, msk, out var mismatch, out var note);
            if (mismatch)
                notes.Add($"{op}: {note}");
        }

        foreach (Match m in SetClearBitPattern.Matches(body))
            Check(m.Groups["op"].Value, PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ModifyRegPattern.Matches(body))
            Check("MODIFY_REG", PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ReadBitShiftPattern.Matches(body))
            Check("READ_BIT_SHIFT", m.Groups["mem"].Value, m.Groups["msk"].Value);
        foreach (Match m in ReadBitThenShiftPattern.Matches(body))
            Check("READ_BIT>>Pos", m.Groups["mem"].Value, m.Groups["msk"].Value);
        foreach (Match m in ReadBitBoolPattern.Matches(body))
            Check("READ_BIT", m.Groups["mem"].Value, m.Groups["msk"].Value);
        foreach (Match m in WriteRegPattern.Matches(body))
        {
            var mskTok = Regex.Match(m.Groups["val"].Value, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\b");
            if (mskTok.Success)
                Check("WRITE_REG", PathLeaf(m), mskTok.Groups["msk"].Value);
        }

        return notes;
    }

    private static void EnsureNonZeroPayloadParams(List<LlTestParameterValue> parameters, uint maxFieldValue)
    {
        var payload = Math.Max(1u, maxFieldValue);
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*')) continue;
            if (!string.Equals(p.ValueExpression, "0", StringComparison.Ordinal)
                && !string.Equals(p.ValueExpression, "0x0", StringComparison.OrdinalIgnoreCase))
                continue;
            if (p.Name.Contains("Len", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Size", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Count", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Timeout", StringComparison.OrdinalIgnoreCase))
                continue;
            p.ValueExpression = payload.ToString();
            p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }
    }

    private static List<LlFunctionParameter> FakeParamsFromSig(LlFunction fn)
    {
        var parsed = TestHarnessGenerator.ParseParametersFromSignature(
            fn.Signature ?? $"{fn.ReturnType} {fn.FunctionName}({fn.Parameters})");
        return parsed.Select((p, i) => new LlFunctionParameter
        {
            Name = p.Name,
            Type = p.Type,
            Position = i
        }).ToList();
    }

    private static bool IsWriteLike(string name)
        => name.Contains("Write", StringComparison.OrdinalIgnoreCase)
           || name.Contains("SetOutput", StringComparison.OrdinalIgnoreCase)
           || name.Contains("SetPin", StringComparison.OrdinalIgnoreCase);

    private static bool IsReadLike(string name)
        => name.Contains("Read", StringComparison.OrdinalIgnoreCase)
           || name.Contains("Get", StringComparison.OrdinalIgnoreCase);

    private static bool IsClearLike(string name)
        => name.Contains("Clear", StringComparison.OrdinalIgnoreCase)
           || name.Contains("ResetOutput", StringComparison.OrdinalIgnoreCase);

    private static string? SuggestGpioReadCompanion(string writeName)
    {
        if (writeName.Contains("WriteOutputPort", StringComparison.OrdinalIgnoreCase)
            || writeName.Contains("SetOutputPin", StringComparison.OrdinalIgnoreCase)
            || writeName.Contains("ResetOutputPin", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_ReadOutputPort";
        if (writeName.Contains("SetPinPull", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_GetPinPull";
        if (writeName.Contains("SetPinSpeed", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_GetPinSpeed";
        if (writeName.Contains("SetPinOutputType", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_GetPinOutputType";
        if (writeName.Contains("SetAFPin", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_GetAFPin";
        if (writeName.Contains("SetDrvCap", StringComparison.OrdinalIgnoreCase))
            return "LL_GPIO_GetDrvCap";
        return null;
    }

    private static bool HeaderDeclares(string? filePath, string functionName)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return false;
            var text = File.ReadAllText(resolved);
            return text.Contains(functionName + "(", StringComparison.Ordinal);
        }
        catch { return false; }
    }

    private static uint ExpectedPortAfterWrite(string writeName, string pinExpr)
    {
        var v = TestHarnessGenerator.ParseUIntExpression(pinExpr);
        if (writeName.Contains("ResetOutput", StringComparison.OrdinalIgnoreCase))
            return 0;
        return v;
    }

    private static List<LlTestParameterValue> BuildParamsForRead(string readName, string instance, string pinExpr)
    {
        // ReadOutputPort(GPIOx) — pin not used; Get* may need Pin
        if (readName.Contains("ReadOutputPort", StringComparison.OrdinalIgnoreCase)
            || readName.Contains("ReadInputPort", StringComparison.OrdinalIgnoreCase))
        {
            return
            [
                new LlTestParameterValue
                {
                    Name = "GPIOx",
                    Type = "const GPIO_TypeDef*",
                    ValueExpression = instance,
                    RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                }
            ];
        }

        return
        [
            new LlTestParameterValue
            {
                Name = "GPIOx",
                Type = "const GPIO_TypeDef*",
                ValueExpression = instance,
                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
            },
            new LlTestParameterValue
            {
                Name = "Pin",
                Type = "uint32_t",
                ValueExpression = pinExpr,
                RuleSource = nameof(LlAssertionRuleSource.AutoGeneratedFromSdkMacro)
            }
        ];
    }

    private static string InferDefaultInstance(string? peripheralName, string functionName)
    {
        if (!string.IsNullOrWhiteSpace(peripheralName))
            return MapModuleToDefaultInstance(peripheralName!);
        var m = Regex.Match(functionName, @"^LL_([A-Z0-9]+)_");
        return m.Success ? MapModuleToDefaultInstance(m.Groups[1].Value) : "PERI";
    }

    private static string MapModuleToDefaultInstance(string moduleOrInstance)
        => moduleOrInstance.ToUpperInvariant() switch
        {
            "ADC" => "ADC0",
            "GPIO" => "GPIOA",
            "GPTMRX" => "TMR0",
            "GPTMRY" => "TMR3",
            "LPTMR" => "TMR6",
            "BSTMR" => "TMR7",
            "ADTMR" => "TMR9",
            _ when moduleOrInstance.Any(char.IsDigit) => moduleOrInstance,
            _ => moduleOrInstance
        };

    private static LlTestCaseEditModel DraftShell(LlFunction fn, string name)
    {
        var m = BaseModel(fn);
        m.Name = name;
        m.Status = "Draft";
        m.IsAutoGenerated = true;
        m.Parameters = BuildParams(
            fn.ParseParameters.OrderBy(p => p.Position).ToList(),
            InferDefaultInstance(fn.PeripheralName, fn.FunctionName),
            null);
        if (m.Parameters.Count == 0)
        {
            m.Parameters = TestHarnessGenerator.ParseParametersFromSignature(
                fn.Signature ?? $"{fn.ReturnType} {fn.FunctionName}({fn.Parameters})");
            var inst = InferDefaultInstance(fn.PeripheralName, fn.FunctionName);
            foreach (var p in m.Parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
                p.ValueExpression = inst;
        }
        m.Notes = "自动草稿：参数/断言需人工根据真实 SDK 补全。";
        return m;
    }

    /// <summary>
    /// clear-check 只在该实例的解析寄存器里确实有 ISR 时生成，避免断言打到不存在的成员。
    /// </summary>
    private static async Task<bool> InstanceHasRegisterMemberAsync(
        AppDbContext db,
        Guid sdkProjectId,
        string instanceName,
        string memberName,
        CancellationToken cancellationToken)
    {
        return await (
            from reg in db.RegisterDefinitions.AsNoTracking()
            join inst in db.PeripheralInstances.AsNoTracking() on reg.PeripheralInstanceId equals inst.Id
            where reg.SdkProjectId == sdkProjectId
                  && inst.Name == instanceName
                  && reg.MemberName == memberName
            select reg.Id).AnyAsync(cancellationToken);
    }

    private static void ApplyHostPolicy(LlTestCaseEditModel model, LlFunction fn)
    {
        // Host harness (shim + pointer buffers + CAN wait ack) runs all auto drafts as Draft/Ready.
        _ = fn;
        _ = model;
    }

    private static LlTestCaseEditModel BaseModel(LlFunction fn) => new()
    {
        SdkProjectId = fn.SdkProjectId,
        ChipId = fn.ChipId,
        LlFunctionId = fn.Id,
        ChipModelName = fn.ChipName,
        PeripheralName = fn.PeripheralName,
        FunctionName = fn.FunctionName,
        FunctionSignature = fn.Signature ?? $"{fn.ReturnType} {fn.FunctionName}({fn.Parameters})",
        SourceFile = fn.FilePath
    };

    private static List<LlTestParameterValue> BuildParams(
        IReadOnlyList<LlFunctionParameter> parameters,
        string instance,
        string? pinValueExpr,
        string? functionName = null)
    {
        var list = new List<LlTestParameterValue>();
        foreach (var p in parameters.OrderBy(x => x.Position))
        {
            var expr = "0";
            var source = "Manual";
            if (p.Type.Contains("TypeDef", StringComparison.OrdinalIgnoreCase) && p.Type.Contains('*'))
            {
                expr = instance;
                source = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
            else if (pinValueExpr is not null && UsesPinMacroForParameter(p.Name))
            {
                expr = pinValueExpr;
                source = nameof(LlAssertionRuleSource.AutoGeneratedFromSdkMacro);
            }

            list.Add(new LlTestParameterValue
            {
                Name = p.Name,
                Type = p.Type,
                ValueExpression = expr,
                RuleSource = source
            });
        }

        ApplySmartDefaults(functionName, list);
        return list;
    }

    private static bool UsesPinMacroForParameter(string paramName)
        => paramName.Contains("Pin", StringComparison.OrdinalIgnoreCase)
           || paramName.Contains("PinMask", StringComparison.OrdinalIgnoreCase)
           || paramName.Equals("PortValue", StringComparison.OrdinalIgnoreCase);

    private static void ApplySmartDefaults(string? functionName, List<LlTestParameterValue> list)
    {
        var isSetter = functionName is not null && IsLikelyRegisterSetter(functionName);
        foreach (var p in list)
        {
            if (!string.Equals(p.ValueExpression, "0", StringComparison.Ordinal)) continue;
            if (p.Name.Contains("CPU_Clk", StringComparison.OrdinalIgnoreCase)
                || p.Name.Contains("Clk_Freq", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "168000000";
            else if (p.Name.Equals("Ticks", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "1000";
            else if (p.Name.Equals("Pull", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "2";
            else if (p.Name.Equals("Speed", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "1";
            else if (p.Name.Equals("OutputType", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "1";
            else if (isSetter
                     && (p.Name.Equals("Mode", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("State", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Enable", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Cmd", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("NewState", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Level", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Value", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Cfg", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Config", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Shift", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Ratio", StringComparison.OrdinalIgnoreCase)))
                p.ValueExpression = "1";
        }
    }

    private static bool TryBuildGpioGetterPreparedCase(
        string functionName,
        string instance,
        string pinExpr,
        out List<LlTestInitialRegister> initials,
        out List<LlTestAssertionSpec> assertions)
    {
        initials = [];
        assertions = DefaultTimeoutAssertions();
        var pin = TestHarnessGenerator.ParseUIntExpression(pinExpr);
        var pinIdx = LlClearStatusRegisterResolver.GpioPinBitIndex(pin);

        if (functionName.Contains("GetPinPull", StringComparison.OrdinalIgnoreCase))
        {
            var udr = 2u << (pinIdx * 2);
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "UDR", ValueHex = $"0x{udr:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x2", "预置 UDR 上拉编码，GetPinPull 应返回 2"));
            return true;
        }

        if (functionName.Contains("GetPinSpeed", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "OSR", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 OSR 后 GetPinSpeed 应返回 HIGH(1)"));
            return true;
        }

        if (functionName.Contains("GetPinOutputType", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "ODR", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 ODR 开漏位后 GetPinOutputType 应返回 OPENDRAIN(1)"));
            return true;
        }

        return false;
    }

    private static bool TryBuildGpioGetterAssertionsAfterSet(
        string setFunctionName,
        string getFunctionName,
        string instance,
        string pinExpr,
        out List<LlTestAssertionSpec> assertions)
    {
        assertions = DefaultTimeoutAssertions();
        if (!getFunctionName.Contains("Get", StringComparison.OrdinalIgnoreCase))
            return false;

        if (setFunctionName.Contains("SetPinPull", StringComparison.OrdinalIgnoreCase)
            && getFunctionName.Contains("GetPinPull", StringComparison.OrdinalIgnoreCase))
        {
            assertions.Insert(0, ReturnValueAssertion("0x2", "SetPinPull(Pull=2) 后 GetPinPull 应返回 2"));
            return true;
        }

        if (setFunctionName.Contains("SetPinSpeed", StringComparison.OrdinalIgnoreCase)
            && getFunctionName.Contains("GetPinSpeed", StringComparison.OrdinalIgnoreCase))
        {
            assertions.Insert(0, ReturnValueAssertion("0x1", "SetPinSpeed(HIGH) 后 GetPinSpeed 应返回 1"));
            return true;
        }

        if (setFunctionName.Contains("SetPinOutputType", StringComparison.OrdinalIgnoreCase)
            && getFunctionName.Contains("GetPinOutputType", StringComparison.OrdinalIgnoreCase))
        {
            assertions.Insert(0, ReturnValueAssertion("0x1", "SetPinOutputType(OD) 后 GetPinOutputType 应返回 1"));
            return true;
        }

        return false;
    }

    private static LlTestAssertionSpec ReturnValueAssertion(string expectedHex, string detail) => new()
    {
        Kind = LlAssertionKind.ReturnValue,
        ExpectedHex = expectedHex,
        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
        RuleSourceDetail = detail
    };

    private static List<LlTestAssertionSpec> BuildGpioWriteAssertions(string functionName, string instance, string pinExpr)
    {
        var pinVal = TestHarnessGenerator.ParseUIntExpression(pinExpr);
        var pinIdx = LlClearStatusRegisterResolver.GpioPinBitIndex(pinVal);
        var list = DefaultTimeoutAssertions();
        list.Add(new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.FunctionCall,
            ExpectedExpression = functionName,
            RuleSource = LlAssertionRuleSource.AutoGeneratedFromSignature,
            RuleSourceDetail = "追踪上下文应标记被测 LL 函数"
        });

        if (functionName.Contains("SetPinPull", StringComparison.OrdinalIgnoreCase))
        {
            var field = 2u << (pinIdx * 2);
            list.Add(GpioRegAssert(instance, "UDR", field, 3u << (pinIdx * 2),
                "SetPinPull(Pull=2) 后 UDR 上下拉编码应写入虚拟寄存器"));
            return list;
        }

        if (functionName.Contains("SetPinSpeed", StringComparison.OrdinalIgnoreCase))
        {
            list.Add(GpioRegAssert(instance, "OSR", pinVal, pinVal,
                "SetPinSpeed(HIGH) 后 OSR 对应位应置位"));
            return list;
        }

        if (functionName.Contains("SetPinOutputType", StringComparison.OrdinalIgnoreCase))
        {
            list.Add(GpioRegAssert(instance, "ODR", pinVal, pinVal,
                "SetPinOutputType(OPENDRAIN) 后 ODR 开漏位应置位"));
            return list;
        }

        var expected = ExpectedPortAfterWrite(functionName, pinExpr);
        list.Add(GpioRegAssert(instance, "DOR", expected,
            functionName.Contains("WriteOutputPort", StringComparison.OrdinalIgnoreCase)
                ? 0xFFFFu
                : (pinVal == 0 ? 0xFFFFu : pinVal),
            "写后检查 DOR（虚拟 GPIO BSR→DOR）"));
        return list;
    }

    private static LlTestAssertionSpec GpioRegAssert(
        string instance, string member, uint expected, uint mask, string detail) => new()
    {
        Kind = LlAssertionKind.RegisterValue,
        InstanceName = instance,
        MemberName = member,
        ExpectedHex = $"0x{expected:X}",
        ExpectedMask = mask,
        RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
        RuleSourceDetail = detail
    };

    private static List<LlTestAssertionSpec> DefaultTimeoutAssertions() =>
    [
        new()
        {
            Kind = LlAssertionKind.Timeout,
            TimeoutMs = 5000,
            RuleSource = LlAssertionRuleSource.Manual,
            RuleSourceDetail = "默认超时"
        }
    ];

    internal static List<(string Name, string ValueExpr)> ExtractNamedMacros(string filePath, string prefix)
    {
        var list = new List<(string, string)>();
        try
        {
            if (!File.Exists(filePath)) return list;
            var text = File.ReadAllText(filePath);
            var matches = Regex.Matches(text,
                $@"#define\s+(?<n>{Regex.Escape(prefix)}[A-Z0-9_]*)\s+(?<v>0x[0-9A-Fa-f]+UL|0x[0-9A-Fa-f]+u?l?|\d+UL|\d+)");
            foreach (Match m in matches)
                list.Add((m.Groups["n"].Value, m.Groups["v"].Value));
        }
        catch
        {
            /* ignore IO */
        }
        return list;
    }
}
