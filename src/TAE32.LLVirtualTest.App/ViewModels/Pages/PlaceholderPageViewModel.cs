using CommunityToolkit.Mvvm.ComponentModel;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class PlaceholderPageViewModel : ObservableObject
{
    [ObservableProperty] private string _title = string.Empty;
    [ObservableProperty] private string _description = string.Empty;
    [ObservableProperty] private string _extensionHint = string.Empty;

    public PlaceholderPageViewModel(string title, string description, string extensionHint)
    {
        Title = title;
        Description = description;
        ExtensionHint = extensionHint;
    }
}
