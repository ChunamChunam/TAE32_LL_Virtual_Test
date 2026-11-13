using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.Services;

namespace TAE32.LLVirtualTest.Tests.Services;

public sealed class SdkSourcePathResolverTests
{
    [Fact]
    public void TryResolve_finds_header_under_repo_sdk_content()
    {
        var repo = FindRepoRoot();
        if (repo is null) return;

        var rel = @"SDKContent\Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0\SDK\Drivers\TAE32G58xx_Driver\LL\tae32g58xx_ll_gpio.h";
        SdkSourcePathResolver.TryResolve(rel, sdkRootPath: null, out var path).Should().BeTrue();
        path.Should().EndWith("tae32g58xx_ll_gpio.h");
        File.Exists(path).Should().BeTrue();
    }

    private static string? FindRepoRoot()
    {
        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 10 && !string.IsNullOrEmpty(dir); i++)
        {
            if (Directory.Exists(Path.Combine(dir, "SDKContent")))
                return dir;
            dir = Path.GetDirectoryName(dir);
        }
        return null;
    }
}
