using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ITestPlanStore
{
    Task<IReadOnlyList<TestPlan>> ListAsync(Guid sdkProjectId, bool includeArchived = false, CancellationToken ct = default);
    Task<TestPlan?> GetAsync(Guid id, CancellationToken ct = default);
    Task<TestPlan> UpsertAsync(TestPlanEditModel model, CancellationToken ct = default);
    Task<TestPlan> DuplicateAsync(Guid id, CancellationToken ct = default);
    Task ArchiveAsync(Guid id, CancellationToken ct = default);
    Task DeleteAsync(Guid id, CancellationToken ct = default);
}

public interface ITestSuiteStore
{
    Task<IReadOnlyList<TestSuite>> ListAsync(Guid sdkProjectId, Guid? planId = null, CancellationToken ct = default);
    Task<TestSuite?> GetAsync(Guid id, CancellationToken ct = default);
    Task<TestSuite> UpsertAsync(TestSuiteEditModel model, CancellationToken ct = default);
    Task DeleteAsync(Guid id, CancellationToken ct = default);
    Task<IReadOnlyList<Guid>> GetCaseIdsAsync(Guid suiteId, CancellationToken ct = default);
}

public interface ITestBatchService
{
    Task<TestBatchRun> RunAsync(
        TestBatchRunRequest request,
        IProgress<TestBatchProgress>? progress = null,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<TestBatchRun>> ListHistoryAsync(
        Guid sdkProjectId,
        Guid? planId = null,
        Guid? suiteId = null,
        int take = 100,
        CancellationToken ct = default);

    Task<TestBatchRun?> GetAsync(Guid batchRunId, CancellationToken ct = default);
}

public interface ITestAnalyticsService
{
    Task<TestStatistics> GetStatisticsAsync(Guid sdkProjectId, Guid? batchRunId = null, CancellationToken ct = default);
    Task<CoverageStats> GetCoverageAsync(Guid sdkProjectId, CancellationToken ct = default);
    Task<IReadOnlyList<FailureAnalysisItem>> GetFailuresAsync(
        Guid sdkProjectId,
        Guid? batchRunId = null,
        int take = 100,
        CancellationToken ct = default);
}

public interface ISystemMaintenanceService
{
    Task<string> BackupDatabaseAsync(string? destinationDirectory = null, CancellationToken ct = default);
    Task RestoreDatabaseAsync(string backupFilePath, CancellationToken ct = default);
    Task<int> TrimLogsAsync(TimeSpan olderThan, CancellationToken ct = default);
    Task<string> GetDiagnosticsSummaryAsync(CancellationToken ct = default);
}
