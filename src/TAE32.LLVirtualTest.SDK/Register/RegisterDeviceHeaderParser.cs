using System.Globalization;
using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class RegisterDeviceParseResult
{
    public List<RegisterDefinition> Registers { get; } = new();
    public List<RegisterField> Fields { get; } = new();
    public List<RegisterMacroReference> Macros { get; } = new();
    public List<RegisterParseDiagnostic> Diagnostics { get; } = new();
    public Dictionary<string, uint> InstanceBaseAddresses { get; } = new(StringComparer.Ordinal);
    public Dictionary<string, string> TypeAliases { get; } = new(StringComparer.Ordinal); // GPIO_TypeDef -> GPIOA_Type
}

/// <summary>
/// Parses authoritative CMSIS device / chip headers (tae32g58xx.h + tae32g58xx_chip.h).
/// Offsets prefer explicit CMSIS comments <c>(@ 0x....)</c>; access from __IOM/__IM/__OM.
/// </summary>
public sealed class RegisterDeviceHeaderParser
{
    private static readonly Regex TypedefAlias = new(
        @"typedef\s+([A-Za-z_][A-Za-z0-9_]*)\s+([A-Za-z_][A-Za-z0-9_]*)\s*;",
        RegexOptions.Compiled);

    private static readonly Regex TypedefStruct = new(
        @"typedef\s+struct\s*(?:/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)?\s*\{",
        RegexOptions.Compiled);

    private static readonly Regex MemberLine = new(
        @"^\s*(?<qual>__IOM|__IM|__OM|__IO|__I|__O)\s+(?<type>uint\d+_t|int\d+_t)\s+(?<name>[A-Za-z_][A-Za-z0-9_]*)(?<array>\[[^\]]*\])?\s*;(?<tail>.*)$",
        RegexOptions.Compiled | RegexOptions.Multiline);

    private static readonly Regex OffsetInComment = new(
        @"\(@\s*(0x[0-9A-Fa-f]+)\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    private static readonly Regex StructNameAfter = new(
        @"\}\s*([A-Za-z_][A-Za-z0-9_]*)\s*;",
        RegexOptions.Compiled);

    private static readonly Regex DefineMacro = new(
        @"#define\s+([A-Za-z_][A-Za-z0-9_]*(?:_Pos|_Msk|_Shift|_BIT))\s+(.+?)(?:\s*/\*.*)?$",
        RegexOptions.Compiled | RegexOptions.Multiline);

    private static readonly Regex BaseDefine = new(
        @"#define\s+([A-Z0-9_]+_BASE)\s+(0x[0-9A-Fa-f]+UL|0x[0-9A-Fa-f]+)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    public RegisterDeviceParseResult Parse(
        Guid sdkProjectId,
        string deviceHeaderPath,
        string? chipHeaderPath,
        RegisterLlScanResult llEvidence,
        Guid? chipId)
    {
        var result = new RegisterDeviceParseResult();
        var deviceText = File.ReadAllText(deviceHeaderPath);
        var chipText = !string.IsNullOrWhiteSpace(chipHeaderPath) && File.Exists(chipHeaderPath)
            ? File.ReadAllText(chipHeaderPath)
            : deviceText;
        var definitionFile = chipHeaderPath ?? deviceHeaderPath;

        CollectBases(deviceText, result);
        CollectBases(chipText, result);

        foreach (Match m in TypedefAlias.Matches(deviceText))
        {
            var src = m.Groups[1].Value;
            var dst = m.Groups[2].Value;
            if (dst.EndsWith("_TypeDef", StringComparison.Ordinal))
                result.TypeAliases[dst] = src;
        }

        ParseStructs(sdkProjectId, chipId, chipText, definitionFile, result);

        // Also map TypeDef alias names onto register StructName for LL matching (GPIO_TypeDef).
        ExpandTypeDefAliases(sdkProjectId, chipId, result);

        CollectMacros(sdkProjectId, chipText, definitionFile, result);
        CollectMacros(sdkProjectId, deviceText, deviceHeaderPath, result);

        LinkFieldsFromMacros(sdkProjectId, result);

        result.Diagnostics.Add(new RegisterParseDiagnostic
        {
            SdkProjectId = sdkProjectId,
            Severity = RegisterParseDiagnosticSeverity.Info.ToString(),
            Category = RegisterParseDiagnosticCategory.DeviceHeader.ToString(),
            Message = $"Parsed device/chip headers: structs registers={result.Registers.Count}, bases={result.InstanceBaseAddresses.Count}, macros={result.Macros.Count}",
            FilePath = definitionFile,
            Detail = $"device={deviceHeaderPath}; chip={chipHeaderPath}"
        });

        _ = llEvidence;
        return result;
    }

