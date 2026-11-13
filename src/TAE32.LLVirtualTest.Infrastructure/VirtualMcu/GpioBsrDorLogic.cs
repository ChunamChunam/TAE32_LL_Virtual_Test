namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal static class GpioBsrDorLogic
{
    /// <summary>
    /// STM32 BSRR: low 16 set, high 16 reset. TAE32 SetOutputPin may write only the upper half (PinMask &lt;&lt; BSn_Pos).
    /// </summary>
    public static uint MergeBsrIntoDor(uint bsr, uint dor)
    {
        var low = bsr & 0xFFFFu;
        var high = (bsr >> 16) & 0xFFFFu;
        if (low != 0u && high != 0u)
            return (dor | low) & ~high;
        if (high != 0u)
            return dor | high;
        if (low != 0u)
            return dor | low;
        return dor;
    }
}
