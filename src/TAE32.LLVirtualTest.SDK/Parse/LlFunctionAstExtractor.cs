using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlFunctionAstExtractor
{
    private readonly Guid _sdkProjectId;
    private readonly string _relativeHeaderPath;
    private readonly string _headerFileName;
    private readonly string? _absoluteHeaderPath;

    public LlFunctionAstExtractor(Guid sdkProjectId, string relativeHeaderPath, string headerFileName, string? absoluteHeaderPath = null)
    {
        _sdkProjectId = sdkProjectId;
        _relativeHeaderPath = NormalizePath(relativeHeaderPath);
        _headerFileName = headerFileName;
        _absoluteHeaderPath = absoluteHeaderPath;
    }

    public IReadOnlyList<LlAstFunctionResult> Extract(ParseTranslationResult parseResult)
    {
        var results = new Dictionary<string, LlAstFunctionResult>(StringComparer.Ordinal);

        ClangCursorHelpers.VisitRecursive(parseResult.RootCursor, (cursor, _) =>
        {
            if (cursor.Kind != CXCursorKind.CXCursor_FunctionDecl)
                return;
            if (!cursor.IsDefinition)
                return;
            if (!ClangCursorHelpers.IsFromFile(cursor, _headerFileName))
                return;

            var name = ClangCursorHelpers.GetSpelling(cursor);
            if (string.IsNullOrWhiteSpace(name))
                return;

            var startLine = ClangCursorHelpers.GetStartLine(cursor);
            var key = $"{startLine}|{name}";
            results[key] = BuildFunction(cursor, name, startLine);
        });

        return results.Values.ToList();
    }

    private LlAstFunctionResult BuildFunction(CXCursor cursor, string name, int startLine)
    {
        var returnType = ClangCursorHelpers.GetResultTypeSpelling(cursor);
        var parms = ExtractParameters(cursor);
        var signature = $"{returnType} {name}({string.Join(", ", parms.Select(p => p.RawText))})";

        var isInline = cursor.IsFunctionInlined;
        var isStatic = cursor.StorageClass == CX_StorageClass.CX_SC_Static;
        var modifiers = (isStatic, isInline) switch
        {
            (true, true) => "static inline",
            (true, false) => "static",
            (false, true) => "inline",
            _ => null
        };

        CXCursor? bodyCursor = ClangCursorHelpers.FindChild(cursor, CXCursorKind.CXCursor_CompoundStmt);
        int? bodyStart = bodyCursor.HasValue ? ClangCursorHelpers.GetStartLine(bodyCursor.Value) : null;
        int? bodyEnd = bodyCursor.HasValue ? ClangCursorHelpers.GetEndLine(bodyCursor.Value) : null;

        var physical = ClangCursorHelpers.GetPhysicalFilePath(cursor) ?? _absoluteHeaderPath;
        var source = ClangCursorHelpers.ReadSourceLines(physical, startLine, ClangCursorHelpers.GetEndLine(cursor));

        var result = new LlAstFunctionResult
        {
            FunctionName = name,
            ReturnType = returnType,
            Signature = signature,
            Modifiers = modifiers,
            IsStatic = isStatic,
            IsInline = isInline,
            StartLine = startLine,
            EndLine = ClangCursorHelpers.GetEndLine(cursor),
            BodyStartLine = bodyStart,
            BodyEndLine = bodyEnd,
            SourceText = source,
            FilePath = _relativeHeaderPath,
            Form = "inline_definition",
            ParseSucceeded = bodyCursor.HasValue
        };

        if (!result.ParseSucceeded)
        {
            result.Diagnostics.Add(new LlParseDiagnostic
            {
                SdkProjectId = _sdkProjectId,
                Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                Category = LlParseDiagnosticCategory.Clang.ToString(),
                Message = $"Function {name} has no compound body in AST",
                FilePath = _relativeHeaderPath,
                Line = result.StartLine
            });
        }
        else
        {
            new LlOperationAnalyzer().Analyze(bodyCursor!.Value, result);
            new LlRegisterAccessAnalyzer().Analyze(bodyCursor.Value, result);
            new LlCallGraphAnalyzer().Analyze(bodyCursor.Value, result);
            new LlMacroReferenceCollector(_sdkProjectId, _relativeHeaderPath, physical).Collect(bodyCursor.Value, result);
        }

        result.Parameters.AddRange(parms);
        return result;
    }

    private static List<LlFunctionParameter> ExtractParameters(CXCursor func)
    {
        var list = new List<LlFunctionParameter>();
        var pos = 0;
        foreach (var child in ClangCursorHelpers.Children(func))
        {
            if (child.Kind != CXCursorKind.CXCursor_ParmDecl)
                continue;
            var type = child.Type.Spelling.ToString();
            var name = ClangCursorHelpers.GetSpelling(child);
            if (string.IsNullOrWhiteSpace(name))
                name = $"p{pos}";
            list.Add(new LlFunctionParameter
            {
                Name = name,
                Type = type,
                Position = pos,
                IsConst = type.Contains("const", StringComparison.Ordinal),
                IsPointer = type.Contains('*'),
                RawText = $"{type} {name}".Trim()
            });
            pos++;
        }
        return list;
    }

    private static string NormalizePath(string path) => path.Replace('\\', '/').Trim().TrimStart('/');
}
