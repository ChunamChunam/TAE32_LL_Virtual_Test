using System.Collections.Concurrent;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal sealed class AccessTraceStore
{
    private readonly ConcurrentQueue<VirtualAccessRecord> _records = new();
    private long _sequence;

    public int Count => _records.Count;

    public VirtualAccessRecord Add(
        Guid mcuId,
        VirtualAccessKind kind,
        VirtualRegisterSlot? slot,
        uint? address,
        uint? raw,
        uint? before,
        uint? after,
        VirtualAccessResult result,
        VirtualAccessContext? context,
        string? message,
        SimulationLimitationKind limitation)
    {
        var rec = new VirtualAccessRecord
        {
            Sequence = Interlocked.Increment(ref _sequence),
            Timestamp = DateTimeOffset.UtcNow,
            McuId = mcuId,
            AccessKind = kind,
            Address = address ?? slot?.AbsoluteAddress,
            RegisterName = slot is null ? (address is uint a ? $"@{a:X8}" : "?") : slot.NameKey,
            InstanceName = slot?.InstanceName,
            ModuleName = slot?.ModuleName,
            RawValue = raw,
            ValueBefore = before,
            ValueAfter = after,
            LlFunctionName = context?.LlFunctionName,
            SourceFile = context?.SourceFile,
            SourceLine = context?.SourceLine,
            Result = result,
            Message = message ?? context?.Note,
            Limitation = limitation
        };
        _records.Enqueue(rec);
        return rec;
    }

    public IReadOnlyList<VirtualAccessRecord> Query(VirtualAccessFilter? filter)
    {
        filter ??= new VirtualAccessFilter();
        IEnumerable<VirtualAccessRecord> q = _records;
        if (!string.IsNullOrWhiteSpace(filter.LlFunctionName))
            q = q.Where(x => string.Equals(x.LlFunctionName, filter.LlFunctionName, StringComparison.OrdinalIgnoreCase));
        if (!string.IsNullOrWhiteSpace(filter.ModuleName))
            q = q.Where(x => string.Equals(x.ModuleName, filter.ModuleName, StringComparison.OrdinalIgnoreCase));
        if (!string.IsNullOrWhiteSpace(filter.InstanceName))
            q = q.Where(x => string.Equals(x.InstanceName, filter.InstanceName, StringComparison.OrdinalIgnoreCase));
        if (!string.IsNullOrWhiteSpace(filter.RegisterName))
            q = q.Where(x => x.RegisterName.Contains(filter.RegisterName!, StringComparison.OrdinalIgnoreCase));
        if (filter.AccessKind is VirtualAccessKind kind)
            q = q.Where(x => x.AccessKind == kind);

        return q.OrderByDescending(x => x.Sequence)
            .Skip(Math.Max(0, filter.Skip))
            .Take(filter.Take <= 0 ? 200 : filter.Take)
            .ToList();
    }

    public void Clear()
    {
        while (_records.TryDequeue(out _)) { }
    }
}
