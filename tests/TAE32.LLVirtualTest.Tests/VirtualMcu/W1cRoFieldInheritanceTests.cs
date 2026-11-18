using FluentAssertions;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class W1cRoFieldInheritanceTests
{
    [Fact]
    public void ApplyFieldInheritance_Upgrades_ReadOnly_Status_Flags_To_W1c()
    {
        var slot = new VirtualRegisterSlot
        {
            InstanceName = "ADC0",
            MemberName = "ISR",
            Behavior = VirtualRegisterBehavior.Write1Clear,
            WritableMask = 0xFFFF,
            WidthBits = 32
        };
        slot.Fields.Add(new VirtualBitFieldSlot
        {
            Name = "EOC", BitPosition = 0, BitWidth = 1, Mask = 0x1,
            AccessAttribute = "read-only"
        });
        slot.Fields.Add(new VirtualBitFieldSlot
        {
            Name = "ADRDY", BitPosition = 8, BitWidth = 1, Mask = 0x100,
            AccessAttribute = "Ro"
        });

        VirtualRegisterSemanticsOverrides.ApplyFieldInheritance(slot);

        slot.Fields[0].AccessAttribute.Should().Be("W1c");
        slot.Fields[1].AccessAttribute.Should().Be("W1c");

        RegisterSemanticsEngine.TryApplyWrite(
                VirtualRegisterBehavior.Write1Clear, slot.Fields,
                current: 0x101, written: 0x101,
                writableMask: 0xFFFF, widthMask: 0xFFFF,
                out var next, out _, out _)
            .Should().BeTrue();
        next.Should().Be(0u);
    }
}
