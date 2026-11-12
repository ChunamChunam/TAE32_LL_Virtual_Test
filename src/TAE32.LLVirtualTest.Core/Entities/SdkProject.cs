using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Entities;

public class SdkProject
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public string Name { get; set; } = string.Empty;

    /// <summary>Absolute path to SDK package root (contains LL).</summary>
    public string SdkRootPath { get; set; } = string.Empty;

    /// <summary>Absolute path to ScanResults directory.</summary>
    public string ScanResultsPath { get; set; } = string.Empty;

    public string? Version { get; set; }

    public string? Description { get; set; }

    public ScanStatus ScanStatus { get; set; } = ScanStatus.NotScanned;

    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;

    public DateTime? UpdatedAtUtc { get; set; }

    public DateTime? LastImportedAtUtc { get; set; }

    public bool IsActive { get; set; } = true;

    public ICollection<Chip> Chips { get; set; } = new List<Chip>();
    public ICollection<SdkFile> Files { get; set; } = new List<SdkFile>();
    public ICollection<ScanRecord> ScanRecords { get; set; } = new List<ScanRecord>();
    public ICollection<PeripheralInstance> PeripheralInstances { get; set; } = new List<PeripheralInstance>();
    public ICollection<RegisterDefinition> RegisterDefinitions { get; set; } = new List<RegisterDefinition>();
    public ICollection<RegisterMacroReference> RegisterMacroReferences { get; set; } = new List<RegisterMacroReference>();
    public ICollection<RegisterParseDiagnostic> RegisterParseDiagnostics { get; set; } = new List<RegisterParseDiagnostic>();
}
