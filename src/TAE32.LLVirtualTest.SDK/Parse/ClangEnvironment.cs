using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Sdk;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class ClangEnvironment
{
    public string LlRoot { get; init; } = string.Empty;
    public string SdkRoot { get; init; } = string.Empty;
    public string BridgeRoot { get; init; } = string.Empty;
    public string FamilyId { get; init; } = string.Empty;
    public string ChipModel { get; init; } = string.Empty;
    public string DeviceHeaderFileName { get; init; } = string.Empty;
    public string LlConfFileName { get; init; } = string.Empty;
    public IReadOnlyList<string> IncludePaths { get; init; } = Array.Empty<string>();
    public IReadOnlyList<string> MissingHeaders { get; init; } = Array.Empty<string>();
    public bool RequiresParseBridge { get; init; }
    public string ClangVersion { get; init; } = string.Empty;

    public static ClangEnvironment Resolve(string sdkRootPath, string bridgeRoot)
    {
        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var layout = SdkSeriesLayout.Discover(sdkRoot);
        var familyId = layout?.FamilyId ?? Core.Sdk.SdkSeriesLayout.FallbackFamilyId;
        var llRoot = layout?.LlRoot ?? sdkRoot;

        var missing = new List<string>();
        var deviceHeader = layout?.DeviceHeaderPath;
        if (deviceHeader is null)
            missing.Add(familyId + ".h");

        var confHeader = layout?.LlConfHeaderPath;
        if (confHeader is null)
            missing.Add(familyId + "_ll_conf.h");

        // Prefer real device headers; only require bridge when device header missing.
        var requiresBridge = deviceHeader is null;

        Directory.CreateDirectory(bridgeRoot);
        var includes = new List<string> { llRoot };
        if (deviceHeader is not null)
        {
            var inc = Path.GetDirectoryName(deviceHeader)!;
            if (!includes.Contains(inc, StringComparer.OrdinalIgnoreCase))
                includes.Add(inc);
        }
        if (confHeader is not null)
        {
            var inc = Path.GetDirectoryName(confHeader)!;
            if (!includes.Contains(inc, StringComparer.OrdinalIgnoreCase))
                includes.Add(inc);
        }
        // Always keep bridge last as fallback for missing conf stubs if still needed.
        includes.Add(bridgeRoot);

        foreach (var sub in new[]
                 {
                     "SDK/Drivers/CMSISv5/Core/Include",
                     "SDK/Drivers/CMSISv6/Core/Include",
                     "Drivers/CMSIS/Core/Include",
                     "Drivers/CMSISv5/Core/Include",
                     "Drivers/CMSISv6/Core/Include"
                 })
        {
            var p = Path.Combine(sdkRoot, sub.Replace('/', Path.DirectorySeparatorChar));
            if (Directory.Exists(p) && !includes.Contains(p, StringComparer.OrdinalIgnoreCase))
                includes.Add(p);
        }

        // Also pick up any CMSIS Core Include under the tree.
        try
        {
            foreach (var cmsis in Directory.EnumerateDirectories(sdkRoot, "Include", SearchOption.AllDirectories)
                         .Where(d => d.Contains("CMSIS", StringComparison.OrdinalIgnoreCase))
                         .Take(8))
            {
                if (!includes.Contains(cmsis, StringComparer.OrdinalIgnoreCase))
                    includes.Add(cmsis);
            }
        }
        catch
        {
            // ignore
        }

        return new ClangEnvironment
        {
            SdkRoot = sdkRoot,
            LlRoot = llRoot,
            BridgeRoot = bridgeRoot,
            FamilyId = familyId,
            ChipModel = layout?.ChipModel ?? familyId.ToUpperInvariant(),
            DeviceHeaderFileName = familyId + ".h",
            LlConfFileName = familyId + "_ll_conf.h",
            IncludePaths = includes,
            MissingHeaders = missing.Distinct(StringComparer.OrdinalIgnoreCase).ToList(),
            RequiresParseBridge = requiresBridge,
            ClangVersion = TryGetClangVersion()
        };
    }

    public string[] BuildClangArgs()
    {
        var args = new List<string>
        {
            "-x", "c",
            "-std=c11",
            "-fparse-all-comments",
            "-D__GNUC__=1",
            "-D__STDC__=1",
            "-D__STDC_VERSION__=201112L",
            "-Wno-everything",
            "-fno-delayed-template-parsing"
        };
        foreach (var inc in IncludePaths)
            args.Add("-I" + inc);
        return args.ToArray();
    }

    private static string TryGetClangVersion()
    {
        try
        {
            return clang.getClangVersion().ToString();
        }
        catch
        {
            return "libclang (unknown)";
        }
    }
}
