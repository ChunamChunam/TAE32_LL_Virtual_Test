using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

/// <summary>Real-SDK generation for nested Master.MCR0 MODIFY_REG (not timeout-only drafts).</summary>
public class HrpwmMstModifyRegGenerateTests
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

    [Theory]
    [InlineData("LL_HRPWM_MST_SetPrescaler", "Div")]
    [InlineData("LL_HRPWM_MST_SetCounterMode", "Mode")]
    public async Task Generate_Mst_ModifyReg_Emits_WriteChecks(string functionName, string paramName)
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull("real SDK ll_hrpwm.h must be present");

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            // Alphabetical COM first — reproducer for Take(2)/FirstOrDefault picking COM.
            foreach (var name in new[] { "HRPWM_COM", "HRPWM_MST", "HRPWM_SLV0" })
            {
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = Guid.NewGuid(), SdkProjectId = projectId, Name = name,
                    ModuleName = "HRPWM", NaturalKey = name
                });
            }

            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "void",
                Parameters = $"HRPWM_TypeDef *HRPWMx, uint32_t {paramName}",
                Signature = $"void {functionName}(HRPWM_TypeDef *HRPWMx, uint32_t {paramName})",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0, IsPointer = true },
                    new LlFunctionParameter { Name = paramName, Type = "uint32_t", Position = 1, IsPointer = false }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);

        cases.Should().NotBeEmpty();
        var writes = cases.Where(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        writes.Should().NotBeEmpty(
            because: "Master.MCR0 MODIFY_REG must auto-emit write-check, not timeout-only draft. Names="
                     + string.Join("; ", cases.Select(c => c.Name)));
        writes.Should().Contain(c => c.Name.Contains("HRPWM_MST", StringComparison.OrdinalIgnoreCase));
        writes.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue && a.MemberName == "MCR0"));

        await conn.DisposeAsync();
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
