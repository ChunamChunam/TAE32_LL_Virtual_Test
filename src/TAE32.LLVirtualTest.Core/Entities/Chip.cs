namespace TAE32.LLVirtualTest.Core.Entities;

public class Chip
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public Guid SdkProjectId { get; set; }

    public string ModelName { get; set; } = string.Empty;

    public string? Level { get; set; }

    public string? DetectionStatus { get; set; }

    public string? Confidence { get; set; }

    public string? Notes { get; set; }

    /// <summary>Business natural key within a project: ModelName.</summary>
    public string NaturalKey { get; set; } = string.Empty;

    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public ICollection<Peripheral> Peripherals { get; set; } = new List<Peripheral>();
    public ICollection<LlFunction> Functions { get; set; } = new List<LlFunction>();
}
