using System.Collections.ObjectModel;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using TAE32.LLVirtualTest.App.Views.Dialogs;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class AutomationTestViewModel : ObservableObject
{
    private const string InlineForm = "inline_definition";
    private readonly ILLTestEngine _engine;
    private readonly ILlTestCaseStore _store;
    private readonly ICompilerService _compiler;
    private readonly IAppDataService _data;
    private readonly ISdkProjectService _projects;
    private readonly HashSet<Guid> _checkedFunctionIds = new();
    private readonly HashSet<Guid> _checkedCaseIds = new();
    private CancellationTokenSource? _busyCts;
    private bool _suppressAllSelectedSync;
    private bool _suppressChipFilterReload;
    private readonly Dictionary<string, Chip> _chipsByModel = new(StringComparer.OrdinalIgnoreCase);
    private bool _contentLoaded;
    private Guid? _contentProjectId;
    private bool _compilerChecked;

    public ObservableCollection<string> PeripheralFilters { get; } = new();
    public ObservableCollection<string> ChipFilters { get; } = new();
    public ObservableCollection<FunctionPickItem> Functions { get; } = new();
    public ObservableCollection<CasePickItem> Cases { get; } = new();
    public ObservableCollection<RunPickItem> Runs { get; } = new();
    public ObservableCollection<string> LogLines { get; } = new();
    public ObservableCollection<int> FunctionPageSizeOptions { get; } = new() { 50, 100, 200, 300 };
    public ObservableCollection<string> CaseStatusFilterOptions { get; } = new()
    {
        "全部状态",
        nameof(LlTestCaseStatus.Draft),
        nameof(LlTestCaseStatus.Ready),
        nameof(LlTestCaseStatus.Disabled),
        nameof(LlTestCaseStatus.Unsupported)
    };
    public ObservableCollection<string> RunStatusFilterOptions { get; } = new()
    {
        "全部状态",
        nameof(LlTestRunStatus.Pending),
        nameof(LlTestRunStatus.Compiling),
        nameof(LlTestRunStatus.Running),
        nameof(LlTestRunStatus.Passed),
        nameof(LlTestRunStatus.Failed),
        nameof(LlTestRunStatus.Error),
        nameof(LlTestRunStatus.Skipped),
        nameof(LlTestRunStatus.Timeout),
        nameof(LlTestRunStatus.Cancelled),
        nameof(LlTestRunStatus.StaticAnalysisFailed)
    };

    [ObservableProperty] private string _selectedPeripheral = "(全部)";
    [ObservableProperty] private string _selectedChip = "(全部)";
    [ObservableProperty] private string _functionSearchText = string.Empty;
    [ObservableProperty] private FunctionPickItem? _selectedFunctionItem;
    [ObservableProperty] private CasePickItem? _selectedCaseItem;
    [ObservableProperty] private RunPickItem? _selectedRunItem;
    [ObservableProperty] private bool _isAllRunsOnPageSelected;
    [ObservableProperty] private string _runSearchText = string.Empty;
    [ObservableProperty] private string _selectedRunStatusFilter = "全部状态";
    [ObservableProperty] private int _runPageIndex = 1;
    [ObservableProperty] private int _runPageSize = 50;
    [ObservableProperty] private int _runTotalCount;
    [ObservableProperty] private int _runTotalPages = 1;
    [ObservableProperty] private string _runPageInfo = string.Empty;
    [ObservableProperty] private bool _canRunPrev;
    [ObservableProperty] private bool _canRunNext;
    private bool _suppressRunAllSelectedSync;

    public LlTestRun? SelectedRun => SelectedRunItem?.Run;
    [ObservableProperty] private bool _isAllCasesSelected;
    [ObservableProperty] private string _caseCheckedCountText = "已勾选用例 0";
    private bool _suppressCaseAllSelectedSync;
    [ObservableProperty] private string _clangPath = string.Empty;
    [ObservableProperty] private string _compilerSummary = "尚未检查编译环境";
    [ObservableProperty] private string _caseEditorJson = string.Empty;
    [ObservableProperty] private string _resultDetail = string.Empty;
    [ObservableProperty] private string _statusText = "就绪（虚拟环境测试，非真实硬件验证）";
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private string _busyOverlayText = "请稍候…";
    [ObservableProperty] private double _progressValue;
    [ObservableProperty] private double _progressMaximum = 100;
    [ObservableProperty] private bool _isProgressIndeterminate = true;
    [ObservableProperty] private bool _showBusyCancel;
    [ObservableProperty] private Guid? _activeProjectId;
    [ObservableProperty] private int _functionPageIndex = 1;
    [ObservableProperty] private int _functionPageSize = 100;
    [ObservableProperty] private int _functionTotalCount;
    [ObservableProperty] private int _functionTotalPages = 1;
    [ObservableProperty] private string _functionPageInfo = string.Empty;
    [ObservableProperty] private bool _canFunctionPrev;
    [ObservableProperty] private bool _canFunctionNext;
    [ObservableProperty] private bool _isAllOnPageSelected;
    [ObservableProperty] private string _checkedCountText = "已勾选 0";
    [ObservableProperty] private string _caseSearchText = string.Empty;
    [ObservableProperty] private string _selectedCaseStatusFilter = "全部状态";
    [ObservableProperty] private int _casePageIndex = 1;
    [ObservableProperty] private int _casePageSize = 100;
    [ObservableProperty] private int _caseTotalCount;
    [ObservableProperty] private int _caseTotalPages = 1;
    [ObservableProperty] private string _casePageInfo = string.Empty;
    [ObservableProperty] private bool _canCasePrev;
    [ObservableProperty] private bool _canCaseNext;

    public LlFunction? SelectedFunction => SelectedFunctionItem?.Function;
    public LlTestCase? SelectedCase => SelectedCaseItem?.Case;

    public AutomationTestViewModel(
        ILLTestEngine engine,
        ILlTestCaseStore store,
        ICompilerService compiler,
        IAppDataService data,
        ISdkProjectService projects)
    {
        _engine = engine;
        _store = store;
        _compiler = compiler;
        _data = data;
        _projects = projects;
    }

    /// <summary>导航进入页：已加载过则只刷新运行记录，避免每次切页全量查库 + Clang 检测。</summary>
    public Task EnsureLoadedAsync() => RefreshCoreAsync(force: false);

    [RelayCommand]
    public Task RefreshAsync() => RefreshCoreAsync(force: true);

    private async Task RefreshCoreAsync(bool force)
    {
        var project = await _projects.GetCurrentAsync();
        ActiveProjectId = project?.Id;
        if (project is null)
        {
            StatusText = "无 SDK 项目";
            _contentLoaded = false;
            _contentProjectId = null;
            return;
        }

        if (project.Id != _contentProjectId)
        {
            force = true;
            _contentLoaded = false;
        }

        if (!force && _contentLoaded && _contentProjectId == project.Id)
        {
            await ReloadRunsAsync();
            return;
        }

        if (force || PeripheralFilters.Count <= 1)
        {
            PeripheralFilters.Clear();
            PeripheralFilters.Add("(全部)");
            foreach (var p in await _data.GetPeripheralsAsync(project.Id))
                PeripheralFilters.Add(p.Name);
            if (!PeripheralFilters.Contains(SelectedPeripheral))
                SelectedPeripheral = "(全部)";
        }

        if (force || ChipFilters.Count == 0)
            await ReloadChipFiltersFromAllAsync(project.Id);

        await Task.WhenAll(ReloadFunctionsAsync(), ReloadCasesAsync(), ReloadRunsAsync());

        if (!_compilerChecked)
        {
            await CheckCompilerAsync();
            _compilerChecked = true;
        }

        _contentLoaded = true;
        _contentProjectId = project.Id;
    }

    [RelayCommand]
    private async Task CheckCompilerAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        var typed = string.IsNullOrWhiteSpace(ClangPath) ? null : ClangPath.Trim();
        if (typed is not null && File.Exists(typed))
            await _compiler.SaveClangPathAsync(typed);
        var env = await _engine.CheckCompilerAsync(pid, typed);
        ClangPath = env.ClangPath ?? typed ?? ClangPath;
        CompilerSummary = env.Summary;
        StatusText = env.Summary;
    }

    [RelayCommand]
    private async Task SaveClangPathAsync()
    {
        await _compiler.SaveClangPathAsync(string.IsNullOrWhiteSpace(ClangPath) ? null : ClangPath.Trim());
        await CheckCompilerAsync();
    }

    [RelayCommand]
    private async Task BrowseClangAsync()
    {
        var dlg = new OpenFileDialog
        {
            Filter = "clang.exe|clang.exe|All|*.*",
            Title = "选择 clang.exe"
        };
        if (!string.IsNullOrWhiteSpace(ClangPath) && File.Exists(ClangPath.Trim()))
            dlg.InitialDirectory = Path.GetDirectoryName(ClangPath.Trim());
        if (dlg.ShowDialog() == true)
        {
            ClangPath = dlg.FileName;
            await CheckCompilerAsync();
        }
    }

    [RelayCommand]
    private async Task FetchEmbeddedClangAsync()
    {
        if (IsBusy) return;
        BeginBusy("正在获取内置 Clang（首次约 350MB，需联网）…", indeterminate: true);
        try
        {
            var progress = new Progress<string>(m =>
            {
                // BeginInvoke: never block download thread waiting on UI (Invoke can freeze/cancel).
                Application.Current.Dispatcher.BeginInvoke(() =>
                {
                    BusyOverlayText = m;
                    StatusText = m;
                    LogLines.Insert(0, $"[{DateTime.Now:HH:mm:ss}] {m}");
                    if (LogLines.Count > 300) LogLines.RemoveAt(LogLines.Count - 1);
                }, DispatcherPriority.Background);
            });
            var result = await Task.Run(() => _compiler.EnsureEmbeddedClangAsync(progress))
                .ConfigureAwait(true);
            if (result.Succeeded && !string.IsNullOrWhiteSpace(result.ClangPath))
                ClangPath = result.ClangPath;
            StatusText = result.Message;
            CompilerSummary = result.Message;
            await CheckCompilerAsync();
        }
        catch (Exception ex)
        {
            StatusText = "获取失败：" + ex.Message;
        }
        finally { EndBusy(); }
    }

    [RelayCommand]
    private async Task GenerateCasesAsync()
    {
        var ids = _checkedFunctionIds.ToList();
        if (ids.Count == 0 && SelectedFunction is not null)
            ids.Add(SelectedFunction.Id);
        if (ids.Count == 0)
        {
            StatusText = "请勾选函数，或点「全选当前页 / 全选全部匹配」";
            return;
        }

        BeginBusy($"准备为 {ids.Count} 个函数生成用例…", indeterminate: false, maximum: ids.Count);
        ShowBusyCancel = ids.Count > 20;
        await Task.Yield();
        try
        {
            var casesWritten = 0;
            var funcWithCases = 0;
            var funcEmpty = 0;
            var funcFailed = 0;
            var fi = 0;
            foreach (var id in ids)
            {
                fi++;
                SetBusyProgress(fi, $"正在生成用例 {fi}/{ids.Count}…");
                try
                {
                    var idLocal = id;
                    var generated = await Task.Run(() => _engine.GenerateCasesAsync(idLocal))
                        .ConfigureAwait(true);
                    if (generated.Count == 0)
                        funcEmpty++;
                    else
                        funcWithCases++;
                    if (generated.Count > 0)
                    {
                        await _store.InsertManyAsync(generated, _busyCts?.Token ?? default);
                        casesWritten += generated.Count;
                    }
                }
                catch (Exception ex)
                {
                    funcFailed++;
                    LogLines.Insert(0, $"[{DateTime.Now:HH:mm:ss}] 跳过 {id}: {ex.Message}");
                    if (LogLines.Count > 300) LogLines.RemoveAt(LogLines.Count - 1);
                }
            }

            await ReloadCasesAsync();
            var filterNote = SelectedPeripheral == "(全部)"
                ? $"库内用例共 {CaseTotalCount} 条"
                : $"当前外设 {SelectedPeripheral} 用例 {CaseTotalCount} 条（左侧外设筛选用例表）";
            StatusText =
                $"生成完成：处理 {ids.Count} 个函数 → 写入 {casesWritten} 条用例（{funcWithCases} 个函数有产出，" +
                $"{funcEmpty} 个无模板，{funcFailed} 个失败）。{filterNote}。" +
                "每个 LL 函数仅 1 条自动用例（读：先写后读；写：先读基线再写后回读），同函数旧自动用例已替换。";
        }
        catch (Exception ex)
        {
            StatusText = "生成失败：" + ex.Message;
        }
        finally { EndBusy(); }
    }

    [RelayCommand]
    private void SelectAllOnPage()
    {
        foreach (var item in Functions)
            item.IsSelected = true;
        SyncCheckedCount();
        RefreshAllOnPageFlag();
    }

    [RelayCommand]
    private void ClearPageSelection()
    {
        foreach (var item in Functions)
            item.IsSelected = false;
        SyncCheckedCount();
        RefreshAllOnPageFlag();
    }

    [RelayCommand]
    private async Task SelectAllMatchingAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "无 SDK 项目";
            return;
        }

        BeginBusy("正在加载匹配函数列表…", indeterminate: true);
        await Task.Yield();
        try
        {
            var peri = SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;
            var search = string.IsNullOrWhiteSpace(FunctionSearchText) ? null : FunctionSearchText.Trim();
            var take = Math.Max(FunctionTotalCount, 1);
            var all = await _data.GetFunctionsAsync(
                sdkProjectId: pid,
                search: search,
                peripheralName: peri,
                form: InlineForm,
                skip: 0,
                take: take);

            _checkedFunctionIds.Clear();
            BeginBusy($"正在勾选 {all.Count} 个函数…", indeterminate: false, maximum: all.Count);
            await Task.Yield();
            for (var i = 0; i < all.Count; i++)
            {
                _checkedFunctionIds.Add(all[i].Id);
                if (i % 80 == 0 || i == all.Count - 1)
                {
                    SetBusyProgress(i + 1, $"正在勾选 {i + 1}/{all.Count}…");
                    await Task.Yield();
                }
            }

            foreach (var item in Functions)
                item.IsSelected = _checkedFunctionIds.Contains(item.Function.Id);
            SyncCheckedCount();
            RefreshAllOnPageFlag();
            StatusText = $"已勾选全部匹配函数 {_checkedFunctionIds.Count} 个（可翻页查看；再点「生成勾选函数用例」）";
        }
        catch (Exception ex)
        {
            StatusText = "全选失败：" + ex.Message;
        }
        finally { EndBusy(); }
    }

    [RelayCommand]
    private void ClearAllSelection()
    {
        _checkedFunctionIds.Clear();
        foreach (var item in Functions)
            item.IsSelected = false;
        SyncCheckedCount();
        RefreshAllOnPageFlag();
        StatusText = "已清空函数勾选";
    }

    [RelayCommand]
    private async Task GeneratePeripheralBatchAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "无 SDK 项目";
            return;
        }

        // "(全部)" → every peripheral; otherwise only the selected one.
        var targets = SelectedPeripheral == "(全部)" || string.IsNullOrWhiteSpace(SelectedPeripheral)
            ? PeripheralFilters.Where(p => p != "(全部)" && !string.IsNullOrWhiteSpace(p)).ToList()
            : new List<string> { SelectedPeripheral };

        if (targets.Count == 0)
        {
            StatusText = "没有可生成的外设";
            return;
        }

        var totalFuncs = 0;
        foreach (var peri in targets)
        {
            totalFuncs += await _data.CountFunctionsAsync(
                sdkProjectId: pid, peripheralName: peri, form: InlineForm);
        }

        if (totalFuncs == 0)
        {
            StatusText = "没有可生成的 inline 函数";
            return;
        }

        BeginBusy($"外设批量：{targets.Count} 个模块、{totalFuncs} 个函数…", indeterminate: false, maximum: totalFuncs);
        ShowBusyCancel = true;
        await Task.Yield();
        var ct = _busyCts?.Token ?? CancellationToken.None;
        try
        {
            var globalFuncDone = 0;
            var totalCases = 0;
            foreach (var peri in targets)
            {
                var offset = globalFuncDone;
                var periLocal = peri;
                var genProgress = new Progress<(int FunctionIndex, int FunctionTotal, int CasesSaved, string PeripheralName)>(p =>
                {
                    var done = offset + p.FunctionIndex;
                    SetBusyProgress(
                        done,
                        $"{p.PeripheralName}：函数 {p.FunctionIndex}/{p.FunctionTotal}，已写入约 {p.CasesSaved} 条");
                });
                // Off UI thread so busy overlay / cancel stay responsive during LL parse.
                var (funcs, cases) = await Task.Run(
                        () => _engine.GenerateAndSaveForPeripheralAsync(pid, periLocal, genProgress, ct),
                        ct)
                    .ConfigureAwait(true);
                globalFuncDone += funcs;
                totalCases += cases;
            }

            await ReloadCasesAsync();
            StatusText = targets.Count == 1
                ? $"外设 {targets[0]}：处理 {globalFuncDone} 个函数，写入 {totalCases} 条用例。库内共 {CaseTotalCount} 条。"
                : $"全部外设（{targets.Count} 个）：处理 {globalFuncDone} 个函数，写入 {totalCases} 条用例。库内共 {CaseTotalCount} 条。";
        }
        catch (OperationCanceledException)
        {
            await ReloadCasesAsync();
            StatusText = "外设批量生成已取消（已写入部分用例）";
        }
        catch (Exception ex)
        {
            StatusText = "批量生成失败：" + ex.Message;
        }
        finally { EndBusy(); }
    }

    [RelayCommand]
    private async Task SaveCaseEditorAsync()
    {
        try
        {
            var model = System.Text.Json.JsonSerializer.Deserialize<LlTestCaseEditModel>(
                CaseEditorJson,
                new System.Text.Json.JsonSerializerOptions
                {
                    PropertyNameCaseInsensitive = true,
                    PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
                });
            if (model is null) throw new InvalidOperationException("JSON 无效");
            if (ActiveProjectId is Guid pid) model.SdkProjectId = pid;
            await _store.UpsertAsync(model);
            StatusText = "用例已保存";
            await ReloadCasesAsync();
        }
        catch (Exception ex)
        {
            StatusText = "保存失败：" + ex.Message;
        }
    }

    [RelayCommand]
    private async Task DeleteCaseAsync()
    {
        var ids = GetSelectedCaseIds();
        if (ids.Count == 0)
        {
            StatusText = "请先勾选要删除的用例";
            return;
        }

        if (!ConfirmDialog.Show(
                "批量删除",
                $"确认删除选中的 {ids.Count} 条测试用例及其运行记录？",
                confirmLabel: "删除",
                cancelLabel: "取消",
                dangerConfirm: true))
            return;

        var n = await _store.DeleteManyAsync(ids);
        _checkedCaseIds.Clear();
        StatusText = $"已删除 {n} 条用例";
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private void SelectAllCasesOnPage()
    {
        foreach (var c in Cases)
        {
            c.IsSelected = true;
            _checkedCaseIds.Add(c.Case.Id);
        }
        RefreshCaseSelectionUi();
    }

    [RelayCommand]
    private async Task SelectAllMatchingCasesAsync()
    {
        if (ActiveProjectId is null)
        {
            StatusText = "无 SDK 项目";
            return;
        }

        BeginBusy("正在加载筛选用例…", indeterminate: true);
        await Task.Yield();
        try
        {
            var all = await LoadFilteredCasesAsync();
            _checkedCaseIds.Clear();
            BeginBusy($"正在勾选 {all.Count} 条用例…", indeterminate: false, maximum: all.Count);
            await Task.Yield();
            for (var i = 0; i < all.Count; i++)
            {
                _checkedCaseIds.Add(all[i].Id);
                if (i % 100 == 0 || i == all.Count - 1)
                {
                    SetBusyProgress(i + 1, $"正在勾选 {i + 1}/{all.Count}…");
                    await Task.Yield();
                }
            }

            foreach (var item in Cases)
                item.IsSelected = _checkedCaseIds.Contains(item.Case.Id);
            RefreshCaseSelectionUi();
            StatusText = $"已勾选当前筛选全部 {_checkedCaseIds.Count} 条用例（跨页；删除/运行作用于全部勾选）";
        }
        catch (Exception ex)
        {
            StatusText = "全选用例失败：" + ex.Message;
        }
        finally { EndBusy(); }
    }

    [RelayCommand]
    private void ClearCaseSelection()
    {
        _checkedCaseIds.Clear();
        foreach (var c in Cases) c.IsSelected = false;
        RefreshCaseSelectionUi();
        StatusText = "已清空用例勾选";
    }

    [RelayCommand]
    private async Task DuplicateCaseAsync()
    {
        if (SelectedCase is null) return;
        await _store.DuplicateAsync(SelectedCase.Id);
        StatusText = "已复制用例";
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task ExportCasesAsync()
    {
        if (Cases.Count == 0) return;
        var dlg = new SaveFileDialog { Filter = "JSON|*.json", FileName = "ll-test-cases.json" };
        if (dlg.ShowDialog() != true) return;
        var exportIds = GetSelectedCaseIds();
        if (exportIds.Count == 0)
        {
            var all = await LoadFilteredCasesAsync();
            exportIds = all.Select(c => c.Id).ToList();
        }
        var json = await _store.ExportJsonAsync(exportIds);
        await File.WriteAllTextAsync(dlg.FileName, json, Encoding.UTF8);
        StatusText = "已导出 " + dlg.FileName;
    }

    [RelayCommand]
    private async Task ImportCasesAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        var dlg = new OpenFileDialog { Filter = "JSON|*.json" };
        if (dlg.ShowDialog() != true) return;
        var json = await File.ReadAllTextAsync(dlg.FileName);
        var n = await _store.ImportJsonAsync(pid, json);
        StatusText = $"已导入 {n} 条";
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task RunSelectedAsync()
    {
        var runIds = GetSelectedCaseIds();
        if (runIds.Count == 0)
        {
            StatusText = "请勾选要运行的用例";
            return;
        }
        await RunInternalAsync(runIds);
    }

    [RelayCommand]
    private async Task RunReadyBatchAsync()
    {
        var all = await LoadFilteredCasesAsync();
        var ids = all.Where(c => c.Status == "Ready").Select(c => c.Id).ToList();
        if (ids.Count == 0)
        {
            StatusText = "当前筛选无 Ready 状态用例（可先批量生成，或把 Draft 改成 Ready）";
            return;
        }
        await RunInternalAsync(ids);
    }

    [RelayCommand]
    private async Task RunAllListedAsync()
    {
        var all = await LoadFilteredCasesAsync();
        var ids = all.Select(c => c.Id).ToList();
        if (ids.Count == 0)
        {
            StatusText = "当前筛选用例为空";
            return;
        }
        await RunInternalAsync(ids);
    }

    [RelayCommand]
    private async Task MarkListedReadyAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "无 SDK 项目";
            return;
        }

        var peri = CasePeripheralFilter();
        var search = string.IsNullOrWhiteSpace(CaseSearchText) ? null : CaseSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedCaseStatusFilter);
        var pending = await _store.CountFilteredNotReadyAsync(pid, peri, search, status);
        if (pending == 0)
        {
            StatusText = "当前筛选内没有 Draft 用例可标为 Ready";
            return;
        }

        BeginBusy($"正在将 {pending} 条用例标为 Ready…", indeterminate: true);
        await Task.Yield();
        try
        {
            var n = await _store.MarkFilteredReadyAsync(
                pid, peri, search, status, _busyCts?.Token ?? CancellationToken.None);
            await ReloadCasesAsync();
            var scope = peri is null && search is null
                ? "当前项目全部筛选用例"
                : $"外设/搜索筛选（{SelectedPeripheral}{(string.IsNullOrWhiteSpace(search) ? "" : " · 含搜索")}）";
            StatusText = $"已将 {scope} 内 {n} 条标为 Ready";
        }
        catch (OperationCanceledException)
        {
            StatusText = "标 Ready 已取消";
        }
        catch (Exception ex)
        {
            StatusText = "标 Ready 失败：" + ex.Message;
        }
        finally
        {
            EndBusy();
        }
    }

    [RelayCommand]
    private void CancelRun()
    {
        _busyCts?.Cancel();
        StatusText = "正在取消…";
    }

    partial void OnSelectedPeripheralChanged(string value)
    {
        FunctionPageIndex = 1;
        CasePageIndex = 1;
        _checkedFunctionIds.Clear();
        _checkedCaseIds.Clear();
        SyncCheckedCount();
        _ = ReloadFunctionsAsync();
        _ = ReloadCasesAsync();
    }

    partial void OnSelectedChipChanged(string value)
    {
        if (_suppressChipFilterReload) return;
        _ = OnChipSelectionChangedAsync();
    }

    private async Task OnChipSelectionChangedAsync()
    {
        if (string.IsNullOrWhiteSpace(SelectedChip) || SelectedChip == "(全部)")
        {
            FunctionPageIndex = 1;
            _checkedFunctionIds.Clear();
            SyncCheckedCount();
            await ReloadFunctionsAsync();
            return;
        }

        if (!_chipsByModel.TryGetValue(SelectedChip.Trim(), out var chip))
        {
            StatusText = $"未找到芯片「{SelectedChip}」对应 SDK 工程";
            return;
        }

        try
        {
            await _projects.SetCurrentAsync(chip.SdkProjectId);
        }
        catch (Exception ex)
        {
            StatusText = $"切换 SDK 失败：{ex.Message}";
            return;
        }

        ActiveProjectId = chip.SdkProjectId;
        _contentProjectId = null;
        _contentLoaded = false;

        PeripheralFilters.Clear();
        PeripheralFilters.Add("(全部)");
        foreach (var p in await _data.GetPeripheralsAsync(chip.SdkProjectId))
            PeripheralFilters.Add(p.Name);
        if (!PeripheralFilters.Contains(SelectedPeripheral))
            SelectedPeripheral = "(全部)";

        FunctionPageIndex = 1;
        _checkedFunctionIds.Clear();
        SyncCheckedCount();

        var proj = await _projects.GetByIdAsync(chip.SdkProjectId);
        await ReloadFunctionsAsync();
        await ReloadCasesAsync();
        StatusText = $"已按芯片 {chip.ModelName} 加载 LL 内容（SDK：{proj?.Name ?? "—"}）";
    }

    [RelayCommand]
    private async Task SearchFunctionsAsync()
    {
        FunctionPageIndex = 1;
        await ReloadFunctionsAsync();
    }

    [RelayCommand]
    private async Task SearchCasesAsync()
    {
        CasePageIndex = 1;
        _checkedCaseIds.Clear();
        await ReloadCasesAsync();
    }

    partial void OnSelectedCaseStatusFilterChanged(string value)
    {
        CasePageIndex = 1;
        _checkedCaseIds.Clear();
        _ = ReloadCasesAsync();
    }

    partial void OnCasePageSizeChanged(int value)
    {
        CasePageIndex = 1;
        _ = ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task CasePreviousPageAsync()
    {
        if (CasePageIndex <= 1) return;
        CasePageIndex--;
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task CaseNextPageAsync()
    {
        if (CasePageIndex >= CaseTotalPages) return;
        CasePageIndex++;
        await ReloadCasesAsync();
    }

    partial void OnIsAllOnPageSelectedChanged(bool value)
    {
        if (_suppressAllSelectedSync) return;
        foreach (var item in Functions)
            item.IsSelected = value;
        SyncCheckedCount();
    }

    partial void OnSelectedFunctionItemChanged(FunctionPickItem? value)
    {
        // Keep highlight selection independent from checkbox multi-select.
    }

    partial void OnFunctionPageSizeChanged(int value)
    {
        FunctionPageIndex = 1;
        _ = ReloadFunctionsAsync();
    }

    [RelayCommand]
    private async Task FunctionFirstPageAsync()
    {
        FunctionPageIndex = 1;
        await ReloadFunctionsAsync();
    }

    [RelayCommand]
    private async Task FunctionPreviousPageAsync()
    {
        if (FunctionPageIndex <= 1) return;
        FunctionPageIndex--;
        await ReloadFunctionsAsync();
    }

    [RelayCommand]
    private async Task FunctionNextPageAsync()
    {
        if (FunctionPageIndex >= FunctionTotalPages) return;
        FunctionPageIndex++;
        await ReloadFunctionsAsync();
    }

    [RelayCommand]
    private async Task FunctionLastPageAsync()
    {
        FunctionPageIndex = Math.Max(1, FunctionTotalPages);
        await ReloadFunctionsAsync();
    }

    partial void OnSelectedCaseItemChanged(CasePickItem? value)
    {
        if (value is null)
        {
            CaseEditorJson = string.Empty;
            return;
        }
        var edit = Infrastructure.TestEngine.LlTestCaseStore.ToEdit(value.Case);
        CaseEditorJson = System.Text.Json.JsonSerializer.Serialize(edit, new System.Text.Json.JsonSerializerOptions
        {
            WriteIndented = true,
            PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
        });
    }

    partial void OnIsAllCasesSelectedChanged(bool value)
    {
        if (_suppressCaseAllSelectedSync) return;
        foreach (var c in Cases)
        {
            c.IsSelected = value;
            if (value)
                _checkedCaseIds.Add(c.Case.Id);
            else
                _checkedCaseIds.Remove(c.Case.Id);
        }
        RefreshCaseSelectionUi(updateAllFlag: false);
    }

    [RelayCommand]
    private async Task SearchRunsAsync()
    {
        RunPageIndex = 1;
        await ReloadRunsAsync();
    }

    partial void OnSelectedRunStatusFilterChanged(string value)
    {
        RunPageIndex = 1;
        _ = ReloadRunsAsync();
    }

    partial void OnRunPageSizeChanged(int value)
    {
        RunPageIndex = 1;
        _ = ReloadRunsAsync();
    }

    [RelayCommand]
    private async Task RunPreviousPageAsync()
    {
        if (RunPageIndex <= 1) return;
        RunPageIndex--;
        await ReloadRunsAsync();
    }

    [RelayCommand]
    private async Task RunNextPageAsync()
    {
        if (RunPageIndex >= RunTotalPages) return;
        RunPageIndex++;
        await ReloadRunsAsync();
    }

    [RelayCommand]
    private async Task DeleteSelectedRunsAsync()
    {
        var ids = Runs.Where(r => r.IsSelected).Select(r => r.Run.Id).ToList();
        if (ids.Count == 0 && SelectedRun is not null)
            ids.Add(SelectedRun.Id);
        if (ids.Count == 0)
        {
            StatusText = "请先勾选要删除的运行记录";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除运行记录",
                $"确认删除选中的 {ids.Count} 条运行记录？（不删除测试用例本身）",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _store.DeleteRunsAsync(ids);
        StatusText = $"已删除 {n} 条运行记录";
        await ReloadRunsAsync();
    }

    partial void OnIsAllRunsOnPageSelectedChanged(bool value)
    {
        if (_suppressRunAllSelectedSync) return;
        foreach (var r in Runs) r.IsSelected = value;
    }

    partial void OnSelectedRunItemChanged(RunPickItem? value) => _ = LoadRunDetailAsync(value);

    private async Task LoadRunDetailAsync(RunPickItem? value)
    {
        var listRun = value?.Run;
        if (listRun is null)
        {
            ResultDetail = string.Empty;
            return;
        }

        ResultDetail = "加载详情…";
        var run = await _store.GetRunAsync(listRun.Id) ?? listRun;

        static string Flag(bool ok, string yes, string no) => ok ? yes : no;
        var sb = new StringBuilder();
        sb.AppendLine("======== 运行摘要（虚拟环境，非真实硬件）========");
        sb.AppendLine($"状态        : {run.Status}");
        sb.AppendLine($"编译        : {Flag(run.CompileSucceeded, "通过", "未通过")}");
        sb.AppendLine($"执行        : {Flag(run.ExecuteCompleted, "完成", "未完成")}");
        sb.AppendLine($"断言        : {Flag(run.AssertionsPassed, "通过", "未通过")}");
        sb.AppendLine($"硬件行为模拟: {Flag(run.HardwareBehaviorSimulated, "是", "否")}");
        sb.AppendLine($"返回值      : {run.ReturnValueText ?? "—"}");
        sb.AppendLine($"耗时        : {run.DurationMs} ms");
        sb.AppendLine($"失败原因    : {run.FailureReason ?? "—"}");
        if (string.Equals(run.Status, nameof(LlTestRunStatus.Skipped), StringComparison.OrdinalIgnoreCase))
        {
            sb.AppendLine();
            sb.AppendLine("说明：Skipped 仍可能已完成环境检查/编译/执行；");
            sb.AppendLine("常见原因是仅超时断言通过、缺少语义校验，故不计 Passed。");
            sb.AppendLine("下方「执行日志 / 阶段」即为本次操作过程。");
        }

        sb.AppendLine();
        sb.AppendLine("======== 静态分析 ========");
        if (string.IsNullOrWhiteSpace(run.StaticAnalysisJson) || run.StaticAnalysisJson is "[]" or "null")
        {
            sb.AppendLine(string.Equals(run.Status, "StaticAnalysisFailed", StringComparison.OrdinalIgnoreCase)
                ? "（失败，但诊断 JSON 缺失）"
                : "通过 / 无诊断");
        }
        else
        {
            try
            {
                var diags = System.Text.Json.JsonSerializer.Deserialize<List<TAE32.LLVirtualTest.Core.Models.StaticAnalysisDiagnostic>>(
                    run.StaticAnalysisJson,
                    new System.Text.Json.JsonSerializerOptions { PropertyNameCaseInsensitive = true })
                    ?? new List<TAE32.LLVirtualTest.Core.Models.StaticAnalysisDiagnostic>();
                var sa = new TAE32.LLVirtualTest.Core.Models.StaticAnalysisResult
                {
                    HasBlockingError = diags.Any(d => string.Equals(d.Severity, "Error", StringComparison.OrdinalIgnoreCase)),
                    HasWarning = diags.Any(d => string.Equals(d.Severity, "Warning", StringComparison.OrdinalIgnoreCase)),
                    Diagnostics = diags
                };
                var fn = run.TestCase?.FunctionName
                         ?? SelectedRunItem?.CaseName
                         ?? "—";
                sb.AppendLine(Infrastructure.TestEngine.LlShiftStaticAnalyzer.FormatReport(fn, sa).TrimEnd());
            }
            catch
            {
                sb.AppendLine(run.StaticAnalysisJson.Trim());
            }
        }

        sb.AppendLine();
        sb.AppendLine("======== 执行日志 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(run.ExecutionLog) ? "（无）" : run.ExecutionLog.Trim());
        sb.AppendLine();
        sb.AppendLine("======== 编译日志 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(run.CompileLog) ? "（无）" : run.CompileLog.Trim());
        sb.AppendLine();
        sb.AppendLine("======== 断言结果 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(run.AssertionResultsJson) ? "（无）" : run.AssertionResultsJson.Trim());
        TryAppendWriteCheckSummary(sb, run);
        sb.AppendLine();
        sb.AppendLine("======== 阶段 / 访问轨迹 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(run.StagesJson) ? "阶段：（无）" : "阶段: " + run.StagesJson.Trim());
        sb.AppendLine(string.IsNullOrWhiteSpace(run.AccessTraceJson) ? "轨迹：（无）" : "轨迹: " + run.AccessTraceJson.Trim());
        ResultDetail = sb.ToString();
    }

    private static void TryAppendWriteCheckSummary(StringBuilder sb, LlTestRun run)
    {
        if (string.IsNullOrWhiteSpace(run.AssertionResultsJson) || run.AssertionResultsJson is "[]" or "null")
            return;
        try
        {
            var results = System.Text.Json.JsonSerializer.Deserialize<List<LlTestAssertionResult>>(
                run.AssertionResultsJson,
                new System.Text.Json.JsonSerializerOptions { PropertyNameCaseInsensitive = true });
            if (results is null || results.Count == 0) return;
            var semantic = results.Where(a => a.Kind is not LlAssertionKind.Timeout).ToList();
            if (semantic.Count == 0) return;

            sb.AppendLine();
            sb.AppendLine("======== 写入验证摘要（无 Get / 虚拟寄存器）========");
            foreach (var a in semantic)
            {
                var mark = a.Passed ? "Passed" : "Failed";
                sb.AppendLine($"{a.Kind,-18} {mark,-6}  expected={a.Expected ?? "—"}  actual={a.Actual ?? "—"}");
                if (!string.IsNullOrWhiteSpace(a.Message))
                    sb.AppendLine($"  {a.Message}");
                if (!string.IsNullOrWhiteSpace(a.RuleSourceDetail))
                    sb.AppendLine($"  {a.RuleSourceDetail}");
            }
        }
        catch
        {
            /* ignore malformed JSON */
        }
    }

    private void RefreshRunSelectionUi()
    {
        _suppressRunAllSelectedSync = true;
        IsAllRunsOnPageSelected = Runs.Count > 0 && Runs.All(r => r.IsSelected);
        _suppressRunAllSelectedSync = false;
    }

    private async Task RunInternalAsync(IReadOnlyList<Guid> ids)
    {
        BeginBusy($"准备执行 {ids.Count} 条用例…", indeterminate: false, maximum: ids.Count);
        ShowBusyCancel = true;
        await Task.Yield();
        LogLines.Clear();
        var ct = _busyCts?.Token ?? CancellationToken.None;
        var runIndex = 0;
        string? pendingLog = null;
        var flushScheduled = false;
        void FlushUi()
        {
            var m = pendingLog;
            if (m is null) return;
            if (m.StartsWith("运行用例", StringComparison.Ordinal))
            {
                // Prefer "运行用例 i/N …" from engine; fall back to sequential bump.
                var parsed = false;
                var slash = m.IndexOf('/');
                if (slash > 0)
                {
                    var sp = m.LastIndexOf(' ', slash);
                    if (sp >= 0 &&
                        int.TryParse(m.AsSpan(sp + 1, slash - sp - 1), out var cur) &&
                        cur >= 1)
                    {
                        runIndex = Math.Min(cur, ids.Count);
                        parsed = true;
                    }
                }
                if (!parsed)
                    runIndex = Math.Min(runIndex + 1, ids.Count);
                SetBusyProgress(runIndex, $"执行中 {runIndex}/{ids.Count}（虚拟 MCU）…");
            }
            else if (m.Contains("装载共享虚拟 MCU", StringComparison.Ordinal) ||
                     m.Contains("预热静态分析", StringComparison.Ordinal) ||
                     m.Contains("虚拟 MCU 就绪", StringComparison.Ordinal) ||
                     m.Contains("创建并装载虚拟 MCU", StringComparison.Ordinal) ||
                     m.Contains("复用共享虚拟 MCU", StringComparison.Ordinal) ||
                     m.Contains("静态分析", StringComparison.Ordinal) ||
                     m.Contains("开始编译", StringComparison.Ordinal) ||
                     m.Contains("SQLite", StringComparison.Ordinal))
            {
                // Mid-case stage text so overlay is not frozen on "1/N" during compile/load.
                BusyOverlayText = runIndex == 0
                    ? m
                    : $"执行中 {runIndex}/{ids.Count} — {m}";
                StatusText = BusyOverlayText;
            }
            LogLines.Insert(0, $"[{DateTime.Now:HH:mm:ss}] {m}");
            if (LogLines.Count > 300) LogLines.RemoveAt(LogLines.Count - 1);
        }

        var progress = new Progress<string>(m =>
        {
            pendingLog = m;
            if (flushScheduled) return;
            flushScheduled = true;
            Application.Current.Dispatcher.BeginInvoke(() =>
            {
                flushScheduled = false;
                FlushUi();
            }, DispatcherPriority.Background);
        });
        try
        {
            StatusText = "测试执行中（虚拟 MCU，非真实硬件）…";
            var results = await _engine.RunManyAsync(ids, progress, ct);
            var passed = results.Count(r => r.Status == Core.Enums.LlTestRunStatus.Passed);
            StatusText = $"完成：{passed}/{results.Count} Passed（虚拟环境结果）";
            await ReloadRunsAsync();
            if (results.Count > 0)
            {
                // Prefer selecting the latest run from the refreshed project-wide list.
                var lastId = results[^1].RunId;
                SelectedRunItem = Runs.FirstOrDefault(r => r.Run.Id == lastId) ?? Runs.FirstOrDefault();
            }
        }
        catch (OperationCanceledException)
        {
            StatusText = "已取消";
        }
        catch (Exception ex)
        {
            StatusText = "执行失败：" + ex.Message;
        }
        finally
        {
            EndBusy();
        }
    }

    private void BeginBusy(string text, bool indeterminate = true, double maximum = 100)
    {
        _busyCts?.Cancel();
        _busyCts?.Dispose();
        _busyCts = new CancellationTokenSource();
        IsBusy = true;
        BusyOverlayText = text;
        StatusText = text;
        IsProgressIndeterminate = indeterminate;
        ProgressMaximum = Math.Max(1, maximum);
        ProgressValue = 0;
        ShowBusyCancel = false;
    }

    private void SetBusyProgress(double value, string text)
    {
        IsProgressIndeterminate = false;
        ProgressValue = Math.Min(value, ProgressMaximum);
        BusyOverlayText = text;
        StatusText = text;
    }

    private void EndBusy()
    {
        ShowBusyCancel = false;
        IsBusy = false;
        BusyOverlayText = string.Empty;
        IsProgressIndeterminate = true;
        ProgressValue = 0;
        _busyCts?.Dispose();
        _busyCts = null;
    }

    private async Task ReloadChipFiltersFromAllAsync(Guid preferProjectId)
    {
        _suppressChipFilterReload = true;
        try
        {
            var allChips = await _data.GetChipsAsync();
            ChipFilters.Clear();
            _chipsByModel.Clear();
            foreach (var c in allChips
                         .Where(c => !string.IsNullOrWhiteSpace(c.ModelName))
                         .OrderBy(c => c.ModelName, StringComparer.OrdinalIgnoreCase))
            {
                var name = c.ModelName.Trim();
                if (_chipsByModel.ContainsKey(name)) continue;
                _chipsByModel[name] = c;
                ChipFilters.Add(name);
            }

            if (ChipFilters.Count == 0)
            {
                SelectedChip = "(全部)";
                return;
            }

            var preferred = allChips.FirstOrDefault(c =>
                c.SdkProjectId == preferProjectId && !string.IsNullOrWhiteSpace(c.ModelName));
            var pick = preferred?.ModelName.Trim();
            if (string.IsNullOrWhiteSpace(SelectedChip)
                || (!ChipFilters.Contains(SelectedChip) && SelectedChip != "(全部)"))
            {
                SelectedChip = !string.IsNullOrWhiteSpace(pick) && ChipFilters.Contains(pick)
                    ? pick
                    : ChipFilters[0];
            }
        }
        finally
        {
            _suppressChipFilterReload = false;
        }
    }

    private async Task ReloadFunctionsAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            Functions.Clear();
            FunctionTotalCount = 0;
            FunctionTotalPages = 1;
            FunctionPageInfo = "无项目";
            CanFunctionPrev = false;
            CanFunctionNext = false;
            SelectedFunctionItem = null;
            return;
        }

        var peri = SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;
        var search = string.IsNullOrWhiteSpace(FunctionSearchText) ? null : FunctionSearchText.Trim();
        // Only real inline LL definitions (baseline: 3628). Paginate so "(全部)" is not truncated to ADC-only.
        FunctionTotalCount = await _data.CountFunctionsAsync(
            sdkProjectId: pid, search: search, peripheralName: peri, form: InlineForm);
        FunctionTotalPages = Math.Max(1, (int)Math.Ceiling(FunctionTotalCount / (double)FunctionPageSize));
        if (FunctionPageIndex > FunctionTotalPages) FunctionPageIndex = FunctionTotalPages;
        if (FunctionPageIndex < 1) FunctionPageIndex = 1;

        var skip = (FunctionPageIndex - 1) * FunctionPageSize;
        var list = await _data.GetFunctionsAsync(
            sdkProjectId: pid,
            search: search,
            peripheralName: peri,
            form: InlineForm,
            skip: skip,
            take: FunctionPageSize);

        Functions.Clear();
        foreach (var f in list)
        {
            var item = new FunctionPickItem(f, _checkedFunctionIds.Contains(f.Id));
            item.SelectionChanged += OnFunctionItemSelectionChanged;
            Functions.Add(item);
        }

        var from = FunctionTotalCount == 0 ? 0 : skip + 1;
        var to = Math.Min(skip + Functions.Count, FunctionTotalCount);
        FunctionPageInfo = $"inline {FunctionTotalCount}　第 {FunctionPageIndex}/{FunctionTotalPages} 页　{from}-{to}";
        CanFunctionPrev = FunctionPageIndex > 1;
        CanFunctionNext = FunctionPageIndex < FunctionTotalPages;
        SelectedFunctionItem = Functions.FirstOrDefault();
        RefreshAllOnPageFlag();
        SyncCheckedCount();
    }

    private void OnFunctionItemSelectionChanged(FunctionPickItem item)
    {
        if (item.IsSelected) _checkedFunctionIds.Add(item.Function.Id);
        else _checkedFunctionIds.Remove(item.Function.Id);
        SyncCheckedCount();
        RefreshAllOnPageFlag();
    }

    private void SyncCheckedCount() => CheckedCountText = $"已勾选 {_checkedFunctionIds.Count}";

    private void RefreshAllOnPageFlag()
    {
        _suppressAllSelectedSync = true;
        IsAllOnPageSelected = Functions.Count > 0 && Functions.All(x => x.IsSelected);
        _suppressAllSelectedSync = false;
    }

    private async Task ReloadCasesAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            Cases.Clear();
            CaseTotalCount = 0;
            CaseTotalPages = 1;
            CasePageInfo = "无项目";
            CanCasePrev = false;
            CanCaseNext = false;
            return;
        }

        var peri = CasePeripheralFilter();
        var search = string.IsNullOrWhiteSpace(CaseSearchText) ? null : CaseSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedCaseStatusFilter);
        var skip = Math.Max(0, (CasePageIndex - 1) * CasePageSize);
        var (list, total) = await _store.ListPagedAsync(pid, peri, search, skip, CasePageSize, status);
        CaseTotalCount = total;
        CaseTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, CasePageSize)));
        if (CasePageIndex > CaseTotalPages) CasePageIndex = CaseTotalPages;
        if (CasePageIndex < 1) CasePageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        CasePageInfo = $"共 {total} 条　第 {CasePageIndex}/{CaseTotalPages} 页　{from}-{to}";
        CanCasePrev = CasePageIndex > 1;
        CanCaseNext = CasePageIndex < CaseTotalPages;

        var selectedId = SelectedCaseItem?.Case.Id;
        Cases.Clear();
        foreach (var c in list)
        {
            var item = new CasePickItem(c, _checkedCaseIds.Contains(c.Id));
            item.SelectionChanged += OnCaseItemSelectionChanged;
            Cases.Add(item);
        }
        SelectedCaseItem = Cases.FirstOrDefault(x => x.Case.Id == selectedId) ?? Cases.FirstOrDefault();
        RefreshCaseSelectionUi();
    }

    private string? CasePeripheralFilter() => SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;

    private static string? NormalizeStatusFilter(string? selected) =>
        string.IsNullOrWhiteSpace(selected) || selected == "全部状态" ? null : selected.Trim();

    private async Task<IReadOnlyList<LlTestCase>> LoadFilteredCasesAsync()
    {
        if (ActiveProjectId is not Guid pid) return Array.Empty<LlTestCase>();
        var search = string.IsNullOrWhiteSpace(CaseSearchText) ? null : CaseSearchText.Trim();
        return await _store.ListFilteredAsync(pid, CasePeripheralFilter(), search, NormalizeStatusFilter(SelectedCaseStatusFilter));
    }

    private void OnCaseItemSelectionChanged(CasePickItem item)
    {
        if (item.IsSelected)
            _checkedCaseIds.Add(item.Case.Id);
        else
            _checkedCaseIds.Remove(item.Case.Id);
        RefreshCaseSelectionUi();
    }

    private IReadOnlyList<Guid> GetSelectedCaseIds()
    {
        if (_checkedCaseIds.Count > 0)
            return _checkedCaseIds.ToList();
        var onPage = Cases.Where(c => c.IsSelected).Select(c => c.Case.Id).ToList();
        if (onPage.Count > 0)
            return onPage;
        return SelectedCase is not null ? new[] { SelectedCase.Id } : Array.Empty<Guid>();
    }

    private void RefreshCaseSelectionUi(bool updateAllFlag = true)
    {
        var crossPage = _checkedCaseIds.Count;
        var onPage = Cases.Count(c => c.IsSelected);
        CaseCheckedCountText = crossPage > 0
            ? $"已勾选 {crossPage} 条（含跨页）"
            : $"已勾选用例 {onPage}";
        if (!updateAllFlag) return;
        _suppressCaseAllSelectedSync = true;
        IsAllCasesSelected = Cases.Count > 0 && Cases.All(c => c.IsSelected);
        _suppressCaseAllSelectedSync = false;
    }

    private async Task ReloadRunsAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            Runs.Clear();
            SelectedRunItem = null;
            RunTotalCount = 0;
            RunTotalPages = 1;
            RunPageInfo = "无项目";
            CanRunPrev = false;
            CanRunNext = false;
            return;
        }

        var search = string.IsNullOrWhiteSpace(RunSearchText) ? null : RunSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedRunStatusFilter);
        var skip = Math.Max(0, (RunPageIndex - 1) * RunPageSize);
        var (list, total) = await _store.ListRunsPagedAsync(pid, search, skip, RunPageSize, status);
        RunTotalCount = total;
        RunTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, RunPageSize)));
        if (RunPageIndex > RunTotalPages) RunPageIndex = RunTotalPages;
        if (RunPageIndex < 1) RunPageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        RunPageInfo = $"共 {total} 条　第 {RunPageIndex}/{RunTotalPages} 页　{from}-{to}";
        CanRunPrev = RunPageIndex > 1;
        CanRunNext = RunPageIndex < RunTotalPages;

        var selectedId = SelectedRunItem?.Run.Id;
        Runs.Clear();
        foreach (var r in list)
        {
            var item = new RunPickItem(r);
            item.SelectionChanged += _ => RefreshRunSelectionUi();
            Runs.Add(item);
        }

        SelectedRunItem = Runs.FirstOrDefault(x => x.Run.Id == selectedId) ?? Runs.FirstOrDefault();
        RefreshRunSelectionUi();
    }
}

