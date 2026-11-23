using System.Collections.ObjectModel;
using System.Text;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class RegisterManagementViewModel : ObservableObject
{
    private readonly IAppDataService _data;
    private readonly IRegisterParser _parser;
    private readonly ISdkProjectService _projects;
    private bool _suppressFilterReload;
    private List<PeripheralInstance> _allInstances = new();

    public ObservableCollection<RegisterCatalogDto> Items { get; } = new();
    public ObservableCollection<Chip> ChipFilters { get; } = new();
    public ObservableCollection<Peripheral> PeripheralFilters { get; } = new();
    public ObservableCollection<PeripheralInstance> InstanceFilters { get; } = new();
    public ObservableCollection<int> PageSizeOptions { get; } = new() { 50, 100, 200, 300, 500 };

    [ObservableProperty] private string _searchText = string.Empty;
    [ObservableProperty] private Chip? _selectedChip;
    [ObservableProperty] private Peripheral? _selectedPeripheral;
    [ObservableProperty] private PeripheralInstance? _selectedInstance;
    [ObservableProperty] private RegisterCatalogDto? _selectedRegister;
    [ObservableProperty] private string _parseSummaryText = string.Empty;
    [ObservableProperty] private bool _isParsing;
    [ObservableProperty] private string _detailFields = "尚未解析";
    [ObservableProperty] private string _detailMacros = "尚未解析";
    [ObservableProperty] private string _detailDiagnostics = "尚未解析";
    [ObservableProperty] private string _detailMeta = string.Empty;
    [ObservableProperty] private string _emptyHint = string.Empty;
    [ObservableProperty] private bool _hideReserved = true;
    [ObservableProperty] private int _totalCount;
    [ObservableProperty] private int _pageIndex = 1;
    [ObservableProperty] private int _pageSize = 100;
    [ObservableProperty] private int _totalPages = 1;
    [ObservableProperty] private string _pageInfoText = string.Empty;
    [ObservableProperty] private bool _canGoPrevious;
    [ObservableProperty] private bool _canGoNext;

    public RegisterManagementViewModel(IAppDataService data, IRegisterParser parser, ISdkProjectService projects)
    {
        _data = data;
        _parser = parser;
        _projects = projects;
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        await LoadFiltersAsync();
        PageIndex = 1;
        await LoadPageAsync();
    }

    [RelayCommand(CanExecute = nameof(CanParse))]
    private async Task ParseRegistersAsync()
    {
        var project = await _projects.GetCurrentAsync();
        if (project is null)
        {
            ParseSummaryText = "无可用 SDK 项目";
            EmptyHint = ParseSummaryText;
            return;
        }

        IsParsing = true;
        ParseRegistersCommand.NotifyCanExecuteChanged();
        ParseSummaryText = "寄存器解析进行中…";
        EmptyHint = ParseSummaryText;
        try
        {
            var projectId = project.Id;
            var summary = await Task.Run(async () => await _parser.ParseAsync(projectId));
            ParseSummaryText =
                $"解析完成：实例 {summary.InstanceCount}，寄存器 {summary.RegisterCount}，字段 {summary.FieldCount}，宏引用 {summary.MacroReferenceCount}（已解析数值 {summary.ResolvedMacroCount}），诊断 {summary.DiagnosticCount}"
                + (summary.UsedParseBridgeEvidenceOnly ? "（仅 LL 证据）" : "（设备头）");

            await LoadFiltersAsync(preferAll: true);
            PageIndex = 1;
            await LoadPageAsync();
        }
        catch (Exception ex)
        {
            ParseSummaryText = $"解析失败：{ex.Message}";
            EmptyHint = ParseSummaryText;
        }
        finally
        {
            IsParsing = false;
            ParseRegistersCommand.NotifyCanExecuteChanged();
        }
    }

    private bool CanParse() => !IsParsing;

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

    partial void OnHideReservedChanged(bool value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedChipChanged(Chip? value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedPeripheralChanged(Peripheral? value)
    {
        if (_suppressFilterReload) return;
        RebuildInstanceFilter();
        _ = ResetAndReloadAsync();
    }

    partial void OnSelectedInstanceChanged(PeripheralInstance? value)
    {
        if (_suppressFilterReload) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnPageSizeChanged(int value)
    {
        if (_suppressFilterReload || value <= 0) return;
        _ = ResetAndReloadAsync();
    }

    partial void OnCanGoPreviousChanged(bool value) => PreviousPageCommand.NotifyCanExecuteChanged();
    partial void OnCanGoNextChanged(bool value) => NextPageCommand.NotifyCanExecuteChanged();

    partial void OnSelectedRegisterChanged(RegisterCatalogDto? value)
    {
        if (value is null)
        {
            _ = LoadProjectDiagnosticsAsync();
            return;
        }
        _ = LoadDetailAsync(value.Register.Id);
    }

    private async Task ResetAndReloadAsync()
    {
        PageIndex = 1;
        await LoadPageAsync();
    }

    private async Task LoadFiltersAsync(bool preferAll = false)
    {
        _suppressFilterReload = true;
        try
        {
            var prevChipId = preferAll ? Guid.Empty : SelectedChip?.Id;
            var prevPeriId = preferAll ? Guid.Empty : SelectedPeripheral?.Id;
            var prevInstId = preferAll ? Guid.Empty : SelectedInstance?.Id;

            var chips = await _data.GetChipsAsync();
            var peris = await _data.GetPeripheralsAsync();
            _allInstances = (await _data.GetPeripheralInstancesAsync()).ToList();

            ChipFilters.Clear();
            ChipFilters.Add(new Chip { Id = Guid.Empty, ModelName = "(全部)" });
            foreach (var c in chips) ChipFilters.Add(c);

            PeripheralFilters.Clear();
            PeripheralFilters.Add(new Peripheral { Id = Guid.Empty, Name = "(全部)" });
            foreach (var p in peris) PeripheralFilters.Add(p);

            SelectedChip = ChipFilters.FirstOrDefault(c => c.Id == prevChipId) ?? ChipFilters[0];
            SelectedPeripheral = PeripheralFilters.FirstOrDefault(p => p.Id == prevPeriId) ?? PeripheralFilters[0];
            RebuildInstanceFilter(prevInstId);
        }
        finally
        {
            _suppressFilterReload = false;
        }
    }

    private void RebuildInstanceFilter(Guid? preferredId = null)
    {
        _suppressFilterReload = true;
        try
        {
            var keepId = preferredId ?? SelectedInstance?.Id ?? Guid.Empty;
            InstanceFilters.Clear();
            InstanceFilters.Add(new PeripheralInstance { Id = Guid.Empty, Name = "(全部)" });

            IEnumerable<PeripheralInstance> src = _allInstances;
            if (SelectedPeripheral is { Id: var periId } && periId != Guid.Empty)
            {
                src = _allInstances.Where(i =>
                    i.PeripheralId == periId
                    || string.Equals(i.ModuleName, SelectedPeripheral.Name, StringComparison.OrdinalIgnoreCase));
            }

            foreach (var i in src.OrderBy(x => x.ModuleName).ThenBy(x => x.Name))
                InstanceFilters.Add(i);

            SelectedInstance = InstanceFilters.FirstOrDefault(i => i.Id == keepId) ?? InstanceFilters[0];
        }
        finally
        {
            _suppressFilterReload = false;
        }
    }

    private async Task LoadPageAsync()
    {
        try
        {
            Guid? chipId = SelectedChip is null || SelectedChip.Id == Guid.Empty ? null : SelectedChip.Id;
            Guid? periId = SelectedPeripheral is null || SelectedPeripheral.Id == Guid.Empty ? null : SelectedPeripheral.Id;
            Guid? instId = SelectedInstance is null || SelectedInstance.Id == Guid.Empty ? null : SelectedInstance.Id;
            var search = string.IsNullOrWhiteSpace(SearchText) ? null : SearchText.Trim();

            TotalCount = await _data.CountRegistersAsync(
                chipId: chipId, peripheralId: periId, instanceId: instId,
                search: search, hideReserved: HideReserved);

            TotalPages = Math.Max(1, (int)Math.Ceiling(TotalCount / (double)PageSize));
            if (PageIndex > TotalPages) PageIndex = TotalPages;
            if (PageIndex < 1) PageIndex = 1;

            var skip = (PageIndex - 1) * PageSize;
            var list = await _data.GetRegistersAsync(
                chipId: chipId, peripheralId: periId, instanceId: instId,
                search: search, hideReserved: HideReserved, skip: skip, take: PageSize);

            Items.Clear();
            foreach (var r in list) Items.Add(r);

            CanGoPrevious = PageIndex > 1;
            CanGoNext = PageIndex < TotalPages;
            PageInfoText = TotalCount == 0
                ? "无匹配寄存器"
                : $"第 {PageIndex}/{TotalPages} 页，共 {TotalCount} 条（本页 {Items.Count}）";

            if (Items.Count == 0)
            {
                SelectedRegister = null;
                var totalAll = await _data.CountRegistersAsync(hideReserved: false);
                EmptyHint = totalAll == 0
                    ? "数据库中尚无寄存器数据。请点击「解析寄存器」。"
                    : "当前筛选无结果。可改选「(全部)」、取消隐藏保留位，或清空搜索后查询。";
                DetailMeta = EmptyHint;
                DetailFields = EmptyHint;
                DetailMacros = "—";
                await LoadProjectDiagnosticsAsync();
            }
            else
            {
                EmptyHint = string.Empty;
                SelectedRegister = Items.FirstOrDefault();
            }
        }
        catch (Exception ex)
        {
            EmptyHint = $"加载失败：{ex.Message}";
            ParseSummaryText = EmptyHint;
            Items.Clear();
        }
    }

    private async Task LoadDetailAsync(Guid id)
    {
        var detail = await _data.GetRegisterDetailAsync(id);
        if (detail is null)
        {
            await LoadProjectDiagnosticsAsync();
            return;
        }

        var r = detail.Register;
        DetailMeta =
            $"结构体 {r.StructName}　成员 {r.MemberName}　偏移 {FormatOffset(r)}　绝对地址 {FormatAddress(r)}　宽度 {r.WidthBits?.ToString() ?? "—"}　访问 {r.AccessAttribute}　状态 {r.ParseStatus}";

        if (detail.Fields.Count > 0)
        {
            var sb = new StringBuilder();
            foreach (var f in detail.Fields)
                sb.AppendLine($"{f.Name}: pos={f.BitPosition?.ToString() ?? "—"} width={f.BitWidth?.ToString() ?? "—"} {f.PosMacroName} {f.MskMacroName}");
            DetailFields = sb.ToString().TrimEnd();
        }
        else DetailFields = "无位域字段（或该寄存器无 *_Pos/*_Msk 定义）";

        DetailMacros = detail.Macros.Count == 0
            ? "无"
            : string.Join(Environment.NewLine, detail.Macros.Take(80).Select(m =>
                $"{m.MacroName} [{m.MacroKind}] resolved={m.Resolved} L{m.ReferenceLine}"));

        DetailDiagnostics = detail.Diagnostics.Count == 0
            ? "无"
            : string.Join(Environment.NewLine, detail.Diagnostics.Take(30).Select(d =>
                $"[{d.Severity}/{d.Category}] {d.Message}"));
    }

    private async Task LoadProjectDiagnosticsAsync()
    {
        try
        {
            var diags = await _data.GetRegisterParseDiagnosticsAsync();
            DetailDiagnostics = diags.Count == 0
                ? "尚无解析诊断。请先执行「解析寄存器」。"
                : string.Join(Environment.NewLine, diags.Take(30).Select(d =>
                    $"[{d.Severity}/{d.Category}] {d.Message}"));
        }
        catch
        {
            DetailDiagnostics = "无法读取诊断。";
        }
    }

    private static string FormatOffset(RegisterDefinition r)
        => r.OffsetBytes is int o ? $"0x{o:X} / {o} ({r.OffsetStatus})" : $"— ({r.OffsetStatus})";

    private static string FormatAddress(RegisterDefinition r)
        => r.AbsoluteAddress is uint a ? $"0x{a:X8} ({r.AbsoluteAddressStatus})" : $"— ({r.AbsoluteAddressStatus})";
}
