using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal static class RegisterSemanticsEngine
{
    public static uint WidthMask(int widthBits)
    {
        if (widthBits >= 32) return 0xFFFFFFFFu;
        if (widthBits <= 0) return 0u;
        return (1u << widthBits) - 1u;
    }

    public static bool IsSupportedWidth(int widthBits) => widthBits is 8 or 16 or 32;

    public static VirtualRegisterBehavior ResolveBehavior(
        string accessAttribute,
        bool defaultUnknownToRw,
        out SimulationLimitationKind limitation,
        out string note)
    {
        limitation = SimulationLimitationKind.None;
        note = string.Empty;
        var key = (accessAttribute ?? "Unknown").Trim();

        if (Enum.TryParse<RegisterAccessAttributeKind>(key, ignoreCase: true, out var kind))
        {
            return kind switch
            {
                RegisterAccessAttributeKind.Ro => VirtualRegisterBehavior.ReadOnly,
                RegisterAccessAttributeKind.Wo => VirtualRegisterBehavior.WriteOnly,
                RegisterAccessAttributeKind.Rw => VirtualRegisterBehavior.ReadWrite,
                RegisterAccessAttributeKind.W1c => VirtualRegisterBehavior.Write1Clear,
                RegisterAccessAttributeKind.W0c => VirtualRegisterBehavior.Write0Clear,
                RegisterAccessAttributeKind.Rc => VirtualRegisterBehavior.ReadClear,
                RegisterAccessAttributeKind.Reserved => VirtualRegisterBehavior.Reserved,
                _ => DefaultUnknown(defaultUnknownToRw, out limitation, out note)
            };
        }

        return key.ToUpperInvariant() switch
        {
            "RO" or "R" or "READ-ONLY" => VirtualRegisterBehavior.ReadOnly,
            "WO" or "W" or "WRITE-ONLY" => VirtualRegisterBehavior.WriteOnly,
            "RW" or "R/W" or "READ-WRITE" => VirtualRegisterBehavior.ReadWrite,
            "W1C" or "WC1" => VirtualRegisterBehavior.Write1Clear,
            "W0C" or "WC0" => VirtualRegisterBehavior.Write0Clear,
            "RC" or "RC_W0" or "RC_W1" => VirtualRegisterBehavior.ReadClear,
            "RESERVED" => VirtualRegisterBehavior.Reserved,
            _ => DefaultUnknown(defaultUnknownToRw, out limitation, out note)
        };
    }

    private static VirtualRegisterBehavior DefaultUnknown(
        bool defaultUnknownToRw,
        out SimulationLimitationKind limitation,
        out string note)
    {
        if (defaultUnknownToRw)
        {
            limitation = SimulationLimitationKind.UnknownAccessDefaultedToRw;
            note = "SDK access Unknown → 默认按 ReadWrite 模拟（可配置）";
            return VirtualRegisterBehavior.ReadWrite;
        }

        limitation = SimulationLimitationKind.SpecialWriteSemanticsNotDeclared;
        note = "SDK access Unknown → 拒绝写入（DefaultUnknownAccessToReadWrite=false）";
        return VirtualRegisterBehavior.ReadOnly;
    }

    public static uint ParseResetValue(string? text, out SimulationLimitationKind limitation)
    {
        limitation = SimulationLimitationKind.None;
        if (string.IsNullOrWhiteSpace(text))
        {
            limitation = SimulationLimitationKind.MissingResetValueAssumedZero;
            return 0;
        }

        var s = text.Trim();
        if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase)
            && uint.TryParse(s.AsSpan(2), System.Globalization.NumberStyles.HexNumber, null, out var hex))
            return hex;
        if (uint.TryParse(s, out var dec))
            return dec;

        limitation = SimulationLimitationKind.MissingResetValueAssumedZero;
        return 0;
    }

    /// <summary>
    /// Apply write semantics. Returns false if write rejected.
    /// </summary>
    public static bool TryApplyWrite(
        VirtualRegisterBehavior behavior,
        uint current,
        uint written,
        uint writableMask,
        uint widthMask,
        out uint next,
        out VirtualAccessResult result,
        out string? message)
    {
        written &= widthMask;
        next = current;
        result = VirtualAccessResult.Ok;
        message = null;

        switch (behavior)
        {
            case VirtualRegisterBehavior.Reserved:
                result = VirtualAccessResult.RejectedReserved;
                message = "保留寄存器不可写";
                return false;
            case VirtualRegisterBehavior.ReadOnly:
                result = VirtualAccessResult.RejectedReadOnly;
                message = "只读寄存器不可写";
                return false;
            case VirtualRegisterBehavior.WriteOnly:
            case VirtualRegisterBehavior.ReadWrite:
                next = (current & ~writableMask) | (written & writableMask);
                next &= widthMask;
                return true;
            case VirtualRegisterBehavior.Write1Clear:
                // bits written as 1 are cleared in storage
                next = current & ~(written & writableMask);
                next &= widthMask;
                return true;
            case VirtualRegisterBehavior.Write0Clear:
                // bits written as 0 are cleared; bits written as 1 keep current
                next = current & (written | ~writableMask);
                next &= widthMask;
                return true;
            case VirtualRegisterBehavior.ReadClear:
                // write still allowed as RW unless separately restricted
                next = (current & ~writableMask) | (written & writableMask);
                next &= widthMask;
                return true;
            default:
                result = VirtualAccessResult.Error;
                message = $"未支持的行为 {behavior}";
                return false;
        }
    }

    public static bool TryApplyRead(
        VirtualRegisterBehavior behavior,
        uint current,
        out uint readValue,
        out uint nextStored,
        out VirtualAccessResult result,
        out string? message)
    {
        readValue = current;
        nextStored = current;
        result = VirtualAccessResult.Ok;
        message = null;

        switch (behavior)
        {
            case VirtualRegisterBehavior.WriteOnly:
                result = VirtualAccessResult.RejectedWriteOnly;
                message = "只写寄存器不可读（返回 0 且不修改存储）";
                readValue = 0;
                return false;
            case VirtualRegisterBehavior.Reserved:
                result = VirtualAccessResult.RejectedReserved;
                message = "保留寄存器不可读";
                readValue = 0;
                return false;
            case VirtualRegisterBehavior.ReadClear:
                nextStored = 0;
                return true;
            default:
                return true;
        }
    }
}
