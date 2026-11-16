namespace TAE32.LLVirtualTest.Core.Enums;

public enum RegisterAccessAttributeKind
{
    Ro,
    Wo,
    Rw,
    W1c,
    W0c,
    W1s,
    Toggle,
    Rc,
    Reserved,
    Unknown
}

public enum AddressConfirmationStatus
{
    Confirmed,
    PendingConfirmation,
    Missing
}

public enum RegisterEntityParseStatus
{
    Complete,
    Partial,
    Unconfirmed,
    Failed
}

public enum RegisterMacroKind
{
    Pos,
    Msk,
    Shift,
    Bit,
    Other
}

public enum RegisterParseDiagnosticSeverity
{
    Info,
    Warning,
    Error
}

public enum RegisterParseDiagnosticCategory
{
    MissingSdkHeader,
    PendingConfirmation,
    Environment,
    DeviceHeader,
    LlEvidence,
    General
}
