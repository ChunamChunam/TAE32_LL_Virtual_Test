namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>
/// Runs <c>LlShiftStaticAnalyzer</c> over LL functions and persists
/// <c>LlFunctions.StaticAnalysisJson</c> (typically after deep parse / register parse).
/// </summary>
public interface ILlStaticAnalysisPersistService
{
    /// <summary>Analyze all functions for a project that have SourceText (or resolvable FilePath).</summary>
    Task<LlStaticAnalysisPersistResult> AnalyzeProjectAsync(
        Guid sdkProjectId,
        CancellationToken cancellationToken = default);

    /// <summary>Analyze a subset of function ids (e.g. just deep-parsed).</summary>
    Task<LlStaticAnalysisPersistResult> AnalyzeFunctionsAsync(
        Guid sdkProjectId,
        IReadOnlyList<Guid> functionIds,
        CancellationToken cancellationToken = default);
}

public sealed class LlStaticAnalysisPersistResult
{
    public Guid SdkProjectId { get; init; }
    public int FunctionsConsidered { get; init; }
    public int FunctionsAnalyzed { get; init; }
    public int FunctionsCached { get; init; }
    public int WithErrors { get; init; }
    public int WithWarnings { get; init; }
    public string Message { get; init; } = string.Empty;
}
