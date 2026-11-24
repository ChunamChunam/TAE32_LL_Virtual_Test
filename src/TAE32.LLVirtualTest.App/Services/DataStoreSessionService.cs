namespace TAE32.LLVirtualTest.App.Services;

/// <summary>Signals that the SQLite file was replaced or fully cleared so open pages reload from DB.</summary>
public sealed class DataStoreSessionService
{
    public Func<Task>? ReloadAllPagesAsync { get; set; }

    public Task NotifyStoreChangedAsync() =>
        ReloadAllPagesAsync?.Invoke() ?? Task.CompletedTask;
}