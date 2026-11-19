using System.Text;
using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Sdk;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class ClangAstSession : IDisposable
{
    private CXIndex _index;
    private CXTranslationUnit _tu;
    private bool _hasTu;
    private bool _disposed;

    public ParseTranslationResult ParseHeader(string wrapperSourcePath, string[] clangArgs, string mainFileName)
    {
        if (_disposed) throw new ObjectDisposedException(nameof(ClangAstSession));
        if (_hasTu)
        {
            _tu.Dispose();
            _hasTu = false;
        }

        if (_index.Handle == default)
            _index = CXIndex.Create();

        var args = clangArgs.AsSpan();
        _tu = CXTranslationUnit.CreateFromSourceFile(_index, wrapperSourcePath, args, ReadOnlySpan<CXUnsavedFile>.Empty);
        _hasTu = true;

        var diags = new List<string>();
        var count = _tu.NumDiagnostics;
        for (uint i = 0; i < count; i++)
        {
            using var d = _tu.GetDiagnostic(i);
            if (d.Severity >= CXDiagnosticSeverity.CXDiagnostic_Warning)
                diags.Add(d.Format(CXDiagnosticDisplayOptions.CXDiagnostic_DisplaySourceLocation).ToString());
        }

        return new ParseTranslationResult(_tu, _tu.Cursor, diags, mainFileName, wrapperSourcePath);
    }

    public static string CreateWrapperFile(
        string tempDir,
        string includeHeaderFileName,
        bool includeParseBridgeConf = true,
        string? llConfFileName = null)
    {
        Directory.CreateDirectory(tempDir);
        var wrapper = Path.Combine(tempDir, $"wrap_{includeHeaderFileName}.c");
        var sb = new StringBuilder();
        sb.AppendLine("/* Auto wrapper for Clang TU */");
        if (includeParseBridgeConf)
            sb.AppendLine(
                $"#include \"{llConfFileName ?? SdkSeriesLayout.FallbackFamilyId + "_ll_conf.h"}\"");
        sb.AppendLine($"#include \"{includeHeaderFileName}\"");
        File.WriteAllText(wrapper, sb.ToString(), Encoding.UTF8);
        return wrapper;
    }

    public void Dispose()
    {
        if (_disposed) return;
        if (_hasTu) _tu.Dispose();
        if (_index.Handle != default) _index.Dispose();
        _disposed = true;
    }
}

public sealed class ParseTranslationResult
{
    public CXTranslationUnit TranslationUnit { get; }
    public CXCursor RootCursor { get; }
    public IReadOnlyList<string> ClangDiagnostics { get; }
    public string MainHeaderFileName { get; }
    public string WrapperPath { get; }

    public ParseTranslationResult(CXTranslationUnit tu, CXCursor root, IReadOnlyList<string> diags, string mainHeader, string wrapperPath)
    {
        TranslationUnit = tu;
        RootCursor = root;
        ClangDiagnostics = diags;
        MainHeaderFileName = mainHeader;
        WrapperPath = wrapperPath;
    }
}
