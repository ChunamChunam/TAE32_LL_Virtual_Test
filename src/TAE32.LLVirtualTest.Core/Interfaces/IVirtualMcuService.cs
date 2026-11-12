using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>
/// Phase-5 virtual MCU runtime. In-memory only — never mutates Phase-4 register definition tables.
/// Each Create produces an isolated instance (create / init / reset / snapshot / restore / destroy).
/// </summary>
public interface IVirtualMcuService
{
    Task<VirtualMcuInfo> CreateAsync(VirtualMcuCreateOptions options, CancellationToken cancellationToken = default);

    Task InitializeAsync(Guid mcuId, CancellationToken cancellationToken = default);

    /// <summary>Convenience: create (if needed) and initialize a virtual MCU bound to a chip.</summary>
    Task InitializeForChipAsync(Guid chipId, CancellationToken cancellationToken = default);

    Task ResetAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task DestroyAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualMcuInfo>> ListAsync(CancellationToken cancellationToken = default);

    Task<VirtualMcuInfo?> GetInfoAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task<VirtualMcuSnapshotInfo> TakeSnapshotAsync(Guid mcuId, string? label = null, CancellationToken cancellationToken = default);

    Task RestoreSnapshotAsync(Guid mcuId, Guid snapshotId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualMcuSnapshotInfo>> ListSnapshotsAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualPeripheralTreeNode>> GetPeripheralTreeAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualRegisterView>> GetRegistersAsync(
        Guid mcuId,
        string? moduleName = null,
        string? instanceName = null,
        CancellationToken cancellationToken = default);

    Task<VirtualRegisterView?> GetRegisterAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualPeripheralView>> GetPeripheralStatesAsync(Guid mcuId, CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> ReadAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> ReadByAddressAsync(
        Guid mcuId,
        uint address,
        int widthBits = 32,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> WriteAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        uint value,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> WriteByAddressAsync(
        Guid mcuId,
        uint address,
        uint value,
        int widthBits = 32,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> SetBitsAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        uint mask,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> ClearBitsAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        uint mask,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> ModifyBitsAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        uint clearMask,
        uint setMask,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> WriteBitFieldAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        string fieldName,
        uint fieldValue,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<VirtualAccessResultDto> ResetRegisterAsync(
        Guid mcuId,
        string instanceOrStruct,
        string memberName,
        VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<VirtualAccessRecord>> GetAccessTraceAsync(
        Guid mcuId,
        VirtualAccessFilter? filter = null,
        CancellationToken cancellationToken = default);

    Task ClearAccessTraceAsync(Guid mcuId, CancellationToken cancellationToken = default);
}