    private static void CollectBases(string text, RegisterDeviceParseResult result)
    {
        foreach (Match m in BaseDefine.Matches(text))
        {
            if (!TryParseHex(m.Groups[2].Value, out var addr)) continue;
            var name = m.Groups[1].Value;
            if (!name.EndsWith("_BASE", StringComparison.Ordinal)) continue;
            var inst = name[..^5];
            result.InstanceBaseAddresses[inst] = addr;
        }
    }

    private static void ParseStructs(
        Guid sdkProjectId,
        Guid? chipId,
        string text,
        string definitionFile,
        RegisterDeviceParseResult result)
    {
        foreach (Match start in TypedefStruct.Matches(text))
        {
            var open = text.IndexOf('{', start.Index);
            if (open < 0) continue;
            var close = FindMatchingBrace(text, open);
            if (close < 0) continue;
            var body = text[(open + 1)..close];
            var after = text[close..Math.Min(text.Length, close + 200)];
            var nameMatch = StructNameAfter.Match(after);
            if (!nameMatch.Success) continue;
            var structName = nameMatch.Groups[1].Value;

            var lineBase = CountLines(text, 0, open);
            foreach (Match mem in MemberLine.Matches(body))
            {
                var memberName = mem.Groups["name"].Value;
                var qual = mem.Groups["qual"].Value;
                var type = mem.Groups["type"].Value.Trim();
                var tail = mem.Groups["tail"].Success ? mem.Groups["tail"].Value : string.Empty;
                var comment = tail.Trim();
                var array = mem.Groups["array"].Success ? mem.Groups["array"].Value : null;

                int? offset = null;
                var offsetStatus = AddressConfirmationStatus.PendingConfirmation.ToString();
                var om = OffsetInComment.Match(tail);
                if (om.Success && TryParseHex(om.Groups[1].Value, out var off))
                {
                    offset = (int)off;
                    offsetStatus = AddressConfirmationStatus.Confirmed.ToString();
                }

                var width = type.Contains("uint16", StringComparison.OrdinalIgnoreCase) ? 16
                    : type.Contains("uint8", StringComparison.OrdinalIgnoreCase) ? 8
                    : 32;

                // Arrays of reserved words: keep as reserved, width *= count when simple [N]
                if (!string.IsNullOrEmpty(array))
                {
                    var n = Regex.Match(array, @"\[(\d+)\]");
                    if (n.Success && int.TryParse(n.Groups[1].Value, out var count) && count > 0)
                        width *= count;
                }

                var access = MapAccess(qual, memberName);
                var abs = (uint?)null;
                var absStatus = AddressConfirmationStatus.PendingConfirmation.ToString();
                // Absolute filled later when instance known; for GPIOA_Type etc. use struct comment base if present.

                var line = lineBase + CountLines(body, 0, mem.Index);
                result.Registers.Add(new RegisterDefinition
                {
                    SdkProjectId = sdkProjectId,
                    ChipId = chipId,
                    StructName = structName,
                    MemberName = memberName,
                    MemberType = string.IsNullOrWhiteSpace(qual) ? type : $"{qual} {type}".Trim(),
                    OffsetBytes = offset,
                    OffsetStatus = offsetStatus,
                    AbsoluteAddress = abs,
                    AbsoluteAddressStatus = absStatus,
                    WidthBits = width,
                    AccessAttribute = access,
                    Comment = comment,
                    DefinitionFile = ToRelish(definitionFile),
                    StartLine = line,
                    EndLine = line,
                    ParseStatus = offsetStatus == AddressConfirmationStatus.Confirmed.ToString()
                        ? RegisterEntityParseStatus.Complete.ToString()
                        : RegisterEntityParseStatus.Partial.ToString(),
                    NaturalKey = RegisterNaturalKeys.Register(sdkProjectId, structName, memberName)
                });
            }

            // CMSIS often omits (@ offset) on RESERVED pads — fill from adjacent confirmed members.
            FillReservedOffsetsFromLayout(result.Registers, structName);
        }
    }

