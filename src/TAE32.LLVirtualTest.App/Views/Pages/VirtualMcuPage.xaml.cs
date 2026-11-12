using System.Windows;
using System.Windows.Controls;
using TAE32.LLVirtualTest.App.ViewModels.Pages;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.Views.Pages;

public partial class VirtualMcuPage : UserControl
{
    public VirtualMcuPage() => InitializeComponent();

    private void OnTreeSelected(object sender, RoutedPropertyChangedEventArgs<object> e)
    {
        if (DataContext is VirtualMcuViewModel vm && e.NewValue is VirtualPeripheralTreeNode node)
            vm.SelectedTreeNode = node;
    }
}
