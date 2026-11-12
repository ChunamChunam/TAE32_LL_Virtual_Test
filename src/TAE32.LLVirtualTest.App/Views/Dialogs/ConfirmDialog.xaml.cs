using System.Windows;

namespace TAE32.LLVirtualTest.App.Views.Dialogs;

public partial class ConfirmDialog : Window
{
    public ConfirmDialog()
    {
        InitializeComponent();
    }

    public static bool Show(
        string title,
        string message,
        string confirmLabel = "确定",
        string cancelLabel = "取消",
        bool dangerConfirm = true,
        Window? owner = null)
    {
        var dlg = new ConfirmDialog
        {
            Owner = owner ?? Application.Current.MainWindow as Window
        };
        dlg.TitleText.Text = title;
        dlg.MessageText.Text = message;
        dlg.ConfirmButton.Content = confirmLabel;
        dlg.CancelButton.Content = cancelLabel;
        if (!dangerConfirm)
            dlg.ConfirmButton.Background = Application.Current.TryFindResource("BrushAccent") as System.Windows.Media.Brush
                                           ?? dlg.ConfirmButton.Background;
        return dlg.ShowDialog() == true;
    }

    private void ConfirmButton_OnClick(object sender, RoutedEventArgs e)
    {
        DialogResult = true;
        Close();
    }

    private void CancelButton_OnClick(object sender, RoutedEventArgs e)
    {
        DialogResult = false;
        Close();
    }
}
