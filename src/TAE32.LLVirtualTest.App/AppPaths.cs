using System.IO;

namespace TAE32.LLVirtualTest.App;

public static class AppPaths
{
    public static string WorkspaceRoot
    {
        get
        {
            // Prefer repo root when running from src/.../bin/...
            var dir = new DirectoryInfo(AppContext.BaseDirectory);
            while (dir is not null)
            {
                if (Directory.Exists(Path.Combine(dir.FullName, "ScanResults"))
                    && Directory.Exists(Path.Combine(dir.FullName, "SDKContent")))
                {
                    return dir.FullName;
                }
                dir = dir.Parent;
            }
            return Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", ".."));
        }
    }

    public static string DataDirectory => Path.Combine(WorkspaceRoot, "data");
    public static string LogDirectory => Path.Combine(DataDirectory, "logs");
    public static string DatabasePath => Path.Combine(DataDirectory, "tae32_ll_virtual_test.db");
    public static string DefaultSdkRoot => Path.Combine(WorkspaceRoot, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
    public static string DefaultScanResults => Path.Combine(WorkspaceRoot, "ScanResults");
}
