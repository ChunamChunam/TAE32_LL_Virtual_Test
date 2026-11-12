using ClangSharp.Interop;

internal static class Program
{
    public static void Main()
    {
        var index = CXIndex.Create();
        var tu = CXTranslationUnit.CreateFromSourceFile(index, "dummy.c", ["-x", "c"], []);
        var root = tu.Cursor;
        _ = root.Kind;
        _ = root.IsDefinition;
        _ = root.Spelling;
        _ = root.Extent;
        _ = root.Location;
        _ = root.StorageClass;
        _ = root.ResultType;
        _ = root.IsFunctionInlined;
        unsafe
        {
            CXCursorVisitor visitor = Visitor;
            root.VisitChildren(visitor, default);
        }
        var loc = root.Location;
        loc.GetSpellingLocation(out var file, out var line, out var col, out _);
        _ = file.Name;
        _ = line;
        _ = col;
        tu.Dispose();
        index.Dispose();
        Console.WriteLine("ok");
    }

    private static unsafe CXChildVisitResult Visitor(CXCursor c, CXCursor p, void* clientData)
        => CXChildVisitResult.CXChildVisit_Continue;
}
