using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class TestManagementViewModel : ObservableObject
{
    private readonly ITestPlanStore _plans;
    private readonly ITestSuiteStore _suites;
    private readonly ITestBatchService _batches;
    private readonly ITestAnalyticsService _analytics;
    private readonly ITestReportService _reports;
    private readonly ILlTestCaseStore _cases;
    private readonly ISdkProjectService _projects;
    private readonly IAppDataService _data;
    private CancellationTokenSource? _batchCts;

    public ObservableCollection<TestPlan> Plans { get; } = new();
    public ObservableCollection<TestSuite> Suites { get; } = new();
    public ObservableCollection<LlTestCase> AvailableCases { get; } = new();
    public ObservableCollection<Guid> SelectedCaseIds { get; } = new();
    public ObservableCollection<TestBatchRun> History { get; } = new();
    public ObservableCollection<FailureAnalysisItem> Failures { get; } = new();
    public ObservableCollection<TestReportArtifact> Artifacts { get; } = new();
    public ObservableCollection<string> PeripheralFilters { get; } = new();
    public ObservableCollection<string> SectionTabs { get; } = new()
    {
        "测试计划", "测试套件", "执行历史", "统计覆盖率", "失败分析", "报告管理"
    };

    [ObservableProperty] private string _selectedSection = "测试计划";
    [ObservableProperty] private Guid? _activeProjectId;
    [ObservableProperty] private TestPlan? _selectedPlan;
    [ObservableProperty] private TestSuite? _selectedSuite;
    [ObservableProperty] private TestBatchRun? _selectedBatch;
    [ObservableProperty] private FailureAnalysisItem? _selectedFailure;
    [ObservableProperty] private string _planName = string.Empty;
    [ObservableProperty] private string _planChip = "TAE32G58xx";
    [ObservableProperty] private string _planPeripheral = "(全部)";
    [ObservableProperty] private string _planTestType = "VirtualMcu";
    [ObservableProperty] private string _suiteName = string.Empty;
    [ObservableProperty] private string _suitePeripheral = "(全部)";
    [ObservableProperty] private string _statsText = string.Empty;
    [ObservableProperty] private string _coverageText = string.Empty;
    [ObservableProperty] private string _failureDetail = string.Empty;
    [ObservableProperty] private string _statusText = "就绪（虚拟环境测试管理，非真实硬件）";
    [ObservableProperty] private string _progressText = string.Empty;
    [ObservableProperty] private double _progressPercent;
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private string _selectedReportFormat = "Html";

    public TestManagementViewModel(
        ITestPlanStore plans,
        ITestSuiteStore suites,
        ITestBatchService batches,
        ITestAnalyticsService analytics,
        ITestReportService reports,
        ILlTestCaseStore cases,
        ISdkProjectService projects,
        IAppDataService data)
    {
        _plans = plans;
        _suites = suites;
        _batches = batches;
        _analytics = analytics;
        _reports = reports;
        _cases = cases;
        _projects = projects;
        _data = data;
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
        if (string.IsNullOrWhiteSpace(PlanPeripheral))
            PlanPeripheral = "(全部)";

        await ReloadPlansAsync();
        await ReloadSuitesAsync();
        await ReloadCasesAsync();
        await ReloadHistoryAsync();
        await ReloadStatsAsync();
        await ReloadFailuresAsync();
        await ReloadArtifactsAsync();
        StatusText = "测试管理已刷新（虚拟 MCU 数据）";
    }

    [RelayCommand]
    private async Task SavePlanAsync()
    {
        if (ActiveProjectId is not Guid pid || string.IsNullOrWhiteSpace(PlanName)) return;
        await _plans.UpsertAsync(new TestPlanEditModel
        {
            Id = SelectedPlan?.Id,
            SdkProjectId = pid,
            Name = PlanName.Trim(),
            ChipModelName = PlanChip,
            PeripheralFilter = string.IsNullOrWhiteSpace(PlanPeripheral) || PlanPeripheral == "(全部)"
                ? null
                : PlanPeripheral,
            TestType = PlanTestType,
            SdkVersion = (await _projects.GetByIdAsync(pid))?.Version,
            Status = "Active"
        });
        StatusText = "测试计划已保存";
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task DuplicatePlanAsync()
    {
        if (SelectedPlan is null) return;
        await _plans.DuplicateAsync(SelectedPlan.Id);
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task ArchivePlanAsync()
    {
        if (SelectedPlan is null) return;
        await _plans.ArchiveAsync(SelectedPlan.Id);
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task SaveSuiteAsync()
    {
        if (ActiveProjectId is not Guid pid || string.IsNullOrWhiteSpace(SuiteName)) return;
        await _suites.UpsertAsync(new TestSuiteEditModel
        {
            Id = SelectedSuite?.Id,
            SdkProjectId = pid,
            TestPlanId = SelectedPlan?.Id,
            Name = SuiteName.Trim(),
            PeripheralName = string.IsNullOrWhiteSpace(SuitePeripheral) || SuitePeripheral == "(全部)"
                ? null
                : SuitePeripheral,
            TestCaseIds = SelectedCaseIds.ToList(),
            Status = "Active"
        });
        StatusText = $"套件已保存（{SelectedCaseIds.Count} 个真实用例）";
        await ReloadSuitesAsync();
    }

    [RelayCommand]
    private void ToggleCaseSelection(LlTestCase? c)
    {
        if (c is null) return;
        if (SelectedCaseIds.Contains(c.Id)) SelectedCaseIds.Remove(c.Id);
        else SelectedCaseIds.Add(c.Id);
    }

    [RelayCommand]
    private async Task RunSuiteAsync()
    {
        if (ActiveProjectId is not Guid pid || SelectedSuite is null) return;
        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            TestSuiteId = SelectedSuite.Id,
            TestPlanId = SelectedPlan?.Id,
            ScopeKind = "Suite",
            ScopeValue = SelectedSuite.Name
        });
    }

    [RelayCommand]
    private async Task RunPlanAsync()
    {
        if (ActiveProjectId is not Guid pid || SelectedPlan is null) return;
        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            TestPlanId = SelectedPlan.Id,
            ScopeKind = "Plan",
            ScopeValue = SelectedPlan.Name
        });
    }

    [RelayCommand]
    private async Task RunPeripheralAsync()
    {
        if (ActiveProjectId is not Guid pid
            || string.IsNullOrWhiteSpace(SuitePeripheral)
            || SuitePeripheral == "(全部)")
        {
            StatusText = "请选择具体外设后再按外设执行";
            return;
        }
        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            ScopeKind = "Peripheral",
            ScopeValue = SuitePeripheral
        });
    }

    [RelayCommand]
    private async Task RetryFailedAsync()
    {
        if (ActiveProjectId is not Guid pid || SelectedBatch is null) return;
        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            ScopeKind = "FailedRetry",
            RetryFailedOnly = true,
            SourceBatchRunId = SelectedBatch.Id,
            TestPlanId = SelectedBatch.TestPlanId,
            TestSuiteId = SelectedBatch.TestSuiteId
        });
    }

    [RelayCommand]
    private void CancelBatch()
    {
        _batchCts?.Cancel();
        StatusText = "正在取消批量执行…";
    }

    [RelayCommand]
    private async Task ExportReportAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        IsBusy = true;
        try
        {
            var fmt = SelectedReportFormat.ToLowerInvariant() switch
            {
                "pdf" => TestReportFormat.Pdf,
                "excel" or "csv" => TestReportFormat.Excel,
                _ => TestReportFormat.Html
            };
            var result = await _reports.GenerateAsync(new TestReportRequest
            {
                SdkProjectId = pid,
                BatchRunId = SelectedBatch?.Id,
                Format = fmt,
                Title = $"TAE32 LL Virtual Test — {SelectedPlan?.Name ?? "项目汇总"}"
            });
            StatusText = result.Message;
            await ReloadArtifactsAsync();
            if (File.Exists(result.FilePath))
                Process.Start(new ProcessStartInfo { FileName = result.FilePath, UseShellExecute = true });
        }
        catch (Exception ex)
        {
            StatusText = "导出失败：" + ex.Message;
        }
        finally { IsBusy = false; }
    }

    [RelayCommand]
    private void OpenSource(FailureAnalysisItem? item)
    {
        if (item?.SourceFile is null || !File.Exists(item.SourceFile))
        {
            StatusText = "源码文件不存在或路径未知";
            return;
        }
        Process.Start(new ProcessStartInfo { FileName = item.SourceFile, UseShellExecute = true });
    }

    partial void OnSelectedPlanChanged(TestPlan? value)
    {
        if (value is null) return;
        PlanName = value.Name;
        PlanChip = value.ChipModelName ?? "TAE32G58xx";
        PlanPeripheral = string.IsNullOrWhiteSpace(value.PeripheralFilter) ? "(全部)" : value.PeripheralFilter;
        PlanTestType = value.TestType ?? "VirtualMcu";
        _ = ReloadSuitesAsync();
    }

    partial void OnSelectedSuiteChanged(TestSuite? value)
    {
        if (value is null) return;
        SuiteName = value.Name;
        SuitePeripheral = string.IsNullOrWhiteSpace(value.PeripheralName) ? "(全部)" : value.PeripheralName;
        _ = LoadSuiteCaseIdsAsync(value.Id);
    }

    partial void OnSelectedFailureChanged(FailureAnalysisItem? value)
    {
        if (value is null)
        {
            FailureDetail = string.Empty;
            return;
        }
        FailureDetail =
            $"用例: {value.CaseName}\n函数: {value.FunctionName}\n源码: {value.SourceFile}\n状态: {value.Status}\n原因: {value.FailureReason}\n寄存器: {value.RelatedRegisters}\n\n--- 编译摘录 ---\n{value.CompileLogExcerpt}\n\n--- 断言 ---\n{value.AssertionResultsJson}\n\n--- 轨迹 ---\n{value.AccessTraceJson}";
    }

    private async Task LoadSuiteCaseIdsAsync(Guid suiteId)
    {
        SelectedCaseIds.Clear();
        foreach (var id in await _suites.GetCaseIdsAsync(suiteId))
            SelectedCaseIds.Add(id);
    }

    private async Task RunBatchInternalAsync(TestBatchRunRequest request)
    {
        IsBusy = true;
        _batchCts = new CancellationTokenSource();
        var progress = new Progress<TestBatchProgress>(p =>
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                ProgressPercent = p.Percent;
                ProgressText = $"{p.Completed}/{p.Total} {p.CurrentCaseName}";
                StatusText = p.Message;
            });
        });
        try
        {
            var batch = await _batches.RunAsync(request, progress, _batchCts.Token);
            StatusText = $"批次完成：{batch.Status} Passed={batch.PassedCount} Failed={batch.FailedCount} Error={batch.ErrorCount}（虚拟环境）";
            SelectedBatch = batch;
            await ReloadHistoryAsync();
            await ReloadStatsAsync();
            await ReloadFailuresAsync();
        }
        catch (OperationCanceledException)
        {
            StatusText = "批量执行已取消";
        }
        catch (Exception ex)
        {
            StatusText = "批量执行失败：" + ex.Message;
        }
        finally
        {
            IsBusy = false;
            _batchCts = null;
        }
    }

    private async Task ReloadPlansAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        Plans.Clear();
        foreach (var p in await _plans.ListAsync(pid, includeArchived: true))
            Plans.Add(p);
        SelectedPlan ??= Plans.FirstOrDefault();
    }

    private async Task ReloadSuitesAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        Suites.Clear();
        foreach (var s in await _suites.ListAsync(pid, SelectedPlan?.Id))
            Suites.Add(s);
        SelectedSuite ??= Suites.FirstOrDefault();
    }

    private async Task ReloadCasesAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        AvailableCases.Clear();
        foreach (var c in await _cases.ListAsync(pid))
            AvailableCases.Add(c);
    }

    private async Task ReloadHistoryAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        History.Clear();
        foreach (var h in await _batches.ListHistoryAsync(pid))
            History.Add(h);
        SelectedBatch ??= History.FirstOrDefault();
    }

    private async Task ReloadStatsAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        var s = await _analytics.GetStatisticsAsync(pid, SelectedBatch?.Id);
        StatsText =
            $"用例总数 {s.CaseTotal}\n已执行 {s.ExecutedRuns}\n通过 {s.Passed} / 失败 {s.Failed} / 错误 {s.Error} / 跳过 {s.Skipped} / 超时 {s.Timeout}\n通过率 {s.PassRate:F1}%\n编译失败率 {s.CompileFailRate:F1}%\n平均耗时 {s.AverageDurationMs:F0} ms";
        var c = await _analytics.GetCoverageAsync(pid);
        CoverageText =
            $"LL 函数覆盖率: {Pct(c.FunctionCoveragePercent)} ({c.FunctionsCoveredByCases}/{c.FunctionsTotal})\n" +
            $"外设覆盖率: {Pct(c.PeripheralCoveragePercent)} ({c.PeripheralsCoveredByCases}/{c.PeripheralsTotal})\n" +
            $"寄存器访问覆盖率: {Pct(c.RegisterAccessCoveragePercent)} ({c.RegistersTouchedInRuns}/{c.RegistersReferencedInParse})\n" +
            $"位域断言覆盖率: {Pct(c.BitFieldCoveragePercent)} ({c.BitFieldsAsserted}/{c.BitFieldsTotal})\n" +
            $"用例覆盖率: {Pct(c.CaseCoveragePercent)} ({c.CasesExecutedAtLeastOnce}/{c.CasesTotal})\n\n{c.Notes}";
    }

    private async Task ReloadFailuresAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        Failures.Clear();
        foreach (var f in await _analytics.GetFailuresAsync(pid, SelectedBatch?.Id))
            Failures.Add(f);
    }

    private async Task ReloadArtifactsAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        Artifacts.Clear();
        foreach (var a in await _reports.ListArtifactsAsync(pid))
            Artifacts.Add(a);
    }

    private static string Pct(double? v) => v is null ? "N/A" : $"{v:F1}%";
}
