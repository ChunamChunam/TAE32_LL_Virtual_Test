using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu.Peripherals;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal sealed class VirtualMcuSnapshot
{
    public Guid SnapshotId { get; init; } = Guid.NewGuid();
    public DateTimeOffset CreatedAt { get; init; } = DateTimeOffset.UtcNow;
    public string? Label { get; init; }
    public Dictionary<Guid, uint> RegisterValues { get; init; } = new();
    public Dictionary<string, Dictionary<string, string>> PeripheralStates { get; init; } = new();
}

internal sealed class VirtualMcuRuntime
{
    private readonly object _gate = new();
    private readonly VirtualRegisterSpace _space = new();
    private readonly AccessTraceStore _trace = new();
    private readonly List<IVirtualPeripheral> _peripherals = new();
    private readonly Dictionary<Guid, VirtualMcuSnapshot> _snapshots = new();
    private readonly VirtualMcuCreateOptions _options;

    public VirtualMcuRuntime(Guid id, VirtualMcuCreateOptions options, string chipModelName)
    {
        Id = id;
        _options = options;
        ChipModelName = chipModelName;
        DisplayName = options.DisplayName ?? $"VirtualMCU-{chipModelName}-{id.ToString()[..8]}";
        State = VirtualMcuLifecycleState.Created;
    }

    public Guid Id { get; }
    public string DisplayName { get; }
    public string ChipModelName { get; }
    public Guid? ChipId => _options.ChipId;
    public Guid? SdkProjectId => _options.SdkProjectId;
    public VirtualMcuCreateOptions Options => _options;
    public VirtualMcuLifecycleState State { get; private set; }
    public VirtualRegisterSpace Space => _space;
    public AccessTraceStore Trace => _trace;

    public void LoadSlots(IEnumerable<VirtualRegisterSlot> slots)
    {
        lock (_gate)
        {
            foreach (var s in slots)
                _space.Add(s);

            var groups = _space.Slots
                .GroupBy(x => (Module: x.ModuleName ?? "?", Instance: x.InstanceName ?? x.StructName))
                .ToList();

            foreach (var g in groups)
            {
                var peri = PeripheralSimulatorFactory.Create(g.Key.Module, g.Key.Instance);
                peri.OnAttached(_space);
                _peripherals.Add(peri);
            }

            State = VirtualMcuLifecycleState.Initialized;
        }
    }

    public VirtualMcuInfo ToInfo()
    {
        lock (_gate)
        {
            return new VirtualMcuInfo
            {
                Id = Id,
                DisplayName = DisplayName,
                ChipModelName = ChipModelName,
                ChipId = ChipId,
                SdkProjectId = SdkProjectId,
                State = State,
                RegisterCount = _space.Slots.Count,
                PeripheralCount = _peripherals.Count,
                TraceCount = _trace.Count,
                ActiveLimitations = _space.CollectLimitations().ToList()
            };
        }
    }

    public void EnsureAlive()
    {
        if (State == VirtualMcuLifecycleState.Destroyed)
            throw new ObjectDisposedException(nameof(VirtualMcuRuntime), "虚拟 MCU 已销毁");
        if (State == VirtualMcuLifecycleState.Created)
            throw new InvalidOperationException("虚拟 MCU 尚未初始化（请先 Initialize）");
    }

    public void Reset()
    {
        lock (_gate)
        {
            EnsureAlive();
            _space.ResetAll();
            foreach (var p in _peripherals) p.Reset();
            foreach (var p in _peripherals) p.OnAttached(_space);
            State = VirtualMcuLifecycleState.Reset;
            _trace.Add(Id, VirtualAccessKind.Reset, null, null, null, null, null,
                VirtualAccessResult.Ok, null, "全寄存器复位", SimulationLimitationKind.None);
        }
    }

    public void Destroy()
    {
        lock (_gate)
        {
            State = VirtualMcuLifecycleState.Destroyed;
            _snapshots.Clear();
            _trace.Clear();
        }
    }

