using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu.Peripherals;

/// <summary>
/// Minimal GPIO behavior using real member names from loaded definitions (ODR/IDR/BSR when present).
/// Does not invent pins or alternate functions.
/// </summary>
internal sealed class GpioPeripheralSimulator : IVirtualPeripheral
{
    private IVirtualRegisterSpace? _space;
    private uint _outputShadow;
    private readonly Dictionary<string, string> _state = new(StringComparer.OrdinalIgnoreCase);

    public GpioPeripheralSimulator(string instanceName)
    {
        InstanceName = instanceName;
        ModuleName = "GPIO";
    }

    public string ModuleName { get; }
    public string InstanceName { get; }
    public string SimulatorKind => "GPIO-Basic";
    public bool HasModeledBehavior => true;

    public void OnAttached(IVirtualRegisterSpace space)
    {
        _space = space;
        if (_space.TryGetByName(InstanceName, "ODR", out var odr) && odr is not null)
            _outputShadow = odr.CurrentValue;
        _state["Mode"] = "Basic ODR/IDR/BSR shadow";
    }

    public void OnAfterWrite(VirtualRegisterView register, uint previous, uint current, VirtualAccessContext? context)
    {
        var member = register.MemberName.ToUpperInvariant();
        if (member is "ODR")
        {
            _outputShadow = current;
            _state["ODR"] = $"0x{current:X8}";
            TryMirrorToIdr(current);
        }
        else if (member is "BSR" or "BSRR")
        {
            // Common pattern: low 16 set, high 16 reset — only apply if width suggests it
            var set = current & 0xFFFFu;
            var reset = (current >> 16) & 0xFFFFu;
            if (set == 0 && reset == 0 && register.WidthBits <= 16)
            {
                // Some parts use separate set register; treat write as OR into ODR
                _outputShadow |= current;
            }
            else
            {
                _outputShadow = (_outputShadow | set) & ~reset;
            }
            _state["BSR"] = $"0x{current:X8}";
            _state["ODR_shadow"] = $"0x{_outputShadow:X8}";
            WriteOdrShadow();
            TryMirrorToIdr(_outputShadow);
        }
        else if (member is "BRR")
        {
            _outputShadow &= ~current;
            _state["BRR"] = $"0x{current:X8}";
            WriteOdrShadow();
            TryMirrorToIdr(_outputShadow);
        }
    }

    public void OnAfterRead(VirtualRegisterView register, uint value, VirtualAccessContext? context)
    {
        if (register.MemberName.Equals("IDR", StringComparison.OrdinalIgnoreCase))
            _state["IDR"] = $"0x{value:X8}";
    }

    private void WriteOdrShadow()
    {
        _state["ODR_shadow"] = $"0x{_outputShadow:X8}";
    }

    /// <summary>TAE32 uses DOR (and some aliases ODR); keep storage in sync after BSR/BRR.</summary>
    public void SyncOutputRegisters(Action<string, string, uint> forceWrite)
    {
        if (_space is null) return;
        foreach (var member in new[] { "DOR", "ODR" })
        {
            if (_space.TryGetByName(InstanceName, member, out _))
                forceWrite(InstanceName, member, _outputShadow);
        }
    }

    private void TryMirrorToIdr(uint level)
    {
        // Loopback model: IDR mirrors ODR when IDR register exists (marked as limitation-lite).
        _state["IDR_loopback"] = $"0x{level:X8}";
        _state["Note"] = "IDR 默认回环到 ODR（非真实引脚输入）";
    }

    public VirtualPeripheralView GetView()
    {
        var state = new Dictionary<string, string>(_state, StringComparer.OrdinalIgnoreCase);
        state["ODR_shadow"] = $"0x{_outputShadow:X8}";
        return new VirtualPeripheralView
        {
            ModuleName = ModuleName,
            InstanceName = InstanceName,
            SimulatorKind = SimulatorKind,
            HasModeledBehavior = true,
            StatusSummary = $"ODR_shadow=0x{_outputShadow:X8}（基础 GPIO；无 AF/中断模拟）",
            State = state
        };
    }

    public void Reset()
    {
        _outputShadow = 0;
        _state.Clear();
        _state["Mode"] = "Basic ODR/IDR/BSR shadow";
    }

    public IReadOnlyDictionary<string, string> ExportState()
    {
        var d = new Dictionary<string, string>(_state, StringComparer.OrdinalIgnoreCase);
        d["ODR_shadow"] = _outputShadow.ToString();
        return d;
    }

    public void ImportState(IReadOnlyDictionary<string, string> state)
    {
        _state.Clear();
        foreach (var kv in state)
        {
            if (kv.Key == "ODR_shadow" && uint.TryParse(kv.Value, out var v))
                _outputShadow = v;
            else
                _state[kv.Key] = kv.Value;
        }
    }

    /// <summary>Apply loopback IDR value into register space when IDR exists.</summary>
    public void SyncIdrLoopback(Action<string, string, uint> forceWrite)
    {
        if (_space is null) return;
        if (_space.TryGetByName(InstanceName, "IDR", out _))
            forceWrite(InstanceName, "IDR", _outputShadow);
    }
}
