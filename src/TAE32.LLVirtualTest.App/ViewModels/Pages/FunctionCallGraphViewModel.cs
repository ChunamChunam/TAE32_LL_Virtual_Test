using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

/// <summary>跨函数浏览 LL 深度解析得到的调用边（非全局图画布）。</summary>
public partial class FunctionCallGraphViewModel : ObservableObject
{
    private readonly IAppDataService _data;

    public ObservableCollection<LlFunctionCallRowDto> Items { get; } = new();
    public ObservableCollection<string> PeripheralFilters { get; } = new() { "(全部)" };
    public ObservableCollection<string> CalleeKindFilters { get; } = new()
    {
        "(全部)", "LL", "HAL", "SdkInternal", "External", "Indirect", "Unknown"
    };
    public ObservableCollection<int> PageSizeOptions { get; } = new() { 50, 100, 200, 500 };

    [ObservableProperty] private string _searchText = string.Empty;
    [ObservableProperty] private string? _selectedPeripheral = "(全部)";
    [ObservableProperty] private string? _selectedCalleeKind = "(全部)";
    [ObservableProperty] private LlFunctionCallRowDto? _selectedRow;
    [ObservableProperty] private int _pageIndex = 1;
    [ObservableProperty] private int _pageSize = 100;
    [ObservableProperty] private int _totalCount;
    [ObservableProperty] private int _totalPages = 1;
    [ObservableProperty] private string _pageInfoText = string.Empty;
    [ObservableProperty] private bool _canGoPrevious;
    [ObservableProperty] private bool _canGoNext;
    [ObservableProperty] private string _summaryText = "加载中…";
    [ObservableProperty] private string _detailText = "选择一行查看调用详情。";
    [ObservableProperty] private string _hintText =
        "数据来自「LL 函数库 → 深度解析」。本页用于跨函数检索调用边；单函数明细见函数库「调用」Tab。";

    public FunctionCallGraphViewModel(IAppDataService data) => _data = data;

    [RelayCommand]
    public async Task RefreshAsync()
    {
        await LoadFiltersAsync();
        var stats = await _data.GetCallGraphStatsAsync();
        SummaryText = stats.TotalEdges == 0
            ? "尚无调用边：请先在 LL 函数库对目标外设执行「深度解析」。"
            : $"调用边 {stats.TotalEdges}　含调用的函数 {stats.CallerFunctions}　已解析函数 {stats.ParsedFunctionCount}　Unknown/Indirect {stats.UnknownCalleeEdges}";
        PageIndex = 1;
        await LoadPageAsync();
    }

    [RelayCommand]
    private async Task SearchAsync()
    {
        PageIndex = 1;
        await LoadPageAsync();
    }

    [RelayCommand(CanExecute = nameof(CanGoPrevious))]
    private async Task PreviousPageAsync()
    {
        PageIndex--;
        await LoadPageAsync();
    }

    [RelayCommand(CanExecute = nameof(CanGoNext))]
    private async Task NextPageAsync()
    {
        PageIndex++;
        await LoadPageAsync();
    }

    partial void OnSelectedRowChanged(LlFunctionCallRowDto? value)
    {
        if (value is null)
        {
            DetailText = "选择一行查看调用详情。";
            return;
        }

        DetailText =
            $"调用方：{value.CallerPeripheral} :: {value.CallerName}{Environment.NewLine}" +
            $"被调：{value.CalleeName}（{value.CalleeKind}）× {value.CallCount}{Environment.NewLine}" +
            $"位置：{value.CallFile} : {value.CallLine}{Environment.NewLine}" +
            (string.IsNullOrWhiteSpace(value.CalleePeripheral) ? "" : $"推断外设：{value.CalleePeripheral}");
    }

    partial void OnSelectedPeripheralChanged(string? value) => _ = SearchAsync();

    partial void OnSelectedCalleeKindChanged(string? value) => _ = SearchAsync();

    partial void OnPageSizeChanged(int value) => _ = SearchAsync();

    private async Task LoadFiltersAsync()
    {
        PeripheralFilters.Clear();
        PeripheralFilters.Add("(全部)");
        foreach (var p in await _data.GetCallGraphCallerPeripheralsAsync())
            PeripheralFilters.Add(p);
    }

    private async Task LoadPageAsync()
    {
        var peri = SelectedPeripheral == "(全部)" ? null : SelectedPeripheral;
        var kind = SelectedCalleeKind == "(全部)" ? null : SelectedCalleeKind;
        var search = string.IsNullOrWhiteSpace(SearchText) ? null : SearchText.Trim();

        TotalCount = await _data.CountFunctionCallsAsync(search, peri, kind);
        TotalPages = Math.Max(1, (int)Math.Ceiling(TotalCount / (double)PageSize));
        if (PageIndex > TotalPages) PageIndex = TotalPages;
        if (PageIndex < 1) PageIndex = 1;

        var skip = (PageIndex - 1) * PageSize;
        var rows = await _data.SearchFunctionCallsAsync(search, peri, kind, skip, PageSize);

        Items.Clear();
        foreach (var r in rows) Items.Add(r);

        CanGoPrevious = PageIndex > 1;
        CanGoNext = PageIndex < TotalPages;
        PreviousPageCommand.NotifyCanExecuteChanged();
        NextPageCommand.NotifyCanExecuteChanged();
        PageInfoText = TotalCount == 0
            ? "无匹配调用边"
            : $"共 {TotalCount} 条　第 {PageIndex}/{TotalPages} 页";
    }
}
