using System.Text;
using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Sdk;

namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class LlInstanceEvidence
{
    public string Name { get; init; } = string.Empty;
    public string SourceFile { get; init; } = string.Empty;
    public int Line { get; init; }
    public string ModuleName { get; init; } = string.Empty;
    public string? TypeDefName { get; init; }
}

public sealed class LlRegisterMemberEvidence
{
    public string StructName { get; init; } = string.Empty;
    public string MemberName { get; init; } = string.Empty;
    public string SourceFile { get; init; } = string.Empty;
    public int Line { get; init; }
    public string ModuleName { get; init; } = string.Empty;
}

public sealed class LlMacroEvidence
{
    public string MacroName { get; init; } = string.Empty;
    public string MacroKind { get; init; } = "Other";
    public string SourceFile { get; init; } = string.Empty;
    public int Line { get; init; }
    public string ModuleName { get; init; } = string.Empty;
}

public sealed class RegisterLlScanResult
{
    public IReadOnlyList<LlInstanceEvidence> Instances { get; init; } = Array.Empty<LlInstanceEvidence>();
    public IReadOnlyList<LlRegisterMemberEvidence> RegisterMembers { get; init; } = Array.Empty<LlRegisterMemberEvidence>();
    public IReadOnlyList<LlMacroEvidence> MacroReferences { get; init; } = Array.Empty<LlMacroEvidence>();
    public IReadOnlyDictionary<string, string> InstanceToTypeDef { get; init; } =
        new Dictionary<string, string>(StringComparer.Ordinal);
    public IReadOnlyDictionary<string, string> ModuleToPrimaryTypeDef { get; init; } =
        new Dictionary<string, string>(StringComparer.Ordinal);
}

public sealed class RegisterLlEvidenceScanner
{
    private static readonly Regex DefinedInstance = new(
        @"#if\s+defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    private static readonly Regex OrDefinedInstance = new(
        @"defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    private static readonly Regex TypeDefParam = new(
        @"\b([A-Za-z][A-Za-z0-9_]*_TypeDef)\s*\*",
        RegexOptions.Compiled);

    private static readonly Regex MemberAccess = new(
        @"\b(?:\w+|[)]\w+)\s*->\s*([A-Za-z][A-Za-z0-9_]*)\b",
        RegexOptions.Compiled);

    private static readonly Regex ParenMemberAccess = new(
        @"\(\s*\w+\s*\)\s*->\s*([A-Za-z][A-Za-z0-9_]*)",
        RegexOptions.Compiled);

    private static readonly Regex MacroPattern = new(
        @"\b([A-Z][A-Za-z0-9_]*(?:_Pos|_Msk|_Shift|_BIT))\b",
        RegexOptions.Compiled);

    public RegisterLlScanResult Scan(string llRoot, string? familyId = null)
    {
        familyId ??= DiscoverFamilyId(llRoot);
        var headers = string.IsNullOrWhiteSpace(familyId)
            ? Directory.GetFiles(llRoot, "tae32*_ll_*.h", SearchOption.TopDirectoryOnly)
                .Where(p =>
                {
                    var n = Path.GetFileName(p);
                    return !n.EndsWith("_ll.h", StringComparison.OrdinalIgnoreCase)
                           && !n.EndsWith("_ll_def.h", StringComparison.OrdinalIgnoreCase);
                })
                .ToList()
            : SdkSeriesLayout.EnumerateLlModuleHeaders(llRoot, familyId).ToList();

        var instances = new List<LlInstanceEvidence>();
        var members = new List<LlRegisterMemberEvidence>();
        var macros = new List<LlMacroEvidence>();
        var instanceToTd = new Dictionary<string, string>(StringComparer.Ordinal);
        var moduleToTd = new Dictionary<string, string>(StringComparer.Ordinal);

        foreach (var file in headers)
        {
            var text = File.ReadAllText(file, Encoding.UTF8);
            var rel = Path.GetRelativePath(llRoot, file).Replace('\\', '/');
            if (!rel.StartsWith("LL/", StringComparison.OrdinalIgnoreCase))
                rel = "LL/" + Path.GetFileName(file);

            var module = SdkSeriesLayout.ModuleFromLlHeader(Path.GetFileName(file), familyId)
                         ?? ModuleFromHeader(Path.GetFileName(file));
            var lines = text.Replace("\r\n", "\n").Split('\n');
            var fileTypedefs = TypeDefParam.Matches(text).Select(m => m.Groups[1].Value).Distinct(StringComparer.Ordinal).ToList();
            if (fileTypedefs.Count > 0)
                moduleToTd[module] = fileTypedefs[0];

            for (var i = 0; i < lines.Length; i++)
            {
                var lineNo = i + 1;
                var line = lines[i];

                foreach (Match m in OrDefinedInstance.Matches(line))
                {
                    var inst = m.Groups[1].Value;
                    if (inst.StartsWith("TAE32_", StringComparison.Ordinal)) continue;
                    instances.Add(new LlInstanceEvidence
                    {
                        Name = inst,
                        SourceFile = rel,
                        Line = lineNo,
                        ModuleName = RegisterTimerModuleMap.ResolveModuleForInstance(inst) ?? module,
                        TypeDefName = GuessTypedef(inst, fileTypedefs)
                    });
                    if (GuessTypedef(inst, fileTypedefs) is { } td)
                        instanceToTd.TryAdd(inst, td);
                }

                foreach (Match m in MemberAccess.Matches(line))
                    AddMember(members, module, fileTypedefs, rel, lineNo, m.Groups[1].Value);

                foreach (Match m in ParenMemberAccess.Matches(line))
                    AddMember(members, module, fileTypedefs, rel, lineNo, m.Groups[1].Value);

                foreach (Match m in MacroPattern.Matches(line))
                {
                    var name = m.Groups[1].Value;
                    macros.Add(new LlMacroEvidence
                    {
                        MacroName = name,
                        MacroKind = ClassifyMacroKind(name),
                        SourceFile = rel,
                        Line = lineNo,
                        ModuleName = module
                    });
                }
            }
        }

        return new RegisterLlScanResult
        {
            Instances = DeduplicateInstances(instances),
            RegisterMembers = DeduplicateMembers(members),
            MacroReferences = DeduplicateMacros(macros),
            InstanceToTypeDef = instanceToTd,
            ModuleToPrimaryTypeDef = moduleToTd
        };
    }

