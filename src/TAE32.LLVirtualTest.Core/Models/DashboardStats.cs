namespace TAE32.LLVirtualTest.Core.Models;

public sealed class DashboardStats
{
    public int SdkProjectCount { get; init; }
    public int ChipCount { get; init; }
    public int PeripheralCount { get; init; }
    public int LlFunctionCount { get; init; }
    public int InlineFunctionCount { get; init; }
    public string ScanStatusText { get; init; } = "尚未导入";
    public DateTime? LastImportedAtUtc { get; init; }
}
