using FluentAssertions;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class NativeTestHostHrpwmImageTests
{
    [Fact]
    public void ResolveAggregateImageBase_Prefers_Hrpwm_Mst_Bank()
    {
        var regs = new List<VirtualRegisterView>
        {
            new() { InstanceName = "HRPWM_SLV0", MemberName = "PWMCR0", AbsoluteAddress = 0x4003B100 },
            new() { InstanceName = "HRPWM_MST", MemberName = "MCR0", AbsoluteAddress = 0x4003B000 },
            new() { InstanceName = "HRPWM_COM", MemberName = "CR", AbsoluteAddress = 0x4003BF00 },
        };

        var bas = NativeTestHost.ResolveAggregateImageBase("HRPWM", "HRPWM_MST", regs);
        bas.Should().Be(0x4003B000u);
        var mcr0Off = (int)(0x4003B000u - bas);
        var pwm0Off = (int)(0x4003B100u - bas);
        mcr0Off.Should().Be(0, "Master.MCR0 offsetof must be 0");
        pwm0Off.Should().Be(0x100, "PWM[0] starts at 0x100 in HRPWM_TypeDef");
    }

    [Fact]
    public void ResolveAggregateImageBase_Ignores_Outlier_Low_Address()
    {
        // A stale AbsoluteAddress of 0 must not become the TypeDef image base.
        var regs = new List<VirtualRegisterView>
        {
            new() { InstanceName = "HRPWM_MST", MemberName = "MCR0", AbsoluteAddress = 0x4003B000 },
            new() { InstanceName = "HRPWM_SLV0", MemberName = "PWMCR0", AbsoluteAddress = 0x4003B100 },
        };

        NativeTestHost.ResolveAggregateImageBase("HRPWM", "HRPWM", regs)
            .Should().Be(0x4003B000u);
    }

    [Fact]
    public void AnalyzeBufferDeltas_Reports_Unmapped_Native_Writes()
    {
        const int size = 256;
        var ptr = System.Runtime.InteropServices.Marshal.AllocHGlobal(size);
        try
        {
            for (var i = 0; i < size; i += 4)
                System.Runtime.InteropServices.Marshal.WriteInt32(ptr, i, 0);

            // Map only a far slot; native TypeDef write hits offset 0 (Master.MCR0).
            var map = new Dictionary<int, string> { [0x100] = "HRPWM_SLV0::PWMCR0" };
            var before = new Dictionary<int, uint> { [0] = 0, [0x100] = 0 };
            System.Runtime.InteropServices.Marshal.WriteInt32(ptr, 0, unchecked((int)0xA5A55A5Au));

            var report = NativeTestHost.AnalyzeBufferDeltas(ptr, size, map, before, 0x4003B000);
            report.HasUnmappedWrites.Should().BeTrue();
            report.UnmappedChanges.Should().Contain(d => d.Offset == 0 && d.After == 0xA5A55A5Au);
            report.HasMappedWrites.Should().BeFalse();
        }
        finally
        {
            System.Runtime.InteropServices.Marshal.FreeHGlobal(ptr);
        }
    }
}
