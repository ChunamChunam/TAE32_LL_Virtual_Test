using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Data;
using System.Windows.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.App.Views.Dialogs;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Services;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class TestManagementViewModel : ObservableObject
{
    private readonly ITestPlanStore _plans;
    private readonly ITestSuiteStore _suites;
    private readonly ITestBatchService _batches;
    private readonly ITestAnalyticsService _analytics;
    private readonly ITestReportService _reports;
    private readonly ILlTestCaseStore _cases;
    private readonly ILLTestEngine _engine;
    private readonly ISdkProjectService _projects;
    private readonly IAppDataService _data;
    private CancellationTokenSource? _batchCts;

    public ObservableCollection<TestPlan> Plans { get; } = new();
    public ObservableCollection<TestSuite> Suites { get; } = new();
    public ObservableCollection<LlTestCase> AvailableCases { get; } = new();
    public ObservableCollection<Guid> SelectedCaseIds { get; } = new();
    public ObservableCollection<TestBatchRun> History { get; } = new();
    public ObservableCollection<FailurePickItem> FailureRows { get; } = new();
    public ObservableCollection<TestReportArtifact> Artifacts { get; } = new();
    public ObservableCollection<string> PeripheralFilters { get; } = new();
    public ObservableCollection<int> AvailableCasePageSizeOptions { get; } = new() { 50, 100, 200, 300 };
    public ObservableCollection<string> SectionTabs { get; } = new()
    {
        "测试计划", "测试套件", "执行历史", "统计覆盖率", "失败分析", "报告管理"
    };

    [ObservableProperty] private string _selectedSection = "测试计划";
    [ObservableProperty] private Guid? _activeProjectId;
    [ObservableProperty] private TestPlan? _selectedPlan;
    [ObservableProperty] private TestSuite? _selectedSuite;
    [ObservableProperty] private TestBatchRun? _selectedBatch;
    [ObservableProperty] private FailurePickItem? _selectedFailureRow;
    [ObservableProperty] private string _failureSearchText = string.Empty;
    [ObservableProperty] private int _failurePageIndex = 1;
    [ObservableProperty] private int _failurePageSize = 50;
    [ObservableProperty] private int _failureTotalCount;
    [ObservableProperty] private int _failureTotalPages = 1;
    [ObservableProperty] private string _failurePageInfo = string.Empty;
    [ObservableProperty] private bool _canFailurePrev;
    [ObservableProperty] private bool _canFailureNext;
    [ObservableProperty] private bool _isAllFailuresOnPageSelected;
    private bool _suppressFailureAllSelectedSync;
    [ObservableProperty] private string _planName = string.Empty;
    [ObservableProperty] private string _planChip = "TAE32G58xx";
    [ObservableProperty] private string _planPeripheral = "(全部)";
    [ObservableProperty] private string _planTestType = "VirtualMcu";
    [ObservableProperty] private string _planSearchText = string.Empty;
    [ObservableProperty] private int _planPageIndex = 1;
    [ObservableProperty] private int _planPageSize = 50;
    [ObservableProperty] private int _planTotalCount;
    [ObservableProperty] private int _planTotalPages = 1;
    [ObservableProperty] private string _planPageInfo = string.Empty;
    [ObservableProperty] private bool _canPlanPrev;
    [ObservableProperty] private bool _canPlanNext;
    public ObservableCollection<string> PlanStatusFilterOptions { get; } = new()
    {
        "全部状态",
        "仅活动",
        "仅归档"
    };
    public ObservableCollection<string> CaseStatusFilterOptions { get; } = new()
    {
        "全部状态",
        nameof(LlTestCaseStatus.Draft),
        nameof(LlTestCaseStatus.Ready),
        nameof(LlTestCaseStatus.Disabled),
        nameof(LlTestCaseStatus.Unsupported)
    };
    public ObservableCollection<string> BatchStatusFilterOptions { get; } = new()
    {
        "全部状态",
        "Running",
        "Completed",
        "Cancelled",
        "Error"
    };
    public ObservableCollection<string> FailureStatusFilterOptions { get; } = new()
    {
        "全部状态",
        nameof(LlTestRunStatus.Failed),
        nameof(LlTestRunStatus.Error),
        nameof(LlTestRunStatus.Timeout),
        nameof(LlTestRunStatus.Skipped),
        nameof(LlTestRunStatus.StaticAnalysisFailed)
    };
    [ObservableProperty] private string _selectedPlanStatusFilter = "全部状态";
    [ObservableProperty] private string _selectedAvailableCaseStatusFilter = "全部状态";
    [ObservableProperty] private string _selectedHistoryStatusFilter = "全部状态";
    [ObservableProperty] private string _selectedExportBatchStatusFilter = "全部状态";
    [ObservableProperty] private string _selectedFailureStatusFilter = "全部状态";
    [ObservableProperty] private string _suiteName = string.Empty;
    [ObservableProperty] private string _suitePeripheral = "(全部)";
    [ObservableProperty] private TestStatistics _statistics = new();
    [ObservableProperty] private CoverageStats _coverage = new();
    [ObservableProperty] private string _coverageNotes = string.Empty;
    [ObservableProperty] private string _statsScopeHint = "全项目";
    [ObservableProperty] private string _functionCoverageText = "N/A";
    [ObservableProperty] private string _peripheralCoverageText = "N/A";
    [ObservableProperty] private string _registerCoverageText = "N/A";
    [ObservableProperty] private string _bitFieldCoverageText = "N/A";
    [ObservableProperty] private string _caseCoverageText = "N/A";
    [ObservableProperty] private string _failureDetail = string.Empty;
    [ObservableProperty] private string _statusText = "就绪（虚拟环境测试管理，非真实硬件）";
    [ObservableProperty] private string _progressText = string.Empty;
    [ObservableProperty] private double _progressPercent;
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private string _busyOverlayText = string.Empty;
    [ObservableProperty] private string _selectedReportFormat = "Html";
    public ObservableCollection<TestBatchRun> ExportBatchRows { get; } = new();
    [ObservableProperty] private ICollectionView? _exportBatchTableView;
    public ObservableCollection<string> ExportRunScopeOptions { get; } = new()
    {
        "当前选中批次",
        "自动（已选批次→该批全部；未选→每用例最新）",
        "全项目（每用例最新）",
        "全项目（全部运行历史）"
    };
    [ObservableProperty] private string _selectedExportRunScope = "自动（已选批次→该批全部；未选→每用例最新）";
    [ObservableProperty] private string _exportScopeHint =
        "在下方表格选中一批次；默认「自动」会导出该批全部运行记录（条数与「总数」一致，无上限）。";
    [ObservableProperty] private string _availableCaseSearchText = string.Empty;
    [ObservableProperty] private int _availableCasePageIndex = 1;
    [ObservableProperty] private int _availableCasePageSize = 100;
    [ObservableProperty] private int _availableCaseTotalCount;
    [ObservableProperty] private int _availableCaseTotalPages = 1;
    [ObservableProperty] private string _availableCasePageInfo = string.Empty;
    [ObservableProperty] private bool _canAvailableCasePrev;
    [ObservableProperty] private bool _canAvailableCaseNext;
    [ObservableProperty] private string _historySearchText = string.Empty;
    [ObservableProperty] private int _historyPageIndex = 1;
    [ObservableProperty] private int _historyPageSize = 50;
    [ObservableProperty] private int _historyTotalCount;
    [ObservableProperty] private int _historyTotalPages = 1;
    [ObservableProperty] private string _historyPageInfo = string.Empty;
    [ObservableProperty] private bool _canHistoryPrev;
    [ObservableProperty] private bool _canHistoryNext;
    [ObservableProperty] private string _exportBatchSearchText = string.Empty;
    [ObservableProperty] private int _exportBatchPageIndex = 1;
    [ObservableProperty] private int _exportBatchPageSize = 50;
    [ObservableProperty] private int _exportBatchTotalCount;
    [ObservableProperty] private int _exportBatchTotalPages = 1;
    [ObservableProperty] private string _exportBatchPageInfo = string.Empty;
    [ObservableProperty] private bool _canExportBatchPrev;
    [ObservableProperty] private bool _canExportBatchNext;
    [ObservableProperty] private string _artifactSearchText = string.Empty;
    [ObservableProperty] private int _artifactPageIndex = 1;
    [ObservableProperty] private int _artifactPageSize = 50;
    [ObservableProperty] private int _artifactTotalCount;
    [ObservableProperty] private int _artifactTotalPages = 1;
    [ObservableProperty] private string _artifactPageInfo = string.Empty;
    [ObservableProperty] private bool _canArtifactPrev;
    [ObservableProperty] private bool _canArtifactNext;
    [ObservableProperty] private TestReportArtifact? _selectedArtifact;

    public bool CanExecuteWhileIdle => !IsBusy;

    partial void OnIsBusyChanged(bool value)
    {
        RunPlanCommand.NotifyCanExecuteChanged();
        RunSuiteCommand.NotifyCanExecuteChanged();
        RunPeripheralCommand.NotifyCanExecuteChanged();
        SavePlanCommand.NotifyCanExecuteChanged();
        ExportReportCommand.NotifyCanExecuteChanged();
        ExportSelectedBatchReportCommand.NotifyCanExecuteChanged();
        RefreshCommand.NotifyCanExecuteChanged();
    }

    public TestManagementViewModel(
        ITestPlanStore plans,
        ITestSuiteStore suites,
        ITestBatchService batches,
        ITestAnalyticsService analytics,
        ITestReportService reports,
        ILlTestCaseStore cases,
        ILLTestEngine engine,
        ISdkProjectService projects,
        IAppDataService data)
    {
        _plans = plans;
        _suites = suites;
        _batches = batches;
        _analytics = analytics;
        _reports = reports;
        _cases = cases;
        _engine = engine;
        _projects = projects;
        _data = data;
    }

    [RelayCommand(CanExecute = nameof(CanExecuteWhileIdle))]
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

        // Only load the active tab (+ shared plan list used by suite/run actions).
        await ReloadPlansAsync();
        await ReloadSectionAsync(SelectedSection);
        StatusText = "测试管理已刷新（虚拟 MCU 数据）";
    }

    partial void OnSelectedSectionChanged(string value) => _ = ReloadSectionAsync(value);

    private async Task ReloadSectionAsync(string section)
    {
        switch (section)
        {
            case "测试计划":
                await ReloadPlansAsync();
                break;
            case "测试套件":
                await ReloadSuitesAsync();
                await ReloadCasesAsync();
                break;
            case "执行历史":
                await ReloadHistoryAsync();
                break;
            case "统计覆盖率":
                await ReloadStatsAsync(includeCoverage: true);
                break;
            case "失败分析":
                await ReloadFailuresAsync();
                break;
            case "报告管理":
                await ReloadExportBatchListAsync();
                await ReloadArtifactsAsync();
                break;
        }
    }

    [RelayCommand(CanExecute = nameof(CanExecuteWhileIdle))]
    private async Task SavePlanAsync() => await SavePlanInnerAsync();

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
        StatusText = $"已归档计划：{SelectedPlan.Name}";
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task RestorePlanAsync()
    {
        if (SelectedPlan is null) return;
        await _plans.RestoreAsync(SelectedPlan.Id);
        StatusText = $"已恢复计划为活动：{SelectedPlan.Name}";
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task SearchPlansAsync()
    {
        PlanPageIndex = 1;
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task PlanPreviousPageAsync()
    {
        if (PlanPageIndex <= 1) return;
        PlanPageIndex--;
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task PlanNextPageAsync()
    {
        if (PlanPageIndex >= PlanTotalPages) return;
        PlanPageIndex++;
        await ReloadPlansAsync();
    }

    partial void OnPlanPageSizeChanged(int value)
    {
        PlanPageIndex = 1;
        _ = ReloadPlansAsync();
    }

    partial void OnSelectedPlanStatusFilterChanged(string value)
    {
        PlanPageIndex = 1;
        _ = ReloadPlansAsync();
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
        StatusText = $"套件已选 {SelectedCaseIds.Count} 个用例";
    }

    [RelayCommand]
    private async Task SearchAvailableCasesAsync()
    {
        AvailableCasePageIndex = 1;
        await ReloadCasesAsync();
    }

    partial void OnSuitePeripheralChanged(string value)
    {
        AvailableCasePageIndex = 1;
        _ = ReloadCasesAsync();
    }

    partial void OnAvailableCasePageSizeChanged(int value)
    {
        AvailableCasePageIndex = 1;
        _ = ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task AvailableCasePreviousPageAsync()
    {
        if (AvailableCasePageIndex <= 1) return;
        AvailableCasePageIndex--;
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task AvailableCaseNextPageAsync()
    {
        if (AvailableCasePageIndex >= AvailableCaseTotalPages) return;
        AvailableCasePageIndex++;
        await ReloadCasesAsync();
    }

    [RelayCommand]
    private async Task SearchHistoryAsync()
    {
        HistoryPageIndex = 1;
        await ReloadHistoryAsync();
    }

    partial void OnHistoryPageSizeChanged(int value)
    {
        HistoryPageIndex = 1;
        _ = ReloadHistoryAsync();
    }

    [RelayCommand]
    private async Task HistoryPreviousPageAsync()
    {
        if (HistoryPageIndex <= 1) return;
        HistoryPageIndex--;
        await ReloadHistoryAsync();
    }

    [RelayCommand]
    private async Task HistoryNextPageAsync()
    {
        if (HistoryPageIndex >= HistoryTotalPages) return;
        HistoryPageIndex++;
        await ReloadHistoryAsync();
    }

    [RelayCommand]
    private async Task SearchExportBatchesAsync()
    {
        ExportBatchPageIndex = 1;
        await ReloadExportBatchListAsync();
    }

    partial void OnExportBatchPageSizeChanged(int value)
    {
        ExportBatchPageIndex = 1;
        _ = ReloadExportBatchListAsync();
    }

    [RelayCommand]
    private async Task ExportBatchPreviousPageAsync()
    {
        if (ExportBatchPageIndex <= 1) return;
        ExportBatchPageIndex--;
        await ReloadExportBatchListAsync();
    }

    [RelayCommand]
    private async Task ExportBatchNextPageAsync()
    {
        if (ExportBatchPageIndex >= ExportBatchTotalPages) return;
        ExportBatchPageIndex++;
        await ReloadExportBatchListAsync();
    }

    [RelayCommand]
    private async Task DeleteHistorySelectedAsync()
    {
        if (SelectedBatch is null)
        {
            StatusText = "请先在列表中选中一条批次记录";
            return;
        }

        if (string.Equals(SelectedBatch.Status, "Running", StringComparison.OrdinalIgnoreCase))
        {
            StatusText = "该批次正在 Running，无法删除（请先取消或等待结束）";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除执行历史",
                $"确认删除所选批次？\n状态: {SelectedBatch.Status} · 范围: {SelectedBatch.ScopeKind} · 总数: {SelectedBatch.TotalCount}\n不会删除各用例的 LlTestRun 明细。",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _batches.DeleteManyAsync(new[] { SelectedBatch.Id });
        StatusText = n > 0 ? "已删除所选批次记录" : "未删除（可能为 Running）";
        await ReloadHistoryAsync();
        await ReloadStatsAsync();
        await ReloadFailuresAsync();
    }

    [RelayCommand]
    private async Task DeleteHistoryPageAsync()
    {
        if (ActiveProjectId is null)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (History.Count == 0)
        {
            StatusText = "本页无批次记录";
            return;
        }

        var running = History.Count(h =>
            string.Equals(h.Status, "Running", StringComparison.OrdinalIgnoreCase));
        var deletable = History.Count - running;
        if (deletable == 0)
        {
            StatusText = "本页均为 Running 批次，未删除（请取消执行或等待完成）";
            return;
        }

        var note = running > 0
            ? $"（本页 {running} 条 Running 将跳过）"
            : string.Empty;
        if (!ConfirmDialog.Show(
                "删除执行历史",
                $"确认删除本页 {deletable} 条批次记录？{note}\n不会删除各用例的 LlTestRun 明细。",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _batches.DeleteManyAsync(History.Select(h => h.Id));
        StatusText = n > 0
            ? $"已删除本页 {n} 条批次记录{note}"
            : "未删除任何记录";
        await ReloadHistoryAsync();
        if (SelectedBatch is null)
        {
            await ReloadStatsAsync();
            await ReloadFailuresAsync();
        }
    }

    [RelayCommand]
    private async Task DeleteHistoryAllAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (HistoryTotalCount == 0)
        {
            StatusText = "当前筛选下无批次记录";
            return;
        }

        var scope = string.IsNullOrWhiteSpace(HistorySearchText)
            ? "当前项目下全部批次"
            : $"当前搜索条件下全部 {HistoryTotalCount} 条批次";
        if (!ConfirmDialog.Show(
                "删除执行历史",
                $"确认删除 {scope}？\n不会删除 LlTestRun 明细。Status=Running 的批次将保留。",
                confirmLabel: "删除全部",
                dangerConfirm: true))
            return;

        var search = string.IsNullOrWhiteSpace(HistorySearchText) ? null : HistorySearchText.Trim();
        var status = NormalizeStatusFilter(SelectedHistoryStatusFilter);
        var n = await _batches.DeleteFilteredAsync(pid, search, statusFilter: status);
        HistoryPageIndex = 1;
        StatusText = $"已删除 {n} 条批次记录（Running 未删）";
        await ReloadHistoryAsync();
        await ReloadStatsAsync();
        await ReloadFailuresAsync();
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

    [RelayCommand(CanExecute = nameof(CanExecuteWhileIdle))]
    private async Task RunPlanAsync()
    {
        if (ActiveProjectId is not Guid pid) return;
        if (string.IsNullOrWhiteSpace(PlanName) && SelectedPlan is null)
        {
            StatusText = "请先填写并保存测试计划";
            return;
        }

        IsBusy = true;
        BusyOverlayText = "正在保存测试计划…";
        try
        {
            await SavePlanInnerAsync();
            var plan = SelectedPlan ?? Plans.FirstOrDefault(p => p.Name == PlanName.Trim());
            if (plan is null)
            {
                StatusText = "请先保存测试计划";
                return;
            }

            var periFilter = NormalizePeripheralFilter(plan.PeripheralFilter ?? PlanPeripheral);
            var targets = IsAllPeripherals(periFilter)
                ? PeripheralFilters.Where(p => !IsAllPeripherals(p) && !string.IsNullOrWhiteSpace(p)).ToList()
                : new List<string> { periFilter! };

            var generatedCount = 0;
            var i = 0;
            foreach (var peri in targets)
            {
                i++;
                BusyOverlayText = IsAllPeripherals(periFilter)
                    ? $"正在生成用例：{peri}（{i}/{targets.Count}）…"
                    : $"正在生成用例：{peri}…";
                StatusText = BusyOverlayText;
                await Task.Yield();

                var (_, saved) = await _engine.GenerateAndSaveForPeripheralAsync(pid, peri);
                generatedCount += saved;
            }

            BusyOverlayText = $"已生成 {generatedCount} 条用例，正在批量执行（不限制条数）…";
            StatusText = BusyOverlayText;
            await ReloadCasesAsync();

            await RunBatchInternalAsync(new TestBatchRunRequest
            {
                SdkProjectId = pid,
                TestPlanId = plan.Id,
                ScopeKind = "Plan",
                ScopeValue = IsAllPeripherals(periFilter) ? "(全部)" : periFilter
            }, manageBusyFlag: false);
        }
        catch (Exception ex)
        {
            StatusText = "按计划执行失败：" + ex.Message;
        }
        finally
        {
            IsBusy = false;
            BusyOverlayText = string.Empty;
        }
    }

    private async Task SavePlanInnerAsync()
    {
        if (ActiveProjectId is not Guid pid || string.IsNullOrWhiteSpace(PlanName)) return;
        await _plans.UpsertAsync(new TestPlanEditModel
        {
            Id = SelectedPlan?.Id,
            SdkProjectId = pid,
            Name = PlanName.Trim(),
            ChipModelName = PlanChip,
            PeripheralFilter = NormalizePeripheralFilter(PlanPeripheral) is var p && !IsAllPeripherals(p) ? p : null,
            TestType = PlanTestType,
            SdkVersion = (await _projects.GetByIdAsync(pid))?.Version,
            Status = "Active"
        });
        StatusText = "测试计划已保存";
        await ReloadPlansAsync();
    }

    [RelayCommand]
    private async Task RunPeripheralAsync()
    {
        if (ActiveProjectId is not Guid pid) return;

        // Suite peripheral: concrete = that module; "(全部)" = every peripheral.
        var periFilter = NormalizePeripheralFilter(SuitePeripheral);
        var targets = IsAllPeripherals(periFilter)
            ? PeripheralFilters.Where(p => !IsAllPeripherals(p) && !string.IsNullOrWhiteSpace(p)).ToList()
            : new List<string> { periFilter! };

        if (targets.Count == 0)
        {
            StatusText = "没有可执行的外设";
            return;
        }

        if (IsAllPeripherals(periFilter))
        {
            // Run all cases in project (all peripherals).
            await RunBatchInternalAsync(new TestBatchRunRequest
            {
                SdkProjectId = pid,
                ScopeKind = "Plan",
                ScopeValue = "(全部)",
                TestPlanId = SelectedPlan?.Id
            });
            return;
        }

        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            ScopeKind = "Peripheral",
            ScopeValue = periFilter
        });
    }

    private static TestReportRunScope MapExportRunScope(string? label) => label switch
    {
        "当前选中批次" => TestReportRunScope.SelectedBatchOnly,
        "全项目（全部运行历史）" => TestReportRunScope.ProjectAllRuns,
        "自动（已选批次→该批全部；未选→每用例最新）" or "自动（跟批次选择）" => TestReportRunScope.Auto,
        _ => TestReportRunScope.ProjectLatestPerCase
    };

    private TestReportRunScope ResolveEffectiveExportScope()
    {
        var scope = MapExportRunScope(SelectedExportRunScope);
        return scope == TestReportRunScope.Auto
            ? SelectedBatch is not null ? TestReportRunScope.SelectedBatchOnly : TestReportRunScope.ProjectLatestPerCase
            : scope;
    }

    private void RefreshExportScopeHint()
    {
        var effective = ResolveEffectiveExportScope();
        ExportScopeHint = effective switch
        {
            TestReportRunScope.SelectedBatchOnly when SelectedBatch is not null =>
                $"将导出：{SelectedBatch.ScopeKind} · {SelectedBatch.Status} · 共 {SelectedBatch.TotalCount} 条。",
            TestReportRunScope.SelectedBatchOnly =>
                "请在下表选中一条批次。",
            TestReportRunScope.ProjectAllRuns =>
                "将导出本项目全部历史运行。",
            _ =>
                "未选批次时将导出全项目「每用例最新一次」；要整批导出请选中批次，范围用「当前选中批次」或「自动」。"
        };
        ExportReportCommand.NotifyCanExecuteChanged();
        ExportSelectedBatchReportCommand.NotifyCanExecuteChanged();
    }

    private async Task ReloadExportBatchListAsync()
    {
        ExportBatchRows.Clear();
        if (ActiveProjectId is not Guid pid)
        {
            ExportBatchTotalCount = 0;
            ExportBatchTotalPages = 1;
            ExportBatchPageInfo = "无项目";
            CanExportBatchPrev = false;
            CanExportBatchNext = false;
            RebuildExportBatchTableView();
            return;
        }

        var search = string.IsNullOrWhiteSpace(ExportBatchSearchText) ? null : ExportBatchSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedExportBatchStatusFilter);
        var skip = Math.Max(0, (ExportBatchPageIndex - 1) * ExportBatchPageSize);
        var (list, total) = await _batches.ListHistoryPagedAsync(
            pid, search, skip: skip, take: ExportBatchPageSize, statusFilter: status);
        ExportBatchTotalCount = total;
        ExportBatchTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, ExportBatchPageSize)));
        if (ExportBatchPageIndex > ExportBatchTotalPages) ExportBatchPageIndex = ExportBatchTotalPages;
        if (ExportBatchPageIndex < 1) ExportBatchPageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        ExportBatchPageInfo = $"共 {total} 条　第 {ExportBatchPageIndex}/{ExportBatchTotalPages} 页　{from}-{to}";
        CanExportBatchPrev = ExportBatchPageIndex > 1;
        CanExportBatchNext = ExportBatchPageIndex < ExportBatchTotalPages;

        foreach (var b in list)
            ExportBatchRows.Add(b);
        RebuildExportBatchTableView();

        var selectedId = SelectedBatch?.Id;
        var onPage = selectedId is Guid sid ? ExportBatchRows.FirstOrDefault(x => x.Id == sid) : null;
        if (onPage is not null)
            SelectedBatch = onPage;
        else if (SelectedBatch is null)
            SelectedBatch = ExportBatchRows.FirstOrDefault();
    }

    private void RebuildExportBatchTableView()
    {
        var cvs = new CollectionViewSource { Source = ExportBatchRows };
        // 不用 DataGrid 行分组（WPF 下表头与单元格易错位）；按类型排序实现视觉上的「分组」。
        cvs.SortDescriptions.Add(new SortDescription(nameof(TestBatchRun.ScopeKind), ListSortDirection.Ascending));
        cvs.SortDescriptions.Add(new SortDescription(nameof(TestBatchRun.StartedAtUtc), ListSortDirection.Descending));
        ExportBatchTableView = cvs.View;
    }

    private bool CanExportReport()
    {
        if (IsBusy || ActiveProjectId is null) return false;
        if (ResolveEffectiveExportScope() == TestReportRunScope.SelectedBatchOnly && SelectedBatch is null)
            return false;
        return true;
    }

    private static string NormalizePeripheralFilter(string? value)
        => string.IsNullOrWhiteSpace(value) || value == "全部" || value == "(全部)"
            ? "(全部)"
            : value.Trim();

    private static bool IsAllPeripherals(string? value)
        => string.IsNullOrWhiteSpace(value) || value == "全部" || value == "(全部)";

    [RelayCommand]
    private Task RetryNonPassedAsync() => RetryFromSelectedBatchAsync("NonPassed", "非通过重跑");

    [RelayCommand]
    private Task RetryAssertionFailedAsync() => RetryFromSelectedBatchAsync("Failed", "仅断言失败");

    [RelayCommand]
    private Task RetryErrorsAsync() => RetryFromSelectedBatchAsync("Error", "仅错误");

    /// <summary>Back-compat alias used by older bindings; same as non-passed retry.</summary>
    [RelayCommand]
    private Task RetryFailedAsync() => RetryNonPassedAsync();

    private async Task RetryFromSelectedBatchAsync(string retryMode, string label)
    {
        if (ActiveProjectId is not Guid pid || SelectedBatch is null)
        {
            StatusText = "请先在执行历史中选中一个批次";
            return;
        }

        if (string.Equals(SelectedBatch.Status, "Running", StringComparison.OrdinalIgnoreCase))
        {
            StatusText = "源批次仍在 Running，无法重跑";
            return;
        }

        var nonPassHint = SelectedBatch.FailedCount
                          + SelectedBatch.ErrorCount
                          + SelectedBatch.SkippedCount
                          + SelectedBatch.TimeoutCount
                          + SelectedBatch.CancelledCount;
        StatusText = $"{label}：源批次 {SelectedBatch.ScopeKind}（非通过合计约 {nonPassHint}，以实际筛选为准）…";

        await RunBatchInternalAsync(new TestBatchRunRequest
        {
            SdkProjectId = pid,
            ScopeKind = "FailedRetry",
            ScopeValue = retryMode,
            RetryMode = retryMode,
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

    [RelayCommand(CanExecute = nameof(CanExportReport))]
    private Task ExportReportAsync() => ExportReportCoreAsync(null);

    [RelayCommand(CanExecute = nameof(CanExportSelectedBatchReport))]
    private Task ExportSelectedBatchReportAsync()
    {
        SelectedExportRunScope = "当前选中批次";
        return ExportReportCoreAsync(TestReportRunScope.SelectedBatchOnly);
    }

    private bool CanExportSelectedBatchReport()
        => CanExportReport() && SelectedBatch is not null;

    private async Task ExportReportCoreAsync(TestReportRunScope? forceScope)
    {
        if (ActiveProjectId is not Guid pid) return;
        if (ResolveEffectiveExportScope() == TestReportRunScope.SelectedBatchOnly && SelectedBatch is null)
        {
            StatusText = "请先在「执行历史」选中一条批次。";
            return;
        }
        IsBusy = true;
        try
        {
            var scope = forceScope ?? MapExportRunScope(SelectedExportRunScope);
            var fmt = SelectedReportFormat.ToLowerInvariant() switch
            {
                "pdf" => TestReportFormat.Pdf,
                "excel" or "csv" => TestReportFormat.Excel,
                _ => TestReportFormat.Html
            };
            var effectiveScope = scope == TestReportRunScope.Auto
                ? SelectedBatch is not null ? TestReportRunScope.SelectedBatchOnly : TestReportRunScope.ProjectLatestPerCase
                : scope;
            var title = SelectedBatch is not null && effectiveScope == TestReportRunScope.SelectedBatchOnly
                ? $"批次报告 {Converters.BeijingTime.Format(SelectedBatch.StartedAtUtc)} · {SelectedBatch.TotalCount} 条 · {SelectedBatch.ScopeKind}"
                : $"TAE32 LL Virtual Test — {SelectedPlan?.Name ?? "项目汇总"}";
            var result = await _reports.GenerateAsync(new TestReportRequest
            {
                SdkProjectId = pid,
                BatchRunId = SelectedBatch?.Id,
                RunScope = scope,
                Format = fmt,
                Title = title
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
    private async Task OpenSourceAsync(FailureAnalysisItem? item)
    {
        item ??= SelectedFailureRow?.Item;
        if (string.IsNullOrWhiteSpace(item?.SourceFile))
        {
            StatusText = "源码路径未知";
            return;
        }

        string? sdkRoot = null;
        if (ActiveProjectId is Guid pid)
            sdkRoot = (await _projects.GetByIdAsync(pid))?.SdkRootPath;

        if (!SdkSourcePathResolver.TryResolve(item.SourceFile, sdkRoot, out var absolutePath))
        {
            StatusText = "源码文件不存在。请确认 SDK 根路径与仓库内 SDKContent 仍有效。路径：" + item.SourceFile;
            return;
        }

        try
        {
            Process.Start(new ProcessStartInfo { FileName = absolutePath, UseShellExecute = true });
            StatusText = "已打开 " + absolutePath;
        }
        catch (Exception ex)
        {
            StatusText = "打开失败：" + ex.Message;
            MessageBox.Show(
                "无法打开文件：\n" + absolutePath + "\n\n" + ex.Message,
                "TAE32 LL Virtual Test",
                MessageBoxButton.OK,
                MessageBoxImage.Warning);
        }
    }

    [RelayCommand]
    private void OpenArtifact(TestReportArtifact? artifact)
    {
        artifact ??= SelectedArtifact;
        if (artifact is null)
        {
            StatusText = "请先选择一条报告记录";
            return;
        }

        var path = artifact.FilePath;
        if (string.IsNullOrWhiteSpace(path) || !File.Exists(path))
        {
            StatusText = "报告文件不存在或路径无效";
            return;
        }

        Process.Start(new ProcessStartInfo { FileName = path, UseShellExecute = true });
        StatusText = "已打开报告：" + path;
    }

    [RelayCommand]
    private async Task SearchArtifactsAsync()
    {
        ArtifactPageIndex = 1;
        await ReloadArtifactsAsync();
    }

    partial void OnArtifactPageSizeChanged(int value)
    {
        ArtifactPageIndex = 1;
        _ = ReloadArtifactsAsync();
    }

    [RelayCommand]
    private async Task ArtifactPreviousPageAsync()
    {
        if (ArtifactPageIndex <= 1) return;
        ArtifactPageIndex--;
        await ReloadArtifactsAsync();
    }

    [RelayCommand]
    private async Task ArtifactNextPageAsync()
    {
        if (ArtifactPageIndex >= ArtifactTotalPages) return;
        ArtifactPageIndex++;
        await ReloadArtifactsAsync();
    }

    [RelayCommand]
    private async Task DeleteArtifactSelectedAsync()
    {
        if (SelectedArtifact is null)
        {
            StatusText = "请先在列表中选中一条报告";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除报告",
                $"确认删除所选报告？\n{SelectedArtifact.Title}\n{SelectedArtifact.FilePath}",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _reports.DeleteManyAsync(new[] { SelectedArtifact.Id });
        StatusText = n > 0 ? "已删除所选报告" : "删除失败";
        await ReloadArtifactsAsync();
    }

    [RelayCommand]
    private async Task DeleteArtifactsPageAsync()
    {
        if (ActiveProjectId is null)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (Artifacts.Count == 0)
        {
            StatusText = "本页无报告记录";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除报告",
                $"确认删除本页 {Artifacts.Count} 条报告记录及对应磁盘文件？",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _reports.DeleteManyAsync(Artifacts.Select(a => a.Id));
        StatusText = $"已删除本页 {n} 条报告";
        await ReloadArtifactsAsync();
    }

    [RelayCommand]
    private async Task DeleteArtifactsAllAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (ArtifactTotalCount == 0)
        {
            StatusText = "当前筛选下无报告";
            return;
        }

        var scope = string.IsNullOrWhiteSpace(ArtifactSearchText)
            ? "当前项目下全部报告"
            : $"当前搜索条件下全部 {ArtifactTotalCount} 条报告";
        if (!ConfirmDialog.Show(
                "删除报告",
                $"确认删除 {scope} 及对应磁盘文件？",
                confirmLabel: "删除全部",
                dangerConfirm: true))
            return;

        var search = string.IsNullOrWhiteSpace(ArtifactSearchText) ? null : ArtifactSearchText.Trim();
        var n = await _reports.DeleteFilteredAsync(pid, search);
        ArtifactPageIndex = 1;
        StatusText = $"已删除 {n} 条报告";
        await ReloadArtifactsAsync();
    }

    partial void OnSelectedPlanChanged(TestPlan? value)
    {
        if (value is null) return;
        PlanName = value.Name;
        PlanChip = value.ChipModelName ?? "TAE32G58xx";
        PlanPeripheral = NormalizePeripheralFilter(value.PeripheralFilter);
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

    partial void OnSelectedFailureRowChanged(FailurePickItem? value) => _ = LoadFailureDetailAsync(value);

    private async Task LoadFailureDetailAsync(FailurePickItem? value)
    {
        if (value is null)
        {
            FailureDetail = string.Empty;
            return;
        }

        FailureDetail = "加载详情…";
        var v = await _analytics.GetFailureDetailAsync(value.Item.RunId) ?? value.Item;
        value.Item.CompileLogExcerpt = v.CompileLogExcerpt;
        value.Item.AssertionResultsJson = v.AssertionResultsJson;
        value.Item.AccessTraceJson = v.AccessTraceJson;
        value.Item.RelatedRegisters = v.RelatedRegisters;
        value.Item.ExecutionLogExcerpt = v.ExecutionLogExcerpt;
        value.Item.ParametersJson = v.ParametersJson;
        value.Item.InitialRegistersJson = v.InitialRegistersJson;
        value.Item.RegisterWritesSummary = v.RegisterWritesSummary;
        value.Item.StagesJson = v.StagesJson;
        FailureDetail =
            $"用例: {v.CaseName}\n函数: {v.FunctionName}\n源码: {v.SourceFile}\n状态: {v.Status}\n原因: {v.FailureReason}\n寄存器: {v.RelatedRegisters}\n\n"
            + "--- 操作过程（执行阶段） ---\n"
            + (string.IsNullOrWhiteSpace(v.StagesJson) ? "（无）" : v.StagesJson.Trim()) + "\n\n"
            + "--- 执行日志 ---\n"
            + (string.IsNullOrWhiteSpace(v.ExecutionLogExcerpt) ? "（无）" : v.ExecutionLogExcerpt.Trim()) + "\n\n"
            + "--- 编译摘录 ---\n"
            + (string.IsNullOrWhiteSpace(v.CompileLogExcerpt) ? "（无）" : v.CompileLogExcerpt.Trim()) + "\n\n"
            + "--- 断言 ---\n"
            + (string.IsNullOrWhiteSpace(v.AssertionResultsJson) ? "（无）" : v.AssertionResultsJson.Trim()) + "\n\n"
            + "--- 寄存器写入一览 ---\n"
            + (string.IsNullOrWhiteSpace(v.RegisterWritesSummary) ? "（无）" : v.RegisterWritesSummary.Trim()) + "\n\n"
            + "--- 轨迹 ---\n"
            + (string.IsNullOrWhiteSpace(v.AccessTraceJson) ? "（无）" : v.AccessTraceJson.Trim());
    }

    partial void OnIsAllFailuresOnPageSelectedChanged(bool value)
    {
        if (_suppressFailureAllSelectedSync) return;
        foreach (var row in FailureRows)
            row.IsSelected = value;
    }

    [RelayCommand]
    private async Task SearchFailuresAsync()
    {
        FailurePageIndex = 1;
        await ReloadFailuresAsync();
    }

    partial void OnFailurePageSizeChanged(int value)
    {
        FailurePageIndex = 1;
        _ = ReloadFailuresAsync();
    }

    [RelayCommand]
    private async Task FailurePreviousPageAsync()
    {
        if (FailurePageIndex <= 1) return;
        FailurePageIndex--;
        await ReloadFailuresAsync();
    }

    [RelayCommand]
    private async Task FailureNextPageAsync()
    {
        if (FailurePageIndex >= FailureTotalPages) return;
        FailurePageIndex++;
        await ReloadFailuresAsync();
    }

    [RelayCommand]
    private async Task DeleteSelectedFailuresAsync()
    {
        var ids = FailureRows.Where(r => r.IsSelected).Select(r => r.Item.RunId).ToList();
        if (ids.Count == 0 && SelectedFailureRow is not null)
            ids.Add(SelectedFailureRow.Item.RunId);
        if (ids.Count == 0)
        {
            StatusText = "请勾选要删除的失败运行记录";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除运行记录",
                $"确认删除选中的 {ids.Count} 条失败/错误/超时运行记录？（不删除测试用例）",
                confirmLabel: "删除",
                dangerConfirm: true))
            return;

        var n = await _cases.DeleteRunsAsync(ids);
        StatusText = $"已删除 {n} 条运行记录";
        await ReloadFailuresAsync();
        await ReloadStatsAsync();
    }

    [RelayCommand]
    private async Task DeleteFailuresPageAsync()
    {
        if (ActiveProjectId is null)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (FailureRows.Count == 0)
        {
            StatusText = "本页无失败记录";
            return;
        }

        if (!ConfirmDialog.Show(
                "删除运行记录",
                $"确认删除本页 {FailureRows.Count} 条失败/错误/超时运行记录？",
                confirmLabel: "删除本页",
                dangerConfirm: true))
            return;

        var n = await _cases.DeleteRunsAsync(FailureRows.Select(r => r.Item.RunId));
        StatusText = $"已删除本页 {n} 条运行记录";
        await ReloadFailuresAsync();
        await ReloadStatsAsync();
    }

    [RelayCommand]
    private async Task DeleteFailuresAllAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            StatusText = "请先选择 SDK 项目";
            return;
        }

        if (FailureTotalCount == 0)
        {
            StatusText = "当前筛选下无失败记录";
            return;
        }

        var batchNote = SelectedBatch is null
            ? ""
            : "（限于当前所选批次）";
        var scope = string.IsNullOrWhiteSpace(FailureSearchText)
            ? $"当前条件下全部 {FailureTotalCount} 条失败/错误/超时记录{batchNote}"
            : $"搜索条件下全部 {FailureTotalCount} 条记录{batchNote}";
        if (!ConfirmDialog.Show(
                "删除运行记录",
                $"确认删除 {scope}？\n不删除测试用例本身。",
                confirmLabel: "删除全部",
                dangerConfirm: true))
            return;

        var search = string.IsNullOrWhiteSpace(FailureSearchText) ? null : FailureSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedFailureStatusFilter);
        var n = await _analytics.DeleteFailureRunsFilteredAsync(pid, SelectedBatch?.Id, search, status);
        FailurePageIndex = 1;
        StatusText = $"已删除 {n} 条运行记录";
        await ReloadFailuresAsync();
        await ReloadStatsAsync();
    }

    private async Task LoadSuiteCaseIdsAsync(Guid suiteId)
    {
        SelectedCaseIds.Clear();
        foreach (var id in await _suites.GetCaseIdsAsync(suiteId))
            SelectedCaseIds.Add(id);
    }

    private async Task RunBatchInternalAsync(TestBatchRunRequest request, bool manageBusyFlag = true)
    {
        if (manageBusyFlag)
        {
            IsBusy = true;
            BusyOverlayText = "正在批量执行（虚拟 MCU）…";
        }

        _batchCts = new CancellationTokenSource();
        TestBatchProgress? latest = null;
        var flushScheduled = false;
        void FlushProgress()
        {
            var p = latest;
            if (p is null) return;
            ProgressPercent = p.Percent;
            ProgressText = $"{p.Completed}/{p.Total} {p.CurrentCaseName}";
            StatusText = p.Message;
            BusyOverlayText = $"执行中 {p.Completed}/{p.Total}：{p.CurrentCaseName}";
        }

        var progress = new Progress<TestBatchProgress>(p =>
        {
            latest = p;
            if (flushScheduled) return;
            flushScheduled = true;
            Application.Current.Dispatcher.BeginInvoke(() =>
            {
                flushScheduled = false;
                FlushProgress();
            }, DispatcherPriority.Background);
        });
        try
        {
            var batch = await _batches.RunAsync(request, progress, _batchCts.Token);
            StatusText = batch.TotalCount == 0 && request.SourceBatchRunId is not null
                ? $"重跑未选中任何用例（模式={request.RetryMode ?? "NonPassed"}）。请确认已选中含非通过结果的源批次。"
                : $"批次完成：{batch.Status} Passed={batch.PassedCount} Failed={batch.FailedCount} Error={batch.ErrorCount}（虚拟环境）";
            SelectedBatch = batch;
            await ReloadHistoryAsync();
            if (SelectedSection is "统计覆盖率")
                await ReloadStatsAsync(includeCoverage: true);
            else
                await ReloadStatsAsync(includeCoverage: false);
            if (SelectedSection is "失败分析")
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
            if (manageBusyFlag)
            {
                IsBusy = false;
                BusyOverlayText = string.Empty;
            }
            _batchCts = null;
        }
    }

    private async Task ReloadPlansAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            Plans.Clear();
            PlanTotalCount = 0;
            PlanTotalPages = 1;
            PlanPageInfo = "无项目";
            CanPlanPrev = false;
            CanPlanNext = false;
            return;
        }

        var search = string.IsNullOrWhiteSpace(PlanSearchText) ? null : PlanSearchText.Trim();
        var status = SelectedPlanStatusFilter switch
        {
            "仅活动" => "Active",
            "仅归档" => "Archived",
            _ => null // 全部状态：含历史归档
        };
        var skip = Math.Max(0, (PlanPageIndex - 1) * PlanPageSize);
        var (list, total) = await _plans.ListPagedAsync(pid, search, status, skip, PlanPageSize);
        PlanTotalCount = total;
        PlanTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, PlanPageSize)));
        if (PlanPageIndex > PlanTotalPages) PlanPageIndex = PlanTotalPages;
        if (PlanPageIndex < 1) PlanPageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        PlanPageInfo = $"共 {total} 条　第 {PlanPageIndex}/{PlanTotalPages} 页　{from}-{to}";
        CanPlanPrev = PlanPageIndex > 1;
        CanPlanNext = PlanPageIndex < PlanTotalPages;

        var selectedId = SelectedPlan?.Id;
        Plans.Clear();
        foreach (var p in list)
            Plans.Add(p);
        SelectedPlan = Plans.FirstOrDefault(x => x.Id == selectedId) ?? Plans.FirstOrDefault();
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
        if (ActiveProjectId is not Guid pid)
        {
            AvailableCases.Clear();
            AvailableCaseTotalCount = 0;
            AvailableCaseTotalPages = 1;
            AvailableCasePageInfo = "无项目";
            CanAvailableCasePrev = false;
            CanAvailableCaseNext = false;
            return;
        }

        var peri = string.IsNullOrWhiteSpace(SuitePeripheral) || SuitePeripheral == "(全部)" ? null : SuitePeripheral;
        var search = string.IsNullOrWhiteSpace(AvailableCaseSearchText) ? null : AvailableCaseSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedAvailableCaseStatusFilter);
        var skip = Math.Max(0, (AvailableCasePageIndex - 1) * AvailableCasePageSize);
        var (list, total) = await _cases.ListPagedAsync(pid, peri, search, skip, AvailableCasePageSize, status);
        AvailableCaseTotalCount = total;
        AvailableCaseTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, AvailableCasePageSize)));
        if (AvailableCasePageIndex > AvailableCaseTotalPages) AvailableCasePageIndex = AvailableCaseTotalPages;
        if (AvailableCasePageIndex < 1) AvailableCasePageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        AvailableCasePageInfo = $"共 {total} 条　第 {AvailableCasePageIndex}/{AvailableCaseTotalPages} 页　{from}-{to}";
        CanAvailableCasePrev = AvailableCasePageIndex > 1;
        CanAvailableCaseNext = AvailableCasePageIndex < AvailableCaseTotalPages;

        AvailableCases.Clear();
        foreach (var c in list)
            AvailableCases.Add(c);
    }

    private async Task ReloadHistoryAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            History.Clear();
            HistoryTotalCount = 0;
            HistoryTotalPages = 1;
            HistoryPageInfo = "无项目";
            CanHistoryPrev = false;
            CanHistoryNext = false;
            return;
        }

        var search = string.IsNullOrWhiteSpace(HistorySearchText) ? null : HistorySearchText.Trim();
        var status = NormalizeStatusFilter(SelectedHistoryStatusFilter);
        var skip = Math.Max(0, (HistoryPageIndex - 1) * HistoryPageSize);
        var (list, total) = await _batches.ListHistoryPagedAsync(
            pid, search, skip: skip, take: HistoryPageSize, statusFilter: status);
        HistoryTotalCount = total;
        HistoryTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, HistoryPageSize)));
        if (HistoryPageIndex > HistoryTotalPages) HistoryPageIndex = HistoryTotalPages;
        if (HistoryPageIndex < 1) HistoryPageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        HistoryPageInfo = $"共 {total} 条　第 {HistoryPageIndex}/{HistoryTotalPages} 页　{from}-{to}";
        CanHistoryPrev = HistoryPageIndex > 1;
        CanHistoryNext = HistoryPageIndex < HistoryTotalPages;

        var selectedId = SelectedBatch?.Id;
        History.Clear();
        foreach (var h in list)
            History.Add(h);
        SelectedBatch = History.FirstOrDefault(x => x.Id == selectedId) ?? History.FirstOrDefault();
        RefreshExportScopeHint();
    }

    partial void OnSelectedBatchChanged(TestBatchRun? value)
    {
        FailurePageIndex = 1;
        RefreshExportScopeHint();
        // Only refresh data needed by the current tab (avoid coverage + failures on every selection).
        if (SelectedSection is "统计覆盖率")
            _ = ReloadStatsAsync(includeCoverage: true);
        else if (SelectedSection is "失败分析")
            _ = ReloadFailuresAsync();
        else if (SelectedSection is "执行历史")
            _ = ReloadStatsAsync(includeCoverage: false);
    }

    partial void OnSelectedExportRunScopeChanged(string value) => RefreshExportScopeHint();

    private async Task ReloadStatsAsync(bool includeCoverage = true)
    {
        if (ActiveProjectId is not Guid pid) return;
        var s = await _analytics.GetStatisticsAsync(pid, SelectedBatch?.Id);
        Statistics = s;
        StatsScopeHint = SelectedBatch is null
            ? "全项目累计"
            : $"所选批次 · {SelectedBatch.Status} · {SelectedBatch.ScopeKind}";

        if (!includeCoverage) return;

        var c = await _analytics.GetCoverageAsync(pid);
        Coverage = c;
        CoverageNotes = c.Notes ?? string.Empty;
        FunctionCoverageText = Pct(c.FunctionCoveragePercent);
        PeripheralCoverageText = Pct(c.PeripheralCoveragePercent);
        RegisterCoverageText = Pct(c.RegisterAccessCoveragePercent);
        BitFieldCoverageText = Pct(c.BitFieldCoveragePercent);
        CaseCoverageText = Pct(c.CaseCoveragePercent);
    }

    private async Task ReloadFailuresAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            FailureRows.Clear();
            FailureTotalCount = 0;
            FailureTotalPages = 1;
            FailurePageInfo = "无项目";
            CanFailurePrev = false;
            CanFailureNext = false;
            return;
        }

        var search = string.IsNullOrWhiteSpace(FailureSearchText) ? null : FailureSearchText.Trim();
        var status = NormalizeStatusFilter(SelectedFailureStatusFilter);
        var skip = Math.Max(0, (FailurePageIndex - 1) * FailurePageSize);
        var (list, total) = await _analytics.GetFailuresPagedAsync(
            pid, SelectedBatch?.Id, search, skip, FailurePageSize, status);
        FailureTotalCount = total;
        FailureTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, FailurePageSize)));
        if (FailurePageIndex > FailureTotalPages) FailurePageIndex = FailureTotalPages;
        if (FailurePageIndex < 1) FailurePageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        FailurePageInfo = $"共 {total} 条　第 {FailurePageIndex}/{FailureTotalPages} 页　{from}-{to}";
        CanFailurePrev = FailurePageIndex > 1;
        CanFailureNext = FailurePageIndex < FailureTotalPages;

        var selectedRunId = SelectedFailureRow?.Item.RunId;
        FailureRows.Clear();
        foreach (var f in list)
        {
            var row = new FailurePickItem(f);
            row.SelectionChanged += _ => RefreshFailureSelectionUi();
            FailureRows.Add(row);
        }

        SelectedFailureRow = FailureRows.FirstOrDefault(x => x.Item.RunId == selectedRunId) ?? FailureRows.FirstOrDefault();
        RefreshFailureSelectionUi();
    }

    private void RefreshFailureSelectionUi()
    {
        _suppressFailureAllSelectedSync = true;
        IsAllFailuresOnPageSelected = FailureRows.Count > 0 && FailureRows.All(r => r.IsSelected);
        _suppressFailureAllSelectedSync = false;
    }

    private async Task ReloadArtifactsAsync()
    {
        if (ActiveProjectId is not Guid pid)
        {
            Artifacts.Clear();
            ArtifactTotalCount = 0;
            ArtifactTotalPages = 1;
            ArtifactPageInfo = "无项目";
            CanArtifactPrev = false;
            CanArtifactNext = false;
            return;
        }

        var search = string.IsNullOrWhiteSpace(ArtifactSearchText) ? null : ArtifactSearchText.Trim();
        var skip = Math.Max(0, (ArtifactPageIndex - 1) * ArtifactPageSize);
        var (list, total) = await _reports.ListArtifactsPagedAsync(pid, search, skip, ArtifactPageSize);
        ArtifactTotalCount = total;
        ArtifactTotalPages = Math.Max(1, (int)Math.Ceiling(total / (double)Math.Max(1, ArtifactPageSize)));
        if (ArtifactPageIndex > ArtifactTotalPages) ArtifactPageIndex = ArtifactTotalPages;
        if (ArtifactPageIndex < 1) ArtifactPageIndex = 1;
        var from = total == 0 ? 0 : skip + 1;
        var to = total == 0 ? 0 : Math.Min(total, skip + list.Count);
        ArtifactPageInfo = $"共 {total} 条　第 {ArtifactPageIndex}/{ArtifactTotalPages} 页　{from}-{to}";
        CanArtifactPrev = ArtifactPageIndex > 1;
        CanArtifactNext = ArtifactPageIndex < ArtifactTotalPages;

        var selectedId = SelectedArtifact?.Id;
        Artifacts.Clear();
        foreach (var a in list)
            Artifacts.Add(a);
        SelectedArtifact = Artifacts.FirstOrDefault(x => x.Id == selectedId) ?? Artifacts.FirstOrDefault();
    }

    private static string Pct(double? v) => v is null ? "N/A" : $"{v:F1}%";

    private static string? NormalizeStatusFilter(string? selected) =>
        string.IsNullOrWhiteSpace(selected) || selected == "全部状态" ? null : selected.Trim();

    partial void OnSelectedAvailableCaseStatusFilterChanged(string value)
    {
        AvailableCasePageIndex = 1;
        _ = ReloadCasesAsync();
    }

    partial void OnSelectedHistoryStatusFilterChanged(string value)
    {
        HistoryPageIndex = 1;
        _ = ReloadHistoryAsync();
    }

    partial void OnSelectedExportBatchStatusFilterChanged(string value)
    {
        ExportBatchPageIndex = 1;
        _ = ReloadExportBatchListAsync();
    }

    partial void OnSelectedFailureStatusFilterChanged(string value)
    {
        FailurePageIndex = 1;
        _ = ReloadFailuresAsync();
    }
}

public sealed class FailurePickItem : ObservableObject
{
    private bool _isSelected;

    public FailurePickItem(FailureAnalysisItem item) => Item = item;

    public FailureAnalysisItem Item { get; }
    public string CaseName => Item.CaseName;
    public string FunctionName => Item.FunctionName;
    public string Status => Item.Status;

    public bool IsSelected
    {
        get => _isSelected;
        set
        {
            if (SetProperty(ref _isSelected, value))
                SelectionChanged?.Invoke(this);
        }
    }

    public event Action<FailurePickItem>? SelectionChanged;
}
