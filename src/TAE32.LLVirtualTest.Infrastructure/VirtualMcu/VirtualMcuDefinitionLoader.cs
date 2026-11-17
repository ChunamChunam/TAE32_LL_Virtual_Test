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

        // Authoritative addresses from tae32g58xx_chip.h / chip_struct.h (override stale DB values).
        string? sdkRoot = null;
        var projectId = options.SdkProjectId ?? chip?.SdkProjectId;
        if (projectId is Guid spid)
        {
            sdkRoot = await db.SdkProjects.AsNoTracking()
                .Where(p => p.Id == spid)
                .Select(p => p.SdkRootPath)
                .FirstOrDefaultAsync(cancellationToken);
        }

        var chipAddresses = ChipHeaderAddressCatalog.TryLoad(sdkRoot);

        var slots = new List<VirtualRegisterSlot>(rows.Count);
        foreach (var r in rows)
        {
            var width = r.WidthBits is 8 or 16 or 32 ? r.WidthBits.Value : 32;
            var behavior = RegisterSemanticsEngine.ResolveBehavior(
                r.AccessAttribute, options.DefaultUnknownAccessToReadWrite,
                out var limAccess, out var noteAccess);
            var moduleHint = NormalizeModuleToken(
                                 r.Peripheral?.Name
                                 ?? r.PeripheralInstance?.ModuleName
                                 ?? InferModule(r.StructName, r.PeripheralInstance?.Name))
                             ?? r.Peripheral?.Name
                             ?? r.PeripheralInstance?.ModuleName;
            behavior = VirtualRegisterSemanticsOverrides.OverrideBehavior(moduleHint, r.MemberName, behavior);

            var reset = RegisterSemanticsEngine.ParseResetValue(r.ResetValue, out var limReset);
            var limitation = limAccess != SimulationLimitationKind.None ? limAccess : limReset;
            var note = noteAccess;
            if (limReset != SimulationLimitationKind.None && string.IsNullOrEmpty(note))
                note = "复位值缺失，按 0";

            var instanceNameHint = r.PeripheralInstance?.Name
                                   ?? (r.StructName.EndsWith("_Type", StringComparison.Ordinal)
                                       ? r.StructName[..^5]
                                       : null);

            uint? addr = null;
            // Prefer instance bank Type (HRPWM_MST_Type) over aggregate TypeDef — nested Master.MCR0
            // is not a direct member of HRPWM_TypeDef, so StructName=HRPWM_TypeDef would miss AbsoluteAddress.
            if (chipAddresses is not null
                && (chipAddresses.TryResolveAbsolute(
                        instanceNameHint, r.StructName, r.MemberName,
                        out var chipAbs, out var chipBase, out var chipOff)
                    || (!string.IsNullOrWhiteSpace(instanceNameHint)
                        && chipAddresses.TryResolveAbsolute(
                            instanceNameHint, instanceNameHint + "_Type", r.MemberName,
                            out chipAbs, out chipBase, out chipOff))))
            {
                addr = chipAbs;
                // Keep DB/instance in sync mentally: chip header wins.
                if (r.PeripheralInstance is not null
                    && r.PeripheralInstance.BaseAddress != chipBase)
                {
                    // Do not mutate tracked entity (AsNoTracking); only slot address matters.
                }

                if (r.AbsoluteAddress is uint dbAbs && dbAbs != chipAbs)
                {
                    note = string.IsNullOrEmpty(note)
                        ? $"地址以 chip.h 为准：0x{chipAbs:X8}=BASE 0x{chipBase:X8}+0x{chipOff:X}（DB 曾为 0x{dbAbs:X8}）"
                        : note + $"；地址覆盖为 chip.h 0x{chipAbs:X8}";
                }
                else if (string.IsNullOrEmpty(note))
                {
                    note = $"地址来自 chip.h：0x{chipAbs:X8}";
                }
            }
            else
            {
                addr = r.AbsoluteAddress;
                if (addr is null
                    && r.PeripheralInstance?.BaseAddress is uint bas
                    && r.OffsetBytes is int off)
                {
                    addr = bas + (uint)off;
                }
            }

            if (addr is null)
            {
                if (limitation == SimulationLimitationKind.None)
                    limitation = SimulationLimitationKind.MissingAbsoluteAddress;
                if (string.IsNullOrEmpty(note))
                    note = "无绝对地址：仅支持按名称访问（chip.h 未解析到 BASE+offset）";
            }

            var fields = r.Fields
                .Where(f => f.BitPosition is int || f.Mask is not null || !string.IsNullOrWhiteSpace(f.MskMacroName))
                .Select(f =>
                {
                    var pos = f.BitPosition ?? 0;
                    var bw = f.BitWidth ?? 0;
                    var mask = f.Mask ?? (bw > 0
                        ? (bw >= 32 ? 0xFFFFFFFFu : ((1u << bw) - 1u) << pos)
                        : 0u);

                    // Prefer chip.h literals over stale DB Mask/BitWidth (e.g. PSC wrongly stored as 0x7).
                    if (chipAddresses is not null
                        && chipAddresses.TryResolveFieldMaskPos(
                            instanceNameHint, r.MemberName, f.Name, f.MskMacroName,
                            out var chipMask, out var chipPos)
                        && chipMask != 0)
                    {
                        mask = chipMask;
                        pos = chipPos;
                        bw = CountMaskWidth(chipMask >> chipPos);
                    }
                    else if (mask != 0 && bw <= 0)
                    {
                        var p = pos;
                        var shifted = mask >> p;
                        bw = 0;
                        while (shifted != 0 && bw < 32)
                        {
                            shifted >>= 1;
                            bw++;
                        }
                    }

                    if (mask == 0 || bw <= 0) return null;
                    return new VirtualBitFieldSlot
                    {
                        Name = f.Name,
                        BitPosition = pos,
                        BitWidth = bw,
                        Mask = mask,
                        AccessAttribute = f.AccessAttribute
                    };
                })
                .Where(f => f is not null)
                .Select(f => f!)
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
            var moduleName = NormalizeModuleToken(
                                 r.Peripheral?.Name
                                 ?? r.PeripheralInstance?.ModuleName
                                 ?? InferModule(r.StructName, instanceName))
                             ?? r.Peripheral?.Name
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
            VirtualRegisterSemanticsOverrides.ApplyFieldInheritance(slot);
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

    private static int CountMaskWidth(uint shiftedMask)
    {
        var w = 0;
        while (shiftedMask != 0 && w < 32)
        {
            shiftedMask >>= 1;
            w++;
        }
        return w;
    }

    private static string? InferModule(string structName, string? instanceName)
    {
        if (structName.EndsWith("_TypeDef", StringComparison.Ordinal))
            return NormalizeModuleToken(structName[..^8]);
        if (structName.EndsWith("_Type", StringComparison.Ordinal))
            return NormalizeModuleToken(structName[..^5]);
        if (!string.IsNullOrEmpty(instanceName))
            return NormalizeModuleToken(instanceName);
        return null;
    }

    /// <summary>
    /// Collapse banked names to the host TypeDef module:
    /// HRPWM_MST / HRPWM_SLV0 / HRPWM_COM → HRPWM; ADC0 → ADC; GPIOA → GPIO.
    /// </summary>
    internal static string? NormalizeModuleToken(string? token)
    {
        if (string.IsNullOrWhiteSpace(token)) return null;
        var t = token.Trim();

        // Multi-bank aggregates used by Native host TypeDef images.
        var bank = System.Text.RegularExpressions.Regex.Match(
            t, @"^([A-Za-z]+)_(MST|COM|SLV\d+|CH\d+|UNIT\d+|TIM\d+)$",
            System.Text.RegularExpressions.RegexOptions.IgnoreCase);
        if (bank.Success)
            return bank.Groups[1].Value.ToUpperInvariant();

        // Numbered / lettered instances: ADC0, GPIOA, TMR9.
        var numbered = System.Text.RegularExpressions.Regex.Match(
            t, @"^([A-Za-z]+?)(\d+|[A-F])$",
            System.Text.RegularExpressions.RegexOptions.IgnoreCase);
        if (numbered.Success)
            return numbered.Groups[1].Value.ToUpperInvariant();

        return t.ToUpperInvariant();
    }
}
