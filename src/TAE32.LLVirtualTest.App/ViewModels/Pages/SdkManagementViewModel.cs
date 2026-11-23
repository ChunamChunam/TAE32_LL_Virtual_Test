using System.Collections.ObjectModel;
using System.IO;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using TAE32.LLVirtualTest.App.Services;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class SdkManagementViewModel : ObservableObject
{
    private readonly ISdkProjectService _projects;
    private readonly IScanImportService _import;
    private readonly ISdkScanService _scan;

    private readonly List<SdkProject> _allProjects = new();

    public ObservableCollection<SdkProject> Projects { get; } = new();
    public ObservableCollection<string> StatusFilterOptions { get; } = new() { "全部状态" };

    [ObservableProperty] private SdkProject? _selectedProject;
    [ObservableProperty] private string _newName = "TAE32G58xx DFP LL";
    [ObservableProperty] private string _sdkRootPath = AppPaths.DefaultSdkRoot;
    [ObservableProperty] private string _scanResultsPath = AppPaths.DefaultScanResults;
    [ObservableProperty] private string _statusMessage = string.Empty;
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private string _projectSearchText = string.Empty;
    [ObservableProperty] private string _selectedStatusFilter = "全部状态";

    public SdkManagementViewModel(ISdkProjectService projects, IScanImportService import, ISdkScanService scan)
    {
        _projects = projects;
        _import = import;
        _scan = scan;
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        _allProjects.Clear();
        foreach (var p in await _projects.GetAllAsync())
            _allProjects.Add(p);
        RebuildStatusFilters();
        ApplyProjectFilter();
    }

    [RelayCommand]
    private void SearchProjects() => ApplyProjectFilter();

    partial void OnSelectedStatusFilterChanged(string value) => ApplyProjectFilter();

    private void RebuildStatusFilters()
    {
        var keep = SelectedStatusFilter;
        StatusFilterOptions.Clear();
        StatusFilterOptions.Add("全部状态");
        foreach (var s in _allProjects.Select(x => x.ScanStatus.ToString()).Distinct().OrderBy(x => x))
            StatusFilterOptions.Add(s);
        SelectedStatusFilter = StatusFilterOptions.Contains(keep) ? keep : "全部状态";
    }

    private void ApplyProjectFilter()
    {
        var selectedId = SelectedProject?.Id;
        Projects.Clear();
        var term = string.IsNullOrWhiteSpace(ProjectSearchText) ? null : ProjectSearchText.Trim();
        var status = string.IsNullOrWhiteSpace(SelectedStatusFilter) || SelectedStatusFilter == "全部状态"
            ? null
            : SelectedStatusFilter;
        foreach (var p in _allProjects)
        {
            var statusText = p.ScanStatus.ToString();
            if (status is not null && !string.Equals(statusText, status, StringComparison.OrdinalIgnoreCase))
                continue;
            if (term is not null
                && !(p.Name?.Contains(term, StringComparison.OrdinalIgnoreCase) ?? false)
                && !statusText.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !(p.SdkRootPath?.Contains(term, StringComparison.OrdinalIgnoreCase) ?? false))
                continue;
            Projects.Add(p);
        }

        SelectedProject = Projects.FirstOrDefault(x => x.Id == selectedId) ?? Projects.FirstOrDefault();
    }

    [RelayCommand]
    private void BrowseSdk()
    {
        var dlg = new OpenFolderDialog
        {
            Title = "选择 SDK 根目录（包目录或 LL 目录）",
            Multiselect = false
        };
        if (!string.IsNullOrWhiteSpace(SdkRootPath) && Directory.Exists(SdkRootPath))
            dlg.InitialDirectory = SdkRootPath;

        if (dlg.ShowDialog() == true)
        {
            SdkRootPath = dlg.FolderName;
            // Default scan output beside workspace ScanResults, or under data/scan/<folderName>
            var folderName = Path.GetFileName(SdkRootPath.TrimEnd(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar));
            if (string.Equals(folderName, "LL", StringComparison.OrdinalIgnoreCase))
                folderName = Path.GetFileName(Path.GetDirectoryName(SdkRootPath)!) ?? "SDK";
            ScanResultsPath = Path.Combine(AppPaths.DataDirectory, "scan", Sanitize(folderName));
            if (string.IsNullOrWhiteSpace(NewName) || NewName == "TAE32G58xx DFP LL")
                NewName = folderName;
            StatusMessage = $"已选择 SDK：{SdkRootPath}。扫描结果将输出到：{ScanResultsPath}";
        }
    }

    [RelayCommand]
    private void BrowseScanOutput()
    {
        var dlg = new OpenFolderDialog
        {
            Title = "选择扫描 JSON 输出目录",
            Multiselect = false
        };
        if (!string.IsNullOrWhiteSpace(ScanResultsPath) && Directory.Exists(ScanResultsPath))
            dlg.InitialDirectory = ScanResultsPath;
        else if (Directory.Exists(AppPaths.WorkspaceRoot))
            dlg.InitialDirectory = AppPaths.WorkspaceRoot;

        if (dlg.ShowDialog() == true)
        {
            ScanResultsPath = dlg.FolderName;
            StatusMessage = $"扫描输出目录：{ScanResultsPath}";
        }
    }

    /// <summary>
    /// Core workflow: select SDK → scan sources → write JSON → import into DB.
    /// </summary>
    [RelayCommand]
    public async Task ScanAndImportAsync()
    {
        try
        {
            IsBusy = true;
            if (string.IsNullOrWhiteSpace(SdkRootPath) || !Directory.Exists(SdkRootPath))
            {
                StatusMessage = "请先选择有效的 SDK 路径。";
                return;
            }

            Directory.CreateDirectory(ScanResultsPath);
            StatusMessage = "正在扫描 SDK 并生成 JSON…";
            await Task.Yield();

            var sdkRoot = SdkRootPath;
            var scanOut = ScanResultsPath;
            // File walk + JSON write is CPU/IO heavy — keep off UI thread.
            var scanResult = await Task.Run(() => _scan.ScanAsync(sdkRoot, scanOut))
                .ConfigureAwait(true);
            if (!scanResult.Success)
            {
                StatusMessage = $"扫描失败：{scanResult.Message}";
                return;
            }

            StatusMessage = $"{scanResult.Message} 正在写入数据库…";
            await Task.Yield();

            // Ensure project exists / update paths
            SdkProject project;
            if (SelectedProject is not null
                && string.Equals(SelectedProject.SdkRootPath, Path.GetFullPath(scanResult.SdkRootPath), StringComparison.OrdinalIgnoreCase))
            {
                await _projects.UpdatePathsAsync(SelectedProject.Id, scanResult.SdkRootPath, scanResult.OutputDirectory);
                project = (await _projects.GetByIdAsync(SelectedProject.Id))!;
            }
            else
            {
                var existing = (await _projects.GetAllAsync())
                    .FirstOrDefault(p => string.Equals(p.SdkRootPath, Path.GetFullPath(scanResult.SdkRootPath), StringComparison.OrdinalIgnoreCase));
                if (existing is not null)
                {
                    await _projects.UpdatePathsAsync(existing.Id, scanResult.SdkRootPath, scanResult.OutputDirectory);
                    project = (await _projects.GetByIdAsync(existing.Id))!;
                }
                else
                {
                    project = await _projects.AddAsync(
                        string.IsNullOrWhiteSpace(NewName) ? Path.GetFileName(scanResult.SdkRootPath) : NewName,
                        scanResult.SdkRootPath,
                        scanResult.OutputDirectory);
                }
            }

            var projectId = project.Id;
            var importResult = await Task.Run(() => _import.ImportAsync(projectId))
                .ConfigureAwait(true);
            StatusMessage = importResult.Success
                ? $"扫描+导入完成：芯片 {importResult.ChipCount}，外设 {importResult.PeripheralCount}，函数 {importResult.FunctionCount}。JSON：{scanResult.OutputDirectory}"
                : $"扫描成功，但导入失败：{importResult.Message}";

            await RefreshAsync();
            SelectedProject = Projects.FirstOrDefault(x => x.Id == project.Id);
            SdkRootPath = scanResult.SdkRootPath;
            ScanResultsPath = scanResult.OutputDirectory;
        }
        catch (Exception ex)
        {
            StatusMessage = $"扫描/导入异常：{ex.Message}";
        }
        finally { IsBusy = false; }
    }

    [RelayCommand]
    public async Task AddAsync()
    {
        // Adding a project now also triggers scan+import for the selected SDK path.
        await ScanAndImportAsync();
    }

    [RelayCommand]
    public async Task RemoveAsync()
    {
        if (SelectedProject is null) return;
        try
        {
            IsBusy = true;
            var name = SelectedProject.Name;
            await _projects.RemoveAsync(SelectedProject.Id);
            StatusMessage = $"已移除项目元数据：{name}。原始 SDK 文件仍保留在磁盘。";
            await RefreshAsync();
        }
        catch (Exception ex)
        {
            StatusMessage = $"移除失败：{ex.Message}";
        }
        finally { IsBusy = false; }
    }

    [RelayCommand]
    public async Task ImportAsync()
    {
        if (SelectedProject is null)
        {
            StatusMessage = "请先选择 SDK 项目，或使用「扫描并生成 JSON」。";
            return;
        }

        try
        {
            IsBusy = true;
            if (!StartupScanImportService.HasRequiredScanFiles(SelectedProject.ScanResultsPath))
            {
                StatusMessage = "当前输出目录尚无扫描 JSON，请先点击「扫描并生成 JSON」。";
                return;
            }

            StatusMessage = "正在导入已有扫描 JSON…";
            await Task.Yield();
            var projectId = SelectedProject.Id;
            var result = await Task.Run(() => _import.ImportAsync(projectId))
                .ConfigureAwait(true);
            StatusMessage = result.Success
                ? $"{result.Message} 新增 {result.InsertedCount}，更新 {result.UpdatedCount}。"
                : $"导入失败：{result.Message}";
            await RefreshAsync();
        }
        catch (Exception ex)
        {
            StatusMessage = $"导入异常：{ex.Message}";
        }
        finally { IsBusy = false; }
    }

    [RelayCommand]
    public async Task SavePathsAsync()
    {
        if (SelectedProject is null) return;
        try
        {
            IsBusy = true;
            await _projects.UpdatePathsAsync(SelectedProject.Id, SdkRootPath, ScanResultsPath);
            StatusMessage = "路径已更新。";
            await RefreshAsync();
        }
        catch (Exception ex)
        {
            StatusMessage = $"更新失败：{ex.Message}";
        }
        finally { IsBusy = false; }
    }

    partial void OnSelectedProjectChanged(SdkProject? value)
    {
        if (value is null) return;
        NewName = value.Name;
        SdkRootPath = value.SdkRootPath;
        ScanResultsPath = value.ScanResultsPath;
        _ = ApplyCurrentWorkspaceAsync(value.Id);
    }

    private async Task ApplyCurrentWorkspaceAsync(Guid projectId)
    {
        try
        {
            await _projects.SetCurrentAsync(projectId);
        }
        catch
        {
            // Ignore if project was removed during async selection change.
        }
    }

    private static string Sanitize(string name)
    {
        foreach (var c in Path.GetInvalidFileNameChars())
            name = name.Replace(c, '_');
        return string.IsNullOrWhiteSpace(name) ? "SDK" : name;
    }
}
