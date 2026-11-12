using System.Collections.ObjectModel;
using System.IO;
using System.Text;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class AutomationTestViewModel : ObservableObject
{
    private readonly ILLTestEngine _engine;
    private readonly ILlTestCaseStore _store;
    private readonly ICompilerService _compiler;
    private readonly IAppDataService _data;
    private readonly ISdkProjectService _projects;
    private CancellationTokenSource? _runCts;

    public ObservableCollection<string> PeripheralFilters { get; } = new();
    public ObservableCollection<LlFunction> Functions { get; } = new();
    public ObservableCollection<LlTestCase> Cases { get; } = new();
    public ObservableCollection<LlTestRun> Runs { get; } = new();
    public ObservableCollection<string> LogLines { get; } = new();
    public ObservableCollection<int> FunctionPageSizeOptions { get; } = new() { 50, 100, 200, 300 };

    [ObservableProperty] private string _selectedPeripheral = "(全部)";
    [ObservableProperty] private LlFunction? _selectedFunction;
    [ObservableProperty] private LlTestCase? _selectedCase;
    [ObservableProperty] private LlTestRun? _selectedRun;
    [ObservableProperty] private string _clangPath = string.Empty;
    [ObservableProperty] private string _compilerSummary = "尚未检查编译环境";
    [ObservableProperty] private string _caseEditorJson = string.Empty;
    [ObservableProperty] private string _resultDetail = string.Empty;
    [ObservableProperty] private string _statusText = "就绪（虚拟环境测试，非真实硬件验证）";
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private Guid? _activeProjectId;
    [ObservableProperty] private int _functionPageIndex = 1;
    [ObservableProperty] private int _functionPageSize = 100;
    [ObservableProperty] private int _functionTotalCount;
    [ObservableProperty] private int _functionTotalPages = 1;
    [ObservableProperty] private string _functionPageInfo = string.Empty;
    [ObservableProperty] private bool _canFunctionPrev;
    [ObservableProperty] private bool _canFunctionNext;

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

    [RelayCommand]
    public async Task RefreshAsync()
    {
        var projects = await _projects.GetAllAsync();
        var project = projects.FirstOrDefault(p => p.IsActive) ?? projects.FirstOrDefault();
        ActiveProjectId = project?.Id;
        if (project is null)
        {
            StatusText = "无 SDK 项目";
            return;
        }

        PeripheralFilters.Clear();
        PeripheralFilters.Add("(全部)");
        foreach (var p in await _data.GetPeripheralsAsync(project.Id))
            PeripheralFilters.Add(p.Name);
        if (!PeripheralFilters.Contains(SelectedPeripheral))
            SelectedPeripheral = "(全部)";

        await ReloadFunctionsAsync();
        await ReloadCasesAsync();
        await ReloadRunsAsync();
        await CheckCompilerAsync();
    }

    [RelayCommand]
    private async Task CheckCompilerAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        var env = await _engine.CheckCompilerAsync(pid);
        ClangPath = env.ClangPath ?? ClangPath;
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
    private void BrowseClang()
    {
        var dlg = new OpenFileDialog
        {
            Filter = "clang.exe|clang.exe|All|*.*",
            Title = "选择 clang.exe"
        };
        if (dlg.ShowDialog() == true)
            ClangPath = dlg.FileName;
    }

    [RelayCommand]
    private async Task FetchEmbeddedClangAsync()
    {
        if (IsBusy) return;
        IsBusy = true;
        try
        {
            StatusText = "正在获取内置 Clang（首次约 350MB，需联网）…";
            var progress = new Progress<string>(m =>
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    StatusText = m;
                    LogLines.Insert(0, $"[{DateTime.Now:HH:mm:ss}] {m}");
                    if (LogLines.Count > 300) LogLines.RemoveAt(LogLines.Count - 1);
                });
            });
            var result = await _compiler.EnsureEmbeddedClangAsync(progress);
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
        finally { IsBusy = false; }
    }

    [RelayCommand]
    private async Task GenerateCasesAsync()
    {
        if (SelectedFunction is null)
        {
            StatusText = "请先选择 LL 函数";
            return;
        }
        IsBusy = true;
        try
        {
            var generated = await _engine.GenerateCasesAsync(SelectedFunction.Id);
            var n = 0;
            foreach (var g in generated)
            {
                await _store.UpsertAsync(g);
                n++;
            }
            StatusText = $"已生成并保存 {n} 条用例（含读写成对/清标志草稿，可编辑）。";
            await ReloadCasesAsync();
        }
        catch (Exception ex)
        {
            StatusText = "生成失败：" + ex.Message;
        }
        finally { IsBusy = false; }
    }

    [RelayCommand]
    private async Task GeneratePeripheralBatchAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "无 SDK 项目";
            return;
        }
        if (string.IsNullOrWhiteSpace(SelectedPeripheral) || SelectedPeripheral == "(全部)")
        {
            StatusText = "请先在下拉框选择具体外设（不要选「全部」）";
            return;
        }
        IsBusy = true;
        try
        {
            StatusText = $"正在批量生成 {SelectedPeripheral} 用例…";
            var generated = await _engine.GenerateCasesForPeripheralAsync(pid, SelectedPeripheral, maxFunctions: 40);
            var n = 0;
            foreach (var g in generated)
            {
                await _store.UpsertAsync(g);
                n++;
            }
            StatusText = $"外设 {SelectedPeripheral}：已批量生成并保存 {n} 条（最多 40 个函数；含写读成对）。";
            await ReloadCasesAsync();
        }
        catch (Exception ex)
        {
            StatusText = "批量生成失败：" + ex.Message;
        }
        finally { IsBusy = false; }
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
        if (SelectedCase is null) return;
        await _store.DeleteAsync(SelectedCase.Id);
        StatusText = "已删除用例";
        await ReloadCasesAsync();
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
        var json = await _store.ExportJsonAsync(Cases.Select(c => c.Id));
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
        if (SelectedCase is null) return;
        await RunInternalAsync(new[] { SelectedCase.Id });
    }

    [RelayCommand]
    private async Task RunReadyBatchAsync()
    {
        var ids = Cases.Where(c => c.Status == "Ready").Select(c => c.Id).ToList();
        if (ids.Count == 0)
        {
            StatusText = "当前列表无 Ready 状态用例（可先批量生成，或把 Draft 改成 Ready）";
            return;
        }
        await RunInternalAsync(ids);
    }

    [RelayCommand]
    private async Task RunAllListedAsync()
    {
        var ids = Cases.Select(c => c.Id).ToList();
        if (ids.Count == 0)
        {
            StatusText = "当前列表无用例";
            return;
        }
        await RunInternalAsync(ids);
    }

    [RelayCommand]
    private async Task MarkListedReadyAsync()
    {
        var n = 0;
        foreach (var c in Cases.Where(x => x.Status != "Ready").ToList())
        {
            var edit = Infrastructure.TestEngine.LlTestCaseStore.ToEdit(c);
            edit.Status = "Ready";
            await _store.UpsertAsync(edit);
            n++;
        }
        StatusText = $"已将当前列表中 {n} 条标为 Ready";
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private void CancelRun()
    {
        _runCts?.Cancel();
        StatusText = "正在取消…";
    }

    partial void OnSelectedPeripheralChanged(string value)
    {
        FunctionPageIndex = 1;
        _ = ReloadFunctionsAsync();
        _ = ReloadCasesAsync();
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

    partial void OnSelectedCaseChanged(LlTestCase? value)
    {
        if (value is null)
        {
            CaseEditorJson = string.Empty;
            return;
        }
        var edit = Infrastructure.TestEngine.LlTestCaseStore.ToEdit(value);
        CaseEditorJson = System.Text.Json.JsonSerializer.Serialize(edit, new System.Text.Json.JsonSerializerOptions
        {
            WriteIndented = true,
            PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
        });
    }

    partial void OnSelectedRunChanged(LlTestRun? value)
    {
        if (value is null)
        {
            ResultDetail = string.Empty;
            return;
        }

        static string Flag(bool ok, string yes, string no) => ok ? yes : no;
        var sb = new StringBuilder();
        sb.AppendLine("======== 运行摘要（虚拟环境，非真实硬件）========");
        sb.AppendLine($"状态        : {value.Status}");
        sb.AppendLine($"编译        : {Flag(value.CompileSucceeded, "通过", "未通过")}");
        sb.AppendLine($"执行        : {Flag(value.ExecuteCompleted, "完成", "未完成")}");
        sb.AppendLine($"断言        : {Flag(value.AssertionsPassed, "通过", "未通过")}");
        sb.AppendLine($"硬件行为模拟: {Flag(value.HardwareBehaviorSimulated, "是", "否")}");
        sb.AppendLine($"返回值      : {value.ReturnValueText ?? "—"}");
        sb.AppendLine($"耗时        : {value.DurationMs} ms");
        sb.AppendLine($"失败原因    : {value.FailureReason ?? "—"}");
        sb.AppendLine();
        sb.AppendLine("======== 执行日志 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(value.ExecutionLog) ? "（无）" : value.ExecutionLog.Trim());
        sb.AppendLine();
        sb.AppendLine("======== 编译日志 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(value.CompileLog) ? "（无）" : value.CompileLog.Trim());
        sb.AppendLine();
        sb.AppendLine("======== 断言结果 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(value.AssertionResultsJson) ? "（无）" : value.AssertionResultsJson.Trim());
        sb.AppendLine();
        sb.AppendLine("======== 阶段 / 访问轨迹 ========");
        sb.AppendLine(string.IsNullOrWhiteSpace(value.StagesJson) ? "阶段：（无）" : "阶段: " + value.StagesJson.Trim());
        sb.AppendLine(string.IsNullOrWhiteSpace(value.AccessTraceJson) ? "轨迹：（无）" : "轨迹: " + value.AccessTraceJson.Trim());
        ResultDetail = sb.ToString();
    }

    private async Task RunInternalAsync(IReadOnlyList<Guid> ids)
    {
        IsBusy = true;
        _runCts = new CancellationTokenSource();
        LogLines.Clear();
        var progress = new Progress<string>(m =>
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                LogLines.Insert(0, $"[{DateTime.Now:HH:mm:ss}] {m}");
                if (LogLines.Count > 300) LogLines.RemoveAt(LogLines.Count - 1);
            });
        });
        try
        {
            StatusText = "测试执行中（虚拟 MCU，非真实硬件）…";
            var results = await _engine.RunManyAsync(ids, progress, _runCts.Token);
            var passed = results.Count(r => r.Status == Core.Enums.LlTestRunStatus.Passed);
            StatusText = $"完成：{passed}/{results.Count} Passed（虚拟环境结果）";
            await ReloadRunsAsync();
            if (results.Count > 0)
            {
                // Prefer selecting the latest run from the refreshed project-wide list.
                var lastId = results[^1].RunId;
                SelectedRun = Runs.FirstOrDefault(r => r.Id == lastId) ?? Runs.FirstOrDefault();
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
            IsBusy = false;
            _runCts = null;
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
            return;
        }

        var peri = SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;
        // Only real inline LL definitions (baseline: 3628). Paginate so "(全部)" is not truncated to ADC-only.
        const string inlineForm = "inline_definition";
        FunctionTotalCount = await _data.CountFunctionsAsync(
            sdkProjectId: pid, peripheralName: peri, form: inlineForm);
        FunctionTotalPages = Math.Max(1, (int)Math.Ceiling(FunctionTotalCount / (double)FunctionPageSize));
        if (FunctionPageIndex > FunctionTotalPages) FunctionPageIndex = FunctionTotalPages;
        if (FunctionPageIndex < 1) FunctionPageIndex = 1;

        var skip = (FunctionPageIndex - 1) * FunctionPageSize;
        var list = await _data.GetFunctionsAsync(
            sdkProjectId: pid,
            peripheralName: peri,
            form: inlineForm,
            skip: skip,
            take: FunctionPageSize);

        Functions.Clear();
        foreach (var f in list) Functions.Add(f);

        var from = FunctionTotalCount == 0 ? 0 : skip + 1;
        var to = Math.Min(skip + Functions.Count, FunctionTotalCount);
        FunctionPageInfo = $"inline {FunctionTotalCount}　第 {FunctionPageIndex}/{FunctionTotalPages} 页　{from}-{to}";
        CanFunctionPrev = FunctionPageIndex > 1;
        CanFunctionNext = FunctionPageIndex < FunctionTotalPages;
        SelectedFunction = Functions.FirstOrDefault();
    }

    private async Task ReloadCasesAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        var peri = SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;
        var list = await _store.ListAsync(pid, peri);
        Cases.Clear();
        foreach (var c in list) Cases.Add(c);
        SelectedCase = Cases.FirstOrDefault();
    }

    private async Task ReloadRunsAsync()
    {
        // Project-wide recent runs so batch execution shows every case result, not only the selected case.
        if (ActiveProjectId is not Guid pid)
        {
            Runs.Clear();
            SelectedRun = null;
            return;
        }

        var list = await _store.ListRunsAsync(sdkProjectId: pid, take: 300);
        Runs.Clear();
        foreach (var r in list) Runs.Add(r);
        SelectedRun = Runs.FirstOrDefault();
    }
}
