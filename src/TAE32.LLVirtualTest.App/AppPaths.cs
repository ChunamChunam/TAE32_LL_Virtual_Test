using System.IO;

namespace TAE32.LLVirtualTest.App;

public static class AppPaths
{
    /// <summary>Directory containing the running executable (publish folder or bin output).</summary>
    public static string InstallDirectory => Path.GetFullPath(AppContext.BaseDirectory);

    /// <summary>App-local data: SQLite DB, logs, UI scale, default scan cache (beside the exe).</summary>
    public static string DataDirectory => Path.Combine(InstallDirectory, "data");

    public static string LogDirectory => Path.Combine(DataDirectory, "logs");
    public static string DatabasePath => Path.Combine(DataDirectory, "tae32_ll_virtual_test.db");

    /// <summary>Repo root when SDKContent/ScanResults exist (dev); else install directory.</summary>
    public static string WorkspaceRoot
    {
        get
        {
            var dir = new DirectoryInfo(InstallDirectory);
            while (dir is not null)
            {
                if (Directory.Exists(Path.Combine(dir.FullName, "ScanResults"))
                    && Directory.Exists(Path.Combine(dir.FullName, "SDKContent")))
                {
                    return dir.FullName;
                }
                dir = dir.Parent;
            }
            return InstallDirectory;
        }
    }

    public static string DefaultSdkRoot => Path.Combine(WorkspaceRoot, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
    public static string DefaultScanResults => Path.Combine(WorkspaceRoot, "ScanResults");
}
