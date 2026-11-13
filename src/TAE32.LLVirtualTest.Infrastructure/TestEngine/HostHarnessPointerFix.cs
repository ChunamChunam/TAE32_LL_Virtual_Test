using System.Text.RegularExpressions;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Vendor LL REG_OFFSET macros double-cast &amp;(__REG__) to uint32_t; on Win64 that truncates pointers → AVE.
/// </summary>
internal static class HostHarnessPointerFix
{
    private static readonly Regex TruncatedAddressOf = new(
        @"\(\(uint32_t\)\s*\(\(uint32_t\)\(&",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    public static string Apply(string preprocessed)
    {
        var s = TruncatedAddressOf.Replace(preprocessed, "((uintptr_t)(&");
        // Drop the extra ')' from the removed inner uint32_t cast before REG_OFFSET '+ ...'
        s = s.Replace(")) + (((", ") + (((", StringComparison.Ordinal);
        s = s.Replace(")) + ((", ") + ((", StringComparison.Ordinal);
        s = s.Replace("0x40023048UL", "(uintptr_t)&tae32_host_eflash_chip_size_mode", StringComparison.Ordinal);
        return s;
    }
}
