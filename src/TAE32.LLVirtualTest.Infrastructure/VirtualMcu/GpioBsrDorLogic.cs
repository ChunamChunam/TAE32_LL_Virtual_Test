namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal static class GpioBsrDorLogic
{
    /// <summary>
    /// TAE32 BSR (chip.h): BSn_Pos=0 (low 16 = set), BRn_Pos=16 (high 16 = reset).
    /// Same layout as STM32 BSRR. Apply: DOR = (DOR | set) &amp; ~reset.
    /// </summary>
    public static uint MergeBsrIntoDor(uint bsr, uint dor)
    {
        var setBits = bsr & 0xFFFFu;
        var resetBits = (bsr >> 16) & 0xFFFFu;
        return (dor | setBits) & ~resetBits;
    }
}
