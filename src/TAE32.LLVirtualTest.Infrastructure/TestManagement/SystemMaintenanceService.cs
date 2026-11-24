using System.Data;
using System.Reflection;
using System.Text;
using Microsoft.Data.Sqlite;
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

    public Task RestoreDatabaseAsync(string backupFilePath, CancellationToken ct = default) =>
        Task.Run(() => RestoreDatabaseCore(backupFilePath), ct);

    private void RestoreDatabaseCore(string backupFilePath)
    {
        if (!File.Exists(backupFilePath))
            throw new FileNotFoundException("备份文件不存在", backupFilePath);
        var dir = Path.GetDirectoryName(_databasePath)!;
        Directory.CreateDirectory(dir);

        SqliteConnection.ClearAllPools();

        if (File.Exists(_databasePath))
        {
            var safety = Path.Combine(dir, $"pre_restore_{DateTime.Now:yyyyMMdd_HHmmss}.db");
            File.Copy(_databasePath, safety, overwrite: false);
        }

        File.Copy(backupFilePath, _databasePath, overwrite: true);
        DeleteSqliteSidecarFiles(_databasePath);
        SqliteConnection.ClearAllPools();
    }

    internal static void DeleteSqliteSidecarFiles(string databasePath)
    {
        foreach (var suffix in new[] { "-wal", "-shm", "-journal" })
        {
            var path = databasePath + suffix;
            if (!File.Exists(path)) continue;
            try { File.Delete(path); }
            catch { /* ignore locked sidecars */ }
        }
    }

    public Task<string?> ClearAllDataAsync(CancellationToken ct = default) =>
        Task.Run(async () => await ClearAllDataCoreAsync(ct).ConfigureAwait(false), ct);

    private async Task<string?> ClearAllDataCoreAsync(CancellationToken ct)
    {
        string? safetyPath = null;
        if (File.Exists(_databasePath))
        {
            var dir = Path.GetDirectoryName(_databasePath)!;
            Directory.CreateDirectory(dir);
            safetyPath = Path.Combine(dir, $"pre_clear_{DateTime.Now:yyyyMMdd_HHmmss}.db");
            await CopyDatabaseFileAsync(_databasePath, safetyPath, ct).ConfigureAwait(false);
        }

        // Do not use EF / Cache=Shared here: other pages hold pooled connections and VACUUM would block the UI.
        SqliteConnection.ClearAllPools();
        var cs = new SqliteConnectionStringBuilder
        {
            DataSource = _databasePath,
            Mode = SqliteOpenMode.ReadWriteCreate,
            Cache = SqliteCacheMode.Private,
            Pooling = false,
            DefaultTimeout = 60
        }.ToString();

        await using var conn = new SqliteConnection(cs);
        await conn.OpenAsync(ct).ConfigureAwait(false);
        await ExecuteNonQueryAsync(conn, null, "PRAGMA busy_timeout=60000;", ct).ConfigureAwait(false);

        var tables = await ListUserTablesAsync(conn, ct).ConfigureAwait(false);

        await using (var tx = (SqliteTransaction)await conn.BeginTransactionAsync(ct).ConfigureAwait(false))
        {
            await ExecuteNonQueryAsync(conn, tx, "PRAGMA foreign_keys = OFF;", ct).ConfigureAwait(false);
            foreach (var table in tables)
            {
                if (!IsSafeSqlIdentifier(table)) continue;
                await ExecuteNonQueryAsync(conn, tx, $"DELETE FROM \"{table}\";", ct).ConfigureAwait(false);
            }
            await ExecuteNonQueryAsync(conn, tx, "PRAGMA foreign_keys = ON;", ct).ConfigureAwait(false);
            await tx.CommitAsync(ct).ConfigureAwait(false);
        }

        SqliteConnection.ClearAllPools();
        return safetyPath;
    }

    private static async Task CopyDatabaseFileAsync(string source, string dest, CancellationToken ct)
    {
        await using var src = new FileStream(source, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
        await using var dst = new FileStream(dest, FileMode.CreateNew, FileAccess.Write, FileShare.None);
        await src.CopyToAsync(dst, ct).ConfigureAwait(false);
    }

    private static bool IsSafeSqlIdentifier(string name) =>
        !string.IsNullOrEmpty(name) && name.All(static c => char.IsAsciiLetterOrDigit(c) || c == '_');

    private static async Task ExecuteNonQueryAsync(
        SqliteConnection conn,
        SqliteTransaction? tx,
        string sql,
        CancellationToken ct)
    {
        await using var cmd = conn.CreateCommand();
        cmd.Transaction = tx;
        cmd.CommandText = sql;
        await cmd.ExecuteNonQueryAsync(ct).ConfigureAwait(false);
    }

    private static async Task<IReadOnlyList<string>> ListUserTablesAsync(SqliteConnection conn, CancellationToken ct)
    {
        var list = new List<string>();
        await using var cmd = conn.CreateCommand();
        cmd.CommandText =
            "SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%' AND name <> '__EFMigrationsHistory'";
        await using var reader = await cmd.ExecuteReaderAsync(ct).ConfigureAwait(false);
        while (await reader.ReadAsync(ct).ConfigureAwait(false))
            list.Add(reader.GetString(0));
        return list;
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
