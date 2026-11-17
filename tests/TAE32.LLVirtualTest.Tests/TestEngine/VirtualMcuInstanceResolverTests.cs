using FluentAssertions;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class VirtualMcuInstanceResolverTests
{
    [Fact]
    public void PreferInstance_Does_Not_Pick_Alphabetical_HRPWM_COM()
    {
        var regs = new List<VirtualRegisterView>
        {
            new() { InstanceName = "HRPWM_COM", MemberName = "CR", AbsoluteAddress = 0x4003BF00 },
            new() { InstanceName = "HRPWM_MST", MemberName = "MCR0", AbsoluteAddress = 0x4003B000 },
            new() { InstanceName = "HRPWM_SLV0", MemberName = "PWMCR0", AbsoluteAddress = 0x4003B100 },
        };

        VirtualMcuInstanceResolver.PreferInstance(regs, "HRPWM", "HRPWM", "LL_HRPWM_MST_SetPrescaler")
            .Should().Be("HRPWM_MST");
    }

    [Theory]
    [InlineData("LL_HRPWM_MST_SetCounterMode", "HRPWM_MST")]
    [InlineData("LL_HRPWM_COM_Enable", "HRPWM_COM")]
    [InlineData("LL_HRPWM_SLV_SetCompare", "HRPWM_SLV0")]
    public void InferBankInstance_From_Function_Name(string fn, string expected)
    {
        VirtualMcuInstanceResolver.InferBankInstance(fn, "HRPWM").Should().Be(expected);
    }

    [Fact]
    public void PreferInstance_Uses_COM_When_Function_Is_COM()
    {
        var regs = new List<VirtualRegisterView>
        {
            new() { InstanceName = "HRPWM_COM", MemberName = "CR", AbsoluteAddress = 0x4003BF00 },
            new() { InstanceName = "HRPWM_MST", MemberName = "MCR0", AbsoluteAddress = 0x4003B000 },
        };

        VirtualMcuInstanceResolver.PreferInstance(regs, "HRPWM", "HRPWM", "LL_HRPWM_COM_EnableIT")
            .Should().Be("HRPWM_COM");
    }
}
