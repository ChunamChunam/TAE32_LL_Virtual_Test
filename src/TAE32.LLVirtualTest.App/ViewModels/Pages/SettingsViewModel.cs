using System.IO;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using TAE32.LLVirtualTest.App.Services;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class SettingsViewModel : ObservableObject
{
    private readonly ISystemMaintenanceService _maintenance;
    private readonly UiScaleService _uiScale;

    public IReadOnlyList<double> UiScalePresets => UiScaleService.Presets;

    public double UiScale
    {
        get => _uiScale.Scale;
        set => _uiScale.Scale = value;
    }

    [ObservableProperty] private string _workspaceRoot = AppPaths.WorkspaceRoot;
    [ObservableProperty] private string _databasePath = AppPaths.DatabasePath;
    [ObservableProperty] private string _logDirectory = AppPaths.LogDirectory;
    [ObservableProperty] private string _diagnostics = string.Empty;
    [ObservableProperty] private string _statusText = "就绪";
    [ObservableProperty] private string _note = "移除 SDK 项目仅删除数据库元数据，不会删除 SDKContent 中的原始文件。备份/恢复针对 SQLite 数据库文件。";

    public SettingsViewModel(ISystemMaintenanceService maintenance, UiScaleService uiScale)
    {
        _maintenance = maintenance;
        _uiScale = uiScale;
        _uiScale.PropertyChanged += (_, e) =>
        {
            if (e.PropertyName == nameof(UiScaleService.Scale))
                OnPropertyChanged(nameof(UiScale));
        };
        _ = RefreshDiagnosticsAsync();
    }

    [RelayCommand]
    private async Task RefreshDiagnosticsAsync()
    {
        Diagnostics = await _maintenance.GetDiagnosticsSummaryAsync();
    }

    [RelayCommand]
    private async Task BackupDatabaseAsync()
    {
        try
        {
            var path = await _maintenance.BackupDatabaseAsync();
            StatusText = "备份完成：" + path;
            await RefreshDiagnosticsAsync();
        }
        catch (Exception ex)
        {
            StatusText = "备份失败：" + ex.Message;
            MessageBox.Show(ex.Message, "备份失败");
        }
    }

    [RelayCommand]
    private async Task RestoreDatabaseAsync()
    {
        var dlg = new OpenFileDialog { Filter = "SQLite DB|*.db|All|*.*", Title = "选择备份数据库" };
        if (dlg.ShowDialog() != true) return;
        var confirm = MessageBox.Show(
            "恢复将覆盖当前数据库（会先另存 pre_restore 副本）。需重启应用后生效。继续？",
            "确认恢复", MessageBoxButton.YesNo, MessageBoxImage.Warning);
        if (confirm != MessageBoxResult.Yes) return;
        try
        {
            await _maintenance.RestoreDatabaseAsync(dlg.FileName);
            StatusText = "已恢复，请重启应用：" + dlg.FileName;
        }
        catch (Exception ex)
        {
            StatusText = "恢复失败：" + ex.Message;
            MessageBox.Show(ex.Message, "恢复失败");
        }
    }

    [RelayCommand]
    private async Task TrimLogsAsync()
    {
        try
        {
            var n = await _maintenance.TrimLogsAsync(TimeSpan.FromDays(14));
            StatusText = $"已清理 {n} 个超过 14 天的日志文件";
        }
        catch (Exception ex)
        {
            StatusText = "清理失败：" + ex.Message;
        }
    }

    [RelayCommand]
    private void OpenLogFolder()
    {
        Directory.CreateDirectory(LogDirectory);
        System.Diagnostics.Process.Start(new System.Diagnostics.ProcessStartInfo
        {
            FileName = LogDirectory,
            UseShellExecute = true
        });
    }
}
