namespace TAE32.LLVirtualTest.Core.Entities;

public class RegisterEnumValue
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid? RegisterFieldId { get; set; }
    public Guid? RegisterDefinitionId { get; set; }
    public string Name { get; set; } = string.Empty;
    public long? Value { get; set; }
    public string? Description { get; set; }
    public string? DefinitionFile { get; set; }
    public int? DefinitionLine { get; set; }

    public RegisterField? RegisterField { get; set; }
    public RegisterDefinition? RegisterDefinition { get; set; }
}
