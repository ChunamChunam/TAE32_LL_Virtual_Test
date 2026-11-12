using System.Windows;

namespace TAE32.LLVirtualTest.App.Views.Dialogs;

public partial class MessageDialog : Window
{
    public MessageDialog() => InitializeComponent();

    public static void Show(string title, string message, Window? owner = null)
    {
        var dlg = new MessageDialog
        {
            Owner = owner ?? Application.Current.MainWindow as Window
        };
        dlg.TitleText.Text = title;
        dlg.MessageText.Text = message;
        dlg.ShowDialog();
    }

    private void OkButton_OnClick(object sender, RoutedEventArgs e) => Close();
}
