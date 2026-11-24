using System.IO;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using TAE32.LLVirtualTest.App.Services;
using TAE32.LLVirtualTest.App.Views.Dialogs;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class SettingsViewModel : ObservableObject
{
    private readonly ISystemMaintenanceService _maintenance;
    private readonly DataStoreSessionService _dataStoreSession;
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
    [ObservableProperty] private string _note = "数据库与日志位于程序目录下的 data 文件夹。移除 SDK 项目仅删除数据库元数据，不会删除 SDKContent 中的原始文件。";
    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(ClearAllDataCommand))]
    [NotifyCanExecuteChangedFor(nameof(BackupDatabaseCommand))]
    [NotifyCanExecuteChangedFor(nameof(RestoreDatabaseCommand))]
    private bool _isMaintenanceBusy;

    private bool CanRunMaintenance => !IsMaintenanceBusy;

    public SettingsViewModel(
        ISystemMaintenanceService maintenance,
        DataStoreSessionService dataStoreSession,
        UiScaleService uiScale)
    {
        _maintenance = maintenance;
        _dataStoreSession = dataStoreSession;
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

    [RelayCommand(CanExecute = nameof(CanRunMaintenance))]
    private async Task BackupDatabaseAsync()
    {
        try
        {
            IsMaintenanceBusy = true;
            StatusText = "正在备份数据库…";
            var path = await Task.Run(() => _maintenance.BackupDatabaseAsync());
            StatusText = "备份完成：" + path;
            await RefreshDiagnosticsAsync();
        }
        catch (Exception ex)
        {
            StatusText = "备份失败：" + ex.Message;
            MessageDialog.Show("备份失败", ex.Message);
        }
        finally
        {
            IsMaintenanceBusy = false;
        }
    }

    [RelayCommand(CanExecute = nameof(CanRunMaintenance))]
    private async Task ClearAllDataAsync()
    {
        if (!ConfirmDialog.Show(
                "清空全部数据",
                "将删除 SQLite 中的全部业务数据（SDK 项目、函数、寄存器、测试用例/运行、计划/套件/报告等）。"
                + "不会删除 SDKContent 磁盘上的原始 SDK。"
                + "操作前会自动在 data 目录生成 pre_clear 备份。各功能页请重新打开以刷新列表。继续？",
                confirmLabel: "清空",
                dangerConfirm: true))
            return;
        try
        {
            IsMaintenanceBusy = true;
            StatusText = "正在备份并清空数据库，请稍候…";
            var safety = await _maintenance.ClearAllDataAsync();
            await _dataStoreSession.NotifyStoreChangedAsync();
            StatusText = safety != null
                ? "已清空并刷新界面。清空前备份：" + safety
                : "已清空全部数据并刷新界面。";
        }
        catch (Exception ex)
        {
            StatusText = "清空失败：" + ex.Message;
            MessageDialog.Show("清空失败", ex.Message);
        }
        finally
        {
            IsMaintenanceBusy = false;
        }
    }

    [RelayCommand(CanExecute = nameof(CanRunMaintenance))]
    private async Task RestoreDatabaseAsync()
    {
        var dlg = new OpenFileDialog { Filter = "SQLite DB|*.db|All|*.*", Title = "选择备份数据库" };
        if (dlg.ShowDialog() != true) return;
        if (!ConfirmDialog.Show(
                "确认恢复",
                "恢复将覆盖当前数据库（会先另存 pre_restore 副本），并自动刷新各页面数据。继续？",
                confirmLabel: "恢复",
                dangerConfirm: true))
            return;
        try
        {
            IsMaintenanceBusy = true;
            StatusText = "正在恢复数据库…";
            await _maintenance.RestoreDatabaseAsync(dlg.FileName);
            StatusText = "正在刷新界面…";
            await _dataStoreSession.NotifyStoreChangedAsync();
            StatusText = "已恢复并刷新界面：" + dlg.FileName;
        }
        catch (Exception ex)
        {
            StatusText = "恢复失败：" + ex.Message;
            MessageDialog.Show("恢复失败", ex.Message);
        }
        finally
        {
            IsMaintenanceBusy = false;
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
