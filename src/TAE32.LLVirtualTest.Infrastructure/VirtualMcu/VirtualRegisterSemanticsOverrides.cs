using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

/// <summary>
/// Host virtual model overrides when SVD/DB access is Unknown/RW but hardware is W1C/W0C.
/// Does not modify vendor SDK.
/// </summary>
internal static class VirtualRegisterSemanticsOverrides
{
    private static readonly HashSet<string> Write1ClearMembers = new(StringComparer.OrdinalIgnoreCase)
    {
        "ISR", "DISR", "FISR", "JISR", "RISR", "SR", "IFR", "IR"
    };

    public static VirtualRegisterBehavior OverrideBehavior(
        string? moduleName,
        string memberName,
        VirtualRegisterBehavior resolved)
    {
        if (resolved is VirtualRegisterBehavior.Write1Clear or VirtualRegisterBehavior.Write0Clear
            or VirtualRegisterBehavior.ReadClear)
            return resolved;

        if (!Write1ClearMembers.Contains(memberName))
            return resolved;

        var mod = moduleName ?? string.Empty;
        if (mod.Contains("GPIO", StringComparison.OrdinalIgnoreCase)
            && memberName.Equals("ISR", StringComparison.OrdinalIgnoreCase))
            return VirtualRegisterBehavior.Write1Clear;

        if (mod.Contains("ADC", StringComparison.OrdinalIgnoreCase))
            return VirtualRegisterBehavior.Write1Clear;

        if (mod.Contains("CMP", StringComparison.OrdinalIgnoreCase)
            && memberName.Equals("ISR", StringComparison.OrdinalIgnoreCase))
            return VirtualRegisterBehavior.Write1Clear;

        if ((mod.Contains("IIR", StringComparison.OrdinalIgnoreCase)
             || mod.Contains("WWDG", StringComparison.OrdinalIgnoreCase))
            && memberName.Equals("ISR", StringComparison.OrdinalIgnoreCase))
            return VirtualRegisterBehavior.Write1Clear;

        return resolved;
    }
}
