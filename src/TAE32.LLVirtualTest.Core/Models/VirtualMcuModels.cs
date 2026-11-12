using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Models;

public sealed class VirtualMcuCreateOptions
{
    public Guid? SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public string? ChipModelName { get; set; }
    public string? DisplayName { get; set; }

    /// <summary>When SDK access is Unknown, treat as ReadWrite (default true) and mark limitation.</summary>
    public bool DefaultUnknownAccessToReadWrite { get; set; } = true;

    /// <summary>Protect bits with no named field as reserved when bitfields exist (default true).</summary>
    public bool ProtectUnmappedBitsAsReserved { get; set; } = true;

    /// <summary>Include RESERVED members as storage slots (default false — omit).</summary>
    public bool IncludeReservedMembers { get; set; } = false;
}

public sealed class VirtualMcuInfo
{
    public Guid Id { get; set; }
    public string DisplayName { get; set; } = string.Empty;
    public string ChipModelName { get; set; } = string.Empty;
    public Guid? ChipId { get; set; }
    public Guid? SdkProjectId { get; set; }
    public VirtualMcuLifecycleState State { get; set; }
    public int RegisterCount { get; set; }
    public int PeripheralCount { get; set; }
    public int TraceCount { get; set; }
    public IReadOnlyList<string> ActiveLimitations { get; set; } = Array.Empty<string>();
}

public sealed class VirtualRegisterView
{
    public Guid DefinitionId { get; set; }
    public string ChipModelName { get; set; } = string.Empty;
    public string? ModuleName { get; set; }
    public string? InstanceName { get; set; }
    public string StructName { get; set; } = string.Empty;
    public string MemberName { get; set; } = string.Empty;
    public string DisplayName => string.IsNullOrEmpty(InstanceName)
        ? $"{StructName}.{MemberName}"
        : $"{InstanceName}.{MemberName}";
    public uint? AbsoluteAddress { get; set; }
    public int WidthBits { get; set; }
    public uint CurrentValue { get; set; }
    public uint ResetValue { get; set; }
    public string AccessAttribute { get; set; } = "Unknown";
    public VirtualRegisterBehavior Behavior { get; set; }
    public uint WritableMask { get; set; } = 0xFFFFFFFFu;
    public SimulationLimitationKind Limitation { get; set; }
    public string LimitationNote { get; set; } = string.Empty;
    public IReadOnlyList<VirtualBitFieldView> Fields { get; set; } = Array.Empty<VirtualBitFieldView>();
}

public sealed class VirtualBitFieldView
{
    public string Name { get; set; } = string.Empty;
    public int BitPosition { get; set; }
    public int BitWidth { get; set; }
    public uint Mask { get; set; }
    public uint Value { get; set; }
    public string AccessAttribute { get; set; } = "Unknown";
}

public sealed class VirtualPeripheralView
{
    public string ModuleName { get; set; } = string.Empty;
    public string InstanceName { get; set; } = string.Empty;
    public string SimulatorKind { get; set; } = "Passthrough";
    public bool HasModeledBehavior { get; set; }
    public string StatusSummary { get; set; } = string.Empty;
    public IReadOnlyDictionary<string, string> State { get; set; }
        = new Dictionary<string, string>();
}

public sealed class VirtualAccessContext
{
    public string? LlFunctionName { get; set; }
    public string? SourceFile { get; set; }
    public int? SourceLine { get; set; }
    public string? Note { get; set; }
}

public sealed class VirtualAccessRecord
{
    public long Sequence { get; set; }
    public DateTimeOffset Timestamp { get; set; }
    public Guid McuId { get; set; }
    public VirtualAccessKind AccessKind { get; set; }
    public uint? Address { get; set; }
    public string RegisterName { get; set; } = string.Empty;
    public string? InstanceName { get; set; }
    public string? ModuleName { get; set; }
    public uint? RawValue { get; set; }
    public uint? ValueBefore { get; set; }
    public uint? ValueAfter { get; set; }
    public string? LlFunctionName { get; set; }
    public string? SourceFile { get; set; }
    public int? SourceLine { get; set; }
    public VirtualAccessResult Result { get; set; }
    public string? Message { get; set; }
    public SimulationLimitationKind Limitation { get; set; }
}

public sealed class VirtualAccessFilter
{
    public string? LlFunctionName { get; set; }
    public string? ModuleName { get; set; }
    public string? InstanceName { get; set; }
    public string? RegisterName { get; set; }
    public VirtualAccessKind? AccessKind { get; set; }
    public int Skip { get; set; }
    public int Take { get; set; } = 200;
}

public sealed class VirtualAccessResultDto
{
    public VirtualAccessResult Result { get; set; }
    public uint? Value { get; set; }
    public uint? ValueBefore { get; set; }
    public uint? ValueAfter { get; set; }
    public string? Message { get; set; }
    public SimulationLimitationKind Limitation { get; set; }
    public VirtualAccessRecord? Record { get; set; }
}

public sealed class VirtualMcuSnapshotInfo
{
    public Guid SnapshotId { get; set; }
    public Guid McuId { get; set; }
    public DateTimeOffset CreatedAt { get; set; }
    public string? Label { get; set; }
    public int RegisterCount { get; set; }
}

public sealed class VirtualPeripheralTreeNode
{
    public string Key { get; set; } = string.Empty;
    public string Title { get; set; } = string.Empty;
    public string? ModuleName { get; set; }
    public string? InstanceName { get; set; }
    public bool IsModule { get; set; }
    public IReadOnlyList<VirtualPeripheralTreeNode> Children { get; set; }
        = Array.Empty<VirtualPeripheralTreeNode>();
}
