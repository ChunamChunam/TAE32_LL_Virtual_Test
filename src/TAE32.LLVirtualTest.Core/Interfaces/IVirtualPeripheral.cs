using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>
/// Extensible peripheral simulator. Prefer GPIO/RCU first; others may be passthrough.
/// Must not invent register names — only react to loaded Phase-4 definitions.
/// </summary>
public interface IVirtualPeripheral
{
    string ModuleName { get; }
    string InstanceName { get; }
    string SimulatorKind { get; }
    bool HasModeledBehavior { get; }

    void OnAttached(IVirtualRegisterSpace space);

    void OnAfterWrite(VirtualRegisterView register, uint previous, uint current, VirtualAccessContext? context);

    void OnAfterRead(VirtualRegisterView register, uint value, VirtualAccessContext? context);

    VirtualPeripheralView GetView();

    void Reset();

    IReadOnlyDictionary<string, string> ExportState();

    void ImportState(IReadOnlyDictionary<string, string> state);
}

/// <summary>Addressable / name-addressable register storage for one virtual MCU.</summary>
public interface IVirtualRegisterSpace
{
    bool TryGetByName(string instanceOrStruct, string memberName, out VirtualRegisterView? view);
    bool TryGetByAddress(uint address, out VirtualRegisterView? view);
    IReadOnlyList<VirtualRegisterView> GetAll(string? moduleName = null, string? instanceName = null);
}
