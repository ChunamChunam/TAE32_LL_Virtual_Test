using System.Text.RegularExpressions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Generates editable test cases from real LL inline bodies and SDK/DB macros.
/// One representative case per function: read = write-register then call Get;
/// write = preload baseline then call Set and read-back compare target bits.
/// Does not invent multi-sample / companion-pair / A5A5 interference cases.
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

        // One pin + one instance per LL function — do not fan out ports/pins into extra cases.
        var pinMacros = ExtractNamedMacros(fn.FilePath, "LL_GPIO_PIN_")
            .Where(x => !x.Name.EndsWith("_ALL", StringComparison.Ordinal))
            .Take(1)
            .ToList();

        // Prefer TypeDef-base banks (HRPWM_MST) over alphabetical first (HRPWM_COM).
        var instanceRows = await db.PeripheralInstances.AsNoTracking()
            .Where(x => x.SdkProjectId == fn.SdkProjectId
                        && (x.ModuleName == fn.PeripheralName
                            || (fn.PeripheralName != null && x.Name.StartsWith(fn.PeripheralName))))
            .Select(x => x.Name)
            .ToListAsync(cancellationToken);
        // Prefer module default (ADTMR→TMR9, EFLASH→FLASH) over empty DB shell instances (EFLASH with 0 regs).
        var preferredInstance = InferDefaultInstance(fn.PeripheralName, fn.FunctionName);
        var instances = instanceRows
            .OrderBy(n => preferredInstance is not null
                          && n.Equals(preferredInstance, StringComparison.OrdinalIgnoreCase)
                ? 0
                : 1)
            .ThenBy(n => n.EndsWith("_COM", StringComparison.OrdinalIgnoreCase) ? 2
                : n.Contains("_SLV", StringComparison.OrdinalIgnoreCase) ? 1
                : n.EndsWith("_MST", StringComparison.OrdinalIgnoreCase) ? 0
                : 0)
            .ThenBy(n => n, StringComparer.OrdinalIgnoreCase)
            .Take(1)
            .ToList();
        // EFLASH DB instance is an empty shell; virtual MCU loads FLASH_Type as FLASH.
        if (!string.IsNullOrWhiteSpace(preferredInstance)
            && (instances.Count == 0
                || !instances[0].Equals(preferredInstance, StringComparison.OrdinalIgnoreCase)))
        {
            if (preferredInstance.Equals("FLASH", StringComparison.OrdinalIgnoreCase)
                || preferredInstance.Equals("DMA0", StringComparison.OrdinalIgnoreCase)
                || preferredInstance.StartsWith("HRPWM_", StringComparison.OrdinalIgnoreCase)
                || instances.Count == 0)
                instances = new List<string> { preferredInstance };
        }

        var parameters = fn.ParseParameters.OrderBy(p => p.Position).ToList();
        if (parameters.Count == 0)
        {
            var fromSig = TestHarnessGenerator.ParseParametersFromSignature(
                fn.Signature ?? $"{fn.ReturnType} {fn.FunctionName}({fn.Parameters})");
            if (fromSig.Count > 0)
            {
                parameters = fromSig.Select((p, i) => new LlFunctionParameter
                {
                    Name = p.Name,
                    Type = p.Type,
                    Position = i
                }).ToList();
            }
            // Zero-arg LL (e.g. LL_NVIC_GetPriorityGrouping): continue to BuildGeneric —
            // CORTEX/SCS builders can still emit Ready ReturnValue cases.
        }

        var isGpio = string.Equals(fn.PeripheralName, "GPIO", StringComparison.OrdinalIgnoreCase)
                     || fn.FunctionName.StartsWith("LL_GPIO_", StringComparison.Ordinal);
        var isRcu = string.Equals(fn.PeripheralName, "RCU", StringComparison.OrdinalIgnoreCase)
                    || fn.FunctionName.StartsWith("LL_RCU_", StringComparison.Ordinal);

        if (isGpio)
        {
            var gpioCases = BuildGpioCases(fn, parameters, instances, pinMacros);
            var gpioOne = SelectSingleIntegratedCase(gpioCases);
            ApplyHostPolicy(gpioOne, fn);
            return new[] { gpioOne };
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

        var one = SelectSingleIntegratedCase(cases);
        ApplyHostPolicy(one, fn);
        return new[] { one };
    }

    /// <summary>
    /// Exactly one case per LL function: keep the strongest verifying scenario
    /// (write-back / read-prepared / clear) and drop drafts or duplicate samples.
    /// </summary>
    private static LlTestCaseEditModel SelectSingleIntegratedCase(IReadOnlyList<LlTestCaseEditModel> cases)
    {
        if (cases.Count == 0)
            throw new InvalidOperationException("生成器未产出任何用例");
        if (cases.Count == 1)
            return cases[0];

        static int Score(LlTestCaseEditModel c)
        {
            var score = 0;
            var hasReturn = c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue);
            var hasReg = c.Assertions.Any(a => a.Kind is LlAssertionKind.RegisterValue or LlAssertionKind.PreserveBits);
            var hasSemantic = c.Assertions.Any(a => a.Kind != LlAssertionKind.Timeout);
            if (hasReturn) score += 40;
            if (hasReg) score += 50;
            if (hasSemantic) score += 20;
            if (string.Equals(c.Status, nameof(LlTestCaseStatus.Ready), StringComparison.OrdinalIgnoreCase))
                score += 10;
            if (c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase))
                score -= 30;
            if (c.InitialRegisters.Count > 0)
                score += 5; // write-then-read / read-baseline protocol present
            // Prefer MODIFY_REG write-check over stale SET/CLEAR when both Ready.
            if (c.Notes?.Contains("MODIFY_REG", StringComparison.OrdinalIgnoreCase) == true
                || c.Assertions.Any(a => (a.RuleSourceDetail ?? "").Contains("MODIFY_REG", StringComparison.Ordinal)))
                score += 15;
            // Prefer enum Direction/Parity semantics over raw TE/PEN mask seed.
            if (c.Name.Contains("/dir/", StringComparison.OrdinalIgnoreCase)
                || c.Name.Contains("/none/", StringComparison.OrdinalIgnoreCase)
                || (c.Notes?.Contains("枚举", StringComparison.Ordinal) == true)
                || (c.Notes?.Contains("奇偶", StringComparison.Ordinal) == true))
                score += 25;
            return score;
        }

        return cases.OrderByDescending(Score).First();
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
                // One integrated case per LL write: prefer prelude Write → main Get → ReturnValue;
                // else baseline → Write → register read-back.
                if (IsWriteLike(fn.FunctionName))
                {
                    var readName = SuggestGpioReadCompanion(fn.FunctionName);
                    if (readName is not null
                        && HeaderDeclares(fn.FilePath, readName)
                        && TryBuildGpioGetterAssertionsAfterSet(
                            fn.FunctionName, readName, inst, pin.ValueExpr, out var getterAssertions))
                    {
                        var integrated = BaseModel(fn);
                        integrated.Name = $"{fn.FunctionName}/{inst}/{pin.Name}/write-then-read";
                        integrated.FunctionName = readName;
                        integrated.FunctionSignature = $"uint32_t {readName}(const GPIO_TypeDef *GPIOx)";
                        integrated.Status = nameof(LlTestCaseStatus.Ready);
                        integrated.IsAutoGenerated = true;
                        integrated.PreludeCalls =
                        [
                            new LlTestCallStep
                            {
                                FunctionName = fn.FunctionName,
                                Parameters = BuildParams(parameters, inst, pin.ValueExpr)
                            }
                        ];
                        integrated.Parameters = BuildParamsForRead(readName, inst, pin.ValueExpr);
                        integrated.InitialRegisters =
                        [
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = "0x0" },
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "BSR", ValueHex = "0x0" }
                        ];
                        integrated.Assertions = getterAssertions;
                        // Also keep register write-back so write side is verified in the same case.
                        foreach (var a in BuildGpioWriteAssertions(fn.FunctionName, inst, pin.ValueExpr))
                        {
                            if (a.Kind is LlAssertionKind.RegisterValue or LlAssertionKind.Timeout)
                                continue; // Timeout already in getterAssertions; FunctionCall skipped
                            if (a.Kind == LlAssertionKind.FunctionCall)
                                continue;
                            integrated.Assertions.Insert(0, a);
                        }

                        integrated.Notes =
                            $"单用例整合：先写({fn.FunctionName})→再读({readName})校验返回值，并回读寄存器。宏 {pin.Name}。";
                        cases.Add(integrated);
                    }
                    else
                    {
                        var write = BaseModel(fn);
                        write.Name = $"{fn.FunctionName}/{inst}/{pin.Name}/write-check";
                        write.Status = nameof(LlTestCaseStatus.Ready);
                        write.IsAutoGenerated = true;
                        write.Parameters = BuildParams(parameters, inst, pin.ValueExpr);
                        write.InitialRegisters =
                        [
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "DOR", ValueHex = "0x0" },
                            new LlTestInitialRegister { InstanceName = inst, MemberName = "BSR", ValueHex = "0x0" }
                        ];
                        write.Assertions = BuildGpioWriteAssertions(fn.FunctionName, inst, pin.ValueExpr);
                        write.Notes = $"单用例整合：先读基线→写→回读寄存器。宏 {pin.Name}={pin.ValueExpr}。";
                        cases.Add(write);
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
                    clear.Status = nameof(LlTestCaseStatus.Ready);
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
                            RuleSourceDetail = "先读基线(预置标志)→Clear→回读对比目标位清零"
                        },
                        ..DefaultTimeoutAssertions()
                    ];
                    clear.Notes = "单用例整合校验：预置 ISR→调用 Clear→回读验证。虚拟环境。";
                    cases.Add(clear);
                }
                else if (TryBuildGpioBodyDrivenCase(
                             fn, parameters, inst, pin.Name, pin.ValueExpr, out var bodyCase))
                {
                    cases.Add(bodyCase);
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

        // CORTEX/NVIC/SysTick: CMSIS SCS shadow — ReturnValue via harness out_ret (no peri slots).
        if (!builtSpecial
            && (string.Equals(fn.PeripheralName, "CORTEX", StringComparison.OrdinalIgnoreCase)
                || fn.FunctionName.StartsWith("LL_NVIC_", StringComparison.Ordinal)
                || fn.FunctionName.StartsWith("LL_Init", StringComparison.Ordinal)
                || fn.FunctionName.Equals("LL_Delay_NoISR", StringComparison.Ordinal)))
        {
            var cortex = TryBuildCortexScsCase(fn, draftParams);
            if (cortex is not null)
            {
                cases.Add(cortex);
                builtSpecial = true;
            }
        }

        // Barrier + READ_REG(reg) — OPDR_Refresh: readable / unchanged.
        if (!builtSpecial)
        {
            var live = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
            var refreshRead = Regex.Match(
                live,
                @"READ_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            if (refreshRead.Success
                && (live.Contains("__DSB", StringComparison.Ordinal)
                    || live.Contains("__ISB", StringComparison.Ordinal)
                    || fn.FunctionName.Contains("Refresh", StringComparison.OrdinalIgnoreCase))
                && !live.Contains("WRITE_REG", StringComparison.OrdinalIgnoreCase)
                && !live.Contains("MODIFY_REG", StringComparison.OrdinalIgnoreCase)
                && !live.Contains("SET_BIT", StringComparison.OrdinalIgnoreCase)
                && !live.Contains("CLEAR_BIT", StringComparison.OrdinalIgnoreCase))
            {
                const uint seed = 0xA5A5u;
                var mem = refreshRead.Groups["mem"].Value;
                var model = BaseModel(fn);
                model.Name = $"{fn.FunctionName}/{inst}/{mem}/refresh-read-check";
                model.Status = nameof(LlTestCaseStatus.Ready);
                model.IsAutoGenerated = true;
                model.Parameters = draftParams;
                model.InitialRegisters =
                [
                    new LlTestInitialRegister
                    {
                        InstanceName = inst, MemberName = mem, ValueHex = $"0x{seed:X}"
                    }
                ];
                model.Assertions =
                [
                    new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = inst,
                        MemberName = mem,
                        ExpectedHex = $"0x{seed:X}",
                        ExpectedMask = 0xFFFFFFFFu,
                        RuleSource = LlAssertionRuleSource.FromParseEvidence,
                        RuleSourceDetail = $"Refresh/READ_REG：调用后 {mem} 仍为预置 0x{seed:X}"
                    },
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = $"写校验：屏障+READ_REG → {mem} 不变。虚拟环境。";
                cases.Add(model);
                builtSpecial = true;
            }
        }

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

        // I2C DMAReq: I2Cx->ENABLE = (ENABLE & ~RLSCMD) | DMATXEN — not SET_BIT.
        if (!builtSpecial
            && (fn.FunctionName.Contains("DMAReq", StringComparison.OrdinalIgnoreCase)
                || fn.FunctionName.Contains("DMA_Req", StringComparison.OrdinalIgnoreCase)))
        {
            var dma = TryBuildI2cDmaReqRmwCase(fn, inst, draftParams);
            if (dma is not null)
            {
                cases.Add(dma);
                builtSpecial = true;
            }
        }

        // HandleTransfer: builds ctrl_val then WRITE_REG(CTRL, ctrl_val).
        if (!builtSpecial
            && fn.FunctionName.Contains("HandleTransfer", StringComparison.OrdinalIgnoreCase))
        {
            var ht = TryBuildI2cHandleTransferCase(fn, inst, draftParams);
            if (ht is not null)
            {
                cases.Add(ht);
                builtSpecial = true;
            }
        }

        // Config* wrappers that only call other LL_* setters — assert final CR1 LEN/PEN/MSB.
        if (!builtSpecial
            && fn.FunctionName.Contains("Config", StringComparison.OrdinalIgnoreCase)
            && (fn.FunctionName.Contains("AsyncMode", StringComparison.OrdinalIgnoreCase)
                || fn.FunctionName.Contains("Character", StringComparison.OrdinalIgnoreCase)
                || fn.FunctionName.Contains("MultiProcess", StringComparison.OrdinalIgnoreCase)))
        {
            var cfg = TryBuildUartConfigWrapperCase(fn, inst, draftParams);
            if (cfg is not null)
            {
                cases.Add(cfg);
                builtSpecial = true;
            }
        }

        // Set/Write: MODIFY_REG write-check (chip Mask/Pos + CMSIS RMW formula).
        var modifyChecks = await TryBuildModifyRegWriteCasesAsync(db, fn, inst, draftParams, cancellationToken);
        if (modifyChecks.Count > 0)
        {
            // One representative write-check per LL function — no invented Set→Get pairs.
            cases.Add(modifyChecks[0]);
            builtSpecial = true;
        }

        // Insert*(uint32_t *Addr, Dat): host-buffer RMW; out_ret mirrors *Addr after void call.
        if (!builtSpecial && fn.FunctionName.Contains("Insert", StringComparison.OrdinalIgnoreCase))
        {
            var insertCase = TryBuildInsertHostWordCase(fn, draftParams);
            if (insertCase is not null)
            {
                cases.Add(insertCase);
                builtSpecial = true;
            }
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
                    // One bit-op case per function — stop after first Ready check.
                    break;
                }
            }
            // No invented Enable↔Disable / Assert↔Release companion pairs.
        }

        // At most one case per LL function: prefer clear-check fallback over empty draft.
        if (!builtSpecial)
        {
            var hostCanRun = LlNativeEligibility.DescribeSkip(fn.FunctionName, fn.FilePath, draftParams) is null;
            if (allowClearCheck && hostCanRun && IsClearLike(fn.FunctionName)
                && LlClearStatusRegisterResolver.TryResolve(fn.FunctionName, fn.PeripheralName, out var clrMem, out var clrMask))
            {
                if (clrMask == 0) clrMask = 1u;
                var clear = BaseModel(fn);
                clear.Name = $"{fn.FunctionName}/{inst}/{clrMem}/clear-check";
                clear.Status = nameof(LlTestCaseStatus.Ready);
                clear.IsAutoGenerated = true;
                clear.Parameters = draftParams.Select(p => new LlTestParameterValue
                {
                    Name = p.Name,
                    Type = p.Type,
                    ValueExpression = p.ValueExpression,
                    RuleSource = p.RuleSource
                }).ToList();
                // ClearFlag(ADCx, Mask) with Mask=0 is a no-op on W1C — force target flag bits.
                foreach (var p in clear.Parameters)
                {
                    if (!p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase))
                        continue;
                    if (string.Equals(p.ValueExpression, "0", StringComparison.Ordinal)
                        || string.Equals(p.ValueExpression, "0x0", StringComparison.OrdinalIgnoreCase)
                        || string.IsNullOrWhiteSpace(p.ValueExpression))
                    {
                        p.ValueExpression = $"0x{clrMask:X}";
                        p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                    }
                }

                clear.InitialRegisters =
                [
                    new LlTestInitialRegister { InstanceName = inst, MemberName = clrMem, ValueHex = $"0x{clrMask:X}" }
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
                        RuleSourceDetail =
                            $"单用例整合：先读基线→Clear→回读 (actual & 0x{clrMask:X}) == 0（W1C；{clrMem}）"
                    },
                    ..DefaultTimeoutAssertions()
                ];
                clear.Notes = "单用例整合校验：预置目标位→Clear→回读对比清零。虚拟环境。";
                cases.Add(clear);
            }
            else
            {
                var model = BaseModel(fn);
                model.Name = $"{fn.FunctionName}/{inst}/draft";
                model.Status = nameof(LlTestCaseStatus.Draft);
                model.IsAutoGenerated = true;
                model.Parameters = draftParams;
                // Same case (no new test cases): enrich draft with internal RegisterWrite checks.
                model.Assertions = BuildDraftInternalAssertions(fn, inst, draftParams);
                model.Notes = model.Assertions.Any(a => a.Kind != LlAssertionKind.Timeout)
                    ? "自动草稿：内部补 RegisterWrite/访问校验（不新增用例）。虚拟环境。"
                    : "自动草稿：仅超时断言。未能从 SET_BIT/CLEAR_BIT/WRITE_REG/MODIFY_REG/READ + 寄存器位域生成校验；请手工补断言。";
                cases.Add(model);
            }
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
    // Clear may be bare Msk or (Xxx_Val)<<shift (JSQR ranks).
    private static readonly Regex ModifyRegPattern = new(
        @"MODIFY_REG\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|Val))\b",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>Full MODIFY_REG including RHS (field-value << Pos vs pre-shifted Mask).</summary>
    private static readonly Regex ModifyRegFullPattern = new(
        @"MODIFY_REG\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|Val))\b[^,]*,\s*(?<rhs>[^;]+?)\)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// SET_BIT / CLEAR_BIT(reg-> path, MASK_Msk|_MSK) or runtime Mask param
    /// (e.g. LL_HRPWM_MST_EnableIT(..., Mask)).
    /// </summary>
    // Allow (SPIx)->REG as well as SPIx->REG (common in SPI/I2C-style LL).
    private static readonly Regex SetClearBitPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z_][A-Za-z0-9_]*)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// SET/CLEAR_BIT(reg, (0x1UL &lt;&lt; (Pos &amp; 0x1fUL)) &amp; Xxx_Msk) — SYSCTRL DMARCR DRCR.
    /// Sample Pos = lowest set bit of Msk so effective bit is non-zero.
    /// </summary>
    private static readonly Regex SetClearBitOneShiftPosAndMaskPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(\s*0x1(?:UL|U)?\s*<<\s*\(\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*&\s*0x1[fF](?:UL|U)?\s*\)\s*\)\s*&\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// Channel-lane: SET/CLEAR_BIT(reg, MASK_Msk &lt;&lt; ((Channel%N)*K)).
    /// Sample Channel=0 → effective mask equals base MASK_Msk.
    /// </summary>
    private static readonly Regex SetClearBitChannelShiftedMaskPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)?\s*<<\s*\(",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// Break-input style: SET/CLEAR_BIT(reg, MASK_Msk &amp; (MskBit &lt;&lt; MASK_Pos)).
    /// Sample MskBit=1 (BIT(0)) → effective = Msk &amp; (1&lt;&lt;Pos).
    /// </summary>
    private static readonly Regex SetClearBitMskAndParamShiftPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*&\s*\(\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*<<\s*(?<pos>[A-Za-z0-9_]+_Pos)\s*\)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// SET/CLEAR_BIT(reg, ((Pwmxs) &amp; LL_*_MSK|_MASK) [&lt;&lt; Pos | &gt;&gt; n]).
    /// Covers DMA EnableIT, HRPWM MultiPWM swap/update, MST CounterEnable.
    /// </summary>
    private static readonly Regex SetClearBitRuntimeAndCompositePattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*\(?\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*\)?\s*&\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|MASK|Val))\s*\)?(?:\s*(?:<<\s*(?<shl>[A-Za-z0-9_]+_Pos|\d+)|>>\s*(?<shr>\d+)))?\s*\)?",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// Channel BIT ops: SET/CLEAR_BIT(ADCx->HIER, BIT(((Ch)%LL_ADC_CH_NUMS)))
    /// or BIT(((Num)%N)+Xxx_Pos) / *k+Pos / nested HRPWM. Named-mask regex cannot match → draft/Skipped.
    /// </summary>
    private static readonly Regex SetClearBitChannelBitPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*BIT\s*\(\s*(?<bitexpr>[^;]+?)\s*\)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// REG_OFFSET + channel BIT (ADC AWD / HRPWM EE FastMode / EventBlankLatch):
    /// SET_BIT(LL_*_REG_OFFSET(HRPWMx->Common.EECR0, (Evt_x)/5%…), BIT(((Evt_x)%5)*6+Pos))
    /// or PWM[(Pwmx)%N].REG.EEFR0 + BIT(((Evt_x)%5)*5).
    /// Path may include one nest of brackets; regidx backtracks to <c>), BIT</c>.
    /// </summary>
    private static readonly Regex SetClearBitRegOffsetChannelBitPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>(?:[^()]+|\([^()]*\))+?)\s*,\s*(?<regidx>.+?)\s*\)\s*,\s*BIT\s*\(\s*(?<bitexpr>.+)\s*\)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// ADC DMA style: SET_BIT(LL_ADC_DMA_REG_OFFSET(ADCx->TCR0, Ch%N).TCR, ADC0_TCR0_START_Msk).
    /// </summary>
    private static readonly Regex SetClearBitRegOffsetMemberMaskPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*\.\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// WRITE_REG(LL_*_REG_OFFSET(ADCx->TCR0, Ch%N).TAR, (Addr) & Xxx_Val).
    /// </summary>
    private static readonly Regex WriteRegOffsetMemberPattern = new(
        @"\bWRITE_REG\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*\.\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<val>[^;]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// WRITE_REG(LL_*_REG_OFFSET(ADCx->OFR0, Grp%N), (Val) & Xxx_Val) — no nested .MEM.
    /// Also HRPWM <c>Common.BDUPR0</c> (nested path, flat word bank).
    /// </summary>
    private static readonly Regex WriteRegOffsetFlatPattern = new(
        @"\bWRITE_REG\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[A-Za-z0-9_.]+)\s*,\s*(?<regidx>.+?)\)\s*,\s*(?<val>[^;]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// MODIFY_REG(LL_*_REG_OFFSET(ADCx->TCR0, Ch%N).TCR, Xxx_Msk, rhs) — DMA CIRC/FIX etc.
    /// </summary>
    private static readonly Regex ModifyRegOffsetMemberPattern = new(
        @"MODIFY_REG\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*\.\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*,\s*(?<rhs>[^;]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// READ_BIT_SHIFT(LL_*_REG_OFFSET(...).MEM, Msk, Pos) — ADC DMA IsStopping etc.
    /// </summary>
    private static readonly Regex ReadBitShiftRegOffsetMemberPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*\.\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*,\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// READ_BIT_SHIFT(LL_*_REG_OFFSET(ADCx->OFR0, Grp%N), Msk, Pos) — GetOffset style.
    /// </summary>
    private static readonly Regex ReadBitShiftRegOffsetFlatPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*,\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// READ_REG(LL_*_REG_OFFSET(ADCx->JDR0, Seq%N)) — INJ_ReadConversionData.
    /// </summary>
    private static readonly Regex ReadRegOffsetFlatPattern = new(
        @"READ_REG\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// MODIFY_REG(LL_*_REG_OFFSET(HRPWMx->Common.EECR0, Evt/5%…), 0x1UL&lt;&lt;(lane+Pos), rhs).
    /// Path may be nested; regidx/clear/rhs backtrack on commas carefully via greedy groups.
    /// </summary>
    private static readonly Regex ModifyRegOffsetFlatPattern = new(
        // Path may be PWM[(Pwmx)%N].REG.EEFR0; non-greedy rhs stops at first `);` (EE_SetSrc dual).
        @"MODIFY_REG\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>(?:[^()]+|\([^()]*\))+?)\s*,\s*(?<regidx>.+?)\s*\)\s*,\s*(?<clear>[^,]+)\s*,\s*(?<rhs>.+?)\s*\)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>MODIFY_REG(reg->MEM, BIT(Ch%N), (Mode&amp;1)&lt;&lt;(Ch%N)) — SingleDiff style.</summary>
    private static readonly Regex ModifyRegBitChannelPattern = new(
        @"MODIFY_REG\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*BIT\s*\(\s*(?<bitexpr>[^)]+?)\)\s*,\s*(?<rhs>[^;]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// OC_SetPolarity style: MODIFY_REG(reg, (0x1UL &lt;&lt; Xxx_Pos) &lt;&lt; (Ch*k), ((Pol)&amp;0x1)&lt;&lt;(Pos+Ch*k)).
    /// Sample Channel=0, IsOCN=0 → clear/set use base Pos bit.
    /// </summary>
    private static readonly Regex ModifyRegLiteralPosChannelShiftPattern = new(
        @"MODIFY_REG\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(\s*0x1(?:UL)?\s*<<\s*(?<pos>[A-Za-z0-9_]+_Pos)\s*\)\s*<<\s*\(",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// SET/CLEAR_BIT(LL_*_REG_OFFSET(ADCx->AWD0CR, Num%N), (Mask & Xxx_Val)).
    /// </summary>
    private static readonly Regex SetClearBitRegOffsetRuntimeMaskPattern = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*LL_[A-Za-z0-9_]*REG_OFFSET\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<base>[A-Za-z0-9_]+)\s*,\s*(?<regidx>.+?)\)\s*,\s*\(\s*(?<mskparam>[A-Za-z_][A-Za-z0-9_]*)\s*&\s*(?<val>[A-Za-z0-9_]+_Val)\s*\)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>WRITE_REG(reg->path, VALUE) — VALUE may be literal or named mask macro.</summary>
    /// <remarks>
    /// Val uses greedy <c>[^;]+</c> so nested parens like <c>((Dbc) &amp; Xxx_Val)</c> are kept;
    /// non-greedy previously stopped at the first <c>)</c> and dropped the clamp token.
    /// </remarks>
    private static readonly Regex WriteRegPattern = new(
        @"\bWRITE_REG\s*\(\s*\(?\s*(?<inst>[A-Za-z0-9_]+)\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<val>[^;]+)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>(READ_BIT(reg, Msk) == 0) ? 1UL : 0UL — IsAllChannelDisabled style (requires ?1).</summary>
    private static readonly Regex ReadBitEqZeroBoolPattern = new(
        @"\(\s*READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)\s*==\s*0(?:UL)?\s*\)\s*\?\s*1",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    // 3+ segment chip masks: ADC0_CR_OEN_Msk and HRPWM_MST_MCR1_BDMADIS_Msk.
    private static readonly Regex ChipFieldMskToken = new(
        @"\b(?<tok>[A-Za-z0-9]+(?:_[A-Za-z0-9]+)+_Msk)\b",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    // Flat ADCx->CR or nested HRPWMx->Master.MCR1 / (SPIx)->ENABLE.
    // Mask may be chip *_Msk, LL_*_MSK composite, or literal 0x3fffffffUL (SLV DMAUR).
    private static readonly Regex ReadBitShiftPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>0x[0-9A-Fa-f]+(?:UL|U)?|[A-Za-z0-9_]+_(?:Msk|MSK))\s*,\s*(?<pos>0x[0-9A-Fa-f]+(?:UL|U)?|\d+|[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Scalar Extract: READ_BIT_SHIFT(Info, Xxx_Msk, Xxx_Pos|POSITION_VAL(Msk)) — no peri register path.
    /// </summary>
    private static readonly Regex ReadBitShiftScalarPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*(?<src>[A-Za-z_][A-Za-z0-9_]*)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*,\s*(?:(?<pos>[A-Za-z0-9_]+_Pos)|POSITION_VAL\s*\(\s*\k<msk>\s*\))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Scalar Extract bool: !!READ_BIT(Info, LL_*_MSK) / (READ_BIT(Info, Msk) ? 1 : 0).
    /// </summary>
    private static readonly Regex ReadBitScalarMaskPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*(?<src>[A-Za-z_][A-Za-z0-9_]*)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>sizeof(CANx-&gt;TBUFDT) style FIFO byte-size getters.</summary>
    private static readonly Regex SizeofMemberPattern = new(
        @"sizeof\s*\(\s*(?:\(\s*)?[A-Za-z0-9_]+\s*(?:\)\s*)?->\s*(?<mem>[A-Za-z_][A-Za-z0-9_]*)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Insert*: *tmp &amp;= ~MSK; *tmp |= val; — host uint32_t* buffer RMW.
    /// </summary>
    private static readonly Regex InsertHostWordMaskPattern = new(
        @"\*\s*tmp\s*&=\s*~\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// READ_BIT_SHIFT(reg, Msk &lt;&lt; (Ch*k), Pos + (Ch*k)) — Channel=0 → base field.
    /// </summary>
    private static readonly Regex ReadBitShiftChannelShiftedMaskPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*\)?\s*<<\s*\([^,]+,\s*\(\s*(?<pos>[A-Za-z0-9_]+_Pos)\s*\+",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// READ_BIT(reg, Msk &lt;&lt; (Ch*k)) ? 1 : 0 — Channel=0 → base mask boolean.
    /// </summary>
    private static readonly Regex ReadBitChannelShiftedMaskPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)?\s*<<\s*\(",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// !!READ_BIT(reg, ((Pwmxs)&amp;LL_*_MSK|_MASK) [&lt;&lt; Pos | &gt;&gt; n])) — MultiPWM busy/update.
    /// </summary>
    private static readonly Regex ReadBitRuntimeAndCompositePattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*\(?\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*\)?\s*&\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|MASK|Val))\s*\)?(?:\s*(?:<<\s*(?<shl>[A-Za-z0-9_]+_Pos|\d+)|>>\s*(?<shr>\d+)))?\s*\)?",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>
    /// !!READ_BIT_SHIFT(reg, ((Pwmxs)&amp;MASK)&lt;&lt;Pos, Pos) — IsMultiPWMCountersResetting.
    /// </summary>
    private static readonly Regex ReadBitShiftRuntimeAndCompositePattern = new(
        @"READ_BIT_SHIFT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*\(?\s*\(?\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*\)?\s*&\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|MASK|Val))\s*\)?(?:\s*(?:<<\s*(?<shl>[A-Za-z0-9_]+_Pos|\d+)|>>\s*(?<shr>\d+)))?\s*,\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    /// <summary>Channel flag: READ_BIT_SHIFT(ADCx->DISR, BIT(((Ch)%N)), ((Ch)%M)).</summary>
    private static readonly Regex ReadBitShiftChannelBitPattern = new(
        @"READ_BIT_SHIFT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*BIT\s*\(",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Field getter written as (READ_BIT(reg->MEM, Xxx_Msk) >> Xxx_Pos) — common in WWDG/IWDG/UART/etc.
    /// Equivalent to READ_BIT_SHIFT for expected-value generation.
    /// </summary>
    private static readonly Regex ReadBitThenShiftPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*\)\s*>>\s*(?<pos>[A-Za-z0-9_]+_Pos)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    // READ_BIT(..._Msk|_MSK) — boolean (? 1UL) or masked-return (AllIntPnd_Get / IT_FLAG_MSK).
    private static readonly Regex ReadBitMaskPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// READ_BIT(reg, A_Msk | B_Msk) boolean — IsConversionRunning style.
    /// </summary>
    private static readonly Regex ReadBitOrMaskBoolPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<mskexpr>[^)]+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// IsEnabledIT-style: (READ_BIT(reg, Mask) == (Mask)) ? 1UL : 0UL — Mask is a runtime param.
    /// </summary>
    private static readonly Regex ReadBitParamEqBoolPattern = new(
        @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[A-Za-z_][A-Za-z0-9_]*)\s*\)\s*==\s*\(\s*\k<msk>\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    // Kept name for CollectBody* callers.
    private static readonly Regex ReadBitBoolPattern = ReadBitMaskPattern;

    /// <summary>
    /// READ_REG path may contain one level of nested parens (PWM[(Pwmx)%N].REG.CMPAR).
    /// Do not stop at the first ')' — that used to yield leaf=Pwmx and missing-register fails.
    /// </summary>
    private static readonly Regex ReadRegPattern = new(
        @"READ_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>(?:[^()]+|\([^()]*\))+?)\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// READ_REG(CANx-&gt;RBUFDT[((Num)%N)]) — nested casts beyond one-paren ReadRegPattern.
    /// </summary>
    private static readonly Regex ReadRegBareArrayPattern = new(
        @"READ_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<arr>[A-Za-z_][A-Za-z0-9_]*)\s*\[\s*(?<idx>.+?)\s*\]\s*\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

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

        // Live body wins exclusively when it contains SET/CLEAR — never fall back to possibly
        // stale/wrong LlRegisterAccesses (e.g. DisablePWM2 attributed as CEN1).
        var candidates = new List<string>();
        var liveHasBitOp = !string.IsNullOrWhiteSpace(liveBody)
                           && (SetClearBitPattern.IsMatch(liveBody)
                               || SetClearBitChannelShiftedMaskPattern.IsMatch(liveBody)
                               || SetClearBitMskAndParamShiftPattern.IsMatch(liveBody)
                               || SetClearBitRuntimeAndCompositePattern.IsMatch(liveBody)
                               || SetClearBitChannelBitPattern.IsMatch(liveBody)
                               || SetClearBitRegOffsetChannelBitPattern.IsMatch(liveBody)
                               || SetClearBitRegOffsetMemberMaskPattern.IsMatch(liveBody)
                               || WriteRegOffsetMemberPattern.IsMatch(liveBody)
                               || WriteRegOffsetFlatPattern.IsMatch(liveBody)
                               || WriteRegPattern.IsMatch(liveBody));
        // Live body is MODIFY-only (e.g. SetRxSCLStretchMode): do not fall back to stale
        // LlRegisterAccesses SET_BIT attributions from sibling Enable* helpers.
        var liveModifyOnly = !string.IsNullOrWhiteSpace(liveBody)
                             && ModifyRegPattern.IsMatch(liveBody)
                             && !liveHasBitOp;
        if (liveModifyOnly)
            return results;

        // Name says Set* but body is MODIFY: never trust DB SET_BIT siblings (MSTCH vs RFHSEN).
        if (!string.IsNullOrWhiteSpace(liveBody)
            && ModifyRegPattern.IsMatch(liveBody)
            && fn.FunctionName.Contains("Set", StringComparison.OrdinalIgnoreCase)
            && !SetClearBitPattern.IsMatch(liveBody))
            return results;

        if (liveHasBitOp)
            candidates.Add(liveBody);
        else
        {
            if (!string.IsNullOrWhiteSpace(liveBody))
                candidates.Add(liveBody);
            candidates.AddRange(dbExprs.Where(e => !string.IsNullOrWhiteSpace(e))!);
        }

        foreach (var text in candidates)
        {
            // REG_OFFSET(...).MEM + named mask (ADC DMA ChannelStart).
            var regOffMem = SetClearBitRegOffsetMemberMaskPattern.Match(text);
            if (regOffMem.Success)
            {
                var builtMem = await TryBuildRegOffsetMemberMaskCaseAsync(
                    db, fn, instance, baseParams, regOffMem, ct);
                if (builtMem is not null)
                {
                    results.Add(builtMem);
                    return results;
                }
            }

            // WRITE_REG(REG_OFFSET(...).MEM, Val)
            var writeOff = WriteRegOffsetMemberPattern.Match(text);
            if (writeOff.Success)
            {
                var builtW = await TryBuildRegOffsetWriteCaseAsync(
                    db, fn, instance, baseParams, writeOff, ct);
                if (builtW is not null)
                {
                    results.Add(builtW);
                    return results;
                }
            }

            // WRITE_REG(REG_OFFSET(base), Val) — OFR/GCR flat banks.
            var writeFlat = WriteRegOffsetFlatPattern.Match(text);
            if (writeFlat.Success)
            {
                var builtFlat = await TryBuildRegOffsetWriteCaseAsync(
                    db, fn, instance, baseParams, writeFlat, ct, flatNoLeaf: true);
                if (builtFlat is not null)
                {
                    results.Add(builtFlat);
                    return results;
                }
            }

            // SET/CLEAR REG_OFFSET(..., (Mask & Xxx_Val)) — AWD channel monitor.
            var regOffRt = SetClearBitRegOffsetRuntimeMaskPattern.Match(text);
            if (regOffRt.Success)
            {
                var builtRt = await TryBuildRegOffsetRuntimeMaskCaseAsync(
                    db, fn, instance, baseParams, regOffRt, ct);
                if (builtRt is not null)
                {
                    results.Add(builtRt);
                    return results;
                }
            }

            // REG_OFFSET + BIT(Ch) before flat channel-BIT / named-mask paths.
            var regOffBit = SetClearBitRegOffsetChannelBitPattern.Match(text);
            if (regOffBit.Success)
            {
                var builtOff = TryBuildChannelBitOpCases(
                    fn, instance, baseParams, regOffBit, isRegOffset: true);
                if (builtOff.Count > 0)
                    return builtOff;
            }

            // Channel BIT(Ch%N) / BIT((Num%N)*k+Pos) / literal BIT(n).
            var channelBit = SetClearBitChannelBitPattern.Match(text);
            if (channelBit.Success)
            {
                var built = TryBuildChannelBitOpCases(
                    fn, instance, baseParams, channelBit, isRegOffset: false);
                if (built.Count > 0)
                    return built;
            }

            // MASK_Msk & (MskBit << Pos) — Break0/1 Input / Polarity High/Low.
            var mskAndParam = SetClearBitMskAndParamShiftPattern.Match(text);
            if (mskAndParam.Success)
            {
                var builtAnd = await TryBuildMskAndParamShiftBitOpCaseAsync(
                    db, fn, instance, baseParams, mskAndParam, ct);
                if (builtAnd is not null)
                {
                    results.Add(builtAnd);
                    return results;
                }
            }

            // (0x1UL << (Pos & 0x1f)) & Xxx_Msk — SYSCTRL Set/ResetDMARequestControl.
            var oneShiftPos = SetClearBitOneShiftPosAndMaskPattern.Match(text);
            if (oneShiftPos.Success)
            {
                var builtPos = await TryBuildOneShiftPosAndMaskBitOpCaseAsync(
                    db, fn, instance, baseParams, oneShiftPos, ct);
                if (builtPos is not null)
                {
                    results.Add(builtPos);
                    return results;
                }
            }

            // (Mask & LL_*_MSK) — IntLine set/clear.
            var rtAnd = SetClearBitRuntimeAndCompositePattern.Match(text);
            if (rtAnd.Success)
            {
                var builtRtAnd = await TryBuildRuntimeAndCompositeBitOpCaseAsync(
                    db, fn, instance, baseParams, rtAnd, ct);
                if (builtRtAnd is not null)
                {
                    results.Add(builtRtAnd);
                    return results;
                }
            }

            // MASK_Msk << ((Channel%N)*K) — CxMIE / ChannelTrigger / CCxUG; Channel=0.
            var chShift = SetClearBitChannelShiftedMaskPattern.Match(text);
            if (chShift.Success)
            {
                var builtShift = await TryBuildChannelShiftedMaskBitOpCaseAsync(
                    db, fn, instance, baseParams, chShift, ct);
                if (builtShift is not null)
                {
                    results.Add(builtShift);
                    return results;
                }
            }

            // Prefer SET_BIT for Enable* / CLEAR_BIT for Disable* when both appear
            // (UART EnableLoopback: CLEAR UE then SET LOOP — must not bind CLEAR as the case).
            var setClear = MatchPreferredSetClear(text, fn.FunctionName);
            if (setClear is { Success: true })
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
                // LL_RCU_PLL0CR_VCO_DET (BIT(n)) is a named constant, not a runtime Interrupt param.
                var namedLlConst = bodyMskMacro.StartsWith("LL_", StringComparison.OrdinalIgnoreCase)
                                   && TryParseUintDefineFromFileCandidates(
                                       fn.FilePath, bodyMskMacro, out _);
                var isRuntimeMaskParam = !IsCompileTimeMaskToken(bodyMskMacro) && !namedLlConst;
                string mskMacro;
                uint maskBits;
                var usedTrusted = false;
                string pairNote;
                string trustDetail;

                if (isRuntimeMaskParam)
                {
                    if (!TryResolveRuntimeMaskParam(
                            fn.FilePath, fn.FunctionName, bodyMskMacro,
                            out mskMacro, out maskBits, out var chipTok))
                        continue;
                    bodyMskMacro = chipTok ?? mskMacro;
                    pairNote = $"运行时参数 {setClear.Groups["msk"].Value}→SDK {mskMacro}";
                    trustDetail = $"期望掩码来自 @ref 组宏 {mskMacro}=0x{maskBits:X}";
                }
                else if (namedLlConst
                         && TryParseUintDefineFromFileCandidates(
                             fn.FilePath, bodyMskMacro, out maskBits)
                         && maskBits != 0)
                {
                    // Prefer BIT(n)/named LL_* body constant over function-name EN_Msk trust
                    // (VCODET_Disable must not assert PLL0CR_EN).
                    mskMacro = bodyMskMacro;
                    usedTrusted = false;
                    pairNote = $"断言寄存器 {bodyMember}（体常量 {bodyMskMacro}）";
                    trustDetail = $"期望掩码来自函数体 #define {bodyMskMacro}=0x{maskBits:X}";
                }
                else
                {
                    // DAC0_CR_OEN_Msk embeds CR — must match DACx->CR. Mismatch (e.g. ->SR + CR_OEN)
                    // asserts on the mask's register so the wrong write is caught.
                    _ = ResolveMemberAlignedToMask(
                        bodyMember, bodyMskMacro, out _, out pairNote);

                    // Behavioral expected = what the compiled body will do (body mask), corrected when
                    // function-name channel digit disagrees (DisablePWM2 must not assert CEN1).
                    var resolved = await ResolveBitOpMaskAsync(
                        db, fn, bodyMember, bodyMskMacro, ct);
                    mskMacro = resolved.Macro;
                    maskBits = resolved.Bits;
                    usedTrusted = resolved.UsedNameCorrelation;
                    if (!string.IsNullOrEmpty(resolved.PairNote))
                        pairNote = resolved.PairNote;
                    trustDetail = string.IsNullOrEmpty(resolved.Detail)
                        ? (usedTrusted
                            ? $"期望掩码 {mskMacro}（函数名编号与体一致）"
                            : $"期望掩码来自函数体 {mskMacro}")
                        : resolved.Detail;
                }

                var member = ResolveMemberAlignedToMask(
                    bodyMember, mskMacro, out var alignedMismatch, out var alignedPair);
                if (alignedMismatch)
                    pairNote = alignedPair;

                if (maskBits == 0)
                    continue;

                var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
                var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
                var fieldLabel = TryFieldNameFromMskMacro(mskMacro, member, out var singleField)
                    ? singleField
                    : StripMaskSuffix(mskMacro);

                // One representative channel index from the LL path — no invented edge samples.
                var arrayBound = ResolveArrayBound(accessPath.ArrayIndexExpr, fn.FilePath);
                const uint channelRaw = 0;
                var channelIndex = accessPath.ArrayIndexExpr is not null
                    ? channelRaw % Math.Max(1u, arrayBound)
                    : 0u;
                var targetInstance = ResolveNestedInstance(
                    instance, accessPath, channelIndex, bodyMskMacro);

                // Write protocol: preload baseline (read-before) → LL write → read-back target bits.
                // SET: baseline 0 → expect mask set. CLEAR: baseline mask → expect cleared.
                // WaitBufferRelease: host shim SET then CLEAR so the busy-wait exits → expect 0.
                var hostClearsAfterSet = fn.FunctionName.Contains("WaitBufferRelease", StringComparison.OrdinalIgnoreCase);
                var initialBits = isClear ? maskBits : 0u;
                var expectedTarget = isClear || hostClearsAfterSet ? 0u : maskBits;

                var parameters = CloneParams(baseParams);
                ApplyBitOpChannelParameters(
                    parameters, fn, instance, targetInstance, accessPath, channelRaw);
                if (isRuntimeMaskParam)
                    AssignRuntimeMaskParam(parameters, setClear.Groups["msk"].Value, maskBits, mskMacro);

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

                var trustNote = trustDetail;
                var ruleSource = usedTrusted || isRuntimeMaskParam
                    ? LlAssertionRuleSource.AutoGeneratedFromSdkMacro
                    : LlAssertionRuleSource.FromParseEvidence;

                model.Assertions =
                [
                    new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = targetInstance,
                        MemberName = member,
                        ExpectedHex = $"0x{expectedTarget:X}",
                        ExpectedMask = maskBits,
                        RuleSource = ruleSource,
                        RuleSourceDetail =
                            $"{(isClear ? "CLEAR_BIT" : "SET_BIT")} 先读基线 0x{initialBits:X}，写后回读 " +
                            $"(reg&0x{maskBits:X})==0x{expectedTarget:X}；{pairNote}；{trustNote}"
                    },
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = isClear
                    ? $"写校验：先读基线(预置目标位)→CLEAR→回读对比。path={accessPath.RawPath} " +
                      $"Target={targetInstance}.{member} Mask=0x{maskBits:X}。{trustNote}。"
                    : $"写校验：先读基线(0)→SET→回读对比。path={accessPath.RawPath} " +
                      $"Target={targetInstance}.{member} Mask=0x{maskBits:X}。{trustNote}。";
                results.Add(model);

                return results;
            }

            var write = MatchPreferredWriteReg(text);
            if (!write.Success)
                continue;

            var writePathText = write.Groups["path"].Success
                ? write.Groups["path"].Value
                : "";
            _ = TryParseRegAccessPath(writePathText, out var writePath);
            var writeMember = string.IsNullOrEmpty(writePath.LeafMember)
                ? PathLeaf(write)
                : writePath.LeafMember;
            var writeVal = write.Groups["val"].Value.Trim();
            var writeMskTok = Regex.Match(writeVal, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|MASK|Val))\b",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            // Nested/array only: pass chip mask (Master.MISR + HRPWM_MST_* → HRPWM_MST).
            // Flat paths (ADC/UART ISR…) keep prior instance — do not remap via mask peri.
            var writeMskForNest = (writePath.NestedPrefix is not null || writePath.ArrayIndexExpr is not null)
                                  && writeMskTok.Success
                ? writeMskTok.Groups["msk"].Value
                : null;
            var writeInstance = ResolveNestedInstance(instance, writePath, 0, writeMskForNest);
            var builtWrite = await TryBuildWriteRegCaseAsync(
                db, fn, writeInstance, baseParams, writeMember, writeVal, ct);
            if (builtWrite is not null)
            {
                // Only HRPWM multi-bank aggregate needs TypeDef host pointer remap.
                if (IsHostAggregateModule(fn.PeripheralName)
                    || IsHostAggregateInstance(writeInstance))
                {
                    foreach (var p in builtWrite.Parameters.Where(
                                 TestHarnessGenerator.IsPeripheralTypeDefPointer))
                    {
                        p.ValueExpression = ResolveHostPeriPointer(
                            fn.PeripheralName, instance, writeInstance, p.ValueExpression);
                    }
                }

                // Bare bank TBUFDT[Num%N]: force Num=0 so host writes the mapped TBUFDT word.
                if (writePath.ArrayIndexExpr is not null)
                {
                    ApplyBitOpChannelParameters(
                        builtWrite.Parameters, fn, instance, writeInstance, writePath, 0);
                    foreach (var p in builtWrite.Parameters)
                    {
                        if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                        if (p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Index", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Idx", StringComparison.OrdinalIgnoreCase))
                        {
                            p.ValueExpression = "0";
                            p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                        }
                    }
                }

                results.Add(builtWrite);
                return results;
            }
        }

        return results;
    }

    /// <summary>
    /// SET/CLEAR_BIT(reg, BIT(...)) covering:
    /// flat Ch%N, +Pos, *k+Pos, nested Master/Common/PWM[], REG_OFFSET(AWD0CR,Num), literal BIT(n).
    /// </summary>
    private static List<LlTestCaseEditModel> TryBuildChannelBitOpCases(
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match channelBit,
        bool isRegOffset)
    {
        var results = new List<LlTestCaseEditModel>();
        var op = channelBit.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var bitExpr = channelBit.Groups["bitexpr"].Value;
        if (!TryParseChannelBitFormula(bitExpr, fn.FilePath, out var formula))
            return results;

        string baseMember;
        RegAccessPath accessPath;
        string? regIdxExpr = null;
        string? nestHintMacro = formula.PosMacro is { } pm && pm.EndsWith("_Pos", StringComparison.OrdinalIgnoreCase)
            ? pm[..^4] + "_Msk"
            : null;

        if (isRegOffset)
        {
            var pathText = channelBit.Groups["path"].Success
                ? channelBit.Groups["path"].Value.Trim()
                : channelBit.Groups["base"].Value.Trim();
            regIdxExpr = channelBit.Groups["regidx"].Value.Trim();
            _ = TryParseRegAccessPath(pathText, out accessPath);
            baseMember = string.IsNullOrEmpty(accessPath.LeafMember)
                ? pathText
                : accessPath.LeafMember;
            // Flat fallback when path parse only saw a single token.
            if (string.IsNullOrWhiteSpace(accessPath.NestedPrefix)
                && pathText.Contains('.', StringComparison.Ordinal))
            {
                var leaf = pathText.Split('.').Last();
                accessPath = new RegAccessPath(leaf, pathText, null, pathText.Split('.')[0]);
                baseMember = leaf;
            }
        }
        else
        {
            var pathText = channelBit.Groups["path"].Value;
            _ = TryParseRegAccessPath(pathText, out accessPath);
            baseMember = string.IsNullOrEmpty(accessPath.LeafMember)
                ? pathText.Trim()
                : accessPath.LeafMember;
        }

        if (string.IsNullOrWhiteSpace(baseMember))
            return results;

        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var bitSamples = EnumerateChannelBitSamples(formula);
        var regBound = isRegOffset ? ResolveArrayBound(regIdxExpr, fn.FilePath) : 1u;
        if (regBound == 0) regBound = 1;
        // One representative BIT / REG_OFFSET sample from the LL formula — no invented edges.
        var bitRaw = bitSamples.Count > 0 ? bitSamples[0] : 0u;
        const uint regRaw = 0;

        var pathHasArray = accessPath.ArrayIndexExpr is not null;
        var pathRaw = pathHasArray ? bitRaw : 0u;
        var pathIndex = pathHasArray
            ? pathRaw % Math.Max(1u, ResolveArrayBound(accessPath.ArrayIndexExpr, fn.FilePath))
            : 0u;
        var bitPos = EvalChannelBitPos(formula, bitRaw);
        if (bitPos >= 32)
            return results;

        var member = isRegOffset
            ? ResolveRegOffsetMember(baseMember, regRaw % regBound)
            : baseMember;
        var targetInstance = ResolveNestedInstance(
            instance, accessPath, pathIndex, nestHintMacro);
        if (string.IsNullOrWhiteSpace(targetInstance))
            targetInstance = instance;

        var maskBits = 1u << (int)bitPos;
        var initialBits = isClear ? maskBits : 0u;
        var expectedTarget = isClear ? 0u : maskBits;

        var parameters = CloneParams(baseParams);
        ApplyBitOpChannelParameters(
            parameters, fn, instance, targetInstance, accessPath, pathRaw);
        AssignChannelBitParameters(
            parameters, formula, bitRaw, regIdxExpr, regRaw, isRegOffset);

        var model = BaseModel(fn);
        var scaleNote = formula.Scale != 1 ? $"*{formula.Scale}" : "";
        var posNote = formula.PosOffset != 0 ? $"+{formula.PosOffset}" : "";
        model.Name = formula.IsLiteral
            ? $"{fn.FunctionName}/{targetInstance}/{member}.BIT{bitPos}/literal/{checkSuffix}"
            : $"{fn.FunctionName}/{targetInstance}/{member}.BIT{bitPos}/" +
              $"ch{bitRaw}->{bitPos}{scaleNote}{posNote}/{checkSuffix}";
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

        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expectedTarget:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"{op} BIT({bitExpr.Trim()}) raw={bitRaw}→bit{bitPos} mask=0x{maskBits:X}；" +
                    $"先读基线 0x{initialBits:X}，写后回读对比 0x{expectedTarget:X}"
            },
            ..DefaultTimeoutAssertions()
        ];

        model.Notes =
            $"写校验 BIT：先读基线→{(isClear ? "CLEAR" : "SET")}→回读。{targetInstance}.{member} " +
            $"bit={bitPos} Mask=0x{maskBits:X}。" +
            (isRegOffset ? $" REG_OFFSET {baseMember}+{regRaw % regBound}→{member}。" : "") +
            "虚拟环境。";
        results.Add(model);
        return results;
    }

    /// <summary>
    /// SET/CLEAR_BIT(reg, (Mask &amp; LL_*_MSK)) with Mask=composite bits.
    /// </summary>
    /// <summary>
    /// SET/CLEAR_BIT(reg, (0x1UL &lt;&lt; (Pos &amp; 0x1f)) &amp; Msk). Pos sample = PosFromMask(Msk).
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildOneShiftPosAndMaskBitOpCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match match,
        CancellationToken ct)
    {
        var op = match.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var pathText = match.Groups["path"].Value;
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
            ? PathLeaf(match)
            : accessPath.LeafMember;
        var bodyMskMacro = match.Groups["msk"].Value;
        var paramName = match.Groups["param"].Value;
        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var pairNote);
        var clampBits = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
        if (clampBits == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out clampBits))
            return null;
        if (clampBits == 0) return null;

        var posSample = (uint)PosFromMask(clampBits);
        var maskBits = (1u << (int)(posSample & 0x1fu)) & clampBits;
        if (maskBits == 0) return null;

        var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);
        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var fieldLabel = TryFieldNameFromMskMacro(bodyMskMacro, member, out var singleField)
            ? singleField
            : StripMaskSuffix(bodyMskMacro);
        var initialBits = isClear ? maskBits : 0u;
        var expectedTarget = isClear ? 0u : maskBits;
        var parameters = CloneParams(baseParams);
        ApplyBitOpChannelParameters(parameters, fn, instance, targetInstance, accessPath, 0);
        var posParam = parameters.FirstOrDefault(p =>
            p.Name.Equals(paramName, StringComparison.OrdinalIgnoreCase));
        if (posParam is not null)
        {
            posParam.ValueExpression = posSample.ToString();
            posParam.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
        }

        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/pos{posSample}/{checkSuffix}";
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
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expectedTarget:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.AutoGeneratedFromSdkMacro,
                RuleSourceDetail =
                    $"{op} (1<<({paramName}&0x1f))&{bodyMskMacro}；{paramName}={posSample}→0x{maskBits:X}；{pairNote}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：{op} 1<<(Pos&0x1f)&{bodyMskMacro}，Pos={posSample}→0x{maskBits:X}。虚拟环境。";
        return model;
    }

    private static async Task<LlTestCaseEditModel?> TryBuildRuntimeAndCompositeBitOpCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match match,
        CancellationToken ct)
    {
        var op = match.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var pathText = match.Groups["path"].Value;
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
            ? PathLeaf(match)
            : accessPath.LeafMember;
        var bodyMskMacro = match.Groups["msk"].Value;
        var paramName = match.Groups["param"].Value;
        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var pairNote);
        var clampBits = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
        if (clampBits == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out clampBits))
            clampBits = 0;
        // Xxx_Val = (Xxx_Msk >> Pos) often not a literal — fall back to sibling _Msk.
        if (clampBits == 0
            && bodyMskMacro.EndsWith("_Val", StringComparison.OrdinalIgnoreCase))
        {
            var siblingMsk = bodyMskMacro[..^4] + "_Msk";
            clampBits = await ResolveClearMaskAsync(db, fn, member, siblingMsk, ct);
            if (clampBits == 0)
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, siblingMsk, out clampBits);
        }

        // LL_*_MSK multi-line OR of chip Msk tokens (CR2_SW_UPD_MSK).
        if (clampBits == 0)
        {
            uint orBits = 0;
            foreach (var path in CandidateDefineFiles(fn.FilePath, null))
            {
                var text = TryReadCachedFileText(path);
                if (text is null || !TryExtractDefineBody(text, bodyMskMacro, out var mskBody))
                    continue;
                foreach (Match tm in Regex.Matches(mskBody, @"\b([A-Za-z0-9_]+_(?:Msk|MSK))\b"))
                {
                    if (TryParseUintDefineFromFileCandidates(fn.FilePath, tm.Groups[1].Value, out var one)
                        && one != 0)
                        orBits |= one;
                }

                if (orBits != 0) break;
            }

            clampBits = orBits;
        }

        if (clampBits == 0) return null;

        // ((Pwmxs)&MASK)<<Pos or >>n — assert shifted bits; param keeps pre-shift clamp.
        var maskBits = clampBits;
        if (match.Groups["shl"].Success)
        {
            var shlTok = match.Groups["shl"].Value;
            uint shl = 0;
            if (!uint.TryParse(shlTok, out shl))
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, shlTok, out shl);
            if (shl < 32) maskBits <<= (int)shl;
        }
        else if (match.Groups["shr"].Success
                 && uint.TryParse(match.Groups["shr"].Value, out var shr)
                 && shr < 32)
        {
            maskBits >>= (int)shr;
        }

        if (maskBits == 0) return null;

        var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);
        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var fieldLabel = TryFieldNameFromMskMacro(bodyMskMacro, member, out var singleField)
            ? singleField
            : StripMaskSuffix(bodyMskMacro);
        var initialBits = isClear ? maskBits : 0u;
        var expectedTarget = isClear ? 0u : maskBits;
        var parameters = CloneParams(baseParams);
        ApplyBitOpChannelParameters(parameters, fn, instance, targetInstance, accessPath, 0);
        AssignRuntimeMaskParam(parameters, paramName, clampBits, bodyMskMacro);

        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/mask/{checkSuffix}";
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
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expectedTarget:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.AutoGeneratedFromSdkMacro,
                RuleSourceDetail =
                    $"{op} ({paramName}&{bodyMskMacro})→0x{maskBits:X}；{pairNote}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：{op} Mask&复合宏 {bodyMskMacro}→有效位 0x{maskBits:X}。虚拟环境。";
        return model;
    }

    /// <summary>
    /// READ_BIT/_SHIFT(reg, ((Pwmxs)&amp;MASK)[&lt;&lt;Pos]) → boolean or shifted field.
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildRuntimeAndCompositeReadCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match match,
        bool isShift,
        CancellationToken ct)
    {
        var pathText = match.Groups["path"].Value;
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
            ? pathText.Trim()
            : accessPath.LeafMember;
        var bodyMskMacro = match.Groups["msk"].Value;
        var paramName = match.Groups["param"].Value;
        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var pairNote);

        var clampBits = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
        if (clampBits == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out clampBits))
            clampBits = 0;
        if (clampBits == 0)
        {
            uint orBits = 0;
            foreach (var path in CandidateDefineFiles(fn.FilePath, null))
            {
                var text = TryReadCachedFileText(path);
                if (text is null || !TryExtractDefineBody(text, bodyMskMacro, out var mskBody))
                    continue;
                foreach (Match tm in Regex.Matches(mskBody, @"\b([A-Za-z0-9_]+_(?:Msk|MSK))\b"))
                {
                    if (TryParseUintDefineFromFileCandidates(fn.FilePath, tm.Groups[1].Value, out var one)
                        && one != 0)
                        orBits |= one;
                }

                if (orBits != 0) break;
            }

            clampBits = orBits;
        }

        if (clampBits == 0) return null;

        var maskBits = clampBits;
        if (match.Groups["shl"].Success)
        {
            var shlTok = match.Groups["shl"].Value;
            uint shl = 0;
            if (!uint.TryParse(shlTok, out shl))
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, shlTok, out shl);
            if (shl < 32) maskBits <<= (int)shl;
        }
        else if (match.Groups["shr"].Success
                 && uint.TryParse(match.Groups["shr"].Value, out var shr)
                 && shr < 32)
        {
            maskBits >>= (int)shr;
        }

        if (maskBits == 0) return null;

        var nestMsk = bodyMskMacro;
        if (bodyMskMacro.StartsWith("LL_", StringComparison.OrdinalIgnoreCase))
        {
            var expanded = ExpandDefineBody(fn.FilePath, bodyMskMacro) ?? "";
            var chipTok = ChipFieldMskToken.Match(expanded);
            if (chipTok.Success)
                nestMsk = chipTok.Groups["tok"].Value;
        }

        var targetInstance = ResolveNestedInstance(instance, accessPath, 0, nestMsk);
        var liveBody = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        var isBool = liveBody.Contains("!!", StringComparison.Ordinal)
                     || liveBody.Contains("? 1UL", StringComparison.Ordinal)
                     || liveBody.Contains("?1UL", StringComparison.Ordinal);
        uint expected;
        if (isBool)
            expected = 1u;
        else if (isShift && match.Groups["pos"].Success
                 && TryParseUintDefineFromFileCandidates(
                     fn.FilePath, match.Groups["pos"].Value, out var posLit)
                 && posLit < 32)
            expected = maskBits >> (int)posLit;
        else
            expected = maskBits;

        var parameters = PrepareReadParameters(
            fn, instance, targetInstance, CloneParams(baseParams));
        AssignRuntimeMaskParam(parameters, paramName, clampBits, bodyMskMacro);
        var label = TryFieldNameFromMskMacro(bodyMskMacro, member, out var fnField)
            ? fnField
            : StripMaskSuffix(bodyMskMacro);
        return BuildReadCheckModel(
            fn, targetInstance, parameters, member, initial: maskBits, expectedReturn: expected,
            nameSuffix: $"{member}.{label}/pwmxs/read-check",
            detail:
            $"复合掩码读：({paramName}&{bodyMskMacro})→0x{maskBits:X} seed Expected=0x{expected:X}；{pairNote}",
            notes: $"读校验：Pwmxs 复合掩码 → {targetInstance}.{member}。虚拟环境。");
    }

    /// <summary>
    /// CORTEX LL (NVIC/SysTick): assert via harness out_ret mirroring SCS state after the call.
    /// </summary>
    private static LlTestCaseEditModel? TryBuildCortexScsCase(
        LlFunction fn,
        List<LlTestParameterValue> baseParams)
    {
        const uint group2 = 0x5u; // LL_NVIC_PRIORITYGROUP_2
        const uint clk = 8_000_000u;
        const uint ticks1ms = 1000u;
        var load1ms = (clk / ticks1ms) - 1u; // 7999

        var parameters = CloneParams(baseParams);
        var model = BaseModel(fn);
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.InitialRegisters = [];
        model.Parameters = parameters;

        switch (fn.FunctionName)
        {
            case "LL_NVIC_SetPriorityGrouping":
                SetParam(parameters, "PriorityGroup", group2);
                model.Name = $"{fn.FunctionName}/SCB.AIRCR/group2/write-check";
                model.Assertions =
                [
                    ReturnValueAssertion($"0x{group2:X}", "写后 GetPriorityGrouping 应回读 GROUP_2"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "写校验：SetPriorityGrouping(GROUP_2)→宿主 out_ret=GetPriorityGrouping。虚拟环境。";
                return model;

            case "LL_NVIC_GetPriorityGrouping":
                model.Name = $"{fn.FunctionName}/SCB.AIRCR/group2/read-check";
                model.PreludeCalls =
                [
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriorityGrouping",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "PriorityGroup",
                                Type = "uint32_t",
                                ValueExpression = $"0x{group2:X}",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    }
                ];
                model.Assertions =
                [
                    ReturnValueAssertion($"0x{group2:X}", "预置 GROUP_2 后 GetPriorityGrouping"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "读校验：先 SetPriorityGrouping(GROUP_2) 再 Get。虚拟环境。";
                return model;

            case "LL_NVIC_SetPriority":
                SetParam(parameters, "IRQn", 0);
                SetParam(parameters, "PreemptPriority", 1);
                SetParam(parameters, "SubPriority", 0);
                model.Name = $"{fn.FunctionName}/NVIC.IP0/p1/write-check";
                model.PreludeCalls =
                [
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriorityGrouping",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "PriorityGroup",
                                Type = "uint32_t",
                                ValueExpression = $"0x{group2:X}",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    }
                ];
                // GROUP_2 (0x5) + preempt=1 + sub=0 → EncodePriority readback = 4 (__NVIC_PRIO_BITS=4).
                model.Assertions =
                [
                    ReturnValueAssertion("0x4", "SetPriority 后 NVIC_GetPriority(IRQn) 编码读回"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "写校验：GROUP_2 下 SetPriority(IRQn0,1,0)→宿主 out_ret=GetPriority。虚拟环境。";
                return model;

            case "LL_NVIC_GetPreemptPriority":
                SetParam(parameters, "IRQn", 0);
                SetParam(parameters, "PriorityGroup", group2);
                model.Name = $"{fn.FunctionName}/NVIC.IP0/p1/read-check";
                model.PreludeCalls =
                [
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriorityGrouping",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "PriorityGroup", Type = "uint32_t",
                                ValueExpression = $"0x{group2:X}",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    },
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriority",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "IRQn", Type = "IRQn_Type", ValueExpression = "0",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            },
                            new LlTestParameterValue
                            {
                                Name = "PreemptPriority", Type = "uint32_t", ValueExpression = "0x1",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            },
                            new LlTestParameterValue
                            {
                                Name = "SubPriority", Type = "uint32_t", ValueExpression = "0x0",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    }
                ];
                model.Assertions =
                [
                    ReturnValueAssertion("0x1", "预置 preempt=1 后 GetPreemptPriority"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "读校验：SetPriority(preempt=1) 后 GetPreemptPriority。虚拟环境。";
                return model;

            case "LL_NVIC_GetSubPriority":
                SetParam(parameters, "IRQn", 0);
                SetParam(parameters, "PriorityGroup", group2);
                model.Name = $"{fn.FunctionName}/NVIC.IP0/s0/read-check";
                model.PreludeCalls =
                [
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriorityGrouping",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "PriorityGroup", Type = "uint32_t",
                                ValueExpression = $"0x{group2:X}",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    },
                    new LlTestCallStep
                    {
                        FunctionName = "LL_NVIC_SetPriority",
                        Parameters =
                        [
                            new LlTestParameterValue
                            {
                                Name = "IRQn", Type = "IRQn_Type", ValueExpression = "0",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            },
                            new LlTestParameterValue
                            {
                                Name = "PreemptPriority", Type = "uint32_t", ValueExpression = "0x1",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            },
                            new LlTestParameterValue
                            {
                                Name = "SubPriority", Type = "uint32_t", ValueExpression = "0x0",
                                RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                            }
                        ]
                    }
                ];
                model.Assertions =
                [
                    ReturnValueAssertion("0x0", "预置 sub=0 后 GetSubPriority"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "读校验：SetPriority(sub=0) 后 GetSubPriority。虚拟环境。";
                return model;

            case "LL_InitTick":
                SetParam(parameters, "CPU_Clk_Freq", clk);
                SetParam(parameters, "Ticks", ticks1ms);
                model.Name = $"{fn.FunctionName}/SysTick.LOAD/1ms/write-check";
                model.Assertions =
                [
                    ReturnValueAssertion($"0x{load1ms:X}", $"InitTick → SysTick->LOAD=0x{load1ms:X}"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = $"写校验：InitTick({clk},{ticks1ms})→宿主 out_ret=LOAD。虚拟环境。";
                return model;

            case "LL_Init1msTick":
                SetParam(parameters, "CPU_Clk_Freq", clk);
                model.Name = $"{fn.FunctionName}/SysTick.LOAD/1ms/write-check";
                model.Assertions =
                [
                    ReturnValueAssertion($"0x{load1ms:X}", $"Init1msTick → SysTick->LOAD=0x{load1ms:X}"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = $"写校验：Init1msTick({clk})→宿主 out_ret=LOAD。虚拟环境。";
                return model;

            case "LL_Delay_NoISR":
                SetParam(parameters, "Milliseconds", 1);
                model.Name = $"{fn.FunctionName}/SysTick/host-ack/write-check";
                model.Assertions =
                [
                    ReturnValueAssertion("0x0", "宿主 COUNTFLAG ack 后 Delay 正常返回"),
                    ..DefaultTimeoutAssertions()
                ];
                model.Notes = "写校验：Delay_NoISR 宿主注入 COUNTFLAG 完成等待。虚拟环境。";
                return model;

            default:
                return null;
        }

        static void SetParam(List<LlTestParameterValue> ps, string name, uint value)
        {
            var p = ps.FirstOrDefault(x => x.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
            if (p is null)
            {
                ps.Add(new LlTestParameterValue
                {
                    Name = name,
                    Type = name.Equals("IRQn", StringComparison.OrdinalIgnoreCase) ? "IRQn_Type" : "uint32_t",
                    ValueExpression = $"0x{value:X}",
                    RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition)
                });
                return;
            }

            p.ValueExpression = $"0x{value:X}";
            p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }
    }

    /// <summary>
    /// I2C Enable/DisableDMAReq_*: <c>ENABLE = (ENABLE &amp; ~RLSCMD) [| DMATXEN]</c>.
    /// </summary>
    private static LlTestCaseEditModel? TryBuildI2cDmaReqRmwCase(
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams)
    {
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        if (string.IsNullOrWhiteSpace(body)) return null;
        var m = Regex.Match(
            body,
            @"ENABLE\s*=\s*\([\s\S]*?(?<msk>[A-Za-z0-9_]+_DMA(?:TX|RX)EN_Msk)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (!m.Success) return null;
        var bodyMsk = m.Groups["msk"].Value;
        if (!TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out var mask) || mask == 0)
            return null;
        var isDisable = fn.FunctionName.Contains("Disable", StringComparison.OrdinalIgnoreCase);
        var initial = isDisable ? mask : 0u;
        var expected = isDisable ? 0u : mask;
        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{instance}/ENABLE.{StripMaskSuffix(bodyMsk)}/" +
            $"{(isDisable ? "disable" : "enable")}-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = CloneParams(baseParams);
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance, MemberName = "ENABLE", ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = "ENABLE",
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = mask,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"ENABLE RMW {(isDisable ? "clear" : "set")} {bodyMsk}=0x{mask:X}（RLSCMD 写回 0）"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = $"写校验：I2C DMAReq ENABLE RMW → {bodyMsk}。虚拟环境。";
        return model;
    }

    /// <summary>
    /// LL_I2C_HandleTransfer: START | Direction&lt;&lt;Pos | Count — sample Direction=0 Count=1 AutoEnd=0.
    /// </summary>
    private static LlTestCaseEditModel? TryBuildI2cHandleTransferCase(
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams)
    {
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        if (string.IsNullOrWhiteSpace(body) || !body.Contains("ctrl_val", StringComparison.Ordinal))
            return null;
        if (!TryParseUintDefineFromFileCandidates(fn.FilePath, "I2C0_CTRL_START_Msk", out var start)
            || start == 0)
            return null;
        _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "I2C0_CTRL_I2CCNT_Msk", out var cntMsk);
        if (cntMsk == 0) cntMsk = 0xFFu;
        const uint count = 1u;
        var expected = start | (count & cntMsk);
        var parameters = CloneParams(baseParams);
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (p.Name.Equals("Direction", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("AutoEnd", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = "0";
            else if (p.Name.Equals("Count", StringComparison.OrdinalIgnoreCase))
                p.ValueExpression = count.ToString();
            p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
        }

        var model = BaseModel(fn);
        model.Name = $"{fn.FunctionName}/{instance}/CTRL/write-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance, MemberName = "CTRL", ValueHex = "0x0"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = "CTRL",
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = 0xFFFFFFFFu,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"HandleTransfer Direction=0 Count={count} AutoEnd=0 → CTRL=0x{expected:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = "写校验：HandleTransfer 组装 CTRL。虚拟环境。";
        return model;
    }

    /// <summary>
    /// UART ConfigAsyncMode/Character/MultiProcess: nested LL_* only — assert final CR1/RAR bits.
    /// </summary>
    private static LlTestCaseEditModel? TryBuildUartConfigWrapperCase(
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams)
    {
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        if (!body.Contains("LL_UART_", StringComparison.Ordinal))
            return null;

        // MultiProcess: EnableExtBit + SetRxAddress + EnableRxExtendMode → EBE + RAR + RX extend.
        if (fn.FunctionName.Contains("MultiProcess", StringComparison.OrdinalIgnoreCase))
        {
            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR1_EBE_Msk", out var ebe)
                || ebe == 0
                || !TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR1_REM_Msk", out var rem)
                || rem == 0
                || !TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_RAR_RAR_Msk", out var rarMsk)
                || rarMsk == 0)
                return null;
            const uint addr = 0x5Au;
            var expectedRar = addr & rarMsk;
            var cr1Mask = ebe | rem;
            var parameters = CloneParams(baseParams);
            foreach (var p in parameters)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("NodeAddress", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Addr", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = $"0x{addr:X}";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/{instance}/RAR/config/write-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = parameters;
            model.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = "CR1", ValueHex = "0x0"
                },
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = "RAR", ValueHex = "0x0"
                }
            ];
            model.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = "CR1",
                    ExpectedHex = $"0x{cr1Mask:X}",
                    ExpectedMask = cr1Mask,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = $"ConfigMultiProcess → EBE|REM=0x{cr1Mask:X}"
                },
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = "RAR",
                    ExpectedHex = $"0x{expectedRar:X}",
                    ExpectedMask = rarMsk,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = $"ConfigMultiProcess NodeAddress=0x{addr:X} → RAR"
                },
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "写校验：多处理器模式扩展位+节点地址。虚拟环境。";
            return model;
        }

        // AsyncMode / Character: SetDataWidth(8B) → LEN field = 3.
        if (!TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR1_LEN_Msk", out var lenMsk)
            || lenMsk == 0
            || !TryParseUintDefineFromFileCandidates(fn.FilePath, "LL_UART_DATAWIDTH_8B", out var width8))
            return null;
        var lenPos = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR1_LEN_Pos", out var lp)
            ? (int)lp
            : PosFromMask(lenMsk);
        var expectedLen = (width8 << lenPos) & lenMsk;
        var charParams = CloneParams(baseParams);
        foreach (var p in charParams)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (p.Name.Equals("DataLen", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Len", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = $"0x{width8:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
            else if (p.Name.Equals("Parity", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = "0x0";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
            else if (p.Name.Equals("StopLen", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = "0x0";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
        }

        var charModel = BaseModel(fn);
        charModel.Name = $"{fn.FunctionName}/{instance}/CR1.LEN/config/write-check";
        charModel.Status = nameof(LlTestCaseStatus.Ready);
        charModel.IsAutoGenerated = true;
        charModel.Parameters = charParams;
        charModel.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance, MemberName = "CR1", ValueHex = "0x0"
            }
        ];
        charModel.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = "CR1",
                ExpectedHex = $"0x{expectedLen:X}",
                ExpectedMask = lenMsk,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"Config → DATAWIDTH_8B=0x{width8:X} → LEN=0x{expectedLen:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        charModel.Notes = "写校验：Config 包装最终 CR1.LEN=8bit。虚拟环境。";
        return charModel;
    }

    /// <summary>
    /// CAN Insert*: RMW host uint32_t* buffer; harness returns *Addr via out_ret.
    /// </summary>
    private static LlTestCaseEditModel? TryBuildInsertHostWordCase(
        LlFunction fn,
        List<LlTestParameterValue> baseParams)
    {
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        if (string.IsNullOrWhiteSpace(body)) return null;
        var m = InsertHostWordMaskPattern.Match(body);
        if (!m.Success) return null;
        var mskMacro = m.Groups["msk"].Value;
        if (!TryParseUintDefineFromFileCandidates(fn.FilePath, mskMacro, out var mask) || mask == 0)
            return null;
        var pos = PosFromMask(mask);
        var maxField = mask >> pos;
        var dat = maxField > 1 ? maxField / 2u : 1u;
        if (dat == 0) dat = 1u;
        dat &= maxField;
        if (dat == 0) dat = 1u;
        var expected = (dat << pos) & mask;

        var parameters = CloneParams(baseParams);
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (p.Name.Equals("Dat", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Data", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Val", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Value", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = $"0x{dat:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
        }

        var label = TryFieldNameFromMskMacro(mskMacro, "", out var field)
            ? field
            : StripMaskSuffix(mskMacro);
        var model = BaseModel(fn);
        model.Name = $"{fn.FunctionName}/host/{label}/insert-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters = [];
        model.Assertions =
        [
            ReturnValueAssertion(
                $"0x{expected:X}",
                $"Insert host word：Dat=0x{dat:X} → (*Addr&0x{mask:X})==0x{expected:X}（{mskMacro}）"),
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：Insert 宿主字缓冲 RMW；掩码 {mskMacro}=0x{mask:X} Expected=*Addr=0x{expected:X}。虚拟环境。";
        return model;
    }

    /// <summary>
    /// SET/CLEAR_BIT(reg, MASK_Msk &amp; (Param &lt;&lt; Pos)) with Param=1 (BIT(0) source).
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildMskAndParamShiftBitOpCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match match,
        CancellationToken ct)
    {
        var op = match.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var pathText = match.Groups["path"].Value;
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
            ? PathLeaf(match)
            : accessPath.LeafMember;
        var bodyMskMacro = match.Groups["msk"].Value;
        var posMacro = match.Groups["pos"].Value;
        var paramName = match.Groups["param"].Value;

        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var pairNote);
        var resolved = await ResolveBitOpMaskAsync(db, fn, member, bodyMskMacro, ct);
        var maskFull = resolved.Bits;
        if (maskFull == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out maskFull))
            return null;
        if (maskFull == 0) return null;

        var pos = TryParseUintDefineFromFileCandidates(fn.FilePath, posMacro, out var posLit)
            ? (int)posLit
            : PosFromMask(maskFull);
        if (pos < 0 || pos >= 32) return null;

        // Representative: first break-src bit (LL_ADTMR_BRK_IN_SIGNAL_BREAK0 = BIT(0)).
        const uint paramBits = 1u;
        var maskBits = maskFull & (paramBits << pos);
        if (maskBits == 0) return null;

        var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);
        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var fieldLabel = TryFieldNameFromMskMacro(bodyMskMacro, member, out var singleField)
            ? singleField
            : StripMaskSuffix(bodyMskMacro);

        var initialBits = isClear ? maskBits : 0u;
        var expectedTarget = isClear ? 0u : maskBits;
        var parameters = CloneParams(baseParams);
        ApplyBitOpChannelParameters(parameters, fn, instance, targetInstance, accessPath, 0);
        var p = parameters.FirstOrDefault(x =>
            x.Name.Equals(paramName, StringComparison.OrdinalIgnoreCase));
        if (p is not null)
        {
            p.ValueExpression = $"0x{paramBits:X}";
            p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }

        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/bit0/{checkSuffix}";
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
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expectedTarget:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail =
                    $"{op} Msk&({paramName}<<{posMacro}) Param=0x{paramBits:X} → mask 0x{maskBits:X}；{pairNote}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：{op} 体宏 {bodyMskMacro}&({paramName}<<{pos}) Param=0x{paramBits:X} " +
            $"Mask=0x{maskBits:X}。虚拟环境。";
        return model;
    }

    /// <summary>
    /// SET/CLEAR_BIT(reg, MASK_Msk &lt;&lt; ((Channel%N)*K)) with Channel=0 → base mask.
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildChannelShiftedMaskBitOpCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match match,
        CancellationToken ct)
    {
        var op = match.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var pathText = match.Groups["path"].Value;
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
            ? PathLeaf(match)
            : accessPath.LeafMember;
        var bodyMskMacro = match.Groups["msk"].Value;

        var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var pairNote);
        var resolved = await ResolveBitOpMaskAsync(db, fn, member, bodyMskMacro, ct);
        var maskBits = resolved.Bits;
        if (maskBits == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out maskBits))
            return null;
        if (maskBits == 0) return null;

        var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);
        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var fieldLabel = TryFieldNameFromMskMacro(bodyMskMacro, member, out var singleField)
            ? singleField
            : StripMaskSuffix(bodyMskMacro);

        var initialBits = isClear ? maskBits : 0u;
        var expectedTarget = isClear ? 0u : maskBits;
        var parameters = CloneParams(baseParams);
        ApplyBitOpChannelParameters(parameters, fn, instance, targetInstance, accessPath, 0);
        // Channel lives in the shift expr, not the access path — force lane 0.
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = "0";
                p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
        }

        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{member}.{fieldLabel}/ch0/{checkSuffix}";
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
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expectedTarget:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail =
                    $"{op} {bodyMskMacro}<< (Channel=0) → mask 0x{maskBits:X}；{pairNote}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：{op} 通道移位掩码 Channel=0 → {bodyMskMacro}=0x{maskBits:X}。虚拟环境。";
        return model;
    }

    private readonly record struct ChannelBitFormula(
        bool IsLiteral,
        uint LiteralBit,
        uint Bound,
        uint Scale,
        uint PosOffset,
        string? PosMacro,
        string? IndexParamName,
        bool HasModulo);

    private static bool TryParseChannelBitFormula(
        string bitExpr, string? sourceFile, out ChannelBitFormula formula)
    {
        formula = default;
        if (string.IsNullOrWhiteSpace(bitExpr))
            return false;
        var expr = bitExpr.Trim();

        // Literal BIT(2) / BIT(3)
        var lit = Regex.Match(expr, @"^\(?\s*(?<n>\d+)\s*\)?$");
        if (lit.Success
            && uint.TryParse(lit.Groups["n"].Value, out var litBit)
            && litBit < 32)
        {
            formula = new ChannelBitFormula(true, litBit, 1, 1, 0, null, null, false);
            return true;
        }

        uint posOffset = 0;
        string? posMacro = null;
        var posTok = Regex.Match(expr, @"\+\s*(?<pos>[A-Za-z0-9_]+_Pos)\b",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (posTok.Success)
        {
            posMacro = posTok.Groups["pos"].Value;
            var resolved = false;
            foreach (var path in CandidateDefineFiles(sourceFile, null))
            {
                if (TryParseUintDefineFromFile(path, posMacro, out posOffset))
                {
                    resolved = true;
                    break;
                }
            }

            if (!resolved)
                return false; // never invent Pos
        }

        uint scale = 1;
        var scaleTok = Regex.Match(expr, @"\)\s*\*\s*(?<k>\d+)\s*(?:\+|$)",
            RegexOptions.CultureInvariant);
        if (scaleTok.Success && uint.TryParse(scaleTok.Groups["k"].Value, out var k) && k > 0)
            scale = k;

        var hasMod = expr.Contains('%');
        var bound = hasMod ? ResolveArrayBound(expr, sourceFile) : 32u;
        if (bound == 0) bound = 8;

        var idx = Regex.Match(expr,
            @"\b(?<id>Pwmx|Fltx|Evt_x|Evt|Fil_num|Ch|Num|Pin|Idx|Index|Channel|Unit|Tim|Trigx)\b",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        string? idxName = idx.Success ? idx.Groups["id"].Value : null;
        if (idxName is null)
        {
            // Generic identifier before % or alone (Fil_num-style).
            var any = Regex.Match(expr, @"\b(?<id>[A-Za-z_][A-Za-z0-9_]*)\b");
            if (any.Success
                && !any.Groups["id"].Value.StartsWith("LL_", StringComparison.Ordinal)
                && !any.Groups["id"].Value.EndsWith("_Pos", StringComparison.OrdinalIgnoreCase)
                && !any.Groups["id"].Value.EndsWith("_NUMS", StringComparison.OrdinalIgnoreCase))
                idxName = any.Groups["id"].Value;
        }

        formula = new ChannelBitFormula(
            false, 0, bound, scale, posOffset, posMacro, idxName, hasMod);
        return true;
    }

    private static uint EvalChannelBitPos(ChannelBitFormula formula, uint raw)
    {
        if (formula.IsLiteral)
            return formula.LiteralBit;
        if (!formula.HasModulo)
            return Math.Min(raw, 31u) * formula.Scale + formula.PosOffset;
        var idx = raw % Math.Max(1u, formula.Bound);
        return idx * formula.Scale + formula.PosOffset;
    }

    private static IReadOnlyList<uint> EnumerateChannelBitSamples(ChannelBitFormula formula)
    {
        if (formula.IsLiteral)
            return new uint[] { formula.LiteralBit };

        // One in-range representative index from the LL formula — no invented edge fan-out.
        if (EvalChannelBitPos(formula, 0) < 32)
            return new uint[] { 0 };
        if (EvalChannelBitPos(formula, 1) < 32)
            return new uint[] { 1 };
        return Array.Empty<uint>();
    }

    /// <summary>AWD0CR + 1 → AWD1CR (word-stride REG_OFFSET family).</summary>
    private static string ResolveRegOffsetMember(string baseMember, uint index)
    {
        // REG_OFFSET(BASE, idx) → bank number = baseDigit + idx (EECR2+0→EECR2, AWD0CR+1→AWD1CR).
        var m = Regex.Match(baseMember, @"^(?<pref>.*?)(?<n>\d+)(?<suf>[A-Za-z]*)$");
        if (!m.Success)
            return baseMember;
        var n0 = uint.TryParse(m.Groups["n"].Value, out var n) ? n : 0u;
        return $"{m.Groups["pref"].Value}{n0 + index}{m.Groups["suf"].Value}";
    }

    private static void AssignChannelBitParameters(
        List<LlTestParameterValue> parameters,
        ChannelBitFormula formula,
        uint bitRaw,
        string? regIdxExpr,
        uint regRaw,
        bool isRegOffset)
    {
        if (!formula.IsLiteral && !string.IsNullOrWhiteSpace(formula.IndexParamName))
        {
            var p = parameters.FirstOrDefault(x =>
                !x.Type.Contains('*', StringComparison.Ordinal)
                && x.Name.Equals(formula.IndexParamName, StringComparison.OrdinalIgnoreCase));
            p ??= parameters.FirstOrDefault(x =>
                !x.Type.Contains('*', StringComparison.Ordinal)
                && (x.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Fltx", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Evt_x", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Evt", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Fil_num", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                    || x.Name.Contains("Channel", StringComparison.OrdinalIgnoreCase)));
            if (p is not null)
            {
                p.ValueExpression = bitRaw.ToString();
                p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
        }

        if (!isRegOffset || string.IsNullOrWhiteSpace(regIdxExpr))
            return;

        // Evt_x drives both REG_OFFSET bank and BIT lane — already assigned above; don't overwrite.
        var regNames = Regex.Matches(regIdxExpr, @"\b([A-Za-z_][A-Za-z0-9_]*)\b")
            .Select(m => m.Groups[1].Value)
            .Where(id => !id.StartsWith("LL_", StringComparison.Ordinal)
                         && !id.EndsWith("_NUMS", StringComparison.OrdinalIgnoreCase))
            .ToHashSet(StringComparer.OrdinalIgnoreCase);
        var regParam = parameters.FirstOrDefault(x =>
            !x.Type.Contains('*', StringComparison.Ordinal)
            && regNames.Contains(x.Name)
            && (formula.IndexParamName is null
                || !x.Name.Equals(formula.IndexParamName, StringComparison.OrdinalIgnoreCase)));
        regParam ??= parameters.FirstOrDefault(x =>
            !x.Type.Contains('*', StringComparison.Ordinal)
            && x.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
            && (formula.IndexParamName is null
                || !x.Name.Equals(formula.IndexParamName, StringComparison.OrdinalIgnoreCase)));
        if (regParam is not null)
        {
            regParam.ValueExpression = regRaw.ToString();
            regParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }
    }

    /// <summary>Enable→enable-check, Disable→disable-check; otherwise set/clear-check.</summary>
    private static string ResolveBitOpCheckSuffix(string? functionName, bool isClear)
    {
        var name = functionName ?? "";
        if (name.Contains("Assert", StringComparison.OrdinalIgnoreCase) && !isClear)
            return "assert-check";
        if (name.Contains("Release", StringComparison.OrdinalIgnoreCase) && isClear)
            return "release-check";
        if (!isClear
            && name.Contains("Enable", StringComparison.OrdinalIgnoreCase)
            && !name.Contains("Disable", StringComparison.OrdinalIgnoreCase))
            return "enable-check";
        if (isClear
            && name.Contains("Disable", StringComparison.OrdinalIgnoreCase)
            && !name.Contains("Release", StringComparison.OrdinalIgnoreCase)
            && !name.Contains("Assert", StringComparison.OrdinalIgnoreCase))
            return "disable-check";
        return isClear ? "clear-check" : "set-check";
    }

    /// <summary>
    /// Build complementary pair case when a SET_BIT/CLEAR_BIT companion exists
    /// (Assert↔Release, Enable↔Disable, …) sharing the same register + mask.
    /// </summary>
    private static async Task<LlTestCaseEditModel?> TryBuildComplementBitOpPairAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        LlTestCaseEditModel primaryBitOp,
        List<LlTestParameterValue> draftParams,
        CancellationToken ct)
    {
        var companionName = SuggestComplementFunctionName(fn.FunctionName);
        if (companionName is null || !HeaderDeclares(fn.FilePath, companionName))
            return null;

        var primaryBody = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        var companionBody = TryReadFunctionBodyFromSource(fn.FilePath, companionName) ?? "";
        var primaryOp = SetClearBitPattern.Match(primaryBody);
        var companionOp = SetClearBitPattern.Match(companionBody);
        if (!primaryOp.Success || !companionOp.Success)
            return null;

        var primaryIsClear = primaryOp.Groups["op"].Value.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var companionIsClear = companionOp.Groups["op"].Value.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        if (primaryIsClear == companionIsClear)
            return null; // must be complementary SET vs CLEAR

        _ = TryParseRegAccessPath(primaryOp.Groups["path"].Value, out var primaryPath);
        _ = TryParseRegAccessPath(companionOp.Groups["path"].Value, out var companionPath);
        var primaryMskTok = primaryOp.Groups["msk"].Value;
        var companionMskTok = companionOp.Groups["msk"].Value;
        string? primaryChipTok = primaryMskTok;
        string? companionChipTok = companionMskTok;
        string primaryAlignMacro = primaryMskTok;
        string companionAlignMacro = companionMskTok;

        uint mask;
        if (IsCompileTimeMaskToken(primaryMskTok))
        {
            var primaryMemberProbe = ResolveMemberAlignedToMask(
                primaryPath.LeafMember, primaryMskTok, out _, out _);
            mask = await ResolveClearMaskAsync(db, fn, primaryMemberProbe, primaryMskTok, ct);
        }
        else if (TryResolveRuntimeMaskParam(
                     fn.FilePath, fn.FunctionName, primaryMskTok,
                     out primaryAlignMacro, out mask, out primaryChipTok))
        {
            /* runtime Mask via @ref */
        }
        else
            return null;

        if (mask == 0 && IsCompileTimeMaskToken(companionMskTok))
        {
            var companionMemberProbe = ResolveMemberAlignedToMask(
                companionPath.LeafMember, companionMskTok, out _, out _);
            mask = await ResolveClearMaskAsync(db, fn, companionMemberProbe, companionMskTok, ct);
        }
        else if (mask == 0
                 && TryResolveRuntimeMaskParam(
                     fn.FilePath, companionName, companionMskTok,
                     out companionAlignMacro, out mask, out companionChipTok))
        {
            /* companion runtime Mask */
        }

        if (mask == 0)
            return null;

        var primaryMember = ResolveMemberAlignedToMask(
            primaryPath.LeafMember, primaryAlignMacro, out _, out _);
        var companionMember = ResolveMemberAlignedToMask(
            companionPath.LeafMember, companionAlignMacro, out _, out _);
        if (!string.Equals(primaryMember, companionMember, StringComparison.OrdinalIgnoreCase))
            return null;

        // Same mask (or companion mask equals primary) for high confidence.
        uint companionMask = 0;
        if (IsCompileTimeMaskToken(companionMskTok))
        {
            companionMask = await ResolveClearMaskAsync(
                db, fn, companionMember, companionMskTok, ct);
        }
        else if (TryResolveRuntimeMaskParam(
                     fn.FilePath, companionName, companionMskTok,
                     out companionAlignMacro, out companionMask, out companionChipTok))
        {
            /* ok */
        }

        var confidence = companionMask == mask ? "高" : companionMask == 0 ? "中" : "低";
        if (companionMask != 0 && companionMask != mask)
            return null;

        var nestMsk = primaryChipTok ?? primaryAlignMacro;
        var targetInstance = ResolveNestedInstance(instance, primaryPath, 0, nestMsk);
        var preserveBits = PickUnrelatedPreserveBits(mask);
        var parameters = CloneParams(draftParams);
        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, instance, targetInstance, p.ValueExpression);
        if (!IsCompileTimeMaskToken(primaryMskTok))
            AssignRuntimeMaskParam(parameters, primaryMskTok, mask, primaryAlignMacro);

        // Direction: SET companion as prelude when main CLEARs (Assert→Release);
        // CLEAR companion as prelude when main SETs (Release→Assert).
        //
        // Initial MUST differ from final expected so host delta sync records a Write.
        // Wrong (old): Assert→Release with bit already 0 → Assert sets then Release clears
        // → net zero vs snapshot → empty trace → false RegisterWrite failure.
        // Right: Assert→Release starts with bit SET; Release→Assert starts with bit CLEAR.
        var preludeIsSet = primaryIsClear;
        var initial = primaryIsClear ? (preserveBits | mask) : preserveBits;
        var expected = primaryIsClear ? preserveBits : (preserveBits | mask);
        var assertMask = preserveBits | mask;
        if (assertMask == 0) assertMask = mask;

        var companionParams = CloneParams(parameters);
        var model = BaseModel(fn);
        var dirTag = preludeIsSet ? "assert-then-release" : "release-then-assert";
        if (fn.FunctionName.Contains("Enable", StringComparison.OrdinalIgnoreCase)
            || companionName.Contains("Enable", StringComparison.OrdinalIgnoreCase))
            dirTag = preludeIsSet ? "enable-then-disable" : "disable-then-enable";

        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{primaryMember}/{dirTag}/pair-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.PreludeCalls =
        [
            new LlTestCallStep
            {
                FunctionName = companionName,
                Parameters = companionParams
            }
        ];
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = targetInstance,
                MemberName = primaryMember,
                ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterWrite,
                InstanceName = targetInstance,
                MemberName = primaryMember,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail = $"配对主函数写入 {targetInstance}.{primaryMember}"
            },
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = primaryMember,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = assertMask,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"成对 {companionName} → {fn.FunctionName}：最终 (reg&0x{assertMask:X})=0x{expected:X}；" +
                    $"Mask=0x{mask:X}；可信度={confidence}"
            },
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = primaryMember,
                ExpectedHex = primaryIsClear ? "0x0" : $"0x{mask:X}",
                ExpectedMask = mask,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail = primaryIsClear
                    ? $"配对后目标位清零：(actual & 0x{mask:X}) == 0"
                    : $"配对后目标位置位：(actual & 0x{mask:X}) == 0x{mask:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        if (preserveBits != 0)
        {
            model.Assertions.Insert(model.Assertions.Count - 1, new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.PreserveBits,
                InstanceName = targetInstance,
                MemberName = primaryMember,
                ExpectedHex = $"0x{preserveBits:X}",
                ExpectedMask = preserveBits,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail = $"配对保留位 0x{preserveBits:X}"
            });
        }

        model.Notes =
            $"自动成对校验：主={fn.FunctionName} 关联={companionName}；" +
            $"寄存器={targetInstance}.{primaryMember}；Mask=0x{mask:X}；" +
            $"方式={(preludeIsSet ? "SET→CLEAR" : "CLEAR→SET")}；" +
            $"Initial=0x{initial:X} Expected=0x{expected:X}（保证净变化可同步轨迹）；" +
            $"依据=同路径同Mask互补；可信度={confidence}。";
        _ = ct;
        return model;
    }

    /// <summary>
    /// Map Assert↔Release, Enable↔Disable, Start↔Stop, Lock↔Unlock, …
    /// </summary>
    internal static string? SuggestComplementFunctionName(string functionName)
    {
        var pairs = new (string A, string B)[]
        {
            ("Assert", "Release"),
            ("Release", "Assert"),
            ("Enable", "Disable"),
            ("Disable", "Enable"),
            ("Start", "Stop"),
            ("Stop", "Start"),
            ("Lock", "Unlock"),
            ("Unlock", "Lock"),
            ("Connect", "Disconnect"),
            ("Disconnect", "Connect"),
            ("Open", "Close"),
            ("Close", "Open"),
            ("Activate", "Deactivate"),
            ("Deactivate", "Activate"),
        };

        foreach (var (a, b) in pairs)
        {
            var idx = functionName.IndexOf(a, StringComparison.OrdinalIgnoreCase);
            if (idx < 0) continue;
            // Prefer longer verbs first — pairs list already orders Assert before Enable etc.
            // Avoid Enable matching inside Disable: handled by Disable entry separately.
            if (a.Equals("Enable", StringComparison.OrdinalIgnoreCase)
                && functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase))
                continue;
            return functionName.Remove(idx, a.Length).Insert(idx, MatchCase(functionName, idx, a.Length, b));
        }

        // SetX ↔ ClearX only when verb is a dedicated segment (_Set / _Clear).
        var set = Regex.Match(functionName, @"_(Set)([A-Z]|$)");
        if (set.Success)
            return functionName.Remove(set.Groups[1].Index, 3).Insert(set.Groups[1].Index, "Clear");
        var clear = Regex.Match(functionName, @"_(Clear)([A-Z]|$)");
        if (clear.Success)
            return functionName.Remove(clear.Groups[1].Index, 5).Insert(clear.Groups[1].Index, "Set");

        return null;
    }

    private static string MatchCase(string source, int index, int length, string replacement)
    {
        if (length <= 0 || index >= source.Length) return replacement;
        var sample = source.Substring(index, Math.Min(length, source.Length - index));
        if (sample.All(char.IsUpper)) return replacement.ToUpperInvariant();
        if (char.IsUpper(sample[0]))
            return char.ToUpperInvariant(replacement[0]) + replacement[1..];
        return replacement.ToLowerInvariant();
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

    private static async Task<LlTestCaseEditModel?> TryBuildRegOffsetReadCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match m,
        bool flatNoLeaf,
        CancellationToken ct)
    {
        var baseMem = m.Groups["base"].Value.Trim();
        var leaf = flatNoLeaf || !m.Groups["mem"].Success ? baseMem : m.Groups["mem"].Value.Trim();
        var bodyMsk = m.Groups["msk"].Value;
        var bodyPos = m.Groups["pos"].Success ? m.Groups["pos"].Value : null;
        var regIdx = m.Groups["regidx"].Value.Trim();
        const uint ch = 0;
        var member = flatNoLeaf
            ? ResolveRegOffsetIndexedMember(baseMem, ch)
            : ResolveDmaRegOffsetFlatMember(baseMem, leaf, ch);
        // Prefer chip reg from mask (IIR0_G0A1R_G0A1COEF_Msk → G0A1R) over overlay leaf.
        if (TryParseChipMaskRegAndField(bodyMsk, out var chipReg, out _)
            && !string.IsNullOrEmpty(chipReg)
            && Regex.IsMatch(chipReg, @"^G\d+[AB]\d+R$", RegexOptions.IgnoreCase))
            member = chipReg;

        if (!TryFieldNameFromMskMacro(bodyMsk, member, out var fieldName)
            && !TryParseChipMaskRegAndField(bodyMsk, out _, out fieldName))
            fieldName = StripMaskSuffix(bodyMsk);

        var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
        if (!TryResolveFieldMaskPos(fn.FilePath, field, bodyMsk, bodyPos, out var mask, out var pos)
            || mask == 0)
        {
            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out mask) || mask == 0)
                return null;
            pos = bodyPos is not null
                  && TryParseUintDefineFromFileCandidates(fn.FilePath, bodyPos, out var posLit)
                ? (int)posLit
                : PosFromMask(mask);
        }

        var maxVal = mask >> pos;
        if (maxVal == 0) return null;
        var fieldValue = maxVal > 1 ? maxVal / 2u : 1u;
        if (fieldValue == 0) fieldValue = 1u;
        var initial = (fieldValue << pos) & mask;
        var expected = DeriveFieldReadExpected(initial, mask, pos);

        // DMA Get*TransWidthBytes: return (1 << code) when code is a width enum.
        if (fn.FunctionName.Contains("TransWidthBytes", StringComparison.OrdinalIgnoreCase))
            expected = expected <= 2 ? 1u << (int)expected : 0u;

        var parameters = PrepareReadParameters(fn, instance, instance, CloneParamsLocal(baseParams));
        AssignRegOffsetChannelParam(parameters, regIdx, ch);
        // Signed GetOffset returns int16_t field — keep unsigned expected bits for harness.
        return BuildReadCheckModel(
            fn, instance, parameters, member, initial, expected,
            nameSuffix: $"{member}.{fieldName}/ch{ch}/read-check",
            detail:
            $"REG_OFFSET 读：{member} Mask=0x{mask:X} Pos={pos} Initial=0x{initial:X} Expected=0x{expected:X}",
            notes: $"读校验：REG_OFFSET → {member}.{fieldName}。虚拟环境。");

        static List<LlTestParameterValue> CloneParamsLocal(List<LlTestParameterValue> src)
            => src.Select(p => new LlTestParameterValue
            {
                Name = p.Name,
                Type = p.Type,
                ValueExpression = p.ValueExpression,
                RuleSource = p.RuleSource
            }).ToList();
    }

    private static async Task<LlTestCaseEditModel?> TryBuildRegOffsetRuntimeMaskCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match m,
        CancellationToken ct)
    {
        _ = db;
        var op = m.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var baseMem = m.Groups["base"].Value.Trim();
        var regIdx = m.Groups["regidx"].Value.Trim();
        var valTok = m.Groups["val"].Value;
        var maskParam = m.Groups["mskparam"].Value;
        const uint ch = 0;
        var member = ResolveRegOffsetIndexedMember(baseMem, ch);
        if (!TryParseUintDefineFromFileCandidates(fn.FilePath, valTok, out var clamp) || clamp == 0)
        {
            var mskGuess = valTok.EndsWith("_Val", StringComparison.OrdinalIgnoreCase)
                ? valTok[..^4] + "_Msk"
                : valTok;
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, mskGuess, out clamp);
        }

        if (clamp == 0) return null;
        var maskBits = LowestSetBit(clamp);
        if (maskBits == 0) maskBits = 1u;
        var parameters = CloneParams(baseParams);
        AssignRegOffsetChannelParam(parameters, regIdx, ch);
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (p.Name.Equals(maskParam, StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = $"0x{maskBits:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
        }

        var initial = isClear ? maskBits : 0u;
        var expected = isClear ? 0u : maskBits;
        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{instance}/{member}.{StripMaskSuffix(valTok)}/ch{ch}/{(isClear ? "clear" : "set")}-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance, MemberName = member, ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = member,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"{op} REG_OFFSET({baseMem}) runtime Mask&{valTok}=0x{maskBits:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = $"写校验：REG_OFFSET 运行时掩码 → {member}。虚拟环境。";
        return model;
    }

    private static async Task<LlTestCaseEditModel?> TryBuildRegOffsetModifyCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match m,
        CancellationToken ct,
        bool flatNoLeaf = false)
    {
        var pathText = m.Groups["path"].Success && !string.IsNullOrWhiteSpace(m.Groups["path"].Value)
            ? m.Groups["path"].Value.Trim()
            : m.Groups["base"].Value.Trim();
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var baseMem = string.IsNullOrEmpty(accessPath.LeafMember) ? pathText : accessPath.LeafMember;
        if (pathText.Contains('.', StringComparison.Ordinal)
            && string.IsNullOrWhiteSpace(accessPath.NestedPrefix))
        {
            var parts = pathText.Split('.');
            accessPath = new RegAccessPath(parts[^1], pathText, null, parts[0]);
            baseMem = parts[^1];
        }

        var leaf = flatNoLeaf || !m.Groups["mem"].Success ? baseMem : m.Groups["mem"].Value.Trim();
        var clearExpr = m.Groups["msk"].Success ? m.Groups["msk"].Value : m.Groups["clear"].Value;
        clearExpr = clearExpr.Trim();
        var bodyMsk = clearExpr;
        var rhs = m.Groups["rhs"].Value.Trim();
        var regIdx = m.Groups["regidx"].Value.Trim();
        const uint ch = 0;
        var member = flatNoLeaf
            ? ResolveRegOffsetIndexedMember(baseMem, ch)
            : ResolveDmaRegOffsetFlatMember(baseMem, leaf, ch);
        var targetInstance = ResolveNestedInstance(instance, accessPath, ch, null);

        uint clearMask = 0;
        var namedMsk = Regex.Match(clearExpr, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\b");
        if (namedMsk.Success)
        {
            bodyMsk = namedMsk.Groups["msk"].Value;
            clearMask = await ResolveClearMaskAsync(db, fn, member, bodyMsk, ct);
            if (clearMask == 0)
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out clearMask);
            // (Msk >> Pos) << ((Ch%8)*k) with Ch=0 → field width bits at bit 0.
            if (clearExpr.Contains(">>", StringComparison.Ordinal)
                && TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out var rawMsk)
                && rawMsk != 0)
            {
                var posTok = Regex.Match(clearExpr, @">>\s*(?<pos>[A-Za-z0-9_]+_Pos)");
                var fieldPos = posTok.Success
                               && TryParseUintDefineFromFileCandidates(
                                   fn.FilePath, posTok.Groups["pos"].Value, out var pp)
                    ? (int)pp
                    : PosFromMask(rawMsk);
                var width = rawMsk >> fieldPos;
                if (width == 0) width = rawMsk;
                clearMask = width; // Ch/Seq index 0 → unshifted field lane
            }
            // Msk << ((Fltx%6)*4) with Fltx=0 → base Msk lane.
            else if (clearExpr.Contains("<<", StringComparison.Ordinal)
                     && !clearExpr.Contains(">>", StringComparison.Ordinal))
            {
                // keep clearMask as base field mask at lane 0
            }
        }
        else if (Regex.IsMatch(clearExpr, @"0x[0-9A-Fa-f]+(?:UL)?\s*<<", RegexOptions.IgnoreCase))
        {
            // 0x1UL/0xfUL << (((Evt_x)%5)*k + Xxx_Pos) with Evt_x=0 → width<<Pos.
            // Pos=0 is valid (EE0F_Pos); never treat failed-or-zero parse as "no mask".
            uint width = 1;
            var wTok = Regex.Match(clearExpr, @"0x(?<h>[0-9A-Fa-f]+)", RegexOptions.IgnoreCase);
            if (wTok.Success
                && uint.TryParse(wTok.Groups["h"].Value,
                    System.Globalization.NumberStyles.HexNumber, null, out var w)
                && w != 0)
                width = w;
            uint bitPos = 0;
            var posTok = Regex.Match(clearExpr, @"\+\s*(?<pos>[A-Za-z0-9_]+_Pos)\b");
            if (posTok.Success)
            {
                _ = TryParseUintDefineFromFileCandidates(
                    fn.FilePath, posTok.Groups["pos"].Value, out bitPos);
                bodyMsk = posTok.Groups["pos"].Value;
            }
            else
            {
                var lit = Regex.Match(clearExpr, @"<<\s*\(\s*(?<n>\d+)");
                if (lit.Success && uint.TryParse(lit.Groups["n"].Value, out var bit))
                    bitPos = bit;
            }

            if (bitPos < 32)
                clearMask = width << (int)bitPos;
        }

        if (clearMask == 0) return null;

        var posMacro = Regex.Match(rhs, @"\b(?<pos>[A-Za-z0-9_]+_Pos)\b");
        var pos = posMacro.Success
                  && TryParseUintDefineFromFileCandidates(fn.FilePath, posMacro.Groups["pos"].Value, out var posLit)
            ? (int)posLit
            : PosFromMask(clearMask);

        // Field-value MODIFY: write one representative value into the clear lane (Ch/Time/…).
        // Never expect the entire clearMask unless RHS is a pure mask paste.
        uint setMask = LowestSetBit(clearMask);
        if (setMask == 0) setMask = clearMask;
        if (BitWidthFromMask(clearMask) == 1)
            setMask = clearMask;
        else if (rhs.Contains("!!", StringComparison.Ordinal))
            setMask = clearMask; // (!!(En)) << Pos with 1-bit field already handled above
        else if (pos > 0 && !clearExpr.Contains(">>", StringComparison.Ordinal)
                 && namedMsk.Success)
            setMask = 1u << pos;

        const uint initial = 0u;
        var expected = ComputeModifyRegExpected(initial, clearMask, setMask);
        var parameters = CloneParams(baseParams);
        AssignRegOffsetChannelParam(parameters, regIdx, ch);
        // Field payload is unshifted ((Edge)&0x3)<<Pos — never pass already-shifted mask bits.
        var fieldPayload = pos is >= 0 and < 32 ? setMask >> pos : LowestSetBit(setMask);
        if (fieldPayload == 0) fieldPayload = 1u;
        // SetSequencerRanks: Seq indexes REG_OFFSET; Ch is the channel id payload (not lane).
        var chIsPayload = parameters.Any(p =>
            p.Name.Equals("Seq", StringComparison.OrdinalIgnoreCase)
            || p.Name.Equals("Rank", StringComparison.OrdinalIgnoreCase));
        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            // Lane / bank index (SDK typo Tirgx included).
            if (p.Name.Equals("Evt_x", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Fltx", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Trigx", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Tirgx", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Seq", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Rank", StringComparison.OrdinalIgnoreCase)
                || (!chIsPayload
                    && (p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase))))
            {
                if (string.IsNullOrWhiteSpace(p.ValueExpression)
                    || p.ValueExpression == "0"
                    || p.ValueExpression.Equals("0x0", StringComparison.OrdinalIgnoreCase)
                    || string.Equals(p.RuleSource, "Manual", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }

                continue;
            }

            // Any other scalar is the MODIFY field payload (Pol/Edge/Len/Src/Scl/Ch-for-Seq/…).
            if (string.IsNullOrWhiteSpace(p.ValueExpression)
                || p.ValueExpression == "0"
                || p.ValueExpression.Equals("0x0", StringComparison.OrdinalIgnoreCase)
                || string.Equals(p.RuleSource, "Manual", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = $"0x{fieldPayload:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
        }

        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
        {
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, instance, targetInstance, p.ValueExpression);
        }

        var model = BaseModel(fn);
        model.Name =
            $"{fn.FunctionName}/{targetInstance}/{member}.{StripMaskSuffix(bodyMsk)}/ch{ch}/write-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = targetInstance, MemberName = member, ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = clearMask,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"MODIFY_REG REG_OFFSET({pathText})→{member} mask={bodyMsk}=0x{clearMask:X} set=0x{setMask:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = $"写校验：REG_OFFSET MODIFY → {targetInstance}.{member}。虚拟环境。";
        return model;
    }

    private static async Task<LlTestCaseEditModel?> TryBuildRegOffsetMemberMaskCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match m,
        CancellationToken ct)
    {
        var op = m.Groups["op"].Value.ToUpperInvariant();
        var isClear = op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
        var baseMem = m.Groups["base"].Value.Trim();
        var leaf = m.Groups["mem"].Value.Trim();
        var bodyMsk = m.Groups["msk"].Value;
        var regIdx = m.Groups["regidx"].Value.Trim();
        const uint ch = 0;
        var member = ResolveDmaRegOffsetFlatMember(baseMem, leaf, ch);
        var maskBits = await ResolveClearMaskAsync(db, fn, member, bodyMsk, ct);
        if (maskBits == 0
            && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out maskBits))
            return null;
        if (maskBits == 0) return null;

        var parameters = CloneParams(baseParams);
        AssignRegOffsetChannelParam(parameters, regIdx, ch);
        var checkSuffix = ResolveBitOpCheckSuffix(fn.FunctionName, isClear);
        var initial = isClear ? maskBits : 0u;
        var expected = isClear ? 0u : maskBits;
        var model = BaseModel(fn);
        model.Name = $"{fn.FunctionName}/{instance}/{member}.{StripMaskSuffix(bodyMsk)}/ch{ch}/{checkSuffix}";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = instance, MemberName = member, ValueHex = $"0x{initial:X}"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = instance,
                MemberName = member,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = maskBits,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"{op} REG_OFFSET({baseMem}).{leaf} → {member} mask={bodyMsk}=0x{maskBits:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验：REG_OFFSET DMA/ADC 通道寄存器 {member}。虚拟环境。";
        return model;
    }

    private static async Task<LlTestCaseEditModel?> TryBuildRegOffsetWriteCaseAsync(
        AppDbContext db,
        LlFunction fn,
        string instance,
        List<LlTestParameterValue> baseParams,
        Match m,
        CancellationToken ct,
        bool flatNoLeaf = false)
    {
        _ = db;
        var pathText = m.Groups["path"].Success && !string.IsNullOrWhiteSpace(m.Groups["path"].Value)
            ? m.Groups["path"].Value.Trim()
            : m.Groups["base"].Value.Trim();
        _ = TryParseRegAccessPath(pathText, out var accessPath);
        var baseMem = string.IsNullOrEmpty(accessPath.LeafMember) ? pathText : accessPath.LeafMember;
        if (pathText.Contains('.', StringComparison.Ordinal)
            && string.IsNullOrWhiteSpace(accessPath.NestedPrefix))
        {
            var parts = pathText.Split('.');
            accessPath = new RegAccessPath(parts[^1], pathText, null, parts[0]);
            baseMem = parts[^1];
        }

        var leaf = flatNoLeaf || !m.Groups["mem"].Success ? baseMem : m.Groups["mem"].Value.Trim();
        var valExpr = m.Groups["val"].Value.Trim();
        var regIdx = m.Groups["regidx"].Value.Trim();
        const uint ch = 0;
        var member = flatNoLeaf
            ? ResolveRegOffsetIndexedMember(baseMem, ch)
            : ResolveDmaRegOffsetFlatMember(baseMem, leaf, ch);
        var targetInstance = ResolveNestedInstance(instance, accessPath, ch, null);
        var parameters = CloneParams(baseParams);
        AssignRegOffsetChannelParam(parameters, regIdx, ch);

        uint expected = 1u;
        uint mask = 0xFFFFFFFFu;
        var valTok = Regex.Match(valExpr, @"&\s*(?<val>[A-Za-z0-9_]+_Val)\b");
        if (valTok.Success)
        {
            var mskGuess = valTok.Groups["val"].Value;
            if (mskGuess.EndsWith("_Val", StringComparison.OrdinalIgnoreCase))
                mskGuess = mskGuess[..^4] + "_Msk";
            // IIR0_G0A1R_G0A1COEF_Val → assert G0A1R (overlay leaf is GNA1R).
            if (TryParseChipMaskRegAndField(mskGuess, out var chipReg, out _)
                && !string.IsNullOrEmpty(chipReg)
                && Regex.IsMatch(chipReg, @"^G\d+[AB]\d+R$", RegexOptions.IgnoreCase))
                member = chipReg;

            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, valTok.Groups["val"].Value, out var clamp)
                || clamp == 0)
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, mskGuess, out clamp);

            if (clamp != 0)
            {
                mask = clamp;
                expected = LowestSetBit(clamp);
                if (expected == 0) expected = 1u;
                expected &= clamp;
            }
        }

        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal))
                continue;
            if (p.Name.Equals("Addr", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Len", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Val", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Reg_upd", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Length", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Coef", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Time", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Data", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Value", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("En", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Mode", StringComparison.OrdinalIgnoreCase)
                || Regex.IsMatch(p.Name, @"^[AB]\d+$", RegexOptions.IgnoreCase))
            {
                p.ValueExpression = $"0x{expected:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
        }

        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
        {
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, instance, targetInstance, p.ValueExpression);
        }

        var model = BaseModel(fn);
        model.Name = $"{fn.FunctionName}/{targetInstance}/{member}/ch{ch}/write-check";
        model.Status = nameof(LlTestCaseStatus.Ready);
        model.IsAutoGenerated = true;
        model.Parameters = parameters;
        model.InitialRegisters =
        [
            new LlTestInitialRegister
            {
                InstanceName = targetInstance, MemberName = member, ValueHex = "0x0"
            }
        ];
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{expected:X}",
                ExpectedMask = mask,
                RuleSource = LlAssertionRuleSource.FromParseEvidence,
                RuleSourceDetail =
                    $"WRITE_REG REG_OFFSET({pathText})→{member} Expected=0x{expected:X}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes = $"写校验：REG_OFFSET WRITE → {targetInstance}.{member}。虚拟环境。";
        return model;
    }

    /// <summary>
    /// TCR0 + .TCR → TCR0; TCR0 + .TAR → TAR0 (ADC DMA channel flat map).
    /// IIR: overlay <c>IIR_Coef_TypeDef.GNAxR/GNBxR</c> at <c>G0B0R + grp*sizeof</c>
    /// maps to chip members <c>G{grp}AxR</c> / <c>G{grp}BxR</c> (not GNA1R0).
    /// </summary>
    private static string ResolveDmaRegOffsetFlatMember(string baseMember, string leafMem, uint index)
    {
        // IIR_Coef_TypeDef.GNA1R / GNB0R → G0A1R / G0B0R when grp index is 0.
        var iirLeaf = Regex.Match(
            leafMem, @"^GN(?<kind>[ABab]\d+)R$", RegexOptions.CultureInvariant);
        if (iirLeaf.Success)
            return $"G{index}{iirLeaf.Groups["kind"].Value.ToUpperInvariant()}R";

        var m = Regex.Match(baseMember, @"^(?<pref>[A-Za-z_]+?)(?<n>\d+)(?<suf>[A-Za-z]*)$");
        if (!m.Success)
            return string.IsNullOrEmpty(leafMem) ? baseMember : leafMem + index;
        var pref = m.Groups["pref"].Value;
        var family = leafMem.Equals(pref, StringComparison.OrdinalIgnoreCase)
                     || leafMem.Equals(baseMember, StringComparison.OrdinalIgnoreCase)
            ? pref
            : leafMem;
        return $"{family}{index}{m.Groups["suf"].Value}";
    }

    /// <summary>OFR0 + index → OFR0 / OFR1 (word-stride REG_OFFSET family).</summary>
    private static string ResolveRegOffsetIndexedMember(string baseMember, uint index)
    {
        var m = Regex.Match(baseMember, @"^(?<pref>[A-Za-z_]+?)(?<n>\d+)(?<suf>[A-Za-z]*)$");
        if (!m.Success)
            return baseMember;
        var n0 = uint.TryParse(m.Groups["n"].Value, out var n) ? n : 0u;
        return $"{m.Groups["pref"].Value}{n0 + index}{m.Groups["suf"].Value}";
    }

    private static void AssignRegOffsetChannelParam(
        List<LlTestParameterValue> parameters, string regIdxExpr, uint ch)
    {
        var idxName = Regex.Match(
            regIdxExpr,
            @"\b(?<p>Ch|Channel|Num|Pwmx|Evt_x|Fltx|Trigx|Tirgx)\b",
            RegexOptions.IgnoreCase);
        var name = idxName.Success ? idxName.Groups["p"].Value : "Ch";
        var p = parameters.FirstOrDefault(x =>
            !x.Type.Contains('*', StringComparison.Ordinal)
            && x.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
        p ??= parameters.FirstOrDefault(x =>
            !x.Type.Contains('*', StringComparison.Ordinal)
            && (x.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                || x.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                || x.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                || x.Name.Equals("Evt_x", StringComparison.OrdinalIgnoreCase)));
        if (p is not null)
        {
            p.ValueExpression = ch.ToString();
            p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
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
        string mskLabel = "";
        var writePairNote = $"断言寄存器 {wMember}";

        // _Val is not a sticky mask — handled in the else branch (sibling _Msk fallback).
        var mskTok = Regex.Match(valExpr, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK|MASK))\b",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        // ((Prd) & 0xffUL) / (Evt & 0x7FFFFFUL) — literal clamp without named mask.
        var litClampTok = Regex.Match(
            valExpr,
            @"&\s*(?:0x(?<hex>[0-9A-Fa-f]+)|(?<dec>\d+))(?:UL|U|ull|ULL)?\b",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (mskTok.Success)
        {
            var bodyMsk = mskTok.Groups["msk"].Value;
            // WRITE_REG(ADCx->ISR, ADC0_IER_xxx) style mismatch → assert on mask's register.
            wMember = ResolveMemberAlignedToMask(wMember, bodyMsk, out _, out writePairNote);
            var bodyBits = await ResolveClearMaskAsync(db, fn, wMember, bodyMsk, ct);
            if (bodyBits == 0
                && bodyMsk.EndsWith("_MASK", StringComparison.OrdinalIgnoreCase)
                && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMsk, out bodyBits))
                bodyBits = 0;
            var trusted = await TryResolveTrustedMaskAsync(db, fn, wMember, ct);
            // ClearFlag / W1C: body mask wins (ClearFlag_CC0 uses CC0MIF not CC0OIF;
            // ClearFlag_UPDATE uses SR_UIF not UGR_UG). Trusted only if role-compatible.
            if (IsClearLike(fn.FunctionName))
            {
                if (trusted is { Bits: > 0 }
                    && IsTrustedMaskRoleCompatible(fn.FunctionName, wMember, bodyMsk, trusted.Label)
                    && IsClearFlagTrustedFieldCompatible(fn.FunctionName, bodyMsk, trusted.Label))
                {
                    mask = trusted.Bits;
                    mskLabel = trusted.Label;
                    writeTrusted = true;
                }
                else if (bodyBits != 0)
                {
                    mask = bodyBits;
                    mskLabel = bodyMsk;
                    writeTrusted = false;
                }
                else if (trusted is { Bits: > 0 })
                {
                    mask = trusted.Bits;
                    mskLabel = trusted.Label;
                    writeTrusted = true;
                }
                else
                {
                    mask = 0;
                }
            }
            else if (trusted is { Bits: > 0 }
                     && IsTrustedMaskRoleCompatible(fn.FunctionName, wMember, bodyMsk, trusted.Label))
            {
                mask = trusted.Bits;
                mskLabel = trusted.Label;
                writeTrusted = true;
            }
            else
            {
                mask = bodyBits;
                mskLabel = bodyMsk;
            }

            if (mask == 0) return null;

            // HRPWM SetCounter: WRITE CNTWR|Cnt then wait/clear CNTWR (host shim) → CNTWR bit must be 0.
            if (!IsClearLike(fn.FunctionName)
                && (mskLabel.Contains("CNTWR", StringComparison.OrdinalIgnoreCase)
                    || bodyMsk.Contains("CNTWR", StringComparison.OrdinalIgnoreCase))
                && fn.FunctionName.Contains("SetCounter", StringComparison.OrdinalIgnoreCase))
            {
                var cntwrMask = mask != 0 ? mask : bodyBits;
                if (cntwrMask == 0) cntwrMask = 0x80000u;
                var cntValTok = Regex.Match(valExpr, @"&\s*(?<val>[A-Za-z0-9_]+_(?:Val|VAL))\b");
                uint cntSample = 1u;
                if (cntValTok.Success
                    && TryParseUintDefineFromFileCandidates(fn.FilePath, cntValTok.Groups["val"].Value, out var cntClamp)
                    && cntClamp != 0)
                    cntSample = LowestSetBit(cntClamp) != 0 ? LowestSetBit(cntClamp) : 1u;

                detail =
                    $"WRITE_REG SetCounter：宿主清除 CNTWR 后 (reg&0x{cntwrMask:X})==0；Cnt样本=0x{cntSample:X}";
                var cntModel = BaseModel(fn);
                cntModel.Name = $"{fn.FunctionName}/{instance}/{wMember}/write-check";
                cntModel.Status = nameof(LlTestCaseStatus.Ready);
                cntModel.IsAutoGenerated = true;
                cntModel.Parameters = CloneParams(baseParams);
                foreach (var p in cntModel.Parameters)
                {
                    if (p.Name.Equals("Cnt", StringComparison.OrdinalIgnoreCase))
                    {
                        p.ValueExpression = $"0x{cntSample:X}";
                        p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                    }

                    if (p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                        && string.IsNullOrWhiteSpace(p.ValueExpression))
                        p.ValueExpression = "0";
                }

                cntModel.InitialRegisters =
                [
                    new LlTestInitialRegister
                    {
                        InstanceName = instance, MemberName = wMember, ValueHex = "0x0"
                    }
                ];
                cntModel.Assertions =
                [
                    new LlTestAssertionSpec
                    {
                        Kind = LlAssertionKind.RegisterValue,
                        InstanceName = instance,
                        MemberName = wMember,
                        ExpectedHex = "0x0",
                        ExpectedMask = cntwrMask,
                        RuleSource = LlAssertionRuleSource.FromParseEvidence,
                        RuleSourceDetail = $"{detail}；写后回读对比目标位"
                    },
                    ..DefaultTimeoutAssertions()
                ];
                cntModel.Notes = $"{detail}。虚拟环境。";
                return cntModel;
            }

            if (IsClearLike(fn.FunctionName))
            {
                // W1C: preload flag bits (read-before) → WRITE_REG → read-back target cleared.
                var trust = writeTrusted
                    ? $"期望掩码来自函数名关联的可信源 {mskLabel}"
                    : $"掩码来自体 {mskLabel}（弱可信）";
                detail =
                    $"WRITE_REG W1C：先读基线(预置 0x{mask:X})，写后回读 (reg&0x{mask:X})==0；{writePairNote}；{trust}";
                var clearModel = BaseModel(fn);
                clearModel.Name = $"{fn.FunctionName}/{instance}/{wMember}.{StripMaskSuffix(mskLabel)}/clear-check";
                clearModel.Status = nameof(LlTestCaseStatus.Ready);
                clearModel.IsAutoGenerated = true;
                clearModel.Parameters = CloneParams(baseParams);
                // WRITE_REG(SR, (Mask)&LL_*_MSK): Mask=0 is a W1C no-op — force bits to clear.
                var runtimeMaskParam = Regex.Match(
                    valExpr,
                    @"\(?\s*(?<p>Mask|Flags?|Msk)\s*\)?\s*&",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                if (runtimeMaskParam.Success)
                    AssignRuntimeMaskParam(
                        clearModel.Parameters, runtimeMaskParam.Groups["p"].Value, mask, mskLabel);
                else
                {
                    var maskP = clearModel.Parameters.FirstOrDefault(p =>
                        p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Equals("Flags", StringComparison.OrdinalIgnoreCase));
                    if (maskP is not null)
                        AssignRuntimeMaskParam(clearModel.Parameters, maskP.Name, mask, mskLabel);
                }

                clearModel.InitialRegisters =
                [
                    new LlTestInitialRegister
                    {
                        InstanceName = instance, MemberName = wMember, ValueHex = $"0x{mask:X}"
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
                    ..DefaultTimeoutAssertions()
                ];
                clearModel.Notes = $"{detail}。虚拟环境。";
                return clearModel;
            }

            expected = mask;
            detail = writeTrusted
                ? $"WRITE_REG 先读基线→写→回读 {wMember}；{writePairNote}；期望掩码来自函数名关联的可信源 {mskLabel}"
                : $"WRITE_REG 先读基线→写→回读 {wMember}；{writePairNote}（值/掩码来自 {mskLabel}）";

            // FLASH_KR_KEY_Msk & (((Key) & FLASH_KR_KEY_Val) << Pos) — runtime Key, not full Msk sticky.
            var keyShift = Regex.Match(
                valExpr,
                @"\(\(\s*(?<p>[A-Za-z_][A-Za-z0-9_]*)\s*\)\s*&\s*(?<val>[A-Za-z0-9_]+_Val)\s*\)\s*<<\s*(?<pos>[A-Za-z0-9_]+_Pos)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            if (keyShift.Success)
            {
                uint clamp = 0;
                if (!TryParseUintDefineFromFileCandidates(fn.FilePath, keyShift.Groups["val"].Value, out clamp)
                    || clamp == 0)
                {
                    var mskGuess = keyShift.Groups["val"].Value;
                    if (mskGuess.EndsWith("_Val", StringComparison.OrdinalIgnoreCase))
                        mskGuess = mskGuess[..^4] + "_Msk";
                    _ = TryParseUintDefineFromFileCandidates(fn.FilePath, mskGuess, out clamp);
                }

                if (clamp == 0) clamp = mask != 0 ? mask : 0xFFFFu;
                var posMacro = keyShift.Groups["pos"].Value;
                var pos = TryParseUintDefineFromFileCandidates(fn.FilePath, posMacro, out var posLit)
                    ? (int)posLit
                    : 0;
                var sample = LowestSetBit(clamp);
                if (sample == 0) sample = 1u;
                expected = (sample << pos) & (mask != 0 ? mask : 0xFFFFFFFFu);
                if (expected == 0) expected = sample << pos;
                // Stash for Assign below via mskLabel + synthetic note; Param assigned after CloneParams.
                mskLabel = $"{keyShift.Groups["p"].Value}:{sample:X}";
                detail =
                    $"WRITE_REG Key&Val<<Pos：{keyShift.Groups["p"].Value}=0x{sample:X} → " +
                    $"{wMember}&0x{(mask != 0 ? mask : 0xFFFFFFFFu):X}=0x{expected:X}；{writePairNote}";
            }
        }
        else
        {
            // WRITE_REG(reg, (Val) & Xxx_Val) — resolve clamp from chip header; assign Val param.
            var valTok = Regex.Match(valExpr, @"&\s*(?<val>[A-Za-z0-9_]+_Val)\b");
            if (valTok.Success)
            {
                uint clamp = 0;
                if (!TryParseUintDefineFromFileCandidates(fn.FilePath, valTok.Groups["val"].Value, out clamp)
                    || clamp == 0)
                {
                    // Xxx_Val = Msk>>Pos often not a standalone literal — try sibling _Msk.
                    var mskGuess = valTok.Groups["val"].Value;
                    if (mskGuess.EndsWith("_Val", StringComparison.OrdinalIgnoreCase))
                        mskGuess = mskGuess[..^4] + "_Msk";
                    if (TryParseUintDefineFromFileCandidates(fn.FilePath, mskGuess, out var mskBits)
                        && mskBits != 0)
                        clamp = mskBits;
                }

                if (clamp == 0)
                    return null;

                mask = clamp;
                expected = clamp == 0xFFFFFFFFu ? 0x1u : LowestSetBit(clamp);
                if (expected == 0) expected = 1u;
                expected &= clamp;
                mskLabel = valTok.Groups["val"].Value;
                detail =
                    $"WRITE_REG 先读基线→写→回读 {wMember}&0x{mask:X}=0x{expected:X}；" +
                    $"{writePairNote}（值钳位 {mskLabel}）";
            }
            else if (Regex.IsMatch(valExpr, @"^(0x[0-9A-Fa-f]+|[0-9~]+)(u|U|ul|UL|ull|ULL)?$")
                     || valExpr.Contains("~0", StringComparison.Ordinal)
                     || valExpr.Contains("0xFFFFFFFF", StringComparison.OrdinalIgnoreCase))
            {
                expected = valExpr.Contains('~') || valExpr.Contains("FFFFFFFF", StringComparison.OrdinalIgnoreCase)
                    ? 0xFFFFFFFFu
                    : TestHarnessGenerator.ParseUIntExpression(valExpr);
                mask = 0xFFFFFFFFu;
                // ClearAllIntrFlags / Clear*: WRITE_REG(INTR, ~0) is W1C — expect cleared, not sticky ones.
                if (IsClearLike(fn.FunctionName))
                {
                    var clearAll = BaseModel(fn);
                    clearAll.Name = $"{fn.FunctionName}/{instance}/{wMember}/clear-check";
                    clearAll.Status = nameof(LlTestCaseStatus.Ready);
                    clearAll.IsAutoGenerated = true;
                    clearAll.Parameters = CloneParams(baseParams);
                    clearAll.InitialRegisters =
                    [
                        new LlTestInitialRegister
                        {
                            InstanceName = instance, MemberName = wMember, ValueHex = "0xFFFFFFFF"
                        }
                    ];
                    clearAll.Assertions =
                    [
                        new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.RegisterValue,
                            InstanceName = instance,
                            MemberName = wMember,
                            ExpectedHex = "0x0",
                            ExpectedMask = 0xFFFFFFFFu,
                            RuleSource = LlAssertionRuleSource.FromParseEvidence,
                            RuleSourceDetail =
                                $"WRITE_REG W1C 全清：预置 0xFFFFFFFF→写→回读 {wMember}==0"
                        },
                        ..DefaultTimeoutAssertions()
                    ];
                    clearAll.Notes = "写校验：W1C 全标志清除。虚拟环境。";
                    return clearAll;
                }

                detail = $"WRITE_REG 先读基线→写→回读 {wMember} == 0x{expected:X}；{writePairNote}";
            }
            else if (litClampTok.Success
                     && (litClampTok.Groups["hex"].Success || litClampTok.Groups["dec"].Success))
            {
                uint clamp = 0;
                if (litClampTok.Groups["hex"].Success)
                    _ = uint.TryParse(
                        litClampTok.Groups["hex"].Value,
                        System.Globalization.NumberStyles.HexNumber, null, out clamp);
                else
                    _ = uint.TryParse(litClampTok.Groups["dec"].Value, out clamp);
                if (clamp == 0) return null;
                mask = clamp;
                expected = LowestSetBit(clamp);
                if (expected == 0) expected = 1u;
                expected &= clamp;
                mskLabel = $"0x{clamp:X}";
                detail =
                    $"WRITE_REG 先读基线→写→回读 {wMember}&0x{mask:X}==0x{expected:X}；字面钳位；{writePairNote}";
            }
            else if (Regex.IsMatch(
                         valExpr.Trim(),
                         @"^(?:\(\s*uint32_t\s*\)\s*)?\(?\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)?$",
                         RegexOptions.IgnoreCase))
            {
                var paramName = Regex.Match(
                    valExpr.Trim(),
                    @"([A-Za-z_][A-Za-z0-9_]*)\s*\)?\s*$").Groups[1].Value;
                // Named key/constant (LL_IWDG_KEY_ENABLE=0xCCCC, KEY_WR_ACCESS_DISABLE=0) —
                // not a runtime param defaulting to 0x1. Allow literal 0.
                var keyResolved = false;
                uint keyLit = 0;
                if (paramName.StartsWith("LL_", StringComparison.OrdinalIgnoreCase)
                    || paramName.Contains("KEY", StringComparison.OrdinalIgnoreCase))
                {
                    foreach (var path in CandidateDefineFiles(fn.FilePath, null))
                    {
                        if (TryParseUintDefineFromFile(path, paramName, out keyLit))
                        {
                            keyResolved = true;
                            break;
                        }
                    }
                }
                else if (TryParseUintDefineFromFileCandidates(fn.FilePath, paramName, out keyLit))
                {
                    keyResolved = true;
                }

                if (keyResolved)
                {
                    expected = keyLit;
                    mask = 0xFFFFFFFFu;
                    mskLabel = paramName;
                    detail =
                        $"WRITE_REG 先读基线→写→回读 {wMember}==0x{expected:X}；{writePairNote}（常量 {mskLabel}）";
                }
                // ClearFlag(Mask/FlagMask/IntPnd): WRITE_REG W1C with runtime mask — not sticky 0x1.
                else if (IsClearLike(fn.FunctionName)
                    && (paramName.Equals("Mask", StringComparison.OrdinalIgnoreCase)
                        || paramName.Equals("FlagMask", StringComparison.OrdinalIgnoreCase)
                        || paramName.Equals("Flag", StringComparison.OrdinalIgnoreCase)
                        || paramName.Equals("Flags", StringComparison.OrdinalIgnoreCase)
                        || paramName.Equals("IntPnd", StringComparison.OrdinalIgnoreCase)
                        || paramName.Equals("IntIt", StringComparison.OrdinalIgnoreCase))
                    && TryResolveRuntimeMaskParam(
                        fn.FilePath, fn.FunctionName, paramName,
                        out var llMacro, out var rtMask, out _)
                    && rtMask != 0)
                {
                    var clearModel = BaseModel(fn);
                    clearModel.Name =
                        $"{fn.FunctionName}/{instance}/{wMember}.{StripMaskSuffix(llMacro)}/clear-check";
                    clearModel.Status = nameof(LlTestCaseStatus.Ready);
                    clearModel.IsAutoGenerated = true;
                    clearModel.Parameters = CloneParams(baseParams);
                    AssignRuntimeMaskParam(clearModel.Parameters, paramName, rtMask, llMacro);
                    clearModel.InitialRegisters =
                    [
                        new LlTestInitialRegister
                        {
                            InstanceName = instance, MemberName = wMember, ValueHex = $"0x{rtMask:X}"
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
                            ExpectedMask = rtMask,
                            RuleSource = LlAssertionRuleSource.AutoGeneratedFromSdkMacro,
                            RuleSourceDetail =
                                $"WRITE_REG W1C Mask={llMacro}=0x{rtMask:X}：预置→写→回读清零"
                        },
                        ..DefaultTimeoutAssertions()
                    ];
                    clearModel.Notes =
                        $"写校验：ClearFlag 运行时 Mask={llMacro}=0x{rtMask:X} W1C。虚拟环境。";
                    return clearModel;
                }

                else if (IsClearLike(fn.FunctionName))
                    return null;
                else
                {
                    // WRITE_REG(reg, Val) — raw value parameter (CAN TBUFDT[Num]=Val).
                    expected = 0x1u;
                    mask = 0xFFFFFFFFu;
                    mskLabel = paramName;
                    detail =
                        $"WRITE_REG 先读基线→写→回读 {wMember}==0x{expected:X}；{writePairNote}（参数 {mskLabel}）";
                }
            }
            else
            {
                // WRITE_REG(ISR, BIT(((Fltx)%N) + FLT0_Pos)) — W1C lane clear / sticky bit set.
                var bitLane = Regex.Match(
                    valExpr,
                    @"\bBIT\s*\(\s*(?<bitexpr>[^;]+?)\s*\)\s*$",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
                if (!bitLane.Success)
                    return null;
                var bitExpr = bitLane.Groups["bitexpr"].Value;
                var posTok = Regex.Match(bitExpr, @"(?<pos>[A-Za-z0-9_]+_Pos)\b");
                uint bitPos = 0;
                if (posTok.Success)
                {
                    if (!TryParseUintDefineFromFileCandidates(fn.FilePath, posTok.Groups["pos"].Value, out bitPos))
                        return null;
                }
                // Fltx/Pwmx sample 0 → effective shift == base Pos (or 0 for BIT((Ch)%N)).
                var shift = (int)(bitPos % 32);
                mask = 1u << shift;
                expected = mask;
                mskLabel = posTok.Success ? posTok.Groups["pos"].Value : $"BIT{shift}";
                detail =
                    $"WRITE_REG BIT(lane0+{mskLabel})：先读基线→写→回读 {wMember}&0x{mask:X}；{writePairNote}";

                if (IsClearLike(fn.FunctionName))
                {
                    var clearBit = BaseModel(fn);
                    clearBit.Name =
                        $"{fn.FunctionName}/{instance}/{wMember}.{StripMaskSuffix(mskLabel)}/clear-check";
                    clearBit.Status = nameof(LlTestCaseStatus.Ready);
                    clearBit.IsAutoGenerated = true;
                    clearBit.Parameters = CloneParams(baseParams);
                    foreach (var p in clearBit.Parameters)
                    {
                        if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                        if (p.Name.Equals("Fltx", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                            || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase))
                        {
                            p.ValueExpression = "0";
                            p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                        }
                    }

                    clearBit.InitialRegisters =
                    [
                        new LlTestInitialRegister
                        {
                            InstanceName = instance, MemberName = wMember, ValueHex = $"0x{mask:X}"
                        }
                    ];
                    clearBit.Assertions =
                    [
                        new LlTestAssertionSpec
                        {
                            Kind = LlAssertionKind.RegisterValue,
                            InstanceName = instance,
                            MemberName = wMember,
                            ExpectedHex = "0x0",
                            ExpectedMask = mask,
                            RuleSource = LlAssertionRuleSource.FromParseEvidence,
                            RuleSourceDetail =
                                $"WRITE_REG W1C BIT(lane0)：预置 0x{mask:X}→写→回读 (reg&0x{mask:X})==0"
                        },
                        ..DefaultTimeoutAssertions()
                    ];
                    clearBit.Notes =
                        $"写校验：BIT(param%N+Pos) W1C ClearFlag。{detail}。虚拟环境。";
                    return clearBit;
                }
            }
        }

        // WRITE_REG: baseline 0 → write → read-back compare written value (no invented A5A5).
        const uint writeInitial = 0u;
        var writeAssertMask = mask == 0 ? 0xFFFFFFFFu : mask;

        var wModel = BaseModel(fn);
        wModel.Name = $"{fn.FunctionName}/{instance}/{wMember}/write-check";
        wModel.Status = nameof(LlTestCaseStatus.Ready);
        wModel.IsAutoGenerated = true;
        wModel.Parameters = CloneParams(baseParams);
        // Ensure Val/Period/Addr/Len/Key params are non-zero so host buffer actually changes.
        // SetKey stashes "Key:SAMPLE" in mskLabel when Key&Val<<Pos was parsed.
        uint? keySample = null;
        string? keyParamName = null;
        var keyMeta = Regex.Match(mskLabel, @"^(?<p>[A-Za-z_][A-Za-z0-9_]*):(?<hex>[0-9A-Fa-f]+)$");
        if (keyMeta.Success
            && uint.TryParse(keyMeta.Groups["hex"].Value,
                System.Globalization.NumberStyles.HexNumber, null, out var ks))
        {
            keyParamName = keyMeta.Groups["p"].Value;
            keySample = ks;
        }

        // Payload names from body: ((Prd)&Val), ((Evt)&0xFFFFFFFFUL), ((Mask)&LL_*_MSK).
        var payloadNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        foreach (Match pm in Regex.Matches(
                     valExpr,
                     @"\(\s*(?<p>[A-Za-z_][A-Za-z0-9_]*)\s*\)\s*&",
                     RegexOptions.CultureInvariant))
        {
            var n = pm.Groups["p"].Value;
            if (n.Equals("UL", StringComparison.OrdinalIgnoreCase)
                || n.Equals("ULL", StringComparison.OrdinalIgnoreCase)
                || n.Equals("U", StringComparison.OrdinalIgnoreCase))
                continue;
            payloadNames.Add(n);
        }

        // Bare WRITE_REG(reg, Timing/Data): mskLabel is the param name to assign.
        if (!string.IsNullOrEmpty(mskLabel)
            && Regex.IsMatch(mskLabel, @"^[A-Za-z_][A-Za-z0-9_]*$")
            && !mskLabel.Contains("_Msk", StringComparison.OrdinalIgnoreCase)
            && !mskLabel.Contains("_MSK", StringComparison.OrdinalIgnoreCase)
            && !mskLabel.Contains("_MASK", StringComparison.OrdinalIgnoreCase)
            && !mskLabel.Contains("_Val", StringComparison.OrdinalIgnoreCase)
            && !mskLabel.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            payloadNames.Add(mskLabel);

        foreach (var p in wModel.Parameters)
        {
            if (keyParamName is not null
                && p.Name.Equals(keyParamName, StringComparison.OrdinalIgnoreCase)
                && keySample is uint ksVal)
            {
                p.ValueExpression = $"0x{ksVal:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                continue;
            }

            if (p.Type.Contains('*', StringComparison.Ordinal))
                continue;

            var isPayload =
                payloadNames.Contains(p.Name)
                || p.Name.Equals("Val", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Timing", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Data", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Period", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Prd", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Value", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Dbc", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Dat", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Data", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Addr", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Len", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Length", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Key", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Evt", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Event", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Cmp", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Compare", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Reg_upd", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("RegUpd", StringComparison.OrdinalIgnoreCase);
            if (!isPayload)
                continue;

            if (string.IsNullOrWhiteSpace(p.ValueExpression)
                || p.ValueExpression == "0"
                || p.ValueExpression.Equals("0x0", StringComparison.OrdinalIgnoreCase))
            {
                p.ValueExpression = $"0x{expected:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
            }
        }
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
                RuleSourceDetail = $"{detail}；写后回读对比目标位"
            },
            ..DefaultTimeoutAssertions()
        ];
        wModel.Notes =
            $"写校验：先读基线 0x{writeInitial:X}→WRITE_REG→回读 {wMember}&0x{writeAssertMask:X}=0x{expected:X}。虚拟环境。";
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
        if (mskMacro.EndsWith("_MASK", StringComparison.OrdinalIgnoreCase))
            return mskMacro[..^5];
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

    private readonly record struct BitOpMaskResolve(
        string Macro, uint Bits, bool UsedNameCorrelation, string Detail, string PairNote);

    /// <summary>
    /// Resolve SET/CLEAR expected mask.
    /// Order: (1) PWM/CH digit mismatch correction (DisablePWM2≠CEN1);
    /// (2) function-name trusted (catches wrong body, e.g. AWDG2/PREPARING_START);
    /// (3) body mask.
    /// </summary>
    private static async Task<BitOpMaskResolve> ResolveBitOpMaskAsync(
        AppDbContext db, LlFunction fn, string member, string bodyMskMacro, CancellationToken ct)
    {
        var bodyBits = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
        TryParseChipMaskRegAndField(bodyMskMacro, out _, out var bodyField);
        if (string.IsNullOrEmpty(bodyField))
            _ = TryFieldNameFromMskMacro(bodyMskMacro, member, out bodyField);

        var nameDigit = TryExtractChannelDigit(fn.FunctionName);
        var bodyDigit = TryExtractTrailingDigit(bodyField);

        // Narrow: only PWM{n}/CH{n} names, and only when body field digit disagrees.
        if (nameDigit is int nd)
        {
            var nameField = SuggestChannelFieldAlias(fn.FunctionName, nd);
            if (!string.IsNullOrEmpty(nameField)
                && bodyDigit is int bd
                && bd != nd)
            {
                var correctedMacro = await TryFindChipFieldMaskMacroAsync(
                    db, fn, member, nameField, ct);
                if (correctedMacro is null
                    && TryPeriPrefixFromMask(bodyMskMacro, out var peri)
                    && TryParseChipMaskRegAndField(bodyMskMacro, out var reg, out _))
                    correctedMacro = $"{peri}_{reg}_{nameField}_Msk";

                if (correctedMacro is not null)
                {
                    var correctedBits = await ResolveClearMaskAsync(
                        db, fn, member, correctedMacro, ct);
                    if (correctedBits != 0)
                    {
                        return new BitOpMaskResolve(
                            correctedMacro, correctedBits, UsedNameCorrelation: true,
                            Detail:
                            $"期望掩码按函数名编号纠正为 {correctedMacro}（体为 {bodyMskMacro}；" +
                            $"PWM/CH 编号不一致会假 Passed）",
                            PairNote:
                            $"函数名通道 {nd} 与体字段 {bodyField} 不一致，已按 {nameField} 纠正");
                    }
                }
            }
        }

        // Trusted from function name — keep ADC AWDG2 / PREPARING_START wrong-body detection.
        // Reject cross-peripheral hits and IT/Flag register-role mismatches
        // (EnableIT_CC0 body IER+C0MIE must not bind SR_CC0OIF).
        var trusted = await TryResolveTrustedMaskAsync(db, fn, member, ct);
        if (trusted is { Bits: > 0 }
            && IsMaskPeriCompatible(trusted.Label, fn.PeripheralName, fn.FunctionName)
            && IsTrustedMaskRoleCompatible(fn.FunctionName, member, bodyMskMacro, trusted.Label))
        {
            return new BitOpMaskResolve(
                trusted.Label, trusted.Bits, UsedNameCorrelation: true,
                Detail:
                $"期望掩码来自函数名关联的可信源 {trusted.Label}（非函数体内位操作实参；可检出错误掩码）",
                PairNote: "");
        }

        if (bodyBits != 0)
        {
            var skipNote = trusted is { Bits: > 0 }
                ? $"（已忽略不兼容可信源 {trusted.Label}）"
                : "（未找到函数名关联的 #define/位域；弱可信）";
            return new BitOpMaskResolve(
                bodyMskMacro, bodyBits, UsedNameCorrelation: false,
                Detail: $"期望掩码来自函数体 {bodyMskMacro}{skipNote}",
                PairNote: "");
        }

        return new BitOpMaskResolve(bodyMskMacro, 0, false, "", "");
    }

    private static int? TryExtractChannelDigit(string? functionName)
    {
        if (string.IsNullOrWhiteSpace(functionName)) return null;
        // Only explicit channel tokens — do not match Tim/Unit/AWDG (too broad).
        var m = Regex.Match(functionName,
            @"(?:PWM|Channel|CH)(?<d>\d+)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (m.Success && int.TryParse(m.Groups["d"].Value, out var d))
            return d;
        return null;
    }

    private static int? TryExtractTrailingDigit(string? fieldName)
    {
        if (string.IsNullOrWhiteSpace(fieldName)) return null;
        var m = Regex.Match(fieldName, @"(\d+)$");
        if (m.Success && int.TryParse(m.Groups[1].Value, out var d))
            return d;
        return null;
    }

    /// <summary>PWM2 → CEN2; Channel3/CH3 → CH3. Null if name has no PWM/CH token.</summary>
    private static string? SuggestChannelFieldAlias(string? functionName, int digit)
    {
        var name = functionName ?? "";
        if (name.Contains("PWM", StringComparison.OrdinalIgnoreCase))
            return $"CEN{digit}";
        if (Regex.IsMatch(name, @"CH(?:annel)?\d+", RegexOptions.IgnoreCase))
            return $"CH{digit}";
        return null;
    }

    private static async Task<string?> TryFindChipFieldMaskMacroAsync(
        AppDbContext db, LlFunction fn, string member, string fieldName, CancellationToken ct)
    {
        var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
        if (!string.IsNullOrWhiteSpace(field?.MskMacroName))
            return field!.MskMacroName;
        return null;
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
        // HRPWM_MST_DisablePWM2 → after peri strip still MST_DisablePWM2
        name = Regex.Replace(name, @"^(MST|COM|SLV\d+|CH\d+|UNIT\d+)_", "",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

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
        // AutoReload → ARE (not EN). PLL Enable/Disable alone → EN.
        if (functionName.Contains("AutoReload", StringComparison.OrdinalIgnoreCase))
            yield return "ARE";
        else if (Regex.IsMatch(functionName, @"PLL\d", RegexOptions.IgnoreCase)
            && (functionName.Contains("Enable", StringComparison.OrdinalIgnoreCase)
                || functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)))
            yield return "EN";
        if (functionName.Contains("BTOMode", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("SetBTOMode", StringComparison.OrdinalIgnoreCase))
            yield return "TOSEL";
        if (functionName.Contains("IT_CMP", StringComparison.OrdinalIgnoreCase)
            || (functionName.Contains("EnableIT_CMP", StringComparison.OrdinalIgnoreCase)
                || functionName.Contains("DisableIT_CMP", StringComparison.OrdinalIgnoreCase)))
            yield return "CIE";
        if (functionName.Contains("GenerateEvent_CMP", StringComparison.OrdinalIgnoreCase))
            yield return "CG";
        if (functionName.Contains("DisableCSSwOut", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("EnableCSSwOut", StringComparison.OrdinalIgnoreCase))
            yield return "CSOS";
        if (functionName.Contains("ResetOperationMode", StringComparison.OrdinalIgnoreCase))
            yield return "OP_MODE";
        if (functionName.Contains("AVCC_DisableLowVoltageReset", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("AVCC_EnableLowVoltageReset", StringComparison.OrdinalIgnoreCase))
            yield return "AVCCLVRE";
        if (functionName.Contains("VCC_DisableLowVoltageReset", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("VCC_EnableLowVoltageReset", StringComparison.OrdinalIgnoreCase))
            yield return "VCCLVRE";
        if (functionName.Contains("VDD_DisableLowVoltageReset", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("VDD_EnableLowVoltageReset", StringComparison.OrdinalIgnoreCase))
            yield return "VDDLVRE";
        if (functionName.Contains("AVCC_DisableLowVoltageBrake", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("AVCC_EnableLowVoltageBrake", StringComparison.OrdinalIgnoreCase))
            yield return "AVCCLVBE";
        else if (functionName.Contains("VCC_DisableLowVoltageBrake", StringComparison.OrdinalIgnoreCase)
                 || functionName.Contains("VCC_EnableLowVoltageBrake", StringComparison.OrdinalIgnoreCase))
            yield return "VCCLVBE";
        else if (functionName.Contains("VDD_DisableLowVoltageBrake", StringComparison.OrdinalIgnoreCase)
                 || functionName.Contains("VDD_EnableLowVoltageBrake", StringComparison.OrdinalIgnoreCase))
            yield return "VDDLVBE";

        // HRPWM Master: DisablePWM2 / EnablePWM2 → CEN2 (not CEN1).
        var pwmN = Regex.Match(functionName, @"PWM(?<d>\d+)", RegexOptions.IgnoreCase);
        if (pwmN.Success
            && (member.StartsWith("MCR", StringComparison.OrdinalIgnoreCase)
                || member.StartsWith("PWMCR", StringComparison.OrdinalIgnoreCase)
                || string.IsNullOrEmpty(member)))
            yield return "CEN" + pwmN.Groups["d"].Value;
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

        // UART SetTransferDirection only (SPI uses CTRL RXEN|TXEN + Direction payload).
        // DIRECTION_TX_RX is (TX|RX) — not a hex literal; OR the leaf constants.
        if (fn.FunctionName.StartsWith("LL_UART_SetTransferDirection", StringComparison.OrdinalIgnoreCase))
        {
            uint dirTe = 0, dirRe = 0, dirTx = 0, dirRx = 0;
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR0_TE_Msk", out dirTe);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR0_RE_Msk", out dirRe);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "LL_UART_DIRECTION_TX", out dirTx);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "LL_UART_DIRECTION_RX", out dirRx);
            if (dirTe == 0) dirTe = 0x4u;
            if (dirRe == 0) dirRe = 0x2u;
            if (dirTx == 0) dirTx = 0x1u;
            if (dirRx == 0) dirRx = 0x2u;
            var dirMask = dirTe | dirRe;
            var dirEnum = dirTx | dirRx;
            var dirParams = CloneParams(baseParams);
            foreach (var p in dirParams)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Direction", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = $"0x{dirEnum:X}";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            var dirModel = BaseModel(fn);
            dirModel.Name = $"{fn.FunctionName}/{instance}/CR0.TE_RE/dir/write-check";
            dirModel.Status = nameof(LlTestCaseStatus.Ready);
            dirModel.IsAutoGenerated = true;
            dirModel.Parameters = dirParams;
            dirModel.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = "CR0", ValueHex = "0x0"
                }
            ];
            dirModel.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = "CR0",
                    ExpectedHex = $"0x{dirMask:X}",
                    ExpectedMask = dirMask,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail =
                        $"SetTransferDirection TX_RX=0x{dirEnum:X} → TE|RE=0x{dirMask:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            dirModel.Notes = "写校验：传输方向枚举→TE/RE。虚拟环境。";
            results.Add(dirModel);
            return results;
        }

        // SetBaudRateHz: div = (PclkHz + BaudRate/2) / BaudRate → BAUD field.
        if (fn.FunctionName.Contains("SetBaudRateHz", StringComparison.OrdinalIgnoreCase)
            && TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_BAUD_BAUD_Msk", out var hzMsk)
            && hzMsk != 0)
        {
            var hzPos = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_BAUD_BAUD_Pos", out var hzPosLit)
                ? (int)hzPosLit
                : PosFromMask(hzMsk);
            const uint pclk = 16000000u;
            const uint baud = 115200u;
            var div = (pclk + (baud / 2u)) / baud;
            var hzExpected = (div << hzPos) & hzMsk;
            var hzParams = CloneParams(baseParams);
            foreach (var p in hzParams)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("PclkHz", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Pclk", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = pclk.ToString();
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
                else if (p.Name.Equals("BaudRate", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Baud", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = baud.ToString();
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            var hzModel = BaseModel(fn);
            hzModel.Name = $"{fn.FunctionName}/{instance}/BAUD.hz/write-check";
            hzModel.Status = nameof(LlTestCaseStatus.Ready);
            hzModel.IsAutoGenerated = true;
            hzModel.Parameters = hzParams;
            hzModel.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = "BAUD", ValueHex = "0x0"
                }
            ];
            hzModel.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = "BAUD",
                    ExpectedHex = $"0x{hzExpected:X}",
                    ExpectedMask = hzMsk,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail =
                        $"SetBaudRateHz Pclk={pclk} Baud={baud} → div={div} BAUD=0x{hzExpected:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            hzModel.Notes = "写校验：波特率 Hz→分频寄存器。虚拟环境。";
            results.Add(hzModel);
            return results;
        }

        // MODIFY_REG(reg, 0x3f|BIT_Msk, BIT_Msk|0) — RCU *Reset_Enable/Disable.
        var litOrMsk = Regex.Match(
            liveBody,
            @"MODIFY_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<lit>0x[0-9A-Fa-f]+(?:UL|U)?)\s*\|\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*,\s*(?<rhs>\k<msk>|0(?:UL|U)?)\s*\)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (litOrMsk.Success
            && TryParseHexOrDecToken(litOrMsk.Groups["lit"].Value, out var stickyLit)
            && TryParseUintDefineFromFileCandidates(fn.FilePath, litOrMsk.Groups["msk"].Value, out var enBits)
            && enBits != 0)
        {
            var stickyMem = litOrMsk.Groups["mem"].Value;
            var stickyClear = stickyLit | enBits;
            var stickySet = litOrMsk.Groups["rhs"].Value.StartsWith("0", StringComparison.Ordinal)
                ? 0u
                : enBits;
            var stickyParams = CloneParams(baseParams);
            foreach (var p in stickyParams.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
                p.ValueExpression = ResolveHostPeriPointer(
                    fn.PeripheralName, instance, instance, p.ValueExpression);
            var stickyModel = BaseModel(fn);
            stickyModel.Name =
                $"{fn.FunctionName}/{instance}/{stickyMem}.{StripMaskSuffix(litOrMsk.Groups["msk"].Value)}/flat/write-check";
            stickyModel.Status = nameof(LlTestCaseStatus.Ready);
            stickyModel.IsAutoGenerated = true;
            stickyModel.Parameters = stickyParams;
            stickyModel.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = stickyMem, ValueHex = $"0x{stickyLit:X}"
                }
            ];
            var stickyExpected = (stickyLit & ~stickyClear) | stickySet;
            stickyModel.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = stickyMem,
                    ExpectedHex = $"0x{stickyExpected:X}",
                    ExpectedMask = stickyClear,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail =
                        $"MODIFY lit|Msk：clear=0x{stickyClear:X} set=0x{stickySet:X} → (reg&0x{stickyClear:X})==0x{stickyExpected:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            stickyModel.Notes =
                $"写校验：MODIFY_REG({stickyMem}, 0x{stickyLit:X}|Msk, Msk)。虚拟环境。";
            results.Add(stickyModel);
            return results;
        }

        // MODIFY_REG(REG_OFFSET(...).MEM, Msk, rhs) before flat ->path.
        var regOffMod = ModifyRegOffsetMemberPattern.Match(liveBody);
        if (regOffMod.Success)
        {
            var builtOff = await TryBuildRegOffsetModifyCaseAsync(
                db, fn, instance, baseParams, regOffMod, ct, flatNoLeaf: false);
            if (builtOff is not null)
            {
                results.Add(builtOff);
                return results;
            }
        }

        var regOffModFlat = ModifyRegOffsetFlatPattern.Match(liveBody);
        if (regOffModFlat.Success)
        {
            var builtFlat = await TryBuildRegOffsetModifyCaseAsync(
                db, fn, instance, baseParams, regOffModFlat, ct, flatNoLeaf: true);
            if (builtFlat is not null)
            {
                results.Add(builtFlat);
                return results;
            }
        }

        var bitChMod = ModifyRegBitChannelPattern.Match(liveBody);
        if (bitChMod.Success)
        {
            _ = TryParseRegAccessPath(bitChMod.Groups["path"].Value.Trim(), out var bitPath);
            var bitMem = string.IsNullOrEmpty(bitPath.LeafMember)
                ? bitChMod.Groups["path"].Value.Trim()
                : bitPath.LeafMember;
            const uint bitCh = 0;
            var bitMaskBits = 1u << (int)bitCh;
            var bitParams = CloneParams(baseParams);
            foreach (var p in bitParams)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = "0";
                if (p.Name.Equals("Mode", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("En", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Val", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = "0x1";
            }

            var bitModel = BaseModel(fn);
            bitModel.Name = $"{fn.FunctionName}/{instance}/{bitMem}.BIT{bitCh}/ch{bitCh}/write-check";
            bitModel.Status = nameof(LlTestCaseStatus.Ready);
            bitModel.IsAutoGenerated = true;
            bitModel.Parameters = bitParams;
            bitModel.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = bitMem, ValueHex = "0x0"
                }
            ];
            bitModel.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = bitMem,
                    ExpectedHex = $"0x{bitMaskBits:X}",
                    ExpectedMask = bitMaskBits,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = $"MODIFY_REG BIT(Ch={bitCh}) → {bitMem} set 0x{bitMaskBits:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            bitModel.Notes = $"写校验：MODIFY BIT 通道 → {bitMem}。虚拟环境。";
            results.Add(bitModel);
            return results;
        }

        // (0x1UL << Xxx_Pos) << (Channel*k) — OC_SetPolarity; Channel=0 IsOCN=0 Pol=1.
        var litPosMod = ModifyRegLiteralPosChannelShiftPattern.Match(liveBody);
        if (litPosMod.Success)
        {
            _ = TryParseRegAccessPath(litPosMod.Groups["path"].Value.Trim(), out var litPath);
            var litMem = string.IsNullOrEmpty(litPath.LeafMember)
                ? litPosMod.Groups["path"].Value.Trim()
                : litPath.LeafMember;
            var litPosMacro = litPosMod.Groups["pos"].Value;
            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, litPosMacro, out var litPos)
                || litPos >= 32)
                return results;
            var litClearMask = 1u << (int)litPos;
            var litSetBits = 1u << (int)litPos;
            var litParams = CloneParams(baseParams);
            foreach (var p in litParams)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("IsOCN", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }
                else if (p.Name.Equals("Pol", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Polarity", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0x1";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }
            }

            var litModel = BaseModel(fn);
            litModel.Name =
                $"{fn.FunctionName}/{instance}/{litMem}.{StripMaskSuffix(litPosMacro)}/ch0/seed/write-check";
            litModel.Status = nameof(LlTestCaseStatus.Ready);
            litModel.IsAutoGenerated = true;
            litModel.Parameters = litParams;
            litModel.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance, MemberName = litMem, ValueHex = "0x0"
                }
            ];
            litModel.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = instance,
                    MemberName = litMem,
                    ExpectedHex = $"0x{litSetBits:X}",
                    ExpectedMask = litClearMask,
                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                    RuleSourceDetail =
                        $"MODIFY (0x1<<{litPosMacro})<<Ch Channel=0 IsOCN=0 Pol=1 → (reg&0x{litClearMask:X})==0x{litSetBits:X}"
                },
                ..DefaultTimeoutAssertions()
            ];
            litModel.Notes =
                $"写校验：literal Pos 移位 MODIFY Channel=0 → {litMem} bit {litPosMacro}。虚拟环境。";
            results.Add(litModel);
            return results;
        }

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
                || Regex.IsMatch(rhs, @"\(\s*\(?\s*[A-Za-z_][A-Za-z0-9_]*\s*\)?\s*<<")
                || Regex.IsMatch(rhs, @"\(\([^)]+\)\s*-\s*1(?:UL)?\)\s*<<"));

        // I2C SCL/FIFO: (((Cnt)-1UL)<<Pos) — API count is 1-based, register stores count-1.
        // ((Cnt)-1)<<Pos / ((Div)-1)&mask<<Pos / ((Div-1)&0xf)<<Pos — store N-1.
        var fieldMinusOne = Regex.IsMatch(
            rhs,
            @"[A-Za-z_][A-Za-z0-9_]*\s*\)?\s*-\s*1(?:UL)?",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

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

        // ((Num) & 0x3fUL) << Pos — literal clamp (SetEraseSectorNumber).
        if (valClamp is null or 0)
        {
            var litClamp = Regex.Match(
                rhs,
                @"&\s*(?:0x(?<hex>[0-9A-Fa-f]+)|(?<dec>\d+))(?:UL|U|ull|ULL)?\b",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            if (litClamp.Success)
            {
                if (litClamp.Groups["hex"].Success
                    && uint.TryParse(litClamp.Groups["hex"].Value,
                        System.Globalization.NumberStyles.HexNumber, null, out var hx)
                    && hx != 0)
                    valClamp = hx;
                else if (litClamp.Groups["dec"].Success
                         && uint.TryParse(litClamp.Groups["dec"].Value, out var dec)
                         && dec != 0)
                    valClamp = dec;
            }
        }

        // Named enum: LL_EFLASH_PWRON_ECC_BYPASS_ENABLE << FLASH_OPDR_EBP_Pos.
        uint? namedFieldVal = null;
        var namedLl = Regex.Match(
            rhs,
            @"\b(?<ll>LL_[A-Za-z0-9_]+)\s*<<\s*(?<pos>[A-Za-z0-9_]+_Pos)\b",
            RegexOptions.CultureInvariant);
        if (namedLl.Success
            && TryParseUintDefineFromFileCandidates(fn.FilePath, namedLl.Groups["ll"].Value, out var llConst))
            namedFieldVal = llConst;

        var maxField = clearMask >> pos;
        if (maxField == 0 && isFieldValueStyle && namedFieldVal is null)
            return results;

        IEnumerable<(string Tag, uint Param, bool Interference)> samples;
        if (namedFieldVal is uint nf)
            samples = [("named", nf, false)];
        else if (isFieldValueStyle)
        {
            samples = EnumerateFieldReadSamples(maxField)
                .Select(s => (s.Tag, s.FieldValue, s.Interference));
        }
        else
        {
            samples = EnumerateModifyMaskArgSamples(clearMask);
        }

        // One representative channel + one field sample from the LL body — no invented fan-out.
        var arrayBound = ResolveArrayBound(accessPath.ArrayIndexExpr, fn.FilePath);
        const uint channelRaw = 0;
        var channelIndex = accessPath.ArrayIndexExpr is not null
            ? channelRaw % Math.Max(1u, arrayBound)
            : 0u;
        var targetInstance = ResolveNestedInstance(instance, accessPath, channelIndex, bodyMskMacro);
        var (tag, paramRaw, _) = samples.First();

        uint paramBits;
        uint setMask;
        if (namedFieldVal is uint named)
        {
            paramBits = named;
            setMask = (named << pos) & clearMask;
            tag = "named";
        }
        else if (isFieldValueStyle)
        {
            // For (Cnt-1)<<Pos: pass API count = sample+1 so register gets sample.
            if (fieldMinusOne)
            {
                var stored = valClamp is uint vc ? paramRaw & vc : paramRaw;
                if (stored >= maxField && maxField > 0)
                    stored = maxField > 1 ? maxField / 2u : 0u;
                paramBits = stored + 1u;
                setMask = stored << pos;
                tag = "minus1";
            }
            else
            {
                paramBits = valClamp is uint vc ? paramRaw & vc : paramRaw;
                setMask = paramBits << pos;
            }
        }
        else
        {
            paramBits = paramRaw & clearMask;
            setMask = paramBits;
        }

        // SetAll* style: MODIFY_REG(reg, ALL_MSK, ALL_MSK) → expect full composite mask, not half-sample.
        if (namedFieldVal is null
            && !string.IsNullOrWhiteSpace(rhs)
            && Regex.IsMatch(rhs, $@"\b{Regex.Escape(bodyMskMacro)}\b")
            && !rhs.Contains('&', StringComparison.Ordinal)
            && !Regex.IsMatch(rhs, @"0x0(?:UL)?\b"))
        {
            paramBits = clearMask;
            setMask = clearMask;
        }

        // Clear-style MODIFY (RHS 0x0 / Disable* / Clear*): seed flag bits then expect cleared.
        // Baseline 0 → write 0 leaves host RAM unchanged → empty sync trace.
        var rhsIsZero = Regex.IsMatch(rhs, @"0x0(?:UL)?\b")
                        || Regex.IsMatch(rhs, @"\(\s*0\s*UL\s*\)");
        var isClearModify = setMask == 0
                            || rhsIsZero
                            || (fn.FunctionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)
                                && rhsIsZero)
                            || IsClearLike(fn.FunctionName)
                            || fn.FunctionName.Contains("Clr", StringComparison.OrdinalIgnoreCase);
        if (isClearModify)
            setMask = 0;
        var initial = isClearModify ? clearMask : 0u;
        var expected = ComputeModifyRegExpected(initial, clearMask, setMask);
        EnsureModifyExpectationConsistent($"{targetInstance}.{member}", initial, clearMask, setMask, expected);

        var parameters = baseParams.Select(p => new LlTestParameterValue
        {
            Name = p.Name,
            Type = p.Type,
            ValueExpression = p.ValueExpression,
            RuleSource = p.RuleSource
        }).ToList();

        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
        {
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, instance, targetInstance, p.ValueExpression);
        }

        // ADC Trig 4..9: ((Trigx)%N - 4)*lane — Trigx=0 wraps; force 4 so TLEN4/USRC4 lane matches.
        if (Regex.IsMatch(
                liveBody,
                @"\(\(\s*Trigx\s*\)\s*%[^)]+\)\s*-\s*4",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase))
        {
            foreach (var p in parameters)
            {
                if (p.Name.Equals("Trigx", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "4";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }
        }

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

        static bool IsChannelIndexParam(string name)
            => name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Num", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Seq", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Idx", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Index", StringComparison.OrdinalIgnoreCase)
               || name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
               || name.Equals("MskBit", StringComparison.OrdinalIgnoreCase);

        // Channel-shifted MODIFY (CCER << (Channel*4)): always Channel=0 sample.
        // Do not leave draft non-zero heuristics (Channel=0x1) — that shifts the field lane.
        // Exception: Num in ((Num)&0x3f)<<Pos is a field payload (SetEraseSectorNumber), not lane index.
        bool IsRhsFieldPayload(string name) =>
            Regex.IsMatch(rhs, $@"\(\(\s*{Regex.Escape(name)}\s*\)\s*&")
            || Regex.IsMatch(rhs, $@"\(\s*{Regex.Escape(name)}\s*&\s*")
            || Regex.IsMatch(rhs, $@"\(\({Regex.Escape(name)}\)&")
            || Regex.IsMatch(rhs, $@"\(\(\s*{Regex.Escape(name)}\s*\)\s*-\s*1");

        foreach (var p in parameters)
        {
            if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
            if (!IsChannelIndexParam(p.Name)) continue;
            if (IsRhsFieldPayload(p.Name)) continue;
            p.ValueExpression = "0";
            p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
        }

        // Dual-field MODIFY (Pol+Lvl PolarityAndIdleLevel): assign EVERY RHS payload,
        // not only LastOrDefault — otherwise Pol stays 0 and POLA assertion sees 0.
        var payloadParams = parameters
            .Where(p => !p.Type.Contains('*', StringComparison.Ordinal)
                        && !indexParamNames.Contains(p.Name)
                        && IsRhsFieldPayload(p.Name))
            .ToList();
        if (payloadParams.Count > 0)
        {
            foreach (var p in payloadParams)
            {
                p.ValueExpression = $"0x{paramBits:X}";
                p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
        }
        else
        {
            var modeParam = parameters.LastOrDefault(p =>
                !p.Type.Contains('*', StringComparison.Ordinal)
                && !indexParamNames.Contains(p.Name)
                && !IsChannelIndexParam(p.Name)
                && (p.Name.Contains("Mode", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Value", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Div", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Data", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Cfg", StringComparison.OrdinalIgnoreCase)));
            modeParam ??= parameters.LastOrDefault(p =>
                !p.Type.Contains('*', StringComparison.Ordinal)
                && !indexParamNames.Contains(p.Name)
                && !IsChannelIndexParam(p.Name));

            if (modeParam is not null)
            {
                modeParam.ValueExpression = $"0x{paramBits:X}";
                modeParam.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }
        }

        // Disable*/clear-to-zero MODIFY: RHS uses 0x0 → seed bits then expect cleared.
        if (Regex.IsMatch(rhs, @"\(\s*\(?\s*0x0(?:UL)?\s*\)?")
            || (fn.FunctionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)
                && rhs.Contains("0x0", StringComparison.OrdinalIgnoreCase)))
        {
            // Rebuild as clear-style: already computed setMask from samples — force zero set.
            setMask = 0;
            initial = clearMask;
            expected = ComputeModifyRegExpected(initial, clearMask, setMask);
            EnsureModifyExpectationConsistent($"{targetInstance}.{member}", initial, clearMask, setMask, expected);
            // Patch model fields below use expected/initial — update name tag via setMask==0 path.
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
        model.Assertions =
        [
            new LlTestAssertionSpec
            {
                Kind = LlAssertionKind.RegisterValue,
                InstanceName = targetInstance,
                MemberName = member,
                ExpectedHex = $"0x{setMask:X}",
                ExpectedMask = clearMask,
                RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                RuleSourceDetail =
                    $"MODIFY_REG 先读基线 0x{initial:X}，写后回读 (reg&0x{clearMask:X})==0x{setMask:X}；" +
                    $"Param=0x{paramBits:X}；path={accessPath.RawPath}；{modifyPairNote}；体宏 {bodyMskMacro} pos={pos}"
            },
            ..DefaultTimeoutAssertions()
        ];
        model.Notes =
            $"写校验 MODIFY[{tag}/{channelTag}]：先读基线→写→回读目标位。path={accessPath.RawPath} " +
            $"Target={targetInstance}.{member} Param=0x{paramBits:X} ClearMask=0x{clearMask:X} " +
            $"SetMask=0x{setMask:X} ExpectedReg=0x{expected:X}。";
        results.Add(model);
        return results;
    }

    /// <summary>CMSIS MODIFY_REG: (REG &amp; ~CLEARMASK) | SETMASK</summary>
    /// <summary>CMSIS <c>MODIFY_REG</c>: <c>(REG &amp; ~CLEARMASK) | SETMASK</c> (SETMASK not re-masked).</summary>
    private static uint ComputeModifyRegExpected(uint initial, uint clearMask, uint setMask)
        => (initial & ~clearMask) | setMask;

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
        // One representative field/mask value from the LL clear-mask — no A5A5 interference fan-out.
        var sample = clearMask == 0 ? 0u : (clearMask & (clearMask > 1 ? clearMask >> 1 | LowestSetBit(clearMask) : clearMask));
        if (sample == 0 && clearMask != 0)
            sample = LowestSetBit(clearMask);
        yield return ("seed", sample, false);
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

        var tokens = BuildFunctionMaskSearchTokens(fn.FunctionName ?? "");
        if (tokens.Count == 0) return null;
        // Cap token work — never pull the entire RegisterDefinitions table (HRPWM hung here).
        var tokenList = tokens
            .Where(t => t.Length >= 3)
            .Distinct(StringComparer.OrdinalIgnoreCase)
            .Take(8)
            .ToList();
        if (tokenList.Count == 0) return null;

        // Prefer longest token for SQL Contains (EF cannot translate local list.Any well).
        var primary = tokenList.OrderByDescending(t => t.Length).First();
        var members = await db.RegisterDefinitions.AsNoTracking()
            .Where(r => r.SdkProjectId == fn.SdkProjectId
                        && r.MemberName != null && r.MemberName != ""
                        && r.MemberName!.Contains(primary))
            .Select(r => r.MemberName!)
            .Distinct()
            .Take(64)
            .ToListAsync(ct);
        if (members.Count == 0) return null;

        var scored = new List<(string Member, int Score)>();
        foreach (var mem in members)
        {
            var score = 0;
            foreach (var t in tokenList)
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
        // TAE32 timers use PSCR, not PRESC (name-token PRESC would miss the slot).
        if (functionName.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("GetPSC", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("SetPSC", StringComparison.OrdinalIgnoreCase))
            return "PSCR";
        if (functionName.Contains("MasterConvData", StringComparison.OrdinalIgnoreCase)
            || functionName.Contains("SlaveConvData", StringComparison.OrdinalIgnoreCase))
            return "CDR";
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

        // HSI/LSI_GetValue: nested GetRealFrequency + (field==sentinel ? defaultHz : field).
        var ternFreq = Regex.Match(
            body,
            @"LL_(?<callee>[A-Za-z0-9_]+_GetRealFrequency)\s*\(\s*(?<hardInst>[A-Za-z0-9_]+)\s*\)[\s\S]*?" +
            @"(?<var>[A-Za-z_][A-Za-z0-9_]*)\s*==\s*(?<sent>0x[0-9A-Fa-f]+)(?:UL|U)?\s*\?\s*(?<def>\d+)(?:UL|U)?",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        if (ternFreq.Success
            && uint.TryParse(
                ternFreq.Groups["sent"].Value.Replace("0x", "", StringComparison.OrdinalIgnoreCase),
                System.Globalization.NumberStyles.HexNumber, null, out var sentVal)
            && uint.TryParse(ternFreq.Groups["def"].Value, out var defHz)
            && defHz != 0)
        {
            var callee = "LL_" + ternFreq.Groups["callee"].Value;
            var calleeBody = TryReadFunctionBodyFromSource(fn.FilePath, callee);
            if (!string.IsNullOrWhiteSpace(calleeBody))
            {
                var calleeShift = ReadBitShiftPattern.Match(calleeBody);
                if (calleeShift.Success)
                {
                    _ = TryParseRegAccessPath(calleeShift.Groups["path"].Value.Trim(), out var accessPath);
                    var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
                        ? calleeShift.Groups["path"].Value.Trim()
                        : accessPath.LeafMember;
                    var bodyMskMacro = calleeShift.Groups["msk"].Value;
                    var hardInst = ternFreq.Groups["hardInst"].Value;
                    var targetInstance = string.IsNullOrWhiteSpace(hardInst) ? instance : hardInst;
                    var member = ResolveMemberAlignedToMask(
                        bodyMember, bodyMskMacro, out _, out var pairNote);
                    var mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
                    if (mask == 0)
                        _ = TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask);
                    var pos = 0;
                    if (calleeShift.Groups["pos"].Success
                        && TryParseUintDefineFromFileCandidates(
                            fn.FilePath, calleeShift.Groups["pos"].Value, out var posLit))
                        pos = (int)posLit;
                    else if (mask != 0)
                        pos = PosFromMask(mask);

                    if (mask != 0 && ((mask >> pos) & sentVal) == sentVal)
                    {
                        var seed = (sentVal << pos) & mask;
                        var parameters = PrepareReadParameters(
                            fn, instance, targetInstance, CloneParams());
                        results.Add(BuildReadCheckModel(
                            fn, targetInstance, parameters, member, seed, defHz,
                            nameSuffix: $"{member}.{StripMaskSuffix(bodyMskMacro)}/default-hz/read-check",
                            detail:
                            $"哨兵 0x{sentVal:X}→默认 {defHz}Hz；预置 {targetInstance}.{member}=0x{seed:X}；{pairNote}",
                            notes:
                            $"读校验：{callee} 哨兵字段→{fn.FunctionName} 返回默认频率 {defHz}。虚拟环境。"));
                        return results;
                    }
                }
            }
        }

        // EE_GetSrc: dual READ (EECER|EECR0). Evt_x=0 + EECER=0 → return equals EECR0 SRC field.
        if (fn.FunctionName.Contains("EE_GetSrc", StringComparison.OrdinalIgnoreCase)
            && body.Contains("EECER", StringComparison.Ordinal)
            && body.Contains("EECR0", StringComparison.Ordinal))
        {
            // EE0SRC_Pos is 0 in chip header; tolerate missing parse.
            uint srcPos = 0;
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "HRPWM_COM_EECR0_EE0SRC_Pos", out srcPos);
            srcPos %= 32;
            const uint field = 1u;
            var preload = field << (int)srcPos;
            // Always COM bank — do not invent HRPWM_COM_0 via mis-ordered RegAccessPath.
            const string targetInstance = "HRPWM_COM";
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            foreach (var p in parameters)
            {
                if (p.Name.Equals("Evt_x", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            var model = BuildReadCheckModel(
                fn, targetInstance, parameters, "EECR0", preload, field,
                nameSuffix: "EECR0.EE0SRC/evt0/read-check",
                detail:
                $"EE_GetSrc Evt_x=0 EECER=0：预置 EECR0 SRC=0x{field:X} @pos{srcPos} → Expected=0x{field:X}",
                notes: "读校验：EE_GetSrc 低字段（高位 EECER 默认 0）。虚拟环境。");
            model.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = targetInstance, MemberName = "EECR0", ValueHex = $"0x{preload:X}"
                },
                new LlTestInitialRegister
                {
                    InstanceName = targetInstance, MemberName = "EECER", ValueHex = "0x0"
                }
            ];
            results.Add(model);
            return results;
        }

        // return (uint32_t*)(&(HRPWMx->Master.MDMADR)) / PWM[n].REG.DMADR — host offsetof.
        if (fn.FunctionName.Contains("GetSysDMADataAddr", StringComparison.OrdinalIgnoreCase)
            || Regex.IsMatch(
                body,
                @"return\s*\(\s*uint32_t\s*\*\s*\)\s*\(\s*&\s*\(",
                RegexOptions.IgnoreCase))
        {
            var ptr = Regex.Match(
                body,
                @"return\s*\(\s*uint32_t\s*\*\s*\)\s*\(\s*&\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<path>(?:[^()]+|\([^()]*\))+?)\s*\)\s*\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
            if (ptr.Success && TryParseRegAccessPath(ptr.Groups["path"].Value.Trim(), out var ptrPath))
            {
                var mem = string.IsNullOrEmpty(ptrPath.LeafMember)
                    ? ptr.Groups["path"].Value.Trim()
                    : ptrPath.LeafMember;
                var targetInstance = ResolveNestedInstance(instance, ptrPath, 0, null);
                var sdkRoot = await db.SdkProjects.AsNoTracking()
                    .Where(p => p.Id == fn.SdkProjectId)
                    .Select(p => p.SdkRootPath)
                    .FirstOrDefaultAsync(ct);
                var catalog = VirtualMcu.ChipHeaderAddressCatalog.TryLoad(sdkRoot);
                uint? hostOff = null;
                if (catalog is not null)
                {
                    if (catalog.TryGetOffset(targetInstance, null, mem, out var localOff)
                        && localOff >= 0)
                    {
                        // Banked SLV: AbsoluteAddress(SLVx.mem) - HRPWM_MST_BASE.
                        if (ptrPath.ArrayIndexExpr is not null
                            && catalog.TryResolveAbsolute(
                                targetInstance, null, mem, out var abs, out _, out _)
                            && catalog.TryResolveAbsolute(
                                "HRPWM_MST", null, "MCR0", out var mstAbs, out _, out _))
                            hostOff = abs - mstAbs;
                        else
                            hostOff = (uint)localOff;
                    }
                }

                if (hostOff is uint offVal)
                {
                    var parameters = PrepareReadParameters(
                        fn, instance, targetInstance, CloneParams());
                    foreach (var p in parameters)
                    {
                        if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                        if (p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase))
                        {
                            p.ValueExpression = "0";
                            p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                        }
                    }

                    var addrModel = BaseModel(fn);
                    addrModel.Name = $"{fn.FunctionName}/{targetInstance}/{mem}/addr/read-check";
                    addrModel.Status = nameof(LlTestCaseStatus.Ready);
                    addrModel.IsAutoGenerated = true;
                    addrModel.Parameters = parameters;
                    addrModel.InitialRegisters = [];
                    addrModel.Assertions =
                    [
                        ReturnValueAssertion(
                            $"0x{offVal:X}",
                            $"&{targetInstance}.{mem} host offsetof=0x{offVal:X}"),
                        ..DefaultTimeoutAssertions()
                    ];
                    addrModel.Notes =
                        $"读校验：宿主返回 &{mem} 相对 HRPWM 映像偏移 0x{offVal:X}。虚拟环境。";
                    results.Add(addrModel);
                    return results;
                }
            }
        }

        // ReceiveData8/9: READ_REG(RXDATA)&0xFF or READ_BIT(RDR, 0xff/0x1ff).
        if (fn.FunctionName.Contains("ReceiveData", StringComparison.OrdinalIgnoreCase)
            || Regex.IsMatch(body, @"READ_REG\s*\([^\)]*RXDATA[^\)]*\)\s*&\s*0xFF",
                RegexOptions.IgnoreCase)
            || Regex.IsMatch(body, @"READ_BIT\s*\([^\)]*RDR[^\)]*,\s*0x[0-9A-Fa-f]+",
                RegexOptions.IgnoreCase))
        {
            var rxReg = Regex.Match(
                body,
                @"READ_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            var rxBit = Regex.Match(
                body,
                @"READ_BIT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?:0x(?<hex>[0-9A-Fa-f]+)|(?<dec>\d+))(?:UL|U)?\s*\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            string? mem = null;
            uint clamp = 0xFFu;
            if (rxBit.Success)
            {
                mem = rxBit.Groups["mem"].Value;
                if (rxBit.Groups["hex"].Success)
                    _ = uint.TryParse(
                        rxBit.Groups["hex"].Value,
                        System.Globalization.NumberStyles.HexNumber, null, out clamp);
                else
                    _ = uint.TryParse(rxBit.Groups["dec"].Value, out clamp);
                if (clamp == 0) clamp = 0xFFu;
            }
            else if (rxReg.Success)
            {
                mem = rxReg.Groups["mem"].Value;
                clamp = fn.FunctionName.Contains("9", StringComparison.Ordinal) ? 0x1FFu : 0xFFu;
            }

            if (mem is not null)
            {
                var seed = clamp & 0xA5u;
                if (seed == 0) seed = LowestSetBit(clamp);
                results.Add(BuildReadCheckModel(
                    fn, instance, PrepareReadParameters(fn, instance, instance, CloneParams()),
                    mem, seed, seed & clamp,
                    nameSuffix: $"{mem}/rxdata/read-check",
                    detail: $"ReceiveData：预置 {mem}=0x{seed:X} Expected=0x{seed & clamp:X} clamp=0x{clamp:X}",
                    notes: "读校验：RDR/RXDATA 数据位。虚拟环境。"));
                return results;
            }
        }

        // IsOnAPB1: pointer compare — UART0/1/2 → 0, UART3/4 → 1 (when defined).
        if (fn.FunctionName.Contains("IsOnAPB1", StringComparison.OrdinalIgnoreCase))
        {
            var expect = instance.Equals("UART3", StringComparison.OrdinalIgnoreCase)
                         || instance.Equals("UART4", StringComparison.OrdinalIgnoreCase)
                ? 1u
                : 0u;
            var apbModel = BaseModel(fn);
            apbModel.Name = $"{fn.FunctionName}/{instance}/apb/read-check";
            apbModel.Status = nameof(LlTestCaseStatus.Ready);
            apbModel.IsAutoGenerated = true;
            apbModel.Parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
            apbModel.InitialRegisters = [];
            apbModel.Assertions =
            [
                ReturnValueAssertion($"0x{expect:X}", $"IsOnAPB1({instance})→{expect}"),
                ..DefaultTimeoutAssertions()
            ];
            apbModel.Notes = $"读校验：实例 {instance} APB 归属返回 {expect}。虚拟环境。";
            results.Add(apbModel);
            return results;
        }

        // UART GetTransferDirection only (SPI returns CTRL RXEN|TXEN raw bits).
        if (fn.FunctionName.StartsWith("LL_UART_GetTransferDirection", StringComparison.OrdinalIgnoreCase))
        {
            uint teMsk = 0, reMsk = 0, dirTx = 0, dirRx = 0;
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR0_TE_Msk", out teMsk);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "UART0_CR0_RE_Msk", out reMsk);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "LL_UART_DIRECTION_TX", out dirTx);
            _ = TryParseUintDefineFromFileCandidates(fn.FilePath, "LL_UART_DIRECTION_RX", out dirRx);
            if (teMsk == 0) teMsk = 0x4u;
            if (reMsk == 0) reMsk = 0x2u;
            if (dirTx == 0) dirTx = 0x1u;
            if (dirRx == 0) dirRx = 0x2u;
            var seed = teMsk | reMsk;
            var dirTxRx = dirTx | dirRx;
            results.Add(BuildReadCheckModel(
                fn, instance, PrepareReadParameters(fn, instance, instance, CloneParams()),
                "CR0", seed, dirTxRx,
                nameSuffix: "CR0.TE_RE/dir/read-check",
                detail: $"Direction：预置 TE|RE=0x{seed:X} Expected=DIRECTION_TX_RX=0x{dirTxRx:X}",
                notes: "读校验：传输方向枚举。虚拟环境。"));
            return results;
        }

        // GetParity: PEN=0 → PARITY_NONE (0). Do not treat READ_BIT(PEN) as masked return.
        if (fn.FunctionName.Contains("GetParity", StringComparison.OrdinalIgnoreCase)
            && !fn.FunctionName.Contains("Stick", StringComparison.OrdinalIgnoreCase))
        {
            results.Add(BuildReadCheckModel(
                fn, instance, PrepareReadParameters(fn, instance, instance, CloneParams()),
                "CR1", initial: 0u, expectedReturn: 0u,
                nameSuffix: "CR1.PEN/none/read-check",
                detail: "Parity：PEN 清零→PARITY_NONE=0",
                notes: "读校验：无奇偶校验。虚拟环境。"));
            return results;
        }

        // GetBaudRateHz: (PclkHz + reg/2) / reg.
        if (fn.FunctionName.Contains("GetBaudRateHz", StringComparison.OrdinalIgnoreCase))
        {
            var baudShift = ReadBitShiftPattern.Match(body);
            if (baudShift.Success
                && TryParseUintDefineFromFileCandidates(
                    fn.FilePath, baudShift.Groups["msk"].Value, out var baudMsk)
                && baudMsk != 0)
            {
                var baudPos = TryParseUintDefineFromFileCandidates(
                    fn.FilePath, baudShift.Groups["pos"].Value, out var bp)
                    ? (int)bp
                    : PosFromMask(baudMsk);
                const uint div = 16u;
                const uint pclk = 16000000u;
                var seed = (div << baudPos) & baudMsk;
                var expected = (pclk + (div / 2u)) / div;
                var parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
                foreach (var p in parameters)
                {
                    if (p.Name.Equals("PclkHz", StringComparison.OrdinalIgnoreCase)
                        || p.Name.Equals("Pclk", StringComparison.OrdinalIgnoreCase))
                    {
                        p.ValueExpression = pclk.ToString();
                        p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                    }
                }

                results.Add(BuildReadCheckModel(
                    fn, instance, parameters, "BAUD", seed, expected,
                    nameSuffix: "BAUD.div/hz/read-check",
                    detail: $"BaudRateHz：div={div} Pclk={pclk} → {expected}",
                    notes: "读校验：波特率 Hz 换算。虚拟环境。"));
                return results;
            }
        }

        // Dual out-pointer extractors (GetCaptureAValueAndDirection): avoid heavy/hanging analysis.
        if (fn.FunctionName.Contains("ValueAndDirection", StringComparison.OrdinalIgnoreCase)
            || (body.Contains("*pVal", StringComparison.Ordinal)
                && body.Contains("*pDir", StringComparison.Ordinal)))
        {
            // Use nested-paren path so PWM[(Pwmx)%N].REG.CAPAR does not stop at (Pwmx).
            var cap = ReadRegPattern.Match(body);
            if (cap.Success && TryParseRegAccessPath(cap.Groups["path"].Value.Trim(), out var capPath))
            {
                var mem = string.IsNullOrEmpty(capPath.LeafMember)
                    ? cap.Groups["path"].Value.Trim()
                    : capPath.LeafMember;
                var targetInstance = ResolveNestedInstance(instance, capPath, 0, null);
                // Seed both CAPA (lo16) and DIR (bit16) so pVal extract is non-trivial.
                const uint seed = 0x1A5A5u;
                var capaMsk = Regex.Match(
                    body,
                    @"\b(?<msk>[A-Za-z0-9_]+_CAP[AB]_Msk)\b",
                    RegexOptions.IgnoreCase);
                uint expected = seed & 0xFFFFu;
                if (capaMsk.Success
                    && TryParseUintDefineFromFileCandidates(
                        fn.FilePath, capaMsk.Groups["msk"].Value, out var cm)
                    && cm != 0)
                    expected = (seed & cm) >> PosFromMask(cm);

                var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
                foreach (var p in parameters)
                {
                    if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                    if (p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase))
                    {
                        p.ValueExpression = "0";
                        p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                    }
                }

                // Host void+pVal mirrors first host word into out_ret.
                results.Add(BuildReadCheckModel(
                    fn, targetInstance, parameters, mem, seed, expected,
                    nameSuffix: $"{mem}/dual-out/read-check",
                    detail:
                    $"双输出指针：预置 {targetInstance}.{mem}=0x{seed:X}，Expected pVal=0x{expected:X}",
                    notes: "读校验：ValueAndDirection 预置捕获寄存器，宿主返回 *pVal。虚拟环境。"));
                return results;
            }
        }

        // !(Num & 7) — IsProgAddrOrSizeAlign8Bytes (pure arithmetic, no register).
        var alignExpr = Regex.Match(
            body,
            @"return\s*\(\s*uint32_t\s*\)\s*\(\s*!\s*\(\s*(?<p>[A-Za-z_][A-Za-z0-9_]*)\s*&\s*(?<m>\d+)\s*\)\s*\)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (alignExpr.Success
            && uint.TryParse(alignExpr.Groups["m"].Value, out var alignMask)
            && alignMask != 0)
        {
            var pName = alignExpr.Groups["p"].Value;
            // Aligned sample: Num=0 → !(0&m)=1.
            var parameters = CloneParams();
            foreach (var p in parameters)
            {
                if (p.Name.Equals(pName, StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/align0/read-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = parameters;
            model.InitialRegisters = [];
            model.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.ReturnValue,
                    ExpectedHex = "0x1",
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = $"纯算术对齐：{pName}=0 → !({pName}&{alignMask}) == 1"
                },
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = $"读校验：!(Num&{alignMask}) 对齐判定。虚拟环境。";
            results.Add(model);
            return results;
        }

        // Absolute CHIP_SIZE_MODE compare — IsSize128KB; unmapped/zero → not 128K → return 0.
        if (body.Contains("LL_EFLASH_REG_ADDR_CHIP_SIZE_MODE", StringComparison.Ordinal)
            && body.Contains("LL_EFLASH_CHIP_SIZE_MODE_128K", StringComparison.Ordinal))
        {
            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/chip-size-default/read-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
            model.InitialRegisters = [];
            model.Assertions =
            [
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.ReturnValue,
                    ExpectedHex = "0x0",
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail =
                        "CHIP_SIZE_MODE 绝对址默认非 0xA5A5 → IsSize128KB 返回 0（虚拟环境未烧写 size mode）"
                },
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "读校验：绝对址 chip size mode 默认非 128K。虚拟环境。";
            results.Add(model);
            return results;
        }

        // return (uint32_t)(&CANx->RBUFDT[0]) — host asserts offsetof (x64 truncates absolute ptr).
        var bufAddr = Regex.Match(
            body,
            @"return\s*\(\s*uint32_t\s*\)\s*\(\s*&\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z_][A-Za-z0-9_]*)\s*\[\s*0\s*\]\s*\)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (bufAddr.Success)
        {
            var mem = bufAddr.Groups["mem"].Value;
            // EF/SQLite cannot translate StartsWith(..., StringComparison) — keep equality only.
            var memPrefix = mem + "[";
            var memAlt = mem + "0";
            var offsetRow = await db.RegisterDefinitions.AsNoTracking()
                .Where(r => r.SdkProjectId == fn.SdkProjectId
                            && (r.MemberName == mem
                                || r.MemberName.StartsWith(memPrefix)
                                || r.MemberName.StartsWith(memAlt)))
                .OrderBy(r => r.OffsetBytes ?? int.MaxValue)
                .Select(r => new { r.OffsetBytes, r.AbsoluteAddress })
                .FirstOrDefaultAsync(ct);

            uint? hostOff = offsetRow?.OffsetBytes is int ob && ob >= 0 ? (uint)ob : null;
            if (hostOff is null || hostOff == 0)
            {
                var sdkRoot = await db.SdkProjects.AsNoTracking()
                    .Where(p => p.Id == fn.SdkProjectId)
                    .Select(p => p.SdkRootPath)
                    .FirstOrDefaultAsync(ct);
                var catalog = VirtualMcu.ChipHeaderAddressCatalog.TryLoad(sdkRoot);
                if (catalog is not null
                    && catalog.TryGetOffset(instance, null, mem, out var off)
                    && off >= 0)
                    hostOff = (uint)off;
            }

            if (hostOff is uint offVal)
            {
                var absNote = offsetRow?.AbsoluteAddress is uint abs && abs != 0
                    ? $" AbsoluteAddress=0x{abs:X}"
                    : "";
                var addrModel = BaseModel(fn);
                addrModel.Name = $"{fn.FunctionName}/{instance}/{mem}/addr/read-check";
                addrModel.Status = nameof(LlTestCaseStatus.Ready);
                addrModel.IsAutoGenerated = true;
                addrModel.Parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
                addrModel.InitialRegisters = [];
                addrModel.Assertions =
                [
                    ReturnValueAssertion(
                        $"0x{offVal:X}",
                        $"&{instance}.{mem}[0] host offsetof=0x{offVal:X}{absNote}"),
                    ..DefaultTimeoutAssertions()
                ];
                addrModel.Notes =
                    $"读校验：宿主返回 &{mem}[0] 相对外设映像偏移 0x{offVal:X}（MCU 上为绝对址）。虚拟环境。";
                results.Add(addrModel);
                return results;
            }
        }

        // sizeof(CANx->TBUFDT) — compile-time array byte size (16*4=64).
        var sizeofMem = SizeofMemberPattern.Match(body);
        if (sizeofMem.Success)
        {
            var mem = sizeofMem.Groups["mem"].Value;
            uint words = 0;
            if (!string.IsNullOrWhiteSpace(fn.FilePath))
            {
                foreach (var path in CandidateDefineFiles(fn.FilePath, null))
                {
                    try
                    {
                        var text = File.ReadAllText(path);
                        var arr = Regex.Match(
                            text,
                            $@"\b{Regex.Escape(mem)}\s*\[\s*(?<n>\d+)\s*\]");
                        if (arr.Success && uint.TryParse(arr.Groups["n"].Value, out var n) && n > 0)
                        {
                            words = n;
                            break;
                        }

                        var def = Regex.Match(
                            text,
                            $@"#define\s+LL_[A-Za-z0-9_]*{Regex.Escape(mem)}[A-Za-z0-9_]*_(?:WORD_LAYER_LEVEL|LEVEL|SIZE|NUMS)\s+\(?\s*(?<n>\d+)");
                        if (def.Success && uint.TryParse(def.Groups["n"].Value, out var dn) && dn > 0)
                        {
                            words = dn;
                            break;
                        }
                    }
                    catch { /* ignore */ }
                }
            }

            if (words == 0
                && (mem.Equals("TBUFDT", StringComparison.OrdinalIgnoreCase)
                    || mem.Equals("RBUFDT", StringComparison.OrdinalIgnoreCase)
                    || mem.Equals("SBUFDT", StringComparison.OrdinalIgnoreCase)))
                words = 16;
            if (words != 0)
            {
                var bytes = words * 4u;
                var sizeofModel = BaseModel(fn);
                sizeofModel.Name = $"{fn.FunctionName}/{instance}/{mem}/sizeof/read-check";
                sizeofModel.Status = nameof(LlTestCaseStatus.Ready);
                sizeofModel.IsAutoGenerated = true;
                sizeofModel.Parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
                sizeofModel.InitialRegisters = [];
                sizeofModel.Assertions =
                [
                    ReturnValueAssertion(
                        $"0x{bytes:X}",
                        $"sizeof({mem}[{words}]) = {bytes} bytes"),
                    ..DefaultTimeoutAssertions()
                ];
                sizeofModel.Notes =
                    $"读校验：sizeof 数组 {mem}[{words}] → 0x{bytes:X}。虚拟环境。";
                results.Add(sizeofModel);
                return results;
            }
        }

        // Scalar Extract: READ_BIT_SHIFT(Info, Msk, Pos) — value in Info param, no peri reg.
        var scalarShift = ReadBitShiftScalarPattern.Match(body);
        if (scalarShift.Success
            && !body.Contains("->", StringComparison.Ordinal)
            && !body.Contains("REG_OFFSET", StringComparison.OrdinalIgnoreCase))
        {
            var srcParam = scalarShift.Groups["src"].Value;
            var bodyMskMacro = scalarShift.Groups["msk"].Value;
            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out var mask)
                || mask == 0)
                mask = await ResolveClearMaskAsync(db, fn, "", bodyMskMacro, ct);
            if (mask == 0) return results;
            var bodyPosMacro = scalarShift.Groups["pos"].Success
                ? scalarShift.Groups["pos"].Value
                : null;
            var pos = bodyPosMacro is not null
                      && TryParseUintDefineFromFileCandidates(fn.FilePath, bodyPosMacro, out var posLit)
                ? (int)posLit
                : PosFromMask(mask);
            var maxVal = mask >> pos;
            if (maxVal == 0) return results;
            var fieldValue = maxVal > 1 ? maxVal / 2u : 1u;
            if (fieldValue == 0) fieldValue = 1u;
            var info = (fieldValue << pos) & mask;
            var expected = (info & mask) >> pos;
            var parameters = CloneParams();
            var infoP = parameters.FirstOrDefault(p =>
                p.Name.Equals(srcParam, StringComparison.OrdinalIgnoreCase));
            infoP ??= parameters.FirstOrDefault(p => !p.Type.Contains('*', StringComparison.Ordinal));
            if (infoP is not null)
            {
                infoP.ValueExpression = $"0x{info:X}";
                infoP.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }

            var label = TryFieldNameFromMskMacro(bodyMskMacro, "", out var fnField)
                ? fnField
                : StripMaskSuffix(bodyMskMacro);
            // Scalar Info extract: ReturnValue only — no virtual register member.
            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/{instance}/Info.{label}/seed/read-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = parameters;
            model.InitialRegisters = [];
            model.Assertions =
            [
                ReturnValueAssertion(
                    $"0x{expected:X}",
                    $"Scalar READ_BIT_SHIFT({srcParam}=0x{info:X}, {bodyMskMacro}) → 0x{expected:X}"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "读校验：标量 Info 提取，无外设寄存器。虚拟环境。";
            results.Add(model);
            return results;
        }

        // Scalar Extract bool: !!READ_BIT(Info, MSK)
        var scalarBit = ReadBitScalarMaskPattern.Match(body);
        if (scalarBit.Success
            && !body.Contains("->", StringComparison.Ordinal)
            && !body.Contains("REG_OFFSET", StringComparison.OrdinalIgnoreCase))
        {
            var srcParam = scalarBit.Groups["src"].Value;
            var bodyMskMacro = scalarBit.Groups["msk"].Value;
            if (!TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out var mask)
                || mask == 0)
                mask = await ResolveClearMaskAsync(db, fn, "", bodyMskMacro, ct);
            if (mask == 0) return results;
            var info = mask;
            var isBool = body.Contains("!!", StringComparison.Ordinal)
                         || body.Contains("? 1UL", StringComparison.Ordinal)
                         || body.Contains("?1UL", StringComparison.Ordinal);
            var expected = isBool ? 1u : (info & mask);
            var parameters = CloneParams();
            var infoP = parameters.FirstOrDefault(p =>
                p.Name.Equals(srcParam, StringComparison.OrdinalIgnoreCase));
            infoP ??= parameters.FirstOrDefault(p => !p.Type.Contains('*', StringComparison.Ordinal));
            if (infoP is not null)
            {
                infoP.ValueExpression = $"0x{info:X}";
                infoP.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
            }

            var label = TryFieldNameFromMskMacro(bodyMskMacro, "", out var fnField)
                ? fnField
                : StripMaskSuffix(bodyMskMacro);
            var model = BaseModel(fn);
            model.Name = $"{fn.FunctionName}/{instance}/Info.{label}/seed/read-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = parameters;
            model.InitialRegisters = [];
            model.Assertions =
            [
                ReturnValueAssertion(
                    $"0x{expected:X}",
                    $"Scalar READ_BIT({srcParam}=0x{info:X}, {bodyMskMacro}) → 0x{expected:X}"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "读校验：标量 Info 布尔/掩码提取。虚拟环境。";
            results.Add(model);
            return results;
        }

        // REG_OFFSET(...).MEM READ_BIT_SHIFT (ADC DMA IsStopping) before flat ->path.
        var regOffMemRead = ReadBitShiftRegOffsetMemberPattern.Match(body);
        if (regOffMemRead.Success)
        {
            var built = await TryBuildRegOffsetReadCaseAsync(
                db, fn, instance, CloneParams(), regOffMemRead, flatNoLeaf: false, ct);
            if (built is not null)
            {
                results.Add(built);
                return results;
            }
        }

        var regOffFlatRead = ReadBitShiftRegOffsetFlatPattern.Match(body);
        if (regOffFlatRead.Success)
        {
            var built = await TryBuildRegOffsetReadCaseAsync(
                db, fn, instance, CloneParams(), regOffFlatRead, flatNoLeaf: true, ct);
            if (built is not null)
            {
                results.Add(built);
                return results;
            }
        }

        // READ_REG(REG_OFFSET(JDR0, Seq)) — full word return.
        var regOffReadReg = ReadRegOffsetFlatPattern.Match(body);
        if (regOffReadReg.Success)
        {
            var baseMem = regOffReadReg.Groups["base"].Value.Trim();
            var regIdx = regOffReadReg.Groups["regidx"].Value.Trim();
            const uint ch = 0;
            var member = ResolveRegOffsetIndexedMember(baseMem, ch);
            const uint preload = 0x1u;
            var parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
            AssignRegOffsetChannelParam(parameters, regIdx, ch);
            // Seq / Grp index params
            foreach (var p in parameters)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Seq", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Grp", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = ch.ToString();
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }

            results.Add(BuildReadCheckModel(
                fn, instance, parameters, member, preload, preload,
                nameSuffix: $"{member}/ch{ch}/read-check",
                detail: $"READ_REG REG_OFFSET({baseMem})→{member} Expected=0x{preload:X}",
                notes: $"读校验：REG_OFFSET READ_REG → {member}。虚拟环境。"));
            return results;
        }

        // Channel-indexed BIT(...) flag — BIT((Ch)%N) or BIT(((Fltx)%N)+Pos) / BIT(((Pwmx)%N)*2+Pos).
        var chBit = ReadBitShiftChannelBitPattern.Match(body);
        if (chBit.Success)
        {
            var laneRead = Regex.Match(
                body,
                @"READ_BIT_SHIFT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*BIT\s*\(\s*(?<bitexpr>[^,]+?)\s*\)\s*,\s*\((?<posexpr>[^)]*)\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
            _ = TryParseRegAccessPath(
                (laneRead.Success ? laneRead.Groups["path"].Value : chBit.Groups["path"].Value).Trim(),
                out var chPath);
            var member = string.IsNullOrEmpty(chPath.LeafMember)
                ? chBit.Groups["path"].Value.Trim()
                : chPath.LeafMember;
            var targetInstance = ResolveNestedInstance(instance, chPath, 0, null);
            const uint ch = 0;
            var bitExpr = laneRead.Success ? laneRead.Groups["bitexpr"].Value : "";
            var posExpr = laneRead.Success ? laneRead.Groups["posexpr"].Value : "";
            uint bitPos = 0;
            var posTok = Regex.Match(
                string.IsNullOrEmpty(bitExpr) ? posExpr : bitExpr,
                @"(?<pos>[A-Za-z0-9_]+_Pos)\b");
            if (posTok.Success)
                _ = TryParseUintDefineFromFileCandidates(fn.FilePath, posTok.Groups["pos"].Value, out bitPos);
            // Lane index 0 → shift equals base Pos (0 when BIT((Ch)%N) only).
            var laneShift = (int)(bitPos % 32);
            var bitMask = 1u << laneShift;
            var preloadFull = bitMask;
            // READ_BIT_SHIFT returns the bit field value at posexpr (0/1 for single bit).
            var expected = 1u;
            EnsureReadExpectationConsistent(
                $"{targetInstance}.{member}", preloadFull, bitMask, laneShift, expected);

            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            foreach (var p in parameters)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Contains("Channel", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Pin", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Fltx", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Trigx", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = ch.ToString();
                    p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }
            }

            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, member, preloadFull, expected,
                nameSuffix: $"{member}.BIT{laneShift}/read-check",
                detail:
                $"lane=0；Initial=0x{preloadFull:X} Mask=0x{bitMask:X} Pos={laneShift} Expected=0x{expected:X}",
                notes:
                $"自动读校验：lane=0，InitialRegisterValue=0x{preloadFull:X}，ExpectedReturn=0x{expected:X}。虚拟环境。"));
            return results;
        }

        // READ_BIT_SHIFT(reg, Msk<<(Ch*k), Pos+(Ch*k)) — Channel=0 → base field.
        var chShiftRead = ReadBitShiftChannelShiftedMaskPattern.Match(body);
        if (chShiftRead.Success)
        {
            _ = TryParseRegAccessPath(chShiftRead.Groups["path"].Value.Trim(), out var accessPath);
            var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
                ? chShiftRead.Groups["path"].Value.Trim()
                : accessPath.LeafMember;
            var bodyMskMacro = chShiftRead.Groups["msk"].Value;
            var bodyPosMacro = chShiftRead.Groups["pos"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var readPairNote);
            var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);
            if (!TryFieldNameFromMskMacro(bodyMskMacro, member, out var fieldName)
                && !TryParseChipMaskRegAndField(bodyMskMacro, bodyMember, out _, out fieldName))
                fieldName = bodyMskMacro;
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (!TryResolveFieldMaskPos(fn.FilePath, field, bodyMskMacro, bodyPosMacro, out var mask, out var pos)
                || mask == 0)
            {
                mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
                if (mask == 0
                    && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask))
                    return results;
                if (mask == 0) return results;
                pos = TryParseUintDefineFromFileCandidates(fn.FilePath, bodyPosMacro, out var posLit)
                    ? (int)posLit
                    : PosFromMask(mask);
            }

            var maxVal = mask >> pos;
            if (maxVal == 0) return results;
            var (tag, fieldValue, withInterference) = EnumerateFieldReadSamples(maxVal).First();
            var initial = BuildFieldReadInitial(fieldValue, mask, pos, withInterference);
            var expected = DeriveFieldReadExpected(initial, mask, pos);
            EnsureReadExpectationConsistent(
                $"{targetInstance}.{member}.{fieldName}", initial, mask, pos, expected);
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            foreach (var p in parameters)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }
            }

            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, member, initial, expected,
                nameSuffix: $"{member}.{fieldName}/ch0/{tag}/read-check",
                detail:
                $"Channel=0；Register={targetInstance}.{member} Field={fieldName} Initial=0x{initial:X} " +
                $"Mask=0x{mask:X} Pos={pos} ExpectedReturn=0x{expected:X}；{readPairNote}",
                notes:
                $"自动读校验[ch0/{tag}]：移位掩码 Channel=0；Initial=0x{initial:X} Expected=0x{expected:X}。虚拟环境。"));
            return results;
        }

        // READ_BIT(reg, Msk<<(Ch*k)) ? 1 : 0 — Channel=0 boolean.
        var chShiftBool = ReadBitChannelShiftedMaskPattern.Match(body);
        if (chShiftBool.Success)
        {
            _ = TryParseRegAccessPath(chShiftBool.Groups["path"].Value.Trim(), out var bitPath);
            var bodyMember = string.IsNullOrEmpty(bitPath.LeafMember)
                ? chShiftBool.Groups["path"].Value.Trim()
                : bitPath.LeafMember;
            var bodyMskMacro = chShiftBool.Groups["msk"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var bitPairNote);
            var targetInstance = ResolveNestedInstance(instance, bitPath, 0, bodyMskMacro);
            var mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
            if (mask == 0
                && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask))
                return results;
            if (mask == 0) return results;
            var label = TryFieldNameFromMskMacro(bodyMskMacro, member, out var fnField)
                ? fnField
                : StripMaskSuffix(bodyMskMacro);
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            foreach (var p in parameters)
            {
                if (p.Type.Contains('*', StringComparison.Ordinal)) continue;
                if (p.Name.Equals("Channel", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromRegisterDefinition);
                }
            }

            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, member, initial: mask, expectedReturn: 1u,
                nameSuffix: $"{member}.{label}/ch0/seed/read-check",
                detail:
                $"布尔读 Channel=0：先写 0x{mask:X} Mask=0x{mask:X} Expected=1；{bitPairNote}",
                notes: "读校验：通道移位掩码 Channel=0，先写再读返回 1。虚拟环境。"));
            return results;
        }

        // !!READ_BIT_SHIFT(reg, ((Pwmxs)&MASK)<<Pos, Pos) — IsMultiPWMCountersResetting.
        var rtShift = ReadBitShiftRuntimeAndCompositePattern.Match(body);
        if (rtShift.Success)
        {
            var built = await TryBuildRuntimeAndCompositeReadCaseAsync(
                db, fn, instance, CloneParams(), rtShift, isShift: true, ct);
            if (built is not null)
            {
                results.Add(built);
                return results;
            }
        }

        // !!READ_BIT(reg, ((Pwmxs)&MASK)) — IsMultiPWMUpdateBusy.
        var rtBit = ReadBitRuntimeAndCompositePattern.Match(body);
        if (rtBit.Success)
        {
            var built = await TryBuildRuntimeAndCompositeReadCaseAsync(
                db, fn, instance, CloneParams(), rtBit, isShift: false, ct);
            if (built is not null)
            {
                results.Add(built);
                return results;
            }
        }

        // READ_BIT_SHIFT / (READ_BIT >> Pos) field-value getters.
        // Prefer BODY mask/pos (what the compiled LL actually uses).
        var shift = ReadBitShiftPattern.Match(body);
        if (!shift.Success)
            shift = ReadBitThenShiftPattern.Match(body);
        if (shift.Success)
        {
            _ = TryParseRegAccessPath(shift.Groups["path"].Value.Trim(), out var accessPath);
            var bodyMember = string.IsNullOrEmpty(accessPath.LeafMember)
                ? shift.Groups["path"].Value.Trim()
                : accessPath.LeafMember;
            var bodyMskMacro = shift.Groups["msk"].Value;
            var bodyPosMacro = shift.Groups["pos"].Success ? shift.Groups["pos"].Value : null;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var readPairNote);
            var targetInstance = ResolveNestedInstance(instance, accessPath, 0, bodyMskMacro);

            if (!TryFieldNameFromMskMacro(bodyMskMacro, member, out var fieldName)
                && !TryParseChipMaskRegAndField(bodyMskMacro, bodyMember, out _, out fieldName))
                fieldName = bodyMskMacro.StartsWith("0x", StringComparison.OrdinalIgnoreCase)
                    ? "LIT"
                    : bodyMskMacro;

            if (string.IsNullOrWhiteSpace(fieldName))
                return results;

            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (!TryResolveFieldMaskPos(fn.FilePath, field, bodyMskMacro, bodyPosMacro, out var mask, out var pos)
                || mask == 0)
            {
                // Chip literal OR LL_* composite expand (MST_IT_FLAG = EOC|… OR of chip masks).
                mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
                if (mask == 0
                    && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask))
                    mask = 0;
                if (mask == 0)
                    _ = TryParseHexOrDecToken(bodyMskMacro, out mask);
                if (mask == 0) return results;
                pos = 0;
                if (bodyPosMacro is not null)
                {
                    if (TryParseHexOrDecToken(bodyPosMacro, out var posLit))
                        pos = (int)posLit;
                    else if (TryParseUintDefineFromFileCandidates(
                                 fn.FilePath, bodyPosMacro, out posLit))
                        pos = (int)posLit;
                    else
                        pos = PosFromMask(mask);
                }
                else
                    pos = PosFromMask(mask);
            }

            var maxVal = mask >> pos;
            if (maxVal == 0) return results;

            // IsEnabledUpdateEvent / IsBufferReleaseDone: return (!READ_BIT_SHIFT(...))
            // !!READ_BIT_SHIFT is double-negation (positive); only a single ! inverts.
            // UART IsEnabledFIFO/OverrunDetect: READ_BIT_SHIFT(...) ^ 0x1UL (active-low disable bit).
            var invertShift = Regex.IsMatch(
                body,
                @"(?<!\!)!\s*\(?\s*READ_BIT(?:_SHIFT)?\s*\(",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase)
                || Regex.IsMatch(
                    body,
                    @"READ_BIT(?:_SHIFT)?\s*\([^;]{0,200}?\)\s*\^\s*(?:0x1|1)(?:UL|U)?",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

            var fieldSource = $"体宏 {bodyMskMacro}/{bodyPosMacro ?? $"pos={pos}"} path={accessPath.RawPath}";
            foreach (var (tag, fieldValue, withInterference) in EnumerateFieldReadSamples(maxVal))
            {
                // Invert getters: seed field clear so !0 → return 1.
                var seedField = invertShift ? 0u : fieldValue;
                var initial = BuildFieldReadInitial(seedField, mask, pos, withInterference && !invertShift);
                var raw = DeriveFieldReadExpected(initial, mask, pos);
                var expected = invertShift ? (raw == 0 ? 1u : 0u) : raw;
                // !!READ_BIT_SHIFT → boolean 0/1 (RCU IsEnabledADCClock multi-bit gate).
                var asBool = !invertShift && Regex.IsMatch(
                    body, @"!!\s*READ_BIT(?:_SHIFT)?\s*\(",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                if (asBool)
                    expected = raw != 0 ? 1u : 0u;
                // I2C GetSCL*Count / GetRxFIFOThreshold: return (field + 1UL).
                var plusOne = !invertShift && !asBool && Regex.IsMatch(
                    body,
                    @"READ_BIT(?:_SHIFT)?[\s\S]{0,120}\+\s*1(?:UL)?",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                if (plusOne)
                    expected = raw + 1u;
                // DMA Get*TransWidthBytes returns (1<<code), not the raw field code.
                var widthBytes = !invertShift && !asBool
                                 && fn.FunctionName.Contains("TransWidthBytes", StringComparison.OrdinalIgnoreCase);
                if (widthBytes)
                    expected = raw <= 2 ? 1u << (int)raw : 0u;
                // Compare-to-constant getters: (field == LL_*_LOCK) ? 1 : 0
                var cmpConst = TryMatchFieldCompareConstant(body, fn.FilePath, out var cmpLit);
                if (!invertShift && !asBool && cmpConst)
                {
                    expected = raw == cmpLit ? 1u : 0u;
                    // Seed the constant so Get returns 1.
                    seedField = cmpLit;
                    initial = BuildFieldReadInitial(seedField, mask, pos, withInterference: false);
                    raw = DeriveFieldReadExpected(initial, mask, pos);
                    expected = raw == cmpLit ? 1u : 0u;
                }

                if (!invertShift && !asBool && !widthBytes && !cmpConst && !plusOne)
                {
                    EnsureReadExpectationConsistent(
                        $"{targetInstance}.{member}.{fieldName}", initial, mask, pos, expected);
                    if (expected != fieldValue)
                    {
                        throw new InvalidOperationException(
                            $"读用例字段干扰位泄漏：{member}.{fieldName} fieldValue=0x{fieldValue:X} " +
                            $"initial=0x{initial:X} → derived=0x{expected:X}");
                    }
                }

                results.Add(BuildReadCheckModel(
                    fn, targetInstance,
                    PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                    member, initial, expected,
                    nameSuffix: $"{member}.{fieldName}/{(invertShift ? "invert-" : asBool ? "bool-" : "")}{tag}/read-check",
                    detail:
                    $"Register={targetInstance}.{member} Field={fieldName} Initial=0x{initial:X} " +
                    $"Mask=0x{mask:X} Pos={pos} ExpectedReturn=0x{expected:X}" +
                    $"{(invertShift ? "（逻辑取反 !READ_BIT_SHIFT）" : "")}" +
                    $"{(asBool ? "（!! 布尔化）" : "")}" +
                    $"{(widthBytes ? "（宽度字节 1<<code）" : "")}" +
                    $"{(cmpConst ? $"（比较常量 0x{cmpLit:X}）" : "")}（{fieldSource}；{readPairNote}）",
                    notes:
                    $"自动读校验[{tag}]：InitialRegisterValue=0x{initial:X}；" +
                    $"ExpectedReturn=0x{expected:X}；读后寄存器不变。虚拟环境。"));

                // Invert / compare / width / bool: one representative sample is enough.
                if (invertShift || asBool || widthBytes || cmpConst)
                    break;
            }

            return results;
        }

        // (READ_BIT(reg, Msk) == 0) ? 1UL : 0UL — IsAllChannelDisabled / idle-active style.
        var eqZero = ReadBitEqZeroBoolPattern.Match(body);
        if (eqZero.Success)
        {
            _ = TryParseRegAccessPath(eqZero.Groups["path"].Value.Trim(), out var zPath);
            var bodyMember = string.IsNullOrEmpty(zPath.LeafMember)
                ? eqZero.Groups["path"].Value.Trim()
                : zPath.LeafMember;
            var bodyMskMacro = eqZero.Groups["msk"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var zNote);
            var targetInstance = ResolveNestedInstance(instance, zPath, 0, bodyMskMacro);
            var mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
            if (mask == 0
                && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask))
                return results;
            if (mask == 0) return results;
            // Seed cleared field → READ_BIT==0 → return 1.
            results.Add(BuildReadCheckModel(
                fn, targetInstance,
                PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                member, initial: 0u, expectedReturn: 1u,
                nameSuffix: $"{member}.{StripMaskSuffix(bodyMskMacro)}/eq0/read-check",
                detail:
                $"布尔 (READ_BIT==0)：初值 0 Mask=0x{mask:X} ExpectedReturn=1；{zNote}",
                notes: "读校验：通道全关/标志清零时返回 1。虚拟环境。"));
            return results;
        }

        // (READ_BIT(reg, Mask) & LL_*_MSK) ? 1UL : 0UL — EFLASH IsActiveFlag(Mask).
        var paramAndMsk = Regex.Match(
            body,
            @"READ_BIT\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<param>[A-Za-z_][A-Za-z0-9_]*)\s*\)\s*&\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*\)\s*\?\s*1",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        if (paramAndMsk.Success && !IsCompileTimeMaskToken(paramAndMsk.Groups["param"].Value))
        {
            var clampMacro = paramAndMsk.Groups["msk"].Value;
            var maskParamName = paramAndMsk.Groups["param"].Value;
            _ = TryParseRegAccessPath(paramAndMsk.Groups["path"].Value.Trim(), out var andPath);
            var bodyMember = string.IsNullOrEmpty(andPath.LeafMember)
                ? paramAndMsk.Groups["path"].Value.Trim()
                : andPath.LeafMember;
            var member = ResolveMemberAlignedToMask(bodyMember, clampMacro, out _, out var andNote);
            var mask = await ResolveClearMaskAsync(db, fn, member, clampMacro, ct);
            if (mask == 0
                && !TryParseUintDefineFromFileCandidates(fn.FilePath, clampMacro, out mask))
                return results;
            if (mask == 0) return results;
            var targetInstance = ResolveNestedInstance(instance, andPath, 0, clampMacro);
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            AssignRuntimeMaskParam(parameters, maskParamName, mask, clampMacro);
            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, member, initial: mask, expectedReturn: 1u,
                nameSuffix: $"{member}.{StripMaskSuffix(clampMacro)}/mask-and/read-check",
                detail:
                $"(READ_BIT&{clampMacro})?1：Mask=0x{mask:X} Initial=0x{mask:X} Expected=1；{andNote}",
                notes: "读校验：Mask 与复合 IT/Flag 掩码相交非零时返回 1。虚拟环境。"));
            return results;
        }

        // IsEnabledIT: (READ_BIT(reg, Mask) == (Mask)) ? 1UL : 0UL — Mask is a function param.
        // Draft previously left Mask=0 → always returns 1 with timeout-only Skipped.
        var paramEq = ReadBitParamEqBoolPattern.Match(body);
        if (paramEq.Success && !IsCompileTimeMaskToken(paramEq.Groups["msk"].Value))
        {
            var maskParamName = paramEq.Groups["msk"].Value;
            if (!TryResolveRuntimeMaskParam(
                    fn.FilePath, fn.FunctionName, maskParamName,
                    out var llMacro, out var mask, out var chipTok)
                || mask == 0)
                return results;

            _ = TryParseRegAccessPath(paramEq.Groups["path"].Value.Trim(), out var bitPath);
            var bodyMember = string.IsNullOrEmpty(bitPath.LeafMember)
                ? paramEq.Groups["path"].Value.Trim()
                : bitPath.LeafMember;
            var member = ResolveMemberAlignedToMask(bodyMember, llMacro, out _, out var bitPairNote);
            var nestMsk = chipTok ?? llMacro;
            var targetInstance = ResolveNestedInstance(instance, bitPath, 0, nestMsk);
            var label = TryFieldNameFromMskMacro(llMacro, member, out var fnField)
                ? fnField
                : StripMaskSuffix(llMacro);
            // One representative true sample: write mask bits, then Get should return 1.
            var initial = mask;
            var expected = 1u;
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            AssignRuntimeMaskParam(parameters, maskParamName, mask, llMacro);
            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, member, initial, expected,
                nameSuffix: $"{member}.{label}/seed/read-check",
                detail:
                $"参数掩码布尔：(reg&Mask)==Mask；Mask={llMacro}=0x{mask:X}；" +
                $"先写 0x{initial:X} 再读 Expected=0x{expected:X}；path={bitPath.RawPath}；{bitPairNote}",
                notes:
                $"读校验：先写寄存器 0x{initial:X}，再调用 Get 校验返回 0x{expected:X}。虚拟环境。"));

            return results;
        }

        // READ_BIT(reg, A_Msk | B_Msk) ? 1 : 0 — IsConversionRunning.
        var orMask = ReadBitOrMaskBoolPattern.Match(body);
        if (orMask.Success && orMask.Groups["mskexpr"].Value.Contains('|'))
        {
            _ = TryParseRegAccessPath(orMask.Groups["path"].Value.Trim(), out var orPath);
            var bodyMember = string.IsNullOrEmpty(orPath.LeafMember)
                ? orMask.Groups["path"].Value.Trim()
                : orPath.LeafMember;
            var mskExpr = orMask.Groups["mskexpr"].Value;
            uint mask = 0;
            foreach (Match tok in ChipFieldMskToken.Matches(mskExpr))
            {
                if (TryParseUintDefineFromFileCandidates(fn.FilePath, tok.Groups["tok"].Value, out var bit)
                    && bit != 0)
                    mask |= bit;
                else
                    mask |= await ResolveClearMaskAsync(db, fn, bodyMember, tok.Groups["tok"].Value, ct);
            }

            if (mask != 0)
            {
                var targetInstance = ResolveNestedInstance(instance, orPath, 0, null);
                var isBool = body.Contains("? 1UL", StringComparison.Ordinal)
                             || body.Contains("?1UL", StringComparison.Ordinal)
                             || Regex.IsMatch(body, @"\(\s*READ_BIT[^)]+\)\s*\?\s*1");
                // IWDG IsReady: (READ_BIT(SR, A|B) == 0) ? 1 : 0 — seed cleared, expect 1.
                var orEqZero = Regex.IsMatch(
                    body,
                    @"READ_BIT[\s\S]{0,220}==\s*0(?:UL)?\s*\)\s*\?\s*1",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                var initial = orEqZero ? 0u : mask;
                var expected = isBool || orEqZero ? 1u : mask;
                results.Add(BuildReadCheckModel(
                    fn, targetInstance,
                    PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                    bodyMember, initial, expected,
                    nameSuffix: $"{bodyMember}.OR_MSK/{(orEqZero ? "eq0" : "seed")}/read-check",
                    detail:
                    $"OR 掩码读{(orEqZero ? "==0→1" : "")}：Initial=0x{initial:X} Mask=0x{mask:X} Expected=0x{expected:X}",
                    notes: orEqZero
                        ? "读校验：OR 掩码全清时返回 1。虚拟环境。"
                        : "读校验：多位 OR 掩码。虚拟环境。"));
                return results;
            }
        }

        // READ_BIT(reg, Flag/Interrupt) runtime mask — IsActiveFlag / IsEnabledIT.
        var rtFlag = Regex.Match(
            body,
            @"READ_BIT(?!_SHIFT)\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^,]+?)\s*,\s*(?<param>Flag|Interrupt|Mask)\s*\)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        if (rtFlag.Success
            && TryResolveRuntimeMaskParam(
                fn.FilePath, fn.FunctionName, rtFlag.Groups["param"].Value,
                out var rtMacro, out var rtBits, out var rtChip)
            && rtBits != 0)
        {
            _ = TryParseRegAccessPath(rtFlag.Groups["path"].Value.Trim(), out var rtPath);
            var mem = string.IsNullOrEmpty(rtPath.LeafMember)
                ? rtFlag.Groups["path"].Value.Trim()
                : rtPath.LeafMember;
            var nest = rtChip ?? rtMacro;
            var targetInstance = ResolveNestedInstance(instance, rtPath, 0, nest);
            var isBool = body.Contains("? 1UL", StringComparison.Ordinal)
                         || body.Contains("?1UL", StringComparison.Ordinal)
                         || body.Contains("!= 0", StringComparison.Ordinal)
                         || body.Contains("!=0", StringComparison.Ordinal);
            var expected = isBool ? 1u : rtBits;
            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            AssignRuntimeMaskParam(parameters, rtFlag.Groups["param"].Value, rtBits, rtMacro);
            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters, mem, initial: rtBits, expectedReturn: expected,
                nameSuffix: $"{mem}.{StripMaskSuffix(rtMacro)}/flag/read-check",
                detail:
                $"运行时 {rtFlag.Groups["param"].Value}→{rtMacro}=0x{rtBits:X} Expected=0x{expected:X}",
                notes: "读校验：运行时 Flag/Interrupt 掩码。虚拟环境。"));
            return results;
        }

        // READ_BIT(..._Msk|_MSK): boolean (? 1UL) OR masked-return (reg & mask), e.g.
        // LL_HRPWM_Mst_AllIntPnd_Get → READ_BIT(Master.MISR, LL_HRPWM_MISR_MST_IT_FLAG_MSK).
        var bitMaskRead = ReadBitMaskPattern.Match(body);
        if (bitMaskRead.Success)
        {
            _ = TryParseRegAccessPath(bitMaskRead.Groups["path"].Value.Trim(), out var bitPath);
            var bodyMember = string.IsNullOrEmpty(bitPath.LeafMember)
                ? bitMaskRead.Groups["path"].Value.Trim()
                : bitPath.LeafMember;
            var bodyMskMacro = bitMaskRead.Groups["msk"].Value;
            var member = ResolveMemberAlignedToMask(bodyMember, bodyMskMacro, out _, out var bitPairNote);
            // Nested Master + LL_HRPWM_*_MSK: peri prefix may not parse; pass expanded chip token.
            var nestMsk = bodyMskMacro;
            if (bodyMskMacro.StartsWith("LL_", StringComparison.OrdinalIgnoreCase))
            {
                var expanded = ExpandDefineBody(fn.FilePath, bodyMskMacro) ?? "";
                var chipTok = ChipFieldMskToken.Match(expanded);
                if (chipTok.Success)
                    nestMsk = chipTok.Groups["tok"].Value;
            }

            var targetInstance = ResolveNestedInstance(instance, bitPath, 0, nestMsk);
            var mask = await ResolveClearMaskAsync(db, fn, member, bodyMskMacro, ct);
            if (mask == 0
                && !TryParseUintDefineFromFileCandidates(fn.FilePath, bodyMskMacro, out mask))
                return results;
            if (mask == 0)
                return results;

            var label = TryFieldNameFromMskMacro(bodyMskMacro, member, out var fnField)
                        || TryParseChipMaskRegAndField(bodyMskMacro, out _, out fnField)
                ? fnField
                : StripMaskSuffix(bodyMskMacro);

            var isBool = body.Contains("? 1UL", StringComparison.Ordinal)
                         || body.Contains("?1UL", StringComparison.Ordinal)
                         || Regex.IsMatch(body, @"!!\s*READ_BIT")
                         // (READ_BIT(reg, Msk) == Msk) cast to uint — PLL0_IsEnabled.
                         || Regex.IsMatch(
                             body,
                             $@"READ_BIT\s*\([\s\S]{{0,160}}{Regex.Escape(bodyMskMacro)}\s*\)\s*==\s*{Regex.Escape(bodyMskMacro)}",
                             RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

            if (isBool)
            {
                // !!READ_BIT is double-negation (still positive); only single ! inverts.
                var invert = Regex.IsMatch(
                    body,
                    @"(?<!\!)!\s*\(?\s*READ_BIT",
                    RegexOptions.CultureInvariant);
                // One representative: write the condition that makes Get return 1.
                var setFlag = !invert;
                var initial = setFlag ? mask : 0u;
                var expected = 1u;
                results.Add(BuildReadCheckModel(
                    fn, targetInstance,
                    PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                    member, initial, expected,
                    nameSuffix: $"{member}.{label}/seed/read-check",
                    detail:
                    $"布尔读：先写 0x{initial:X} Mask=0x{mask:X} 再读 Expected=0x{expected:X}（{bitPairNote}）",
                    notes:
                    $"读校验：先写寄存器 0x{initial:X}，再调用 Get 校验返回 0x{expected:X}。虚拟环境。"));

                return results;
            }

            // Masked return: READ_BIT → (reg & mask). One seed = full mask bits.
            {
                var initial = mask;
                var expected = initial & mask;
                results.Add(BuildReadCheckModel(
                    fn, targetInstance,
                    PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                    member, initial, expected,
                    nameSuffix: $"{member}.{label}/seed/read-check",
                    detail:
                    $"掩码读：先写 0x{initial:X} Mask=0x{mask:X} ExpectedReturn=(initial&mask)=0x{expected:X}；" +
                    $"path={bitPath.RawPath}；体宏 {bodyMskMacro}；{bitPairNote}",
                    notes:
                    $"读校验：先写寄存器 0x{initial:X}，再调用 Get 校验返回 0x{expected:X}。虚拟环境。"));
            }

            return results;
        }

        // READ_REG(CANx->RBUFDT[((Num)%N)]) before flat ReadRegPattern (nested casts).
        var readBareArr = ReadRegBareArrayPattern.Match(body);
        if (readBareArr.Success
            && !body.Contains("LL_ADC_REG_OFFSET", StringComparison.Ordinal))
        {
            var member = readBareArr.Groups["arr"].Value;
            var idxExpr = readBareArr.Groups["idx"].Value;
            const uint channelRaw = 0;
            const uint preload = 0x1u;
            var parameters = PrepareReadParameters(fn, instance, instance, CloneParams());
            AssignRegOffsetChannelParam(parameters, idxExpr, channelRaw);
            results.Add(BuildReadCheckModel(
                fn, instance, parameters, member, preload, preload,
                nameSuffix: $"{member}/ch0/seed/read-check",
                detail: $"READ_REG {member}[Num=0]：先写 0x{preload:X} 再读 Expected=0x{preload:X}",
                notes: $"读校验：数组寄存器 {member}[0]。虚拟环境。"));
            return results;
        }

        // (READ_REG(reg) & lit) == 0 / == lit — RCU IsForceResetAll / IsReleaseResetAll.
        var andCmp = Regex.Match(
            body,
            @"\(\s*READ_REG\s*\(\s*\(?\s*[A-Za-z0-9_]+\s*\)?\s*->\s*(?<path>[^)]+?)\s*\)\s*&\s*(?<lit>0x[0-9A-Fa-f]+(?:UL|U)?|\d+(?:UL|U)?)\s*\)\s*==\s*(?<rhs>0x[0-9A-Fa-f]+(?:UL|U)?|\d+(?:UL|U)?)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        if (andCmp.Success
            && TryParseHexOrDecToken(andCmp.Groups["lit"].Value, out var andLit)
            && andLit != 0
            && TryParseHexOrDecToken(andCmp.Groups["rhs"].Value, out var andRhs))
        {
            _ = TryParseRegAccessPath(andCmp.Groups["path"].Value.Trim(), out var andPath);
            var mem = string.IsNullOrEmpty(andPath.LeafMember)
                ? andCmp.Groups["path"].Value.Trim()
                : andPath.LeafMember;
            var targetInstance = ResolveNestedInstance(instance, andPath, 0, null);
            // ==0 → ready when clear; ==lit → ready when all bits set.
            var wantClear = andRhs == 0;
            var initial = wantClear ? 0u : andLit;
            const uint expected = 1u;
            results.Add(BuildReadCheckModel(
                fn, targetInstance,
                PrepareReadParameters(fn, instance, targetInstance, CloneParams()),
                mem, initial, expected,
                nameSuffix: $"{mem}/and-cmp-{(wantClear ? "eq0" : "eqmask")}/read-check",
                detail:
                $"(READ_REG&0x{andLit:X})==0x{andRhs:X} → Initial=0x{initial:X} Expected=1",
                notes: wantClear
                    ? "读校验：掩码位全清时返回 1。虚拟环境。"
                    : "读校验：掩码位全置时返回 1。虚拟环境。"));
            return results;
        }

        // Full register READ_REG — optionally masked with &_Val (GetPrescaler: READ_REG(PSCR)&PSC_Val).
        // Skip REG_OFFSET forms (handled above); do not use bare "OFFSET" — that false-hit
        // LL_HRPWM_PWMx_NUMS-style tokens historically.
        var readReg = ReadRegPattern.Match(body);
        if (readReg.Success
            && !body.Contains("LL_ADC_REG_OFFSET", StringComparison.Ordinal)
            && !body.Contains("REG_OFFSET", StringComparison.Ordinal))
        {
            _ = TryParseRegAccessPath(readReg.Groups["path"].Value.Trim(), out var regPath);
            var bodyMember = string.IsNullOrEmpty(regPath.LeafMember)
                ? readReg.Groups["path"].Value.Trim()
                : regPath.LeafMember;
            // Body leaf (CMPAR/CAPAR/…) already authoritative — skip full-table trusted scan.
            var member = bodyMember;
            if (string.IsNullOrWhiteSpace(bodyMember)
                || bodyMember.Contains('[', StringComparison.Ordinal)
                || bodyMember.Contains('.', StringComparison.Ordinal)
                || !Regex.IsMatch(bodyMember, @"^[A-Za-z_][A-Za-z0-9_]*$"))
            {
                var trustedMember = await TryResolveTrustedMemberAsync(db, fn, ct);
                if (!string.IsNullOrWhiteSpace(trustedMember))
                    member = trustedMember!;
            }

            const uint channelRaw = 0;
            var targetInstance = ResolveNestedInstance(instance, regPath, channelRaw, null);
            uint preload = 0x1u;
            uint expected = preload;
            // Gate + bounded path: nested PWM[(Pwmx)%N] makes
            // (?:[^()]+|\([^()]*\))+ catastrophically backtrack when `&_Val` is absent.
            if (body.Contains("_Val", StringComparison.Ordinal) && body.Contains('&'))
            {
                var valTok = Regex.Match(
                    body,
                    @"READ_REG\s*\([^;&]{0,240}?\)\s*&\s*(?<val>[A-Za-z0-9_]+_Val)\b",
                    RegexOptions.CultureInvariant);
                if (valTok.Success
                    && TryParseUintDefineFromFileCandidates(fn.FilePath, valTok.Groups["val"].Value, out var clamp)
                    && clamp != 0)
                {
                    preload = clamp == 0xFFFFFFFFu ? 0xA5A55A5Au : (clamp & 0xA5A55A5Au) != 0
                        ? clamp & 0xA5A55A5Au
                        : clamp;
                    if (preload == 0) preload = LowestSetBit(clamp);
                    expected = preload & clamp;
                }
            }

            var parameters = PrepareReadParameters(fn, instance, targetInstance, CloneParams());
            if (regPath.ArrayIndexExpr is not null)
                AssignRegOffsetChannelParam(parameters, regPath.ArrayIndexExpr, channelRaw);

            results.Add(BuildReadCheckModel(
                fn, targetInstance, parameters,
                member, preload, expected,
                nameSuffix: $"{member}/seed/read-check",
                detail: $"READ_REG：先写 0x{preload:X} 再读 Expected=0x{expected:X}（体成员 {bodyMember}；inst={targetInstance}）",
                notes: $"读校验：先写寄存器 0x{preload:X}，再调用 Get 校验返回 0x{expected:X}。虚拟环境。"));
        }

        return results;
    }

    private static List<LlTestParameterValue> PrepareReadParameters(
        LlFunction fn, string fallbackInstance, string targetInstance, List<LlTestParameterValue> parameters)
    {
        foreach (var p in parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
        {
            p.ValueExpression = ResolveHostPeriPointer(
                fn.PeripheralName, fallbackInstance, targetInstance, p.ValueExpression);
        }

        return parameters;
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
        model.Notes = string.IsNullOrWhiteSpace(notes)
            ? $"读校验：先写寄存器 0x{initial:X}，再调用 Get 校验返回 0x{expectedReturn:X}。"
            : notes;
        return model;
    }

    /// <summary>expected = (initial &amp; mask) &gt;&gt; pos</summary>
    private static uint DeriveFieldReadExpected(uint initial, uint mask, int pos)
        => pos is >= 0 and < 32 ? (initial & mask) >> pos : initial & mask;

    /// <summary>
    /// (READ_BIT_SHIFT(...) == LL_EFLASH_BOOT_LOCK_CFG_LOCK) ? 1UL : 0UL style.
    /// </summary>
    private static bool TryMatchFieldCompareConstant(string body, string? filePath, out uint literal)
    {
        literal = 0;
        var m = Regex.Match(
            body,
            @"READ_BIT(?:_SHIFT)?\s*\([^;]+?\)\s*==\s*(?<lit>[A-Za-z0-9_]+)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        if (!m.Success) return false;
        var tok = m.Groups["lit"].Value;
        if (tok.Equals("0", StringComparison.Ordinal) || tok.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
        {
            literal = TestHarnessGenerator.ParseUIntExpression(tok);
            return true;
        }

        return TryParseUintDefineFromFileCandidates(filePath, tok, out literal);
    }

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
        // One representative field value from the LL mask width — write that value then Get.
        var sample = maxVal == 0 ? 0u : (maxVal > 1 ? maxVal / 2u : 1u);
        if (sample == 0 && maxVal >= 1)
            sample = 1u;
        yield return ("seed", sample, false);
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
            var familyId = Core.Sdk.SdkSeriesLayout.TryFamilyIdFromLlHeader(Path.GetFileName(ll));
            Core.Sdk.SdkSeriesLayout? layout = null;
            var dir = new DirectoryInfo(Path.GetDirectoryName(ll)!);
            for (var i = 0; i < 8 && dir is not null; i++, dir = dir.Parent)
            {
                layout = Core.Sdk.SdkSeriesLayout.Discover(dir.FullName);
                if (layout?.ChipHeaderPath is not null || layout?.DeviceHeaderPath is not null)
                    break;
            }

            familyId ??= layout?.FamilyId;
            if (layout?.ChipHeaderPath is not null && seen.Add(Path.GetFullPath(layout.ChipHeaderPath)))
                yield return Path.GetFullPath(layout.ChipHeaderPath);
            if (layout?.DeviceHeaderPath is not null && seen.Add(Path.GetFullPath(layout.DeviceHeaderPath)))
                yield return Path.GetFullPath(layout.DeviceHeaderPath);

            if (string.IsNullOrWhiteSpace(familyId))
                yield break;

            var headerNames = new[] { familyId + "_chip.h", familyId + "_chip_struct.h", familyId + ".h" };
            foreach (var full in CollectSeriesChipHeaderPaths(Path.GetDirectoryName(ll)!, headerNames))
            {
                if (seen.Add(full))
                    yield return full;
            }
        }
    }

    private static List<string> CollectSeriesChipHeaderPaths(string llDir, IReadOnlyList<string> headerNames)
    {
        var found = new List<string>();
        var dir = new DirectoryInfo(llDir);
        for (var i = 0; i < 6 && dir is not null; i++, dir = dir.Parent)
        {
            foreach (var name in headerNames)
            {
                foreach (var p in new[]
                         {
                             Path.Combine(dir.FullName, name),
                             Path.Combine(dir.FullName, "Inc", name)
                         })
                {
                    if (File.Exists(p))
                        found.Add(Path.GetFullPath(p));
                }
            }

            try
            {
                var drivers = Path.Combine(dir.FullName, "Drivers");
                var sdkDrivers = Path.Combine(dir.FullName, "SDK", "Drivers");
                foreach (var driversRoot in new[] { drivers, sdkDrivers }.Where(Directory.Exists))
                {
                    foreach (var deviceInc in Directory.EnumerateDirectories(driversRoot, "*_Device", SearchOption.TopDirectoryOnly)
                                 .Select(d => Path.Combine(d, "Inc"))
                                 .Where(Directory.Exists)
                                 .Take(6))
                    {
                        foreach (var name in headerNames)
                        {
                            var p = Path.Combine(deviceInc, name);
                            if (File.Exists(p))
                                found.Add(Path.GetFullPath(p));
                        }
                    }
                }
            }
            catch
            {
                // ignore inaccessible trees
            }
        }

        return found;
    }

    private static readonly System.Collections.Concurrent.ConcurrentDictionary<string, string> DefineFileTextCache =
        new(StringComparer.OrdinalIgnoreCase);

    private static string? TryReadCachedFileText(string filePath)
    {
        try
        {
            var full = Path.GetFullPath(filePath);
            return DefineFileTextCache.GetOrAdd(full, static p => File.ReadAllText(p));
        }
        catch
        {
            return null;
        }
    }

    /// <summary>
    /// Extract #define body for one macro only (line + optional \ continuations).
    /// Index scan — never Multiline <c>.*</c> on multi-MB chip headers (that hung HRPWM gen).
    /// </summary>
    private static bool TryExtractDefineBody(string text, string macroName, out string body)
    {
        body = "";
        if (string.IsNullOrWhiteSpace(text) || string.IsNullOrWhiteSpace(macroName))
            return false;

        const string token = "#define";
        var idx = 0;
        while (idx < text.Length)
        {
            idx = text.IndexOf(token, idx, StringComparison.Ordinal);
            if (idx < 0) return false;
            // Must be line-start (or only whitespace before on the line).
            var lineStart = text.LastIndexOf('\n', idx) + 1;
            var prefix = text.AsSpan(lineStart, idx - lineStart);
            if (!prefix.IsEmpty && !prefix.Trim().IsEmpty)
            {
                idx += token.Length;
                continue;
            }

            var nameStart = idx + token.Length;
            while (nameStart < text.Length
                   && (text[nameStart] == ' ' || text[nameStart] == '\t'))
                nameStart++;
            if (nameStart + macroName.Length > text.Length
                || !text.AsSpan(nameStart, macroName.Length).Equals(macroName, StringComparison.Ordinal))
            {
                idx = nameStart;
                continue;
            }

            var afterName = nameStart + macroName.Length;
            if (afterName < text.Length
                && (char.IsLetterOrDigit(text[afterName]) || text[afterName] == '_'))
            {
                idx = afterName;
                continue;
            }

            var i = afterName;
            while (i < text.Length && (text[i] == ' ' || text[i] == '\t'))
                i++;
            var sb = new System.Text.StringBuilder();
            while (i < text.Length)
            {
                var lineEnd = text.IndexOf('\n', i);
                if (lineEnd < 0) lineEnd = text.Length;
                var line = text.AsSpan(i, lineEnd - i).TrimEnd('\r');
                var cont = line.Length > 0 && line[^1] == '\\';
                if (cont)
                    line = line[..^1];
                if (sb.Length > 0) sb.Append(' ');
                sb.Append(line.Trim());
                if (!cont) break;
                i = lineEnd + 1;
            }

            body = sb.ToString();
            return body.Length > 0;
        }

        return false;
    }

    private static bool TryParseUintDefineFromFile(string filePath, string macroName, out uint value)
    {
        value = 0;
        try
        {
            var text = TryReadCachedFileText(filePath);
            if (text is null || !TryExtractDefineBody(text, macroName, out var body))
                return false;
            // LL_RCU_PLL0CR_VCO_DET (BIT(17)) — must not grab the digit 17 as the value.
            var bit = Regex.Match(
                body, @"BIT\s*\(\s*(?<b>\d+)\s*\)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            if (bit.Success
                && int.TryParse(bit.Groups["b"].Value, out var bitPos)
                && bitPos is >= 0 and < 32)
            {
                value = 1u << bitPos;
                return true;
            }

            // Reject OR-composites / chip-token aliases: bare \d+ would grab TMR9→9 / CC3→3.
            if (body.Contains('|', StringComparison.Ordinal)
                || (Regex.IsMatch(body, @"\b[A-Za-z0-9_]+_Msk\b", RegexOptions.IgnoreCase)
                    && !Regex.IsMatch(body, @"0x[0-9A-Fa-f]+", RegexOptions.IgnoreCase)))
                return false;

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
            _ = TryParseRegAccessPath(shift.Groups["path"].Value.Trim(), out var getPath);
            var bodyMember = string.IsNullOrEmpty(getPath.LeafMember)
                ? shift.Groups["path"].Value.Trim()
                : getPath.LeafMember;
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
            _ = TryParseRegAccessPath(rr.Groups["path"].Value.Trim(), out var rrPath);
            var member = string.IsNullOrEmpty(rrPath.LeafMember)
                ? rr.Groups["path"].Value.Trim()
                : rrPath.LeafMember;
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
           || name.Contains("Receive", StringComparison.OrdinalIgnoreCase)
           || name.Contains("Extract", StringComparison.OrdinalIgnoreCase)
           || name.Contains("Retrieve", StringComparison.OrdinalIgnoreCase)
           // LL_*_IsEnabled… and camelCase MasterTxRxIsStarted
           || Regex.IsMatch(name, @"_Is[A-Z]")
           || Regex.IsMatch(name, @"[a-z]Is[A-Z]");

    /// <summary>
    /// Locate the inline definition of <paramref name="functionName"/>, skipping comment
    /// references such as <c>See LL_I2C_SetRxSCLStretchMode()</c> that IndexOf would hit first.
    /// </summary>
    private static int IndexOfInlineFunctionDefinition(string text, string functionName)
    {
        if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(functionName))
            return -1;

        // Prefer __STATIC_INLINE … FunctionName(
        var def = Regex.Match(
            text,
            $@"__STATIC_INLINE\b[\s\S]{{0,160}}?\b{Regex.Escape(functionName)}\s*\(",
            RegexOptions.CultureInvariant);
        if (def.Success)
        {
            var nameAt = text.IndexOf(
                functionName + "(", def.Index, StringComparison.Ordinal);
            if (nameAt >= 0) return nameAt;
        }

        // Fallback: first name( not inside a block comment.
        var needle = functionName + "(";
        var idx = 0;
        while ((idx = text.IndexOf(needle, idx, StringComparison.Ordinal)) >= 0)
        {
            var commentOpen = text.LastIndexOf("/*", idx, StringComparison.Ordinal);
            var commentClose = text.LastIndexOf("*/", idx, StringComparison.Ordinal);
            var inBlockComment = commentOpen >= 0 && commentOpen > commentClose;
            if (!inBlockComment)
                return idx;
            idx += needle.Length;
        }

        return -1;
    }

    private static string? TryReadFunctionBodyFromSource(string? filePath, string functionName)
    {
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return null;
            var text = File.ReadAllText(resolved);
            var fnIdx = IndexOfInlineFunctionDefinition(text, functionName);
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

    private static bool TryParseHexOrDecToken(string? token, out uint value)
    {
        value = 0;
        if (string.IsNullOrWhiteSpace(token)) return false;
        var t = token.Trim();
        if (t.EndsWith("ULL", StringComparison.OrdinalIgnoreCase))
            t = t[..^3];
        else if (t.EndsWith("UL", StringComparison.OrdinalIgnoreCase))
            t = t[..^2];
        else if (t.EndsWith("U", StringComparison.OrdinalIgnoreCase)
                 && !t.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            t = t[..^1];
        if (t.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            return uint.TryParse(
                t[2..], System.Globalization.NumberStyles.HexNumber, null, out value);
        return uint.TryParse(t, out value);
    }

    private static async Task<uint> ResolveClearMaskAsync(
        AppDbContext db, LlFunction fn, string member, string mskMacro, CancellationToken ct)
    {
        // LL_*_MSK / LL_*_Msk are usually OR-composites (IER_IT_EN = OVIE|UIE).
        // Never treat the trailing token (IT_EN / IT_FLAG) as a single DB field — that
        // falsely yielded masks like 0x7 while hardware bits are 0x100|0x200=0x300.
        var isLlAlias = mskMacro.StartsWith("LL_", StringComparison.OrdinalIgnoreCase)
                        && (mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase)
                            || mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase));

        if (!isLlAlias && TryFieldNameFromMskMacro(mskMacro, member, out var fieldName))
        {
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fieldName, ct);
            if (field?.Mask is uint m && m != 0)
                return m;
        }

        // Chip/header literal: HRPWM_MST_MCR1_BDMADIS_Msk (0x80000000UL) — required when DB
        // has no RegisterFields yet (nested Master.MCR1 banks often missing from scan).
        // Skip literal parse for LL_* aliases: body is (A_Msk|B_Msk) without a hex constant.
        if (!isLlAlias)
        {
            foreach (var path in CandidateDefineFiles(fn.FilePath, null))
            {
                if (TryParseUintDefineFromFile(path, mskMacro, out var lit) && lit != 0)
                    return lit;
            }
        }

        // Composite LL mask: expand #define and OR chip *_Msk tokens.
        var expanded = ExpandDefineBody(fn.FilePath, mskMacro);
        if (string.IsNullOrWhiteSpace(expanded))
            return 0;

        // LL_RCU_PLL0CR_VCO_DET (BIT(17)) — single-bit alias without *_Msk token.
        var bitLit = Regex.Match(
            expanded,
            @"BIT\s*\(\s*(?<b>\d+)\s*\)",
            RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
        if (bitLit.Success
            && int.TryParse(bitLit.Groups["b"].Value, out var bitPos)
            && bitPos is >= 0 and < 32)
            return 1u << bitPos;

        uint combined = 0;
        foreach (Match tok in ChipFieldMskToken.Matches(expanded))
        {
            var chipMsk = tok.Groups["tok"].Value;
            if (TryParseUintDefineFromFileCandidates(fn.FilePath, chipMsk, out var chipLit) && chipLit != 0)
            {
                combined |= chipLit;
                continue;
            }

            if (!TryFieldNameFromMskMacro(chipMsk, member, out var fnName))
                continue;
            var field = await FindRegisterFieldAsync(db, fn.SdkProjectId, member, fnName, ct);
            if (field?.Mask is uint m)
                combined |= m;
        }

        return combined;
    }

    private static bool TryParseUintDefineFromFileCandidates(string? llFilePath, string macroName, out uint value)
    {
        value = 0;
        foreach (var path in CandidateDefineFiles(llFilePath, null))
        {
            if (TryParseUintDefineFromFile(path, macroName, out value) && value != 0)
                return true;
        }

        return false;
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
            var fnIdx = IndexOfInlineFunctionDefinition(text, functionName);
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
            var text = TryReadCachedFileText(resolved);
            if (text is null || !TryExtractDefineBody(text, macroName, out var body))
                return null;
            // Also search chip headers for LL composite masks defined outside the LL file.
            if (string.IsNullOrWhiteSpace(body))
                return null;
            return body.Replace("\\", "", StringComparison.Ordinal);
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
           || functionName.Contains("Stop", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Clear", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Clr", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Reset", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Insert", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Generate", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Acknowledge", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Transmit", StringComparison.OrdinalIgnoreCase)
           || functionName.Contains("Handle", StringComparison.OrdinalIgnoreCase);

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
        => TryParseChipMaskRegAndField(mskMacro, preferRegMember: null, out regMember, out fieldName);

    /// <summary>
    /// Parse <c>PERI_REG_FIELD[_FIELD…]_Msk</c>.
    /// Multi-token fields (e.g. <c>CAN0_CTRL_FD_EN_Msk</c>, <c>ADC0_CDR_RDATA_MST_Msk</c>)
    /// must not be split as REG=FD/RDATA — pass <paramref name="preferRegMember"/> from the LL body
    /// (<c>->CTRL</c>/<c>->CDR</c>) when known.
    /// </summary>
    private static bool TryParseChipMaskRegAndField(
        string mskMacro,
        string? preferRegMember,
        out string regMember,
        out string fieldName)
    {
        regMember = "";
        fieldName = "";
        if (string.IsNullOrWhiteSpace(mskMacro)) return false;
        if (!mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
            && !mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return false;

        var core = mskMacro[..^4];
        if (!string.IsNullOrWhiteSpace(preferRegMember))
        {
            var aligned = Regex.Match(
                core,
                $@"^(?<peri>.+?)_{Regex.Escape(preferRegMember!)}_(?<field>.+)$",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
            if (aligned.Success
                && aligned.Groups["field"].Value.Length > 0
                && Regex.IsMatch(aligned.Groups["field"].Value, @"^[A-Za-z][A-Za-z0-9_]*$"))
            {
                regMember = preferRegMember!;
                fieldName = aligned.Groups["field"].Value;
                return true;
            }
        }

        var parts = core.Split('_', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length < 3) return false;
        // LL_EFLASH_SR_ERROR_IT_FLAG_MSK → strip LL_ and parse as EFLASH_SR_ERROR_IT_FLAG.
        if (parts[0].Equals("LL", StringComparison.OrdinalIgnoreCase) && parts.Length >= 4)
        {
            var stripped = string.Join('_', parts.Skip(1)) +
                           (mskMacro.EndsWith("_MSK", StringComparison.Ordinal) ? "_MSK" : "_Msk");
            return TryParseChipMaskRegAndField(stripped, preferRegMember, out regMember, out fieldName);
        }

        // Try multi-token fields first: CAN0_CTRL_FD_EN → CTRL + FD_EN (not FD + EN).
        for (var fieldLen = Math.Min(3, parts.Length - 2); fieldLen >= 1; fieldLen--)
        {
            var field = string.Join("_", parts.Skip(parts.Length - fieldLen));
            var reg = parts[^(fieldLen + 1)];
            var periLen = parts.Length - fieldLen - 1;
            if (periLen <= 0) continue;
            if (!Regex.IsMatch(reg, @"^[A-Za-z][A-Za-z0-9]*$")) continue;
            if (!Regex.IsMatch(field, @"^[A-Za-z][A-Za-z0-9_]*$")) continue;

            var peri = string.Join("_", parts.Take(periLen));
            var periLooksLikeInstance =
                Regex.IsMatch(peri, @"\d$")
                || peri.Contains("_MST", StringComparison.OrdinalIgnoreCase)
                || peri.Contains("_SLV", StringComparison.OrdinalIgnoreCase)
                || peri.Contains("_COM", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("RCU", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("SYSCTRL", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("FLASH", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("EFLASH", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("WWDG", StringComparison.OrdinalIgnoreCase)
                || peri.Equals("IWDG", StringComparison.OrdinalIgnoreCase);

            if (fieldLen > 1 && periLooksLikeInstance)
            {
                regMember = reg;
                fieldName = field;
                return true;
            }

            if (fieldLen == 1 && (periLooksLikeInstance || parts.Length == 3))
            {
                regMember = reg;
                fieldName = field;
                return true;
            }
        }

        fieldName = parts[^1];
        regMember = parts[^2];
        if (fieldName.Length == 0 || regMember.Length == 0) return false;
        if (!Regex.IsMatch(fieldName, @"^[A-Za-z][A-Za-z0-9]*$")) return false;
        if (!Regex.IsMatch(regMember, @"^[A-Za-z][A-Za-z0-9]*$")) return false;
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

        // Bare bank: TBUFDT[((Num)%N)] / RBUFDT[i] — leaf is the array member itself.
        var bareArr = Regex.Match(p,
            @"^(?<arr>[A-Za-z_][A-Za-z0-9_]*)\s*\[\s*(?<idx>.+?)\s*\]\s*$",
            RegexOptions.CultureInvariant | RegexOptions.Singleline);
        if (bareArr.Success)
        {
            parsed = new RegAccessPath(
                bareArr.Groups["arr"].Value,
                p,
                bareArr.Groups["idx"].Value.Trim(),
                null);
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

            // CAN TBUFDT: LL_CAN_TBUFDT_WORD_LAYER_LEVEL (not *_NUMS).
            var levelMacro = Regex.Match(indexExpr, @"\b(LL_[A-Za-z0-9_]+_(?:LEVEL|SIZE|LEN|LENGTH|COUNT|WORDS?))\b");
            if (levelMacro.Success && !string.IsNullOrWhiteSpace(sourceFile))
            {
                foreach (var path in CandidateDefineFiles(sourceFile, null))
                {
                    if (TryParseUintDefineFromFile(path, levelMacro.Groups[1].Value, out var n) && n > 0)
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
        => TryPeriPrefixFromMask(mskMacro, preferRegMember: null, out peri);

    private static bool TryPeriPrefixFromMask(string? mskMacro, string? preferRegMember, out string peri)
    {
        peri = "";
        if (string.IsNullOrWhiteSpace(mskMacro)) return false;
        if (!mskMacro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
            && !mskMacro.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return false;
        if (!TryParseChipMaskRegAndField(mskMacro, preferRegMember, out var reg, out var field))
            return false;
        var core = mskMacro[..^4];
        var suffix = $"_{reg}_{field}";
        if (core.Length > suffix.Length
            && core.EndsWith(suffix, StringComparison.OrdinalIgnoreCase))
        {
            peri = core[..^suffix.Length];
            return peri.Length > 0;
        }

        // Fallback: strip last two underscore tokens.
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
            // DMA CH[n]: chip models DMA0..DMA5 as instances — never invent DMA_CH0.
            if (path.NestedPrefix is not null
                && path.NestedPrefix.Equals("CH", StringComparison.OrdinalIgnoreCase))
            {
                if (!string.IsNullOrWhiteSpace(periFromMask)
                    && Regex.IsMatch(periFromMask, @"^DMA\d+$", RegexOptions.IgnoreCase))
                    return Regex.Replace(periFromMask, @"\d+$", channelIndex.ToString());
                if (fallbackInstance.StartsWith("DMA", StringComparison.OrdinalIgnoreCase))
                    return $"DMA{channelIndex}";
            }

            // HRPWM PWM[n]: banked SLV instances.
            if (path.NestedPrefix is not null
                && path.NestedPrefix.Equals("PWM", StringComparison.OrdinalIgnoreCase)
                && (fallbackInstance.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase)
                    || (!string.IsNullOrWhiteSpace(periFromMask)
                        && periFromMask.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase))))
                return $"HRPWM_SLV{channelIndex}";

            if (!string.IsNullOrWhiteSpace(periFromMask))
            {
                var bank = Regex.Replace(periFromMask, @"\d+$", channelIndex.ToString());
                if (!bank.Equals(periFromMask, StringComparison.Ordinal)
                    || Regex.IsMatch(periFromMask, @"\d+$"))
                    return bank;
                return periFromMask + channelIndex;
            }

            if (Regex.IsMatch(fallbackInstance, @"\d+$"))
                return Regex.Replace(fallbackInstance, @"\d+$", channelIndex.ToString());
            // Avoid Module_CH0 fake instances for DMA-like trees.
            if (path.NestedPrefix is not null
                && path.NestedPrefix.Equals("CH", StringComparison.OrdinalIgnoreCase))
                return fallbackInstance.StartsWith("DMA", StringComparison.OrdinalIgnoreCase)
                    ? $"DMA{channelIndex}"
                    : fallbackInstance;
            return $"{fallbackInstance}_{path.NestedPrefix}{channelIndex}";
        }

        if (!string.IsNullOrWhiteSpace(path.NestedPrefix))
        {
            var pref = path.NestedPrefix!;
            // LL_* composite / REG-field tokens (LL_HRPWM_OENR_…) are not instances —
            // inventing LL_COM from root "LL" broke EnableOutput/DisableOutput.
            var maskPeriUsable = !string.IsNullOrWhiteSpace(periFromMask)
                                 && !periFromMask.StartsWith("LL_", StringComparison.OrdinalIgnoreCase)
                                 && IsLikelyPeripheralInstanceName(periFromMask);
            if (maskPeriUsable)
            {
                // Master / Common / shared block: swap bank token
                if (pref.Equals("Master", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("MST", StringComparison.OrdinalIgnoreCase))
                {
                    var mst = Regex.Replace(periFromMask!, @"_(SLV|CH|UNIT|TIM)\d+$", "_MST",
                        RegexOptions.IgnoreCase);
                    if (mst.Equals(periFromMask, StringComparison.OrdinalIgnoreCase)
                        && !periFromMask!.Contains("_MST", StringComparison.OrdinalIgnoreCase))
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
                    var com = Regex.Replace(periFromMask!, @"_(SLV|CH|UNIT|TIM|MST)\d*$", "_COM",
                        RegexOptions.IgnoreCase);
                    if (com.Equals(periFromMask, StringComparison.OrdinalIgnoreCase)
                        && !periFromMask!.Contains("_COM", StringComparison.OrdinalIgnoreCase))
                    {
                        var root = Regex.Match(periFromMask, @"^[A-Za-z]+");
                        com = root.Success ? $"{root.Value}_COM" : periFromMask;
                    }
                    return com;
                }

                // Other nested: use mask peri as-is (e.g. still SLV0 template)
                return periFromMask!;
            }

            // Master/Common bank remap is HRPWM-only (SDK has no other ->Master./->Common.).
            if (IsHrpwmBankFamily(fallbackInstance, periFromMask, mskMacro))
            {
                if (pref.Equals("Master", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("MST", StringComparison.OrdinalIgnoreCase))
                    return ToHrpwmBankedInstance(fallbackInstance, "_MST");
                if (pref.Equals("Common", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("COM", StringComparison.OrdinalIgnoreCase)
                    || pref.Equals("Shared", StringComparison.OrdinalIgnoreCase))
                    return ToHrpwmBankedInstance(fallbackInstance, "_COM");
            }
        }

        // Flat path: only adopt mask peri when it is a real instance (CAN0 / HRPWM_MST),
        // never PERI_REG composites from mis-split multi-token fields (CAN0_CTRL / ADC0_CDR).
        if (!string.IsNullOrWhiteSpace(periFromMask) && IsLikelyPeripheralInstanceName(periFromMask))
        {
            // Timer family: GPTMRX/Y/ADTMR share TMR* chip macros. Body may cite TMR9_* while
            // the LL call instance is TMR0 — keep fallback so seed/assert match the peri pointer.
            var fb = fallbackInstance ?? "";
            var fbFam = Regex.Replace(fb, @"\d+$", "");
            var maskFam = Regex.Replace(periFromMask, @"\d+$", "");
            if (fbFam.Equals("TMR", StringComparison.OrdinalIgnoreCase)
                && maskFam.Equals("TMR", StringComparison.OrdinalIgnoreCase)
                && fb.Length > 0
                && !fb.Equals(periFromMask, StringComparison.OrdinalIgnoreCase))
                return fb;

            return periFromMask;
        }

        return fallbackInstance;
    }

    private static bool IsHrpwmBankFamily(string? fallback, string? periFromMask, string? mskMacro)
        => (!string.IsNullOrWhiteSpace(fallback)
            && fallback.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase))
           || (!string.IsNullOrWhiteSpace(periFromMask)
               && periFromMask.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase))
           || (!string.IsNullOrWhiteSpace(mskMacro)
               && (mskMacro.StartsWith("HRPWM_", StringComparison.OrdinalIgnoreCase)
                   || mskMacro.StartsWith("LL_HRPWM_", StringComparison.OrdinalIgnoreCase)));

    private static uint LowestSetBit(uint mask)
    {
        if (mask == 0) return 0;
        return mask & ~(mask - 1u);
    }

    private static Match MatchPreferredSetClear(string text, string functionName)
    {
        var matches = SetClearBitPattern.Matches(text);
        if (matches.Count == 0)
            return SetClearBitPattern.Match(text);
        if (matches.Count == 1)
            return matches[0];

        var wantSet = functionName.Contains("Enable", StringComparison.OrdinalIgnoreCase)
                      && !functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase);
        var wantClear = functionName.Contains("Disable", StringComparison.OrdinalIgnoreCase)
                        || functionName.Contains("Reset", StringComparison.OrdinalIgnoreCase);
        foreach (Match m in matches)
        {
            var op = m.Groups["op"].Value;
            if (wantSet && op.Equals("SET_BIT", StringComparison.OrdinalIgnoreCase))
                return m;
            if (wantClear && op.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase))
                return m;
        }

        return matches[^1];
    }

    /// <summary>
    /// Prefer last WRITE_REG when several target the same path (Unlock KEY1→KEY2 sticky).
    /// </summary>
    private static Match MatchPreferredWriteReg(string text)
    {
        var matches = WriteRegPattern.Matches(text);
        if (matches.Count == 0)
            return WriteRegPattern.Match(text);
        if (matches.Count == 1)
            return matches[0];

        var last = matches[^1];
        var lastPath = last.Groups["path"].Value.Trim();
        var samePath = 0;
        foreach (Match m in matches)
        {
            if (string.Equals(
                    m.Groups["path"].Value.Trim(), lastPath, StringComparison.OrdinalIgnoreCase))
                samePath++;
        }

        return samePath >= 2 ? last : matches[0];
    }

    private static bool IsCompileTimeMaskToken(string? token)
        => !string.IsNullOrWhiteSpace(token)
           && (token.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
               || token.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase));

    private static void AssignRuntimeMaskParam(
        List<LlTestParameterValue> parameters,
        string maskParamName,
        uint maskBits,
        string llMacro)
    {
        var p = parameters.FirstOrDefault(x =>
            x.Name.Equals(maskParamName, StringComparison.OrdinalIgnoreCase));
        if (p is null) return;
        // Pure hex only — ParseUIntExpression rejects "0xN /* MACRO */" and would pass Mask=0.
        p.ValueExpression = $"0x{maskBits:X}";
        p.RuleSource = nameof(LlAssertionRuleSource.AutoGeneratedFromSdkMacro);
    }

    /// <summary>
    /// Resolve runtime Mask argument from doxygen <c>@ref LL_*TypeDef</c> to a concrete
    /// SDK #define in that @name group (never invent bits).
    /// </summary>
    /// <summary>
    /// Index-scan first single-bit <c>#define PREF*_Msk (0x…)</c>. Avoids Regex.Matches on
    /// multi-MB chip.h (that path hung / failed IsEnabledIT without @ref prose).
    /// </summary>
    private static bool TryFindFirstSingleBitMaskByPrefix(
        string? filePath, string prefix, out string macroName, out uint bits)
    {
        macroName = "";
        bits = 0;
        if (string.IsNullOrWhiteSpace(prefix)) return false;
        var needle = "#define " + prefix;
        // Prefer chip_struct / smaller headers before the multi-MB chip.h aggregate.
        foreach (var path in CandidateDefineFiles(filePath, null)
                     .OrderBy(p =>
                     {
                         var n = Path.GetFileName(p);
                         if (n.Contains("chip_struct", StringComparison.OrdinalIgnoreCase)) return 0;
                         if (n.Equals("tae32g58xx.h", StringComparison.OrdinalIgnoreCase)) return 1;
                         if (n.Contains("chip.h", StringComparison.OrdinalIgnoreCase)) return 3;
                         return 2;
                     }))
        {
            var hdr = TryReadCachedFileText(path);
            if (hdr is null) continue;
            var idx = 0;
            while ((idx = hdr.IndexOf(needle, idx, StringComparison.Ordinal)) >= 0)
            {
                var lineEnd = hdr.IndexOfAny(['\r', '\n'], idx);
                if (lineEnd < 0) lineEnd = hdr.Length;
                var line = hdr[idx..lineEnd];
                var m = Regex.Match(
                    line,
                    @"#define\s+(?<n>[A-Za-z0-9_]+_Msk)\s+\(?(?<hex>0x[0-9A-Fa-f]+)(?:UL|U)?\)?",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                idx = lineEnd + 1;
                if (!m.Success) continue;
                if (!uint.TryParse(
                        m.Groups["hex"].Value[2..],
                        System.Globalization.NumberStyles.HexNumber, null, out var b)
                    || b == 0
                    || BitWidthFromMask(b) != 1)
                    continue;
                macroName = m.Groups["n"].Value;
                bits = b;
                return true;
            }
        }

        return false;
    }

    private static bool TryResolveRuntimeMaskParam(
        string? filePath,
        string functionName,
        string maskParamName,
        out string llMacro,
        out uint bits,
        out string? chipMskToken)
    {
        llMacro = "";
        bits = 0;
        chipMskToken = null;
        try
        {
            var resolved = ResolveLlHeaderPath(filePath);
            if (resolved is null) return false;
            var text = File.ReadAllText(resolved);
            var fnIdx = IndexOfInlineFunctionDefinition(text, functionName);
            if (fnIdx < 0) return false;

            var commentStart = text.LastIndexOf("/**", fnIdx, StringComparison.Ordinal);
            if (commentStart < 0 || fnIdx - commentStart > 1600)
                return false;
            var comment = text[commentStart..fnIdx];
            var refMatch = Regex.Match(
                comment,
                $@"@param(?:\[[^\]]*\])?\s+{Regex.Escape(maskParamName)}\b[\s\S]*?@ref\s+(?<td>LL_[A-Za-z0-9_]+)",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

            // Prose without @ref: "I2C0_INTREN_xxx_Msk" / "I2C0_INTR_xxx_Msk" → first chip mask.
            if (!refMatch.Success)
            {
                var family = Regex.Match(
                    comment,
                    @"\b(?<fam>[A-Za-z0-9]+_(?:INTREN|INTR|INT|IER|ISR|MISR|SR)_)(?:[xX]{2,3}_Msk|\*)",
                    RegexOptions.CultureInvariant);
                string? pref = family.Success ? family.Groups["fam"].Value : null;
                if (pref is null)
                {
                    var body = TryReadFunctionBodyFromSource(filePath, functionName) ?? "";
                    // I2C / GPTMRX: digits are part of the peri token (LL_I2C_… → I2C, not I).
                    var peri = Regex.Match(functionName, @"^LL_([A-Za-z][A-Za-z0-9]*)").Groups[1].Value;
                    if (string.IsNullOrEmpty(peri)) peri = "I2C";
                    if (body.Contains("INTREN", StringComparison.OrdinalIgnoreCase))
                        pref = $"{peri}0_INTREN_";
                    else if (body.Contains("INTR", StringComparison.OrdinalIgnoreCase))
                        pref = $"{peri}0_INTR_";
                    else if (Regex.IsMatch(body, @"->\s*INT\b|\)\s*->\s*INT\b"))
                        pref = $"{peri}0_INT_";
                }

                // Sibling EnableIT doc often has I2C0_INTREN_xxx_Msk when IsEnabledIT omits it.
                if (string.IsNullOrEmpty(pref))
                {
                    var sibling = Regex.Replace(
                        functionName, @"_IsEnabledIT$", "_EnableIT", RegexOptions.IgnoreCase);
                    if (!sibling.Equals(functionName, StringComparison.Ordinal))
                    {
                        var sibIdx = IndexOfInlineFunctionDefinition(text, sibling);
                        if (sibIdx >= 0)
                        {
                            var sibCommentStart =
                                text.LastIndexOf("/**", sibIdx, StringComparison.Ordinal);
                            if (sibCommentStart >= 0 && sibIdx - sibCommentStart <= 1600)
                            {
                                var sibFam = Regex.Match(
                                    text[sibCommentStart..sibIdx],
                                    @"\b(?<fam>[A-Za-z0-9]+_(?:INTREN|INTR|IER|ISR|MISR|SR)_)[xX]{2,3}_Msk\b",
                                    RegexOptions.CultureInvariant);
                                if (sibFam.Success)
                                    pref = sibFam.Groups["fam"].Value;
                            }
                        }
                    }
                }

                if (!string.IsNullOrEmpty(pref)
                    && TryFindFirstSingleBitMaskByPrefix(filePath, pref, out llMacro, out bits))
                {
                    chipMskToken = llMacro;
                    return true;
                }

                return false;
            }

            var typeDef = refMatch.Groups["td"].Value;

            // Prefer first single-bit #define under /** @name TypeDef */
            var nameIdx = text.IndexOf($"@name {typeDef}", StringComparison.Ordinal);
            if (nameIdx >= 0)
            {
                var chunkLen = Math.Min(4000, text.Length - nameIdx);
                var chunk = text.Substring(nameIdx, chunkLen);
                var close = Regex.Match(chunk, @"/\*\*\s*@\}");
                if (close.Success)
                    chunk = chunk[..close.Index];

                foreach (Match dm in Regex.Matches(
                             chunk,
                             @"#define\s+(?<n>LL_[A-Za-z0-9_]+)\s+\((?<c>[A-Za-z0-9_]+_Msk)\)",
                             RegexOptions.CultureInvariant))
                {
                    var name = dm.Groups["n"].Value;
                    if (name.Equals(typeDef, StringComparison.OrdinalIgnoreCase))
                        continue;
                    if (TryParseUintDefineFromFileCandidates(filePath, name, out bits) && bits != 0)
                    {
                        llMacro = name;
                        chipMskToken = dm.Groups["c"].Value;
                        return true;
                    }

                    if (TryParseUintDefineFromFileCandidates(filePath, dm.Groups["c"].Value, out bits)
                        && bits != 0)
                    {
                        llMacro = name;
                        chipMskToken = dm.Groups["c"].Value;
                        return true;
                    }
                }

                // CMP EdgeIT etc.: #define LL_*_RISING (BIT(0)) / (0x1UL) — not chip *_Msk aliases.
                foreach (Match dm in Regex.Matches(
                             chunk,
                             @"#define\s+(?<n>LL_[A-Za-z0-9_]+)\s+\(\s*(?:BIT\s*\(\s*(?<bit>\d+)\s*\)|(?<hex>0x[0-9A-Fa-f]+)(?:UL|U)?|(?<dec>\d+)(?:UL|U)?)\s*\)",
                             RegexOptions.CultureInvariant | RegexOptions.IgnoreCase))
                {
                    var name = dm.Groups["n"].Value;
                    if (name.Equals(typeDef, StringComparison.OrdinalIgnoreCase))
                        continue;
                    if (name.StartsWith("IS_LL_", StringComparison.OrdinalIgnoreCase))
                        continue;
                    if (dm.Groups["bit"].Success
                        && int.TryParse(dm.Groups["bit"].Value, out var bit)
                        && bit is >= 0 and < 32)
                        bits = 1u << bit;
                    else if (dm.Groups["hex"].Success)
                        bits = TestHarnessGenerator.ParseUIntExpression(dm.Groups["hex"].Value);
                    else if (dm.Groups["dec"].Success)
                        bits = TestHarnessGenerator.ParseUIntExpression(dm.Groups["dec"].Value);
                    if (bits == 0) continue;
                    llMacro = name;
                    return true;
                }
            }

            // Fallback: LL_ADC_IER_ITEnMskTypeDef → LL_ADC_IER_IT_EN_MSK (and similar).
            string? aggregate = null;
            if (typeDef.EndsWith("ITEnMskTypeDef", StringComparison.OrdinalIgnoreCase))
                aggregate = typeDef[..^"ITEnMskTypeDef".Length] + "IT_EN_MSK";
            else if (typeDef.EndsWith("ITPendingMskTypeDef", StringComparison.OrdinalIgnoreCase))
                aggregate = typeDef[..^"ITPendingMskTypeDef".Length] + "IT_FLAG_MSK";
            else if (typeDef.EndsWith("DmaEnMskTypeDef", StringComparison.OrdinalIgnoreCase))
                aggregate = typeDef[..^"DmaEnMskTypeDef".Length] + "DMA_EN_MSK";

            if (aggregate is not null)
            {
                // Composite LL_*_IT_EN_MSK = (A_Msk | B_Msk | …) has no hex literal — OR chip tokens.
                var expanded = ExpandDefineBody(filePath, aggregate) ?? "";
                foreach (Match tok in ChipFieldMskToken.Matches(expanded))
                {
                    if (TryParseUintDefineFromFileCandidates(filePath, tok.Groups["tok"].Value, out var bit)
                        && bit != 0)
                    {
                        bits |= bit;
                        chipMskToken ??= tok.Groups["tok"].Value;
                    }
                }

                if (bits == 0)
                    _ = TryParseUintDefineFromFileCandidates(filePath, aggregate, out bits);

                if (bits != 0)
                {
                    llMacro = aggregate;
                    return true;
                }
            }

            // CMP: @ref LL_CMP_ISR_ITPendingMskTypeDef has no @name group — use ClearFlag_* chip Msk.
            if (typeDef.EndsWith("ITPendingMskTypeDef", StringComparison.OrdinalIgnoreCase))
            {
                var peri = typeDef.StartsWith("LL_", StringComparison.Ordinal)
                    ? typeDef[3..].Split('_')[0]
                    : "";
                var clearM = Regex.Match(
                    text,
                    $@"LL_{Regex.Escape(peri)}_ClearFlag_[A-Za-z0-9_]+\s*\([^)]*\)\s*\{{[\s\S]*?WRITE_REG\s*\([^,]+,\s*(?<m>[A-Za-z0-9_]+_Msk)\s*\)",
                    RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);
                if (clearM.Success
                    && TryParseUintDefineFromFileCandidates(filePath, clearM.Groups["m"].Value, out bits)
                    && bits != 0)
                {
                    llMacro = clearM.Groups["m"].Value;
                    chipMskToken = clearM.Groups["m"].Value;
                    return true;
                }
            }

            // UART-style: TypeDef is `#define …TypeDef uint32_t`; real masks are LL_*_IT_* / LL_*_FLAG_*.
            var periTok = Regex.Match(typeDef, @"^LL_([A-Za-z][A-Za-z0-9]*)_");
            if (periTok.Success)
            {
                var peri = periTok.Groups[1].Value;
                string? llPref = null;
                if (typeDef.Contains("ITEn", StringComparison.OrdinalIgnoreCase))
                    llPref = $"LL_{peri}_IT_";
                else if (typeDef.Contains("ITPending", StringComparison.OrdinalIgnoreCase))
                    llPref = $"LL_{peri}_FLAG_";

                if (llPref is not null
                    && TryFindFirstLlAliasMaskByPrefix(filePath, llPref, out llMacro, out bits, out chipMskToken)
                    && bits != 0)
                    return true;
            }
        }
        catch
        {
            /* ignore IO / parse */
        }

        return false;
    }

    /// <summary>
    /// First <c>#define LL_UART_IT_xxx (UART0_INTEN_xxx_Msk)</c> under prefix — not chip *_Msk name.
    /// </summary>
    private static bool TryFindFirstLlAliasMaskByPrefix(
        string? filePath,
        string prefix,
        out string macroName,
        out uint bits,
        out string? chipMskToken)
    {
        macroName = "";
        bits = 0;
        chipMskToken = null;
        if (string.IsNullOrWhiteSpace(prefix)) return false;
        var needle = "#define " + prefix;
        foreach (var path in CandidateDefineFiles(filePath, null))
        {
            var text = TryReadCachedFileText(path);
            if (text is null) continue;
            var idx = 0;
            while ((idx = text.IndexOf(needle, idx, StringComparison.Ordinal)) >= 0)
            {
                var lineEnd = text.IndexOf('\n', idx);
                if (lineEnd < 0) lineEnd = text.Length;
                var line = text[idx..lineEnd];
                var m = Regex.Match(
                    line,
                    @"#define\s+(?<n>LL_[A-Za-z0-9_]+)\s+\(\s*(?<c>[A-Za-z0-9_]+_Msk)\s*\)",
                    RegexOptions.CultureInvariant);
                idx = lineEnd;
                if (!m.Success) continue;
                if (!TryParseUintDefineFromFileCandidates(filePath, m.Groups["c"].Value, out bits)
                    || bits == 0
                    || BitWidthFromMask(bits) != 1)
                    continue;
                macroName = m.Groups["n"].Value;
                chipMskToken = m.Groups["c"].Value;
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// HRPWM → HRPWM_MST; HRPWM_SLV0/COM → HRPWM_MST; already HRPWM_MST → unchanged.
    /// </summary>
    private static string ToHrpwmBankedInstance(string fallbackInstance, string bankSuffix)
    {
        if (string.IsNullOrWhiteSpace(fallbackInstance))
            return "HRPWM" + bankSuffix;
        if (!fallbackInstance.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase))
            return fallbackInstance;
        if (fallbackInstance.EndsWith(bankSuffix, StringComparison.OrdinalIgnoreCase))
            return fallbackInstance;
        if (Regex.IsMatch(fallbackInstance, @"_(SLV|CH|COM|MST)\d*$", RegexOptions.IgnoreCase))
            return Regex.Replace(fallbackInstance, @"_(SLV|CH|COM|MST)\d*$", bankSuffix,
                RegexOptions.IgnoreCase);
        return fallbackInstance + bankSuffix;
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

        // Mask/nest may resolve TMR9 while draftParams still hold alphabetical TMR10 —
        // always align the peri pointer with the instance we seed/assert on.
        if (!string.IsNullOrWhiteSpace(targetInstance)
            && !IsHostAggregateInstance(targetInstance)
            && (string.IsNullOrWhiteSpace(current)
                || current.Equals("0", StringComparison.Ordinal)
                || IsHostAggregateInstance(current)
                || !current.Equals(targetInstance, StringComparison.OrdinalIgnoreCase)))
            return targetInstance;

        if (!string.IsNullOrWhiteSpace(current)
            && !current.Equals("0", StringComparison.Ordinal)
            && !IsHostAggregateInstance(current))
            return current;

        return string.IsNullOrWhiteSpace(fallbackInstance)
            ? (peripheralName ?? "PERI")
            : fallbackInstance;
    }

    /// <summary>
    /// Chip mask peri prefix must match the LL module family
    /// (reject UART0_* when generating ADTMR/TMR*, TMR*_DIR when generating UART, …).
    /// </summary>
    private static bool IsMaskPeriCompatible(string? mskMacro, string? peripheralName, string? functionName)
    {
        if (string.IsNullOrWhiteSpace(mskMacro))
            return true;
        // Composite LL_*_MSK aliases are module-scoped; keep them.
        if (mskMacro.StartsWith("LL_", StringComparison.OrdinalIgnoreCase))
            return true;
        if (!TryPeriPrefixFromMask(mskMacro, out var peri))
            return true;

        var periFam = Regex.Replace(peri, @"\d+$", "");
        if (!string.IsNullOrWhiteSpace(peripheralName)
            && peri.StartsWith(peripheralName, StringComparison.OrdinalIgnoreCase))
            return true;

        var expected = InferDefaultInstance(peripheralName, functionName ?? "");
        var expFam = Regex.Replace(expected, @"\d+$", "");
        if (string.Equals(periFam, expFam, StringComparison.OrdinalIgnoreCase))
            return true;

        // Timer modules share TMR* chip prefixes.
        if (expFam.Equals("TMR", StringComparison.OrdinalIgnoreCase)
            && periFam.Equals("TMR", StringComparison.OrdinalIgnoreCase))
            return true;

        return false;
    }

    /// <summary>
    /// Reject function-name trusted masks that target the wrong register role vs the LL body
    /// (EnableIT body IER must not bind SR_*IF; DisableBreak body DCR must not bind UGR_*G).
    /// </summary>
    private static bool IsTrustedMaskRoleCompatible(
        string? functionName,
        string bodyMember,
        string? bodyMskMacro,
        string? trustedLabel)
    {
        if (string.IsNullOrWhiteSpace(trustedLabel))
            return true;

        TryParseChipMaskRegAndField(trustedLabel, bodyMember, out var trustedReg, out var trustedField);
        TryParseChipMaskRegAndField(bodyMskMacro ?? "", bodyMember, out var bodyReg, out var bodyField);
        if (string.IsNullOrEmpty(trustedReg) && string.IsNullOrEmpty(bodyReg))
            return true;

        var fn = functionName ?? "";
        var isItEn =
            Regex.IsMatch(fn, @"(?:Enable|Disable|IsEnabled)IT", RegexOptions.IgnoreCase)
            || fn.Contains("IT_", StringComparison.OrdinalIgnoreCase)
               && (fn.Contains("Enable", StringComparison.OrdinalIgnoreCase)
                   || fn.Contains("Disable", StringComparison.OrdinalIgnoreCase));
        var isFlag =
            fn.Contains("ClearFlag", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("IsActiveFlag", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("GetFlag", StringComparison.OrdinalIgnoreCase);

        static bool IsStatusReg(string? r)
            => !string.IsNullOrEmpty(r)
               && (r.Equals("SR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("ISR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("DISR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("FISR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("HISR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("MISR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("IFR", StringComparison.OrdinalIgnoreCase));

        static bool IsEnableReg(string? r)
            => !string.IsNullOrEmpty(r)
               && (r.Equals("IER", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("DIER", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("FIER", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("HIER", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("CR", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("CR0", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("CR1", StringComparison.OrdinalIgnoreCase)
                   || r.Equals("DCR", StringComparison.OrdinalIgnoreCase));

        // EnableIT/DisableIT: refuse status-flag trusted masks when body writes IER/DIER/….
        if (isItEn && !isFlag)
        {
            if (IsStatusReg(trustedReg) && (IsEnableReg(bodyMember) || IsEnableReg(bodyReg)))
                return false;
            if (!string.IsNullOrEmpty(trustedField)
                && (trustedField.EndsWith("IF", StringComparison.OrdinalIgnoreCase)
                    || trustedField.Contains("FLAG", StringComparison.OrdinalIgnoreCase)
                    || trustedField.Contains("IT_FLAG", StringComparison.OrdinalIgnoreCase))
                && (IsEnableReg(bodyMember) || IsEnableReg(bodyReg)
                    || (!string.IsNullOrEmpty(bodyField)
                        && (bodyField.EndsWith("IE", StringComparison.OrdinalIgnoreCase)
                            || bodyField.Contains("IE", StringComparison.OrdinalIgnoreCase)))))
                return false;
            // LL_*_SR_*_IT_FLAG_MSK naming vs body IER
            if (trustedLabel.Contains("_SR_", StringComparison.OrdinalIgnoreCase)
                && (bodyMember.Equals("IER", StringComparison.OrdinalIgnoreCase)
                    || (bodyMskMacro?.Contains("_IER_", StringComparison.OrdinalIgnoreCase) == true)))
                return false;
        }

        // Break enable/disable: body DCR.BKxE, not UGR.BxG software trigger.
        if (fn.Contains("Break", StringComparison.OrdinalIgnoreCase)
            && (fn.Contains("Enable", StringComparison.OrdinalIgnoreCase)
                || fn.Contains("Disable", StringComparison.OrdinalIgnoreCase)))
        {
            if (trustedReg.Equals("UGR", StringComparison.OrdinalIgnoreCase)
                && bodyMember.Equals("DCR", StringComparison.OrdinalIgnoreCase))
                return false;
            if (!string.IsNullOrEmpty(trustedField)
                && Regex.IsMatch(trustedField, @"^B\d*G$", RegexOptions.IgnoreCase)
                && !string.IsNullOrEmpty(bodyField)
                && Regex.IsMatch(bodyField, @"^BK\d*E$", RegexOptions.IgnoreCase))
                return false;
        }

        // SPI CSSwOut body uses CSOS, not CSO.
        if (fn.Contains("CSSwOut", StringComparison.OrdinalIgnoreCase)
            && trustedLabel.Contains("_CSO_Msk", StringComparison.OrdinalIgnoreCase)
            && bodyMskMacro?.Contains("_CSOS_", StringComparison.OrdinalIgnoreCase) == true)
            return false;

        // ResetOperationMode body OP_MODE composite, not RESET bit.
        if (fn.Contains("ResetOperationMode", StringComparison.OrdinalIgnoreCase)
            && trustedLabel.Contains("_RESET_", StringComparison.OrdinalIgnoreCase)
            && bodyMskMacro?.Contains("OP_MODE", StringComparison.OrdinalIgnoreCase) == true)
            return false;

        // Body register known and trusted points at a different member while body mask embeds body member.
        if (!string.IsNullOrWhiteSpace(bodyMember)
            && !string.IsNullOrEmpty(trustedReg)
            && !trustedReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase)
            && (bodyMskMacro?.Contains($"_{bodyMember}_", StringComparison.OrdinalIgnoreCase) == true
                || (!string.IsNullOrEmpty(bodyReg)
                    && bodyReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase))))
            return false;

        // Reject false name hits: EnableChannel → LL_ADC_AWDG_MONITOR_CHANNEL_MSK while body is CHEN.
        // LL_*_MSK macros often fail chip-field parse (trustedField empty) — check Label too.
        // Keep trusted when the function name itself carries AWD/Monitor (AWDG2 wrong-body catch).
        if ((trustedLabel.Contains("AWDG", StringComparison.OrdinalIgnoreCase)
             || trustedLabel.Contains("MONITOR", StringComparison.OrdinalIgnoreCase)
             || (!string.IsNullOrEmpty(trustedField)
                 && trustedField.Contains("AWD", StringComparison.OrdinalIgnoreCase)))
            && !fn.Contains("AWD", StringComparison.OrdinalIgnoreCase)
            && !fn.Contains("Monitor", StringComparison.OrdinalIgnoreCase)
            && !string.IsNullOrEmpty(bodyField)
            && (string.IsNullOrEmpty(trustedField)
                || !bodyField.Equals(trustedField, StringComparison.OrdinalIgnoreCase)))
            return false;

        // ClearFlag / IT: CCER composite must not bind to IER/UGR/SR (LPTMR ClearFlag_CMP→SR.CIF).
        if ((trustedLabel.Contains("_CCER_", StringComparison.OrdinalIgnoreCase)
             || trustedReg.Equals("CCER", StringComparison.OrdinalIgnoreCase))
            && (bodyMember.Equals("IER", StringComparison.OrdinalIgnoreCase)
                || bodyMember.Equals("UGR", StringComparison.OrdinalIgnoreCase)
                || bodyMember.Equals("SR", StringComparison.OrdinalIgnoreCase)
                || bodyMember.Equals("ISR", StringComparison.OrdinalIgnoreCase)
                || bodyMskMacro?.Contains("_IER_", StringComparison.OrdinalIgnoreCase) == true
                || bodyMskMacro?.Contains("_SR_", StringComparison.OrdinalIgnoreCase) == true))
            return false;

        // ClearFlag: reject trusted when register differs (UGR vs SR) or OIF vs MIF / UG vs UIF.
        if (fn.Contains("ClearFlag", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("ClearDataFlag", StringComparison.OrdinalIgnoreCase))
        {
            if (!string.IsNullOrEmpty(trustedReg)
                && !string.IsNullOrEmpty(bodyMember)
                && !trustedReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase)
                && (bodyMskMacro?.Contains($"_{bodyMember}_", StringComparison.OrdinalIgnoreCase) == true
                    || bodyReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase)))
                return false;
            if (!IsClearFlagTrustedFieldCompatible(fn, bodyMskMacro, trustedLabel))
                return false;
        }

        // AutoReload vs EN; BTOMode TOSEL vs BTO full field.
        if (fn.Contains("AutoReload", StringComparison.OrdinalIgnoreCase)
            && trustedLabel.Contains("_EN_Msk", StringComparison.OrdinalIgnoreCase)
            && bodyMskMacro?.Contains("_ARE_", StringComparison.OrdinalIgnoreCase) == true)
            return false;
        if (fn.Contains("BTOMode", StringComparison.OrdinalIgnoreCase)
            && trustedLabel.Contains("_BTO_Msk", StringComparison.OrdinalIgnoreCase)
            && bodyMskMacro?.Contains("_TOSEL_", StringComparison.OrdinalIgnoreCase) == true)
            return false;

        return true;
    }

    /// <summary>
    /// ClearFlag_CC0 body uses CC0MIF; name token CC0 alone must not bind CC0OIF.
    /// ClearFlag_UPDATE body uses SR_UIF; must not bind UGR_UG.
    /// </summary>
    private static bool IsClearFlagTrustedFieldCompatible(
        string? functionName, string? bodyMskMacro, string? trustedLabel)
    {
        if (string.IsNullOrWhiteSpace(trustedLabel) || string.IsNullOrWhiteSpace(bodyMskMacro))
            return true;
        var fn = functionName ?? "";
        // Body always preferred when both are chip masks on same family — require field token match.
        TryParseChipMaskRegAndField(bodyMskMacro, out _, out var bodyField);
        TryParseChipMaskRegAndField(trustedLabel, out var trustedReg, out var trustedField);
        if (string.IsNullOrEmpty(bodyField) || string.IsNullOrEmpty(trustedField))
        {
            // Fall back: body macro substring must appear in trusted or vice versa for ClearFlag_UPDATE.
            if (fn.Contains("ClearFlag_UPDATE", StringComparison.OrdinalIgnoreCase)
                && trustedLabel.Contains("_UGR_", StringComparison.OrdinalIgnoreCase)
                && bodyMskMacro.Contains("_SR_", StringComparison.OrdinalIgnoreCase))
                return false;
            if (fn.Contains("ClearFlag_TRIG", StringComparison.OrdinalIgnoreCase)
                && trustedLabel.Contains("_UGR_", StringComparison.OrdinalIgnoreCase)
                && bodyMskMacro.Contains("_SR_", StringComparison.OrdinalIgnoreCase))
                return false;
            // Unparsed LL_/composite: require exact macro match (ERROR_FLAG ≠ ERROR_IT_FLAG).
            return bodyMskMacro.Equals(trustedLabel, StringComparison.OrdinalIgnoreCase);
        }

        if (bodyField.Equals(trustedField, StringComparison.OrdinalIgnoreCase))
            return true;

        // CCxMIF (capture) vs CCxOIF (overcapture)
        if (Regex.IsMatch(bodyField, @"^CC\d*MIF$", RegexOptions.IgnoreCase)
            && Regex.IsMatch(trustedField, @"^CC\d*OIF$", RegexOptions.IgnoreCase))
            return false;
        if (Regex.IsMatch(bodyField, @"^CC\d*OIF$", RegexOptions.IgnoreCase)
            && Regex.IsMatch(trustedField, @"^CC\d*MIF$", RegexOptions.IgnoreCase)
            && !fn.Contains("OVR", StringComparison.OrdinalIgnoreCase))
            return false;

        // UIF vs UG / TIF vs TG
        if (bodyField.Equals("UIF", StringComparison.OrdinalIgnoreCase)
            && (trustedField.Equals("UG", StringComparison.OrdinalIgnoreCase)
                || trustedReg.Equals("UGR", StringComparison.OrdinalIgnoreCase)))
            return false;
        if (bodyField.Equals("TIF", StringComparison.OrdinalIgnoreCase)
            && (trustedField.Equals("TG", StringComparison.OrdinalIgnoreCase)
                || trustedReg.Equals("UGR", StringComparison.OrdinalIgnoreCase)))
            return false;

        // ERROR_IT_FLAG (clearable IT subset) vs ERROR_FLAG (full status OR).
        if (bodyField.Contains("IT_FLAG", StringComparison.OrdinalIgnoreCase)
            != trustedField.Contains("IT_FLAG", StringComparison.OrdinalIgnoreCase))
            return false;
        if (bodyField.Contains("ERROR", StringComparison.OrdinalIgnoreCase)
            && trustedField.Contains("ERROR", StringComparison.OrdinalIgnoreCase)
            && !bodyField.Equals(trustedField, StringComparison.OrdinalIgnoreCase))
            return false;

        return bodyField.Equals(trustedField, StringComparison.OrdinalIgnoreCase);
    }

    /// <summary>True when mask peri token is a real instance (CAN0), not PERI_REG (CAN0_CTRL).</summary>
    private static bool IsLikelyPeripheralInstanceName(string? peri)
    {
        if (string.IsNullOrWhiteSpace(peri)) return false;
        // Never adopt LL_* composite tokens as instances (LL_ADC_CSR_MST from MST_IT_FLAG).
        if (peri.StartsWith("LL_", StringComparison.OrdinalIgnoreCase))
            return false;
        if (IsHostAggregateInstance(peri)) return true;
        // HRPWM_MST / HRPWM_SLV0 / HRPWM_COM — not ADC_CSR_MST mis-splits.
        if (Regex.IsMatch(
                peri,
                @"^[A-Za-z]+(\d+)?_(MST|SLV\d*|COM)$",
                RegexOptions.CultureInvariant | RegexOptions.IgnoreCase))
            return true;
        // ADC0 / CAN0 / TMR9 / RCU / WWDG / SYSCTRL
        return Regex.IsMatch(peri, @"^[A-Za-z]+(\d+)?$", RegexOptions.CultureInvariant);
    }

    /// <summary>
    /// Enrich an existing draft (no new cases) with RegisterWrite checks derived from the LL body.
    /// </summary>
    private static List<LlTestAssertionSpec> BuildDraftInternalAssertions(
        LlFunction fn, string instance, List<LlTestParameterValue> parameters)
    {
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName);
        var list = new List<LlTestAssertionSpec>();
        if (!string.IsNullOrWhiteSpace(body))
        {
            void AddWrite(string member, string detail)
            {
                if (string.IsNullOrWhiteSpace(member)) return;
                if (list.Any(a => a.Kind == LlAssertionKind.RegisterWrite
                                  && string.Equals(a.MemberName, member, StringComparison.OrdinalIgnoreCase)))
                    return;
                list.Add(new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterWrite,
                    InstanceName = instance,
                    MemberName = member,
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = detail
                });
            }

            foreach (Match m in SetClearBitPattern.Matches(body))
            {
                _ = TryParseRegAccessPath(m.Groups["path"].Value, out var path);
                var mem = ResolveMemberAlignedToMask(
                    string.IsNullOrEmpty(path.LeafMember) ? m.Groups["path"].Value.Trim() : path.LeafMember,
                    m.Groups["msk"].Value, out _, out var note);
                AddWrite(mem, $"草稿内部校验：{m.Groups["op"].Value} → {mem}；{note}");
            }

            foreach (Match m in ModifyRegPattern.Matches(body))
            {
                _ = TryParseRegAccessPath(m.Groups["path"].Value, out var path);
                var mem = ResolveMemberAlignedToMask(
                    string.IsNullOrEmpty(path.LeafMember) ? m.Groups["path"].Value.Trim() : path.LeafMember,
                    m.Groups["msk"].Value, out _, out var note);
                AddWrite(mem, $"草稿内部校验：MODIFY_REG → {mem}；{note}");
            }

            foreach (Match m in WriteRegPattern.Matches(body))
            {
                _ = TryParseRegAccessPath(m.Groups["path"].Value, out var path);
                var mem = string.IsNullOrEmpty(path.LeafMember)
                    ? m.Groups["path"].Value.Trim()
                    : path.LeafMember;
                var mskTok = Regex.Match(m.Groups["val"].Value, @"\b(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\b");
                if (mskTok.Success)
                    mem = ResolveMemberAlignedToMask(mem, mskTok.Groups["msk"].Value, out _, out _);
                AddWrite(mem, $"草稿内部校验：WRITE_REG → {mem}");
            }

            // SET_BIT / CLEAR_BIT with BIT(Ch) / REG_OFFSET — still enrich write target.
            foreach (Match m in SetClearBitChannelBitPattern.Matches(body))
            {
                _ = TryParseRegAccessPath(m.Groups["path"].Value, out var path);
                var mem = string.IsNullOrEmpty(path.LeafMember)
                    ? m.Groups["path"].Value.Trim()
                    : path.LeafMember;
                AddWrite(mem, $"草稿内部校验：{m.Groups["op"].Value} BIT(Ch) → {mem}");
            }

            foreach (Match m in SetClearBitRegOffsetChannelBitPattern.Matches(body))
            {
                var mem = m.Groups["base"].Value.Trim();
                AddWrite(mem, $"草稿内部校验：{m.Groups["op"].Value} REG_OFFSET → {mem}");
            }

            // GetRegAddr / DMA_GetRegAddr: return value must be non-zero mapped address.
            if (fn.FunctionName.Contains("GetRegAddr", StringComparison.OrdinalIgnoreCase)
                || fn.FunctionName.Contains("DMA_GetRegAddr", StringComparison.OrdinalIgnoreCase))
            {
                list.Add(new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.ReturnValue,
                    ExpectedExpression = "nonzero",
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = "草稿内部校验：GetRegAddr 返回值应非 0"
                });
            }

            // Boolean Is* with READ_BIT / READ_BIT_SHIFT: seed + expect return 1.
            if (list.All(a => a.Kind != LlAssertionKind.ReturnValue)
                && (fn.FunctionName.StartsWith("LL_", StringComparison.Ordinal)
                    && (fn.FunctionName.Contains("_Is", StringComparison.Ordinal)
                        || fn.FunctionName.Contains("Get", StringComparison.OrdinalIgnoreCase)))
                && (ReadBitShiftPattern.IsMatch(body) || ReadBitMaskPattern.IsMatch(body)
                    || ReadRegPattern.IsMatch(body)))
            {
                list.Add(new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.ReturnValue,
                    ExpectedExpression = "nonzero",
                    RuleSource = LlAssertionRuleSource.FromParseEvidence,
                    RuleSourceDetail = "草稿内部校验：读类 API 返回值应非 0（需配合初值；弱校验）"
                });
            }
        }

        // Ensure value params are non-zero so draft RegisterWrite can observe a host delta.
        foreach (var p in parameters)
        {
            if (p.Name.Equals("Val", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Period", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Value", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Addr", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Len", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
                || p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase))
            {
                if (string.IsNullOrWhiteSpace(p.ValueExpression)
                    || p.ValueExpression == "0"
                    || p.ValueExpression.Equals("0x0", StringComparison.OrdinalIgnoreCase))
                {
                    p.ValueExpression = "0x1";
                    p.RuleSource = nameof(LlAssertionRuleSource.FromParseEvidence);
                }
            }
        }

        list.AddRange(DefaultTimeoutAssertions());
        return list;
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
            && TryParseChipMaskRegAndField(mskMacro, bodyMember, out var maskReg, out _))
        {
            if (!maskReg.Equals(bodyMember, StringComparison.OrdinalIgnoreCase))
            {
                // Body wins when mask token is a multi-part field misread as REG
                // (historical: CAN0_CTRL_FD_EN → FD) — keep body member.
                if (mskMacro.Contains($"_{bodyMember}_", StringComparison.OrdinalIgnoreCase))
                {
                    pairNote =
                        $"断言寄存器 {bodyMember}（掩码含 _{bodyMember}_，忽略误解析 REG={maskReg}）";
                    return bodyMember;
                }

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
            if (!IsCompileTimeMaskToken(msk))
                return;
            _ = ResolveMemberAlignedToMask(mem, msk, out var mismatch, out var note);
            if (mismatch)
                notes.Add($"{op}: {note}");
        }

        foreach (Match m in SetClearBitPattern.Matches(body))
            Check(m.Groups["op"].Value, PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ModifyRegPattern.Matches(body))
            Check("MODIFY_REG", PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ReadBitShiftPattern.Matches(body))
            Check("READ_BIT_SHIFT", PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ReadBitThenShiftPattern.Matches(body))
            Check("READ_BIT>>Pos", PathLeaf(m), m.Groups["msk"].Value);
        foreach (Match m in ReadBitBoolPattern.Matches(body))
            Check("READ_BIT", PathLeaf(m), m.Groups["msk"].Value);
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
           || name.Contains("Get", StringComparison.OrdinalIgnoreCase)
           || name.Contains("Is", StringComparison.OrdinalIgnoreCase);

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
        // HRPWM multi-bank: prefer bank named in the LL symbol over MST default.
        if (functionName.Contains("_COM_", StringComparison.OrdinalIgnoreCase)
            || functionName.StartsWith("LL_HRPWM_COM_", StringComparison.OrdinalIgnoreCase))
            return "HRPWM_COM";
        if (functionName.Contains("_SLV_", StringComparison.OrdinalIgnoreCase)
            || functionName.StartsWith("LL_HRPWM_SLV_", StringComparison.OrdinalIgnoreCase))
            return "HRPWM_SLV0";
        if (functionName.Contains("_MST_", StringComparison.OrdinalIgnoreCase)
            || functionName.StartsWith("LL_HRPWM_MST_", StringComparison.OrdinalIgnoreCase))
            return "HRPWM_MST";

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
            "HRPWM" => "HRPWM_MST",
            // Chip FLASH_BASE; EFLASH_TypeDef maps to FLASH in virtual MCU.
            "EFLASH" => "FLASH",
            "DMA" => "DMA0",
            "CAN" => "CAN0",
            "SPI" => "SPI0",
            "I2C" => "I2C0",
            "UART" => "UART0",
            "DAC" => "DAC0",
            "CMP" => "CMP0",
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
                         || p.Name.Equals("Ratio", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Div", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Equals("Divider", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Contains("Prescaler", StringComparison.OrdinalIgnoreCase)
                         || p.Name.Contains("Prescl", StringComparison.OrdinalIgnoreCase)))
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

        // IsIntPending / IsIntEnable / IsInputPinSet / IsOutputPinSet — READ_BIT(reg, Pin)!=0 ? 1 : 0
        if (functionName.Contains("IsIntPending", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "ISR", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 ISR 对应 Pin 后 IsIntPending 应返回 1"));
            return true;
        }

        if (functionName.Contains("IsIntEnable", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "IER", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 IER 对应 Pin 后 IsIntEnable 应返回 1"));
            return true;
        }

        if (functionName.Contains("IsInputPinSet", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "DIR", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 DIR 对应 Pin 后 IsInputPinSet 应返回 1"));
            return true;
        }

        if (functionName.Contains("IsOutputPinSet", StringComparison.OrdinalIgnoreCase))
        {
            initials.Add(new LlTestInitialRegister { InstanceName = instance, MemberName = "DOR", ValueHex = $"0x{pin:X}" });
            assertions.Insert(0, ReturnValueAssertion("0x1", "预置 DOR 对应 Pin 后 IsOutputPinSet 应返回 1"));
            return true;
        }

        return false;
    }

    /// <summary>
    /// GPIO Enable/Disable/Toggle/Set* driven by SET/CLEAR/MODIFY/WRITE in the LL body (Pin mask).
    /// </summary>
    private static bool TryBuildGpioBodyDrivenCase(
        LlFunction fn,
        List<LlFunctionParameter> parameters,
        string instance,
        string pinName,
        string pinExpr,
        out LlTestCaseEditModel model)
    {
        model = BaseModel(fn);
        var body = TryReadFunctionBodyFromSource(fn.FilePath, fn.FunctionName) ?? "";
        if (string.IsNullOrWhiteSpace(body)) return false;
        var pinVal = TestHarnessGenerator.ParseUIntExpression(pinExpr);
        if (pinVal == 0) pinVal = 1u;
        var pinIdx = LlClearStatusRegisterResolver.GpioPinBitIndex(pinVal);
        var pars = BuildParams(parameters, instance, pinExpr);

        // SET_BIT / CLEAR_BIT(GPIOx->MEM, Pin) — Debounce/IT/Hyst/Sync.
        var setClear = MatchPreferredSetClear(body, fn.FunctionName);
        if (setClear is { Success: true }
            && !IsCompileTimeMaskToken(setClear.Groups["msk"].Value))
        {
            _ = TryParseRegAccessPath(setClear.Groups["path"].Value, out var path);
            var mem = string.IsNullOrEmpty(path.LeafMember)
                ? setClear.Groups["path"].Value.Trim()
                : path.LeafMember;
            var isClear = setClear.Groups["op"].Value.Equals("CLEAR_BIT", StringComparison.OrdinalIgnoreCase);
            model.Name = $"{fn.FunctionName}/{instance}/{pinName}/{mem}/{(isClear ? "clear" : "enable")}-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = pars;
            model.InitialRegisters =
            [
                new LlTestInitialRegister
                {
                    InstanceName = instance,
                    MemberName = mem,
                    ValueHex = $"0x{(isClear ? pinVal : 0u):X}"
                }
            ];
            model.Assertions =
            [
                GpioRegAssert(instance, mem, isClear ? 0u : pinVal, pinVal,
                    $"{setClear.Groups["op"].Value}({mem}, Pin) → (reg&0x{pinVal:X})==0x{(isClear ? 0u : pinVal):X}"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = $"写校验：GPIO {mem} Pin={pinName}。虚拟环境。";
            return true;
        }

        // TogglePin: WRITE BSR from DOR — seed DOR=0 → expect pin set via BS.
        if (fn.FunctionName.Contains("TogglePin", StringComparison.OrdinalIgnoreCase))
        {
            model.Name = $"{fn.FunctionName}/{instance}/{pinName}/toggle-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = pars;
            model.InitialRegisters =
            [
                new LlTestInitialRegister { InstanceName = instance, MemberName = "DOR", ValueHex = "0x0" },
                new LlTestInitialRegister { InstanceName = instance, MemberName = "BSR", ValueHex = "0x0" }
            ];
            model.Assertions =
            [
                GpioRegAssert(instance, "DOR", pinVal, pinVal,
                    "TogglePin 自 0：虚拟 BSR→DOR 应置位 Pin"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "写校验：TogglePin 后 DOR。虚拟环境。";
            return true;
        }

        // SetDrvCap(Pin, DrvCap=1): SET low nibble bit on DHR.
        if (fn.FunctionName.Contains("SetDrvCap", StringComparison.OrdinalIgnoreCase))
        {
            foreach (var p in pars)
            {
                if (p.Name.Equals("DrvCap", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Cap", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = "0x1";
            }

            model.Name = $"{fn.FunctionName}/{instance}/{pinName}/DHR/write-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = pars;
            model.InitialRegisters =
            [
                new LlTestInitialRegister { InstanceName = instance, MemberName = "DHR", ValueHex = "0x0" }
            ];
            model.Assertions =
            [
                GpioRegAssert(instance, "DHR", pinVal, pinVal,
                    "SetDrvCap(DrvCap=1) → DHR 低半字对应 Pin 置位"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "写校验：SetDrvCap → DHR。虚拟环境。";
            return true;
        }

        // SetIntMode(PinNum, Mode): MODIFY IMR 2-bit field.
        if (fn.FunctionName.Contains("SetIntMode", StringComparison.OrdinalIgnoreCase))
        {
            const uint mode = 0x1u;
            var fieldMask = 0x3u << (2 * pinIdx);
            var setBits = (mode & 0x3u) << (2 * pinIdx);
            foreach (var p in pars)
            {
                if (p.Name.Equals("PinNum", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Pin", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = pinIdx.ToString();
                if (p.Name.Equals("Mode", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = $"0x{mode:X}";
            }

            model.Name = $"{fn.FunctionName}/{instance}/{pinName}/IMR/write-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = pars;
            model.InitialRegisters =
            [
                new LlTestInitialRegister { InstanceName = instance, MemberName = "IMR", ValueHex = "0x0" }
            ];
            model.Assertions =
            [
                GpioRegAssert(instance, "IMR", setBits, fieldMask,
                    $"SetIntMode(PinNum={pinIdx}, Mode=0x{mode:X}) → IMR"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = "写校验：SetIntMode → IMR。虚拟环境。";
            return true;
        }

        // SetAFPin(Pin, Alternate=1): MODIFY MR0 for pin0-7.
        if (fn.FunctionName.Contains("SetAFPin", StringComparison.OrdinalIgnoreCase))
        {
            const uint alt = 0x1u;
            var mem = pinIdx < 8 ? "MR0" : "MR1";
            var lane = pinIdx < 8 ? pinIdx : pinIdx % 8;
            var fieldMask = 0xFu << (4 * lane);
            var setBits = (alt & 0xFu) << (4 * lane);
            foreach (var p in pars)
            {
                if (p.Name.Equals("Alternate", StringComparison.OrdinalIgnoreCase)
                    || p.Name.Equals("Af", StringComparison.OrdinalIgnoreCase))
                    p.ValueExpression = $"0x{alt:X}";
            }

            model.Name = $"{fn.FunctionName}/{instance}/{pinName}/{mem}/write-check";
            model.Status = nameof(LlTestCaseStatus.Ready);
            model.IsAutoGenerated = true;
            model.Parameters = pars;
            model.InitialRegisters =
            [
                new LlTestInitialRegister { InstanceName = instance, MemberName = mem, ValueHex = "0x0" }
            ];
            model.Assertions =
            [
                GpioRegAssert(instance, mem, setBits, fieldMask,
                    $"SetAFPin(AF=0x{alt:X}) → {mem}"),
                ..DefaultTimeoutAssertions()
            ];
            model.Notes = $"写校验：SetAFPin → {mem}。虚拟环境。";
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
