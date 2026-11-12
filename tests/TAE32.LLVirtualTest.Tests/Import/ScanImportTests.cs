using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.SDK;

namespace TAE32.LLVirtualTest.Tests.Import;

public class ScanImportTests
{
    private static string FindWorkspaceRoot()
    {
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        while (dir is not null)
        {
            if (Directory.Exists(Path.Combine(dir.FullName, "ScanResults"))
                && Directory.Exists(Path.Combine(dir.FullName, "SDKContent")))
                return dir.FullName;
            dir = dir.Parent;
        }
        throw new DirectoryNotFoundException("Workspace root with ScanResults/SDKContent not found.");
    }

    private static ServiceProvider BuildServices(string dbPath)
    {
        var services = new ServiceCollection();
        services.AddLogging(b => b.AddDebug());
        services.AddInfrastructure(dbPath);
        services.AddSdkServices();
        return services.BuildServiceProvider();
    }

    [Fact]
    public async Task Import_RealScanResults_PersistsExpectedCounts()
    {
        var root = FindWorkspaceRoot();
        var sdkRoot = Path.Combine(root, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
        var scan = Path.Combine(root, "ScanResults");
        var dbPath = Path.Combine(Path.GetTempPath(), $"tae32_import_{Guid.NewGuid():N}.db");

        await using var sp = BuildServices(dbPath);
        var factory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
        await using (var db = await factory.CreateDbContextAsync())
            await db.Database.MigrateAsync();

        var projects = sp.GetRequiredService<ISdkProjectService>();
        var import = sp.GetRequiredService<IScanImportService>();
        var data = sp.GetRequiredService<IAppDataService>();

        var project = await projects.AddAsync("Test DFP", sdkRoot, scan);
        var result = await import.ImportAsync(project.Id);

        result.Success.Should().BeTrue(result.Message);
        result.ChipCount.Should().Be(1);
        result.PeripheralCount.Should().Be(23);
        result.FunctionCount.Should().Be(6879);

        var stats = await data.GetDashboardStatsAsync();
        stats.ChipCount.Should().Be(1);
        stats.PeripheralCount.Should().Be(23);
        stats.LlFunctionCount.Should().Be(6879);
        stats.InlineFunctionCount.Should().Be(3628);

        var chips = await data.GetChipsAsync();
        chips.Should().ContainSingle(c => c.ModelName == "TAE32G58xx");

        var peris = await data.GetPeripheralsAsync();
        peris.Select(p => p.Name).Should().Contain(new[] { "ADC", "UART", "LPTMR", "GPTMRX", "HRPWM" });

        var funcs = await data.GetFunctionsAsync(search: "LL_GPIO_SetPinOutputType", form: "inline_definition", take: 10);
        funcs.Should().NotBeEmpty();
        funcs[0].FilePath.Should().Contain("tae32g58xx_ll_gpio.h");
        funcs[0].StartLine.Should().BeGreaterThan(0);

        // Re-import should update without duplicating by natural key
        var again = await import.ImportAsync(project.Id);
        again.Success.Should().BeTrue();
        again.FunctionCount.Should().Be(6879);
        (await data.CountFunctionsAsync()).Should().Be(6879);

        try { File.Delete(dbPath); } catch { /* ignore */ }
    }

    [Fact]
    public async Task RemoveProject_DoesNotDeleteSdkFilesOnDisk()
    {
        var root = FindWorkspaceRoot();
        var sdkRoot = Path.Combine(root, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
        var scan = Path.Combine(root, "ScanResults");
        var markerCandidates = new[]
        {
            Path.Combine(sdkRoot, "LL", "tae32g58xx_ll_gpio.h"),
            Path.Combine(sdkRoot, "SDK", "Drivers", "TAE32G58xx_Driver", "LL", "tae32g58xx_ll_gpio.h")
        };
        var marker = markerCandidates.FirstOrDefault(File.Exists);
        marker.Should().NotBeNull("GPIO LL header should exist in DFP package");
        File.Exists(marker!).Should().BeTrue();

        var dbPath = Path.Combine(Path.GetTempPath(), $"tae32_remove_{Guid.NewGuid():N}.db");
        await using var sp = BuildServices(dbPath);
        var factory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
        await using (var db = await factory.CreateDbContextAsync())
            await db.Database.MigrateAsync();

        var projects = sp.GetRequiredService<ISdkProjectService>();
        var p = await projects.AddAsync("ToRemove", sdkRoot, scan);
        await projects.RemoveAsync(p.Id);

        File.Exists(marker).Should().BeTrue("removing project must not delete original SDK files");
        (await projects.GetAllAsync()).Should().BeEmpty();
        try { File.Delete(dbPath); } catch { /* ignore */ }
    }
}
