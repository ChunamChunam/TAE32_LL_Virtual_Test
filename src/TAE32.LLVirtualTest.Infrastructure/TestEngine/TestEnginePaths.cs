namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

internal static class TestEnginePaths
{
    public static string HostSdkIncludeDirectory()
    {
        // Do not use Assembly.Location — empty under single-file publish (IL3000).
        var roots = new List<string> { AppContext.BaseDirectory };

        foreach (var baseDir in roots)
        {
            foreach (var rel in new[] { "HostSdk", Path.Combine("TestEngine", "HostSdk") })
            {
                var candidate = Path.Combine(baseDir, rel);
                if (Directory.Exists(candidate))
                    return candidate;
            }
        }

        var walk = AppContext.BaseDirectory;
        for (var i = 0; i < 8; i++)
        {
            foreach (var rel in new[] { "HostSdk", Path.Combine("TestEngine", "HostSdk") })
            {
                var candidate = Path.Combine(walk, rel);
                if (Directory.Exists(candidate))
                    return candidate;
            }

            // Infrastructure project source layout (dev): .../src/TAE32.LLVirtualTest.Infrastructure/TestEngine/HostSdk
            var infraHost = Path.Combine(walk, "src", "TAE32.LLVirtualTest.Infrastructure", "TestEngine", "HostSdk");
            if (Directory.Exists(infraHost))
                return infraHost;

            var parent = Path.GetDirectoryName(walk);
            if (string.IsNullOrEmpty(parent) || string.Equals(parent, walk, StringComparison.OrdinalIgnoreCase))
                break;
            walk = parent;
        }

        var fallback = Path.Combine(AppContext.BaseDirectory, "HostSdk");
        var dev = Path.GetFullPath(Path.Combine(
            AppContext.BaseDirectory,
            "..", "..", "..", "TestEngine", "HostSdk"));
        return Directory.Exists(dev) ? dev : fallback;
    }
}
