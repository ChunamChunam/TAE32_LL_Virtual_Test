using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlCallGraphAnalyzer
{
    public void Analyze(CXCursor body, LlAstFunctionResult result)
    {
        var counts = new Dictionary<string, (LlCalleeKind Kind, int Line, int Count)>(StringComparer.Ordinal);

        ClangCursorHelpers.VisitRecursive(body, (cursor, _) =>
        {
            if (cursor.Kind != CXCursorKind.CXCursor_CallExpr)
                return;

            var name = GetCalleeName(cursor);
            if (string.IsNullOrWhiteSpace(name))
                return;

            var kind = Classify(name);
            var line = ClangCursorHelpers.GetStartLine(cursor);
            if (counts.TryGetValue(name, out var existing))
                counts[name] = (kind, existing.Line, existing.Count + 1);
            else
                counts[name] = (kind, line, 1);
        });

        foreach (var (name, info) in counts.OrderBy(x => x.Key))
        {
            result.Calls.Add(new LlFunctionCall
            {
                CalleeName = name,
                CalleeKind = info.Kind.ToString(),
                CallLine = info.Line,
                CallCount = info.Count,
                CalleePeripheral = GuessPeripheral(name)
            });
        }
    }

    private static string GetCalleeName(CXCursor call)
    {
        foreach (var child in ClangCursorHelpers.Children(call))
        {
            if (child.Kind == CXCursorKind.CXCursor_DeclRefExpr)
                return ClangCursorHelpers.GetSpelling(child);
        }
        var spell = ClangCursorHelpers.GetSpelling(call);
        var idx = spell.IndexOf('(');
        return idx > 0 ? spell[..idx] : spell;
    }

    private static LlCalleeKind Classify(string name)
    {
        if (name.StartsWith("LL_", StringComparison.Ordinal)) return LlCalleeKind.LL;
        if (name.StartsWith("HAL_", StringComparison.Ordinal)) return LlCalleeKind.HAL;
        if (name.StartsWith("ASSERT_", StringComparison.Ordinal)) return LlCalleeKind.SdkInternal;
        if (name is "SET_BIT" or "CLEAR_BIT" or "READ_BIT" or "READ_REG" or "WRITE_REG" or "MODIFY_REG" or "POSITION_VAL")
            return LlCalleeKind.SdkInternal;
        return LlCalleeKind.External;
    }

    private static string? GuessPeripheral(string name)
    {
        if (!name.StartsWith("LL_", StringComparison.Ordinal)) return null;
        var parts = name.Split('_');
        return parts.Length > 1 ? parts[1] : null;
    }
}