    public VirtualMcuSnapshotInfo TakeSnapshot(string? label)
    {
        lock (_gate)
        {
            EnsureAlive();
            var snap = new VirtualMcuSnapshot
            {
                Label = label,
                RegisterValues = _space.ExportValues(),
                PeripheralStates = _peripherals.ToDictionary(
                    p => $"{p.ModuleName}:{p.InstanceName}",
                    p => p.ExportState().ToDictionary(kv => kv.Key, kv => kv.Value))
            };
            _snapshots[snap.SnapshotId] = snap;
            _trace.Add(Id, VirtualAccessKind.Snapshot, null, null, null, null, null,
                VirtualAccessResult.Ok, null, $"snapshot {snap.SnapshotId}", SimulationLimitationKind.None);
            return new VirtualMcuSnapshotInfo
            {
                SnapshotId = snap.SnapshotId,
                McuId = Id,
                CreatedAt = snap.CreatedAt,
                Label = snap.Label,
                RegisterCount = snap.RegisterValues.Count
            };
        }
    }

    public void RestoreSnapshot(Guid snapshotId)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_snapshots.TryGetValue(snapshotId, out var snap))
                throw new KeyNotFoundException($"快照不存在: {snapshotId}");
            _space.ImportValues(snap.RegisterValues);
            foreach (var p in _peripherals)
            {
                var key = $"{p.ModuleName}:{p.InstanceName}";
                if (snap.PeripheralStates.TryGetValue(key, out var st))
                    p.ImportState(st);
            }
            _trace.Add(Id, VirtualAccessKind.Restore, null, null, null, null, null,
                VirtualAccessResult.Ok, null, $"restore {snapshotId}", SimulationLimitationKind.None);
        }
    }

    public IReadOnlyList<VirtualMcuSnapshotInfo> ListSnapshots()
    {
        lock (_gate)
        {
            return _snapshots.Values.Select(s => new VirtualMcuSnapshotInfo
            {
                SnapshotId = s.SnapshotId,
                McuId = Id,
                CreatedAt = s.CreatedAt,
                Label = s.Label,
                RegisterCount = s.RegisterValues.Count
            }).OrderByDescending(x => x.CreatedAt).ToList();
        }
    }

    public IReadOnlyList<VirtualPeripheralTreeNode> GetTree()
    {
        lock (_gate)
        {
            return _peripherals
                .GroupBy(p => p.ModuleName, StringComparer.OrdinalIgnoreCase)
                .OrderBy(g => g.Key)
                .Select(g => new VirtualPeripheralTreeNode
                {
                    Key = "mod:" + g.Key,
                    Title = g.Key,
                    ModuleName = g.Key,
                    IsModule = true,
                    Children = g.OrderBy(x => x.InstanceName).Select(p => new VirtualPeripheralTreeNode
                    {
                        Key = "inst:" + p.InstanceName,
                        Title = p.InstanceName,
                        ModuleName = p.ModuleName,
                        InstanceName = p.InstanceName,
                        IsModule = false
                    }).ToList()
                }).ToList();
        }
    }

    public IReadOnlyList<VirtualPeripheralView> GetPeripheralViews()
    {
        lock (_gate)
            return _peripherals.Select(p => p.GetView()).ToList();
    }

    public VirtualAccessResultDto Read(string instanceOrStruct, string member, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.Read, instanceOrStruct, member, ctx);

            return ApplyRead(slot, ctx);
        }
    }

    public VirtualAccessResultDto ReadByAddress(uint address, int widthBits, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlotByAddress(address, out var slot) || slot is null)
            {
                var rec = _trace.Add(Id, VirtualAccessKind.Read, null, address, null, null, null,
                    VirtualAccessResult.AddressOutOfRange, ctx, "地址未映射", SimulationLimitationKind.None);
                return new VirtualAccessResultDto
                {
                    Result = VirtualAccessResult.AddressOutOfRange,
                    Message = "地址未映射到虚拟寄存器",
                    Record = rec
                };
            }

            if (!RegisterSemanticsEngine.IsSupportedWidth(widthBits) || widthBits != slot.WidthBits)
            {
                var rec = _trace.Add(Id, VirtualAccessKind.Read, slot, address, null, slot.CurrentValue, null,
                    VirtualAccessResult.WidthMismatch, ctx, $"宽度不匹配 expect={slot.WidthBits} got={widthBits}",
                    slot.Limitation);
                return new VirtualAccessResultDto
                {
                    Result = VirtualAccessResult.WidthMismatch,
                    ValueBefore = slot.CurrentValue,
                    Message = rec.Message,
                    Record = rec,
                    Limitation = slot.Limitation
                };
            }

            return ApplyRead(slot, ctx);
        }
    }

    public VirtualAccessResultDto Write(string instanceOrStruct, string member, uint value, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.Write, instanceOrStruct, member, ctx);
            return ApplyWrite(slot, value, VirtualAccessKind.Write, ctx);
        }
    }

    /// <summary>Direct storage write for test preload (ignores W1C clear-on-write).</summary>
    public VirtualAccessResultDto SeedRegister(string instanceOrStruct, string member, uint value, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.Write, instanceOrStruct, member, ctx);

            var before = slot.CurrentValue;
            var next = value & RegisterSemanticsEngine.WidthMask(slot.WidthBits);
            slot.CurrentValue = next;
            var message = "测试预置寄存器（直接写入存储，绕过 W1C/W0C）";
            var okResult = slot.Limitation == SimulationLimitationKind.None
                ? VirtualAccessResult.Ok
                : VirtualAccessResult.LimitationApplied;
            var rec = _trace.Add(Id, VirtualAccessKind.Write, slot, slot.AbsoluteAddress, value, before, next,
                okResult, ctx, message, slot.Limitation);
            return new VirtualAccessResultDto
            {
                Result = okResult,
                Value = next,
                ValueBefore = before,
                ValueAfter = next,
                Message = message,
                Record = rec,
                Limitation = slot.Limitation
            };
        }
    }

    public VirtualAccessResultDto WriteByAddress(uint address, uint value, int widthBits, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlotByAddress(address, out var slot) || slot is null)
            {
                var rec = _trace.Add(Id, VirtualAccessKind.Write, null, address, value, null, null,
                    VirtualAccessResult.AddressOutOfRange, ctx, "地址未映射", SimulationLimitationKind.None);
                return new VirtualAccessResultDto
                {
                    Result = VirtualAccessResult.AddressOutOfRange,
                    Message = "地址未映射到虚拟寄存器",
                    Record = rec
                };
            }

            if (!RegisterSemanticsEngine.IsSupportedWidth(widthBits) || widthBits != slot.WidthBits)
            {
                var rec = _trace.Add(Id, VirtualAccessKind.Write, slot, address, value, slot.CurrentValue, null,
                    VirtualAccessResult.WidthMismatch, ctx, $"宽度不匹配 expect={slot.WidthBits} got={widthBits}",
                    slot.Limitation);
                return new VirtualAccessResultDto
                {
                    Result = VirtualAccessResult.WidthMismatch,
                    ValueBefore = slot.CurrentValue,
                    Message = rec.Message,
                    Record = rec,
                    Limitation = slot.Limitation
                };
            }

            return ApplyWrite(slot, value, VirtualAccessKind.Write, ctx);
        }
    }

    public VirtualAccessResultDto SetBits(string instanceOrStruct, string member, uint mask, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.SetBits, instanceOrStruct, member, ctx);
            var next = slot.CurrentValue | mask;
            return ApplyWrite(slot, next, VirtualAccessKind.SetBits, ctx, raw: mask);
        }
    }

    public VirtualAccessResultDto ClearBits(string instanceOrStruct, string member, uint mask, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.ClearBits, instanceOrStruct, member, ctx);
            var next = slot.CurrentValue & ~mask;
            return ApplyWrite(slot, next, VirtualAccessKind.ClearBits, ctx, raw: mask);
        }
    }

    public VirtualAccessResultDto ModifyBits(string instanceOrStruct, string member, uint clearMask, uint setMask, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.ModifyBits, instanceOrStruct, member, ctx);
            var next = (slot.CurrentValue & ~clearMask) | setMask;
            return ApplyWrite(slot, next, VirtualAccessKind.ModifyBits, ctx, raw: setMask);
        }
    }

    public VirtualAccessResultDto WriteBitField(string instanceOrStruct, string member, string fieldName, uint fieldValue, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.WriteBitField, instanceOrStruct, member, ctx);

            var field = slot.Fields.FirstOrDefault(f => f.Name.Equals(fieldName, StringComparison.OrdinalIgnoreCase));
            if (field is null)
            {
                var rec = _trace.Add(Id, VirtualAccessKind.WriteBitField, slot, slot.AbsoluteAddress, fieldValue,
                    slot.CurrentValue, null, VirtualAccessResult.NotFound, ctx, $"位域不存在: {fieldName}", slot.Limitation);
                return new VirtualAccessResultDto { Result = VirtualAccessResult.NotFound, Message = rec.Message, Record = rec };
            }

            var max = field.BitWidth >= 32 ? 0xFFFFFFFFu : (1u << field.BitWidth) - 1u;
            var clipped = fieldValue & max;
            var next = (slot.CurrentValue & ~field.Mask) | ((clipped << field.BitPosition) & field.Mask);
            return ApplyWrite(slot, next, VirtualAccessKind.WriteBitField, ctx, raw: clipped);
        }
    }

    public VirtualAccessResultDto ResetRegister(string instanceOrStruct, string member, VirtualAccessContext? ctx)
    {
        lock (_gate)
        {
            EnsureAlive();
            if (!_space.TryGetSlot(instanceOrStruct, member, out var slot) || slot is null)
                return NotFound(VirtualAccessKind.Reset, instanceOrStruct, member, ctx);

            var before = slot.CurrentValue;
            slot.CurrentValue = slot.ResetValue;
            NotifyWrite(slot, before, slot.CurrentValue, ctx);
            var rec = _trace.Add(Id, VirtualAccessKind.Reset, slot, slot.AbsoluteAddress, slot.ResetValue, before, slot.CurrentValue,
                VirtualAccessResult.Ok, ctx, "寄存器复位", slot.Limitation);
            return new VirtualAccessResultDto
            {
                Result = VirtualAccessResult.Ok,
                Value = slot.CurrentValue,
                ValueBefore = before,
                ValueAfter = slot.CurrentValue,
                Record = rec,
                Limitation = slot.Limitation
            };
        }
    }

    private VirtualAccessResultDto ApplyRead(VirtualRegisterSlot slot, VirtualAccessContext? ctx)
    {
        var before = slot.CurrentValue;
        if (!RegisterSemanticsEngine.TryApplyRead(slot.Behavior, before, out var readValue, out var next, out var result, out var message))
        {
            var recFail = _trace.Add(Id, VirtualAccessKind.Read, slot, slot.AbsoluteAddress, null, before, before,
                result, ctx, message, slot.Limitation);
            return new VirtualAccessResultDto
            {
                Result = result,
                Value = readValue,
                ValueBefore = before,
                ValueAfter = before,
                Message = message,
                Record = recFail,
                Limitation = slot.Limitation
            };
        }

        slot.CurrentValue = next;
        NotifyRead(slot, readValue, ctx);
        var okResult = slot.Limitation == SimulationLimitationKind.None
            ? VirtualAccessResult.Ok
            : VirtualAccessResult.LimitationApplied;
        var rec = _trace.Add(Id, VirtualAccessKind.Read, slot, slot.AbsoluteAddress, null, before, slot.CurrentValue,
            okResult, ctx, message, slot.Limitation);
        return new VirtualAccessResultDto
        {
            Result = okResult,
            Value = readValue,
            ValueBefore = before,
            ValueAfter = slot.CurrentValue,
            Message = message,
            Record = rec,
            Limitation = slot.Limitation
        };
    }

    private VirtualAccessResultDto ApplyWrite(
        VirtualRegisterSlot slot,
        uint value,
        VirtualAccessKind kind,
        VirtualAccessContext? ctx,
        uint? raw = null)
    {
        var before = slot.CurrentValue;
        if (!RegisterSemanticsEngine.TryApplyWrite(slot.Behavior, slot.Fields, before, value, slot.WritableMask,
                RegisterSemanticsEngine.WidthMask(slot.WidthBits), out var next, out var result, out var message))
        {
            var recFail = _trace.Add(Id, kind, slot, slot.AbsoluteAddress, raw ?? value, before, before,
                result, ctx, message, slot.Limitation);
            return new VirtualAccessResultDto
            {
                Result = result,
                ValueBefore = before,
                ValueAfter = before,
                Message = message,
                Record = recFail,
                Limitation = slot.Limitation
            };
        }

        slot.CurrentValue = next;
        NotifyWrite(slot, before, next, ctx);

        // GPIO: apply BSR/BRR side-effects to DOR/ODR/IDR storage (virtual HW behavior).
        foreach (var gpio in _peripherals.OfType<GpioPeripheralSimulator>())
        {
            void Force(string inst, string mem, uint v)
            {
                if (_space.TryGetSlot(inst, mem, out var slot) && slot is not null)
                    slot.CurrentValue = v & RegisterSemanticsEngine.WidthMask(slot.WidthBits);
            }
            gpio.SyncOutputRegisters(Force);
            gpio.SyncIdrLoopback(Force);
        }

        var requested = raw ?? value;
        var widthMask = RegisterSemanticsEngine.WidthMask(slot.WidthBits);
        var effectiveWritable = slot.WritableMask & widthMask;
        if (kind == VirtualAccessKind.Write
            && effectiveWritable != widthMask
            && (requested & widthMask) != (requested & effectiveWritable))
        {
            var clipped = (before & ~effectiveWritable) | (requested & effectiveWritable);
            message = string.IsNullOrEmpty(message)
                ? $"按可写掩码裁剪：请求 0x{requested:X8} → 实际 0x{clipped:X8}（WritableMask=0x{effectiveWritable:X8}，未映射位保留保护）"
                : message;
            if (slot.Limitation == SimulationLimitationKind.None)
                slot.Limitation = SimulationLimitationKind.IncompleteReservedMask;
        }

        var okResult = slot.Limitation == SimulationLimitationKind.None
            ? VirtualAccessResult.Ok
            : VirtualAccessResult.LimitationApplied;
        var rec = _trace.Add(Id, kind, slot, slot.AbsoluteAddress, requested, before, next,
            okResult, ctx, message, slot.Limitation);
        return new VirtualAccessResultDto
        {
            Result = okResult,
            Value = next,
            ValueBefore = before,
            ValueAfter = next,
            Message = message,
            Record = rec,
            Limitation = slot.Limitation
        };
    }

    private void NotifyWrite(VirtualRegisterSlot slot, uint before, uint after, VirtualAccessContext? ctx)
    {
        var view = slot.ToView();
        foreach (var p in _peripherals)
        {
            if (!Matches(p, slot)) continue;
            p.OnAfterWrite(view, before, after, ctx);
        }
    }

    private void NotifyRead(VirtualRegisterSlot slot, uint value, VirtualAccessContext? ctx)
    {
        var view = slot.ToView();
        foreach (var p in _peripherals)
        {
            if (!Matches(p, slot)) continue;
            p.OnAfterRead(view, value, ctx);
        }
    }

    private static bool Matches(IVirtualPeripheral p, VirtualRegisterSlot slot)
    {
        if (!string.IsNullOrEmpty(slot.InstanceName)
            && slot.InstanceName.Equals(p.InstanceName, StringComparison.OrdinalIgnoreCase))
            return true;
        if (!string.IsNullOrEmpty(slot.ModuleName)
            && slot.ModuleName.Equals(p.ModuleName, StringComparison.OrdinalIgnoreCase)
            && (slot.InstanceName is null || slot.InstanceName.Equals(p.InstanceName, StringComparison.OrdinalIgnoreCase)))
            return string.Equals(slot.InstanceName, p.InstanceName, StringComparison.OrdinalIgnoreCase)
                   || slot.StructName.StartsWith(p.ModuleName, StringComparison.OrdinalIgnoreCase);
        return false;
    }

    private VirtualAccessResultDto NotFound(VirtualAccessKind kind, string inst, string member, VirtualAccessContext? ctx)
    {
        var rec = _trace.Add(Id, kind, null, null, null, null, null,
            VirtualAccessResult.NotFound, ctx, $"{inst}.{member} 不存在", SimulationLimitationKind.None);
        return new VirtualAccessResultDto { Result = VirtualAccessResult.NotFound, Message = rec.Message, Record = rec };
    }
}
