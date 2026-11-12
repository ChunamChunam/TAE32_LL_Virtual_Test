using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.SDK;

namespace TAE32.LLVirtualTest.Tests.Register;

public class RegisterParseTests
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
        throw new DirectoryNotFoundException("Workspace root not found.");
    }

    private static async Task<(ServiceProvider Sp, Guid ProjectId)> SetupImportedProjectAsync()
    {
        var root = FindWorkspaceRoot();
        var sdkRoot = Path.Combine(root, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
        var scan = Path.Combine(root, "ScanResults");
        var dbPath = Path.Combine(Path.GetTempPath(), $"tae32_reg_{Guid.NewGuid():N}.db");

        var services = new ServiceCollection();
        services.AddLogging(b => b.AddDebug());
        services.AddInfrastructure(dbPath);
        services.AddSdkServices();
        var sp = services.BuildServiceProvider();

        var factory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
        await using (var db = await factory.CreateDbContextAsync())
            await db.Database.MigrateAsync();

        var projects = sp.GetRequiredService<ISdkProjectService>();
        var import = sp.GetRequiredService<IScanImportService>();
        var project = await projects.AddAsync("Reg Parse Test", sdkRoot, scan);
        var importResult = await import.ImportAsync(project.Id);
        importResult.Success.Should().BeTrue(importResult.Message);

        return (sp, project.Id);
    }

    [Fact]
    public async Task Parse_WithFullDfp_UsesDeviceHeader_ConfirmsGpioOffsets()
    {
        var (sp, projectId) = await SetupImportedProjectAsync();
        await using (sp)
        {
            var parser = sp.GetRequiredService<IRegisterParser>();
            var summary = await parser.ParseAsync(projectId);

            summary.UsedDeviceHeader.Should().BeTrue(summary.Message);
            summary.UsedParseBridgeEvidenceOnly.Should().BeFalse();
            summary.InstanceCount.Should().BeGreaterThan(0);
            summary.RegisterCount.Should().BeGreaterThan(0);
            summary.MissingHeaders.Should().BeEmpty();

            var factory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
            await using var db = await factory.CreateDbContextAsync();

            var gpioa = await db.PeripheralInstances.FirstOrDefaultAsync(x =>
                x.SdkProjectId == projectId && x.Name == "GPIOA");
            gpioa.Should().NotBeNull();
            gpioa!.BaseAddress.Should().Be(0x40024000u);
            gpioa.BaseAddressStatus.Should().Be(AddressConfirmationStatus.Confirmed.ToString());

            var odr = await db.RegisterDefinitions.FirstOrDefaultAsync(x =>
                x.SdkProjectId == projectId
                && x.StructName == "GPIOA_Type"
                && x.MemberName == "ODR");
            odr.Should().NotBeNull();
            odr!.OffsetBytes.Should().Be(0x38);
            odr.OffsetStatus.Should().Be(AddressConfirmationStatus.Confirmed.ToString());
            odr.AbsoluteAddress.Should().Be(0x40024000u + 0x38u);
            odr.AbsoluteAddressStatus.Should().Be(AddressConfirmationStatus.Confirmed.ToString());
            odr.AccessAttribute.Should().Be(RegisterAccessAttributeKind.Rw.ToString());
            odr.WidthBits.Should().Be(32);
        }
    }

    [Fact]
    public async Task Parse_Resolves_GpioPosMsk_FromChipHeader()
    {
        var (sp, projectId) = await SetupImportedProjectAsync();
        await using (sp)
        {
            var parser = sp.GetRequiredService<IRegisterParser>();
            _ = await parser.ParseAsync(projectId);

            var factory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
            await using var db = await factory.CreateDbContextAsync();

            var macros = await db.RegisterMacroReferences
                .Where(x => x.SdkProjectId == projectId && x.MacroName == "GPIOA_BSR_BSn_Pos")
                .ToListAsync();
            macros.Should().NotBeEmpty();
            macros.Should().Contain(m => m.Resolved);
        }
    }
}
