namespace TAE32.LLVirtualTest.Core.Entities;

public class RegisterMacroReference
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? RegisterDefinitionId { get; set; }
    public Guid? RegisterFieldId { get; set; }
    public string MacroName { get; set; } = string.Empty;
    public string MacroKind { get; set; } = "Other";
    public string? Expansion { get; set; }
    public string? DefinitionFile { get; set; }
    public int? DefinitionLine { get; set; }
    public string? ReferenceFile { get; set; }
    public int? ReferenceLine { get; set; }
    public bool Resolved { get; set; }

    public SdkProject? SdkProject { get; set; }
    public RegisterDefinition? RegisterDefinition { get; set; }
    public RegisterField? RegisterField { get; set; }
}
