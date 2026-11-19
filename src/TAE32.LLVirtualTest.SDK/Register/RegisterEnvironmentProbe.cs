using TAE32.LLVirtualTest.Core.Sdk;

namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class RegisterEnvironmentProbeResult
{
    public string SdkRoot { get; init; } = string.Empty;
    public string LlRoot { get; init; } = string.Empty;
    public string FamilyId { get; init; } = string.Empty;
    public string ChipModel { get; init; } = string.Empty;
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
    public RegisterEnvironmentProbeResult Probe(string sdkRootPath)
    {
        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var layout = SdkSeriesLayout.Discover(sdkRoot);

        var foundDevice = new List<string>();
        if (layout?.DeviceHeaderPath is not null)
            foundDevice.Add(layout.DeviceHeaderPath);

        var missing = new List<string>();
        if (layout is null)
        {
            missing.Add("tae32*.h (authoritative device header — no series layout discovered)");
            missing.Add("tae32*_chip.h / tae32*_chip_struct.h");
            return new RegisterEnvironmentProbeResult
            {
                SdkRoot = sdkRoot,
                LlRoot = sdkRoot,
                MissingExpected = missing,
                FoundDeviceIncludes = foundDevice,
                FoundRegHeaders = FindRegHeaders(sdkRoot)
            };
        }

        if (layout.DeviceHeaderPath is null)
            missing.Add($"{layout.DeviceHeaderFileName} (authoritative device header)");
        if (layout.ChipHeaderPath is null)
            missing.Add($"{layout.ChipHeaderFileName} / {layout.ChipStructFileName}");

        var llRoot = layout.LlRoot ?? sdkRoot;
        if (layout.LlRoot is null)
            missing.Add($"LL root with {layout.LlHeaderGlob}");

        return new RegisterEnvironmentProbeResult
        {
            SdkRoot = sdkRoot,
            LlRoot = llRoot,
            FamilyId = layout.FamilyId,
            ChipModel = layout.ChipModel,
            AuthoritativeDeviceHeader = layout.DeviceHeaderPath,
            ChipHeader = layout.ChipHeaderPath,
            SvdPath = layout.SvdPath,
            HasAuthoritativeDeviceHeader = layout.DeviceHeaderPath is not null && layout.ChipHeaderPath is not null,
            FoundDeviceIncludes = foundDevice.Distinct(StringComparer.OrdinalIgnoreCase).ToList(),
            FoundRegHeaders = FindRegHeaders(sdkRoot),
            MissingExpected = missing
        };
    }

    private static List<string> FindRegHeaders(string sdkRoot)
    {
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
                // ignore inaccessible dirs
            }
        }

        return regHeaders;
    }

    private static IEnumerable<string> EnumerateSearchDirs(string sdkRoot)
    {
        var dirs = new List<string> { sdkRoot };
        foreach (var sub in new[] { "Include", "Device", "CMSIS", "SVD" })
            dirs.Add(Path.Combine(sdkRoot, sub));

        try
        {
            dirs.AddRange(Directory.EnumerateDirectories(sdkRoot, "Inc", SearchOption.AllDirectories)
                .Where(d => d.Contains("Device", StringComparison.OrdinalIgnoreCase))
                .Take(20));
        }
        catch
        {
            // ignore inaccessible trees
        }

        return dirs;
    }
}
