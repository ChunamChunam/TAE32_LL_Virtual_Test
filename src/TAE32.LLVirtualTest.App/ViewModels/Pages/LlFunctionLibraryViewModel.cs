using System.Collections.ObjectModel;
using System.Text;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class LlFunctionLibraryViewModel : ObservableObject
{
    private readonly IAppDataService _data;
    private readonly ILLFunctionParser _parser;
    private readonly ISdkProjectService _projects;
    private readonly HashSet<Guid> _checkedIds = new();
    private bool _suppressFilterReload;
    private bool _suppressAllSelectedSync;

    public ObservableCollection<LlFunctionRowItem> Items { get; } = new();
    public ObservableCollection<string> PeripheralFilters { get; } = new();
    public ObservableCollection<string> ChipFilters { get; } = new();
    public ObservableCollection<string> FormFilters { get; } = new() { "(全部)", "inline_definition", "function_macro", "declaration" };
    public ObservableCollection<string> ParseStatusFilterOptions { get; } = new()
    {
        "全部状态",
        nameof(LlParseStatus.NotParsed),
        nameof(LlParseStatus.InProgress),
        nameof(LlParseStatus.Success),
        nameof(LlParseStatus.Partial),
        nameof(LlParseStatus.Failed)
    };
    public ObservableCollection<int> PageSizeOptions { get; } = new() { 50, 100, 200, 300, 500 };

    [ObservableProperty] private string _searchText = string.Empty;
    [ObservableProperty] private string? _selectedPeripheral;
    [ObservableProperty] private string? _selectedChip;
    [ObservableProperty] private string? _selectedForm = "(全部)";
    [ObservableProperty] private string _selectedParseStatusFilter = "全部状态";
    [ObservableProperty] private LlFunctionRowItem? _selectedItem;
    [ObservableProperty] private int _totalCount;
    [ObservableProperty] private int _pageIndex = 1;
    [ObservableProperty] private int _pageSize = 100;
    [ObservableProperty] private int _totalPages = 1;
    [ObservableProperty] private string _pageInfoText = string.Empty;
    [ObservableProperty] private string _checkedCountText = "已勾选 0";
    [ObservableProperty] private bool _canGoPrevious;
    [ObservableProperty] private bool _canGoNext;
    [ObservableProperty] private bool _isAllOnPageSelected;
    [ObservableProperty] private string _detailSignature = "尚未解析";
    [ObservableProperty] private string _detailParameters = "尚未解析";
    [ObservableProperty] private string _detailReturn = "尚未解析";
    [ObservableProperty] private string _detailSource = "尚未解析";
    [ObservableProperty] private string _detailOperations = "尚未解析";
    [ObservableProperty] private string _detailRegisters = "尚未解析";
    [ObservableProperty] private string _detailMacros = "尚未解析";
    [ObservableProperty] private string _detailCallGraph = "尚未解析";
    [ObservableProperty] private string _detailDiagnostics = "尚未解析";
    [ObservableProperty] private string _parseStatusText = "尚未解析";
    [ObservableProperty] private string _parseSummaryText = string.Empty;
    [ObservableProperty] private bool _isParsing;

    public LlFunctionLibraryViewModel(IAppDataService data, ILLFunctionParser parser, ISdkProjectService projects)
    {
        _data = data;
        _parser = parser;
        _projects = projects;
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        await EnsureFiltersAsync();
        PageIndex = 1;
        await LoadPageAsync();
    }

    [RelayCommand(CanExecute = nameof(CanDeepParse))]
    private async Task DeepParseAsync()
    {
        var projects = await _projects.GetAllAsync();
        var project = projects.FirstOrDefault(p => p.IsActive) ?? projects.FirstOrDefault();
        if (project is null)
        {
            ParseSummaryText = "无可用 SDK 项目";
            return;
        }

        IsParsing = true;
        NotifyParseCommands();
        ParseSummaryText = "深度解析全部进行中…";
        try
        {
            var projectId = project.Id;
            var summary = await Task.Run(async () => await _parser.ParseAsync(projectId));
            ParseSummaryText =
                $"全部解析完成：匹配 {summary.FunctionsMatched}/{summary.FunctionsParsed}，头文件 {summary.HeadersSucceeded}/{summary.HeadersAttempted}，诊断 {summary.DiagnosticCount}"
                + (summary.UsedParseBridge ? "（使用 Parse Bridge）" : "");
            var keepId = SelectedItem?.Function.Id;
            await LoadPageAsync(preserveSelectedId: keepId);
            if (SelectedItem is not null)
                await LoadDetailAsync(SelectedItem.Function.Id);
        }
        catch (Exception ex)
        {
            ParseSummaryText = $"解析失败：{ex.Message}";
        }
        finally
        {
            IsParsing = false;
            NotifyParseCommands();
        }
    }

    [RelayCommand(CanExecute = nameof(CanDeepParseSelected))]
    private async Task DeepParseSelectedAsync()
    {
        var ids = GetCheckedOrHighlightedIds();
        if (ids.Count == 0)
        {
            ParseSummaryText = "请勾选函数，或先点选一行再解析";
            return;
        }

        IsParsing = true;
        NotifyParseCommands();
        var ok = 0;
        var fail = 0;
        try
        {
            for (var i = 0; i < ids.Count; i++)
            {
                var id = ids[i];
                var name = Items.FirstOrDefault(x => x.Function.Id == id)?.Function.FunctionName ?? id.ToString("N")[..8];
                ParseSummaryText = $"正在解析勾选 {i + 1}/{ids.Count}：{name}…";
                try
                {
                    var summary = await Task.Run(async () => await _parser.ParseOneAsync(id));
                    if (summary.FunctionsMatched > 0) ok++;
                    else fail++;
                }
                catch
                {
                    fail++;
                }
            }

            ParseSummaryText = $"勾选解析完成：成功 {ok}，未匹配/失败 {fail}，合计 {ids.Count}";
            var keepId = SelectedItem?.Function.Id ?? ids[0];
            await LoadPageAsync(preserveSelectedId: keepId);
            if (SelectedItem is not null)
                await LoadDetailAsync(SelectedItem.Function.Id);
        }
        catch (Exception ex)
        {
            ParseSummaryText = $"勾选解析失败：{ex.Message}";
        }
        finally
        {
            IsParsing = false;
            NotifyParseCommands();
        }
    }

    private bool CanDeepParse() => !IsParsing;
    private bool CanDeepParseSelected() => !IsParsing && (_checkedIds.Count > 0 || SelectedItem is not null);

    private void NotifyParseCommands()
    {
        DeepParseCommand.NotifyCanExecuteChanged();
        DeepParseSelectedCommand.NotifyCanExecuteChanged();
    }

    [RelayCommand]
    private void SelectPage()
    {
        foreach (var item in Items)
            item.IsSelected = true;
        SyncCheckedUi();
    }

    [RelayCommand]
    private void ClearPageSelection()
    {
        foreach (var item in Items)
            item.IsSelected = false;
        SyncCheckedUi();
    }

    [RelayCommand]
    private void ClearAllSelection()
    {
        _checkedIds.Clear();
        foreach (var item in Items)
            item.IsSelected = false;
        SyncCheckedUi();
        ParseSummaryText = "已清空勾选";
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
        if (PageIndex <= 1) return;
        PageIndex--;
        await LoadPageAsync();
    }

    [RelayCommand(CanExecute = nameof(CanGoNext))]
    private async Task NextPageAsync()
    {
        if (PageIndex >= TotalPages) return;
        PageIndex++;
        await LoadPageAsync();
    }

    [RelayCommand]
    private async Task FirstPageAsync()
    {
        if (PageIndex == 1) return;
        PageIndex = 1;
        await LoadPageAsync();
    }

    [RelayCommand]
    private async Task LastPageAsync()
    {
        if (PageIndex >= TotalPages) return;
        PageIndex = Math.Max(1, TotalPages);
        await LoadPageAsync();
    }

    partial void OnSelectedPeripheralChanged(string? value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedChipChanged(string? value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedFormChanged(string? value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedParseStatusFilterChanged(string value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnPageSizeChanged(int value)
    {
        if (_suppressFilterReload || value <= 0) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnIsAllOnPageSelectedChanged(bool value)
    {
        if (_suppressAllSelectedSync) return;
        foreach (var item in Items)
            item.IsSelected = value;
        SyncCheckedUi(updateAllFlag: false);
    }

    partial void OnCanGoPreviousChanged(bool value) => PreviousPageCommand.NotifyCanExecuteChanged();
    partial void OnCanGoNextChanged(bool value) => NextPageCommand.NotifyCanExecuteChanged();

    private async Task ResetAndReloadAsync()
    {
        PageIndex = 1;
        await LoadPageAsync();
    }

    private async Task EnsureFiltersAsync()
    {
        _suppressFilterReload = true;
        try
        {
            var peris = await _data.GetPeripheralsAsync();
            PeripheralFilters.Clear();
            PeripheralFilters.Add("(全部)");
            foreach (var p in peris.Select(x => x.Name).Distinct().OrderBy(x => x))
                PeripheralFilters.Add(p);

            var chips = await _data.GetChipsAsync();
            ChipFilters.Clear();
            ChipFilters.Add("(全部)");
            foreach (var c in chips.Select(x => x.ModelName).Distinct().OrderBy(x => x))
                ChipFilters.Add(c);

            if (SelectedPeripheral is null || !PeripheralFilters.Contains(SelectedPeripheral))
                SelectedPeripheral = "(全部)";
            if (SelectedChip is null || !ChipFilters.Contains(SelectedChip))
                SelectedChip = "(全部)";
            if (SelectedForm is null || !FormFilters.Contains(SelectedForm))
                SelectedForm = "(全部)";
            if (!PageSizeOptions.Contains(PageSize))
                PageSize = 100;
        }
        finally
        {
            _suppressFilterReload = false;
        }
    }

    private async Task LoadPageAsync(Guid? preserveSelectedId = null)
    {
        var peri = SelectedPeripheral is null or "(全部)" ? null : SelectedPeripheral;
        var chip = SelectedChip is null or "(全部)" ? null : SelectedChip;
        var form = SelectedForm is null or "(全部)" ? null : SelectedForm;
        var parseStatus = string.IsNullOrWhiteSpace(SelectedParseStatusFilter) || SelectedParseStatusFilter == "全部状态"
            ? null
            : SelectedParseStatusFilter;
        var search = NullIfEmpty(SearchText);

        TotalCount = await _data.CountFunctionsAsync(
            search: search, peripheralName: peri, chipName: chip, form: form, parseStatus: parseStatus);
        TotalPages = Math.Max(1, (int)Math.Ceiling(TotalCount / (double)PageSize));
        if (PageIndex > TotalPages) PageIndex = TotalPages;
        if (PageIndex < 1) PageIndex = 1;

        var skip = (PageIndex - 1) * PageSize;
        var list = await _data.GetFunctionsAsync(
            search: search,
            peripheralName: peri,
            chipName: chip,
            form: form,
            skip: skip,
            take: PageSize,
            parseStatus: parseStatus);

        Items.Clear();
        foreach (var f in list)
        {
            var row = new LlFunctionRowItem(f)
            {
                IsSelected = _checkedIds.Contains(f.Id)
            };
            row.SelectionChanged += OnRowSelectionChanged;
            Items.Add(row);
        }

        var from = TotalCount == 0 ? 0 : skip + 1;
        var to = Math.Min(skip + Items.Count, TotalCount);
        PageInfoText = $"匹配总数: {TotalCount}　第 {PageIndex}/{TotalPages} 页　显示 {from}-{to}";
        CanGoPrevious = PageIndex > 1;
        CanGoNext = PageIndex < TotalPages;
        SyncCheckedUi();

        SelectedItem = preserveSelectedId is Guid id
            ? Items.FirstOrDefault(x => x.Function.Id == id) ?? Items.FirstOrDefault()
            : Items.FirstOrDefault();
    }

    partial void OnSelectedItemChanged(LlFunctionRowItem? value)
    {
        NotifyParseCommands();
        if (value is null)
        {
            ClearDetail();
            return;
        }

        _ = LoadDetailAsync(value.Function.Id);
    }

    private void OnRowSelectionChanged(LlFunctionRowItem item)
    {
        if (item.IsSelected) _checkedIds.Add(item.Function.Id);
        else _checkedIds.Remove(item.Function.Id);
        SyncCheckedUi();
        NotifyParseCommands();
    }

    private void SyncCheckedUi(bool updateAllFlag = true)
    {
        CheckedCountText = $"已勾选 {_checkedIds.Count}";
        if (!updateAllFlag) return;
        _suppressAllSelectedSync = true;
        IsAllOnPageSelected = Items.Count > 0 && Items.All(x => x.IsSelected);
        _suppressAllSelectedSync = false;
    }

    private List<Guid> GetCheckedOrHighlightedIds()
    {
        if (_checkedIds.Count > 0)
            return _checkedIds.ToList();
        return SelectedItem is not null ? new List<Guid> { SelectedItem.Function.Id } : new List<Guid>();
    }

    private async Task LoadDetailAsync(Guid id)
    {
        var detail = await _data.GetFunctionDetailAsync(id);
        if (detail is null)
        {
            ClearDetail();
            return;
        }

        var fn = detail.Function;
        ParseStatusText = fn.ParseStatus ?? LlParseStatus.NotParsed.ToString();
        DetailSignature = !string.IsNullOrWhiteSpace(fn.Signature)
            ? fn.Signature!
            : $"{fn.ReturnType ?? "?"} {fn.FunctionName}({fn.Parameters})";

        if (detail.Parameters.Count > 0)
        {
            var sb = new StringBuilder();
            foreach (var p in detail.Parameters)
                sb.AppendLine($"{p.Position}: {p.Type} {p.Name}");
            DetailParameters = sb.ToString().TrimEnd();
        }
        else
            DetailParameters = string.IsNullOrWhiteSpace(fn.Parameters) ? "尚未解析" : fn.Parameters!;

        DetailReturn = fn.ReturnType ?? "尚未解析";
        DetailSource = !string.IsNullOrWhiteSpace(fn.SourceText)
            ? fn.SourceText!
            : $"{fn.FilePath}:{fn.StartLine}-{fn.EndLine}";

        DetailOperations = detail.Operations.Count == 0
            ? "尚未解析"
            : string.Join(Environment.NewLine, detail.Operations.Take(80).Select(o => $"{o.Sequence}: [{o.OpKind}] L{o.StartLine} {o.SourceText}"));

        DetailRegisters = detail.RegisterAccesses.Count == 0
            ? "尚未解析"
            : string.Join(Environment.NewLine, detail.RegisterAccesses.Select(r =>
                $"{r.AccessKind} {(r.MacroName is not null ? r.MacroName + " " : "")}{r.RegisterPath ?? r.Expression}"));

        DetailMacros = detail.RegisterReferences.Count == 0
            ? "尚未解析"
            : string.Join(Environment.NewLine, detail.RegisterReferences.Take(50).Select(m => $"L{m.ReferenceLine}: {m.MacroName}"));

        DetailCallGraph = detail.Calls.Count == 0
            ? "尚未解析"
            : string.Join(Environment.NewLine, detail.Calls.Select(c => $"{c.CalleeName} ({c.CalleeKind}) x{c.CallCount} @L{c.CallLine}"));

        DetailDiagnostics = detail.Diagnostics.Count == 0
            ? "无"
            : string.Join(Environment.NewLine, detail.Diagnostics.Take(30).Select(d => $"[{d.Severity}/{d.Category}] {d.Message}"));
    }

    private void ClearDetail()
    {
        DetailSignature = DetailParameters = DetailReturn = DetailSource = DetailOperations =
            DetailRegisters = DetailMacros = DetailCallGraph = DetailDiagnostics = "尚未解析";
        ParseStatusText = LlParseStatus.NotParsed.ToString();
    }

    private static string? NullIfEmpty(string? s) => string.IsNullOrWhiteSpace(s) ? null : s.Trim();
}

public sealed class LlFunctionRowItem : ObservableObject
{
    private bool _isSelected;

    public LlFunctionRowItem(LlFunction function) => Function = function;

    public LlFunction Function { get; }

    public string FunctionName => Function.FunctionName;
    public string? ChipName => Function.ChipName;
    public string? PeripheralName => Function.PeripheralName;
    public string? Form => Function.Form;
    public string? ParseStatus => Function.ParseStatus;
    public string? FilePath => Function.FilePath;
    public int StartLine => Function.StartLine;

    public bool IsSelected
    {
        get => _isSelected;
        set
        {
            if (SetProperty(ref _isSelected, value))
                SelectionChanged?.Invoke(this);
        }
    }

    public event Action<LlFunctionRowItem>? SelectionChanged;
}
