namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class RegisterEnvironmentProbeResult
{
    public string SdkRoot { get; init; } = string.Empty;
    public string LlRoot { get; init; } = string.Empty;
    public string? AuthoritativeDeviceHeader { get; init; }
    public string? ChipHeader { get; init; }
    public string? SvdPath { get; init; }
    public bool HasAuthoritativeDeviceHeader { get; init; }
    public IReadOnlyList<string> FoundDeviceIncludes { get; init; } = Array.Empty<string>();
    public IReadOnlyList<string> FoundRegHeaders { get; init; } = Array.Empty<string>();
    public IReadOnlyList<string> MissingExpected { get; init; } = Array.Empty<string>();
}

public sealed class RegisterEnvironmentProbe
{
    private static readonly string[] DeviceHeaderRelPaths =
    [
        "tae32g58xx.h",
        "Inc/tae32g58xx.h",
        "Include/tae32g58xx.h",
        "Device/tae32g58xx.h",
        "SDK/Drivers/TAE32G58xx_Device/Inc/tae32g58xx.h",
        "Drivers/TAE32G58xx_Device/Inc/tae32g58xx.h",
        "CMSIS/Device/Tai-Action/TAE32G58xx/Include/tae32g58xx.h"
    ];

    public RegisterEnvironmentProbeResult Probe(string sdkRootPath)
    {
        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var llRoot = ResolveLlRoot(sdkRoot) ?? sdkRoot;

        var foundDevice = new List<string>();
        string? authoritative = null;
        foreach (var rel in DeviceHeaderRelPaths)
        {
            var full = FindFile(sdkRoot, rel);
            if (full is null) continue;
            foundDevice.Add(full);
            if (authoritative is null && IsAuthoritativeHeader(full))
                authoritative = full;
        }

        // Deep fallback: search for tae32g58xx.h under package (skip Parse Bridge temps).
        if (authoritative is null)
        {
            foreach (var hit in SafeEnumerateFiles(sdkRoot, "tae32g58xx.h"))
            {
                if (!IsAuthoritativeHeader(hit)) continue;
                foundDevice.Add(hit);
                authoritative = hit;
                break;
            }
        }

        string? chipHeader = null;
        if (authoritative is not null)
        {
            var dir = Path.GetDirectoryName(authoritative)!;
            var chip = Path.Combine(dir, "tae32g58xx_chip.h");
            var chipStruct = Path.Combine(dir, "tae32g58xx_chip_struct.h");
            // Default build path uses chip.h (REG_BIT_VERSION off). Prefer it when present.
            if (File.Exists(chip)) chipHeader = chip;
            else if (File.Exists(chipStruct)) chipHeader = chipStruct;
        }

        string? svd = SafeEnumerateFiles(sdkRoot, "TAE32G58xx.svd").FirstOrDefault()
                      ?? SafeEnumerateFiles(sdkRoot, "*.svd").FirstOrDefault();

        var regHeaders = new List<string>();
        foreach (var dir in EnumerateSearchDirs(sdkRoot))
        {
            if (!Directory.Exists(dir)) continue;
            try
            {
                foreach (var f in Directory.EnumerateFiles(dir, "*reg*.h", SearchOption.TopDirectoryOnly))
                {
                    if (!regHeaders.Contains(f, StringComparer.OrdinalIgnoreCase))
                        regHeaders.Add(f);
                }
            }
            catch
            {
                // ignore
            }
        }

        var missing = new List<string>();
        if (authoritative is null)
            missing.Add("tae32g58xx.h (authoritative device header)");
        if (chipHeader is null)
            missing.Add("tae32g58xx_chip.h / tae32g58xx_chip_struct.h");

        return new RegisterEnvironmentProbeResult
        {
            SdkRoot = sdkRoot,
            LlRoot = llRoot,
            AuthoritativeDeviceHeader = authoritative,
            ChipHeader = chipHeader,
            SvdPath = svd,
            HasAuthoritativeDeviceHeader = authoritative is not null && chipHeader is not null,
            FoundDeviceIncludes = foundDevice.Distinct(StringComparer.OrdinalIgnoreCase).ToList(),
            FoundRegHeaders = regHeaders,
            MissingExpected = missing
        };
    }

    private static string? ResolveLlRoot(string sdkRoot)
    {
        var direct = Path.Combine(sdkRoot, "LL");
        if (Directory.Exists(direct) && Directory.EnumerateFiles(direct, "tae32g58xx_ll_*.h").Any())
            return direct;

        var nested = Path.Combine(sdkRoot, "SDK", "Drivers", "TAE32G58xx_Driver", "LL");
        if (Directory.Exists(nested))
            return nested;

        try
        {
            return Directory.EnumerateDirectories(sdkRoot, "LL", SearchOption.AllDirectories)
                .FirstOrDefault(d => Directory.EnumerateFiles(d, "tae32g58xx_ll_*.h").Any());
        }
        catch
        {
            return null;
        }
    }

    private static bool IsAuthoritativeHeader(string path)
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

    private static IEnumerable<string> EnumerateSearchDirs(string sdkRoot)
    {
        yield return sdkRoot;
        foreach (var sub in new[]
                 {
                     "SDK/Drivers/TAE32G58xx_Device/Inc",
                     "Drivers/TAE32G58xx_Device/Inc",
                     "Include", "Device", "CMSIS", "SVD"
                 })
        {
            yield return Path.Combine(sdkRoot, sub.Replace('/', Path.DirectorySeparatorChar));
        }
    }

    private static string? FindFile(string start, string relative)
    {
        var dir = start;
        for (var i = 0; i < 4 && !string.IsNullOrEmpty(dir); i++)
        {
            var full = Path.Combine(dir, relative.Replace('/', Path.DirectorySeparatorChar));
            if (File.Exists(full)) return full;
            dir = Directory.GetParent(dir)?.FullName;
        }
        return null;
    }

    private static IEnumerable<string> SafeEnumerateFiles(string root, string pattern)
    {
        try
        {
            return Directory.EnumerateFiles(root, pattern, SearchOption.AllDirectories)
                .Where(p => !p.Contains($"{Path.DirectorySeparatorChar}obj{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase))
                .Take(20);
        }
        catch
        {
            return Array.Empty<string>();
        }
    }
}
