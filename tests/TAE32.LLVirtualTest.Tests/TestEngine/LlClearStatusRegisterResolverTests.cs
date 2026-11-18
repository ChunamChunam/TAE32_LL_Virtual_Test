using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class LlClearStatusRegisterResolverTests
{
    [Theory]
    [InlineData("LL_ADC_ClearFlag_FULx", "ADC", "FISR")]
    [InlineData("LL_ADC_ClearFlag_HLFx", "ADC", "HISR")]
    [InlineData("LL_ADC_ClearFlag_DONx", "ADC", "DISR")]
    [InlineData("LL_ADC_ClearDataFlag", "ADC", "DISR")]
    [InlineData("LL_ADC_ClearFlag_EOC", "ADC", "ISR")]
    public void TryResolve_Maps_Adc_Clear_Targets(string fn, string peri, string member)
    {
        LlClearStatusRegisterResolver.TryResolve(fn, peri, out var mem, out var mask)
            .Should().BeTrue();
        mem.Should().Be(member);
        mask.Should().NotBe(0u);
    }
}