    /// <summary>
    /// Walk members in declaration order; for gaps without CMSIS offset comments,
    /// set OffsetBytes from running cursor (validated against next confirmed offset when present).
    /// </summary>
    private static void FillReservedOffsetsFromLayout(List<RegisterDefinition> all, string structName)
    {
        var members = all.Where(r => r.StructName == structName).ToList();
        if (members.Count == 0) return;

        int? cursor = null;
        for (var i = 0; i < members.Count; i++)
        {
            var m = members[i];
            var byteWidth = Math.Max(1, (m.WidthBits ?? 32) / 8);

            if (m.OffsetBytes is int known)
            {
                cursor = known + byteWidth;
                continue;
            }

            if (cursor is null)
                continue;

            // Prefer aligning with next confirmed offset if present.
            var nextConfirmed = members.Skip(i + 1).FirstOrDefault(x => x.OffsetBytes is not null);
            if (nextConfirmed?.OffsetBytes is int nextOff)
            {
                // Gap size must match reserved width when possible.
                var gap = nextOff - cursor.Value;
                if (gap == byteWidth || gap > 0)
                {
                    m.OffsetBytes = cursor.Value;
                    m.OffsetStatus = AddressConfirmationStatus.Confirmed.ToString();
                    m.ParseStatus = RegisterEntityParseStatus.Complete.ToString();
                    if (string.IsNullOrWhiteSpace(m.Comment))
                        m.Comment = $"layout pad inferred before {nextConfirmed.MemberName} (@ 0x{nextOff:X})";
                    cursor = cursor.Value + byteWidth;
                    continue;
                }
            }

            m.OffsetBytes = cursor.Value;
            m.OffsetStatus = AddressConfirmationStatus.Confirmed.ToString();
            m.ParseStatus = RegisterEntityParseStatus.Complete.ToString();
            if (string.IsNullOrWhiteSpace(m.Comment))
                m.Comment = "layout pad inferred from adjacent CMSIS offsets";
            cursor = cursor.Value + byteWidth;
        }
    }

    private static void ExpandTypeDefAliases(Guid sdkProjectId, Guid? chipId, RegisterDeviceParseResult result)
    {
        // GPIO_TypeDef -> GPIOA_Type: duplicate register rows under TypeDef name for LL matching.
        var extras = new List<RegisterDefinition>();
        foreach (var (typeDef, concrete) in result.TypeAliases)
        {
            var source = result.Registers.Where(r => r.StructName == concrete).ToList();
            foreach (var r in source)
            {
                extras.Add(new RegisterDefinition
                {
                    SdkProjectId = sdkProjectId,
                    ChipId = chipId,
                    StructName = typeDef,
                    MemberName = r.MemberName,
                    MemberType = r.MemberType,
                    OffsetBytes = r.OffsetBytes,
                    OffsetStatus = r.OffsetStatus,
                    AbsoluteAddress = r.AbsoluteAddress,
                    AbsoluteAddressStatus = r.AbsoluteAddressStatus,
                    WidthBits = r.WidthBits,
                    AccessAttribute = r.AccessAttribute,
                    Comment = r.Comment,
                    DefinitionFile = r.DefinitionFile,
                    StartLine = r.StartLine,
                    EndLine = r.EndLine,
                    ParseStatus = r.ParseStatus,
                    NaturalKey = RegisterNaturalKeys.Register(sdkProjectId, typeDef, r.MemberName)
                });
            }
        }
        result.Registers.AddRange(extras);
    }

    private static void CollectMacros(Guid sdkProjectId, string text, string file, RegisterDeviceParseResult result)
    {
        var seen = new HashSet<string>(result.Macros.Select(m => m.MacroName), StringComparer.Ordinal);
        foreach (Match dm in DefineMacro.Matches(text))
        {
            var macro = dm.Groups[1].Value;
            if (!seen.Add(macro)) continue;
            var expansion = dm.Groups[2].Value.Trim().TrimEnd('\\').Trim();
            result.Macros.Add(new RegisterMacroReference
            {
                SdkProjectId = sdkProjectId,
                MacroName = macro,
                MacroKind = ClassifyKind(macro),
                Expansion = expansion,
                DefinitionFile = ToRelish(file),
                Resolved = true
            });
        }
    }

