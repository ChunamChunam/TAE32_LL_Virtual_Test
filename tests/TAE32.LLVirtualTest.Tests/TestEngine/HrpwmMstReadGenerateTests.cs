using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class HrpwmMstReadGenerateTests
{
    private static string? FindLlHrpwmHeader()
    {
        var relative = Path.Combine(
            "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0",
            "SDK", "Drivers", "TAE32G58xx_Driver", "LL", "tae32g58xx_ll_hrpwm.h");
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        for (var i = 0; i < 10 && dir is not null; i++, dir = dir.Parent)
        {
            var probe = Path.Combine(dir.FullName, relative);
            if (File.Exists(probe)) return probe;
        }

        var cwd = Path.Combine(Directory.GetCurrentDirectory(), relative);
        return File.Exists(cwd) ? cwd : null;
    }

    [Fact]
    public async Task Generate_IsBurstDMADisableAsserted_Emits_ReadChecks()
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        const string functionName = "LL_HRPWM_MST_IsBurstDMADisableAsserted";

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM_MST", ModuleName = "HRPWM", NaturalKey = "HRPWM_MST"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "uint32_t",
                Parameters = "const HRPWM_TypeDef *HRPWMx",
                Signature = $"uint32_t {functionName}(const HRPWM_TypeDef *HRPWMx)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "const HRPWM_TypeDef *", Position = 0, IsPointer = true
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().NotBeEmpty(
            because: "Names=" + string.Join("; ", cases.Select(c => c.Name)));
        reads.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName == "HRPWM_MST" && r.MemberName == "MCR1"));
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue));
        // Must include both 0 and 1 field samples for 1-bit BDMADIS.
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)));
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && string.Equals(a.ExpectedHex, "0x1", StringComparison.OrdinalIgnoreCase)));

        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_AllIntPnd_Get_Emits_Masked_ReadChecks_On_HrpwmMst_Misr()
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        const string functionName = "LL_HRPWM_Mst_AllIntPnd_Get";

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM", ModuleName = "HRPWM", NaturalKey = "HRPWM"
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM_MST", ModuleName = "HRPWM", NaturalKey = "HRPWM_MST"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "uint32_t",
                Parameters = "const HRPWM_TypeDef *HRPWMx",
                Signature = $"uint32_t {functionName}(const HRPWM_TypeDef *HRPWMx)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "const HRPWM_TypeDef *", Position = 0, IsPointer = true
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().NotBeEmpty(because: "Names=" + string.Join("; ", cases.Select(c => c.Name)));
        reads.Should().OnlyContain(c =>
            c.Name.Contains("HRPWM_MST", StringComparison.OrdinalIgnoreCase)
            && c.Name.Contains("MISR", StringComparison.OrdinalIgnoreCase));
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)));
        // Non-zero masked return sample must exist (partial or all flags).
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && !string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)));

        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_IsEnabledIT_Emits_MaskParam_ReadChecks_On_HrpwmMst_Mdier()
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        const string functionName = "LL_HRPWM_MST_IsEnabledIT";

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM", ModuleName = "HRPWM", NaturalKey = "HRPWM"
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM_MST", ModuleName = "HRPWM", NaturalKey = "HRPWM_MST"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "uint32_t",
                Parameters = "const HRPWM_TypeDef *HRPWMx, uint32_t Mask",
                Signature = $"uint32_t {functionName}(const HRPWM_TypeDef *HRPWMx, uint32_t Mask)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "const HRPWM_TypeDef *", Position = 0, IsPointer = true
                    },
                    new LlFunctionParameter
                    {
                        Name = "Mask", Type = "uint32_t", Position = 1, IsPointer = false
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().NotBeEmpty(
            because: "Names=" + string.Join("; ", cases.Select(c => c.Name + " | " + c.Notes)));
        reads.Should().NotContain(c => c.Name.EndsWith("/draft", StringComparison.OrdinalIgnoreCase));
        reads.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName == "HRPWM_MST" && r.MemberName == "MDIER"));
        reads.Should().Contain(c =>
            c.Parameters.Any(p =>
                p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase)
                && !string.Equals(p.ValueExpression, "0", StringComparison.Ordinal)));
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)));
        reads.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue
                                  && string.Equals(a.ExpectedHex, "0x1", StringComparison.OrdinalIgnoreCase)));

        await conn.DisposeAsync();
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
