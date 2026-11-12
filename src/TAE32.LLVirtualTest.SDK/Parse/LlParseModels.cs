using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlAstFunctionResult
{
    public string FunctionName { get; init; } = string.Empty;
    public string ReturnType { get; init; } = string.Empty;
    public string Signature { get; init; } = string.Empty;
    public string? Modifiers { get; init; }
    public bool IsStatic { get; init; }
    public bool IsInline { get; init; }
    public int StartLine { get; init; }
    public int EndLine { get; init; }
    public int? EndColumn { get; init; }
    public int? BodyStartLine { get; init; }
    public int? BodyEndLine { get; init; }
    public string? SourceText { get; init; }
    public string FilePath { get; init; } = string.Empty;
    public string Form { get; init; } = "inline_definition";
    public bool ParseSucceeded { get; init; }
    public List<LlFunctionParameter> Parameters { get; } = new();
    public List<LlFunctionOperation> Operations { get; } = new();
    public List<LlFunctionCall> Calls { get; } = new();
    public List<LlRegisterAccess> RegisterAccesses { get; } = new();
    public List<LlRegisterReference> RegisterReferences { get; } = new();
    public List<LlParseDiagnostic> Diagnostics { get; } = new();
}
