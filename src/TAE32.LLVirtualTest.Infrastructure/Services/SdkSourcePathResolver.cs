namespace TAE32.LLVirtualTest.Infrastructure.Services;

/// <summary>
/// LL 头文件在库中多为相对路径（相对仓库根/SDKContent）；解析为绝对路径供打开/编译。
/// </summary>
public static class SdkSourcePathResolver
{
    public static bool TryResolve(string? sourceFile, string? sdkRootPath, out string absolutePath)
    {
        absolutePath = string.Empty;
        if (string.IsNullOrWhiteSpace(sourceFile)) return false;

        var normalized = sourceFile.Replace('/', Path.DirectorySeparatorChar).Trim();
        foreach (var candidate in BuildCandidates(normalized, sourceFile, sdkRootPath))
        {
            if (string.IsNullOrWhiteSpace(candidate)) continue;
            try
            {
                var full = Path.GetFullPath(candidate);
                if (File.Exists(full))
                {
                    absolutePath = full;
                    return true;
                }
            }
            catch
            {
                // invalid path segment
            }
        }

        return false;
    }

    private static IEnumerable<string> BuildCandidates(string normalized, string original, string? sdkRootPath)
    {
        if (Path.IsPathRooted(normalized))
            yield return normalized;

        yield return normalized;

        foreach (var root in DiscoverRepoRoots())
            yield return Path.Combine(root, normalized);

        if (!string.IsNullOrWhiteSpace(sdkRootPath))
        {
            var sdkRoot = sdkRootPath.Replace('/', Path.DirectorySeparatorChar).Trim();
            try
            {
                sdkRoot = Path.GetFullPath(sdkRoot);
            }
            catch
            {
                yield break;
            }

            var sdkFolder = Path.GetFileName(sdkRoot.TrimEnd(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar));
            var idx = original.IndexOf(sdkFolder, StringComparison.OrdinalIgnoreCase);
            if (idx >= 0)
            {
                var suffix = original[(idx + sdkFolder.Length)..]
                    .TrimStart('/', '\\')
                    .Replace('/', Path.DirectorySeparatorChar);
                if (suffix.Length > 0)
                    yield return Path.Combine(sdkRoot, suffix);
            }

            // 常见：…/package/SDK/Drivers/…/foo.h
            var sdkSeg = $"{Path.DirectorySeparatorChar}SDK{Path.DirectorySeparatorChar}";
            var segIdx = normalized.IndexOf(sdkSeg, StringComparison.OrdinalIgnoreCase);
            if (segIdx >= 0)
            {
                var fromSdk = normalized[segIdx..].TrimStart(Path.DirectorySeparatorChar);
                yield return Path.Combine(sdkRoot, fromSdk);
            }

            yield return Path.Combine(sdkRoot, Path.GetFileName(normalized));
        }
    }

    private static IEnumerable<string> DiscoverRepoRoots()
    {
        var seen = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        static void TryAdd(string? dir, HashSet<string> set, List<string> list)
        {
            if (string.IsNullOrWhiteSpace(dir)) return;
            try
            {
                dir = Path.GetFullPath(dir);
                if (!set.Add(dir)) return;
                if (Directory.Exists(Path.Combine(dir, "SDKContent"))
                    || Directory.Exists(Path.Combine(dir, "src", "TAE32.LLVirtualTest.App")))
                    list.Add(dir);
            }
            catch { /* ignore */ }
        }

        var list = new List<string>();
        TryAdd(Environment.CurrentDirectory, seen, list);
        TryAdd(AppContext.BaseDirectory, seen, list);

        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 8 && !string.IsNullOrEmpty(dir); i++)
        {
            TryAdd(dir, seen, list);
            dir = Path.GetDirectoryName(dir);
        }

        return list;
    }
}
