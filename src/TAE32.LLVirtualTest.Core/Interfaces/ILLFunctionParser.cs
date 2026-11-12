using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>Clang AST deep LL function parser.</summary>
public interface ILLFunctionParser
{
    Task<LlParseSummary> ParseAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);
}
