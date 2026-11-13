using System.Runtime.InteropServices;
using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;
using Xunit;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class GpioBsrDorLogicTests
{
    [Theory]
    [InlineData(0x00000001u, 0u, 0x00000001u)] // Set pin0 (BSn at bit0)
    [InlineData(0x00000002u, 0u, 0x00000002u)] // Set pin1
    [InlineData(0x00010000u, 0x00000001u, 0x00000000u)] // Reset pin0 (BRn at bit16)
    [InlineData(0x00010001u, 0x00000002u, 0x00000002u)] // set0+reset0 on dor=pin1 → (2|1)&~1 = 2
    public void MergeBsrIntoDor_MatchesTae32Bsn0_BRn16(uint bsr, uint dor, uint expected)
    {
        GpioBsrDorLogic.MergeBsrIntoDor(bsr, dor).Should().Be(expected);
    }

    [Fact]
    public void ApplyHostGpioBsrToDor_PrefersDorOverOdr()
    {
        // Layout: BSR@0, DOR@8, ODR@56 (matches TAE32 GPIOA_Type offsets)
        const int size = 64;
        var ptr = Marshal.AllocHGlobal(size);
        try
        {
            for (var i = 0; i < size; i += 4)
                Marshal.WriteInt32(ptr, i, 0);

            Marshal.WriteInt32(ptr, 0, 0x00000001); // BSR = set pin0
            Marshal.WriteInt32(ptr, 8, 0);           // DOR
            Marshal.WriteInt32(ptr, 56, 0);          // ODR (must stay 0)

            var map = new Dictionary<int, string>
            {
                [0] = "BSR",
                [8] = "DOR",
                [56] = "ODR"
            };

            NativeTestHost.ApplyHostGpioBsrToDor(ptr, map);

            unchecked((uint)Marshal.ReadInt32(ptr, 8)).Should().Be(1u, "DOR should receive BSR set bits");
            unchecked((uint)Marshal.ReadInt32(ptr, 56)).Should().Be(0u, "ODR must not be used as data-out");
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }
}
