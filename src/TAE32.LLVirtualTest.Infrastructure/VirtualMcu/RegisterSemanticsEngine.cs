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
                RegisterAccessAttributeKind.W1s => VirtualRegisterBehavior.Write1Set,
                RegisterAccessAttributeKind.Toggle => VirtualRegisterBehavior.Toggle,
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
            "W1C" or "WC1" or "R/W1C" or "RW1C" => VirtualRegisterBehavior.Write1Clear,
            "W0C" or "WC0" or "R/W0C" => VirtualRegisterBehavior.Write0Clear,
            "W1S" or "WS1" => VirtualRegisterBehavior.Write1Set,
            "TOGGLE" or "W1T" => VirtualRegisterBehavior.Toggle,
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
    /// Per-bit access masks for a register. Unmapped bits stay in <see cref="BitAccessMasks.Unmapped"/>.
    /// </summary>
    public readonly record struct BitAccessMasks(
        uint Rw,
        uint Ro,
        uint Wo,
        uint W1c,
        uint W0c,
        uint W1s,
        uint Toggle,
        uint Reserved,
        uint Unmapped);

    /// <summary>
    /// Build bit-level masks from fields. Fields with Unknown inherit <paramref name="registerFallback"/>.
    /// </summary>
    public static BitAccessMasks BuildBitAccessMasks(
        IReadOnlyList<VirtualBitFieldSlot> fields,
        VirtualRegisterBehavior registerFallback,
        uint writableMask,
        uint widthMask)
    {
        uint rw = 0, ro = 0, wo = 0, w1c = 0, w0c = 0, w1s = 0, toggle = 0, reserved = 0, covered = 0;
        foreach (var f in fields)
        {
            var mask = f.Mask & widthMask;
            if (mask == 0) continue;
            covered |= mask;
            var behavior = ResolveFieldBehavior(f.AccessAttribute, registerFallback);
            Accumulate(behavior, mask, ref rw, ref ro, ref wo, ref w1c, ref w0c, ref w1s, ref toggle, ref reserved);
        }

        var unmapped = widthMask & ~covered;
        if (unmapped != 0 && fields.Count == 0)
        {
            // No fields: whole writable area follows register-level behavior.
            Accumulate(registerFallback, writableMask & widthMask,
                ref rw, ref ro, ref wo, ref w1c, ref w0c, ref w1s, ref toggle, ref reserved);
            unmapped = widthMask & ~(rw | ro | wo | w1c | w0c | w1s | toggle | reserved);
        }
        else if (unmapped != 0)
        {
            // Unmapped bits follow register-level behavior when writable; else reserved.
            var writableUnmapped = unmapped & writableMask;
            if (writableUnmapped != 0)
            {
                Accumulate(registerFallback, writableUnmapped,
                    ref rw, ref ro, ref wo, ref w1c, ref w0c, ref w1s, ref toggle, ref reserved);
                var still = unmapped & ~writableUnmapped;
                if (still != 0)
                    reserved |= still;
            }
            else
                reserved |= unmapped;
        }

        return new BitAccessMasks(rw, ro, wo, w1c, w0c, w1s, toggle, reserved, unmapped);
    }

    public static VirtualRegisterBehavior ResolveFieldBehavior(
        string? accessAttribute,
        VirtualRegisterBehavior registerFallback)
    {
        if (string.IsNullOrWhiteSpace(accessAttribute)
            || accessAttribute.Equals("Unknown", StringComparison.OrdinalIgnoreCase))
            return registerFallback;

        return ResolveBehavior(accessAttribute, defaultUnknownToRw: true, out _, out _);
    }

    private static void Accumulate(
        VirtualRegisterBehavior behavior,
        uint mask,
        ref uint rw, ref uint ro, ref uint wo,
        ref uint w1c, ref uint w0c, ref uint w1s, ref uint toggle, ref uint reserved)
    {
        switch (behavior)
        {
            case VirtualRegisterBehavior.ReadWrite:
                rw |= mask;
                break;
            case VirtualRegisterBehavior.ReadOnly:
                ro |= mask;
                break;
            case VirtualRegisterBehavior.WriteOnly:
                wo |= mask;
                break;
            case VirtualRegisterBehavior.Write1Clear:
                w1c |= mask;
                break;
            case VirtualRegisterBehavior.Write0Clear:
                w0c |= mask;
                break;
            case VirtualRegisterBehavior.Write1Set:
                w1s |= mask;
                break;
            case VirtualRegisterBehavior.Toggle:
                toggle |= mask;
                break;
            case VirtualRegisterBehavior.ReadClear:
                // RC flags are typically cleared on read; writes ignored → treat as RO for write path.
                ro |= mask;
                break;
            default:
                reserved |= mask;
                break;
        }
    }

    /// <summary>
    /// Apply write semantics. Prefer bit-level masks when fields declare mixed access;
    /// otherwise fall back to register-level <paramref name="behavior"/>.
    /// W1C: <c>next = current &amp; ~(written &amp; w1cMask)</c> (bit-wise; does not zero the whole register).
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
        => TryApplyWrite(behavior, fields: null, current, written, writableMask, widthMask,
            out next, out result, out message);

    public static bool TryApplyWrite(
        VirtualRegisterBehavior behavior,
        IReadOnlyList<VirtualBitFieldSlot>? fields,
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

        var useBitLevel = fields is { Count: > 0 }
                          || behavior is VirtualRegisterBehavior.Write1Clear
                              or VirtualRegisterBehavior.Write0Clear
                              or VirtualRegisterBehavior.Write1Set
                              or VirtualRegisterBehavior.Toggle;

        if (useBitLevel)
        {
            var masks = BuildBitAccessMasks(fields ?? Array.Empty<VirtualBitFieldSlot>(), behavior, writableMask, widthMask);
            return TryApplyWriteBitLevel(current, written, masks, widthMask, out next, out result, out message);
        }

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
            case VirtualRegisterBehavior.Write1Set:
                next = current | (written & writableMask);
                next &= widthMask;
                return true;
            case VirtualRegisterBehavior.Toggle:
                next = current ^ (written & writableMask);
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

    /// <summary>
    /// Bit-composed write: each access class applied independently within its mask.
    /// </summary>
    public static bool TryApplyWriteBitLevel(
        uint current,
        uint written,
        BitAccessMasks masks,
        uint widthMask,
        out uint next,
        out VirtualAccessResult result,
        out string? message)
    {
        result = VirtualAccessResult.Ok;
        message = null;
        written &= widthMask;
        next = current & widthMask;

        var writeAffecting = masks.Rw | masks.Wo | masks.W1c | masks.W0c | masks.W1s | masks.Toggle;
        if (writeAffecting == 0 && (masks.Ro | masks.Reserved) != 0)
        {
            // Entire register RO/Reserved
            if ((written & (masks.Ro | masks.Reserved)) != 0
                || written != (current & widthMask))
            {
                result = masks.Reserved != 0 && masks.Ro == 0
                    ? VirtualAccessResult.RejectedReserved
                    : VirtualAccessResult.RejectedReadOnly;
                message = result == VirtualAccessResult.RejectedReserved
                    ? "保留寄存器不可写"
                    : "只读寄存器不可写";
                return false;
            }
        }

        // RW / WO: assign
        var assignMask = (masks.Rw | masks.Wo) & widthMask;
        if (assignMask != 0)
            next = (next & ~assignMask) | (written & assignMask);

        // W1C: clear bits written as 1
        if (masks.W1c != 0)
            next &= ~(written & masks.W1c);

        // W0C: clear bits written as 0; writing 1 keeps current
        if (masks.W0c != 0)
            next = (next & ~masks.W0c) | (current & written & masks.W0c);

        // W1S: set bits written as 1
        if (masks.W1s != 0)
            next |= written & masks.W1s;

        // Toggle: flip bits written as 1
        if (masks.Toggle != 0)
            next ^= written & masks.Toggle;

        // RO / Reserved: keep current (already in next for those bits)
        var keepMask = (masks.Ro | masks.Reserved) & widthMask;
        if (keepMask != 0)
            next = (next & ~keepMask) | (current & keepMask);

        next &= widthMask;
        return true;
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
