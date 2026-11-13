using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestManagement;

namespace TAE32.LLVirtualTest.Tests.TestManagement;

public class TestManagementTests
{
    private static AppDbContext CreateDb()
    {
        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite($"Data Source={Path.Combine(Path.GetTempPath(), $"tae32_p7_{Guid.NewGuid():N}.db")}")
            .Options;
        var db = new AppDbContext(options);
        db.Database.EnsureCreated();
        return db;
    }

    private static IDbContextFactory<AppDbContext> FactoryFrom(AppDbContext seed)
    {
        var path = seed.Database.GetDbConnection().DataSource;
        return new TestDbFactory(path);
    }

    private sealed class TestDbFactory : IDbContextFactory<AppDbContext>
    {
        private readonly string _path;
        public TestDbFactory(string path) => _path = path;
        public AppDbContext CreateDbContext()
        {
            var options = new DbContextOptionsBuilder<AppDbContext>()
                .UseSqlite($"Data Source={_path}")
                .Options;
            return new AppDbContext(options);
        }
    }

    [Fact]
    public async Task Plan_Suite_CRUD_Uses_Real_Case_Ids()
    {
        await using var seed = CreateDb();
        var projectId = Guid.NewGuid();
        seed.SdkProjects.Add(new SdkProject
        {
            Id = projectId,
            Name = "P7",
            SdkRootPath = "x",
            Version = "2.0.0",
            IsActive = true
        });
        var caseId = Guid.NewGuid();
        seed.LlTestCases.Add(new LlTestCase
        {
            Id = caseId,
            SdkProjectId = projectId,
            Name = "GPIO_Write",
            FunctionName = "LL_GPIO_WritePin",
            Status = "Ready"
        });
        await seed.SaveChangesAsync();
        var factory = FactoryFrom(seed);

        var plans = new TestPlanStore(factory);
        var plan = await plans.UpsertAsync(new TestPlanEditModel
        {
            SdkProjectId = projectId,
            Name = "GPIO Plan",
            ChipModelName = "TAE32G58xx",
            PeripheralFilter = "GPIO",
            TestType = "VirtualMcu",
            SdkVersion = "2.0.0"
        });
        plan.Name.Should().Be("GPIO Plan");

        var suites = new TestSuiteStore(factory);
        var suite = await suites.UpsertAsync(new TestSuiteEditModel
        {
            SdkProjectId = projectId,
            TestPlanId = plan.Id,
            Name = "GPIO Suite",
            PeripheralName = "GPIO",
            TestCaseIds = { caseId }
        });
        var ids = await suites.GetCaseIdsAsync(suite.Id);
        ids.Should().ContainSingle().Which.Should().Be(caseId);

        var copy = await plans.DuplicateAsync(plan.Id);
        copy.Name.Should().Contain("副本");
        await plans.ArchiveAsync(plan.Id);
        var archived = await plans.GetAsync(plan.Id);
        archived!.Status.Should().Be("Archived");
    }

    [Fact]
    public async Task Coverage_Is_Null_When_No_Real_Data()
    {
        await using var seed = CreateDb();
        var projectId = Guid.NewGuid();
        seed.SdkProjects.Add(new SdkProject { Id = projectId, Name = "empty", SdkRootPath = "x", Version = "0" });
        await seed.SaveChangesAsync();

        var analytics = new TestAnalyticsService(FactoryFrom(seed));
        var cov = await analytics.GetCoverageAsync(projectId);
        cov.FunctionCoveragePercent.Should().BeNull();
        cov.PeripheralCoveragePercent.Should().BeNull();
        cov.RegisterAccessCoveragePercent.Should().BeNull();
        cov.BitFieldCoveragePercent.Should().BeNull();
        cov.CaseCoveragePercent.Should().BeNull();
        cov.Notes.Should().Contain("未生成覆盖率");
    }

    [Fact]
    public async Task Report_Contains_Disclaimer_And_Stats()
    {
        await using var seed = CreateDb();
        var projectId = Guid.NewGuid();
        seed.SdkProjects.Add(new SdkProject
        {
            Id = projectId,
            Name = "ReportProj",
            SdkRootPath = "x",
            Version = "2.0.0"
        });
        var caseId = Guid.NewGuid();
        seed.LlTestCases.Add(new LlTestCase
        {
            Id = caseId,
            SdkProjectId = projectId,
            Name = "c1",
            FunctionName = "LL_GPIO_Init",
            Status = "Ready"
        });
        seed.LlTestRuns.Add(new LlTestRun
        {
            Id = Guid.NewGuid(),
            SdkProjectId = projectId,
            LlTestCaseId = caseId,
            Status = nameof(LlTestRunStatus.Passed),
            CompileSucceeded = true,
            DurationMs = 12
        });
        await seed.SaveChangesAsync();

        var factory = FactoryFrom(seed);
        var analytics = new TestAnalyticsService(factory);
        var reports = new TestReportService(factory, analytics);
        var outDir = Path.Combine(Path.GetTempPath(), "tae32_p7_reports_" + Guid.NewGuid().ToString("N"));
        var result = await reports.GenerateAsync(new TestReportRequest
        {
            SdkProjectId = projectId,
            Format = TestReportFormat.Html,
            OutputDirectory = outDir,
            Title = "Unit Report"
        });

        File.Exists(result.FilePath).Should().BeTrue();
        var html = await File.ReadAllTextAsync(result.FilePath);
        html.Should().Contain("不等同于真实硬件");
        html.Should().Contain("Unit Report");
        html.Should().Contain("2.0.0");
        html.Should().Contain("通过 — 详细测试记录");
        html.Should().Contain("LL_GPIO_Init");
    }

    [Fact]
    public async Task Maintenance_Backup_And_Diagnostics()
    {
        await using var seed = CreateDb();
        var dbPath = seed.Database.GetDbConnection().DataSource;
        seed.SdkProjects.Add(new SdkProject { Id = Guid.NewGuid(), Name = "m", SdkRootPath = "x", Version = "1" });
        await seed.SaveChangesAsync();
        await seed.DisposeAsync();

        var logDir = Path.Combine(Path.GetTempPath(), "tae32_p7_logs_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(logDir);
        File.WriteAllText(Path.Combine(logDir, "old.log"), "x");
        File.SetLastWriteTimeUtc(Path.Combine(logDir, "old.log"), DateTime.UtcNow.AddDays(-30));

        var svc = new SystemMaintenanceService(new TestDbFactory(dbPath), dbPath, logDir);
        var backup = await svc.BackupDatabaseAsync();
        File.Exists(backup).Should().BeTrue();
        var diag = await svc.GetDiagnosticsSummaryAsync();
        diag.Should().Contain("Projects=1");
        var trimmed = await svc.TrimLogsAsync(TimeSpan.FromDays(14));
        trimmed.Should().BeGreaterThan(0);
    }
}
