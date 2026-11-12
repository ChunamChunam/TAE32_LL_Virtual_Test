namespace TAE32.LLVirtualTest.Core.Entities;

public class RegisterDefinition
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public Guid? PeripheralId { get; set; }
    public Guid? PeripheralInstanceId { get; set; }
    public string StructName { get; set; } = string.Empty;
    public string MemberName { get; set; } = string.Empty;
    public string? MemberType { get; set; }
    public int? OffsetBytes { get; set; }
    public string OffsetStatus { get; set; } = "PendingConfirmation";
    public uint? AbsoluteAddress { get; set; }
    public string AbsoluteAddressStatus { get; set; } = "PendingConfirmation";
    public int? WidthBits { get; set; }
    public string? ResetValue { get; set; }
    public string AccessAttribute { get; set; } = "Unknown";
    public string? Comment { get; set; }
    public string DefinitionFile { get; set; } = string.Empty;
    public int StartLine { get; set; }
    public int EndLine { get; set; }
    public string ParseStatus { get; set; } = "Unconfirmed";
    public string NaturalKey { get; set; } = string.Empty;

    public SdkProject? SdkProject { get; set; }
    public Chip? Chip { get; set; }
    public Peripheral? Peripheral { get; set; }
    public PeripheralInstance? PeripheralInstance { get; set; }
    public ICollection<RegisterField> Fields { get; set; } = new List<RegisterField>();
    public ICollection<RegisterMacroReference> MacroReferences { get; set; } = new List<RegisterMacroReference>();
    public ICollection<RegisterEnumValue> EnumValues { get; set; } = new List<RegisterEnumValue>();
}
