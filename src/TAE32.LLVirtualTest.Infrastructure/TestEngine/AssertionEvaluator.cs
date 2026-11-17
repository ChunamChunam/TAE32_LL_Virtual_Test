using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using VirtualAccessKind = TAE32.LLVirtualTest.Core.Enums.VirtualAccessKind;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

internal static class AssertionEvaluator
{
    public static async Task<List<LlTestAssertionResult>> EvaluateAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        IReadOnlyList<LlTestAssertionSpec> specs,
        uint? returnValue,
        IReadOnlyList<VirtualAccessRecord> trace,
        Exception? executionException,
        int elapsedMs,
        CancellationToken ct)
    {
        var results = new List<LlTestAssertionResult>();
        foreach (var spec in specs)
        {
            results.Add(spec.Kind switch
            {
                LlAssertionKind.ReturnValue => EvalReturn(spec, returnValue),
                LlAssertionKind.RegisterValue => await EvalRegister(mcu, mcuId, spec, ct),
                LlAssertionKind.BitField => await EvalBitField(mcu, mcuId, spec, ct),
                LlAssertionKind.PreserveBits => await EvalRegister(mcu, mcuId, spec, ct),
                LlAssertionKind.RegisterAccessOrder => EvalAccessOrder(spec, trace),
                LlAssertionKind.FunctionCall => EvalFunctionCall(spec, trace),
                LlAssertionKind.Exception => EvalException(spec, executionException),
                LlAssertionKind.Timeout => EvalTimeout(spec, elapsedMs),
                LlAssertionKind.RegisterWrite => EvalRegisterWrite(spec, trace),
                LlAssertionKind.RegisterAddress => await EvalRegisterAddress(mcu, mcuId, spec, ct),
                LlAssertionKind.NoUnexpectedWrite => EvalNoUnexpectedWrite(spec, trace),
                LlAssertionKind.ArrayIndex => EvalArrayIndex(spec),
                _ => Fail(spec, "未支持的断言类型")
            });
        }
        return results;
    }

    private static LlTestAssertionResult EvalReturn(LlTestAssertionSpec spec, uint? actual)
    {
        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);
        var ok = actual is uint a && a == expected;
        return Result(spec, ok, $"0x{expected:X8}", actual is uint v ? $"0x{v:X8}" : "null",
            ok ? "返回值匹配" : "返回值不匹配");
    }

    private static async Task<LlTestAssertionResult> EvalRegister(
        IVirtualMcuService mcu, Guid mcuId, LlTestAssertionSpec spec, CancellationToken ct)
    {
        if (string.IsNullOrWhiteSpace(spec.InstanceName) || string.IsNullOrWhiteSpace(spec.MemberName))
            return Fail(spec, "寄存器断言缺少 instance/member");
        var reg = await mcu.GetRegisterAsync(mcuId, spec.InstanceName!, spec.MemberName!, ct);
        if (reg is null) return Fail(spec, "寄存器不存在于虚拟 MCU");
        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);
        var mask = spec.ExpectedMask ?? 0xFFFFFFFFu;
        var actualMasked = reg.CurrentValue & mask;
        var expectedMasked = expected & mask;
        var ok = actualMasked == expectedMasked;
        var detail = string.IsNullOrWhiteSpace(spec.RuleSourceDetail) ? "" : $"；{spec.RuleSourceDetail}";
        return Result(spec, ok, $"0x{expectedMasked:X8}", $"0x{actualMasked:X8}",
            ok
                ? "寄存器值匹配（虚拟环境）"
                : $"寄存器断言失败：期望 0x{expectedMasked:X}，实际 0x{actualMasked:X}（掩码 0x{mask:X}）{detail}");
    }

    private static async Task<LlTestAssertionResult> EvalBitField(
        IVirtualMcuService mcu, Guid mcuId, LlTestAssertionSpec spec, CancellationToken ct)
    {
        if (string.IsNullOrWhiteSpace(spec.InstanceName) || string.IsNullOrWhiteSpace(spec.MemberName)
            || string.IsNullOrWhiteSpace(spec.BitFieldName))
            return Fail(spec, "位域断言缺少字段");
        var reg = await mcu.GetRegisterAsync(mcuId, spec.InstanceName!, spec.MemberName!, ct);
        if (reg is null) return Fail(spec, "寄存器不存在于虚拟 MCU");
        var field = reg.Fields.FirstOrDefault(f =>
            f.Name.Equals(spec.BitFieldName, StringComparison.OrdinalIgnoreCase));

        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);

        // Prefer assertion FieldMask (chip-resolved ExpectedMask) over possibly-stale DB field.Mask.
        uint fieldMask;
        int pos;
        if (spec.ExpectedMask is uint m && m != 0)
        {
            fieldMask = m;
            pos = field?.BitPosition ?? CountTrailingZeros(m);
        }
        else if (field is not null && field.Mask != 0)
        {
            fieldMask = field.Mask;
            pos = field.BitPosition;
        }
        else
            return Fail(spec, "位域不存在且断言未提供 FieldMask");

        var actual = (reg.CurrentValue & fieldMask) >> pos;
        var width = CountMaskWidth(fieldMask >> pos);
        var ok = actual == expected;
        var detail =
            $"FieldMask=0x{fieldMask:X} Pos={pos} Width={width} " +
            $"BitFieldExpected=0x{expected:X} BitFieldActual=0x{actual:X} " +
            $"Reg=0x{reg.CurrentValue:X}" +
            (field is not null && field.Mask != fieldMask
                ? $"；slot.Mask=0x{field.Mask:X}已忽略"
                : "");
        return Result(spec, ok, $"0x{expected:X}", $"0x{actual:X}",
            ok ? $"位域匹配；{detail}" : $"位域不匹配；{detail}");
    }

    private static int CountTrailingZeros(uint mask)
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

    private static int CountMaskWidth(uint shiftedMask)
    {
        var w = 0;
        while (shiftedMask != 0 && w < 32)
        {
            shiftedMask >>= 1;
            w++;
        }
        return w;
    }

    private static LlTestAssertionResult EvalAccessOrder(LlTestAssertionSpec spec, IReadOnlyList<VirtualAccessRecord> trace)
    {
        var expected = spec.ExpectedAccessOrder ?? Array.Empty<string>();
        if (expected.Count == 0) return Fail(spec, "访问顺序断言为空");
        var actual = trace
            .Where(t => t.AccessKind is VirtualAccessKind.Write or VirtualAccessKind.Read
                or VirtualAccessKind.SetBits or VirtualAccessKind.ClearBits)
            .Where(IsLlAttributedAccess)
            .OrderBy(t => t.Sequence)
            .Select(t => t.RegisterName)
            .ToList();
        var idx = 0;
        foreach (var name in actual)
        {
            if (idx < expected.Count
                && name.Contains(expected[idx], StringComparison.OrdinalIgnoreCase))
                idx++;
        }
        var ok = idx >= expected.Count;
        return Result(spec, ok, string.Join(" → ", expected), string.Join(" → ", actual.Take(20)),
            ok ? "访问顺序满足" : "访问顺序不满足");
    }

    private static LlTestAssertionResult EvalFunctionCall(LlTestAssertionSpec spec, IReadOnlyList<VirtualAccessRecord> trace)
    {
        var expected = spec.ExpectedExpression ?? "";
        var ok = trace.Any(t =>
            !string.IsNullOrEmpty(t.LlFunctionName)
            && t.LlFunctionName.Contains(expected, StringComparison.OrdinalIgnoreCase));
        // Native harness marks context as the LL function name.
        return Result(spec, ok, expected, ok ? expected : "(未在追踪中出现)",
            ok ? "追踪中出现目标函数上下文" : "追踪中未出现目标函数上下文");
    }

    private static LlTestAssertionResult EvalException(LlTestAssertionSpec spec, Exception? ex)
    {
        var expectException = string.Equals(spec.ExpectedExpression, "throw", StringComparison.OrdinalIgnoreCase)
                              || string.Equals(spec.ExpectedHex, "1", StringComparison.OrdinalIgnoreCase);
        var ok = expectException ? ex is not null : ex is null;
        return Result(spec, ok, expectException ? "exception" : "no-exception",
            ex?.GetType().Name ?? "none", ok ? "异常断言通过" : "异常断言失败");
    }

    private static LlTestAssertionResult EvalTimeout(LlTestAssertionSpec spec, int elapsedMs)
    {
        var limit = spec.TimeoutMs ?? 10000;
        var ok = elapsedMs <= limit;
        // elapsedMs is native-execute duration (not compile wall time).
        return Result(spec, ok, $"<= {limit} ms (native)", $"{elapsedMs} ms",
            ok ? "未超时" : "原生执行超时");
    }

    private static LlTestAssertionResult EvalRegisterWrite(
        LlTestAssertionSpec spec, IReadOnlyList<VirtualAccessRecord> trace)
    {
        if (string.IsNullOrWhiteSpace(spec.InstanceName) || string.IsNullOrWhiteSpace(spec.MemberName))
            return Fail(spec, "RegisterWrite 缺少 instance/member");
        var key = $"{spec.InstanceName}.{spec.MemberName}";
        var llTrace = trace.Where(IsLlAttributedAccess).ToList();
        if (llTrace.Count == 0)
        {
            return Result(spec, false, key, "轨迹为空/不完整",
                "未捕获到寄存器访问轨迹：不能判定已写入。可能是宿主映像偏移与 AbsoluteAddress 不一致，" +
                "或 MODIFY_REG 写到了未映射地址（非确认“未发生写入”）。");
        }

        var writes = llTrace
            .Where(t => t.AccessKind is VirtualAccessKind.Write or VirtualAccessKind.SetBits
                or VirtualAccessKind.ClearBits or VirtualAccessKind.ModifyBits or VirtualAccessKind.WriteBitField)
            .Where(t =>
                (t.RegisterName?.Contains(spec.MemberName!, StringComparison.OrdinalIgnoreCase) ?? false)
                && (string.IsNullOrWhiteSpace(t.InstanceName)
                    || t.InstanceName.Equals(spec.InstanceName, StringComparison.OrdinalIgnoreCase)
                    || (t.RegisterName?.Contains(spec.InstanceName!, StringComparison.OrdinalIgnoreCase) ?? false)))
            .ToList();
        var ok = writes.Count > 0;
        return Result(spec, ok, key, ok ? $"{writes.Count} write(s)" : "无目标写入",
            ok ? "检测到目标寄存器写入（虚拟轨迹）" : "轨迹非空但未检测到目标寄存器写入");
    }

    private static async Task<LlTestAssertionResult> EvalRegisterAddress(
        IVirtualMcuService mcu, Guid mcuId, LlTestAssertionSpec spec, CancellationToken ct)
    {
        if (string.IsNullOrWhiteSpace(spec.InstanceName) || string.IsNullOrWhiteSpace(spec.MemberName))
            return Fail(spec, "RegisterAddress 缺少 instance/member");
        var reg = await mcu.GetRegisterAsync(mcuId, spec.InstanceName!, spec.MemberName!, ct);
        if (reg is null) return Fail(spec, "寄存器不存在于虚拟 MCU");
        if (reg.AbsoluteAddress is null)
            return Fail(spec, "虚拟寄存器无 AbsoluteAddress");
        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);
        var actual = reg.AbsoluteAddress.Value;
        var ok = actual == expected;
        return Result(spec, ok, $"0x{expected:X8}", $"0x{actual:X8}",
            ok ? "寄存器地址匹配" : "寄存器地址不匹配");
    }

    private static LlTestAssertionResult EvalNoUnexpectedWrite(
        LlTestAssertionSpec spec, IReadOnlyList<VirtualAccessRecord> trace)
    {
        var allow = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        if (!string.IsNullOrWhiteSpace(spec.InstanceName) && !string.IsNullOrWhiteSpace(spec.MemberName))
            allow.Add($"{spec.InstanceName}.{spec.MemberName}");
        if (spec.ExpectedAccessOrder is { Count: > 0 })
        {
            foreach (var a in spec.ExpectedAccessOrder)
                if (!string.IsNullOrWhiteSpace(a))
                    allow.Add(a.Trim());
        }

        if (allow.Count == 0)
            return Fail(spec, "NoUnexpectedWrite 未指定允许的寄存器");

        var llWrites = trace.Where(IsLlAttributedAccess)
            .Where(x => x.AccessKind is VirtualAccessKind.Write or VirtualAccessKind.SetBits
                or VirtualAccessKind.ClearBits or VirtualAccessKind.ModifyBits
                or VirtualAccessKind.WriteBitField)
            .ToList();

        // Empty/incomplete capture must NOT pass as "no unexpected writes".
        if (llWrites.Count == 0)
        {
            return Result(spec, false,
                string.Join(", ", allow),
                "轨迹为空/不完整",
                "访问轨迹为空或不完整：不能判定“无意外写入”（可能未捕获到 MMIO，而非确认没有副作用）。");
        }

        var unexpected = new List<string>();
        foreach (var t in llWrites)
        {
            var name = !string.IsNullOrWhiteSpace(t.InstanceName) && !string.IsNullOrWhiteSpace(t.RegisterName)
                ? $"{t.InstanceName}.{t.RegisterName}"
                : (t.RegisterName ?? "");
            var ok = allow.Any(a =>
                name.Equals(a, StringComparison.OrdinalIgnoreCase)
                || name.EndsWith("." + a, StringComparison.OrdinalIgnoreCase)
                || (t.RegisterName?.Equals(a, StringComparison.OrdinalIgnoreCase) ?? false)
                || name.Contains(a, StringComparison.OrdinalIgnoreCase));
            if (!ok && !string.IsNullOrWhiteSpace(name))
                unexpected.Add(name);
        }

        var passed = unexpected.Count == 0;
        return Result(spec, passed,
            string.Join(", ", allow),
            unexpected.Count == 0 ? "(无意外写入)" : string.Join(", ", unexpected.Distinct().Take(12)),
            passed ? "无意外寄存器写入" : "检测到非目标寄存器写入");
    }

    private static LlTestAssertionResult EvalArrayIndex(LlTestAssertionSpec spec)
    {
        // Generation embeds computed index in ExpectedHex and resolved instance in InstanceName.
        // Runtime re-check: InstanceName ends with the index digit(s) when pattern HRPWM_SLVn.
        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);
        var inst = spec.InstanceName ?? "";
        var m = System.Text.RegularExpressions.Regex.Match(inst, @"(\d+)\s*$");
        if (!m.Success)
            return Result(spec, true, $"index={expected}", inst,
                "ArrayIndex：实例名无尾缀数字，已按生成期计算接受");
        var actual = uint.Parse(m.Groups[1].Value);
        var ok = actual == expected;
        return Result(spec, ok, $"index={expected}", $"instance={inst} → {actual}",
            ok ? "数组索引与实例一致" : "数组索引与实例不一致");
    }

    /// <summary>
    /// Exclude test preload / unchanged harness sync noise from LL write/order checks.
    /// Keep records attributed to the LL function (including Note=ll-native-write).
    /// </summary>
    private static bool IsLlAttributedAccess(VirtualAccessRecord t)
    {
        if (string.Equals(t.LlFunctionName, "(init)", StringComparison.OrdinalIgnoreCase))
            return false;
        if (!string.IsNullOrEmpty(t.Message)
            && t.Message.Contains("测试预置", StringComparison.Ordinal))
            return false;
        // AccessTraceStore stores context.Note into Message when no other message is set.
        if (!string.IsNullOrEmpty(t.Message)
            && t.Message.Equals("native-harness-sync", StringComparison.OrdinalIgnoreCase))
            return false;
        return true;
    }

    private static LlTestAssertionResult Fail(LlTestAssertionSpec spec, string message)
        => Result(spec, false, spec.ExpectedHex ?? spec.ExpectedExpression, null, message);

    private static LlTestAssertionResult Result(
        LlTestAssertionSpec spec, bool passed, string? expected, string? actual, string message)
        => new()
        {
            AssertionId = spec.Id,
            Kind = spec.Kind,
            Passed = passed,
            Expected = expected,
            Actual = actual,
            Message = message,
            RuleSource = spec.RuleSource,
            RuleSourceDetail = spec.RuleSourceDetail
        };
}
