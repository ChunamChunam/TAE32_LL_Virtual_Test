using FluentAssertions;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.SDK;

namespace TAE32.LLVirtualTest.Tests.Scan;

public class SdkScanTests
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
        throw new DirectoryNotFoundException("Workspace not found");
    }

    [Fact]
    public async Task Scan_RealSdk_WritesPhase1CompatibleJson()
    {
        var root = FindWorkspaceRoot();
        var sdk = Path.Combine(root, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
        var outDir = Path.Combine(Path.GetTempPath(), $"tae32_scan_{Guid.NewGuid():N}");

        var services = new ServiceCollection();
        services.AddLogging(b => b.AddDebug());
        services.AddSdkServices();
        // Scan service only needs logger; import/db not required
        await using var sp = services.BuildServiceProvider();
        // AddInfrastructure not needed for scan-only, but AddSdkServices registers scan+import.
        // Import needs DbContextFactory - so only resolve scan via manual construct if needed.
        var scan = sp.GetService<ISdkScanService>();
        if (scan is null)
        {
            // Fallback: register scan alone
            var sc = new ServiceCollection();
            sc.AddLogging(b => b.AddDebug());
            sc.AddSingleton<ISdkScanService, TAE32.LLVirtualTest.SDK.Scan.LlSdkScanService>();
            await using var sp2 = sc.BuildServiceProvider();
            scan = sp2.GetRequiredService<ISdkScanService>();
            var result = await scan.ScanAsync(sdk, outDir);
            AssertResult(result, outDir);
            return;
        }

        // AddSdkServices also registers Import which needs EF - GetRequiredService<ISdkScanService> might still work
        // because Scan doesn't need DB. But DI build of Import may pull factory...
        // Actually AddSdkServices only registers Singleton Scan and Import; Import ctor needs IDbContextFactory which isn't registered.
        // So BuildServiceProvider may succeed lazily. GetService<ISdkScanService> should work.
        {
            var sc = new ServiceCollection();
            sc.AddLogging(b => b.AddDebug());
            sc.AddSingleton<ISdkScanService, TAE32.LLVirtualTest.SDK.Scan.LlSdkScanService>();
            await using var sp2 = sc.BuildServiceProvider();
            var result = await sp2.GetRequiredService<ISdkScanService>().ScanAsync(sdk, outDir);
            AssertResult(result, outDir);
        }
    }

    private static void AssertResult(Core.Models.SdkScanResult result, string outDir)
    {
        result.Success.Should().BeTrue(result.Message);
        result.PeripheralCount.Should().BeGreaterThanOrEqualTo(20);
        result.FunctionCount.Should().BeGreaterThan(1000);
        result.InlineFunctionCount.Should().BeGreaterThan(1000);
        File.Exists(Path.Combine(outDir, "03_ChipDiscovery.json")).Should().BeTrue();
        File.Exists(Path.Combine(outDir, "04_PeripheralDiscovery.json")).Should().BeTrue();
        File.Exists(Path.Combine(outDir, "05_LLFunctionDiscovery.json")).Should().BeTrue();
        try { Directory.Delete(outDir, true); } catch { /* ignore */ }
    }
}
