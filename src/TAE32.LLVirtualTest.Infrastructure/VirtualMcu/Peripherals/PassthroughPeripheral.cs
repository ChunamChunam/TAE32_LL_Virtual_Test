using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu.Peripherals;

/// <summary>Stores registers only; no side-effect modeling.</summary>
internal sealed class PassthroughPeripheral : IVirtualPeripheral
{
    private readonly Dictionary<string, string> _extra = new(StringComparer.OrdinalIgnoreCase);

    public PassthroughPeripheral(string moduleName, string instanceName)
    {
        ModuleName = moduleName;
        InstanceName = instanceName;
    }

    public string ModuleName { get; }
    public string InstanceName { get; }
    public string SimulatorKind => "Passthrough";
    public bool HasModeledBehavior => false;

    public void OnAttached(IVirtualRegisterSpace space) { }

    public void OnAfterWrite(VirtualRegisterView register, uint previous, uint current, VirtualAccessContext? context)
        => _extra["LastWrite"] = $"{register.MemberName}: 0x{previous:X8}→0x{current:X8}";

    public void OnAfterRead(VirtualRegisterView register, uint value, VirtualAccessContext? context) { }

    public VirtualPeripheralView GetView()
    {
        var state = new Dictionary<string, string>(_extra, StringComparer.OrdinalIgnoreCase);
        state["Limitation"] = "PeripheralBehaviorNotModeled";
        return new VirtualPeripheralView
        {
            ModuleName = ModuleName,
            InstanceName = InstanceName,
            SimulatorKind = SimulatorKind,
            HasModeledBehavior = false,
            StatusSummary = "仅寄存器存储；外设侧效应未模拟",
            State = state
        };
    }

    public void Reset() => _extra.Clear();

    public IReadOnlyDictionary<string, string> ExportState() => new Dictionary<string, string>(_extra);

    public void ImportState(IReadOnlyDictionary<string, string> state)
    {
        _extra.Clear();
        foreach (var kv in state) _extra[kv.Key] = kv.Value;
    }
}
