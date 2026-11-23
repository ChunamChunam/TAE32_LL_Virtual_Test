using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ISdkProjectService
{
    Task<IReadOnlyList<SdkProject>> GetAllAsync(CancellationToken cancellationToken = default);

    /// <summary>Current workspace SDK (exactly one <c>IsActive</c> when possible).</summary>
    Task<SdkProject?> GetCurrentAsync(CancellationToken cancellationToken = default);

    /// <summary>Marks the project used for LL / tests / virtual MCU and clears other actives.</summary>
    Task SetCurrentAsync(Guid id, CancellationToken cancellationToken = default);

    Task<SdkProject?> GetByIdAsync(Guid id, CancellationToken cancellationToken = default);

    Task<SdkProject> AddAsync(string name, string sdkRootPath, string scanResultsPath, CancellationToken cancellationToken = default);

    /// <summary>Removes project metadata from DB only. Never deletes original SDK files.</summary>
    Task RemoveAsync(Guid id, CancellationToken cancellationToken = default);

    Task UpdatePathsAsync(Guid id, string sdkRootPath, string scanResultsPath, CancellationToken cancellationToken = default);
}
