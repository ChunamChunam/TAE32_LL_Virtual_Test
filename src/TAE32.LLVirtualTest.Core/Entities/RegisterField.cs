namespace TAE32.LLVirtualTest.Core.Entities;

public class RegisterField
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid RegisterDefinitionId { get; set; }
    public string Name { get; set; } = string.Empty;
    public int? BitPosition { get; set; }
    public int? BitWidth { get; set; }
    public uint? Mask { get; set; }
    public string? MaskExpression { get; set; }
    public string? ResetValue { get; set; }
    public string AccessAttribute { get; set; } = "Unknown";
    public string? Description { get; set; }
    public string? PosMacroName { get; set; }
    public string? MskMacroName { get; set; }
    public string? DefinitionFile { get; set; }
    public int? DefinitionLine { get; set; }
    public string ParseStatus { get; set; } = "Unconfirmed";
    public string NaturalKey { get; set; } = string.Empty;

    public RegisterDefinition? RegisterDefinition { get; set; }
    public ICollection<RegisterMacroReference> MacroReferences { get; set; } = new List<RegisterMacroReference>();
    public ICollection<RegisterEnumValue> EnumValues { get; set; } = new List<RegisterEnumValue>();
}
