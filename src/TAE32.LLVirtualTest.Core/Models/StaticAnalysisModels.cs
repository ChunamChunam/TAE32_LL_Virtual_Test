namespace TAE32.LLVirtualTest.Core.Models;

/// <summary>LL source static-analysis diagnostic (shift / macro misuse).</summary>
public sealed class StaticAnalysisDiagnostic
{
    public string RuleId { get; set; } = string.Empty;
    public string Severity { get; set; } = "Warning";
    public string FunctionName { get; set; } = string.Empty;
    public string SourceFile { get; set; } = string.Empty;
    public int LineNumber { get; set; }
    public string Expression { get; set; } = string.Empty;
    public string Operator { get; set; } = string.Empty;
    public string LeftOperand { get; set; } = string.Empty;
    public string RightOperand { get; set; } = string.Empty;
    public string? ResolvedMacroValue { get; set; }
    public string? ExpectedOperandType { get; set; }
    public string? ActualOperandType { get; set; }
    public string Description { get; set; } = string.Empty;
    public string? SuggestedFix { get; set; }
}

public sealed class StaticAnalysisResult
{
    public bool HasBlockingError { get; set; }
    public bool HasWarning { get; set; }
    public IReadOnlyList<StaticAnalysisDiagnostic> Diagnostics { get; set; } = Array.Empty<StaticAnalysisDiagnostic>();

    public static StaticAnalysisResult Empty { get; } = new();
}

public enum SdkMacroSemanticKind
{
    Unknown = 0,
    BitFieldMask = 1,
    BitFieldPosition = 2,
    BitFieldValue = 3,
    RegisterBase = 4,
    RegisterOffset = 5,
    NumericOther = 6
}

public sealed class SdkMacroSemanticInfo
{
    public string Name { get; set; } = string.Empty;
    public uint? NumericValue { get; set; }
    public string? Expansion { get; set; }
    public SdkMacroSemanticKind Kind { get; set; } = SdkMacroSemanticKind.Unknown;
    public string? PeripheralHint { get; set; }
    public string? RegisterHint { get; set; }
    public string? FieldHint { get; set; }
    public string? DefinitionFile { get; set; }
}
