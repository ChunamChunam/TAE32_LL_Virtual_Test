using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class InferModuleNormalizeTests
{
    [Theory]
    [InlineData("HRPWM_MST", "HRPWM")]
    [InlineData("HRPWM_SLV0", "HRPWM")]
    [InlineData("HRPWM_COM", "HRPWM")]
    [InlineData("HRPWM_MST_Type", "HRPWM")]
    [InlineData("ADC0", "ADC")]
    [InlineData("GPIOA", "GPIO")]
    [InlineData("TMR9", "TMR")]
    [InlineData("HRPWM", "HRPWM")]
    public void NormalizeModuleToken_Collapses_Banked_Names(string input, string expected)
    {
        // Strip _Type suffix the same way InferModule does before normalize for struct names.
        var token = input.EndsWith("_Type", StringComparison.Ordinal)
            ? input[..^5]
            : input;
        VirtualMcuDefinitionLoader.NormalizeModuleToken(token).Should().Be(expected);
    }

    [Theory]
    [InlineData("DMA0_Type", "DMA0")]
    [InlineData("FLASH_Type", "FLASH")]
    [InlineData("EFLASH_TypeDef", "FLASH")]
    [InlineData("HRPWM_MST_Type", "HRPWM_MST")]
    [InlineData("HRPWM_SLV0_Type", "HRPWM_SLV0")]
    public void InferInstanceFromStruct_Maps_Orphan_Structs(string structName, string expected)
    {
        VirtualMcuDefinitionLoader.InferInstanceFromStruct(structName).Should().Be(expected);
    }
}
