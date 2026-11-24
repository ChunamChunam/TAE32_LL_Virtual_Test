using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ITestPlanStore
{
    Task<IReadOnlyList<TestPlan>> ListAsync(Guid sdkProjectId, bool includeArchived = false, CancellationToken ct = default);

    /// <param name="statusFilter">null/"全部"=Active+Archived; "Active"; "Archived".</param>
    Task<(IReadOnlyList<TestPlan> Items, int TotalCount)> ListPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        string? statusFilter = null,
        int skip = 0,
        int take = 50,
        CancellationToken ct = default);

    Task<TestPlan?> GetAsync(Guid id, CancellationToken ct = default);
    Task<TestPlan> UpsertAsync(TestPlanEditModel model, CancellationToken ct = default);
    Task<TestPlan> DuplicateAsync(Guid id, CancellationToken ct = default);
    Task ArchiveAsync(Guid id, CancellationToken ct = default);
    Task RestoreAsync(Guid id, CancellationToken ct = default);
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

    Task<(IReadOnlyList<TestBatchRun> Items, int TotalCount)> ListHistoryPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        Guid? planId = null,
        Guid? suiteId = null,
        int skip = 0,
        int take = 50,
        string? statusFilter = null,
        CancellationToken ct = default);

    Task<TestBatchRun?> GetAsync(Guid batchRunId, CancellationToken ct = default);

    /// <summary>Delete batch history rows (not individual LlTestRun records). Skips Running.</summary>
    Task<int> DeleteManyAsync(IEnumerable<Guid> ids, CancellationToken ct = default);

    /// <summary>Delete all batch rows for project matching the same filters as list/search. Skips Running.</summary>
    Task<int> DeleteFilteredAsync(
        Guid sdkProjectId,
        string? searchText = null,
        Guid? planId = null,
        Guid? suiteId = null,
        string? statusFilter = null,
        CancellationToken ct = default);
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

    /// <summary>
    /// 报告专用：批次内全部运行，或项目下「每个用例最新一次运行」（含 Passed 明细字段）。
    /// </summary>
    Task<IReadOnlyList<FailureAnalysisItem>> GetReportRunDetailsAsync(
        Guid sdkProjectId,
        Guid? batchRunId = null,
        TestReportRunScope runScope = TestReportRunScope.ProjectLatestPerCase,
        CancellationToken ct = default);

    /// <summary>报告页预览：批次登记条数 + 库中命中数 + 前若干条运行摘要（导出仍含全部）。</summary>
    Task<BatchExportPreviewModel?> GetBatchExportPreviewAsync(
        Guid batchRunId,
        int maxPreviewRows = 40,
        CancellationToken ct = default);

    Task<(IReadOnlyList<FailureAnalysisItem> Items, int TotalCount)> GetFailuresPagedAsync(
        Guid sdkProjectId,
        Guid? batchRunId = null,
        string? searchText = null,
        int skip = 0,
        int take = 50,
        string? statusFilter = null,
        CancellationToken ct = default);

    /// <summary>Load full failure detail (logs / traces) for the selected list row.</summary>
    Task<FailureAnalysisItem?> GetFailureDetailAsync(Guid runId, CancellationToken ct = default);

    /// <summary>Delete LlTestRun rows (Failed / Error / Timeout) matching the failure-analysis filters.</summary>
    Task<int> DeleteFailureRunsFilteredAsync(
        Guid sdkProjectId,
        Guid? batchRunId = null,
        string? searchText = null,
        string? statusFilter = null,
        CancellationToken ct = default);
}

public interface ISystemMaintenanceService
{
    Task<string> BackupDatabaseAsync(string? destinationDirectory = null, CancellationToken ct = default);
    Task RestoreDatabaseAsync(string backupFilePath, CancellationToken ct = default);

    /// <summary>Delete all application rows from SQLite (keeps schema/migrations). Returns pre-clear backup path if created.</summary>
    Task<string?> ClearAllDataAsync(CancellationToken ct = default);

    Task<int> TrimLogsAsync(TimeSpan olderThan, CancellationToken ct = default);
    Task<string> GetDiagnosticsSummaryAsync(CancellationToken ct = default);
}
