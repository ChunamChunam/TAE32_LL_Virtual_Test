using System.Text.RegularExpressions;

namespace TAE32.LLVirtualTest.Core.Sdk;

/// <summary>
/// Discovers Tai-Action device/LL layout from the selected SDK tree without hardcoding a chip series.
/// Family id is the lowercase stem used by headers, e.g. <c>tae32g58xx</c> / <c>tae32f561x</c>.
/// </summary>
public sealed class SdkSeriesLayout
{
    private static readonly Regex ChipHeaderName = new(
        @"^(?<fam>tae32[a-z0-9]+)_chip(?:_struct)?\.h$",
        RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex DeviceHeaderName = new(
        @"^(?<fam>tae32[a-z0-9]+)\.h$",
        RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex LlModuleHeaderName = new(
        @"^(?<fam>tae32[a-z0-9]+)_ll_(?!def$)(?<mod>[a-z0-9]+)\.h$",
        RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex LlAnyHeaderName = new(
        @"^(?<fam>tae32[a-z0-9]+)_ll(?:_[a-z0-9]+)?\.h$",
        RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.CultureInvariant);

    public string FamilyId { get; init; } = string.Empty;
    public string ChipModel { get; init; } = string.Empty;
    public string? DeviceHeaderPath { get; init; }
    public string? ChipHeaderPath { get; init; }
    public string? LlConfHeaderPath { get; init; }
    public string? LlRoot { get; init; }
    public string? SvdPath { get; init; }

    public string DeviceHeaderFileName => FamilyId + ".h";
    public string ChipHeaderFileName => FamilyId + "_chip.h";
    public string ChipStructFileName => FamilyId + "_chip_struct.h";
    public string LlUmbrellaFileName => FamilyId + "_ll.h";
    public string LlDefFileName => FamilyId + "_ll_def.h";
    public string LlConfFileName => FamilyId + "_ll_conf.h";
    public string LlHeaderGlob => FamilyId + "_ll_*.h";

    public static SdkSeriesLayout? Discover(string sdkRootPath)
    {
        if (string.IsNullOrWhiteSpace(sdkRootPath) || !Directory.Exists(sdkRootPath))
            return null;

        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var candidates = new Dictionary<string, Candidate>(StringComparer.OrdinalIgnoreCase);

        foreach (var chipPath in SafeEnumerateFiles(sdkRoot, "tae32*_chip*.h"))
        {
            var name = Path.GetFileName(chipPath);
            var m = ChipHeaderName.Match(name);
            if (!m.Success) continue;
            var fam = m.Groups["fam"].Value.ToLowerInvariant();
            var c = GetOrAdd(candidates, fam);
            var isStruct = name.Contains("_chip_struct", StringComparison.OrdinalIgnoreCase);
            if (isStruct)
                c.ChipStructPath ??= chipPath;
            else
                c.ChipHeaderPath ??= chipPath;

            var dir = Path.GetDirectoryName(chipPath)!;
            var device = Path.Combine(dir, fam + ".h");
            if (File.Exists(device) && IsAuthoritativeHeader(device))
                c.DeviceHeaderPath ??= device;
        }

        foreach (var devicePath in SafeEnumerateFiles(sdkRoot, "tae32*.h"))
        {
            var name = Path.GetFileName(devicePath);
            var m = DeviceHeaderName.Match(name);
            if (!m.Success) continue;
            if (name.Contains("_ll", StringComparison.OrdinalIgnoreCase)
                || name.Contains("_chip", StringComparison.OrdinalIgnoreCase)
                || name.Contains("_hal", StringComparison.OrdinalIgnoreCase)
                || name.StartsWith("system_", StringComparison.OrdinalIgnoreCase))
                continue;
            if (!IsAuthoritativeHeader(devicePath)) continue;

            var fam = m.Groups["fam"].Value.ToLowerInvariant();
            var c = GetOrAdd(candidates, fam);
            c.DeviceHeaderPath ??= devicePath;
            var dir = Path.GetDirectoryName(devicePath)!;
            var chip = Path.Combine(dir, fam + "_chip.h");
            var chipStruct = Path.Combine(dir, fam + "_chip_struct.h");
            if (File.Exists(chip)) c.ChipHeaderPath ??= chip;
            if (File.Exists(chipStruct)) c.ChipStructPath ??= chipStruct;
        }

        foreach (var llFile in SafeEnumerateFiles(sdkRoot, "tae32*_ll_*.h"))
        {
            var m = LlModuleHeaderName.Match(Path.GetFileName(llFile));
            if (!m.Success) continue;
            var fam = m.Groups["fam"].Value.ToLowerInvariant();
            var c = GetOrAdd(candidates, fam);
            c.LlRoot ??= Path.GetDirectoryName(llFile);
            c.LlModuleCount++;
        }

        foreach (var conf in SafeEnumerateFiles(sdkRoot, "tae32*_ll_conf.h"))
        {
            var m = Regex.Match(
                Path.GetFileName(conf),
                @"^(?<fam>tae32[a-z0-9]+)_ll_conf\.h$",
                RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);
            if (!m.Success) continue;
            var fam = m.Groups["fam"].Value.ToLowerInvariant();
            var c = GetOrAdd(candidates, fam);
            c.LlConfPath ??= conf;
        }

        if (candidates.Count == 0)
            return null;

        var best = candidates.Values
            .OrderByDescending(Score)
            .ThenByDescending(c => c.LlModuleCount)
            .ThenBy(c => c.FamilyId, StringComparer.OrdinalIgnoreCase)
            .First();

        if (string.IsNullOrWhiteSpace(best.FamilyId))
            return null;

        var chipHeader = best.ChipHeaderPath ?? best.ChipStructPath;
        var svd = SafeEnumerateFiles(sdkRoot, best.FamilyId.ToUpperInvariant() + ".svd").FirstOrDefault()
                  ?? SafeEnumerateFiles(sdkRoot, "*.svd").FirstOrDefault();

        return new SdkSeriesLayout
        {
            FamilyId = best.FamilyId,
            ChipModel = ToChipModel(best.FamilyId),
            DeviceHeaderPath = best.DeviceHeaderPath,
            ChipHeaderPath = chipHeader,
            LlConfHeaderPath = best.LlConfPath,
            LlRoot = best.LlRoot ?? ResolveLlRootFallback(sdkRoot, best.FamilyId),
            SvdPath = svd
        };
    }

    public static IReadOnlyList<string> EnumerateLlModuleHeaders(string llRoot, string familyId)
    {
        if (!Directory.Exists(llRoot) || string.IsNullOrWhiteSpace(familyId))
            return Array.Empty<string>();

        var umbrella = familyId + "_ll.h";
        var def = familyId + "_ll_def.h";
        return Directory.GetFiles(llRoot, familyId + "_ll_*.h", SearchOption.TopDirectoryOnly)
            .Where(p =>
            {
                var name = Path.GetFileName(p);
                return !name.Equals(umbrella, StringComparison.OrdinalIgnoreCase)
                       && !name.Equals(def, StringComparison.OrdinalIgnoreCase);
            })
            .OrderBy(p => p, StringComparer.OrdinalIgnoreCase)
            .ToList();
    }

    public static string? ModuleFromLlHeader(string fileName, string? familyId = null)
    {
        var name = Path.GetFileName(fileName);
        if (!string.IsNullOrWhiteSpace(familyId))
        {
            var prefix = familyId + "_ll_";
            const string suffix = ".h";
            if (name.StartsWith(prefix, StringComparison.OrdinalIgnoreCase)
                && name.EndsWith(suffix, StringComparison.OrdinalIgnoreCase))
                return name[prefix.Length..^suffix.Length].ToUpperInvariant();
        }

        var m = LlModuleHeaderName.Match(name);
        if (m.Success)
            return m.Groups["mod"].Value.ToUpperInvariant();
        return Path.GetFileNameWithoutExtension(name).ToUpperInvariant();
    }

    public static bool IsLlUmbrellaOrDef(string fileName, string familyId)
    {
        var name = Path.GetFileName(fileName);
        return name.Equals(familyId + "_ll.h", StringComparison.OrdinalIgnoreCase)
               || name.Equals(familyId + "_ll_def.h", StringComparison.OrdinalIgnoreCase);
    }

    public static string? TryFamilyIdFromLlHeader(string fileName)
    {
        var m = LlAnyHeaderName.Match(Path.GetFileName(fileName));
        return m.Success ? m.Groups["fam"].Value.ToLowerInvariant() : null;
    }

    public static bool IsAuthoritativeHeader(string path)
    {
        try
        {
            using var reader = new StreamReader(path);
            for (var i = 0; i < 12 && !reader.EndOfStream; i++)
            {
                var line = reader.ReadLine() ?? string.Empty;
                if (line.Contains("PARSE BRIDGE", StringComparison.OrdinalIgnoreCase))
                    return false;
            }
            return true;
        }
        catch
        {
            return false;
        }
    }

    private static string ToChipModel(string familyId)
    {
        // Preserve established G58 series spelling used by baseline / DB.
        if (familyId.Equals("tae32g58xx", StringComparison.OrdinalIgnoreCase))
            return "TAE32G58xx";
        if (familyId.Length <= 5)
            return familyId.ToUpperInvariant();
        // tae32f561x → TAE32F561x (keep trailing letter case like vendor folders)
        var body = familyId[5..]; // after "tae32"
        return "TAE32" + char.ToUpperInvariant(body[0]) + body[1..];
    }

    private static int Score(Candidate c)
    {
        var score = 0;
        if (c.DeviceHeaderPath is not null) score += 100;
        if (c.ChipHeaderPath is not null) score += 40;
        if (c.ChipStructPath is not null) score += 20;
        if (c.LlRoot is not null) score += 30;
        score += Math.Min(c.LlModuleCount, 50);
        if (c.LlConfPath is not null) score += 10;
        if (c.DeviceHeaderPath is not null
            && c.DeviceHeaderPath.Contains("Device", StringComparison.OrdinalIgnoreCase))
            score += 15;
        return score;
    }

    private static string? ResolveLlRootFallback(string sdkRoot, string familyId)
    {
        var direct = Path.Combine(sdkRoot, "LL");
        if (Directory.Exists(direct)
            && Directory.EnumerateFiles(direct, familyId + "_ll_*.h").Any())
            return direct;

        try
        {
            return Directory.EnumerateDirectories(sdkRoot, "LL", SearchOption.AllDirectories)
                .FirstOrDefault(d => Directory.EnumerateFiles(d, familyId + "_ll_*.h").Any());
        }
        catch
        {
            return null;
        }
    }

    private static Candidate GetOrAdd(Dictionary<string, Candidate> map, string familyId)
    {
        if (!map.TryGetValue(familyId, out var c))
        {
            c = new Candidate { FamilyId = familyId };
            map[familyId] = c;
        }
        return c;
    }

    private static IEnumerable<string> SafeEnumerateFiles(string root, string pattern)
    {
        try
        {
            return Directory.EnumerateFiles(root, pattern, SearchOption.AllDirectories)
                .Where(p =>
                    !p.Contains($"{Path.DirectorySeparatorChar}obj{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase)
                    && !p.Contains($"{Path.DirectorySeparatorChar}bin{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase)
                    && !p.Contains("parse_bridge", StringComparison.OrdinalIgnoreCase))
                .Take(200);
        }
        catch
        {
            return Array.Empty<string>();
        }
    }

    private sealed class Candidate
    {
        public string FamilyId { get; init; } = string.Empty;
        public string? DeviceHeaderPath { get; set; }
        public string? ChipHeaderPath { get; set; }
        public string? ChipStructPath { get; set; }
        public string? LlRoot { get; set; }
        public string? LlConfPath { get; set; }
        public int LlModuleCount { get; set; }
    }
}
