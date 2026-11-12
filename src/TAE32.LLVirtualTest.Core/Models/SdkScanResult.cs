namespace TAE32.LLVirtualTest.Core.Models;

public sealed class SdkScanResult
{
    public bool Success { get; init; }
    public string Message { get; init; } = string.Empty;
    public string SdkRootPath { get; init; } = string.Empty;
    public string LlRootPath { get; init; } = string.Empty;
    public string OutputDirectory { get; init; } = string.Empty;
    public int ChipCount { get; init; }
    public int PeripheralCount { get; init; }
    public int FunctionCount { get; init; }
    public int InlineFunctionCount { get; init; }
    public int FileCount { get; init; }
    public IReadOnlyList<string> GeneratedFiles { get; init; } = Array.Empty<string>();
    public IReadOnlyList<string> Errors { get; init; } = Array.Empty<string>();
}
