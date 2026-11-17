using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class ClangHostCrtIncludeTests
{
    [Fact]
    public void ResolveHostCrtIncludePaths_Finds_StringH_When_WindowsSdk_Present()
    {
        if (!OperatingSystem.IsWindows())
            return;

        var paths = ClangCompilerService.ResolveHostCrtIncludePaths();
        // Machines without VS/Windows SDK (like some CI images) may return empty — soft skip.
        if (paths.Count == 0)
            return;

        paths.Should().Contain(p => File.Exists(Path.Combine(p, "string.h")));
    }

    [Fact]
    public void EmbeddedHostCrtIncludeDirectory_Ships_StringH()
    {
        var crt = ClangCompilerService.EmbeddedHostCrtIncludeDirectory();
        crt.Should().NotBeNull("HostSdk/crt must ship with the app so string.h works without Windows SDK");
        File.Exists(Path.Combine(crt!, "string.h")).Should().BeTrue();
        File.Exists(Path.Combine(crt!, "stdint.h")).Should().BeTrue();
        File.Exists(Path.Combine(crt!, "stddef.h")).Should().BeTrue();
        ClangCompilerService.EmbeddedHostCrtSourcePath().Should().NotBeNull();
        File.Exists(ClangCompilerService.EmbeddedHostCrtSourcePath()!).Should().BeTrue();
    }

    [Fact]
    public void ResolveMsvcLibraryPaths_When_Present_Contains_Libcmt()
    {
        if (!OperatingSystem.IsWindows())
            return;

        var paths = ClangCompilerService.ResolveMsvcLibraryPaths();
        if (paths.Count == 0)
            return; // no VS Build Tools — freestanding link path is used instead

        paths.Should().Contain(p => File.Exists(Path.Combine(p, "libcmt.lib")));
    }
}
