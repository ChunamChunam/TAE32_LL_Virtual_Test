using System.Security.Cryptography;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

public sealed class LlStaticAnalysisPersistService : ILlStaticAnalysisPersistService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly LlShiftStaticAnalyzer _analyzer;
    private readonly ILogger<LlStaticAnalysisPersistService> _logger;
    private static int _schemaReady;

    public LlStaticAnalysisPersistService(
        IDbContextFactory<AppDbContext> dbFactory,
        LlShiftStaticAnalyzer analyzer,
        ILogger<LlStaticAnalysisPersistService> logger)
    {
        _dbFactory = dbFactory;
        _analyzer = analyzer;
        _logger = logger;
    }

    public Task<LlStaticAnalysisPersistResult> AnalyzeProjectAsync(
        Guid sdkProjectId, CancellationToken cancellationToken = default)
        => AnalyzeCoreAsync(sdkProjectId, functionIds: null, cancellationToken);

    public Task<LlStaticAnalysisPersistResult> AnalyzeFunctionsAsync(
        Guid sdkProjectId,
        IReadOnlyList<Guid> functionIds,
        CancellationToken cancellationToken = default)
        => AnalyzeCoreAsync(sdkProjectId, functionIds, cancellationToken);

    private async Task<LlStaticAnalysisPersistResult> AnalyzeCoreAsync(
        Guid sdkProjectId,
        IReadOnlyList<Guid>? functionIds,
        CancellationToken cancellationToken)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken)
            .ConfigureAwait(false);
        await EnsureSchemaAsync(db, cancellationToken).ConfigureAwait(false);

        var project = await db.SdkProjects.AsNoTracking()
            .FirstOrDefaultAsync(x => x.Id == sdkProjectId, cancellationToken)
            .ConfigureAwait(false);
        if (project is null)
        {
            return new LlStaticAnalysisPersistResult
            {
                SdkProjectId = sdkProjectId,
                Message = "SDK project not found"
            };
        }

        var q = db.LlFunctions.Where(x => x.SdkProjectId == sdkProjectId);
        if (functionIds is { Count: > 0 })
            q = q.Where(x => functionIds.Contains(x.Id));

        var rows = await q
            .Select(x => new
            {
                x.Id,
                x.FunctionName,
                x.FilePath,
                x.SourceText,
                x.StaticAnalysisJson,
                x.StaticAnalysisStamp
            })
            .ToListAsync(cancellationToken)
            .ConfigureAwait(false);

        var catalog = await SdkMacroSemanticCatalog.TryLoadFromDbAsync(
                _dbFactory, sdkProjectId, cancellationToken)
            .ConfigureAwait(false);
        // Fall back to chip.h only when register parse has not populated macros yet.
        catalog ??= SdkMacroSemanticCatalog.TryLoad(project.SdkRootPath);

        var analyzed = 0;
        var cached = 0;
        var withErrors = 0;
        var withWarnings = 0;
        var workspace = FindWorkspaceRoot(project.SdkRootPath);

        foreach (var row in rows)
        {
            cancellationToken.ThrowIfCancellationRequested();
            var resolved = ResolveSourcePath(row.FilePath, project.SdkRootPath, workspace);
            var stamp = BuildStamp(row.Id, row.SourceText, resolved);

            if (!string.IsNullOrWhiteSpace(row.StaticAnalysisJson)
                && string.Equals(row.StaticAnalysisStamp, stamp, StringComparison.Ordinal))
            {
                cached++;
                var existing = LlTestJson.Deserialize<List<StaticAnalysisDiagnostic>>(row.StaticAnalysisJson!)
                               ?? new List<StaticAnalysisDiagnostic>();
                if (existing.Any(d => string.Equals(d.Severity, "Error", StringComparison.OrdinalIgnoreCase)))
                    withErrors++;
                else if (existing.Any(d => string.Equals(d.Severity, "Warning", StringComparison.OrdinalIgnoreCase)))
                    withWarnings++;
                continue;
            }

            if (string.IsNullOrWhiteSpace(row.SourceText)
                && (string.IsNullOrWhiteSpace(resolved) || !File.Exists(resolved)))
                continue;

            var result = _analyzer.AnalyzeWithCatalog(
                project.SdkRootPath,
                resolved,
                row.FunctionName,
                catalog,
                string.IsNullOrWhiteSpace(row.SourceText) ? null : row.SourceText);

            analyzed++;
            if (result.HasBlockingError) withErrors++;
            else if (result.HasWarning) withWarnings++;

            var json = LlTestJson.Serialize(result.Diagnostics);
            await db.LlFunctions.Where(f => f.Id == row.Id)
                .ExecuteUpdateAsync(s => s
                        .SetProperty(f => f.StaticAnalysisJson, json)
                        .SetProperty(f => f.StaticAnalysisStamp, stamp)
                        .SetProperty(f => f.UpdatedAtUtc, DateTime.UtcNow),
                    cancellationToken)
                .ConfigureAwait(false);

            // Mirror Errors into LlParseDiagnostics for SDK management UI.
            if (result.HasBlockingError)
            {
                foreach (var d in result.Diagnostics.Where(x =>
                             string.Equals(x.Severity, "Error", StringComparison.OrdinalIgnoreCase)))
                {
                    db.LlParseDiagnostics.Add(new LlParseDiagnostic
                    {
                        SdkProjectId = sdkProjectId,
                        LlFunctionId = row.Id,
                        Severity = LlParseDiagnosticSeverity.Error.ToString(),
                        Category = LlParseDiagnosticCategory.StaticAnalysis.ToString(),
                        Message = $"{d.RuleId}: {d.Description}",
                        FilePath = d.SourceFile,
                        Line = d.LineNumber,
                        Detail = d.Expression
                    });
                }
            }
        }

        await db.SaveChangesAsync(cancellationToken).ConfigureAwait(false);

        var msg =
            $"静态分析完成：分析 {analyzed}，命中缓存 {cached}，Error 函数 {withErrors}，Warning 函数 {withWarnings}";
        _logger.LogInformation("Static analysis project {ProjectId}: {Message}", sdkProjectId, msg);

        return new LlStaticAnalysisPersistResult
        {
            SdkProjectId = sdkProjectId,
            FunctionsConsidered = rows.Count,
            FunctionsAnalyzed = analyzed,
            FunctionsCached = cached,
            WithErrors = withErrors,
            WithWarnings = withWarnings,
            Message = msg
        };
    }

    private static async Task EnsureSchemaAsync(AppDbContext db, CancellationToken ct)
    {
        if (Interlocked.CompareExchange(ref _schemaReady, 1, 0) != 0)
            return;
        foreach (var sql in new[]
                 {
                     """ALTER TABLE "LlFunctions" ADD COLUMN "StaticAnalysisJson" TEXT""",
                     """ALTER TABLE "LlFunctions" ADD COLUMN "StaticAnalysisStamp" TEXT"""
                 })
        {
            try { await db.Database.ExecuteSqlRawAsync(sql, ct).ConfigureAwait(false); }
            catch { /* exists */ }
        }
    }

    private static string BuildStamp(Guid functionId, string? sourceText, string? resolvedPath)
    {
        if (!string.IsNullOrWhiteSpace(sourceText))
        {
            var hash = Convert.ToHexString(SHA256.HashData(Encoding.UTF8.GetBytes(sourceText)))[..16];
            return $"v3|src|{functionId:N}|{hash}";
        }

        var filePart = "nofile";
        if (!string.IsNullOrWhiteSpace(resolvedPath) && File.Exists(resolvedPath))
            filePart = File.GetLastWriteTimeUtc(resolvedPath).Ticks.ToString();
        return $"v3|file|{functionId:N}|{filePart}";
    }

    private static string? ResolveSourcePath(string? filePath, string? sdkRoot, string? workspace)
    {
        if (string.IsNullOrWhiteSpace(filePath)) return null;
        if (File.Exists(filePath)) return Path.GetFullPath(filePath);
        var normalized = filePath.Replace('/', Path.DirectorySeparatorChar);
        if (!string.IsNullOrWhiteSpace(sdkRoot))
        {
            var underSdk = Path.Combine(sdkRoot, normalized);
            if (File.Exists(underSdk)) return underSdk;

            var fileName = Path.GetFileName(normalized);
            var layout = Core.Sdk.SdkSeriesLayout.Discover(sdkRoot);
            if (!string.IsNullOrWhiteSpace(layout?.LlRoot))
            {
                var underLl = Path.Combine(layout.LlRoot, fileName);
                if (File.Exists(underLl)) return underLl;
            }

            // Series-aware *Driver/LL fallbacks, then G58 legacy path.
            foreach (var drivers in new[]
                     {
                         Path.Combine(sdkRoot, "Drivers"),
                         Path.Combine(sdkRoot, "SDK", "Drivers")
                     }.Where(Directory.Exists))
            {
                try
                {
                    foreach (var llDir in Directory.EnumerateDirectories(drivers, "*_Driver", SearchOption.TopDirectoryOnly)
                                 .Select(d => Path.Combine(d, "LL"))
                                 .Where(Directory.Exists)
                                 .Take(6))
                    {
                        var hit = Path.Combine(llDir, fileName);
                        if (File.Exists(hit)) return hit;
                    }
                }
                catch
                {
                    // ignore
                }
            }

            var g58Legacy = Path.Combine(sdkRoot, "SDK", "Drivers", "TAE32G58xx_Driver", "LL", fileName);
            if (File.Exists(g58Legacy)) return g58Legacy;
        }

        if (!string.IsNullOrWhiteSpace(workspace))
        {
            var underWs = Path.Combine(workspace, normalized);
            if (File.Exists(underWs)) return underWs;
        }

        return null;
    }

    private static string? FindWorkspaceRoot(string? sdkRoot)
    {
        if (string.IsNullOrWhiteSpace(sdkRoot)) return null;
        var dir = new DirectoryInfo(sdkRoot);
        while (dir is not null)
        {
            if (Directory.Exists(Path.Combine(dir.FullName, "SDKContent"))
                && Directory.Exists(Path.Combine(dir.FullName, "ScanResults")))
                return dir.FullName;
            dir = dir.Parent;
        }

        return null;
    }
}
