namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Maps LL Clear* functions to the status register they touch (from SDK inline bodies, not guessed per chip).
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
            return true;
        }

        if (fn.Contains("DMA_Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "FISR";
            flagMask = 0xFFFFu;
            return true;
        }

        if (peri.Contains("ADC", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("ClearFlag", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 0xFFFFu;
            return true;
        }

        if (peri.Contains("GPIO", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("ClearIntPending", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            return true;
        }

        if (peri.Contains("CMP", StringComparison.OrdinalIgnoreCase)
            && fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 0xFFFFu;
            return true;
        }

        if ((peri.Contains("IIR", StringComparison.OrdinalIgnoreCase)
             || peri.Contains("WWDG", StringComparison.OrdinalIgnoreCase))
            && fn.Contains("Clear", StringComparison.OrdinalIgnoreCase))
        {
            memberName = "ISR";
            flagMask = 0xFFFFu;
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
