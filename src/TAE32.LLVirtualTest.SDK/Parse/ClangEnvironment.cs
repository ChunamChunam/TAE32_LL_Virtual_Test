using ClangSharp.Interop;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class ClangEnvironment
{
    private static readonly string[] DeviceHeaderRelPaths =
    [
        "tae32g58xx.h",
        "SDK/Drivers/TAE32G58xx_Device/Inc/tae32g58xx.h",
        "Drivers/TAE32G58xx_Device/Inc/tae32g58xx.h",
        "Device/tae32g58xx.h",
        "Include/tae32g58xx.h"
    ];

    private static readonly string[] ConfHeaderRelPaths =
    [
        "tae32g58xx_ll_conf.h",
        "SDK/ProjectTemplateLL/User/Inc/tae32g58xx_ll_conf.h",
        "Include/tae32g58xx_ll_conf.h"
    ];

    public string LlRoot { get; init; } = string.Empty;
    public string SdkRoot { get; init; } = string.Empty;
    public string BridgeRoot { get; init; } = string.Empty;
    public IReadOnlyList<string> IncludePaths { get; init; } = Array.Empty<string>();
    public IReadOnlyList<string> MissingHeaders { get; init; } = Array.Empty<string>();
    public bool RequiresParseBridge { get; init; }
    public string ClangVersion { get; init; } = string.Empty;

    public static ClangEnvironment Resolve(string sdkRootPath, string bridgeRoot)
    {
        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var llRoot = ResolveLlRoot(sdkRoot) ?? sdkRoot;

        var missing = new List<string>();
        string? deviceHeader = null;
        foreach (var rel in DeviceHeaderRelPaths)
        {
            var hit = FindFile(sdkRoot, rel);
            if (hit is not null) { deviceHeader = hit; break; }
        }
        if (deviceHeader is null) missing.Add("tae32g58xx.h");

        string? confHeader = null;
        foreach (var rel in ConfHeaderRelPaths)
        {
            var hit = FindFile(sdkRoot, rel);
            if (hit is not null) { confHeader = hit; break; }
        }
        if (confHeader is null) missing.Add("tae32g58xx_ll_conf.h");

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
                     "Drivers/CMSIS/Core/Include"
                 })
        {
            var p = Path.Combine(sdkRoot, sub.Replace('/', Path.DirectorySeparatorChar));
            if (Directory.Exists(p) && !includes.Contains(p, StringComparer.OrdinalIgnoreCase))
                includes.Add(p);
        }

        return new ClangEnvironment
        {
            SdkRoot = sdkRoot,
            LlRoot = llRoot,
            BridgeRoot = bridgeRoot,
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
}
