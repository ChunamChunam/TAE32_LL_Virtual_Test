using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>SDK register definition parsing (Phase 4).</summary>
public interface IRegisterParser
{
    Task<RegisterParseSummary> ParseAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);
}
