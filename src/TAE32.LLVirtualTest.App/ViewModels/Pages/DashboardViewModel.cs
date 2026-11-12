using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class DashboardViewModel : ObservableObject
{
    private readonly IAppDataService _data;

    [ObservableProperty] private int _sdkProjectCount;
    [ObservableProperty] private int _chipCount;
    [ObservableProperty] private int _peripheralCount;
    [ObservableProperty] private int _llFunctionCount;
    [ObservableProperty] private int _inlineFunctionCount;
    [ObservableProperty] private string _scanStatusText = "加载中…";
    [ObservableProperty] private string _lastImportText = "—";
    [ObservableProperty] private string _liveStatsLine = "—";
    [ObservableProperty] private string _baselineNoteText = "—";
    [ObservableProperty] private bool _matchesBaseline;

    public string BaselineTooltip { get; } =
        $"结构基线：{Tae32LlStructureBaseline.PeripheralModuleCount} 外设 · " +
        $"{Tae32LlStructureBaseline.InlineDefinitionCount} inline（KnowledgeBase）";

    public DashboardViewModel(IAppDataService data) => _data = data;

    [RelayCommand]
    public async Task RefreshAsync()
    {
        var s = await _data.GetDashboardStatsAsync();
        SdkProjectCount = s.SdkProjectCount;
        ChipCount = s.ChipCount;
        PeripheralCount = s.PeripheralCount;
        LlFunctionCount = s.LlFunctionCount;
        InlineFunctionCount = s.InlineFunctionCount;
        ScanStatusText = s.ScanStatusText;
        LastImportText = s.LastImportedAtUtc?.ToLocalTime().ToString("yyyy-MM-dd HH:mm:ss") ?? "尚未导入";
        UpdateLiveAndBaselineLines();
    }

    private void UpdateLiveAndBaselineLines()
    {
        LiveStatsLine =
            $"{PeripheralCount} 外设模块 · {InlineFunctionCount} inline 定义（库内实时）";

        var peripheralOk = PeripheralCount == Tae32LlStructureBaseline.PeripheralModuleCount;
        var inlineOk = InlineFunctionCount == Tae32LlStructureBaseline.InlineDefinitionCount;
        MatchesBaseline = peripheralOk && inlineOk;

        if (MatchesBaseline)
        {
            BaselineNoteText = "与基线一致";
            return;
        }

        var parts = new List<string>(2);
        if (!peripheralOk)
        {
            parts.Add(
                $"外设 基线 {Tae32LlStructureBaseline.PeripheralModuleCount}，当前 {PeripheralCount}");
        }

        if (!inlineOk)
        {
            parts.Add(
                $"inline 基线 {Tae32LlStructureBaseline.InlineDefinitionCount}，当前 {InlineFunctionCount}");
        }

        BaselineNoteText = string.Join("；", parts);
    }
}
