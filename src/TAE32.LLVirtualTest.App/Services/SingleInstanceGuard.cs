using System.Threading;

namespace TAE32.LLVirtualTest.App.Services;

/// <summary>
/// Ensures only one UI process runs. Secondary instances signal the primary to activate.
/// </summary>
internal sealed class SingleInstanceGuard : IDisposable
{
    private const string MutexName = @"Local\TAE32.LLVirtualTest.App.SingleInstance";
    private const string ActivateEventName = @"Local\TAE32.LLVirtualTest.App.Activate";

    private readonly Mutex _mutex;
    private readonly EventWaitHandle _activateEvent;
    private readonly bool _ownsMutex;
    private CancellationTokenSource? _cts;
    private Thread? _listenThread;

    public bool IsPrimary { get; }

    public SingleInstanceGuard()
    {
        _mutex = new Mutex(false, MutexName);
        try
        {
            _ownsMutex = _mutex.WaitOne(0, false);
        }
        catch (AbandonedMutexException)
        {
            // Previous process crashed while holding the mutex.
            _ownsMutex = true;
        }

        IsPrimary = _ownsMutex;
        _activateEvent = new EventWaitHandle(false, EventResetMode.AutoReset, ActivateEventName);
    }

    public void RequestActivatePrimary() => _activateEvent.Set();

    public void BeginListenForActivate(Action onActivate)
    {
        if (!IsPrimary) return;

        _cts = new CancellationTokenSource();
        var token = _cts.Token;
        _listenThread = new Thread(() =>
        {
            while (!token.IsCancellationRequested)
            {
                if (_activateEvent.WaitOne(400) && !token.IsCancellationRequested)
                {
                    try { onActivate(); }
                    catch { /* ignore activate failures */ }
                }
            }
        })
        {
            IsBackground = true,
            Name = "SingleInstanceActivate"
        };
        _listenThread.Start();
    }

    public void Dispose()
    {
        _cts?.Cancel();
        if (_listenThread is { IsAlive: true } && !_listenThread.Join(1500))
        {
            // Background thread; process exit will tear it down.
        }

        if (_ownsMutex)
        {
            try { _mutex.ReleaseMutex(); }
            catch (ApplicationException) { /* not owned */ }
        }

        _mutex.Dispose();
        _activateEvent.Dispose();
        _cts?.Dispose();
    }
}
