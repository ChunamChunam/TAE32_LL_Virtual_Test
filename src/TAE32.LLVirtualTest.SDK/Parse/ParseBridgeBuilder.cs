using System.Text;
using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Parse;

/// <summary>
/// Generates explicitly labeled Parse Bridge headers when device/CMSIS headers are missing.
/// Inferences are taken only from real LL header text (#if defined, member accesses, TypeDef parameters).
/// </summary>
public sealed class ParseBridgeBuilder
{
    private static readonly Regex DefinedInstance = new(
        @"defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    private static readonly Regex TypeDefParam = new(
        @"\b([A-Za-z][A-Za-z0-9_]*_TypeDef)\s*\*",
        RegexOptions.Compiled);

    private static readonly Regex MemberAccess = new(
        @"\b\w+\s*->\s*([A-Za-z][A-Za-z0-9_]*)\b",
        RegexOptions.Compiled);

    private static readonly Regex IsInstanceMacro = new(
        @"#define\s+(IS_[A-Z0-9_]+)\s*\(",
        RegexOptions.Compiled);

    public ParseBridgeResult Build(string llRoot, string bridgeRoot, Guid sdkProjectId)
    {
        Directory.CreateDirectory(bridgeRoot);
        var headers = Directory.GetFiles(llRoot, "tae32g58xx_ll_*.h", SearchOption.TopDirectoryOnly)
            .Where(p => !p.EndsWith("tae32g58xx_ll.h", StringComparison.OrdinalIgnoreCase))
            .ToList();

        var instanceDefines = new HashSet<string>(StringComparer.Ordinal);
        var typedefNames = new HashSet<string>(StringComparer.Ordinal);
        var membersByTypedef = new Dictionary<string, HashSet<string>>(StringComparer.Ordinal);
        var perFileInstances = new Dictionary<string, List<string>>(StringComparer.OrdinalIgnoreCase);
        var isMacros = new HashSet<string>(StringComparer.Ordinal);

        foreach (var file in headers)
        {
            var text = File.ReadAllText(file, Encoding.UTF8);
            var fileKey = Path.GetFileName(file);
            var fileInstances = new List<string>();

            foreach (Match m in DefinedInstance.Matches(text))
            {
                var inst = m.Groups[1].Value;
                if (inst.StartsWith("TAE32_", StringComparison.Ordinal))
                    continue;
                instanceDefines.Add(inst);
                fileInstances.Add(inst);
            }

            if (fileInstances.Count > 0)
                perFileInstances[fileKey] = fileInstances.Distinct(StringComparer.Ordinal).ToList();

            foreach (Match m in TypeDefParam.Matches(text))
                typedefNames.Add(m.Groups[1].Value);

            foreach (Match m in IsInstanceMacro.Matches(text))
                isMacros.Add(m.Groups[1].Value);

            foreach (Match m in MemberAccess.Matches(text))
            {
                var member = m.Groups[1].Value;
                foreach (var td in typedefNames)
                {
                    if (!membersByTypedef.ContainsKey(td))
                        membersByTypedef[td] = new HashSet<string>(StringComparer.Ordinal);
                }
                // Associate members with typedefs referenced in the same file
                foreach (var td in ExtractTypedefsFromFile(text))
                {
                    if (!membersByTypedef.TryGetValue(td, out var set))
                    {
                        set = new HashSet<string>(StringComparer.Ordinal);
                        membersByTypedef[td] = set;
                    }
                    set.Add(member);
                }
            }
        }

        foreach (var td in typedefNames)
        {
            if (!membersByTypedef.ContainsKey(td))
                membersByTypedef[td] = new HashSet<string>(StringComparer.Ordinal) { "REG" };
        }

        var diagnostics = new List<LlParseDiagnostic>();

        var deviceHeader = Path.Combine(bridgeRoot, "tae32g58xx.h");
        var confHeader = Path.Combine(bridgeRoot, "tae32g58xx_ll_conf.h");
        var cmsisHeader = Path.Combine(bridgeRoot, "bridge_cmsis.h");

        WriteDeviceHeader(deviceHeader, typedefNames, membersByTypedef, instanceDefines, isMacros);
        WriteConfHeader(confHeader, perFileInstances);
        WriteCmsisStub(cmsisHeader);

        diagnostics.Add(new LlParseDiagnostic
        {
            SdkProjectId = sdkProjectId,
            Severity = LlParseDiagnosticSeverity.Warning.ToString(),
            Category = LlParseDiagnosticCategory.ParseBridge.ToString(),
            Message = "Parse Bridge generated: tae32g58xx.h / tae32g58xx_ll_conf.h are NOT authoritative SDK device headers.",
            FilePath = deviceHeader,
            Detail = $"Instances={instanceDefines.Count}, typedefs={typedefNames.Count}"
        });

        foreach (var h in new[] { "tae32g58xx.h", "tae32g58xx_ll_conf.h" })
        {
            diagnostics.Add(new LlParseDiagnostic
            {
                SdkProjectId = sdkProjectId,
                Severity = LlParseDiagnosticSeverity.Warning.ToString(),
                Category = LlParseDiagnosticCategory.MissingSdkHeader.ToString(),
                Message = $"SDK device header missing; using Parse Bridge substitute for {h}",
                FilePath = h
            });
        }

        return new ParseBridgeResult(bridgeRoot, diagnostics, instanceDefines.Count, typedefNames.Count);
    }

