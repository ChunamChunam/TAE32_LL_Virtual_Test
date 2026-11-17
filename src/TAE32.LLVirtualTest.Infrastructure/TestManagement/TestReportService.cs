using System.Globalization;
using System.IO;
using System.Reflection;
using System.Text;
using System.Text.Json;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class TestReportService : ITestReportService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ITestAnalyticsService _analytics;

    public TestReportService(IDbContextFactory<AppDbContext> dbFactory, ITestAnalyticsService analytics)
    {
        _dbFactory = dbFactory;
        _analytics = analytics;
    }

    public async Task GenerateAsync(Guid runId, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var run = await db.LlTestRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == runId, cancellationToken)
                  ?? throw new KeyNotFoundException("运行记录不存在");
        await GenerateAsync(new TestReportRequest
        {
            SdkProjectId = run.SdkProjectId,
            Format = TestReportFormat.Html,
            Title = $"单次运行报告 {runId:N}"
        }, cancellationToken);
    }

    public async Task<TestReportResult> GenerateAsync(TestReportRequest request, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var project = await db.SdkProjects.AsNoTracking().FirstOrDefaultAsync(x => x.Id == request.SdkProjectId, cancellationToken)
                      ?? throw new InvalidOperationException("SDK 项目不存在");
        var effectiveScope = ResolveEffectiveRunScope(request);
        var statsBatchId = effectiveScope == TestReportRunScope.SelectedBatchOnly ? request.BatchRunId : ResolveStatsBatchId(request);
        var stats = await _analytics.GetStatisticsAsync(request.SdkProjectId, statsBatchId, cancellationToken);
        var coverage = await _analytics.GetCoverageAsync(request.SdkProjectId, cancellationToken);
        var runDetails = await _analytics.GetReportRunDetailsAsync(
            request.SdkProjectId, request.BatchRunId, effectiveScope, cancellationToken);
        var failures = runDetails
            .Where(x => x.Status is nameof(LlTestRunStatus.Failed)
                or nameof(LlTestRunStatus.Error)
                or nameof(LlTestRunStatus.Timeout))
            .ToList();
        var skippedDetails = runDetails
            .Where(x => x.Status == nameof(LlTestRunStatus.Skipped))
            .ToList();
        var passedDetails = runDetails
            .Where(x => x.Status == nameof(LlTestRunStatus.Passed))
            .ToList();
        TestBatchRun? batch = null;
        if (effectiveScope == TestReportRunScope.SelectedBatchOnly && request.BatchRunId is Guid bid)
            batch = await db.TestBatchRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == bid, cancellationToken);

        var outDir = string.IsNullOrWhiteSpace(request.OutputDirectory)
            ? Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
                "TAE32.LLVirtualTest", "reports")
            : request.OutputDirectory!;
        Directory.CreateDirectory(outDir);

        var stamp = DateTime.Now.ToString("yyyyMMdd_HHmmss", CultureInfo.InvariantCulture);
        var title = string.IsNullOrWhiteSpace(request.Title)
            ? $"TAE32 LL Virtual Test Report {stamp}"
            : request.Title!;
        var disclaimer = "本报告基于虚拟 MCU 的软件测试结果，不等同于真实硬件测试验证。";

        string path;
        string format;
        switch (request.Format)
        {
            case TestReportFormat.Csv:
            case TestReportFormat.Excel:
                path = Path.Combine(outDir, $"report_{stamp}.csv");
                await File.WriteAllTextAsync(path, BuildCsv(project, batch, stats, runDetails), Encoding.UTF8, cancellationToken);
                format = request.Format == TestReportFormat.Excel ? "Excel" : "Csv";
                break;
            case TestReportFormat.Pdf:
                // Lightweight printable HTML saved as .pdf.html (open in browser → 打印为 PDF).
                path = Path.Combine(outDir, $"report_{stamp}.pdf.html");
                await File.WriteAllTextAsync(path,
                    BuildHtml(title, disclaimer, project, batch, effectiveScope, stats, coverage, runDetails, failures, skippedDetails, passedDetails, printable: true),
                    Encoding.UTF8, cancellationToken);
                format = "Pdf";
                break;
            default:
                path = Path.Combine(outDir, $"report_{stamp}.html");
                await File.WriteAllTextAsync(path,
                    BuildHtml(title, disclaimer, project, batch, effectiveScope, stats, coverage, runDetails, failures, skippedDetails, passedDetails, printable: false),
                    Encoding.UTF8, cancellationToken);
                format = "Html";
                break;
        }

        var artifact = new TestReportArtifact
        {
            Id = Guid.NewGuid(),
            SdkProjectId = request.SdkProjectId,
            TestBatchRunId = request.BatchRunId,
            Format = format,
            FilePath = path,
            Title = title,
            Disclaimer = disclaimer,
            CreatedAtUtc = DateTime.UtcNow
        };
        db.TestReportArtifacts.Add(artifact);
        await db.SaveChangesAsync(cancellationToken);

        var countMsg = runDetails.Count > 0
            ? $"共 {runDetails.Count} 条运行明细（本报告无条数上限，与所选批次 CaseRunIds 一一对应）。"
            : "未包含运行明细（请检查导出范围或批次是否为空）。";
        if (batch is not null && batch.TotalCount > runDetails.Count)
            countMsg += $" 提示：批次 TotalCount={batch.TotalCount}，实际载入 {runDetails.Count} 条（若有缺口，可能是部分 LlTestRun 已从库中删除）。";
        return new TestReportResult
        {
            ArtifactId = artifact.Id,
            Format = format,
            FilePath = path,
            EffectiveRunScope = effectiveScope,
            RunDetailCount = runDetails.Count,
            BatchExpectedRunCount = batch?.TotalCount,
            Message = (format == "Pdf"
                ? $"已生成可打印 HTML（请用浏览器打开后“打印为 PDF”）：{path}"
                : $"报告已生成：{path}") + " " + countMsg
        };
    }

    public async Task<IReadOnlyList<TestReportArtifact>> ListArtifactsAsync(Guid sdkProjectId, int take = 50, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        return await db.TestReportArtifacts.AsNoTracking()
            .Where(x => x.SdkProjectId == sdkProjectId)
            .OrderByDescending(x => x.CreatedAtUtc)
            .Take(take)
            .ToListAsync(ct);
    }

    public async Task<(IReadOnlyList<TestReportArtifact> Items, int TotalCount)> ListArtifactsPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        int skip = 0,
        int take = 50,
        CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = db.TestReportArtifacts.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId);
        if (!string.IsNullOrWhiteSpace(searchText))
        {
            var term = searchText.Trim();
            q = q.Where(x =>
                x.Title.Contains(term) ||
                x.Format.Contains(term) ||
                x.FilePath.Contains(term));
        }

        var total = await q.CountAsync(ct);
        take = Math.Max(1, take);
        skip = Math.Max(0, skip);
        var items = await q.OrderByDescending(x => x.CreatedAtUtc).Skip(skip).Take(take).ToListAsync(ct);
        return (items, total);
    }

    public async Task<int> DeleteManyAsync(IEnumerable<Guid> ids, CancellationToken ct = default)
    {
        var idList = ids.Distinct().ToList();
        if (idList.Count == 0) return 0;

        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var rows = await db.TestReportArtifacts.Where(x => idList.Contains(x.Id)).ToListAsync(ct);
        if (rows.Count == 0) return 0;
        foreach (var row in rows)
            TryDeleteFile(row.FilePath);
        db.TestReportArtifacts.RemoveRange(rows);
        await db.SaveChangesAsync(ct);
        return rows.Count;
    }

    public async Task<int> DeleteFilteredAsync(Guid sdkProjectId, string? searchText = null, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = db.TestReportArtifacts.Where(x => x.SdkProjectId == sdkProjectId);
        if (!string.IsNullOrWhiteSpace(searchText))
        {
            var term = searchText.Trim();
            q = q.Where(x =>
                x.Title.Contains(term) ||
                x.Format.Contains(term) ||
                x.FilePath.Contains(term));
        }

        var rows = await q.ToListAsync(ct);
        if (rows.Count == 0) return 0;
        foreach (var row in rows)
            TryDeleteFile(row.FilePath);
        db.TestReportArtifacts.RemoveRange(rows);
        await db.SaveChangesAsync(ct);
        return rows.Count;
    }

    private static void TryDeleteFile(string? path)
    {
        try
        {
            if (!string.IsNullOrWhiteSpace(path) && File.Exists(path))
                File.Delete(path);
        }
        catch
        {
            // DB row still removed; orphaned file is acceptable.
        }
    }

    private static string BuildHtml(
        string title,
        string disclaimer,
        SdkProject project,
        TestBatchRun? batch,
        TestReportRunScope runScope,
        TestStatistics stats,
        CoverageStats coverage,
        IReadOnlyList<FailureAnalysisItem> runDetails,
        IReadOnlyList<FailureAnalysisItem> failures,
        IReadOnlyList<FailureAnalysisItem> skippedDetails,
        IReadOnlyList<FailureAnalysisItem> passedDetails,
        bool printable)
    {
        var sb = new StringBuilder();
        sb.AppendLine("<!DOCTYPE html><html><head><meta charset='utf-8'/>");
        sb.AppendLine($"<title>{Escape(title)}</title>");
        sb.AppendLine("<style>body{font-family:Segoe UI,Arial,sans-serif;margin:24px;color:#1a1a1a}h1,h2{color:#0f766e}.warn{background:#fff7ed;border:1px solid #fdba74;padding:12px;margin:12px 0}table{border-collapse:collapse;width:100%;margin:12px 0}th,td{border:1px solid #ddd;padding:6px 8px;font-size:13px}th{background:#f3f4f6;text-align:left}.meta{color:#555}pre{background:#f8fafc;padding:8px;overflow:auto;font-size:12px}details{margin:8px 0;border:1px solid #e5e7eb;border-radius:6px;padding:4px 8px}details>summary{cursor:pointer;font-weight:600}.pass summary{color:#047857}.fail summary{color:#b45309}.skip summary{color:#6b7280}</style>");
        if (printable) sb.AppendLine("<style>@media print{body{margin:12px}}</style>");
        sb.AppendLine("</head><body>");
        sb.AppendLine($"<h1>{Escape(title)}</h1>");
        sb.AppendLine($"<div class='warn'><b>重要声明：</b>{Escape(disclaimer)}</div>");
        sb.AppendLine("<h2>1. 测试基本信息</h2><ul>");
        sb.AppendLine($"<li>生成时间：{DateTime.Now:yyyy-MM-dd HH:mm:ss}</li>");
        sb.AppendLine($"<li>工具版本：{Escape(Assembly.GetExecutingAssembly().GetName().Version?.ToString() ?? "dev")}</li>");
        sb.AppendLine($"<li>SDK 项目：{Escape(project.Name)}</li>");
        sb.AppendLine($"<li>SDK 版本：{Escape(project.Version ?? batch?.SdkVersion ?? "—")}</li>");
        sb.AppendLine($"<li>芯片型号：{Escape(batch?.ChipModelName ?? "—（见用例/计划）")}</li>");
        sb.AppendLine($"<li>批次：{(batch is null ? "项目汇总" : batch.Id.ToString())}</li>");
        sb.AppendLine($"<li>编译器：{Escape(batch?.CompilerVersion ?? "—")}</li>");
        sb.AppendLine("</ul>");

        sb.AppendLine("<h2>2. 测试范围与统计</h2><ul>");
        sb.AppendLine($"<li>用例总数：{stats.CaseTotal}</li>");
        sb.AppendLine($"<li>执行次数：{stats.ExecutedRuns}</li>");
        sb.AppendLine($"<li>通过/失败/错误/跳过/超时：{stats.Passed}/{stats.Failed}/{stats.Error}/{stats.Skipped}/{stats.Timeout}</li>");
        sb.AppendLine($"<li>通过率：{stats.PassRate:F1}%（口径：Passed/(Passed+Failed+Error+Timeout)）</li>");
        sb.AppendLine($"<li>编译失败率：{stats.CompileFailRate:F1}%</li>");
        sb.AppendLine($"<li>平均耗时：{stats.AverageDurationMs:F0} ms</li>");
        sb.AppendLine("</ul>");

        sb.AppendLine("<h2>3. 覆盖率（真实数据口径）</h2><ul>");
        sb.AppendLine($"<li>LL 函数：{FmtPct(coverage.FunctionCoveragePercent)} （{coverage.FunctionsCoveredByCases}/{coverage.FunctionsTotal}）— {Escape(coverage.FunctionCoverageDenomination)}</li>");
        sb.AppendLine($"<li>外设：{FmtPct(coverage.PeripheralCoveragePercent)} （{coverage.PeripheralsCoveredByCases}/{coverage.PeripheralsTotal}）— {Escape(coverage.PeripheralCoverageDenomination)}</li>");
        sb.AppendLine($"<li>寄存器访问：{FmtPct(coverage.RegisterAccessCoveragePercent)} （{coverage.RegistersTouchedInRuns}/{coverage.RegistersReferencedInParse}）— {Escape(coverage.RegisterAccessCoverageDenomination)}</li>");
        sb.AppendLine($"<li>位域断言：{FmtPct(coverage.BitFieldCoveragePercent)} （{coverage.BitFieldsAsserted}/{coverage.BitFieldsTotal}）— {Escape(coverage.BitFieldCoverageDenomination)}</li>");
        sb.AppendLine($"<li>用例执行：{FmtPct(coverage.CaseCoveragePercent)} （{coverage.CasesExecutedAtLeastOnce}/{coverage.CasesTotal}）— {Escape(coverage.CaseCoverageDenomination)}</li>");
        sb.AppendLine($"<li class='meta'>{Escape(coverage.Notes)}</li>");
        sb.AppendLine("</ul>");

        sb.AppendLine($"<h2>4. 执行结果汇总（{runDetails.Count} 条）</h2>");
        sb.AppendLine("<p class='meta'>");
        sb.AppendLine(DescribeReportRunScope(runScope, runDetails.Count, batch));
        sb.AppendLine($"Passed={passedDetails.Count}，失败/错误/超时={failures.Count}，跳过={skippedDetails.Count}。");
        if (batch is not null && batch.TotalCount > runDetails.Count)
            sb.AppendLine($"<br/><b>注意：</b>批次登记 {batch.TotalCount} 次运行，本报告载入 {runDetails.Count} 条明细（无导出条数上限；缺口多为库中运行记录已删）。");
        sb.AppendLine("</p>");
        if (runDetails.Count == 0)
            sb.AppendLine("<p>无运行记录。</p>");
        else
        {
            sb.AppendLine("<table><tr><th>用例</th><th>函数</th><th>状态</th><th>耗时(ms)</th><th>返回值</th><th>编译</th><th>断言</th><th>说明</th></tr>");
            foreach (var r in runDetails)
            {
                sb.AppendLine("<tr>");
                sb.AppendLine($"<td>{Escape(r.CaseName)}</td><td>{Escape(r.FunctionName)}</td><td>{Escape(r.Status)}</td>");
                sb.AppendLine($"<td>{r.DurationMs}</td><td>{Escape(r.ReturnValueText ?? "")}</td>");
                sb.AppendLine($"<td>{(r.CompileSucceeded ? "OK" : "Fail")}</td>");
                sb.AppendLine($"<td>{(r.AssertionsPassed ? "OK" : "—")}</td>");
                sb.AppendLine($"<td>{Escape(r.FailureReason ?? (r.Status == nameof(LlTestRunStatus.Passed) ? "通过" : ""))}</td>");
                sb.AppendLine("</tr>");
            }
            sb.AppendLine("</table>");
        }

        AppendRunDetailSection(sb, "5. 失败 / 错误 / 超时 — 详细记录", failures, cssClass: "fail", expand: true);
        AppendRunDetailSection(sb, "6. 跳过 — 详细测试记录（含操作过程）", skippedDetails, cssClass: "skip", expand: true);
        AppendRunDetailSection(sb, "7. 通过 — 详细测试记录", passedDetails, cssClass: "pass", expand: false);

        sb.AppendLine("<h2>8. 测试结论</h2>");
        sb.AppendLine($"<p>在虚拟 MCU 环境下，选定范围内通过率 {stats.PassRate:F1}%。");
        sb.AppendLine("本结论仅反映软件模拟验证，不能替代板级硬件测试。</p>");
        sb.AppendLine("</body></html>");
        return sb.ToString();
    }

    private static void AppendRunDetailSection(
        StringBuilder sb,
        string heading,
        IReadOnlyList<FailureAnalysisItem> items,
        string cssClass,
        bool expand)
    {
        sb.AppendLine($"<h2>{Escape(heading)} ({items.Count})</h2>");
        if (items.Count == 0)
        {
            sb.AppendLine("<p>无记录。</p>");
            return;
        }

        foreach (var r in items)
        {
            var summary = $"{r.Status} — {r.FunctionName} — {r.CaseName} ({r.DurationMs} ms)";
            sb.AppendLine($"<details class='{cssClass}'{(expand ? " open" : "")}>");
            sb.AppendLine($"<summary>{Escape(summary)}</summary>");
            sb.AppendLine("<ul>");
            sb.AppendLine($"<li>RunId: {r.RunId}</li>");
            sb.AppendLine($"<li>源码: {Escape(r.SourceFile ?? "—")}</li>");
            sb.AppendLine($"<li>返回值: {Escape(r.ReturnValueText ?? "—")}</li>");
            sb.AppendLine($"<li>相关寄存器: {Escape(r.RelatedRegisters ?? "—")}</li>");
            if (!string.IsNullOrWhiteSpace(r.FailureReason))
                sb.AppendLine($"<li>说明: {Escape(r.FailureReason)}</li>");
            sb.AppendLine("</ul>");
            if (string.Equals(r.Status, nameof(LlTestRunStatus.Skipped), StringComparison.OrdinalIgnoreCase))
            {
                sb.AppendLine("<p class='meta'>跳过不等于未执行：多数情况仍走过环境检查/编译/执行；"
                    + "因缺少语义断言（常见仅超时断言）或缺少 Clang 而不计 Passed。"
                    + "下方为该次运行的操作过程。</p>");
            }
            if (!string.IsNullOrWhiteSpace(r.StagesJson) && r.StagesJson.Trim() is not ("[]" or "null"))
            {
                sb.AppendLine("<p><b>操作过程（执行阶段）</b></p>");
                sb.AppendLine($"<pre>{Escape(FormatAssertionJsonForReport(r.StagesJson))}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.ParametersJson))
            {
                sb.AppendLine("<p><b>用例参数（传入 LL 的实参）</b></p>");
                sb.AppendLine($"<pre>{Escape(FormatAssertionJsonForReport(r.ParametersJson))}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.InitialRegistersJson)
                && r.InitialRegistersJson != "[]")
            {
                sb.AppendLine("<p><b>初始寄存器（运行前预置写入）</b></p>");
                sb.AppendLine($"<pre>{Escape(FormatAssertionJsonForReport(r.InitialRegistersJson))}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.RegisterWritesSummary))
            {
                sb.AppendLine("<p><b>寄存器写入值一览</b>（运行前预置、原生 LL 执行后同步到虚拟 MCU）</p>");
                sb.AppendLine($"<pre>{Escape(r.RegisterWritesSummary)}</pre>");
            }
            else if (string.IsNullOrWhiteSpace(r.AccessTraceJson) || r.AccessTraceJson.Trim() is "[]")
            {
                sb.AppendLine("<p><b>寄存器操作记录</b></p>");
                sb.AppendLine("<p class='muted'>本次运行未记录寄存器访问。常见原因：① 草稿用例未配置「初始寄存器」；"
                    + "② 断言仅含超时、未触发明细读写；③ 旧版运行中外设实例名与虚拟寄存器不一致（如 ADC vs ADC0）导致同步未写入。"
                    + "请用最新版重新执行该用例；在虚拟 MCU 页的手动操作不会自动出现在此报告中。</p>");
            }
            if (!string.IsNullOrWhiteSpace(r.ExecutionLogExcerpt))
            {
                sb.AppendLine("<p><b>执行日志</b></p>");
                sb.AppendLine($"<pre>{Escape(r.ExecutionLogExcerpt)}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.CompileLogExcerpt) && !r.CompileSucceeded)
            {
                sb.AppendLine("<p><b>编译日志</b></p>");
                sb.AppendLine($"<pre>{Escape(r.CompileLogExcerpt)}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.AssertionResultsJson))
            {
                sb.AppendLine("<p><b>断言结果</b></p>");
                sb.AppendLine($"<pre>{Escape(FormatAssertionJsonForReport(r.AssertionResultsJson))}</pre>");
            }
            if (!string.IsNullOrWhiteSpace(r.AccessTraceJson))
            {
                sb.AppendLine("<p><b>寄存器访问轨迹（摘录）</b></p>");
                sb.AppendLine($"<pre>{Escape(r.AccessTraceJson)}</pre>");
            }
            sb.AppendLine("</details>");
        }
    }

    private static string FormatAssertionJsonForReport(string? json)
    {
        if (string.IsNullOrWhiteSpace(json)) return "";
        try
        {
            using var doc = JsonDocument.Parse(json);
            return JsonSerializer.Serialize(doc, new JsonSerializerOptions { WriteIndented = true });
        }
        catch
        {
            return json;
        }
    }

    private static string BuildCsv(
        SdkProject project,
        TestBatchRun? batch,
        TestStatistics stats,
        IReadOnlyList<FailureAnalysisItem> runDetails)
    {
        var sb = new StringBuilder();
        sb.AppendLine("Section,Key,Value");
        sb.AppendLine($"Meta,Disclaimer,\"基于虚拟 MCU，不等同真实硬件测试\"");
        sb.AppendLine($"Meta,SdkProject,\"{EscapeCsv(project.Name)}\"");
        sb.AppendLine($"Meta,SdkVersion,\"{EscapeCsv(project.Version ?? "")}\"");
        sb.AppendLine($"Meta,BatchId,\"{batch?.Id}\"");
        sb.AppendLine($"Stats,CaseTotal,{stats.CaseTotal}");
        sb.AppendLine($"Stats,ExecutedRuns,{stats.ExecutedRuns}");
        sb.AppendLine($"Stats,Passed,{stats.Passed}");
        sb.AppendLine($"Stats,Failed,{stats.Failed}");
        sb.AppendLine($"Stats,Error,{stats.Error}");
        sb.AppendLine($"Stats,Skipped,{stats.Skipped}");
        sb.AppendLine($"Stats,Timeout,{stats.Timeout}");
        sb.AppendLine($"Stats,PassRate,{stats.PassRate:F2}");
        sb.AppendLine($"Stats,CompileFailRate,{stats.CompileFailRate:F2}");
        sb.AppendLine($"Stats,AverageDurationMs,{stats.AverageDurationMs:F0}");
        sb.AppendLine("RunDetail,CaseName,FunctionName,Status,DurationMs,ReturnValue,CompileOk,AssertionsOk,FailureReason,SourceFile,Registers,Parameters,InitialRegisters,RegisterWrites,AssertionResults,AccessTrace");
        foreach (var r in runDetails)
        {
            var assertions = EscapeCsv(TruncateForCsv(r.AssertionResultsJson, 8000) ?? "");
            var trace = EscapeCsv(TruncateForCsv(r.AccessTraceJson, 4000) ?? "");
            var parameters = EscapeCsv(TruncateForCsv(r.ParametersJson, 2000) ?? "");
            var initials = EscapeCsv(TruncateForCsv(r.InitialRegistersJson, 1000) ?? "");
            var writes = EscapeCsv(TruncateForCsv(r.RegisterWritesSummary, 4000) ?? "");
            sb.AppendLine(
                $"RunDetail,\"{EscapeCsv(r.CaseName)}\",\"{EscapeCsv(r.FunctionName)}\",{r.Status},{r.DurationMs}," +
                $"\"{EscapeCsv(r.ReturnValueText ?? "")}\",{r.CompileSucceeded},{r.AssertionsPassed}," +
                $"\"{EscapeCsv(r.FailureReason ?? "")}\",\"{EscapeCsv(r.SourceFile ?? "")}\",\"{EscapeCsv(r.RelatedRegisters ?? "")}\"," +
                $"\"{parameters}\",\"{initials}\",\"{writes}\",\"{assertions}\",\"{trace}\"");
        }
        return sb.ToString();
    }

    private static string? TruncateForCsv(string? s, int max)
        => string.IsNullOrEmpty(s) ? s : s.Length <= max ? s : s[..max] + "…";

    private static TestReportRunScope ResolveEffectiveRunScope(TestReportRequest request)
        => request.RunScope switch
        {
            TestReportRunScope.Auto when request.BatchRunId is Guid => TestReportRunScope.SelectedBatchOnly,
            TestReportRunScope.Auto => TestReportRunScope.ProjectLatestPerCase,
            _ => request.RunScope
        };

    private static Guid? ResolveStatsBatchId(TestReportRequest request)
    {
        var scope = ResolveEffectiveRunScope(request);
        return scope == TestReportRunScope.SelectedBatchOnly ? request.BatchRunId : null;
    }

    private static string DescribeReportRunScope(TestReportRunScope scope, int rowCount, TestBatchRun? batch)
    {
        var scopeText = scope switch
        {
            TestReportRunScope.ProjectLatestPerCase => "全项目 · 每用例最新一次运行",
            TestReportRunScope.ProjectAllRuns => "全项目 · 全部历史运行",
            TestReportRunScope.SelectedBatchOnly => "仅当前批次",
            _ => batch is null ? "各用例最新一次运行" : "跟当前选中批次"
        };
        var batchNote = batch is null
            ? ""
            : $"（批次 TotalCount={batch.TotalCount}，导出明细 {rowCount} 条）";
        return $"范围：{scopeText}{batchNote}。汇总表与明细共 {rowCount} 条。";
    }

    private static string FmtPct(double? v) => v is null ? "N/A（无足够真实数据）" : $"{v:F1}%";
    private static string Escape(string s) => s.Replace("&", "&amp;").Replace("<", "&lt;").Replace(">", "&gt;").Replace("\"", "&quot;");
    private static string EscapeCsv(string s) => s.Replace("\"", "\"\"");
}
