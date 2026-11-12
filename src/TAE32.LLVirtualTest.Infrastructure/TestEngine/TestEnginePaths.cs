namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

internal static class TestEnginePaths
{
    public static string HostSdkIncludeDirectory()
    {
        var baseDir = Path.GetDirectoryName(typeof(TestEnginePaths).Assembly.Location) ?? AppContext.BaseDirectory;
        var shipped = Path.Combine(baseDir, "HostSdk");
        if (Directory.Exists(shipped))
            return shipped;

        // dotnet run from project output may nest DLLs; walk up to find HostSdk next to Infrastructure.dll
        for (var i = 0; i < 6; i++)
        {
            var candidate = Path.Combine(baseDir, "HostSdk");
            if (Directory.Exists(candidate))
                return candidate;
            baseDir = Path.GetDirectoryName(baseDir) ?? baseDir;
        }

        // Development tree (TestEngine/HostSdk beside source)
        var dev = Path.GetFullPath(Path.Combine(
            AppContext.BaseDirectory,
            "..", "..", "..", "TestEngine", "HostSdk"));
        return Directory.Exists(dev) ? dev : shipped;
    }
}
