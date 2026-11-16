using System.Collections.Concurrent;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

public sealed class VirtualMcuService : IVirtualMcuService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ConcurrentDictionary<Guid, VirtualMcuRuntime> _mcus = new();
    private Guid? _legacyChipBoundId;

    public VirtualMcuService(IDbContextFactory<AppDbContext> dbFactory)
    {
        _dbFactory = dbFactory;
    }

    public async Task<VirtualMcuInfo> CreateAsync(VirtualMcuCreateOptions options, CancellationToken cancellationToken = default)
    {
        options ??= new VirtualMcuCreateOptions();
        var id = Guid.NewGuid();
        var chipModel = await ResolveChipModelAsync(options, cancellationToken);
        options.ChipModelName ??= chipModel;
        var runtime = new VirtualMcuRuntime(id, options, chipModel);
        if (!_mcus.TryAdd(id, runtime))
            throw new InvalidOperationException("无法创建虚拟 MCU");
        return runtime.ToInfo();
    }

    private async Task<string> ResolveChipModelAsync(VirtualMcuCreateOptions options, CancellationToken cancellationToken)
    {
        if (!string.IsNullOrWhiteSpace(options.ChipModelName))
            return options.ChipModelName!;

        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.Chips.AsNoTracking().AsQueryable();
        if (options.ChipId is Guid cid) q = q.Where(c => c.Id == cid);
        if (options.SdkProjectId is Guid pid) q = q.Where(c => c.SdkProjectId == pid);
        var chip = await q.FirstOrDefaultAsync(cancellationToken);
        return chip?.ModelName ?? "TAE32G58xx";
    }

    public async Task InitializeAsync(Guid mcuId, CancellationToken cancellationToken = default)
    {
        var runtime = Get(mcuId);
        if (runtime.State is Core.Enums.VirtualMcuLifecycleState.Initialized
            or Core.Enums.VirtualMcuLifecycleState.Reset)
            return;

        var (_, slots) = await VirtualMcuDefinitionLoader.LoadAsync(
            _dbFactory, runtime.Options, cancellationToken);

        if (slots.Count == 0)
            throw new InvalidOperationException(
                "无寄存器定义可载入。请先在「寄存器管理」执行解析，再创建虚拟 MCU。");

        runtime.LoadSlots(slots);
    }

    public async Task InitializeForChipAsync(Guid chipId, CancellationToken cancellationToken = default)
    {
        if (_legacyChipBoundId is Guid existing
            && _mcus.TryGetValue(existing, out var live)
            && live.State != Core.Enums.VirtualMcuLifecycleState.Destroyed
            && live.ChipId == chipId)
        {
            if (live.State == Core.Enums.VirtualMcuLifecycleState.Created)
                await InitializeAsync(existing, cancellationToken);
            return;
        }

        var info = await CreateAsync(new VirtualMcuCreateOptions { ChipId = chipId }, cancellationToken);
        await InitializeAsync(info.Id, cancellationToken);
        _legacyChipBoundId = info.Id;
    }

    public Task ResetAsync(Guid mcuId, CancellationToken cancellationToken = default)
    {
        Get(mcuId).Reset();
        return Task.CompletedTask;
    }

    public Task DestroyAsync(Guid mcuId, CancellationToken cancellationToken = default)
    {
        if (_mcus.TryRemove(mcuId, out var runtime))
            runtime.Destroy();
        if (_legacyChipBoundId == mcuId)
            _legacyChipBoundId = null;
        return Task.CompletedTask;
    }

    public Task<IReadOnlyList<VirtualMcuInfo>> ListAsync(CancellationToken cancellationToken = default)
    {
        IReadOnlyList<VirtualMcuInfo> list = _mcus.Values
            .Where(m => m.State != Core.Enums.VirtualMcuLifecycleState.Destroyed)
            .Select(m => m.ToInfo())
            .OrderBy(m => m.DisplayName)
            .ToList();
        return Task.FromResult(list);
    }

    public Task<VirtualMcuInfo?> GetInfoAsync(Guid mcuId, CancellationToken cancellationToken = default)
    {
        if (!_mcus.TryGetValue(mcuId, out var m) || m.State == Core.Enums.VirtualMcuLifecycleState.Destroyed)
            return Task.FromResult<VirtualMcuInfo?>(null);
        return Task.FromResult<VirtualMcuInfo?>(m.ToInfo());
    }

    public Task<VirtualMcuSnapshotInfo> TakeSnapshotAsync(Guid mcuId, string? label = null, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).TakeSnapshot(label));

    public Task RestoreSnapshotAsync(Guid mcuId, Guid snapshotId, CancellationToken cancellationToken = default)
    {
        Get(mcuId).RestoreSnapshot(snapshotId);
        return Task.CompletedTask;
    }

    public Task<IReadOnlyList<VirtualMcuSnapshotInfo>> ListSnapshotsAsync(Guid mcuId, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).ListSnapshots());

    public Task<IReadOnlyList<VirtualPeripheralTreeNode>> GetPeripheralTreeAsync(Guid mcuId, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).GetTree());

    public Task<IReadOnlyList<VirtualRegisterView>> GetRegistersAsync(
        Guid mcuId, string? moduleName = null, string? instanceName = null, CancellationToken cancellationToken = default)
    {
        var m = Get(mcuId);
        m.EnsureAlive();
        return Task.FromResult(m.Space.GetAll(moduleName, instanceName));
    }

    public Task<VirtualRegisterView?> GetRegisterAsync(
        Guid mcuId, string instanceOrStruct, string memberName, CancellationToken cancellationToken = default)
    {
        var m = Get(mcuId);
        m.EnsureAlive();
        m.Space.TryGetByName(instanceOrStruct, memberName, out var view);
        return Task.FromResult(view);
    }

    public Task<IReadOnlyList<VirtualPeripheralView>> GetPeripheralStatesAsync(Guid mcuId, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).GetPeripheralViews());

    public Task<VirtualAccessResultDto> ReadAsync(
        Guid mcuId, string instanceOrStruct, string memberName, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).Read(instanceOrStruct, memberName, context));

    public Task<VirtualAccessResultDto> ReadByAddressAsync(
        Guid mcuId, uint address, int widthBits = 32, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).ReadByAddress(address, widthBits, context));

    public Task<VirtualAccessResultDto> WriteAsync(
        Guid mcuId, string instanceOrStruct, string memberName, uint value, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).Write(instanceOrStruct, memberName, value, context));

    public Task<VirtualAccessResultDto> SeedRegisterAsync(
        Guid mcuId, string instanceOrStruct, string memberName, uint value, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).SeedRegister(instanceOrStruct, memberName, value, context));

    public Task<VirtualAccessResultDto> WriteByAddressAsync(
        Guid mcuId, uint address, uint value, int widthBits = 32, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).WriteByAddress(address, value, widthBits, context));

    public Task<VirtualAccessResultDto> SetBitsAsync(
        Guid mcuId, string instanceOrStruct, string memberName, uint mask, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).SetBits(instanceOrStruct, memberName, mask, context));

    public Task<VirtualAccessResultDto> ClearBitsAsync(
        Guid mcuId, string instanceOrStruct, string memberName, uint mask, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).ClearBits(instanceOrStruct, memberName, mask, context));

    public Task<VirtualAccessResultDto> ModifyBitsAsync(
        Guid mcuId, string instanceOrStruct, string memberName, uint clearMask, uint setMask,
        VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).ModifyBits(instanceOrStruct, memberName, clearMask, setMask, context));

    public Task<VirtualAccessResultDto> WriteBitFieldAsync(
        Guid mcuId, string instanceOrStruct, string memberName, string fieldName, uint fieldValue,
        VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).WriteBitField(instanceOrStruct, memberName, fieldName, fieldValue, context));

    public Task<VirtualAccessResultDto> ResetRegisterAsync(
        Guid mcuId, string instanceOrStruct, string memberName, VirtualAccessContext? context = null,
        CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).ResetRegister(instanceOrStruct, memberName, context));

    public Task<IReadOnlyList<VirtualAccessRecord>> GetAccessTraceAsync(
        Guid mcuId, VirtualAccessFilter? filter = null, CancellationToken cancellationToken = default)
        => Task.FromResult(Get(mcuId).Trace.Query(filter));

    public Task ClearAccessTraceAsync(Guid mcuId, CancellationToken cancellationToken = default)
    {
        Get(mcuId).Trace.Clear();
        return Task.CompletedTask;
    }

    private VirtualMcuRuntime Get(Guid mcuId)
    {
        if (!_mcus.TryGetValue(mcuId, out var m) || m.State == Core.Enums.VirtualMcuLifecycleState.Destroyed)
            throw new KeyNotFoundException($"虚拟 MCU 不存在: {mcuId}");
        return m;
    }
}
