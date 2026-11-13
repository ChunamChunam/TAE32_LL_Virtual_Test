using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal static class VirtualMcuDefinitionLoader
{
    public static async Task<(string ChipModel, List<VirtualRegisterSlot> Slots)> LoadAsync(
        IDbContextFactory<AppDbContext> dbFactory,
        VirtualMcuCreateOptions options,
        CancellationToken cancellationToken)
    {
        await using var db = await dbFactory.CreateDbContextAsync(cancellationToken);

        var chipQuery = db.Chips.AsNoTracking().AsQueryable();
        if (options.ChipId is Guid cid)
            chipQuery = chipQuery.Where(c => c.Id == cid);
        else if (!string.IsNullOrWhiteSpace(options.ChipModelName))
            chipQuery = chipQuery.Where(c => c.ModelName == options.ChipModelName);
        if (options.SdkProjectId is Guid pid)
            chipQuery = chipQuery.Where(c => c.SdkProjectId == pid);

        var chip = await chipQuery.FirstOrDefaultAsync(cancellationToken);
        var chipModel = chip?.ModelName
                        ?? options.ChipModelName
                        ?? "TAE32G58xx";

        var regQuery = db.RegisterDefinitions.AsNoTracking()
            .Include(r => r.Fields)
            .Include(r => r.PeripheralInstance)
            .Include(r => r.Peripheral)
            .Include(r => r.Chip)
            .AsQueryable();

        if (options.SdkProjectId is Guid sp)
            regQuery = regQuery.Where(r => r.SdkProjectId == sp);
        else if (chip is not null)
            regQuery = regQuery.Where(r => r.SdkProjectId == chip.SdkProjectId);

        if (chip is not null)
            regQuery = regQuery.Where(r => r.ChipId == null || r.ChipId == chip.Id);

        if (!options.IncludeReservedMembers)
        {
            regQuery = regQuery.Where(r =>
                !r.MemberName.StartsWith("RESERVED")
                && (r.AccessAttribute == null || r.AccessAttribute != "Reserved"));
        }

        var rows = await regQuery
            .OrderBy(r => r.StructName).ThenBy(r => r.OffsetBytes ?? int.MaxValue).ThenBy(r => r.MemberName)
            .ToListAsync(cancellationToken);

        var slots = new List<VirtualRegisterSlot>(rows.Count);
        foreach (var r in rows)
        {
            var width = r.WidthBits is 8 or 16 or 32 ? r.WidthBits.Value : 32;
            var behavior = RegisterSemanticsEngine.ResolveBehavior(
                r.AccessAttribute, options.DefaultUnknownAccessToReadWrite,
                out var limAccess, out var noteAccess);
            var moduleHint = r.Peripheral?.Name
                             ?? r.PeripheralInstance?.ModuleName
                             ?? InferModule(r.StructName, r.PeripheralInstance?.Name);
            behavior = VirtualRegisterSemanticsOverrides.OverrideBehavior(moduleHint, r.MemberName, behavior);

            var reset = RegisterSemanticsEngine.ParseResetValue(r.ResetValue, out var limReset);
            var limitation = limAccess != SimulationLimitationKind.None ? limAccess : limReset;
            var note = noteAccess;
            if (limReset != SimulationLimitationKind.None && string.IsNullOrEmpty(note))
                note = "复位值缺失，按 0";

            uint? addr = r.AbsoluteAddress;
            if (addr is null
                && r.PeripheralInstance?.BaseAddress is uint bas
                && r.OffsetBytes is int off)
            {
                addr = bas + (uint)off;
            }
            if (addr is null)
            {
                if (limitation == SimulationLimitationKind.None)
                    limitation = SimulationLimitationKind.MissingAbsoluteAddress;
                if (string.IsNullOrEmpty(note))
                    note = "无绝对地址：仅支持按名称访问";
            }

            var fields = r.Fields
                .Where(f => f.BitPosition is int && f.BitWidth is int and > 0)
                .Select(f =>
                {
                    var pos = f.BitPosition!.Value;
                    var bw = f.BitWidth!.Value;
                    var mask = f.Mask ?? (bw >= 32 ? 0xFFFFFFFFu : ((1u << bw) - 1u) << pos);
                    return new VirtualBitFieldSlot
                    {
                        Name = f.Name,
                        BitPosition = pos,
                        BitWidth = bw,
                        Mask = mask,
                        AccessAttribute = f.AccessAttribute
                    };
                })
                .OrderBy(f => f.BitPosition)
                .ToList();

            var widthMask = RegisterSemanticsEngine.WidthMask(width);
            uint writableMask = widthMask;
            if (options.ProtectUnmappedBitsAsReserved && fields.Count > 0)
            {
                uint fieldMask = 0;
                foreach (var f in fields) fieldMask |= f.Mask;
                writableMask = fieldMask & widthMask;
                if (writableMask != widthMask && limitation == SimulationLimitationKind.None)
                {
                    limitation = SimulationLimitationKind.IncompleteReservedMask;
                    note = "未映射位按保留保护（ProtectUnmappedBitsAsReserved）";
                }
            }

            if (behavior is VirtualRegisterBehavior.Write1Clear or VirtualRegisterBehavior.Write0Clear
                or VirtualRegisterBehavior.ReadClear)
            {
                // Special semantics are only active when SDK declared them (already resolved).
            }
            else if (behavior == VirtualRegisterBehavior.ReadWrite
                     && string.Equals(r.AccessAttribute, "Unknown", StringComparison.OrdinalIgnoreCase))
            {
                // already limited
            }

            var instanceName = r.PeripheralInstance?.Name
                               ?? (r.StructName.EndsWith("_Type", StringComparison.Ordinal)
                                   ? r.StructName[..^5]
                                   : null);
            var moduleName = r.Peripheral?.Name
                             ?? r.PeripheralInstance?.ModuleName
                             ?? InferModule(r.StructName, instanceName);

            var slot = new VirtualRegisterSlot
            {
                DefinitionId = r.Id,
                ChipModelName = chipModel,
                ModuleName = moduleName,
                InstanceName = instanceName,
                StructName = r.StructName,
                MemberName = r.MemberName,
                AbsoluteAddress = addr,
                WidthBits = width,
                ResetValue = reset & widthMask,
                AccessAttribute = r.AccessAttribute,
                Behavior = behavior,
                Limitation = limitation,
                LimitationNote = note,
                WritableMask = writableMask,
                CurrentValue = reset & widthMask
            };
            slot.Fields.AddRange(fields);
            slots.Add(slot);
        }

        // Phase-4 may store both ADC0_Type.CR and ADC_TypeDef.CR for the same instance/address.
        // Virtual space must keep one slot, otherwise UI lists stale copy while writes hit the other.
        return (chipModel, DeduplicateSlots(slots));
    }

    private static List<VirtualRegisterSlot> DeduplicateSlots(List<VirtualRegisterSlot> slots)
    {
        var winners = new Dictionary<string, VirtualRegisterSlot>(StringComparer.OrdinalIgnoreCase);
        foreach (var slot in slots)
        {
            var key = slot.AbsoluteAddress is uint addr
                ? $"A:{addr:X8}"
                : $"N:{(slot.InstanceName ?? slot.StructName)}.{slot.MemberName}";

            if (!winners.TryGetValue(key, out var existing))
            {
                winners[key] = slot;
                continue;
            }

            var preferNew = Score(slot) > Score(existing);
            var keep = preferNew ? slot : existing;
            var drop = preferNew ? existing : slot;

            // Prefer richer bitfield set for UI.
            if (drop.Fields.Count > keep.Fields.Count)
            {
                keep.Fields.Clear();
                keep.Fields.AddRange(drop.Fields);
            }

            if (keep.Limitation == SimulationLimitationKind.None && drop.Limitation != SimulationLimitationKind.None)
            {
                keep.Limitation = drop.Limitation;
                keep.LimitationNote = drop.LimitationNote;
            }

            winners[key] = keep;
        }

        return winners.Values
            .OrderBy(x => x.ModuleName)
            .ThenBy(x => x.InstanceName)
            .ThenBy(x => x.AbsoluteAddress ?? uint.MaxValue)
            .ThenBy(x => x.MemberName)
            .ToList();
    }

    private static int Score(VirtualRegisterSlot s)
    {
        var score = 0;
        if (!string.IsNullOrEmpty(s.InstanceName)
            && s.StructName.Equals(s.InstanceName + "_Type", StringComparison.OrdinalIgnoreCase))
            score += 100;
        if (s.StructName.EndsWith("_TypeDef", StringComparison.OrdinalIgnoreCase))
            score += 20;
        if (s.AbsoluteAddress is not null) score += 10;
        score += Math.Min(s.Fields.Count, 50);
        if (!string.Equals(s.AccessAttribute, "Unknown", StringComparison.OrdinalIgnoreCase))
            score += 5;
        return score;
    }

    private static string? InferModule(string structName, string? instanceName)
    {
        if (structName.EndsWith("_TypeDef", StringComparison.Ordinal))
            return structName[..^8];
        if (structName.EndsWith("_Type", StringComparison.Ordinal))
        {
            var inst = structName[..^5];
            var m = System.Text.RegularExpressions.Regex.Match(inst, @"^([A-Z]+?)(\d+|[A-F])?$");
            return m.Success ? m.Groups[1].Value : inst;
        }
        if (!string.IsNullOrEmpty(instanceName))
        {
            var m = System.Text.RegularExpressions.Regex.Match(instanceName, @"^([A-Z]+?)(\d+|[A-F])?$");
            return m.Success ? m.Groups[1].Value : instanceName;
        }
        return null;
    }
}
