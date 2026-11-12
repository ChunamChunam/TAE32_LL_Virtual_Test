using System.Text.RegularExpressions;
using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlMacroReferenceCollector
{
    private static readonly Regex MacroPattern = new(
        @"\b([A-Z][A-Z0-9_]*(?:_Pos|_Msk|_Shift|_BIT))\b",
        RegexOptions.Compiled);

    private readonly string _filePath;
    private readonly string? _absoluteSourceFile;

    public LlMacroReferenceCollector(Guid sdkProjectId, string filePath, string? absoluteSourceFile = null)
    {
        _ = sdkProjectId;
        _filePath = filePath;
        _absoluteSourceFile = absoluteSourceFile;
    }

    public void Collect(CXCursor body, LlAstFunctionResult result)
    {
        ClangCursorHelpers.VisitRecursive(body, (cursor, _) =>
        {
            if (cursor.Kind is not (CXCursorKind.CXCursor_CallExpr
                or CXCursorKind.CXCursor_DeclRefExpr
                or CXCursorKind.CXCursor_MemberRefExpr
                or CXCursorKind.CXCursor_BinaryOperator))
                return;

            var line = ClangCursorHelpers.GetStartLine(cursor);
            var snippet = ClangCursorHelpers.ReadSourceLines(_absoluteSourceFile, line, line);
            if (string.IsNullOrWhiteSpace(snippet))
                snippet = ClangCursorHelpers.GetSpelling(cursor);

            foreach (Match m in MacroPattern.Matches(snippet))
            {
                result.RegisterReferences.Add(new LlRegisterReference
                {
                    MacroName = m.Groups[1].Value,
                    ReferenceFile = _filePath,
                    ReferenceLine = line,
                    ExpansionSnippet = m.Value
                });
            }
        });
    }
}
