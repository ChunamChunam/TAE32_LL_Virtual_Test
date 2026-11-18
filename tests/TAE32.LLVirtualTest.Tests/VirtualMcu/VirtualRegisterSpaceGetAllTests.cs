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

    [Fact]
    public void GetAll_By_Module_ADC_Finds_Numbered_ADC0_Slots()
    {
        var space = new VirtualRegisterSpace();
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "ADC",
            InstanceName = "ADC0",
            StructName = "ADC0_Type",
            MemberName = "CFGR1",
            AbsoluteAddress = 0x40038008,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 0,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });
        // Legacy: ModuleName left as instance token; must still match host module "ADC".
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "ADC0",
            InstanceName = "ADC0",
            StructName = "ADC0_Type",
            MemberName = "CR",
            AbsoluteAddress = 0x40038000,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 0,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });

        var byModule = space.GetAll("ADC", null);
        byModule.Should().HaveCount(2);
        var byInst = space.GetAll("ADC", "ADC0");
        byInst.Should().HaveCount(2);
        byInst.Should().Contain(r => r.MemberName == "CFGR1" && r.AbsoluteAddress == 0x40038008u);
    }

    [Fact]
    public void Add_Prefers_Slot_With_AbsoluteAddress_On_Name_Collision()
    {
        var space = new VirtualRegisterSpace();
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "ADC",
            InstanceName = "ADC0",
            StructName = "ADC_TypeDef",
            MemberName = "CFGR1",
            AbsoluteAddress = null,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 1,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });
        space.Add(new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = "ADC",
            InstanceName = "ADC0",
            StructName = "ADC0_Type",
            MemberName = "CFGR1",
            AbsoluteAddress = 0x40038008,
            WidthBits = 32,
            Behavior = VirtualRegisterBehavior.ReadWrite,
            CurrentValue = 2,
            ResetValue = 0,
            WritableMask = 0xFFFFFFFFu
        });

        space.TryGetByName("ADC0", "CFGR1", out var view).Should().BeTrue();
        view!.AbsoluteAddress.Should().Be(0x40038008u);
        view.CurrentValue.Should().Be(2u);
    }
}
