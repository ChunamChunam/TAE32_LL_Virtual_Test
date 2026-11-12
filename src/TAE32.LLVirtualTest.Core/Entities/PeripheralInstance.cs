namespace TAE32.LLVirtualTest.Core.Entities;

public class PeripheralInstance
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public Guid? PeripheralId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? ModuleName { get; set; }
    public string? TypeDefName { get; set; }
    public uint? BaseAddress { get; set; }
    public string BaseAddressStatus { get; set; } = "Missing";
    public string? DefinitionFile { get; set; }
    public int? DefinitionLine { get; set; }
    public string NaturalKey { get; set; } = string.Empty;

    public SdkProject? SdkProject { get; set; }
    public Chip? Chip { get; set; }
    public Peripheral? Peripheral { get; set; }
    public ICollection<RegisterDefinition> Registers { get; set; } = new List<RegisterDefinition>();
}
