using System.Windows.Controls;
using System.Windows.Input;
using TAE32.LLVirtualTest.App.ViewModels.Pages;
using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.App.Views.Pages;

public partial class TestManagementPage : UserControl
{
    public TestManagementPage() => InitializeComponent();

    private void OnCaseDoubleClick(object sender, MouseButtonEventArgs e)
    {
        if (DataContext is TestManagementViewModel vm && sender is ListBox list && list.SelectedItem is LlTestCase c)
            vm.ToggleCaseSelectionCommand.Execute(c);
    }

    private void OnArtifactDoubleClick(object sender, MouseButtonEventArgs e)
    {
        if (DataContext is not TestManagementViewModel vm) return;
        if (sender is DataGrid grid && grid.SelectedItem is TestReportArtifact artifact)
            vm.OpenArtifactCommand.Execute(artifact);
    }
}
