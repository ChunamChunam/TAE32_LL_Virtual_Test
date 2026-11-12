using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.Core.Models;

public sealed class RegisterCatalogDto
{
    public RegisterDefinition Register { get; set; } = null!;
    public string? InstanceName { get; set; }
    public string? ModuleName { get; set; }
    public string? ChipName { get; set; }

    public string OffsetText =>
        Register.OffsetBytes is int o ? o.ToString() : "—";

    public string AbsoluteAddressText =>
        Register.AbsoluteAddress is uint a ? $"0x{a:X8}" : "—";
}

public sealed class RegisterDetailDto
{
    public RegisterDefinition Register { get; set; } = null!;
    public PeripheralInstance? Instance { get; set; }
    public IReadOnlyList<RegisterField> Fields { get; set; } = Array.Empty<RegisterField>();
    public IReadOnlyList<RegisterMacroReference> Macros { get; set; } = Array.Empty<RegisterMacroReference>();
    public IReadOnlyList<RegisterEnumValue> EnumValues { get; set; } = Array.Empty<RegisterEnumValue>();
    public IReadOnlyList<RegisterParseDiagnostic> Diagnostics { get; set; } = Array.Empty<RegisterParseDiagnostic>();
}
