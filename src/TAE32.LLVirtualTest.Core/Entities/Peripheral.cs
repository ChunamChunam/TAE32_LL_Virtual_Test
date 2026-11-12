namespace TAE32.LLVirtualTest.Core.Entities;

public class Peripheral
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public Guid SdkProjectId { get; set; }

    public Guid? ChipId { get; set; }

    public string Name { get; set; } = string.Empty;

    public int? SerialNumber { get; set; }

    public int InlineFunctionCount { get; set; }

    public int? AllFormsFunctionCount { get; set; }

    public string? InstancesJson { get; set; }

    public string? TypedefsJson { get; set; }

    public string? RelatedFilesJson { get; set; }

    public string? Confidence { get; set; }

    public string? DetectionStatus { get; set; }

    public string? Notes { get; set; }

    public bool IsCommonDriver { get; set; }

    /// <summary>Natural key within project: ChipModel + Name.</summary>
    public string NaturalKey { get; set; } = string.Empty;

    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public Chip? Chip { get; set; }
    public ICollection<LlFunction> Functions { get; set; } = new List<LlFunction>();
    public ICollection<SdkFile> Files { get; set; } = new List<SdkFile>();
}
