using System.Text;
using ClangSharp.Interop;

namespace TAE32.LLVirtualTest.SDK.Parse;

internal static class ClangCursorHelpers
{
    public static unsafe void VisitRecursive(CXCursor root, Action<CXCursor, CXCursor> visitor)
    {
        CXCursorVisitor callback = (cursor, parent, _) =>
        {
            visitor(cursor, parent);
            return CXChildVisitResult.CXChildVisit_Recurse;
        };
        root.VisitChildren(callback, default);
    }

    public static unsafe List<CXCursor> Children(CXCursor parent)
    {
        var list = new List<CXCursor>();
        CXCursorVisitor callback = (cursor, _, _) =>
        {
            list.Add(cursor);
            return CXChildVisitResult.CXChildVisit_Continue;
        };
        parent.VisitChildren(callback, default);
        return list;
    }

    public static unsafe CXCursor? FindChild(CXCursor parent, CXCursorKind kind)
    {
        CXCursor? found = null;
        CXCursorVisitor callback = (cursor, _, _) =>
        {
            if (cursor.Kind == kind)
            {
                found = cursor;
                return CXChildVisitResult.CXChildVisit_Break;
            }
            return CXChildVisitResult.CXChildVisit_Continue;
        };
        parent.VisitChildren(callback, default);
        return found;
    }

    public static int GetStartLine(CXCursor cursor)
    {
        cursor.Extent.Start.GetSpellingLocation(out _, out var line, out _, out _);
        return (int)line;
    }

    public static int GetEndLine(CXCursor cursor)
    {
        cursor.Extent.End.GetSpellingLocation(out _, out var line, out _, out _);
        return (int)line;
    }

    public static string GetSpelling(CXCursor cursor) => cursor.Spelling.ToString();

    public static string GetResultTypeSpelling(CXCursor cursor) => cursor.ResultType.Spelling.ToString();

    public static bool IsFromFile(CXCursor cursor, string fileName)
    {
        cursor.Location.GetSpellingLocation(out var file, out _, out _, out _);
        if (file.Handle == default) return false;
        return file.Name.ToString().EndsWith(fileName, StringComparison.OrdinalIgnoreCase);
    }

    public static string? GetPhysicalFilePath(CXCursor cursor)
    {
        cursor.Location.GetSpellingLocation(out var file, out _, out _, out _);
        if (file.Handle == default) return null;
        return file.Name.ToString();
    }

    public static string? ReadSourceLines(string? sourceFile, int startLine, int endLine)
    {
        if (string.IsNullOrWhiteSpace(sourceFile) || !File.Exists(sourceFile))
            return null;
        try
        {
            var lines = File.ReadAllLines(sourceFile, Encoding.UTF8);
            if (startLine < 1 || startLine > lines.Length) return null;
            var end = Math.Min(endLine, lines.Length);
            return string.Join(Environment.NewLine, lines.Skip(startLine - 1).Take(end - startLine + 1));
        }
        catch
        {
            return null;
        }
    }
}
