namespace TAE32.LLVirtualTest.Core.Models;

public sealed class LlFunctionCallRowDto
{
    public Guid CallId { get; init; }
    public Guid CallerFunctionId { get; init; }
    public string CallerName { get; init; } = string.Empty;
    public string CallerPeripheral { get; init; } = string.Empty;
    public string CalleeName { get; init; } = string.Empty;
    public string CalleeKind { get; init; } = string.Empty;
    public int CallLine { get; init; }
    public int CallCount { get; init; }
    public string? CallFile { get; init; }
    public string? CalleePeripheral { get; init; }
}

public sealed class CallGraphStats
{
    public int TotalEdges { get; init; }
    public int CallerFunctions { get; init; }
    public int UnknownCalleeEdges { get; init; }
    public int ParsedFunctionCount { get; init; }
}
