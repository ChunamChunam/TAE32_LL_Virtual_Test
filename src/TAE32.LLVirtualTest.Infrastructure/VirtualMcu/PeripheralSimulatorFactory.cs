using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu.Peripherals;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

internal static class PeripheralSimulatorFactory
{
    public static IVirtualPeripheral Create(string? moduleName, string instanceName)
    {
        var module = moduleName ?? InferModule(instanceName);
        return module.ToUpperInvariant() switch
        {
            "GPIO" => new GpioPeripheralSimulator(instanceName),
            "RCU" => new RcuPeripheralSimulator(instanceName),
            _ => new PassthroughPeripheral(module, instanceName)
        };
    }

    private static string InferModule(string instanceName)
    {
        if (instanceName.StartsWith("GPIO", StringComparison.OrdinalIgnoreCase)) return "GPIO";
        if (instanceName.Equals("RCU", StringComparison.OrdinalIgnoreCase)) return "RCU";
        var m = System.Text.RegularExpressions.Regex.Match(instanceName, @"^([A-Z]+?)(\d+|[A-F])?$");
        return m.Success ? m.Groups[1].Value : instanceName;
    }
}
