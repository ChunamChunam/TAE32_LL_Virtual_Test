using System.Collections.ObjectModel;
using System.Globalization;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class VirtualMcuViewModel : ObservableObject
{
    private readonly IVirtualMcuService _mcu;
    private readonly IAppDataService _data;
    private readonly ISdkProjectService _projects;
    private bool _suppressMcuSelectionReload;
    private bool _suppressChipWorkspaceReload;
    private bool _suppressPageReload;
    private int _reloadGate;
    private List<VirtualRegisterRow> _registerCache = new();

    public ObservableCollection<Chip> ChipFilters { get; } = new();
    public ObservableCollection<VirtualMcuInfo> McuInstances { get; } = new();
    public ObservableCollection<VirtualPeripheralTreeNode> PeripheralTree { get; } = new();
    public ObservableCollection<VirtualRegisterRow> Registers { get; } = new();
    public ObservableCollection<VirtualBitFieldView> BitFields { get; } = new();
    public ObservableCollection<VirtualAccessRecord> TraceItems { get; } = new();
    public ObservableCollection<VirtualPeripheralView> PeripheralStates { get; } = new();
    public ObservableCollection<VirtualMcuSnapshotInfo> Snapshots { get; } = new();
    public ObservableCollection<int> PageSizeOptions { get; } = new() { 50, 100, 200, 300, 500 };

    [ObservableProperty] private Chip? _selectedChip;
    [ObservableProperty] private VirtualMcuInfo? _selectedMcu;
    [ObservableProperty] private VirtualPeripheralTreeNode? _selectedTreeNode;
    [ObservableProperty] private VirtualRegisterRow? _selectedRegister;
    [ObservableProperty] private VirtualMcuSnapshotInfo? _selectedSnapshot;
    [ObservableProperty] private string _statusText = "尚未创建虚拟 MCU";
    [ObservableProperty] private string _writeValueText = "0";
    [ObservableProperty] private string _bitFieldName = string.Empty;
    [ObservableProperty] private string _bitFieldValueText = "0";
    [ObservableProperty] private string _traceFilterRegister = string.Empty;
    [ObservableProperty] private string _traceFilterFunction = string.Empty;
    [ObservableProperty] private string _limitationSummary = string.Empty;
    [ObservableProperty] private bool _isBusy;
    [ObservableProperty] private string _registerSearchText = string.Empty;
    [ObservableProperty] private int _registerTotalCount;
    [ObservableProperty] private int _registerPageIndex = 1;
    [ObservableProperty] private int _registerPageSize = 100;
    [ObservableProperty] private int _registerTotalPages = 1;
    [ObservableProperty] private string _registerPageInfoText = string.Empty;
    [ObservableProperty] private bool _canGoPreviousRegisterPage;
    [ObservableProperty] private bool _canGoNextRegisterPage;

    public VirtualMcuViewModel(IVirtualMcuService mcu, IAppDataService data, ISdkProjectService projects)
    {
        _mcu = mcu;
        _data = data;
        _projects = projects;
    }

    partial void OnSelectedChipChanged(Chip? value)
    {
        if (_suppressChipWorkspaceReload || value is null) return;
        _ = ApplyChipWorkspaceAsync(value);
    }

    private async Task ApplyChipWorkspaceAsync(Chip chip)
    {
        try
        {
            await _projects.SetCurrentAsync(chip.SdkProjectId);
            var proj = await _projects.GetByIdAsync(chip.SdkProjectId);
            StatusText = $"工作 SDK 已切换为 {proj?.Name ?? chip.ModelName}（芯片 {chip.ModelName}）";
        }
        catch (Exception ex)
        {
            StatusText = $"切换芯片工作区失败：{ex.Message}";
        }
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        var chips = await _data.GetChipsAsync();
        var current = await _projects.GetCurrentAsync();
        ChipFilters.Clear();
        foreach (var c in chips.OrderBy(x => x.ModelName, StringComparer.OrdinalIgnoreCase))
            ChipFilters.Add(c);

        _suppressChipWorkspaceReload = true;
        try
        {
            if (SelectedChip is not null && ChipFilters.Any(x => x.Id == SelectedChip.Id))
            {
                // keep selection
            }
            else if (current is not null)
                SelectedChip = ChipFilters.FirstOrDefault(c => c.SdkProjectId == current.Id) ?? ChipFilters.FirstOrDefault();
            else
                SelectedChip = ChipFilters.FirstOrDefault();
        }
        finally
        {
            _suppressChipWorkspaceReload = false;
        }

        await ReloadMcuListAsync();
    }

    [RelayCommand]
    private async Task CreateAndInitAsync()
    {
        if (SelectedChip is null)
        {
            StatusText = "请先选择芯片型号";
            return;
        }

        IsBusy = true;
        try
        {
            var chipId = SelectedChip.Id;
            var chipName = SelectedChip.ModelName;
            var sdkProjectId = SelectedChip.SdkProjectId;
            await _projects.SetCurrentAsync(sdkProjectId);
            // Create+init loads register space / chip.h — keep off UI thread.
            var info = await Task.Run(async () =>
            {
                var created = await _mcu.CreateAsync(new VirtualMcuCreateOptions
                {
                    ChipId = chipId,
                    ChipModelName = chipName,
                    SdkProjectId = sdkProjectId,
                    DisplayName = $"VM-{chipName}-{DateTime.Now:HHmmss}"
                });
                await _mcu.InitializeAsync(created.Id);
                return created;
            }).ConfigureAwait(true);
            StatusText = $"已创建并初始化：{info.DisplayName}";
            await ReloadMcuListAsync(preferId: info.Id);
        }
        catch (Exception ex)
        {
            StatusText = $"创建失败：{ex.Message}";
        }
        finally
        {
            IsBusy = false;
        }
    }

    [RelayCommand]
    private async Task ResetMcuAsync()
    {
        if (SelectedMcu is null) return;
        await _mcu.ResetAsync(SelectedMcu.Id);
        StatusText = "虚拟 MCU 已复位";
        await ReloadSelectedMcuViewsAsync();
    }

    [RelayCommand]
    private async Task DestroyMcuAsync()
    {
        if (SelectedMcu is null) return;
        var id = SelectedMcu.Id;
        await _mcu.DestroyAsync(id);
        StatusText = "虚拟 MCU 已销毁";
        await ReloadMcuListAsync();
    }

    [RelayCommand]
    private async Task TakeSnapshotAsync()
    {
        if (SelectedMcu is null) return;
        var snap = await _mcu.TakeSnapshotAsync(SelectedMcu.Id, $"snap-{DateTime.Now:HHmmss}");
        StatusText = $"已快照 {snap.SnapshotId.ToString()[..8]}…";
        await ReloadSnapshotsAsync();
    }

    [RelayCommand]
    private async Task RestoreSnapshotAsync()
    {
        if (SelectedMcu is null || SelectedSnapshot is null) return;
        await _mcu.RestoreSnapshotAsync(SelectedMcu.Id, SelectedSnapshot.SnapshotId);
        StatusText = "已从快照恢复";
        await ReloadSelectedMcuViewsAsync();
    }

    [RelayCommand]
    private async Task ReadRegisterAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        var r = await _mcu.ReadAsync(mcuId, inst, member, UiContext("手动读"));
        StatusText = FormatResult("读", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private async Task WriteRegisterAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        if (!TryParseUInt(WriteValueText, out var value))
        {
            StatusText = "写入值无效（支持 0x 十六进制或十进制）";
            return;
        }

        var r = await _mcu.WriteAsync(mcuId, inst, member, value, UiContext("手动写"));
        StatusText = FormatResult("写", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private async Task SetBitsAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        if (!TryParseUInt(WriteValueText, out var mask))
        {
            StatusText = "掩码无效";
            return;
        }
        var r = await _mcu.SetBitsAsync(mcuId, inst, member, mask, UiContext("置位"));
        StatusText = FormatResult("置位", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private async Task ClearBitsAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        if (!TryParseUInt(WriteValueText, out var mask))
        {
            StatusText = "掩码无效";
            return;
        }
        var r = await _mcu.ClearBitsAsync(mcuId, inst, member, mask, UiContext("清位"));
        StatusText = FormatResult("清位", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private async Task WriteBitFieldAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        if (string.IsNullOrWhiteSpace(BitFieldName))
        {
            StatusText = "请输入位域名";
            return;
        }
        if (!TryParseUInt(BitFieldValueText, out var fv))
        {
            StatusText = "位域值无效";
            return;
        }
        var r = await _mcu.WriteBitFieldAsync(mcuId, inst, member, BitFieldName.Trim(), fv, UiContext("位域写"));
        StatusText = FormatResult("位域", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private async Task ResetRegisterAsync()
    {
        if (!TryGetSelectedKeys(out var mcuId, out var inst, out var member)) return;
        var r = await _mcu.ResetRegisterAsync(mcuId, inst, member, UiContext("寄存器复位"));
        StatusText = FormatResult("复位", r);
        await AfterAccessAsync();
    }

    [RelayCommand]
    private void SearchRegisters()
    {
        RegisterPageIndex = 1;
        ApplyRegisterPage();
    }

    [RelayCommand(CanExecute = nameof(CanGoPreviousRegisterPage))]
    private void PreviousRegisterPage()
    {
        if (RegisterPageIndex <= 1) return;
        RegisterPageIndex--;
        ApplyRegisterPage();
    }

    [RelayCommand(CanExecute = nameof(CanGoNextRegisterPage))]
    private void NextRegisterPage()
    {
        if (RegisterPageIndex >= RegisterTotalPages) return;
        RegisterPageIndex++;
        ApplyRegisterPage();
    }

    [RelayCommand]
    private void FirstRegisterPage()
    {
        if (RegisterPageIndex == 1) return;
        RegisterPageIndex = 1;
        ApplyRegisterPage();
    }

    [RelayCommand]
    private void LastRegisterPage()
    {
        if (RegisterPageIndex >= RegisterTotalPages) return;
        RegisterPageIndex = Math.Max(1, RegisterTotalPages);
        ApplyRegisterPage();
    }

    partial void OnRegisterPageSizeChanged(int value)
    {
        if (_suppressPageReload || value <= 0) return;
        RegisterPageIndex = 1;
        ApplyRegisterPage();
    }

    partial void OnCanGoPreviousRegisterPageChanged(bool value) => PreviousRegisterPageCommand.NotifyCanExecuteChanged();
    partial void OnCanGoNextRegisterPageChanged(bool value) => NextRegisterPageCommand.NotifyCanExecuteChanged();

    [RelayCommand]
    private async Task RefreshTraceAsync()
    {
        if (SelectedMcu is null) return;
        var list = await _mcu.GetAccessTraceAsync(SelectedMcu.Id, new VirtualAccessFilter
        {
            RegisterName = string.IsNullOrWhiteSpace(TraceFilterRegister) ? null : TraceFilterRegister.Trim(),
            LlFunctionName = string.IsNullOrWhiteSpace(TraceFilterFunction) ? null : TraceFilterFunction.Trim(),
            Take = 300
        });
        TraceItems.Clear();
        foreach (var t in list) TraceItems.Add(t);
    }

    [RelayCommand]
    private async Task ClearTraceAsync()
    {
        if (SelectedMcu is null) return;
        await _mcu.ClearAccessTraceAsync(SelectedMcu.Id);
        TraceItems.Clear();
        StatusText = "访问追踪已清空";
    }

    partial void OnSelectedMcuChanged(VirtualMcuInfo? value)
    {
        if (_suppressMcuSelectionReload) return;
        if (value is null)
        {
            PeripheralTree.Clear();
            Registers.Clear();
            BitFields.Clear();
            TraceItems.Clear();
            PeripheralStates.Clear();
            Snapshots.Clear();
            return;
        }
        _ = SafeReloadSelectedMcuViewsAsync();
    }

    partial void OnSelectedTreeNodeChanged(VirtualPeripheralTreeNode? value)
    {
        if (_suppressMcuSelectionReload) return;
        _ = SafeReloadRegistersForTreeAsync();
    }

    partial void OnSelectedRegisterChanged(VirtualRegisterRow? value)
    {
        BitFields.Clear();
        if (value is null) return;
        foreach (var f in value.Fields) BitFields.Add(f);
        if (BitFields.Count > 0)
            BitFieldName = BitFields[0].Name;
        WriteValueText = $"0x{value.CurrentValue:X8}";
    }

    private async Task SafeReloadSelectedMcuViewsAsync()
    {
        try { await ReloadSelectedMcuViewsAsync(); }
        catch (Exception ex) { StatusText = $"加载虚拟 MCU 视图失败：{ex.Message}"; }
    }

    private async Task SafeReloadRegistersForTreeAsync()
    {
        try { await ReloadRegistersForTreeAsync(); }
        catch (Exception ex) { StatusText = $"加载寄存器列表失败：{ex.Message}"; }
    }

    private async Task ReloadMcuListAsync(Guid? preferId = null)
    {
        var keep = preferId ?? SelectedMcu?.Id;
        var list = await _mcu.ListAsync();
        _suppressMcuSelectionReload = true;
        try
        {
            McuInstances.Clear();
            foreach (var m in list) McuInstances.Add(m);
            SelectedMcu = keep is Guid id
                ? McuInstances.FirstOrDefault(x => x.Id == id) ?? McuInstances.FirstOrDefault()
                : McuInstances.FirstOrDefault();
        }
        finally
        {
            _suppressMcuSelectionReload = false;
        }

        if (SelectedMcu is not null)
            await ReloadSelectedMcuViewsAsync();
    }

    private async Task ReloadSelectedMcuViewsAsync()
    {
        if (SelectedMcu is null) return;
        if (Interlocked.Exchange(ref _reloadGate, 1) == 1) return;
        try
        {
            var mcuId = SelectedMcu.Id;
            var info = await _mcu.GetInfoAsync(mcuId);
            if (info is not null)
            {
                LimitationSummary = info.ActiveLimitations.Count == 0
                    ? "当前无显著模拟限制标记"
                    : string.Join("；", info.ActiveLimitations.Take(8));

                _suppressMcuSelectionReload = true;
                try
                {
                    var idx = -1;
                    for (var i = 0; i < McuInstances.Count; i++)
                    {
                        if (McuInstances[i].Id == info.Id) { idx = i; break; }
                    }
                    if (idx >= 0)
                        McuInstances[idx] = info;
                    // keep SelectedMcu pointing at updated info without re-entrancy
                    SelectedMcu = info;
                }
                finally
                {
                    _suppressMcuSelectionReload = false;
                }
            }

            var tree = await _mcu.GetPeripheralTreeAsync(mcuId);
            var firstChild = tree.SelectMany(m => m.Children).FirstOrDefault()
                             ?? tree.FirstOrDefault();

            _suppressMcuSelectionReload = true;
            try
            {
                PeripheralTree.Clear();
                foreach (var n in tree) PeripheralTree.Add(n);
                SelectedTreeNode = firstChild;
            }
            finally
            {
                _suppressMcuSelectionReload = false;
            }

            PeripheralStates.Clear();
            foreach (var p in await _mcu.GetPeripheralStatesAsync(mcuId))
                PeripheralStates.Add(p);

            await ReloadSnapshotsAsync();
            await ReloadRegistersForTreeAsync();
            await RefreshTraceAsync();
        }
        finally
        {
            Interlocked.Exchange(ref _reloadGate, 0);
        }
    }

    private async Task ReloadRegistersForTreeAsync(bool resetPage = true)
    {
        if (SelectedMcu is null) return;
        string? module = null;
        string? instance = null;
        if (SelectedTreeNode is { IsModule: true })
            module = SelectedTreeNode.ModuleName;
        else if (SelectedTreeNode is not null)
        {
            module = SelectedTreeNode.ModuleName;
            instance = SelectedTreeNode.InstanceName;
        }

        var regs = await _mcu.GetRegistersAsync(SelectedMcu.Id, module, instance);
        _registerCache = regs.Select(VirtualRegisterRow.From).ToList();
        if (resetPage)
        {
            _suppressPageReload = true;
            try { RegisterPageIndex = 1; }
            finally { _suppressPageReload = false; }
        }
        ApplyRegisterPage(keepDisplayName: SelectedRegister?.DisplayName);
    }

    private void ApplyRegisterPage(string? keepDisplayName = null)
    {
        keepDisplayName ??= SelectedRegister?.DisplayName;
        IEnumerable<VirtualRegisterRow> q = _registerCache;
        if (!string.IsNullOrWhiteSpace(RegisterSearchText))
        {
            var s = RegisterSearchText.Trim();
            q = q.Where(r =>
                r.DisplayName.Contains(s, StringComparison.OrdinalIgnoreCase)
                || r.MemberName.Contains(s, StringComparison.OrdinalIgnoreCase)
                || r.StructName.Contains(s, StringComparison.OrdinalIgnoreCase)
                || (r.InstanceName?.Contains(s, StringComparison.OrdinalIgnoreCase) ?? false)
                || r.AddressText.Contains(s, StringComparison.OrdinalIgnoreCase)
                || r.CurrentValueText.Contains(s, StringComparison.OrdinalIgnoreCase));
        }

        var filtered = q.ToList();
        RegisterTotalCount = filtered.Count;
        if (RegisterPageSize <= 0) RegisterPageSize = 100;
        RegisterTotalPages = Math.Max(1, (int)Math.Ceiling(RegisterTotalCount / (double)RegisterPageSize));
        if (RegisterPageIndex > RegisterTotalPages) RegisterPageIndex = RegisterTotalPages;
        if (RegisterPageIndex < 1) RegisterPageIndex = 1;

        var skip = (RegisterPageIndex - 1) * RegisterPageSize;
        var page = filtered.Skip(skip).Take(RegisterPageSize).ToList();

        Registers.Clear();
        foreach (var r in page) Registers.Add(r);

        CanGoPreviousRegisterPage = RegisterPageIndex > 1;
        CanGoNextRegisterPage = RegisterPageIndex < RegisterTotalPages;
        RegisterPageInfoText = RegisterTotalCount == 0
            ? "无匹配寄存器"
            : $"第 {RegisterPageIndex}/{RegisterTotalPages} 页，共 {RegisterTotalCount} 条（本页 {Registers.Count}）";

        SelectedRegister = Registers.FirstOrDefault(x => x.DisplayName == keepDisplayName)
                           ?? Registers.FirstOrDefault();
    }

    private async Task ReloadSnapshotsAsync()
    {
        if (SelectedMcu is null) return;
        Snapshots.Clear();
        foreach (var s in await _mcu.ListSnapshotsAsync(SelectedMcu.Id))
            Snapshots.Add(s);
        SelectedSnapshot = Snapshots.FirstOrDefault();
    }

    private async Task AfterAccessAsync()
    {
        await ReloadRegistersForTreeAsync(resetPage: false);
        await RefreshTraceAsync();
        if (SelectedMcu is not null)
        {
            PeripheralStates.Clear();
            foreach (var p in await _mcu.GetPeripheralStatesAsync(SelectedMcu.Id))
                PeripheralStates.Add(p);
        }
    }

    private bool TryGetSelectedKeys(out Guid mcuId, out string inst, out string member)
    {
        mcuId = Guid.Empty;
        inst = string.Empty;
        member = string.Empty;
        if (SelectedMcu is null || SelectedRegister is null)
        {
            StatusText = "请选择虚拟 MCU 与寄存器";
            return false;
        }
        mcuId = SelectedMcu.Id;
        inst = SelectedRegister.InstanceName ?? SelectedRegister.StructName;
        member = SelectedRegister.MemberName;
        return true;
    }

    private static VirtualAccessContext UiContext(string note) => new()
    {
        LlFunctionName = "(UI)",
        SourceFile = "VirtualMcuPage",
        Note = note
    };

    private static bool TryParseUInt(string text, out uint value)
    {
        value = 0;
        if (string.IsNullOrWhiteSpace(text)) return false;
        var s = text.Trim();
        if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            return uint.TryParse(s.AsSpan(2), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out value);
        return uint.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out value);
    }

    private static string FormatResult(string op, VirtualAccessResultDto r)
    {
        var ok = r.Result is Core.Enums.VirtualAccessResult.Ok
            or Core.Enums.VirtualAccessResult.LimitationApplied;
        var head = ok ? $"{op}成功" : $"{op}失败({r.Result})";
        var before = r.ValueBefore is uint b ? $"0x{b:X8}" : "—";
        var after = r.ValueAfter is uint a ? $"0x{a:X8}" : "—";
        var lim = r.Limitation == Core.Enums.SimulationLimitationKind.None
            ? ""
            : $"；限制标记 {r.Limitation}（不影响本次已生效的写入）";
        var msg = string.IsNullOrEmpty(r.Message) ? "" : $" — {r.Message}";
        return $"{head}：{before} → {after}{lim}{msg}";
    }
}

public sealed class VirtualRegisterRow
{
    public Guid DefinitionId { get; init; }
    public string? ModuleName { get; init; }
    public string? InstanceName { get; init; }
    public string StructName { get; init; } = string.Empty;
    public string MemberName { get; init; } = string.Empty;
    public string DisplayName { get; init; } = string.Empty;
    public string AddressText { get; init; } = "—";
    public int WidthBits { get; init; }
    public uint CurrentValue { get; init; }
    public string CurrentValueText { get; init; } = "0x00000000";
    public string ResetValueText { get; init; } = "0x00000000";
    public string AccessAttribute { get; init; } = "Unknown";
    public string Behavior { get; init; } = string.Empty;
    public string WritableMaskText { get; init; } = "0xFFFFFFFF";
    public string Limitation { get; init; } = string.Empty;
    public IReadOnlyList<VirtualBitFieldView> Fields { get; init; } = Array.Empty<VirtualBitFieldView>();

    public static VirtualRegisterRow From(VirtualRegisterView r) => new()
    {
        DefinitionId = r.DefinitionId,
        ModuleName = r.ModuleName,
        InstanceName = r.InstanceName,
        StructName = r.StructName,
        MemberName = r.MemberName,
        DisplayName = r.DisplayName,
        AddressText = r.AbsoluteAddress is uint a ? $"0x{a:X8}" : "—",
        WidthBits = r.WidthBits,
        CurrentValue = r.CurrentValue,
        CurrentValueText = $"0x{r.CurrentValue:X8}",
        ResetValueText = $"0x{r.ResetValue:X8}",
        AccessAttribute = r.AccessAttribute,
        Behavior = r.Behavior.ToString(),
        WritableMaskText = $"0x{r.WritableMask:X8}",
        Limitation = r.Limitation == Core.Enums.SimulationLimitationKind.None
            ? ""
            : r.Limitation.ToString(),
        Fields = r.Fields
    };
}
