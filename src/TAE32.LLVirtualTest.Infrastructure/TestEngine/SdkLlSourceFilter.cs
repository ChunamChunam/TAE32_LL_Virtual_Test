namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>Detects LL inline functions that exist in scan DB but are excluded by SDK #if 0.</summary>
internal static class SdkLlSourceFilter
{
    public static bool IsInlineAvailableInSdk(string? sourceFilePath, string functionName)
    {
        if (string.IsNullOrWhiteSpace(sourceFilePath) || !File.Exists(sourceFilePath))
            return true;
        if (string.IsNullOrWhiteSpace(functionName))
            return true;

        var text = File.ReadAllText(sourceFilePath);
        var marker = functionName + "(";
        var searchFrom = 0;
        while (searchFrom < text.Length)
        {
            var idx = text.IndexOf(marker, searchFrom, StringComparison.Ordinal);
            if (idx < 0)
                return false;

            var lineStart = text.LastIndexOf('\n', Math.Max(0, idx - 1)) + 1;
            if (IsInsideDisabledIf0(text, lineStart))
            {
                searchFrom = idx + marker.Length;
                continue;
            }

            var paren = idx + functionName.Length;
            var brace = text.IndexOf('{', paren);
            if (brace < 0)
            {
                searchFrom = idx + marker.Length;
                continue;
            }

            var between = text[paren..brace];
            searchFrom = idx + marker.Length;
            if (between.Contains(';'))
                continue;

            return true;
        }

        return false;
    }

    private static bool IsInsideDisabledIf0(string text, int position)
    {
        var disabledDepth = 0;
        var i = 0;
        while (i < position)
        {
            if (i + 3 < text.Length && text.AsSpan(i, 4).Equals("#if ", StringComparison.Ordinal))
            {
                var lineEnd = text.IndexOf('\n', i);
                if (lineEnd < 0) lineEnd = text.Length;
                var expr = text[(i + 4)..lineEnd].Trim();
                if (IsFalseIfExpression(expr))
                    disabledDepth++;
                i = lineEnd + 1;
                continue;
            }

            if (disabledDepth > 0 && i + 5 < text.Length && text.AsSpan(i, 6).Equals("#elif ", StringComparison.Ordinal))
            {
                var lineEnd = text.IndexOf('\n', i);
                if (lineEnd < 0) lineEnd = text.Length;
                var expr = text[(i + 6)..lineEnd].Trim();
                disabledDepth = IsFalseIfExpression(expr) ? disabledDepth : 0;
                i = lineEnd + 1;
                continue;
            }

            if (disabledDepth > 0 && i + 5 < text.Length && text.AsSpan(i, 6).Equals("#endif", StringComparison.Ordinal))
            {
                disabledDepth = 0;
                i += 6;
                continue;
            }

            i++;
        }

        return disabledDepth > 0;
    }

    private static bool IsFalseIfExpression(string expr)
        => expr == "0" || expr.StartsWith("0/", StringComparison.Ordinal) || expr.StartsWith("0 ", StringComparison.Ordinal);
}
