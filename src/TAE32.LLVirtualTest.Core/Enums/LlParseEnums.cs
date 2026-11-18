namespace TAE32.LLVirtualTest.Core.Enums;

public enum LlParseStatus
{
    NotParsed = 0,
    InProgress = 1,
    Success = 2,
    Partial = 3,
    Failed = 4
}

public enum LlParseDiagnosticSeverity
{
    Info = 0,
    Warning = 1,
    Error = 2
}

public enum LlParseDiagnosticCategory
{
    General = 0,
    MissingSdkHeader = 1,
    ParseBridge = 2,
    Clang = 3,
    Match = 4,
    /// <summary>LL shift / mask / register-field static analysis (LlShiftStaticAnalyzer).</summary>
    StaticAnalysis = 5
}

public enum LlFunctionOpKind
{
    Unknown = 0,
    If = 1,
    For = 2,
    While = 3,
    Do = 4,
    Switch = 5,
    Return = 6,
    BinaryOperator = 7,
    UnaryOperator = 8,
    Call = 9,
    MemberRef = 10,
    CompoundAssign = 11,
    Decl = 12,
    Assign = 13
}

public enum LlRegisterAccessKind
{
    Read = 0,
    Write = 1,
    Modify = 2,
    Test = 3
}

public enum LlCalleeKind
{
    Unknown = 0,
    LL = 1,
    HAL = 2,
    SdkInternal = 3,
    External = 4,
    Indirect = 5
}

public enum LlMacroCategory
{
    Other = 0,
    Position = 1,
    Mask = 2,
    Shift = 3,
    Bit = 4,
    RegisterOp = 5
}
