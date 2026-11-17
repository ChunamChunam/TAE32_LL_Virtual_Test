using FluentAssertions;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class VirtualRegisterSpaceGetAllTests
{
    [Fact]
    public void GetAll_By_Module_HRPWM_Finds_Legacy_HRPWM_MST_Slots()
    {
        var space = new VirtualRegisterSpace();
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "HRPWM_MST", // legacy bank-as-module
            InstanceName = "HRPWM_MST",
            StructName = "HRPWM_MST_Type",
            MemberName = "MCR0",
            AbsoluteAddress = 0x4003B000,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 0,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "HRPWM_SLV0",
            InstanceName = "HRPWM_SLV0",
            StructName = "HRPWM_SLV_Type",
            MemberName = "PWMCR0",
            AbsoluteAddress = 0x4003B100,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 0,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });

        var regs = space.GetAll("HRPWM", null);
        regs.Should().HaveCount(2);
        regs.Should().Contain(r => r.InstanceName == "HRPWM_MST" && r.MemberName == "MCR0");
        regs.Should().Contain(r => r.AbsoluteAddress == 0x4003B000u);
    }
}
