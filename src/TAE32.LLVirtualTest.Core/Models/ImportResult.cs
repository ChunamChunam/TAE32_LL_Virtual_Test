namespace TAE32.LLVirtualTest.Core.Models;

public sealed class ImportResult
{
    public bool Success { get; init; }
    public Guid ScanRecordId { get; init; }
    public int ChipCount { get; init; }
    public int PeripheralCount { get; init; }
    public int FunctionCount { get; init; }
    public int FileCount { get; init; }
    public int InsertedCount { get; init; }
    public int UpdatedCount { get; init; }
    public int SkippedCount { get; init; }
    public int ErrorCount { get; init; }
    public IReadOnlyList<string> Errors { get; init; } = Array.Empty<string>();
    public string Message { get; init; } = string.Empty;
}