    private static IEnumerable<string> ExtractTypedefsFromFile(string text)
    {
        foreach (Match m in TypeDefParam.Matches(text))
            yield return m.Groups[1].Value;
    }

    private static void WriteCmsisStub(string path)
    {
        var sb = new StringBuilder();
        sb.AppendLine("/* PARSE BRIDGE — CMSIS stub for LL deep parse only. NOT authoritative SDK. */");
        sb.AppendLine("#ifndef _BRIDGE_CMSIS_H_");
        sb.AppendLine("#define _BRIDGE_CMSIS_H_");
        sb.AppendLine("#ifndef __STATIC_INLINE");
        sb.AppendLine("#define __STATIC_INLINE static inline");
        sb.AppendLine("#endif");
        sb.AppendLine("#ifndef __CM_CMSIS_VERSION_MAIN");
        sb.AppendLine("#define __CM_CMSIS_VERSION_MAIN 5");
        sb.AppendLine("#endif");
        sb.AppendLine("#include <stdint.h>");
        sb.AppendLine("#endif");
        File.WriteAllText(path, sb.ToString(), Encoding.UTF8);
    }

    private static void WriteConfHeader(string path, Dictionary<string, List<string>> perFileInstances)
    {
        var sb = new StringBuilder();
        sb.AppendLine("/* PARSE BRIDGE — tae32g58xx_ll_conf.h (inferred instance gates). NOT authoritative SDK. */");
        sb.AppendLine("#ifndef _PARSE_BRIDGE_LL_CONF_H_");
        sb.AppendLine("#define _PARSE_BRIDGE_LL_CONF_H_");
        sb.AppendLine("#include \"bridge_cmsis.h\"");
        foreach (var inst in perFileInstances.SelectMany(x => x.Value).Distinct(StringComparer.Ordinal).OrderBy(x => x))
            sb.AppendLine($"#define {inst}");
        sb.AppendLine("#define TAE32_USE_ASSERT_INLINE_MANAGEMENT 0");
        sb.AppendLine("#endif");
        File.WriteAllText(path, sb.ToString(), Encoding.UTF8);
    }

    private static void WriteDeviceHeader(
        string path,
        HashSet<string> typedefNames,
        Dictionary<string, HashSet<string>> membersByTypedef,
        HashSet<string> instanceDefines,
        HashSet<string> isMacros)
    {
        var sb = new StringBuilder();
        sb.AppendLine("/* PARSE BRIDGE — tae32g58xx.h (inferred types/instances). NOT authoritative SDK. */");
        sb.AppendLine("#ifndef _PARSE_BRIDGE_TAE32G58XX_H_");
        sb.AppendLine("#define _PARSE_BRIDGE_TAE32G58XX_H_");
        sb.AppendLine("#include \"bridge_cmsis.h\"");
        sb.AppendLine("#include <stdint.h>");
        sb.AppendLine("#ifndef __IO");
        sb.AppendLine("#define __IO volatile");
        sb.AppendLine("#endif");

        foreach (var td in typedefNames.OrderBy(x => x))
        {
            var members = membersByTypedef.TryGetValue(td, out var m) ? m : new HashSet<string> { "REG" };
            sb.AppendLine($"typedef struct {{");
            foreach (var mem in members.OrderBy(x => x))
                sb.AppendLine($"  __IO uint32_t {mem};");
            sb.AppendLine($"}} {td};");
        }

        foreach (var inst in instanceDefines.OrderBy(x => x))
        {
            var td = GuessTypedefForInstance(inst, typedefNames);
            if (td is not null)
                sb.AppendLine($"extern {td} {inst};");
            else
                sb.AppendLine($"#define {inst} ((void*)0)");
        }

        foreach (var macro in isMacros.OrderBy(x => x))
            sb.AppendLine($"#define {macro}(x) (1)");

        sb.AppendLine("#endif");
        File.WriteAllText(path, sb.ToString(), Encoding.UTF8);
    }

    private static string? GuessTypedefForInstance(string instance, HashSet<string> typedefs)
    {
        if (instance.StartsWith("GPIO", StringComparison.Ordinal))
            return typedefs.FirstOrDefault(t => t.Contains("GPIO", StringComparison.Ordinal));
        if (instance.StartsWith("TMR", StringComparison.Ordinal))
            return typedefs.FirstOrDefault(t => t.Contains("TMR", StringComparison.OrdinalIgnoreCase));
        if (instance.StartsWith("I2C", StringComparison.Ordinal))
            return typedefs.FirstOrDefault(t => t.Contains("I2C", StringComparison.Ordinal));
        var prefix = new string(instance.TakeWhile(char.IsLetter).ToArray());
        return typedefs.FirstOrDefault(t => t.StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
               ?? typedefs.FirstOrDefault();
    }
}

public sealed record ParseBridgeResult(
    string BridgeRoot,
    IReadOnlyList<LlParseDiagnostic> Diagnostics,
    int InstanceCount,
    int TypedefCount);
