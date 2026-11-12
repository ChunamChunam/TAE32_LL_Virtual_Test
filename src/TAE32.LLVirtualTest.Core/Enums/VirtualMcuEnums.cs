namespace TAE32.LLVirtualTest.Core.Enums;

/// <summary>Runtime access kind recorded by the virtual MCU.</summary>
public enum VirtualAccessKind
{
    Read,
    Write,
    SetBits,
    ClearBits,
    ModifyBits,
    WriteBitField,
    Reset,
    Snapshot,
    Restore
}

/// <summary>Outcome of a virtual register access.</summary>
public enum VirtualAccessResult
{
    Ok,
    RejectedReadOnly,
    RejectedWriteOnly,
    RejectedReserved,
    AddressOutOfRange,
    WidthMismatch,
    NotFound,
    LimitationApplied,
    Error
}

/// <summary>
/// Effective write/read semantics used by the simulator.
/// When SDK access is Unknown, defaults apply and are marked as limitations.
/// </summary>
public enum VirtualRegisterBehavior
{
    /// <summary>Normal read/write (masked by reserved bits if configured).</summary>
    ReadWrite,
    ReadOnly,
    WriteOnly,
    /// <summary>Write-1-to-clear: writing 1 clears corresponding stored bits.</summary>
    Write1Clear,
    /// <summary>Write-0-to-clear: writing 0 clears corresponding stored bits.</summary>
    Write0Clear,
    /// <summary>Read clears all bits (RC).</summary>
    ReadClear,
    Reserved
}

/// <summary>Documents what is simulated vs not yet modeled.</summary>
public enum SimulationLimitationKind
{
    None,
    /// <summary>Access attribute was Unknown; default ReadWrite applied.</summary>
    UnknownAccessDefaultedToRw,
    /// <summary>Reset value missing; zero used.</summary>
    MissingResetValueAssumedZero,
    /// <summary>No absolute address; name-based access only (or synthetic map key).</summary>
    MissingAbsoluteAddress,
    /// <summary>Peripheral side-effects not modeled beyond register storage.</summary>
    PeripheralBehaviorNotModeled,
    /// <summary>W1C/W0C/RC not declared by SDK; only active if explicitly configured.</summary>
    SpecialWriteSemanticsNotDeclared,
    /// <summary>Reserved-bit mask incomplete; unprotected bits may be writable.</summary>
    IncompleteReservedMask
}

public enum VirtualMcuLifecycleState
{
    Created,
    Initialized,
    Reset,
    Destroyed
}
