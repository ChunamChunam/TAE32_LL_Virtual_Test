using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Models;

public sealed class LlFunctionDetailDto
{
    public LlFunction Function { get; init; } = null!;
    public IReadOnlyList<LlFunctionParameter> Parameters { get; init; } = Array.Empty<LlFunctionParameter>();
    public IReadOnlyList<LlFunctionOperation> Operations { get; init; } = Array.Empty<LlFunctionOperation>();
    public IReadOnlyList<LlFunctionCall> Calls { get; init; } = Array.Empty<LlFunctionCall>();
    public IReadOnlyList<LlRegisterAccess> RegisterAccesses { get; init; } = Array.Empty<LlRegisterAccess>();
    public IReadOnlyList<LlRegisterReference> RegisterReferences { get; init; } = Array.Empty<LlRegisterReference>();
    public IReadOnlyList<LlParseDiagnostic> Diagnostics { get; init; } = Array.Empty<LlParseDiagnostic>();

    public LlParseStatus ParseStatus =>
        Enum.TryParse<LlParseStatus>(Function.ParseStatus, out var s) ? s : LlParseStatus.NotParsed;
}
