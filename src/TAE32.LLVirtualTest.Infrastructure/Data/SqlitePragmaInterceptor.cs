using System.Data.Common;
using Microsoft.EntityFrameworkCore.Diagnostics;

namespace TAE32.LLVirtualTest.Infrastructure.Data;

/// <summary>
/// Apply SQLite pragmas once per connection open (busy wait + larger page cache).
/// </summary>
internal sealed class SqlitePragmaInterceptor : DbConnectionInterceptor
{
    public override void ConnectionOpened(DbConnection connection, ConnectionEndEventData eventData)
    {
        Apply(connection);
        base.ConnectionOpened(connection, eventData);
    }

    public override async Task ConnectionOpenedAsync(
        DbConnection connection,
        ConnectionEndEventData eventData,
        CancellationToken cancellationToken = default)
    {
        await ApplyAsync(connection, cancellationToken).ConfigureAwait(false);
        await base.ConnectionOpenedAsync(connection, eventData, cancellationToken).ConfigureAwait(false);
    }

    private static void Apply(DbConnection connection)
    {
        using var cmd = connection.CreateCommand();
        cmd.CommandText = "PRAGMA busy_timeout=5000; PRAGMA cache_size=-64000;";
        cmd.ExecuteNonQuery();
    }

    private static async Task ApplyAsync(DbConnection connection, CancellationToken ct)
    {
        await using var cmd = connection.CreateCommand();
        cmd.CommandText = "PRAGMA busy_timeout=5000; PRAGMA cache_size=-64000;";
        await cmd.ExecuteNonQueryAsync(ct).ConfigureAwait(false);
    }
}
