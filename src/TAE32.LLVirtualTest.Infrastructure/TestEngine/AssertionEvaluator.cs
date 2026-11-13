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
                LlAssertionKind.RegisterAccessOrder => EvalAccessOrder(spec, trace),
                LlAssertionKind.FunctionCall => EvalFunctionCall(spec, trace),
                LlAssertionKind.Exception => EvalException(spec, executionException),
                LlAssertionKind.Timeout => EvalTimeout(spec, elapsedMs),
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
        var ok = (reg.CurrentValue & mask) == (expected & mask);
        return Result(spec, ok, $"0x{(expected & mask):X8}", $"0x{(reg.CurrentValue & mask):X8}",
            ok ? "寄存器值匹配（虚拟环境）" : "寄存器值不匹配（虚拟环境）");
    }

    private static async Task<LlTestAssertionResult> EvalBitField(
        IVirtualMcuService mcu, Guid mcuId, LlTestAssertionSpec spec, CancellationToken ct)
    {
        if (string.IsNullOrWhiteSpace(spec.InstanceName) || string.IsNullOrWhiteSpace(spec.MemberName)
            || string.IsNullOrWhiteSpace(spec.BitFieldName))
            return Fail(spec, "位域断言缺少字段");
        var reg = await mcu.GetRegisterAsync(mcuId, spec.InstanceName!, spec.MemberName!, ct);
        var field = reg?.Fields.FirstOrDefault(f =>
            f.Name.Equals(spec.BitFieldName, StringComparison.OrdinalIgnoreCase));
        if (field is null) return Fail(spec, "位域不存在");
        var expected = TestHarnessGenerator.ParseUIntExpression(spec.ExpectedHex ?? spec.ExpectedExpression);
        var ok = field.Value == expected;
        return Result(spec, ok, expected.ToString(), field.Value.ToString(),
            ok ? "位域匹配" : "位域不匹配");
    }

    private static LlTestAssertionResult EvalAccessOrder(LlTestAssertionSpec spec, IReadOnlyList<VirtualAccessRecord> trace)
    {
        var expected = spec.ExpectedAccessOrder ?? Array.Empty<string>();
        if (expected.Count == 0) return Fail(spec, "访问顺序断言为空");
        var actual = trace
            .Where(t => t.AccessKind is VirtualAccessKind.Write or VirtualAccessKind.Read
                or VirtualAccessKind.SetBits or VirtualAccessKind.ClearBits)
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
