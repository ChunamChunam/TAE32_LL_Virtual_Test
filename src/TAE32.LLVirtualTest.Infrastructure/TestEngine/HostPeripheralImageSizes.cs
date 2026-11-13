namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>Minimum host peri image bytes (SDK struct sizes) so REG_OFFSET stays in mapped RAM.</summary>
internal static class HostPeripheralImageSizes
{
    private static readonly Dictionary<string, int> ByModule = new(StringComparer.OrdinalIgnoreCase)
    {
        ["ADC"] = 0x400,
        ["IIR"] = 0x200,
        ["HRPWM"] = 0x1000,
        ["GPIO"] = 0x80,
        ["ADTMR"] = 0x200,
        ["GPTMRX"] = 0x200,
        ["GPTMRY"] = 0x200,
        ["LPTMR"] = 0x100,
        ["SYSCTRL"] = 0x100,
        ["EFLASH"] = 0x200,
    };

    public static int MinBytes(string? instanceName, string? moduleHint)
    {
        if (!string.IsNullOrWhiteSpace(moduleHint) && ByModule.TryGetValue(moduleHint.Trim(), out var m))
            return m;
        if (string.IsNullOrWhiteSpace(instanceName))
            return 0;
        foreach (var prefix in ByModule.Keys)
        {
            if (instanceName.StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
                return ByModule[prefix];
        }
        return 0;
    }
}
