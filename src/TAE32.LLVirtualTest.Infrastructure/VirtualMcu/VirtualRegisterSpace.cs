using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal sealed class VirtualRegisterSpace : IVirtualRegisterSpace
{
    private readonly Dictionary<string, VirtualRegisterSlot> _byName = new(StringComparer.OrdinalIgnoreCase);
    private readonly Dictionary<string, VirtualRegisterSlot> _byStructMember = new(StringComparer.OrdinalIgnoreCase);
    private readonly Dictionary<uint, VirtualRegisterSlot> _byAddress = new();
    private readonly List<VirtualRegisterSlot> _all = new();

    public IReadOnlyList<VirtualRegisterSlot> Slots => _all;

    public void Add(VirtualRegisterSlot slot)
    {
        // One storage cell per absolute address / name key.
        // Prefer a later slot that carries AbsoluteAddress over an earlier nameless-address copy
        // (DB may emit both ADC_TypeDef.CFGR1 and ADC0_Type.CFGR1).
        if (slot.AbsoluteAddress is uint addr && _byAddress.TryGetValue(addr, out var byAddr))
        {
            if (byAddr.AbsoluteAddress is not null)
                return;
            ReplaceSlot(byAddr, slot);
            return;
        }

        if (_byName.TryGetValue(slot.NameKey, out var byName))
        {
            if (byName.AbsoluteAddress is not null || slot.AbsoluteAddress is null)
                return;
            ReplaceSlot(byName, slot);
            return;
        }

        IndexSlot(slot);
    }

    private void ReplaceSlot(VirtualRegisterSlot oldSlot, VirtualRegisterSlot newSlot)
    {
        _all.Remove(oldSlot);
        if (oldSlot.AbsoluteAddress is uint oa)
            _byAddress.Remove(oa);
        _byName.Remove(oldSlot.NameKey);
        if (!string.IsNullOrEmpty(oldSlot.InstanceName))
            _byName.Remove($"{oldSlot.InstanceName}.{oldSlot.MemberName}");
        _byStructMember.Remove($"{oldSlot.StructName}.{oldSlot.MemberName}");
        IndexSlot(newSlot);
    }

    private void IndexSlot(VirtualRegisterSlot slot)
    {
        _all.Add(slot);
        _byName[slot.NameKey] = slot;
        if (!string.IsNullOrEmpty(slot.InstanceName))
            _byName[$"{slot.InstanceName}.{slot.MemberName}"] = slot;
        _byStructMember[$"{slot.StructName}.{slot.MemberName}"] = slot;
        if (slot.AbsoluteAddress is uint a)
            _byAddress[a] = slot;
    }

    public bool TryGetSlot(string instanceOrStruct, string memberName, out VirtualRegisterSlot? slot)
    {
        var key = $"{instanceOrStruct}.{memberName}";
        if (_byName.TryGetValue(key, out slot)) return true;
        if (_byStructMember.TryGetValue(key, out slot)) return true;
        // LL module EFLASH / empty DMA shell → chip instances FLASH / DMA0.
        if (instanceOrStruct.Equals("EFLASH", StringComparison.OrdinalIgnoreCase))
        {
            if (_byName.TryGetValue($"FLASH.{memberName}", out slot)) return true;
            if (_byStructMember.TryGetValue($"FLASH.{memberName}", out slot)) return true;
        }

        if (instanceOrStruct.Equals("DMA", StringComparison.OrdinalIgnoreCase))
        {
            if (_byName.TryGetValue($"DMA0.{memberName}", out slot)) return true;
            if (_byStructMember.TryGetValue($"DMA0.{memberName}", out slot)) return true;
        }

        slot = null;
        return false;
    }

    public bool TryGetSlotByAddress(uint address, out VirtualRegisterSlot? slot)
        => _byAddress.TryGetValue(address, out slot);

    public bool TryGetByName(string instanceOrStruct, string memberName, out VirtualRegisterView? view)
    {
        if (TryGetSlot(instanceOrStruct, memberName, out var slot) && slot is not null)
        {
            view = slot.ToView();
            return true;
        }
        view = null;
        return false;
    }

    public bool TryGetByAddress(uint address, out VirtualRegisterView? view)
    {
        if (_byAddress.TryGetValue(address, out var slot))
        {
            view = slot.ToView();
            return true;
        }
        view = null;
        return false;
    }

    public IReadOnlyList<VirtualRegisterView> GetAll(string? moduleName = null, string? instanceName = null)
    {
        IEnumerable<VirtualRegisterSlot> q = _all;
        if (!string.IsNullOrWhiteSpace(moduleName))
        {
            // Exact ModuleName, or banked/numbered InstanceName/StructName under the same aggregate
            // (legacy slots may store ModuleName=HRPWM_MST / ADC0 while host asks for HRPWM / ADC).
            q = q.Where(x => BelongsToModule(x, moduleName));
        }

        if (!string.IsNullOrWhiteSpace(instanceName))
            q = q.Where(x => string.Equals(x.InstanceName, instanceName, StringComparison.OrdinalIgnoreCase)
                             || string.Equals(x.StructName, instanceName + "_Type", StringComparison.OrdinalIgnoreCase)
                             || string.Equals(x.StructName, instanceName, StringComparison.OrdinalIgnoreCase));
        return q.Select(x => x.ToView()).ToList();
    }

    public void ResetAll()
    {
        foreach (var s in _all)
            s.CurrentValue = s.ResetValue;
    }

    public Dictionary<Guid, uint> ExportValues()
        => _all.ToDictionary(x => x.DefinitionId, x => x.CurrentValue);

    public void ImportValues(IReadOnlyDictionary<Guid, uint> values)
    {
        foreach (var s in _all)
        {
            if (values.TryGetValue(s.DefinitionId, out var v))
                s.CurrentValue = v & RegisterSemanticsEngine.WidthMask(s.WidthBits);
        }
    }

    public bool HasAddress(uint address) => _byAddress.ContainsKey(address);

    public IEnumerable<string> CollectLimitations()
        => _all.Where(x => x.Limitation != SimulationLimitationKind.None)
            .Select(x => $"{x.NameKey}: {x.Limitation}")
            .Distinct(StringComparer.Ordinal)
            .Take(40);

    /// <summary>
    /// HRPWM_MST / ADC0 / GPIOA all belong to host module HRPWM / ADC / GPIO.
    /// </summary>
    internal static bool BelongsToModule(VirtualRegisterSlot x, string moduleName)
    {
        if (string.Equals(x.ModuleName, moduleName, StringComparison.OrdinalIgnoreCase))
            return true;
        if (string.Equals(
                VirtualMcuDefinitionLoader.NormalizeModuleToken(x.ModuleName),
                moduleName, StringComparison.OrdinalIgnoreCase))
            return true;

        if (x.InstanceName is not null
            && (x.InstanceName.Equals(moduleName, StringComparison.OrdinalIgnoreCase)
                || x.InstanceName.StartsWith(moduleName + "_", StringComparison.OrdinalIgnoreCase)
                || MatchesNumberedOrLetterInstance(x.InstanceName, moduleName)))
            return true;

        if (x.StructName is not null
            && (x.StructName.Equals(moduleName + "_TypeDef", StringComparison.OrdinalIgnoreCase)
                || x.StructName.Equals(moduleName + "_Type", StringComparison.OrdinalIgnoreCase)
                || x.StructName.StartsWith(moduleName + "_", StringComparison.OrdinalIgnoreCase)
                || MatchesNumberedOrLetterInstance(
                    x.StructName.EndsWith("_Type", StringComparison.OrdinalIgnoreCase)
                        ? x.StructName[..^5]
                        : x.StructName.EndsWith("_TypeDef", StringComparison.OrdinalIgnoreCase)
                            ? x.StructName[..^8]
                            : x.StructName,
                    moduleName)))
            return true;

        return false;
    }

    /// <summary>ADC0 / TMR9 / GPIOA under module ADC / TMR / GPIO.</summary>
    private static bool MatchesNumberedOrLetterInstance(string name, string moduleName)
    {
        if (!name.StartsWith(moduleName, StringComparison.OrdinalIgnoreCase))
            return false;
        if (name.Length == moduleName.Length)
            return true;
        var next = name[moduleName.Length];
        return char.IsDigit(next) || (next is >= 'A' and <= 'F') || (next is >= 'a' and <= 'f');
    }
}