public sealed class RunPickItem : ObservableObject
{
    private bool _isSelected;

    public RunPickItem(LlTestRun run) => Run = run;

    public LlTestRun Run { get; }
    public string Status => Run.Status;
    public string CaseName => Run.TestCase?.Name ?? "—";
    public int DurationMs => Run.DurationMs;

    public bool IsSelected
    {
        get => _isSelected;
        set
        {
            if (SetProperty(ref _isSelected, value))
                SelectionChanged?.Invoke(this);
        }
    }

    public event Action<RunPickItem>? SelectionChanged;
}

public sealed class FunctionPickItem : ObservableObject
{
    private bool _isSelected;

    public FunctionPickItem(LlFunction function, bool isSelected)
    {
        Function = function;
        _isSelected = isSelected;
    }

    public LlFunction Function { get; }
    public string PeripheralName => Function.PeripheralName ?? "";
    public string FunctionName => Function.FunctionName;

    public bool IsSelected
    {
        get => _isSelected;
        set
        {
            if (SetProperty(ref _isSelected, value))
                SelectionChanged?.Invoke(this);
        }
    }

    public event Action<FunctionPickItem>? SelectionChanged;
}

public sealed class CasePickItem : ObservableObject
{
    private bool _isSelected;

    public CasePickItem(LlTestCase testCase, bool isSelected = false)
    {
        Case = testCase;
        _isSelected = isSelected;
    }

    public LlTestCase Case { get; }
    public string Name => Case.Name;
    public string FunctionName => Case.FunctionName;
    public string? PeripheralName => Case.PeripheralName;
    public string Status => Case.Status;

    public bool IsSelected
    {
        get => _isSelected;
        set
        {
            if (SetProperty(ref _isSelected, value))
                SelectionChanged?.Invoke(this);
        }
    }

    public event Action<CasePickItem>? SelectionChanged;
}
