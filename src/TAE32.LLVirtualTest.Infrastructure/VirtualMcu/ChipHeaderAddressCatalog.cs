using System.Globalization;
using System.Text.RegularExpressions;

namespace TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

/// <summary>
/// Live map of peripheral BASE + register offsets parsed from authoritative chip headers
/// (<c>tae32g58xx_chip.h</c> / <c>tae32g58xx_chip_struct.h</c> / <c>tae32g58xx.h</c>).
/// Absolute address = BASE + member offset; overrides stale DB AbsoluteAddress when present.
/// </summary>
internal sealed class ChipHeaderAddressCatalog
{
    private static readonly Regex BaseDefine = new(
        @"#define\s+(?<name>[A-Z0-9_]+_BASE)\s+(?<val>0x[0-9A-Fa-f]+UL|0x[0-9A-Fa-f]+)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);

    private static readonly Regex TypedefAlias = new(
        @"typedef\s+(?<src>[A-Za-z_][A-Za-z0-9_]*)\s+(?<dst>[A-Za-z_][A-Za-z0-9_]*)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex TypedefStruct = new(
        @"typedef\s+struct\s*(?:/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)?\s*\{",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex StructNameAfter = new(
        @"\}\s*(?<name>[A-Za-z_][A-Za-z0-9_]*)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex MemberWithOffset = new(
        @"^\s*(?:__IOM|__IM|__OM|__IO|__I|__O)\s+(?:uint\d+_t|int\d+_t)\s+(?<name>[A-Za-z_][A-Za-z0-9_]*)\b[^;]*;.*\(@\s*(?<off>0x[0-9A-Fa-f]+)\)",
        RegexOptions.Compiled | RegexOptions.Multiline | RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);

    private readonly Dictionary<string, uint> _bases = new(StringComparer.OrdinalIgnoreCase);
    // structName (WWDG_Type / WWDG_TypeDef) -> member -> offset
    private readonly Dictionary<string, Dictionary<string, int>> _offsets =
        new(StringComparer.OrdinalIgnoreCase);
    private readonly Dictionary<string, string> _aliases = new(StringComparer.OrdinalIgnoreCase);

    public string? ChipHeaderPath { get; private set; }
    public string? ChipStructPath { get; private set; }
    public string? DeviceHeaderPath { get; private set; }
    public int BaseCount => _bases.Count;
    public int StructCount => _offsets.Count;

    public static ChipHeaderAddressCatalog? TryLoad(string? sdkRoot)
    {
        if (string.IsNullOrWhiteSpace(sdkRoot) || !Directory.Exists(sdkRoot))
            return null;

        if (!TryLocateHeaders(sdkRoot, out var device, out var chip, out var chipStruct))
            return null;

        var catalog = new ChipHeaderAddressCatalog
        {
            DeviceHeaderPath = device,
            ChipHeaderPath = chip,
            ChipStructPath = chipStruct
        };

        if (device is not null)
            catalog.IngestText(File.ReadAllText(device), parseStructs: false);
        if (chip is not null)
            catalog.IngestText(File.ReadAllText(chip), parseStructs: true);
        if (chipStruct is not null)
            catalog.IngestText(File.ReadAllText(chipStruct), parseStructs: true);

        return catalog.BaseCount > 0 || catalog.StructCount > 0 ? catalog : null;
    }

    private readonly Dictionary<string, uint> _defines = new(StringComparer.OrdinalIgnoreCase);

    public bool TryGetBase(string instanceName, out uint baseAddr)
        => _bases.TryGetValue(instanceName, out baseAddr);

    /// <summary>Resolve field Mask/Pos from chip #define literals (e.g. WWDG_PSCR_PSC_Msk).</summary>
    public bool TryResolveFieldMaskPos(
        string? instanceName,
        string memberName,
        string fieldName,
        string? mskMacroName,
        out uint mask,
        out int pos)
    {
        mask = 0;
        pos = 0;
        var macros = new List<string>();
        if (!string.IsNullOrWhiteSpace(mskMacroName))
            macros.Add(mskMacroName!);
        if (!string.IsNullOrWhiteSpace(instanceName))
            macros.Add($"{instanceName}_{memberName}_{fieldName}_Msk");
        macros.Add($"{memberName}_{fieldName}_Msk");

        foreach (var macro in macros.Distinct(StringComparer.OrdinalIgnoreCase))
        {
            if (!_defines.TryGetValue(macro, out var m) || m == 0) continue;
            mask = m;
            var posMacro = macro.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
                ? macro[..^4] + "_Pos"
                : macro + "_Pos";
            pos = _defines.TryGetValue(posMacro, out var p) ? (int)p : CountTrailingZeros(m);
            return true;
        }

        return false;
    }

    public bool TryGetOffset(string? instanceName, string? structName, string memberName, out int offset)
    {
        offset = 0;
        foreach (var key in StructKeys(instanceName, structName))
        {
            if (_offsets.TryGetValue(key, out var map)
                && map.TryGetValue(memberName, out offset))
                return true;
        }

        return false;
    }

    /// <summary>
    /// Resolve absolute address from chip headers. Returns false if BASE or offset missing.
    /// </summary>
    public bool TryResolveAbsolute(
        string? instanceName,
        string? structName,
        string memberName,
        out uint absolute,
        out uint baseAddr,
        out int offset)
    {
        absolute = 0;
        baseAddr = 0;
        offset = 0;

        var inst = instanceName;
        if (string.IsNullOrWhiteSpace(inst) && !string.IsNullOrWhiteSpace(structName))
        {
            if (structName!.EndsWith("_Type", StringComparison.Ordinal))
                inst = structName[..^5];
            else if (structName.EndsWith("_TypeDef", StringComparison.Ordinal))
                inst = structName[..^8];
        }

        if (string.IsNullOrWhiteSpace(inst) || !_bases.TryGetValue(inst, out baseAddr))
            return false;

        if (!TryGetOffset(inst, structName, memberName, out offset))
            return false;

        absolute = baseAddr + (uint)offset;
        return true;
    }

    private IEnumerable<string> StructKeys(string? instanceName, string? structName)
    {
        if (!string.IsNullOrWhiteSpace(structName))
        {
            yield return structName!;
            if (_aliases.TryGetValue(structName!, out var aliased))
                yield return aliased;
            // TypeDef -> Type
            if (structName!.EndsWith("_TypeDef", StringComparison.Ordinal))
                yield return structName[..^8] + "_Type";
        }

        if (!string.IsNullOrWhiteSpace(instanceName))
        {
            yield return instanceName + "_Type";
            yield return instanceName + "_TypeDef";
            yield return instanceName!;
        }
    }

    private static readonly Regex UintDefine = new(
        @"#define\s+(?<name>[A-Za-z_][A-Za-z0-9_]*(?:_Msk|_Pos|_Val|_BASE))\s+(?<val>0x[0-9A-Fa-f]+UL|0x[0-9A-Fa-f]+U?|\d+UL|\d+U?)\b",
        RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);

    private void IngestText(string text, bool parseStructs)
    {
        foreach (Match m in BaseDefine.Matches(text))
        {
            if (!TryParseHex(m.Groups["val"].Value, out var addr)) continue;
            var name = m.Groups["name"].Value;
            if (!name.EndsWith("_BASE", StringComparison.OrdinalIgnoreCase)) continue;
            _bases[name[..^5]] = addr;
        }

        foreach (Match m in UintDefine.Matches(text))
        {
            if (!TryParseHex(m.Groups["val"].Value, out var v)) continue;
            _defines[m.Groups["name"].Value] = v;
        }

        foreach (Match m in TypedefAlias.Matches(text))
        {
            var src = m.Groups["src"].Value;
            var dst = m.Groups["dst"].Value;
            if (dst.EndsWith("_TypeDef", StringComparison.Ordinal))
                _aliases[dst] = src;
        }

        if (!parseStructs) return;

        foreach (Match start in TypedefStruct.Matches(text))
        {
            var bodyStart = start.Index + start.Length;
            var depth = 1;
            var i = bodyStart;
            for (; i < text.Length && depth > 0; i++)
            {
                if (text[i] == '{') depth++;
                else if (text[i] == '}') depth--;
            }

            if (depth != 0) continue;
            var body = text[bodyStart..(i - 1)];
            var after = text.Substring(i - 1, Math.Min(120, text.Length - (i - 1)));
            var nameMatch = StructNameAfter.Match(after);
            if (!nameMatch.Success) continue;
            var structName = nameMatch.Groups["name"].Value;

            if (!_offsets.TryGetValue(structName, out var map))
            {
                map = new Dictionary<string, int>(StringComparer.OrdinalIgnoreCase);
                _offsets[structName] = map;
            }

            foreach (Match mem in MemberWithOffset.Matches(body))
            {
                if (!TryParseHex(mem.Groups["off"].Value, out var offU)) continue;
                map[mem.Groups["name"].Value] = (int)offU;
            }
        }
    }

    private static bool TryParseHex(string text, out uint value)
    {
        value = 0;
        var s = text.Trim();
        if (s.EndsWith("UL", StringComparison.OrdinalIgnoreCase))
            s = s[..^2];
        else if (s.EndsWith("U", StringComparison.OrdinalIgnoreCase))
            s = s[..^1];
        if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            return uint.TryParse(s.AsSpan(2), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out value);
        return uint.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out value);
    }

    private static int CountTrailingZeros(uint mask)
    {
        if (mask == 0) return 0;
        var pos = 0;
        while ((mask & 1u) == 0 && pos < 31)
        {
            mask >>= 1;
            pos++;
        }
        return pos;
    }

    private static bool TryLocateHeaders(
        string sdkRoot,
        out string? deviceHeader,
        out string? chipHeader,
        out string? chipStruct)
    {
        deviceHeader = null;
        chipHeader = null;
        chipStruct = null;

        foreach (var hit in SafeEnumerateFiles(sdkRoot, "tae32g58xx.h"))
        {
            if (hit.Contains("ParseBridge", StringComparison.OrdinalIgnoreCase))
                continue;
            deviceHeader = hit;
            break;
        }

        // Prefer Device/Inc next to device header; also search chip files directly.
        var searchDirs = new List<string>();
        if (deviceHeader is not null)
            searchDirs.Add(Path.GetDirectoryName(deviceHeader)!);
        searchDirs.Add(Path.Combine(sdkRoot, "SDK", "Drivers", "TAE32G58xx_Device", "Inc"));
        searchDirs.Add(Path.Combine(sdkRoot, "Drivers", "TAE32G58xx_Device", "Inc"));
        searchDirs.Add(sdkRoot);

        foreach (var dir in searchDirs.Distinct(StringComparer.OrdinalIgnoreCase))
        {
            if (!Directory.Exists(dir)) continue;
            var chip = Path.Combine(dir, "tae32g58xx_chip.h");
            var cs = Path.Combine(dir, "tae32g58xx_chip_struct.h");
            if (chipHeader is null && File.Exists(chip)) chipHeader = chip;
            if (chipStruct is null && File.Exists(cs)) chipStruct = cs;
        }

        if (chipHeader is null)
            chipHeader = SafeEnumerateFiles(sdkRoot, "tae32g58xx_chip.h").FirstOrDefault();
        if (chipStruct is null)
            chipStruct = SafeEnumerateFiles(sdkRoot, "tae32g58xx_chip_struct.h").FirstOrDefault();

        return deviceHeader is not null || chipHeader is not null || chipStruct is not null;
    }

    private static IEnumerable<string> SafeEnumerateFiles(string root, string pattern)
    {
        IEnumerable<string> empty = Array.Empty<string>();
        try
        {
            return Directory.EnumerateFiles(root, pattern, SearchOption.AllDirectories)
                .Where(p => !p.Contains($"{Path.DirectorySeparatorChar}obj{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase)
                            && !p.Contains($"{Path.DirectorySeparatorChar}bin{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase));
        }
        catch
        {
            return empty;
        }
    }
}
