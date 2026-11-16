using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>Clang AST deep LL function parser.</summary>
public interface ILLFunctionParser
{
    /// <summary>Deep-parse all LL headers for an SDK project.</summary>
    Task<LlParseSummary> ParseAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);

    /// <summary>Deep-parse a single LL function (only its header). For quick test iteration.</summary>
    Task<LlParseSummary> ParseOneAsync(Guid llFunctionId, CancellationToken cancellationToken = default);
}
