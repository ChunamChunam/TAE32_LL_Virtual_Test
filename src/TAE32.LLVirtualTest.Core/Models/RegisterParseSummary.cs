namespace TAE32.LLVirtualTest.Core.Models;

public sealed class RegisterParseSummary
{
    public Guid SdkProjectId { get; set; }
    public string? Message { get; set; }
    public bool UsedDeviceHeader { get; set; }
    public bool UsedParseBridgeEvidenceOnly { get; set; }
    public int InstanceCount { get; set; }
    public int RegisterCount { get; set; }
    public int FieldCount { get; set; }
    public int MacroReferenceCount { get; set; }
    public int ResolvedMacroCount { get; set; }
    public int DiagnosticCount { get; set; }
    public IReadOnlyList<string> FoundHeaders { get; set; } = Array.Empty<string>();
    public IReadOnlyList<string> MissingHeaders { get; set; } = Array.Empty<string>();
}
