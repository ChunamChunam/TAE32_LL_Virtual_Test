using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ICompilerService
{
    Task<CompilerEnvironmentInfo> CheckEnvironmentAsync(
        Guid sdkProjectId,
        string? clangPathOverride = null,
        CancellationToken cancellationToken = default);

    Task SaveClangPathAsync(string? clangPath, CancellationToken cancellationToken = default);

    /// <summary>
    /// Ensure a portable Clang exists under LocalAppData (download+silent install if missing).
    /// Returns the clang.exe path when successful.
    /// </summary>
    Task<EmbeddedClangResult> EnsureEmbeddedClangAsync(
        IProgress<string>? progress = null,
        CancellationToken cancellationToken = default);

    Task<CompileJobResult> CompileHarnessAsync(
        Guid sdkProjectId,
        string harnessCPath,
        string outputDllPath,
        IReadOnlyList<string>? extraDefines = null,
        CancellationToken cancellationToken = default);
}
