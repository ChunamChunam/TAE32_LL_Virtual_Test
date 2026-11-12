using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Entities;

public class ScanRecord
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public Guid SdkProjectId { get; set; }

    public DateTime StartedAtUtc { get; set; } = DateTime.UtcNow;

    public DateTime? FinishedAtUtc { get; set; }

    public ScanStatus Status { get; set; } = ScanStatus.NotScanned;

    public string SourceDirectory { get; set; } = string.Empty;

    public int ChipCount { get; set; }

    public int PeripheralCount { get; set; }

    public int FunctionCount { get; set; }

    public int FileCount { get; set; }

    public int InsertedCount { get; set; }

    public int UpdatedCount { get; set; }

    public int SkippedCount { get; set; }

    public int ErrorCount { get; set; }

    public string? SummaryJson { get; set; }

    public string? ErrorSummary { get; set; }

    public SdkProject? SdkProject { get; set; }
}
