using System.Text.Json;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class TestAnalyticsService : ITestAnalyticsService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    public TestAnalyticsService(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task<TestStatistics> GetStatisticsAsync(Guid sdkProjectId, Guid? batchRunId = null, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var caseTotal = await db.LlTestCases.CountAsync(x => x.SdkProjectId == sdkProjectId, ct);

        IQueryable<Core.Entities.LlTestRun> runs = db.LlTestRuns.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId);
        if (batchRunId is Guid bid)
        {
            var batch = await db.TestBatchRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == bid, ct);
            var ids = batch is null
                ? new List<Guid>()
                : JsonSerializer.Deserialize<List<Guid>>(batch.CaseRunIdsJson) ?? new();
            runs = runs.Where(x => ids.Contains(x.Id));
        }

        var list = await runs.Select(x => new { x.Status, x.CompileSucceeded, x.DurationMs }).ToListAsync(ct);
        var stats = new TestStatistics
        {
            CaseTotal = caseTotal,
            ExecutedRuns = list.Count,
            Passed = list.Count(x => x.Status == nameof(LlTestRunStatus.Passed)),
            Failed = list.Count(x => x.Status == nameof(LlTestRunStatus.Failed)),
            Error = list.Count(x => x.Status == nameof(LlTestRunStatus.Error)),
            Skipped = list.Count(x => x.Status == nameof(LlTestRunStatus.Skipped)),
            Timeout = list.Count(x => x.Status == nameof(LlTestRunStatus.Timeout)),
            Cancelled = list.Count(x => x.Status == nameof(LlTestRunStatus.Cancelled)),
            CompileFailed = list.Count(x => !x.CompileSucceeded),
            AverageDurationMs = list.Count == 0 ? 0 : list.Average(x => x.DurationMs)
        };
        var decided = stats.Passed + stats.Failed + stats.Error + stats.Timeout;
        stats.PassRate = decided == 0 ? 0 : stats.Passed * 100.0 / decided;
        stats.CompileFailRate = list.Count == 0 ? 0 : stats.CompileFailed * 100.0 / list.Count;
        return stats;
    }

    public async Task<CoverageStats> GetCoverageAsync(Guid sdkProjectId, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var cov = new CoverageStats();

        var fnTotal = await db.LlFunctions.CountAsync(
            x => x.SdkProjectId == sdkProjectId && (x.Form == null || x.Form.Contains("inline")), ct);
        var coveredFns = await db.LlTestCases.AsNoTracking()
            .Where(c => c.SdkProjectId == sdkProjectId && c.LlFunctionId != null)
            .Select(c => c.LlFunctionId!.Value)
            .Distinct()
            .CountAsync(ct);
        cov.FunctionCoverageDenomination = "项目中 Form 含 inline 的 LL 函数（真实扫描/解析）";
        cov.FunctionsTotal = fnTotal;
        cov.FunctionsCoveredByCases = coveredFns;
        cov.FunctionCoveragePercent = fnTotal == 0 ? null : coveredFns * 100.0 / fnTotal;

        var periTotal = await db.Peripherals.CountAsync(x => x.SdkProjectId == sdkProjectId, ct);
        var periCovered = await db.LlTestCases.AsNoTracking()
            .Where(c => c.SdkProjectId == sdkProjectId && c.PeripheralName != null)
            .Select(c => c.PeripheralName!)
            .Distinct()
            .CountAsync(ct);
        cov.PeripheralCoverageDenomination = "项目外设模块表（真实导入）";
        cov.PeripheralsTotal = periTotal;
        cov.PeripheralsCoveredByCases = periCovered;
        cov.PeripheralCoveragePercent = periTotal == 0 ? null : periCovered * 100.0 / periTotal;

        var regsReferenced = await db.LlRegisterAccesses.AsNoTracking()
            .Where(r => r.LlFunction!.SdkProjectId == sdkProjectId
                        && r.RegisterPath != null && r.RegisterPath != "")
            .Select(r => r.RegisterPath!)
            .Distinct()
            .CountAsync(ct);
        // Touched registers: parse AccessTraceJson for member names is expensive; use runs with non-empty trace as proxy of "touched".
        var traces = await db.LlTestRuns.AsNoTracking()
            .Where(r => r.SdkProjectId == sdkProjectId && r.AccessTraceJson != null && r.AccessTraceJson != "[]")
            .Select(r => r.AccessTraceJson!)
            .Take(200)
            .ToListAsync(ct);
        var touched = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        foreach (var json in traces)
        {
            try
            {
                var recs = JsonSerializer.Deserialize<List<VirtualAccessRecord>>(json);
                if (recs is null) continue;
                foreach (var r in recs)
                    if (!string.IsNullOrWhiteSpace(r.RegisterName))
                        touched.Add(r.RegisterName);
            }
            catch { /* ignore bad json */ }
        }
        cov.RegisterAccessCoverageDenomination = "解析得到的寄存器引用名 vs 运行轨迹中出现的寄存器名（抽样最多 200 次运行）";
        cov.RegistersReferencedInParse = regsReferenced;
        cov.RegistersTouchedInRuns = touched.Count;
        cov.RegisterAccessCoveragePercent = regsReferenced == 0 ? null : Math.Min(100, touched.Count * 100.0 / regsReferenced);

        var bitFieldsTotal = await db.RegisterFields.AsNoTracking()
            .CountAsync(f => f.RegisterDefinition!.SdkProjectId == sdkProjectId, ct);
        var assertedBits = 0;
        var assertionJsons = await db.LlTestCases.AsNoTracking()
            .Where(c => c.SdkProjectId == sdkProjectId)
            .Select(c => c.AssertionsJson)
            .ToListAsync(ct);
        foreach (var aj in assertionJsons)
        {
            var specs = LlTestJson.DeserializeAssertions(aj);
            assertedBits += specs.Count(s => s.Kind == LlAssertionKind.BitField && !string.IsNullOrWhiteSpace(s.BitFieldName));
        }
        cov.BitFieldCoverageDenomination = "寄存器位域定义总数 vs 用例中 BitField 断言条数（非唯一位域名）";
        cov.BitFieldsTotal = bitFieldsTotal;
        cov.BitFieldsAsserted = assertedBits;
        cov.BitFieldCoveragePercent = bitFieldsTotal == 0 ? null : Math.Min(100, assertedBits * 100.0 / bitFieldsTotal);

        var casesTotal = await db.LlTestCases.CountAsync(c => c.SdkProjectId == sdkProjectId, ct);
        var casesExecuted = await db.LlTestRuns.AsNoTracking()
            .Where(r => r.SdkProjectId == sdkProjectId)
            .Select(r => r.LlTestCaseId)
            .Distinct()
            .CountAsync(ct);
        cov.CaseCoverageDenomination = "测试用例表总数 vs 至少执行过一次的用例数";
        cov.CasesTotal = casesTotal;
        cov.CasesExecutedAtLeastOnce = casesExecuted;
        cov.CaseCoveragePercent = casesTotal == 0 ? null : casesExecuted * 100.0 / casesTotal;

        if (fnTotal == 0 && periTotal == 0 && regsReferenced == 0 && bitFieldsTotal == 0 && casesTotal == 0)
            cov.Notes = "当前项目缺少可统计的真实数据，未生成覆盖率百分比。";

        return cov;
    }

    public async Task<IReadOnlyList<FailureAnalysisItem>> GetFailuresAsync(
        Guid sdkProjectId, Guid? batchRunId = null, int take = 100, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        IQueryable<Core.Entities.LlTestRun> q = db.LlTestRuns.AsNoTracking()
            .Include(x => x.TestCase)
            .Where(x => x.SdkProjectId == sdkProjectId
                        && (x.Status == nameof(LlTestRunStatus.Failed)
                            || x.Status == nameof(LlTestRunStatus.Error)
                            || x.Status == nameof(LlTestRunStatus.Timeout)));

        if (batchRunId is Guid bid)
        {
            var batch = await db.TestBatchRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == bid, ct);
            var ids = batch is null ? new List<Guid>() : JsonSerializer.Deserialize<List<Guid>>(batch.CaseRunIdsJson) ?? new();
            q = q.Where(x => ids.Contains(x.Id));
        }

        var rows = await q.OrderByDescending(x => x.StartedAtUtc).Take(take).ToListAsync(ct);
        return rows.Select(r =>
        {
            var regs = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
            try
            {
                var trace = JsonSerializer.Deserialize<List<VirtualAccessRecord>>(r.AccessTraceJson ?? "[]") ?? new();
                foreach (var t in trace)
                    if (!string.IsNullOrWhiteSpace(t.RegisterName))
                        regs.Add(t.RegisterName);
            }
            catch { /* ignore */ }

            return new FailureAnalysisItem
            {
                RunId = r.Id,
                TestCaseId = r.LlTestCaseId,
                CaseName = r.TestCase?.Name ?? "",
                FunctionName = r.TestCase?.FunctionName ?? "",
                SourceFile = r.TestCase?.SourceFile,
                Status = r.Status,
                FailureReason = r.FailureReason,
                CompileSucceeded = r.CompileSucceeded,
                CompileLogExcerpt = Truncate(r.CompileLog, 800),
                AssertionResultsJson = r.AssertionResultsJson,
                AccessTraceJson = Truncate(r.AccessTraceJson, 1200),
                RelatedRegisters = regs.Count == 0 ? null : string.Join(", ", regs.Take(20)),
                StartedAtUtc = r.StartedAtUtc
            };
        }).ToList();
    }

    private static string? Truncate(string? s, int max)
        => string.IsNullOrEmpty(s) ? s : s.Length <= max ? s : s[..max] + "…";
}
