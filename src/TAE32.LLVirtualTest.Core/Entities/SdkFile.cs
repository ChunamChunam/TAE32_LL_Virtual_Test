namespace TAE32.LLVirtualTest.Core.Entities;

public class SdkFile
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public Guid SdkProjectId { get; set; }

    public Guid? PeripheralId { get; set; }

    public string RelativePath { get; set; } = string.Empty;

    public string FileName { get; set; } = string.Empty;

    public string Extension { get; set; } = string.Empty;

    public string? Role { get; set; }

    public long? SizeBytes { get; set; }

    /// <summary>Natural key within project: RelativePath (normalized).</summary>
    public string NaturalKey { get; set; } = string.Empty;

    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public Peripheral? Peripheral { get; set; }
    public ICollection<LlFunction> Functions { get; set; } = new List<LlFunction>();
}