    private static void AddMember(List<LlRegisterMemberEvidence> list, string module, List<string> typedefs, string file, int line, string member)
    {
        var td = typedefs.FirstOrDefault() ?? $"{module}_TypeDef";
        list.Add(new LlRegisterMemberEvidence
        {
            StructName = td,
            MemberName = member,
            SourceFile = file,
            Line = line,
            ModuleName = module
        });
    }

    private static string? DiscoverFamilyId(string llRoot)
    {
        if (!Directory.Exists(llRoot)) return null;
        try
        {
            return Directory.EnumerateFiles(llRoot, "tae32*_ll_*.h", SearchOption.TopDirectoryOnly)
                .Select(SdkSeriesLayout.TryFamilyIdFromLlHeader)
                .FirstOrDefault(id => !string.IsNullOrWhiteSpace(id));
        }
        catch
        {
            return null;
        }
    }

    private static string ModuleFromHeader(string fileName)
        => SdkSeriesLayout.ModuleFromLlHeader(fileName) ?? Path.GetFileNameWithoutExtension(fileName).ToUpperInvariant();

    private static string? GuessTypedef(string instance, IReadOnlyList<string> typedefs)
    {
        if (instance.StartsWith("GPIO", StringComparison.Ordinal))
            return typedefs.FirstOrDefault(t => t.Contains("GPIO", StringComparison.Ordinal)) ?? "GPIO_TypeDef";
        if (instance.StartsWith("TMR", StringComparison.Ordinal))
            return typedefs.FirstOrDefault(t => t.Contains("TMR", StringComparison.OrdinalIgnoreCase));
        var letters = new string(instance.TakeWhile(char.IsLetter).ToArray());
        return typedefs.FirstOrDefault(t => t.StartsWith(letters, StringComparison.OrdinalIgnoreCase))
               ?? typedefs.FirstOrDefault();
    }

    private static string ClassifyMacroKind(string name)
    {
        if (name.EndsWith("_Pos", StringComparison.Ordinal)) return "Pos";
        if (name.EndsWith("_Msk", StringComparison.Ordinal)) return "Msk";
        if (name.EndsWith("_Shift", StringComparison.Ordinal)) return "Shift";
        if (name.EndsWith("_BIT", StringComparison.Ordinal)) return "Bit";
        return "Other";
    }

    private static List<LlInstanceEvidence> DeduplicateInstances(List<LlInstanceEvidence> items)
        => items.GroupBy(x => x.Name, StringComparer.Ordinal)
            .Select(g => g.OrderBy(x => x.Line).First())
            .OrderBy(x => x.Name, StringComparer.Ordinal)
            .ToList();

    private static List<LlRegisterMemberEvidence> DeduplicateMembers(List<LlRegisterMemberEvidence> items)
        => items.GroupBy(x => (x.StructName, x.MemberName), TupleEqualityComparer.Instance)
            .Select(g => g.OrderBy(x => x.Line).First())
            .OrderBy(x => x.StructName).ThenBy(x => x.MemberName)
            .ToList();

    private static List<LlMacroEvidence> DeduplicateMacros(List<LlMacroEvidence> items)
        => items.GroupBy(x => (x.MacroName, x.SourceFile, x.Line))
            .Select(g => g.First())
            .OrderBy(x => x.MacroName, StringComparer.Ordinal)
            .ToList();

    private sealed class TupleEqualityComparer : IEqualityComparer<(string, string)>
    {
        public static readonly TupleEqualityComparer Instance = new();
        public bool Equals((string, string) x, (string, string) y)
            => string.Equals(x.Item1, y.Item1, StringComparison.Ordinal)
               && string.Equals(x.Item2, y.Item2, StringComparison.Ordinal);
        public int GetHashCode((string, string) obj)
            => HashCode.Combine(obj.Item1, obj.Item2);
    }
}
