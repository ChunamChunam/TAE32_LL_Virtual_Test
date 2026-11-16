using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

/// <summary>
/// Host virtual model overrides when SVD/DB access is Unknown/RW but hardware is W1C/W0C.
/// Does not modify vendor SDK.
/// Evidence for status W1C: LL ClearFlag_* uses WRITE_REG(reg, Flag_Msk); DMA comments say R/W1C;
/// WWDG SVD marks EWIF as read-write but ClearFlag_EWIF is the classic W1C idiom.
/// </summary>
internal static class VirtualRegisterSemanticsOverrides
{
    /// <summary>Register members that are flag/status banks cleared by writing 1.</summary>
    private static readonly HashSet<string> Write1ClearMembers = new(StringComparer.OrdinalIgnoreCase)
    {
        "ISR", "DISR", "FISR", "JISR", "RISR", "SR", "IFR", "IR", "ICR",
        "MISR", "PWMISR"
    };

    public static VirtualRegisterBehavior OverrideBehavior(
        string? moduleName,
        string memberName,
        VirtualRegisterBehavior resolved)
    {
        if (resolved is VirtualRegisterBehavior.Write1Clear or VirtualRegisterBehavior.Write0Clear
            or VirtualRegisterBehavior.ReadClear or VirtualRegisterBehavior.Write1Set
            or VirtualRegisterBehavior.Toggle)
            return resolved;

        // Status / flag registers across peripherals (WWDG/IWDG/ADC/CMP/UART/DAC/TMR/HRPWM/…).
        if (Write1ClearMembers.Contains(memberName))
            return VirtualRegisterBehavior.Write1Clear;

        return resolved;
    }

    /// <summary>
    /// When register is modeled as W1C and a field still says Unknown/RW, inherit W1C at bit level.
    /// </summary>
    public static void ApplyFieldInheritance(VirtualRegisterSlot slot)
    {
        if (slot.Behavior is not (VirtualRegisterBehavior.Write1Clear or VirtualRegisterBehavior.Write0Clear
            or VirtualRegisterBehavior.Write1Set or VirtualRegisterBehavior.Toggle))
            return;

        foreach (var f in slot.Fields)
        {
            if (!string.IsNullOrWhiteSpace(f.AccessAttribute)
                && !f.AccessAttribute.Equals("Unknown", StringComparison.OrdinalIgnoreCase)
                && !f.AccessAttribute.Equals("Rw", StringComparison.OrdinalIgnoreCase)
                && !f.AccessAttribute.Equals("read-write", StringComparison.OrdinalIgnoreCase))
                continue;

            f.AccessAttribute = slot.Behavior switch
            {
                VirtualRegisterBehavior.Write1Clear => "W1c",
                VirtualRegisterBehavior.Write0Clear => "W0c",
                VirtualRegisterBehavior.Write1Set => "W1s",
                VirtualRegisterBehavior.Toggle => "Toggle",
                _ => f.AccessAttribute
            };
        }
    }
}
