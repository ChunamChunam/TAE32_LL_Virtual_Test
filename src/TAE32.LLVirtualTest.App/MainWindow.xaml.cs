using System.Windows;
using TAE32.LLVirtualTest.App.ViewModels;

namespace TAE32.LLVirtualTest.App;

public partial class MainWindow : Window
{
    private readonly MainViewModel _viewModel;

    public MainWindow(MainViewModel viewModel)
    {
        InitializeComponent();
        _viewModel = viewModel;
        DataContext = _viewModel;
        Loaded += OnLoaded;
    }

    private async void OnLoaded(object sender, RoutedEventArgs e)
    {
        var summary = Tag as string;
        await _viewModel.InitializeAsync(summary);
    }
}
