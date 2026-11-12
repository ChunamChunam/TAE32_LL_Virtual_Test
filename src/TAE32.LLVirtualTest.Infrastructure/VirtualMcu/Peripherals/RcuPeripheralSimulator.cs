using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu.Peripherals;

/// <summary>
/// Minimal RCU clock-enable tracking: records writes to *EN* / *CLK* style registers when present.
/// Does not invent clock trees or frequencies.
/// </summary>
internal sealed class RcuPeripheralSimulator : IVirtualPeripheral
{
    private readonly Dictionary<string, uint> _enableRegs = new(StringComparer.OrdinalIgnoreCase);
    private readonly Dictionary<string, string> _notes = new(StringComparer.OrdinalIgnoreCase);

    public RcuPeripheralSimulator(string instanceName = "RCU")
    {
        InstanceName = instanceName;
        ModuleName = "RCU";
    }

    public string ModuleName { get; }
    public string InstanceName { get; }
    public string SimulatorKind => "RCU-Basic";
    public bool HasModeledBehavior => true;

    public void OnAttached(IVirtualRegisterSpace space)
    {
        _notes["Mode"] = "跟踪含 EN/CLK 名称的寄存器写；无频率/复位树模拟";
        foreach (var reg in space.GetAll(moduleName: "RCU", instanceName: InstanceName))
        {
            if (LooksLikeEnable(reg.MemberName))
                _enableRegs[reg.MemberName] = reg.CurrentValue;
        }
    }

    public void OnAfterWrite(VirtualRegisterView register, uint previous, uint current, VirtualAccessContext? context)
    {
        if (!LooksLikeEnable(register.MemberName)) return;
        _enableRegs[register.MemberName] = current;
        _notes[$"LastEnWrite"] = $"{register.MemberName}: 0x{previous:X8}→0x{current:X8}";
    }

    public void OnAfterRead(VirtualRegisterView register, uint value, VirtualAccessContext? context) { }

    private static bool LooksLikeEnable(string member)
        => member.Contains("EN", StringComparison.OrdinalIgnoreCase)
           || member.Contains("CLK", StringComparison.OrdinalIgnoreCase);

    public VirtualPeripheralView GetView()
    {
        var state = new Dictionary<string, string>(_notes);
        foreach (var kv in _enableRegs)
            state[kv.Key] = $"0x{kv.Value:X8}";
        return new VirtualPeripheralView
        {
            ModuleName = ModuleName,
            InstanceName = InstanceName,
            SimulatorKind = SimulatorKind,
            HasModeledBehavior = true,
            StatusSummary = $"已跟踪使能寄存器 {_enableRegs.Count} 个（无时钟树）",
            State = state
        };
    }

    public void Reset()
    {
        foreach (var key in _enableRegs.Keys.ToList())
            _enableRegs[key] = 0;
        _notes.Clear();
        _notes["Mode"] = "跟踪含 EN/CLK 名称的寄存器写；无频率/复位树模拟";
    }

    public IReadOnlyDictionary<string, string> ExportState()
    {
        var d = new Dictionary<string, string>(_notes);
        foreach (var kv in _enableRegs)
            d["EN:" + kv.Key] = kv.Value.ToString();
        return d;
    }

    public void ImportState(IReadOnlyDictionary<string, string> state)
    {
        _enableRegs.Clear();
        _notes.Clear();
        foreach (var kv in state)
        {
            if (kv.Key.StartsWith("EN:", StringComparison.Ordinal) && uint.TryParse(kv.Value, out var v))
                _enableRegs[kv.Key[3..]] = v;
            else
                _notes[kv.Key] = kv.Value;
        }
    }
}
