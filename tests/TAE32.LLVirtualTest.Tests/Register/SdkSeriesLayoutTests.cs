using FluentAssertions;
using TAE32.LLVirtualTest.Core.Sdk;
using TAE32.LLVirtualTest.SDK.Register;

namespace TAE32.LLVirtualTest.Tests.Register;

public class SdkSeriesLayoutTests
{
    private static string FindWorkspaceRoot()
    {
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        while (dir is not null)
        {
            if (Directory.Exists(Path.Combine(dir.FullName, "SDKContent")))
                return dir.FullName;
            dir = dir.Parent;
        }
        throw new DirectoryNotFoundException("Workspace root not found.");
    }

    [Fact]
    public void Discover_G58xx_FindsDeviceAndLl()
    {
        var root = Path.Combine(FindWorkspaceRoot(), "SDKContent",
            "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
        if (!Directory.Exists(root))
            return;

        var layout = SdkSeriesLayout.Discover(root);
        layout.Should().NotBeNull();
        layout!.FamilyId.Should().Be("tae32g58xx");
        layout.ChipModel.Should().Be("TAE32G58xx");
        layout.DeviceHeaderPath.Should().NotBeNullOrWhiteSpace();
        layout.ChipHeaderPath.Should().NotBeNullOrWhiteSpace();
        layout.LlRoot.Should().NotBeNullOrWhiteSpace();
        File.Exists(layout.DeviceHeaderPath!).Should().BeTrue();
        Directory.Exists(layout.LlRoot!).Should().BeTrue();

        var probe = new RegisterEnvironmentProbe().Probe(root);
        probe.HasAuthoritativeDeviceHeader.Should().BeTrue();
        probe.FamilyId.Should().Be("tae32g58xx");
        probe.MissingExpected.Should().BeEmpty();
    }

    [Fact]
    public void Discover_F561x_FindsDeviceAndLl()
    {
        var root = Path.Combine(FindWorkspaceRoot(), "SDKContent", "TAE32F561x_FW_AlphaV2.0.0");
        if (!Directory.Exists(root))
            return;

        var layout = SdkSeriesLayout.Discover(root);
        layout.Should().NotBeNull();
        layout!.FamilyId.Should().Be("tae32f561x");
        layout.DeviceHeaderPath.Should().EndWith("tae32f561x.h");
        layout.ChipHeaderPath.Should().NotBeNullOrWhiteSpace();
        layout.LlRoot.Should().NotBeNullOrWhiteSpace();
        layout.LlRoot!.Replace('\\', '/').Should().Contain("TAE32F561x_Driver/LL");

        var probe = new RegisterEnvironmentProbe().Probe(root);
        probe.HasAuthoritativeDeviceHeader.Should().BeTrue(string.Join("; ", probe.MissingExpected));
        probe.FamilyId.Should().Be("tae32f561x");
        probe.AuthoritativeDeviceHeader.Should().EndWith("tae32f561x.h");
        probe.MissingExpected.Should().BeEmpty();

        var modules = SdkSeriesLayout.EnumerateLlModuleHeaders(probe.LlRoot, probe.FamilyId);
        modules.Should().NotBeEmpty();
        modules.Should().Contain(p => Path.GetFileName(p).Equals("tae32f561x_ll_gpio.h", StringComparison.OrdinalIgnoreCase));
    }
}
