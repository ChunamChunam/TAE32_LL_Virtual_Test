using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Maps harness peripheral hints (e.g. macro name ADC) to virtual MCU register instance names (ADC0).
/// Multi-bank aggregates (HRPWM MST/SLVn/COM) must not pick the alphabetically-first bank.
/// </summary>
internal static class VirtualMcuInstanceResolver
{
    private static readonly Dictionary<string, string> ModuleDefaultInstance = new(StringComparer.OrdinalIgnoreCase)
    {
        ["ADC"] = "ADC0",
        ["GPIO"] = "GPIOA",
        ["TMR"] = "TMR0",
        ["HRPWM"] = "HRPWM_MST", // TypeDef image base = Master bank (not HRPWM_COM)
        ["RCU"] = "RCU",
        ["SYSCTRL"] = "SYSCTRL",
    };

    public static async Task<string> ResolveAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string hint,
        string? moduleName,
        CancellationToken cancellationToken,
        string? functionName = null)
    {
        if (string.IsNullOrWhiteSpace(hint))
            hint = moduleName ?? "PERI";

        // Exact instance filter (ADC0, HRPWM_MST, …).
        var exact = await mcu.GetRegistersAsync(mcuId, moduleName, hint, cancellationToken);
        if (exact.Count > 0
            && exact.Any(r => string.Equals(r.InstanceName, hint, StringComparison.OrdinalIgnoreCase)))
            return hint;

        var moduleRegs = string.IsNullOrWhiteSpace(moduleName)
            ? await mcu.GetRegistersAsync(mcuId, hint, null, cancellationToken)
            : await mcu.GetRegistersAsync(mcuId, moduleName, null, cancellationToken);

        if (moduleRegs.Count > 0)
        {
            var picked = PreferInstance(moduleRegs, hint, moduleName, functionName);
            if (!string.IsNullOrWhiteSpace(picked))
                return picked!;
        }

        if (ModuleDefaultInstance.TryGetValue(hint, out var fallback))
            return fallback;
        if (moduleName is not null && ModuleDefaultInstance.TryGetValue(moduleName, out fallback))
            return fallback;

        // Function-name bank even when MCU has no regs yet (generation-time safety).
        var fromFn = InferBankInstance(functionName, moduleName ?? hint);
        if (!string.IsNullOrWhiteSpace(fromFn))
            return fromFn!;

        return hint;
    }

    /// <summary>
    /// Prefer function bank (MST/COM/SLV), then module default, then TypeDef-base (lowest address),
    /// never alphabetical first (HRPWM_COM would win over MST).
    /// </summary>
    internal static string? PreferInstance(
        IReadOnlyList<VirtualRegisterView> moduleRegs,
        string hint,
        string? moduleName,
        string? functionName)
    {
        var instances = moduleRegs
            .Select(r => r.InstanceName)
            .Where(n => !string.IsNullOrWhiteSpace(n))
            .Distinct(StringComparer.OrdinalIgnoreCase)
            .ToList();
        if (instances.Count == 0)
            return null;

        if (instances.Any(i => string.Equals(i, hint, StringComparison.OrdinalIgnoreCase)))
            return hint;

        var bank = InferBankInstance(functionName, moduleName ?? hint);
        if (!string.IsNullOrWhiteSpace(bank)
            && instances.Any(i => string.Equals(i, bank, StringComparison.OrdinalIgnoreCase)))
            return bank!;

        var moduleKey = moduleName ?? hint;
        if (ModuleDefaultInstance.TryGetValue(moduleKey, out var def)
            && instances.Any(i => string.Equals(i, def, StringComparison.OrdinalIgnoreCase)))
            return def;

        // Aggregate: Master / lowest AbsoluteAddress (HRPWM_TypeDef base).
        if (IsAggregateModule(moduleKey) || instances.Any(IsBankedInstance))
        {
            var mst = instances.FirstOrDefault(i =>
                i!.EndsWith("_MST", StringComparison.OrdinalIgnoreCase));
            if (!string.IsNullOrWhiteSpace(mst))
                return mst;

            var byAddr = moduleRegs
                .Where(r => r.AbsoluteAddress is not null && !string.IsNullOrWhiteSpace(r.InstanceName))
                .OrderBy(r => r.AbsoluteAddress!.Value)
                .Select(r => r.InstanceName!)
                .FirstOrDefault();
            if (!string.IsNullOrWhiteSpace(byAddr))
                return byAddr;
        }

        return instances[0];
    }

    /// <summary>
    /// <c>LL_HRPWM_MST_SetPrescaler</c> → <c>HRPWM_MST</c>;
    /// <c>LL_HRPWM_COM_*</c> → <c>HRPWM_COM</c>;
    /// <c>LL_HRPWM_SLV_*</c> → <c>HRPWM_SLV0</c>.
    /// </summary>
    internal static string? InferBankInstance(string? functionName, string? moduleOrHint)
    {
        if (string.IsNullOrWhiteSpace(functionName))
            return null;

        var m = Regex.Match(
            functionName,
            @"^LL_(?<mod>[A-Za-z][A-Za-z0-9]*)_(?<bank>MST|COM|SLV)(?:_|$)",
            RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);
        if (!m.Success)
            return null;

        var mod = m.Groups["mod"].Value.ToUpperInvariant();
        var bank = m.Groups["bank"].Value.ToUpperInvariant();
        if (bank == "SLV")
            return $"{mod}_SLV0";
        return $"{mod}_{bank}";
    }

    private static bool IsAggregateModule(string? module)
        => string.Equals(module, "HRPWM", StringComparison.OrdinalIgnoreCase);

    private static bool IsBankedInstance(string? instance)
        => !string.IsNullOrWhiteSpace(instance)
           && Regex.IsMatch(instance,
               @"^[A-Za-z]+_(MST|COM|SLV\d+|CH\d+|UNIT\d+|TIM\d+)$",
               RegexOptions.IgnoreCase);
}
