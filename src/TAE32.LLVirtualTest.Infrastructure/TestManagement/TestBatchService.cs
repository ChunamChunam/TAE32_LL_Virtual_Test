using System.Reflection;
using System.Text.Json;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class TestBatchService : ITestBatchService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ILLTestEngine _engine;
    private readonly ITestSuiteStore _suites;
    private readonly ICompilerService _compiler;

    public TestBatchService(
        IDbContextFactory<AppDbContext> dbFactory,
        ILLTestEngine engine,
        ITestSuiteStore suites,
        ICompilerService compiler)
    {
        _dbFactory = dbFactory;
        _engine = engine;
        _suites = suites;
        _compiler = compiler;
    }

    public async Task<TestBatchRun> RunAsync(
        TestBatchRunRequest request,
        IProgress<TestBatchProgress>? progress = null,
        CancellationToken cancellationToken = default)
    {
        var caseIds = await ResolveCaseIdsAsync(request, cancellationToken);
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var project = await db.SdkProjects.AsNoTracking().FirstOrDefaultAsync(x => x.Id == request.SdkProjectId, cancellationToken)
                      ?? throw new InvalidOperationException("SDK 项目不存在");

        CompilerEnvironmentInfo? env = null;
        try { env = await _compiler.CheckEnvironmentAsync(request.SdkProjectId, cancellationToken); } catch { /* optional */ }

        var batch = new TestBatchRun
        {
            Id = Guid.NewGuid(),
            SdkProjectId = request.SdkProjectId,
            TestPlanId = request.TestPlanId,
            TestSuiteId = request.TestSuiteId,
            ScopeKind = request.ScopeKind,
            ScopeValue = request.ScopeValue,
            Status = "Running",
            ToolVersion = Assembly.GetExecutingAssembly().GetName().Version?.ToString() ?? "dev",
            CompilerVersion = env?.ClangVersion,
            SdkVersion = project.Version,
            ChipModelName = request.ScopeKind == "Chip" ? request.ScopeValue : null,
            TotalCount = caseIds.Count,
            LogDirectory = Path.Combine(Path.GetTempPath(), "tae32_ll_test_work", "batch"),
            StartedAtUtc = DateTime.UtcNow
        };
        db.TestBatchRuns.Add(batch);
        await db.SaveChangesAsync(cancellationToken);

        var runIds = new List<Guid>();
        var completed = 0;
        try
        {
            foreach (var caseId in caseIds)
            {
                cancellationToken.ThrowIfCancellationRequested();
                var caseName = await db.LlTestCases.AsNoTracking()
                    .Where(x => x.Id == caseId).Select(x => x.Name).FirstOrDefaultAsync(cancellationToken) ?? caseId.ToString();
                progress?.Report(new TestBatchProgress
                {
                    BatchRunId = batch.Id,
                    Total = caseIds.Count,
                    Completed = completed,
                    CurrentCaseName = caseName,
                    Message = $"执行 {caseName}（独立虚拟 MCU）"
                });

                var result = await _engine.RunCaseAsync(new LlTestRunRequest { TestCaseId = caseId }, null, cancellationToken);
                runIds.Add(result.RunId);
                completed++;
                ApplyStatus(batch, result.Status, result.CompileSucceeded);

                progress?.Report(new TestBatchProgress
                {
                    BatchRunId = batch.Id,
                    Total = caseIds.Count,
                    Completed = completed,
                    CurrentCaseName = caseName,
                    Message = $"{caseName} → {result.Status}"
                });
            }

            batch.Status = "Completed";
        }
        catch (OperationCanceledException)
        {
            batch.Status = "Cancelled";
            batch.CancelledCount++;
        }
        catch (Exception ex)
        {
            batch.Status = "Error";
            batch.Notes = ex.Message;
        }

        batch.CaseRunIdsJson = JsonSerializer.Serialize(runIds);
        batch.FinishedAtUtc = DateTime.UtcNow;
        if (runIds.Count > 0)
        {
            var durations = await db.LlTestRuns.AsNoTracking()
                .Where(x => runIds.Contains(x.Id))
                .Select(x => x.DurationMs)
                .ToListAsync(cancellationToken);
            batch.AverageDurationMs = durations.Count == 0 ? 0 : durations.Average();
        }

        await using (var db2 = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            db2.TestBatchRuns.Update(batch);
            await db2.SaveChangesAsync(cancellationToken);
        }

        return batch;
    }

    public async Task<IReadOnlyList<TestBatchRun>> ListHistoryAsync(
        Guid sdkProjectId, Guid? planId = null, Guid? suiteId = null, int take = 100, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = db.TestBatchRuns.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId);
        if (planId is Guid p) q = q.Where(x => x.TestPlanId == p);
        if (suiteId is Guid s) q = q.Where(x => x.TestSuiteId == s);
        return await q.OrderByDescending(x => x.StartedAtUtc).Take(take).ToListAsync(ct);
    }

    public async Task<(IReadOnlyList<TestBatchRun> Items, int TotalCount)> ListHistoryPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        Guid? planId = null,
        Guid? suiteId = null,
        int skip = 0,
        int take = 50,
        CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = ApplyHistoryFilters(db.TestBatchRuns.AsNoTracking(), sdkProjectId, planId, suiteId, searchText);
        var total = await q.CountAsync(ct);
        take = Math.Max(1, take);
        skip = Math.Max(0, skip);
        var items = await q.OrderByDescending(x => x.StartedAtUtc).Skip(skip).Take(take).ToListAsync(ct);
        return (items, total);
    }

    private static IQueryable<TestBatchRun> ApplyHistoryFilters(
        IQueryable<TestBatchRun> q,
        Guid sdkProjectId,
        Guid? planId,
        Guid? suiteId,
        string? searchText)
    {
        q = q.Where(x => x.SdkProjectId == sdkProjectId);
        if (planId is Guid p) q = q.Where(x => x.TestPlanId == p);
        if (suiteId is Guid s) q = q.Where(x => x.TestSuiteId == s);
        if (!string.IsNullOrWhiteSpace(searchText))
        {
            var term = searchText.Trim();
            q = q.Where(x =>
                x.Status.Contains(term) ||
                x.ScopeKind.Contains(term) ||
                (x.ScopeValue != null && x.ScopeValue.Contains(term)));
        }

        return q;
    }

    public async Task<TestBatchRun?> GetAsync(Guid batchRunId, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        return await db.TestBatchRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == batchRunId, ct);
    }

    public async Task<int> DeleteManyAsync(IEnumerable<Guid> ids, CancellationToken ct = default)
    {
        var idList = ids.Distinct().ToList();
        if (idList.Count == 0) return 0;

        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var rows = await db.TestBatchRuns
            .Where(x => idList.Contains(x.Id) && x.Status != "Running")
            .ToListAsync(ct);
        if (rows.Count == 0) return 0;
        db.TestBatchRuns.RemoveRange(rows);
        await db.SaveChangesAsync(ct);
        return rows.Count;
    }

    public async Task<int> DeleteFilteredAsync(
        Guid sdkProjectId,
        string? searchText = null,
        Guid? planId = null,
        Guid? suiteId = null,
        CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = ApplyHistoryFilters(db.TestBatchRuns, sdkProjectId, planId, suiteId, searchText)
            .Where(x => x.Status != "Running");
        var rows = await q.ToListAsync(ct);
        if (rows.Count == 0) return 0;
        db.TestBatchRuns.RemoveRange(rows);
        await db.SaveChangesAsync(ct);
        return rows.Count;
    }

    private async Task<List<Guid>> ResolveCaseIdsAsync(TestBatchRunRequest request, CancellationToken ct)
    {
        if (request.ExplicitCaseIds is { Count: > 0 })
            return request.ExplicitCaseIds.Distinct().ToList();

        await using var db = await _dbFactory.CreateDbContextAsync(ct);

        if (request.RetryFailedOnly && request.SourceBatchRunId is Guid srcId)
        {
            var src = await db.TestBatchRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == srcId, ct)
                      ?? throw new InvalidOperationException("源批次不存在");
            var runIds = JsonSerializer.Deserialize<List<Guid>>(src.CaseRunIdsJson) ?? new();
            return await db.LlTestRuns.AsNoTracking()
                .Where(r => runIds.Contains(r.Id)
                            && (r.Status == nameof(LlTestRunStatus.Failed)
                                || r.Status == nameof(LlTestRunStatus.Error)
                                || r.Status == nameof(LlTestRunStatus.Timeout)))
                .Select(r => r.LlTestCaseId)
                .Distinct()
                .ToListAsync(ct);
        }

        if (request.TestSuiteId is Guid suiteId)
            return (await _suites.GetCaseIdsAsync(suiteId, ct)).ToList();

        var q = db.LlTestCases.AsNoTracking().Where(c => c.SdkProjectId == request.SdkProjectId);
        switch (request.ScopeKind)
        {
            case "Peripheral" when !string.IsNullOrWhiteSpace(request.ScopeValue):
                q = q.Where(c => c.PeripheralName == request.ScopeValue);
                break;
            case "Chip" when !string.IsNullOrWhiteSpace(request.ScopeValue):
                q = q.Where(c => c.ChipModelName == request.ScopeValue);
                break;
            case "Plan" when request.TestPlanId is Guid planId:
            {
                var plan = await db.TestPlans.AsNoTracking().FirstOrDefaultAsync(x => x.Id == planId, ct);
                if (plan is null) break;
                // "(全部)" / null / empty → all peripherals; otherwise only that module.
                var peri = plan.PeripheralFilter;
                if (!string.IsNullOrWhiteSpace(peri)
                    && peri != "(全部)"
                    && peri != "全部")
                {
                    q = q.Where(c => c.PeripheralName == peri);
                }
                // Chip on plan is series label; do not drop cases with empty ChipModelName.
                if (!string.IsNullOrWhiteSpace(plan.ChipModelName))
                {
                    var chip = plan.ChipModelName;
                    q = q.Where(c => c.ChipModelName == null
                                     || c.ChipModelName == ""
                                     || c.ChipModelName == chip);
                }
                if (!string.IsNullOrWhiteSpace(plan.FunctionFilter))
                    q = q.Where(c => c.FunctionName.Contains(plan.FunctionFilter));
                break;
            }
            case "Plan" when string.Equals(request.ScopeValue, "(全部)", StringComparison.Ordinal)
                            || string.Equals(request.ScopeValue, "全部", StringComparison.Ordinal)
                            || string.IsNullOrWhiteSpace(request.ScopeValue):
                // No peripheral filter: all cases in project.
                break;
        }

        return await q.OrderBy(c => c.Name).Select(c => c.Id).ToListAsync(ct);
    }

    private static void ApplyStatus(TestBatchRun batch, LlTestRunStatus status, bool compileSucceeded)
    {
        if (!compileSucceeded) batch.CompileFailCount++;
        switch (status)
        {
            case LlTestRunStatus.Passed: batch.PassedCount++; break;
            case LlTestRunStatus.Failed: batch.FailedCount++; break;
            case LlTestRunStatus.Error: batch.ErrorCount++; break;
            case LlTestRunStatus.Skipped: batch.SkippedCount++; break;
            case LlTestRunStatus.Timeout: batch.TimeoutCount++; break;
            case LlTestRunStatus.Cancelled: batch.CancelledCount++; break;
        }
    }
}
