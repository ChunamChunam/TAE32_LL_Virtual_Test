using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.SDK.Import;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlFunctionParseService : ILLFunctionParser
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ILogger<LlFunctionParseService> _logger;

    public LlFunctionParseService(IDbContextFactory<AppDbContext> dbFactory, ILogger<LlFunctionParseService> logger)
    {
        _dbFactory = dbFactory;
        _logger = logger;
    }

    public async Task<LlParseSummary> ParseAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
    {
        string sdkRootPath;
        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            var project = await db.SdkProjects.AsNoTracking()
                .FirstOrDefaultAsync(x => x.Id == sdkProjectId, cancellationToken);
            if (project is null)
            {
                return new LlParseSummary
                {
                    SdkProjectId = sdkProjectId,
                    Message = "SDK project not found"
                };
            }

            sdkRootPath = project.SdkRootPath;
        }

        var bridgeRoot = Path.Combine(Path.GetTempPath(), "tae32_ll_parse_bridge", sdkProjectId.ToString("N"));
        var env = ClangEnvironment.Resolve(sdkRootPath, bridgeRoot);
        var diagnostics = new List<LlParseDiagnostic>();

        if (env.RequiresParseBridge)
        {
            var bridge = new ParseBridgeBuilder().Build(env.LlRoot, env.BridgeRoot, sdkProjectId);
            diagnostics.AddRange(bridge.Diagnostics);
        }

        // Lightweight match index — no change tracking.
        List<FunctionMatchRow> matchRows;
        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            matchRows = await db.LlFunctions.AsNoTracking()
                .Where(x => x.SdkProjectId == sdkProjectId)
                .Select(x => new FunctionMatchRow(x.Id, x.NaturalKey, x.FunctionName, x.FilePath, x.StartLine, x.Form))
                .ToListAsync(cancellationToken);
        }

        var headers = Directory.GetFiles(env.LlRoot, "tae32g58xx_ll_*.h", SearchOption.TopDirectoryOnly)
            .Where(p => !p.EndsWith("tae32g58xx_ll.h", StringComparison.OrdinalIgnoreCase)
                        && !p.EndsWith("tae32g58xx_ll_def.h", StringComparison.OrdinalIgnoreCase))
            .OrderBy(p => p, StringComparer.OrdinalIgnoreCase)
            .ToList();

        var clangArgs = env.BuildClangArgs();
        var parsed = 0;
        var matched = 0;
        var unmatched = 0;
        var headersOk = 0;
        var matchedResults = new List<(Guid FunctionId, LlAstFunctionResult Ast)>();

        using var session = new ClangAstSession();
        var wrapperDir = Path.Combine(bridgeRoot, "wrappers");
        Directory.CreateDirectory(wrapperDir);

        foreach (var headerPath in headers)
        {
            cancellationToken.ThrowIfCancellationRequested();
            var fileName = Path.GetFileName(headerPath);
            var relPath = NormalizeRelative(headerPath, env.LlRoot);

            try
            {
                var wrapper = ClangAstSession.CreateWrapperFile(wrapperDir, fileName);
                var parseResult = session.ParseHeader(wrapper, clangArgs, fileName);

                if (parseResult.ClangDiagnostics.Count > 0)
                {
                    foreach (var msg in parseResult.ClangDiagnostics.Take(20))
                    {
                        diagnostics.Add(new LlParseDiagnostic
                        {
                            SdkProjectId = sdkProjectId,
                            Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                            Category = LlParseDiagnosticCategory.Clang.ToString(),
                            Message = msg.Length > 1900 ? msg[..1900] : msg,
                            FilePath = relPath
                        });
                    }
                }

                var extractor = new LlFunctionAstExtractor(sdkProjectId, relPath, fileName, headerPath);
                var astFunctions = extractor.Extract(parseResult);

                if (astFunctions.Count == 0)
                {
                    diagnostics.Add(new LlParseDiagnostic
                    {
                        SdkProjectId = sdkProjectId,
                        Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                        Category = LlParseDiagnosticCategory.Clang.ToString(),
                        Message = $"No function definitions extracted from {fileName}",
                        FilePath = relPath
                    });
                    continue;
                }

                headersOk++;
                foreach (var ast in astFunctions)
                {
                    parsed++;
                    if (!TryMatchFunction(matchRows, fileName, ast, out var functionId))
                    {
                        unmatched++;
                        diagnostics.Add(new LlParseDiagnostic
                        {
                            SdkProjectId = sdkProjectId,
                            Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                            Category = LlParseDiagnosticCategory.Match.ToString(),
                            Message = $"AST function not matched to DB: {ast.FunctionName} @ {relPath}:{ast.StartLine}",
                            FilePath = relPath,
                            Line = ast.StartLine
                        });
                        continue;
                    }

                    matched++;
                    matchedResults.Add((functionId, ast));
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Parse failed for {Header}", headerPath);
                diagnostics.Add(new LlParseDiagnostic
                {
                    SdkProjectId = sdkProjectId,
                    Severity = LlParseDiagnosticSeverity.Error.ToString(),
                    Category = LlParseDiagnosticCategory.Clang.ToString(),
                    Message = $"Parse failed: {fileName}",
                    FilePath = relPath,
                    Detail = ex.Message
                });
            }
        }

        await PersistResultsAsync(
            sdkProjectId, matchedResults, diagnostics, env.ClangVersion,
            clearFunctionIds: null, cancellationToken);

        return new LlParseSummary
        {
            SdkProjectId = sdkProjectId,
            HeadersAttempted = headers.Count,
            HeadersSucceeded = headersOk,
            FunctionsParsed = parsed,
            FunctionsMatched = matched,
            FunctionsUnmatched = unmatched,
            DiagnosticCount = diagnostics.Count,
            UsedParseBridge = env.RequiresParseBridge,
            ClangVersion = env.ClangVersion,
            Message = matched > 0 ? "Parse completed" : "Parse completed with no DB matches"
        };
    }

    public async Task<LlParseSummary> ParseOneAsync(Guid llFunctionId, CancellationToken cancellationToken = default)
    {
        string sdkRootPath;
        Guid sdkProjectId;
        string functionName;
        string? filePath;
        int startLine;
        string? form;

        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            var fn = await db.LlFunctions.AsNoTracking()
                .FirstOrDefaultAsync(x => x.Id == llFunctionId, cancellationToken);
            if (fn is null)
            {
                return new LlParseSummary
                {
                    Message = "LL 函数不存在"
                };
            }

            var project = await db.SdkProjects.AsNoTracking()
                .FirstOrDefaultAsync(x => x.Id == fn.SdkProjectId, cancellationToken);
            if (project is null)
            {
                return new LlParseSummary
                {
                    SdkProjectId = fn.SdkProjectId,
                    Message = "SDK project not found"
                };
            }

            sdkProjectId = fn.SdkProjectId;
            sdkRootPath = project.SdkRootPath;
            functionName = fn.FunctionName;
            filePath = fn.FilePath;
            startLine = fn.StartLine;
            form = fn.Form;
        }

        var bridgeRoot = Path.Combine(Path.GetTempPath(), "tae32_ll_parse_bridge", sdkProjectId.ToString("N"));
        var env = ClangEnvironment.Resolve(sdkRootPath, bridgeRoot);
        var diagnostics = new List<LlParseDiagnostic>();

        if (env.RequiresParseBridge)
        {
            var bridge = new ParseBridgeBuilder().Build(env.LlRoot, env.BridgeRoot, sdkProjectId);
            diagnostics.AddRange(bridge.Diagnostics);
        }

        var headerFileName = string.IsNullOrWhiteSpace(filePath)
            ? null
            : Path.GetFileName(filePath.Replace('/', Path.DirectorySeparatorChar));
        if (string.IsNullOrWhiteSpace(headerFileName))
        {
            return new LlParseSummary
            {
                SdkProjectId = sdkProjectId,
                Message = $"函数 {functionName} 无有效 FilePath"
            };
        }

        string? headerPath = null;
        try
        {
            headerPath = Directory.EnumerateFiles(env.LlRoot, headerFileName, SearchOption.TopDirectoryOnly)
                .FirstOrDefault();
        }
        catch
        {
            /* ignore */
        }

        if (headerPath is null || !File.Exists(headerPath))
        {
            return new LlParseSummary
            {
                SdkProjectId = sdkProjectId,
                HeadersAttempted = 1,
                Message = $"未在 SDK LL 目录找到头文件 {headerFileName}（函数 {functionName}）"
            };
        }

        List<FunctionMatchRow> matchRows;
        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            // Same-header rows for AST matching; only target id is persisted.
            matchRows = await db.LlFunctions.AsNoTracking()
                .Where(x => x.SdkProjectId == sdkProjectId)
                .Select(x => new FunctionMatchRow(x.Id, x.NaturalKey, x.FunctionName, x.FilePath, x.StartLine, x.Form))
                .ToListAsync(cancellationToken);
        }

        var clangArgs = env.BuildClangArgs();
        var matchedResults = new List<(Guid FunctionId, LlAstFunctionResult Ast)>();
        var parsed = 0;
        var matched = 0;
        var unmatched = 0;
        var headersOk = 0;
        var relPath = NormalizeRelative(headerPath, env.LlRoot);

        using var session = new ClangAstSession();
        var wrapperDir = Path.Combine(bridgeRoot, "wrappers");
        Directory.CreateDirectory(wrapperDir);

        try
        {
            var wrapper = ClangAstSession.CreateWrapperFile(wrapperDir, headerFileName);
            var parseResult = session.ParseHeader(wrapper, clangArgs, headerFileName);

            if (parseResult.ClangDiagnostics.Count > 0)
            {
                foreach (var msg in parseResult.ClangDiagnostics.Take(20))
                {
                    diagnostics.Add(new LlParseDiagnostic
                    {
                        SdkProjectId = sdkProjectId,
                        LlFunctionId = llFunctionId,
                        Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                        Category = LlParseDiagnosticCategory.Clang.ToString(),
                        Message = msg.Length > 1900 ? msg[..1900] : msg,
                        FilePath = relPath
                    });
                }
            }

            var extractor = new LlFunctionAstExtractor(sdkProjectId, relPath, headerFileName, headerPath);
            var astFunctions = extractor.Extract(parseResult);
            headersOk = 1;

            var targetAst = astFunctions.FirstOrDefault(a =>
                string.Equals(a.FunctionName, functionName, StringComparison.Ordinal)
                && (a.StartLine == startLine
                    || string.Equals(a.Form, form, StringComparison.Ordinal)
                    || form == "inline_definition"));

            // Prefer exact name + line; fall back to name-only in this header.
            targetAst ??= astFunctions.FirstOrDefault(a =>
                string.Equals(a.FunctionName, functionName, StringComparison.Ordinal));

            if (targetAst is null)
            {
                unmatched = 1;
                diagnostics.Add(new LlParseDiagnostic
                {
                    SdkProjectId = sdkProjectId,
                    LlFunctionId = llFunctionId,
                    Severity = LlParseDiagnosticSeverity.Error.ToString(),
                    Category = LlParseDiagnosticCategory.Match.ToString(),
                    Message = $"头文件 AST 中未找到函数 {functionName}（DB 行 {startLine}）",
                    FilePath = relPath,
                    Line = startLine
                });
            }
            else
            {
                parsed = 1;
                if (!TryMatchFunction(matchRows, headerFileName, targetAst, out var matchedId)
                    || matchedId != llFunctionId)
                {
                    // Force bind to the requested row when name matches this header.
                    matchedId = llFunctionId;
                }

                matched = 1;
                matchedResults.Add((matchedId, targetAst));
            }
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "ParseOne failed for {Header} / {Fn}", headerPath, functionName);
            diagnostics.Add(new LlParseDiagnostic
            {
                SdkProjectId = sdkProjectId,
                LlFunctionId = llFunctionId,
                Severity = LlParseDiagnosticSeverity.Error.ToString(),
                Category = LlParseDiagnosticCategory.Clang.ToString(),
                Message = $"ParseOne failed: {headerFileName} / {functionName}",
                FilePath = relPath,
                Detail = ex.Message
            });
        }

        await PersistResultsAsync(
            sdkProjectId, matchedResults, diagnostics, env.ClangVersion,
            clearFunctionIds: new[] { llFunctionId }, cancellationToken);

        return new LlParseSummary
        {
            SdkProjectId = sdkProjectId,
            HeadersAttempted = 1,
            HeadersSucceeded = headersOk,
            FunctionsParsed = parsed,
            FunctionsMatched = matched,
            FunctionsUnmatched = unmatched,
            DiagnosticCount = diagnostics.Count,
            UsedParseBridge = env.RequiresParseBridge,
            ClangVersion = env.ClangVersion,
            Message = matched > 0
                ? $"单函数解析完成：{functionName}"
                : $"单函数解析未匹配：{functionName}"
        };
    }

    private async Task PersistResultsAsync(
        Guid sdkProjectId,
        List<(Guid FunctionId, LlAstFunctionResult Ast)> matchedResults,
        List<LlParseDiagnostic> diagnostics,
        string clangVersion,
        IReadOnlyList<Guid>? clearFunctionIds,
        CancellationToken cancellationToken)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);

        if (clearFunctionIds is null)
            await ClearPreviousParseDataAsync(db, sdkProjectId, cancellationToken);
        else
            await ClearFunctionsParseDataAsync(db, clearFunctionIds, cancellationToken);
        db.ChangeTracker.Clear();

        // Parent fields via ExecuteUpdate (no tracked Modified entities → no false concurrency).
        // Children inserted in small batches.
        const int childBatchSize = 40;
        var pending = 0;
        var now = DateTime.UtcNow;

        foreach (var (functionId, ast) in matchedResults)
        {
            cancellationToken.ThrowIfCancellationRequested();

            var status = ast.ParseSucceeded ? LlParseStatus.Success.ToString() : LlParseStatus.Partial.ToString();
            var returnType = string.IsNullOrWhiteSpace(ast.ReturnType) ? null : ast.ReturnType;
            var signature = ast.Signature;
            var sourceText = ast.SourceText;
            var modifiers = ast.Modifiers;
            var isStatic = ast.IsStatic;
            var isInline = ast.IsInline;
            var endLine = ast.EndLine;
            var endColumn = ast.EndColumn;
            var bodyStart = ast.BodyStartLine;
            var bodyEnd = ast.BodyEndLine;

            var updated = returnType is null
                ? await db.LlFunctions.Where(f => f.Id == functionId).ExecuteUpdateAsync(s => s
                    .SetProperty(f => f.Signature, signature)
                    .SetProperty(f => f.SourceText, sourceText)
                    .SetProperty(f => f.Modifiers, modifiers)
                    .SetProperty(f => f.IsStatic, isStatic)
                    .SetProperty(f => f.IsInline, isInline)
                    .SetProperty(f => f.EndLine, endLine)
                    .SetProperty(f => f.EndColumn, endColumn)
                    .SetProperty(f => f.BodyStartLine, bodyStart)
                    .SetProperty(f => f.BodyEndLine, bodyEnd)
                    .SetProperty(f => f.ClangVersion, clangVersion)
                    .SetProperty(f => f.ParsedAtUtc, now)
                    .SetProperty(f => f.ParseStatus, status)
                    .SetProperty(f => f.UpdatedAtUtc, now), cancellationToken)
                : await db.LlFunctions.Where(f => f.Id == functionId).ExecuteUpdateAsync(s => s
                    .SetProperty(f => f.Signature, signature)
                    .SetProperty(f => f.SourceText, sourceText)
                    .SetProperty(f => f.Modifiers, modifiers)
                    .SetProperty(f => f.IsStatic, isStatic)
                    .SetProperty(f => f.IsInline, isInline)
                    .SetProperty(f => f.EndLine, endLine)
                    .SetProperty(f => f.EndColumn, endColumn)
                    .SetProperty(f => f.BodyStartLine, bodyStart)
                    .SetProperty(f => f.BodyEndLine, bodyEnd)
                    .SetProperty(f => f.ClangVersion, clangVersion)
                    .SetProperty(f => f.ParsedAtUtc, now)
                    .SetProperty(f => f.ParseStatus, status)
                    .SetProperty(f => f.UpdatedAtUtc, now)
                    .SetProperty(f => f.ReturnType, returnType), cancellationToken);

            if (updated == 0)
            {
                diagnostics.Add(new LlParseDiagnostic
                {
                    SdkProjectId = sdkProjectId,
                    LlFunctionId = functionId,
                    Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                    Category = LlParseDiagnosticCategory.Match.ToString(),
                    Message = $"DB row missing while saving parse result: {ast.FunctionName}",
                    FilePath = ast.FilePath,
                    Line = ast.StartLine
                });
                continue;
            }

            foreach (var p in ast.Parameters)
            {
                p.Id = Guid.NewGuid();
                p.LlFunctionId = functionId;
                db.LlFunctionParameters.Add(p);
            }

            foreach (var o in ast.Operations)
            {
                o.LlFunctionId = functionId;
                db.LlFunctionOperations.Add(o);
            }

            foreach (var c in ast.Calls)
            {
                c.Id = Guid.NewGuid();
                c.LlFunctionId = functionId;
                db.LlFunctionCalls.Add(c);
            }

            foreach (var r in ast.RegisterAccesses)
            {
                r.Id = Guid.NewGuid();
                r.LlFunctionId = functionId;
                db.LlRegisterAccesses.Add(r);
            }

            foreach (var m in ast.RegisterReferences)
            {
                m.Id = Guid.NewGuid();
                m.LlFunctionId = functionId;
                m.MacroInfoId = null;
                db.LlRegisterReferences.Add(m);
            }

            pending++;
            if (pending >= childBatchSize)
            {
                await db.SaveChangesAsync(cancellationToken);
                db.ChangeTracker.Clear();
                pending = 0;
            }
        }

        if (pending > 0)
        {
            await db.SaveChangesAsync(cancellationToken);
            db.ChangeTracker.Clear();
        }

        if (diagnostics.Count > 0)
        {
            foreach (var d in diagnostics)
            {
                d.Id = Guid.NewGuid();
                if (d.Message.Length > 2000)
                    d.Message = d.Message[..2000];
            }

            db.LlParseDiagnostics.AddRange(diagnostics);
            await db.SaveChangesAsync(cancellationToken);
        }

        _logger.LogInformation(
            "Deep parse persisted: project={ProjectId} functions={Count}",
            sdkProjectId, matchedResults.Count);
    }

    private static async Task ClearPreviousParseDataAsync(AppDbContext db, Guid sdkProjectId, CancellationToken ct)
    {
        var funcIds = await db.LlFunctions.AsNoTracking()
            .Where(x => x.SdkProjectId == sdkProjectId)
            .Select(x => x.Id)
            .ToListAsync(ct);

        if (funcIds.Count == 0)
            return;

        await ClearFunctionsParseDataAsync(db, funcIds, ct);
        await db.LlParseDiagnostics.Where(x => x.SdkProjectId == sdkProjectId).ExecuteDeleteAsync(ct);

        await db.LlFunctions.Where(x => x.SdkProjectId == sdkProjectId).ExecuteUpdateAsync(s => s
            .SetProperty(f => f.Signature, (string?)null)
            .SetProperty(f => f.SourceText, (string?)null)
            .SetProperty(f => f.Modifiers, (string?)null)
            .SetProperty(f => f.IsStatic, (bool?)null)
            .SetProperty(f => f.IsInline, (bool?)null)
            .SetProperty(f => f.ParseStatus, (string?)null)
            .SetProperty(f => f.ClangVersion, (string?)null)
            .SetProperty(f => f.ParsedAtUtc, (DateTime?)null)
            .SetProperty(f => f.EndColumn, (int?)null)
            .SetProperty(f => f.BodyStartLine, (int?)null)
            .SetProperty(f => f.BodyEndLine, (int?)null), ct);
    }

    /// <summary>Clear child parse rows for specific functions only (single-function reparse).</summary>
    private static async Task ClearFunctionsParseDataAsync(
        AppDbContext db, IReadOnlyList<Guid> funcIds, CancellationToken ct)
    {
        if (funcIds.Count == 0) return;

        foreach (var chunk in funcIds.Chunk(400))
        {
            var ids = chunk.ToArray();
            await db.LlFunctionParameters.Where(x => ids.Contains(x.LlFunctionId)).ExecuteDeleteAsync(ct);
            await db.LlFunctionOperations.Where(x => ids.Contains(x.LlFunctionId)).ExecuteDeleteAsync(ct);
            await db.LlFunctionCalls.Where(x => ids.Contains(x.LlFunctionId)).ExecuteDeleteAsync(ct);
            await db.LlRegisterAccesses.Where(x => ids.Contains(x.LlFunctionId)).ExecuteDeleteAsync(ct);
            await db.LlRegisterReferences.Where(x => ids.Contains(x.LlFunctionId)).ExecuteDeleteAsync(ct);
            await db.LlParseDiagnostics.Where(x => x.LlFunctionId != null && ids.Contains(x.LlFunctionId.Value))
                .ExecuteDeleteAsync(ct);
        }
    }

    private static bool TryMatchFunction(
        IReadOnlyList<FunctionMatchRow> functions,
        string fileName,
        LlAstFunctionResult ast,
        out Guid functionId)
    {
        var row = functions.FirstOrDefault(f =>
            f.StartLine == ast.StartLine
            && string.Equals(f.FunctionName, ast.FunctionName, StringComparison.Ordinal)
            && (string.Equals(f.Form, ast.Form, StringComparison.Ordinal) || f.Form == "inline_definition")
            && f.FilePath.Replace('\\', '/').EndsWith(fileName, StringComparison.OrdinalIgnoreCase));

        if (row is not null)
        {
            functionId = row.Id;
            return true;
        }

        var key = ScanImportService.BuildFunctionNaturalKey(ast.FilePath, ast.StartLine, ast.FunctionName, ast.Form);
        row = functions.FirstOrDefault(f => string.Equals(f.NaturalKey, key, StringComparison.Ordinal));
        if (row is not null)
        {
            functionId = row.Id;
            return true;
        }

        functionId = Guid.Empty;
        return false;
    }

    private static string NormalizeRelative(string fullPath, string llRoot)
    {
        var rel = Path.GetRelativePath(llRoot, fullPath).Replace('\\', '/');
        if (!rel.StartsWith("LL/", StringComparison.OrdinalIgnoreCase))
            rel = "LL/" + rel.TrimStart('/');
        return rel;
    }

    private sealed record FunctionMatchRow(
        Guid Id,
        string NaturalKey,
        string FunctionName,
        string FilePath,
        int StartLine,
        string? Form);
}
