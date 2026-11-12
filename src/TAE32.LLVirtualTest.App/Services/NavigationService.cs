using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.App.Services;

public sealed class NavigationService
{
    public event Action<NavigationItem>? Navigated;

    public NavigationItem Current { get; private set; } = NavigationItem.Dashboard;

    public void Navigate(NavigationItem item)
    {
        Current = item;
        Navigated?.Invoke(item);
    }
}
