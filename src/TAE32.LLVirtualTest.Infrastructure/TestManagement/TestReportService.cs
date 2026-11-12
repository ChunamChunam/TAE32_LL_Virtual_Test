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
        var stats = await _analytics.GetStatisticsAsync(request.SdkProjectId, request.BatchRunId, cancellationToken);
        var coverage = await _analytics.GetCoverageAsync(request.SdkProjectId, cancellationToken);
        var failures = await _analytics.GetFailuresAsync(request.SdkProjectId, request.BatchRunId, 200, cancellationToken);
        TestBatchRun? batch = null;
        if (request.BatchRunId is Guid bid)
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
                await File.WriteAllTextAsync(path, BuildCsv(project, batch, stats, failures), Encoding.UTF8, cancellationToken);
                format = request.Format == TestReportFormat.Excel ? "Excel" : "Csv";
                break;
            case TestReportFormat.Pdf:
                // Lightweight printable HTML saved as .pdf.html (open in browser → 打印为 PDF).
                path = Path.Combine(outDir, $"report_{stamp}.pdf.html");
                await File.WriteAllTextAsync(path,
                    BuildHtml(title, disclaimer, project, batch, stats, coverage, failures, printable: true),
                    Encoding.UTF8, cancellationToken);
                format = "Pdf";
                break;
            default:
                path = Path.Combine(outDir, $"report_{stamp}.html");
                await File.WriteAllTextAsync(path,
                    BuildHtml(title, disclaimer, project, batch, stats, coverage, failures, printable: false),
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

        return new TestReportResult
        {
            ArtifactId = artifact.Id,
            Format = format,
            FilePath = path,
            Message = format == "Pdf"
                ? $"已生成可打印 HTML（请用浏览器打开后“打印为 PDF”）：{path}"
                : $"报告已生成：{path}"
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
        TestStatistics stats,
        CoverageStats coverage,
        IReadOnlyList<FailureAnalysisItem> failures,
        bool printable)
    {
        var sb = new StringBuilder();
        sb.AppendLine("<!DOCTYPE html><html><head><meta charset='utf-8'/>");
        sb.AppendLine($"<title>{Escape(title)}</title>");
        sb.AppendLine("<style>body{font-family:Segoe UI,Arial,sans-serif;margin:24px;color:#1a1a1a}h1,h2{color:#0f766e}.warn{background:#fff7ed;border:1px solid #fdba74;padding:12px;margin:12px 0}table{border-collapse:collapse;width:100%;margin:12px 0}th,td{border:1px solid #ddd;padding:6px 8px;font-size:13px}th{background:#f3f4f6;text-align:left}.meta{color:#555}pre{background:#f8fafc;padding:8px;overflow:auto;font-size:12px}</style>");
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

        sb.AppendLine("<h2>4. 失败用例清单</h2>");
        if (failures.Count == 0) sb.AppendLine("<p>无失败/错误/超时记录（基于所选范围的真实运行数据）。</p>");
        else
        {
            sb.AppendLine("<table><tr><th>用例</th><th>函数</th><th>状态</th><th>失败原因</th><th>源码</th><th>相关寄存器</th></tr>");
            foreach (var f in failures)
            {
                sb.AppendLine("<tr>");
                sb.AppendLine($"<td>{Escape(f.CaseName)}</td><td>{Escape(f.FunctionName)}</td><td>{Escape(f.Status)}</td>");
                sb.AppendLine($"<td>{Escape(f.FailureReason ?? "")}</td><td>{Escape(f.SourceFile ?? "")}</td><td>{Escape(f.RelatedRegisters ?? "")}</td>");
                sb.AppendLine("</tr>");
            }
            sb.AppendLine("</table>");
            sb.AppendLine("<h3>编译 / 断言摘录</h3>");
            foreach (var f in failures.Take(20))
            {
                sb.AppendLine($"<h4>{Escape(f.CaseName)}</h4>");
                if (!string.IsNullOrWhiteSpace(f.CompileLogExcerpt))
                    sb.AppendLine($"<pre>{Escape(f.CompileLogExcerpt)}</pre>");
                if (!string.IsNullOrWhiteSpace(f.AssertionResultsJson))
                    sb.AppendLine($"<pre>{Escape(f.AssertionResultsJson)}</pre>");
            }
        }

        sb.AppendLine("<h2>5. 测试结论</h2>");
        sb.AppendLine($"<p>在虚拟 MCU 环境下，选定范围内通过率 {stats.PassRate:F1}%。");
        sb.AppendLine("本结论仅反映软件模拟验证，不能替代板级硬件测试。</p>");
        sb.AppendLine("</body></html>");
        return sb.ToString();
    }

    private static string BuildCsv(
        SdkProject project,
        TestBatchRun? batch,
        TestStatistics stats,
        IReadOnlyList<FailureAnalysisItem> failures)
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
        sb.AppendLine("Failure,CaseName,FunctionName,Status,FailureReason,SourceFile,Registers");
        foreach (var f in failures)
            sb.AppendLine($"Failure,\"{EscapeCsv(f.CaseName)}\",\"{EscapeCsv(f.FunctionName)}\",{f.Status},\"{EscapeCsv(f.FailureReason ?? "")}\",\"{EscapeCsv(f.SourceFile ?? "")}\",\"{EscapeCsv(f.RelatedRegisters ?? "")}\"");
        return sb.ToString();
    }

    private static string FmtPct(double? v) => v is null ? "N/A（无足够真实数据）" : $"{v:F1}%";
    private static string Escape(string s) => s.Replace("&", "&amp;").Replace("<", "&lt;").Replace(">", "&gt;").Replace("\"", "&quot;");
    private static string EscapeCsv(string s) => s.Replace("\"", "\"\"");
}
