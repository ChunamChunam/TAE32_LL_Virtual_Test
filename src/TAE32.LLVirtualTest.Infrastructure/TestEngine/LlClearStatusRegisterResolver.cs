namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Maps LL Clear* functions to the status register they touch (from SDK inline bodies / module conventions).
/// Prefer WRITE_REG body parsing in LlTestCaseGenerator; this is a fallback only.
/// flagMask must be the target flag bits — never force 0xFFFF whole-register clear expectations.
/// </summary>
internal static class LlClearStatusRegisterResolver
{
    public static bool TryResolve(string functionName, string? peripheral, out string memberName, out uint flagMask)
    {
        memberName = "ISR";
        flagMask = 1u;
        var fn = functionName ?? string.Empty;
        var peri = peripheral ?? string.Empty;

        if (fn.Contains("ClearDataFlag", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("ClearFlag_DONx", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("ClearFlag_HLFx", StringComparison.OrdinalIgnoreCase)
            || fn.Contains("ClearFlag_FULx", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "DISR";
            flagMask = 1u;
            return true;
        }

        if (fn.Contains("DMA_Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "FISR";
            flagMask = 1u;
            return true;
        }

        if (peri.Contains("ADC", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("ClearFlag", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 1u;
            return true;
        }

        if (peri.Contains("GPIO", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("ClearIntPending", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 1u;
            return true;
        }

        if (peri.Contains("CMP", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 1u;
            return true;
        }

        if ((peri.Contains("IIR", StringComparison.OrdinalIgnoreCase)
             || peri.Contains("WWDG", StringComparison.OrdinalIgnoreCase))
            && fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            // WWDG EWIF = bit0; do not use 0xFFFF (that caused false Failed expecting whole ISR==0).
            flagMask = 1u;
            return true;
        }

        if (peri.Contains("IWDG", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "SR";
            flagMask = 1u;
            return true;
        }

        if (fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
            return true;

        return false;
    }

    public static int GpioPinBitIndex(uint pinMask)
    {
        if (pinMask == 0) return 0;
        var i = 0;
        while ((pinMask & 1u) == 0u && i < 31)
        {
            pinMask >>= 1;
            i++;
        }
        return i;
    }
}
