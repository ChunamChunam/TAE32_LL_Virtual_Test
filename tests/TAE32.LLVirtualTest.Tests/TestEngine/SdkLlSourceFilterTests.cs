using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class SdkLlSourceFilterTests
{
    [Fact]
    public void IsInlineAvailableInSdk_False_When_Inside_If_Zero()
    {
        var dir = Path.Combine(Path.GetTempPath(), "sdk_if0_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "t.h");
        try
        {
            File.WriteAllText(path, """
                #if 0
                __STATIC_INLINE void LL_DEMO_Disabled(DEMO_TypeDef *x) { (void)x; }
                #endif
                __STATIC_INLINE void LL_DEMO_Enabled(DEMO_TypeDef *x) { (void)x; }
                """);

            SdkLlSourceFilter.IsInlineAvailableInSdk(path, "LL_DEMO_Disabled").Should().BeFalse();
            SdkLlSourceFilter.IsInlineAvailableInSdk(path, "LL_DEMO_Enabled").Should().BeTrue();
        }
        finally
        {
            Directory.Delete(dir, true);
        }
    }
}
