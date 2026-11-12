using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface IAppDataService
{
    Task<DashboardStats> GetDashboardStatsAsync(CancellationToken cancellationToken = default);

    Task<IReadOnlyList<Chip>> GetChipsAsync(Guid? sdkProjectId = null, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<Peripheral>> GetPeripheralsAsync(Guid? sdkProjectId = null, string? search = null, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<LlFunction>> GetFunctionsAsync(
        Guid? sdkProjectId = null,
        string? search = null,
        string? peripheralName = null,
        string? chipName = null,
        string? form = null,
        int skip = 0,
        int take = 200,
        CancellationToken cancellationToken = default);

    Task<int> CountFunctionsAsync(
        Guid? sdkProjectId = null,
        string? search = null,
        string? peripheralName = null,
        string? chipName = null,
        string? form = null,
        CancellationToken cancellationToken = default);

    Task<LlFunction?> GetFunctionByIdAsync(Guid id, CancellationToken cancellationToken = default);

    Task<LlFunctionDetailDto?> GetFunctionDetailAsync(Guid id, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<PeripheralInstance>> GetPeripheralInstancesAsync(
        Guid? sdkProjectId = null,
        Guid? peripheralId = null,
        string? search = null,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<RegisterCatalogDto>> GetRegistersAsync(
        Guid? sdkProjectId = null,
        Guid? chipId = null,
        Guid? peripheralId = null,
        Guid? instanceId = null,
        string? search = null,
        bool hideReserved = true,
        int skip = 0,
        int take = 200,
        CancellationToken cancellationToken = default);

    Task<int> CountRegistersAsync(
        Guid? sdkProjectId = null,
        Guid? chipId = null,
        Guid? peripheralId = null,
        Guid? instanceId = null,
        string? search = null,
        bool hideReserved = true,
        CancellationToken cancellationToken = default);

    Task<RegisterDetailDto?> GetRegisterDetailAsync(Guid registerId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<RegisterParseDiagnostic>> GetRegisterParseDiagnosticsAsync(
        Guid? sdkProjectId = null,
        CancellationToken cancellationToken = default);

    Task EnsureDatabaseCreatedAsync(CancellationToken cancellationToken = default);
}
