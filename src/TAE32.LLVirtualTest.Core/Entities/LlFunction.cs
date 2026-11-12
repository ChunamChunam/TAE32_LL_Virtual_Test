namespace TAE32.LLVirtualTest.Core.Entities;

/// <summary>
/// LL function record. Unique identity is NOT FunctionName alone —
/// use NaturalKey = FilePath + StartLine + FunctionName (+ Form).
/// </summary>
public class LlFunction
{
    public Guid Id { get; set; } = Guid.NewGuid();

    public Guid SdkProjectId { get; set; }

    public Guid? ChipId { get; set; }

    public Guid? PeripheralId { get; set; }

    public Guid? SdkFileId { get; set; }

    public string FunctionName { get; set; } = string.Empty;

    public string? ReturnType { get; set; }

    public string? Parameters { get; set; }

    public string? FunctionType { get; set; }

    public string? Form { get; set; }

    public string? PeripheralName { get; set; }

    public string? ChipName { get; set; }

    public string FilePath { get; set; } = string.Empty;

    public int StartLine { get; set; }

    public int EndLine { get; set; }

    public string? DetectionStatus { get; set; }

    /// <summary>
    /// Stable natural key for upsert: normalized FilePath|StartLine|FunctionName|Form
    /// </summary>
    public string NaturalKey { get; set; } = string.Empty;

    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }

    // Phase-3 Clang AST parse fields (nullable for Phase-2 data)
    public string? Signature { get; set; }
    public string? SourceText { get; set; }
    public string? Modifiers { get; set; }
    public bool? IsStatic { get; set; }
    public bool? IsInline { get; set; }
    public string? ParseStatus { get; set; }
    public string? ClangVersion { get; set; }
    public DateTime? ParsedAtUtc { get; set; }
    public int? EndColumn { get; set; }
    public int? BodyStartLine { get; set; }
    public int? BodyEndLine { get; set; }

    public ICollection<LlFunctionParameter> ParseParameters { get; set; } = new List<LlFunctionParameter>();
    public ICollection<LlFunctionOperation> Operations { get; set; } = new List<LlFunctionOperation>();
    public ICollection<LlFunctionCall> Calls { get; set; } = new List<LlFunctionCall>();
    public ICollection<LlRegisterAccess> RegisterAccesses { get; set; } = new List<LlRegisterAccess>();
    public ICollection<LlRegisterReference> RegisterReferences { get; set; } = new List<LlRegisterReference>();

    public SdkProject? SdkProject { get; set; }
    public Chip? Chip { get; set; }
    public Peripheral? Peripheral { get; set; }
    public SdkFile? SdkFile { get; set; }
}
