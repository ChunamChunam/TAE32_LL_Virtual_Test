using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ILlTestCaseStore
{
    Task<IReadOnlyList<LlTestCase>> ListAsync(
        Guid? sdkProjectId = null,
        string? peripheralName = null,
        string? functionName = null,
        CancellationToken cancellationToken = default);

    Task<(IReadOnlyList<LlTestCase> Items, int TotalCount)> ListPagedAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        int skip = 0,
        int take = 100,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<LlTestCase>> ListFilteredAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default);

    Task<LlTestCase?> GetAsync(Guid id, CancellationToken cancellationToken = default);

    Task<LlTestCase> UpsertAsync(LlTestCaseEditModel model, CancellationToken cancellationToken = default);

    /// <summary>Insert many new auto-generated cases in one transaction (models must have Id = null).</summary>
    Task<int> InsertManyAsync(IReadOnlyList<LlTestCaseEditModel> models, CancellationToken cancellationToken = default);

    /// <summary>Bulk set Status=Ready for Draft cases matching the case-list filters. Unsupported is left unchanged.</summary>
    Task<int> MarkFilteredReadyAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default);

    Task<int> CountFilteredNotReadyAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default);

    Task DeleteAsync(Guid id, CancellationToken cancellationToken = default);

    Task<int> DeleteManyAsync(IEnumerable<Guid> ids, CancellationToken cancellationToken = default);

    Task<LlTestCase> DuplicateAsync(Guid id, CancellationToken cancellationToken = default);

    Task<string> ExportJsonAsync(IEnumerable<Guid> ids, CancellationToken cancellationToken = default);

    Task<int> ImportJsonAsync(Guid sdkProjectId, string json, CancellationToken cancellationToken = default);

    /// <summary>
    /// List recent runs. Prefer <paramref name="sdkProjectId"/> for batch history.
    /// When <paramref name="testCaseId"/> is set, only that case's runs are returned.
    /// </summary>
    Task<IReadOnlyList<LlTestRun>> ListRunsAsync(
        Guid? sdkProjectId = null,
        Guid? testCaseId = null,
        int take = 200,
        CancellationToken cancellationToken = default);

    Task<(IReadOnlyList<LlTestRun> Items, int TotalCount)> ListRunsPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        int skip = 0,
        int take = 50,
        CancellationToken cancellationToken = default);

    Task<int> DeleteRunsAsync(IEnumerable<Guid> runIds, CancellationToken cancellationToken = default);

    Task<LlTestRun?> GetRunAsync(Guid runId, CancellationToken cancellationToken = default);

    Task SaveRunAsync(LlTestRun run, CancellationToken cancellationToken = default);
}
