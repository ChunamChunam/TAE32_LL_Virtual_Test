namespace TAE32.LLVirtualTest.Core.Models;

public sealed class LlParseSummary
{
    public Guid SdkProjectId { get; init; }
    public int HeadersAttempted { get; init; }
    public int HeadersSucceeded { get; init; }
    public int FunctionsParsed { get; init; }
    public int FunctionsMatched { get; init; }
    public int FunctionsUnmatched { get; init; }
    public int DiagnosticCount { get; init; }
    public bool UsedParseBridge { get; init; }
    public string? ClangVersion { get; init; }
    public DateTime CompletedAtUtc { get; init; } = DateTime.UtcNow;
    public string? Message { get; init; }
}
