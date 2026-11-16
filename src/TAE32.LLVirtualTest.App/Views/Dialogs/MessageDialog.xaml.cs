using System.Windows;

namespace TAE32.LLVirtualTest.App.Views.Dialogs;

public partial class MessageDialog : Window
{
    public MessageDialog() => InitializeComponent();

    public static void Show(string title, string message, Window? owner = null)
    {
        var dlg = new MessageDialog();
        dlg.TitleText.Text = title;
        dlg.MessageText.Text = message ?? string.Empty;

        // Startup / nested exception handlers may run before MainWindow is shown,
        // or MainWindow may already be this dialog — never set an invalid Owner.
        try
        {
            var candidate = owner ?? Application.Current?.MainWindow;
            if (candidate is not null
                && !ReferenceEquals(candidate, dlg)
                && candidate.IsLoaded
                && candidate.IsVisible)
            {
                dlg.Owner = candidate;
            }
        }
        catch
        {
            /* leave Owner unset */
        }

        try
        {
            dlg.ShowDialog();
        }
        catch
        {
            // Last resort so exception handlers never crash the process again.
            MessageBox.Show(message ?? string.Empty, title, MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }

    private void OkButton_OnClick(object sender, RoutedEventArgs e) => Close();
}
