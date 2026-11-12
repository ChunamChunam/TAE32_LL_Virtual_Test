using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class SystemMaintenanceService : ISystemMaintenanceService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly string _databasePath;
    private readonly string _logDirectory;

    public SystemMaintenanceService(
        IDbContextFactory<AppDbContext> dbFactory,
        string databasePath,
        string logDirectory)
    {
        _dbFactory = dbFactory;
        _databasePath = databasePath;
        _logDirectory = logDirectory;
    }

    public Task<string> BackupDatabaseAsync(string? destinationDirectory = null, CancellationToken ct = default)
    {
        if (!File.Exists(_databasePath))
            throw new FileNotFoundException("数据库文件不存在", _databasePath);

        var destDir = string.IsNullOrWhiteSpace(destinationDirectory)
            ? Path.Combine(Path.GetDirectoryName(_databasePath)!, "backups")
            : destinationDirectory!;
        Directory.CreateDirectory(destDir);
        var dest = Path.Combine(destDir, $"tae32_ll_virtual_test_{DateTime.Now:yyyyMMdd_HHmmss}.db");
        File.Copy(_databasePath, dest, overwrite: false);
        return Task.FromResult(dest);
    }

    public Task RestoreDatabaseAsync(string backupFilePath, CancellationToken ct = default)
    {
        if (!File.Exists(backupFilePath))
            throw new FileNotFoundException("备份文件不存在", backupFilePath);
        var dir = Path.GetDirectoryName(_databasePath)!;
        Directory.CreateDirectory(dir);
        // Safety copy of current DB first.
        if (File.Exists(_databasePath))
        {
            var safety = Path.Combine(dir, $"pre_restore_{DateTime.Now:yyyyMMdd_HHmmss}.db");
            File.Copy(_databasePath, safety, overwrite: false);
        }
        File.Copy(backupFilePath, _databasePath, overwrite: true);
        return Task.CompletedTask;
    }

    public Task<int> TrimLogsAsync(TimeSpan olderThan, CancellationToken ct = default)
    {
        if (!Directory.Exists(_logDirectory)) return Task.FromResult(0);
        var cutoff = DateTime.UtcNow - olderThan;
        var n = 0;
        foreach (var file in Directory.EnumerateFiles(_logDirectory, "*.*", SearchOption.AllDirectories))
        {
            try
            {
                if (File.GetLastWriteTimeUtc(file) < cutoff)
                {
                    File.Delete(file);
                    n++;
                }
            }
            catch { /* ignore locked */ }
        }
        return Task.FromResult(n);
    }

    public async Task<string> GetDiagnosticsSummaryAsync(CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var sb = new StringBuilder();
        sb.AppendLine($"ToolVersion={Assembly.GetExecutingAssembly().GetName().Version}");
        sb.AppendLine($"Database={_databasePath} exists={File.Exists(_databasePath)}");
        if (File.Exists(_databasePath))
            sb.AppendLine($"DatabaseSizeBytes={new FileInfo(_databasePath).Length}");
        sb.AppendLine($"LogDirectory={_logDirectory}");
        sb.AppendLine($"Projects={await db.SdkProjects.CountAsync(ct)}");
        sb.AppendLine($"Functions={await db.LlFunctions.CountAsync(ct)}");
        sb.AppendLine($"TestCases={await db.LlTestCases.CountAsync(ct)}");
        sb.AppendLine($"TestRuns={await db.LlTestRuns.CountAsync(ct)}");
        sb.AppendLine($"BatchRuns={await db.TestBatchRuns.CountAsync(ct)}");
        return sb.ToString();
    }
}
