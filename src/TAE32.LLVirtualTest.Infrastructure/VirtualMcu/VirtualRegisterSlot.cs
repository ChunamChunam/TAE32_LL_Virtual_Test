using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal sealed class VirtualBitFieldSlot
{
    public string Name { get; init; } = string.Empty;
    public int BitPosition { get; init; }
    public int BitWidth { get; init; }
    public uint Mask { get; init; }
    public string AccessAttribute { get; init; } = "Unknown";
}

internal sealed class VirtualRegisterSlot
{
    public Guid DefinitionId { get; init; }
    public string ChipModelName { get; init; } = string.Empty;
    public string? ModuleName { get; init; }
    public string? InstanceName { get; init; }
    public string StructName { get; init; } = string.Empty;
    public string MemberName { get; init; } = string.Empty;
    public uint? AbsoluteAddress { get; init; }
    public int WidthBits { get; init; } = 32;
    public uint ResetValue { get; init; }
    public string AccessAttribute { get; init; } = "Unknown";
    public VirtualRegisterBehavior Behavior { get; init; }
    public SimulationLimitationKind Limitation { get; set; }
    public string LimitationNote { get; set; } = string.Empty;
    public uint WritableMask { get; init; } = 0xFFFFFFFFu;
    public List<VirtualBitFieldSlot> Fields { get; } = new();

    public uint CurrentValue { get; set; }

    public string NameKey => $"{InstanceName ?? StructName}.{MemberName}";

    public VirtualRegisterView ToView()
    {
        var widthMask = RegisterSemanticsEngine.WidthMask(WidthBits);
        return new VirtualRegisterView
        {
            DefinitionId = DefinitionId,
            ChipModelName = ChipModelName,
            ModuleName = ModuleName,
            InstanceName = InstanceName,
            StructName = StructName,
            MemberName = MemberName,
            AbsoluteAddress = AbsoluteAddress,
            WidthBits = WidthBits,
            CurrentValue = CurrentValue & widthMask,
            ResetValue = ResetValue & widthMask,
            AccessAttribute = AccessAttribute,
            Behavior = Behavior,
            WritableMask = WritableMask,
            Limitation = Limitation,
            LimitationNote = LimitationNote,
            Fields = Fields.Select(f => new VirtualBitFieldView
            {
                Name = f.Name,
                BitPosition = f.BitPosition,
                BitWidth = f.BitWidth,
                Mask = f.Mask,
                Value = (CurrentValue & f.Mask) >> f.BitPosition,
                AccessAttribute = f.AccessAttribute
            }).ToList()
        };
    }
}
