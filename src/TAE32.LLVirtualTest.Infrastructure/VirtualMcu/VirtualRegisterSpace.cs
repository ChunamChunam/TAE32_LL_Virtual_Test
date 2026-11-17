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
        if (slot.AbsoluteAddress is uint addr && _byAddress.ContainsKey(addr))
            return;
        if (_byName.ContainsKey(slot.NameKey))
            return;

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
            // Exact ModuleName, or banked InstanceName/StructName under the same aggregate
            // (legacy slots may store ModuleName=HRPWM_MST while host asks for HRPWM).
            q = q.Where(x =>
                string.Equals(x.ModuleName, moduleName, StringComparison.OrdinalIgnoreCase)
                || string.Equals(
                    VirtualMcuDefinitionLoader.NormalizeModuleToken(x.ModuleName),
                    moduleName, StringComparison.OrdinalIgnoreCase)
                || (x.InstanceName is not null
                    && (x.InstanceName.Equals(moduleName, StringComparison.OrdinalIgnoreCase)
                        || x.InstanceName.StartsWith(moduleName + "_", StringComparison.OrdinalIgnoreCase)))
                || (x.StructName is not null
                    && (x.StructName.StartsWith(moduleName + "_", StringComparison.OrdinalIgnoreCase)
                        || x.StructName.Equals(moduleName + "_TypeDef", StringComparison.OrdinalIgnoreCase)
                        || x.StructName.Equals(moduleName + "_Type", StringComparison.OrdinalIgnoreCase))));
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
}