    private static void LinkFieldsFromMacros(Guid sdkProjectId, RegisterDeviceParseResult result)
    {
        // GPIOA_BSR_BSn_Pos / _Msk -> field on register BSR of GPIOA_Type / GPIO_TypeDef
        var byStructMember = result.Registers
            .GroupBy(r => (r.StructName, r.MemberName), r => r)
            .ToDictionary(g => g.Key, g => g.First());

        var pos = result.Macros.Where(m => m.MacroKind == "Pos").ToList();
        foreach (var p in pos)
        {
            // NAME = PERIPH_REG_FIELD_Pos
            var parts = p.MacroName.Split('_');
            if (parts.Length < 4) continue;
            var periph = parts[0]; // GPIOA
            var reg = parts[1];    // BSR
            var field = string.Join("_", parts.Skip(2).Take(parts.Length - 3)); // BSn

            foreach (var structName in new[] { periph + "_Type", MapCommonTypeDef(periph) })
            {
                if (structName is null) continue;
                if (!byStructMember.TryGetValue((structName, reg), out var register)) continue;

                int? bitPos = null;
                if (TryParseHex(p.Expansion ?? "", out var pv))
                    bitPos = (int)pv;
                else if (uint.TryParse(StripUl(p.Expansion), NumberStyles.Integer, CultureInfo.InvariantCulture, out var pi))
                    bitPos = (int)pi;

                var mskName = p.MacroName[..^4] + "_Msk";
                var msk = result.Macros.FirstOrDefault(m => m.MacroName == mskName);
                string? maskExpr = msk?.Expansion;
                int? width = null;
                if (msk is not null && TryParseHex(msk.Expansion ?? "", out var mv))
                    width = CountBits(mv);

                var naturalKey = $"{register.NaturalKey}|{field}";
                if (result.Fields.Any(f => f.RegisterDefinitionId == register.Id
                                           && string.Equals(f.NaturalKey, naturalKey, StringComparison.Ordinal)))
                    continue;

                var fieldEntity = new RegisterField
                {
                    RegisterDefinitionId = register.Id,
                    Name = field,
                    BitPosition = bitPos,
                    BitWidth = width,
                    Mask = maskExpr is not null && TryParseHex(maskExpr, out var maskVal) ? maskVal : null,
                    MaskExpression = maskExpr,
                    AccessAttribute = register.AccessAttribute,
                    PosMacroName = p.MacroName,
                    MskMacroName = msk?.MacroName,
                    DefinitionFile = p.DefinitionFile,
                    ParseStatus = bitPos is not null
                        ? RegisterEntityParseStatus.Complete.ToString()
                        : RegisterEntityParseStatus.Partial.ToString(),
                    NaturalKey = naturalKey
                };
                result.Fields.Add(fieldEntity);
                p.RegisterDefinitionId = register.Id;
                if (msk is not null) msk.RegisterDefinitionId = register.Id;
            }
        }

        _ = sdkProjectId;
    }

    private static string? MapCommonTypeDef(string periphInstance)
    {
        // GPIOA -> GPIO_TypeDef; UART0 -> UART_TypeDef
        if (periphInstance.StartsWith("GPIO", StringComparison.Ordinal)) return "GPIO_TypeDef";
        var m = Regex.Match(periphInstance, @"^([A-Z]+)(\d+)$");
        return m.Success ? m.Groups[1].Value + "_TypeDef" : null;
    }

    private static string MapAccess(string qual, string memberName)
    {
        if (memberName.StartsWith("RESERVED", StringComparison.OrdinalIgnoreCase))
            return RegisterAccessAttributeKind.Reserved.ToString();
        return qual switch
        {
            "__IM" or "__I" => RegisterAccessAttributeKind.Ro.ToString(),
            "__OM" or "__O" => RegisterAccessAttributeKind.Wo.ToString(),
            "__IOM" or "__IO" => RegisterAccessAttributeKind.Rw.ToString(),
            _ => RegisterAccessAttributeKind.Unknown.ToString()
        };
    }

    private static string ClassifyKind(string name)
    {
        if (name.EndsWith("_Pos", StringComparison.Ordinal)) return "Pos";
        if (name.EndsWith("_Msk", StringComparison.Ordinal)) return "Msk";
        if (name.EndsWith("_Shift", StringComparison.Ordinal)) return "Shift";
        if (name.EndsWith("_BIT", StringComparison.Ordinal)) return "Bit";
        return "Other";
    }

    private static int FindMatchingBrace(string text, int openIdx)
    {
        var depth = 0;
        for (var i = openIdx; i < text.Length; i++)
        {
            var c = text[i];
            if (c == '{') depth++;
            else if (c == '}')
            {
                depth--;
                if (depth == 0) return i;
            }
        }
        return -1;
    }

    private static int CountLines(string text, int start, int end)
    {
        var n = 1;
        var lim = Math.Min(end, text.Length);
        for (var i = start; i < lim; i++)
            if (text[i] == '\n') n++;
        return n;
    }

    private static int CountBits(uint value)
    {
        var n = 0;
        while (value != 0)
        {
            n += (int)(value & 1);
            value >>= 1;
        }
        return Math.Max(n, 1);
    }

    private static string StripUl(string? s)
        => (s ?? string.Empty).Replace("UL", "", StringComparison.OrdinalIgnoreCase)
            .Replace("U", "", StringComparison.OrdinalIgnoreCase)
            .Trim();

    private static bool TryParseHex(string raw, out uint value)
    {
        value = 0;
        var s = StripUl(raw).Trim().Trim('(', ')');
        if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            return uint.TryParse(s[2..], NumberStyles.HexNumber, CultureInfo.InvariantCulture, out value);
        return uint.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out value);
    }

    private static string ToRelish(string path)
    {
        var idx = path.IndexOf("SDKContent", StringComparison.OrdinalIgnoreCase);
        return idx >= 0 ? path[idx..].Replace('\\', '/') : path.Replace('\\', '/');
    }
}
