namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

internal static class TestEnginePaths
{
    public static string HostSdkIncludeDirectory()
    {
        var roots = new List<string> { AppContext.BaseDirectory };
        var loc = typeof(TestEnginePaths).Assembly.Location;
        if (!string.IsNullOrEmpty(loc))
        {
            var asmDir = Path.GetDirectoryName(loc);
            if (!string.IsNullOrEmpty(asmDir))
                roots.Add(asmDir);
        }

        foreach (var baseDir in roots.Distinct(StringComparer.OrdinalIgnoreCase))
        {
            foreach (var rel in new[] { "HostSdk", Path.Combine("TestEngine", "HostSdk") })
            {
                var candidate = Path.Combine(baseDir, rel);
                if (Directory.Exists(candidate))
                    return candidate;
            }
        }

        var walk = roots[0];
        for (var i = 0; i < 6; i++)
        {
            foreach (var rel in new[] { "HostSdk", Path.Combine("TestEngine", "HostSdk") })
            {
                var candidate = Path.Combine(walk, rel);
                if (Directory.Exists(candidate))
                    return candidate;
            }

            walk = Path.GetDirectoryName(walk) ?? walk;
        }

        var fallback = Path.Combine(AppContext.BaseDirectory, "HostSdk");

        // Development tree (TestEngine/HostSdk beside source)
        var dev = Path.GetFullPath(Path.Combine(
            AppContext.BaseDirectory,
            "..", "..", "..", "TestEngine", "HostSdk"));
        return Directory.Exists(dev) ? dev : fallback;
    }
}
