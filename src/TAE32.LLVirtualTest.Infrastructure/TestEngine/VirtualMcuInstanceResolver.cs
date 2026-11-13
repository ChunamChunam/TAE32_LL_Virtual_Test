using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Maps harness peripheral hints (e.g. macro name ADC) to virtual MCU register instance names (ADC0).
/// </summary>
internal static class VirtualMcuInstanceResolver
{
    private static readonly Dictionary<string, string> ModuleDefaultInstance = new(StringComparer.OrdinalIgnoreCase)
    {
        ["ADC"] = "ADC0",
        ["GPIO"] = "GPIOA",
        ["TMR"] = "TMR0",
        ["HRPWM"] = "HRPWM",
        ["RCU"] = "RCU",
        ["SYSCTRL"] = "SYSCTRL",
    };

    public static async Task<string> ResolveAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string hint,
        string? moduleName,
        CancellationToken cancellationToken)
    {
        if (string.IsNullOrWhiteSpace(hint))
            hint = moduleName ?? "PERI";

        var regs = await mcu.GetRegistersAsync(mcuId, moduleName, hint, cancellationToken);
        if (regs.Count > 0)
            return hint;

        var moduleRegs = string.IsNullOrWhiteSpace(moduleName)
            ? await mcu.GetRegistersAsync(mcuId, hint, null, cancellationToken)
            : await mcu.GetRegistersAsync(mcuId, moduleName, null, cancellationToken);

        if (moduleRegs.Count > 0)
        {
            var inst = moduleRegs[0].InstanceName;
            if (!string.IsNullOrWhiteSpace(inst))
                return inst;
        }

        if (ModuleDefaultInstance.TryGetValue(hint, out var fallback))
            return fallback;
        if (moduleName is not null && ModuleDefaultInstance.TryGetValue(moduleName, out fallback))
            return fallback;

        return hint;
    }
}
