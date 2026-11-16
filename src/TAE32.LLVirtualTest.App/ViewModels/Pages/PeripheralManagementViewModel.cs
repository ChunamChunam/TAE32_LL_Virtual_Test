using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class PeripheralManagementViewModel : ObservableObject
{
    private readonly IAppDataService _data;
    private readonly List<PeripheralRow> _all = new();

    public ObservableCollection<PeripheralRow> Items { get; } = new();
    public ObservableCollection<string> StatusFilterOptions { get; } = new() { "全部状态" };

    [ObservableProperty] private string _searchText = string.Empty;
    [ObservableProperty] private string _selectedStatusFilter = "全部状态";

    public PeripheralManagementViewModel(IAppDataService data) => _data = data;

    [RelayCommand]
    public async Task RefreshAsync()
    {
        _all.Clear();
        var list = await _data.GetPeripheralsAsync();
        foreach (var p in list)
        {
            _all.Add(new PeripheralRow
            {
                SerialNumber = p.SerialNumber?.ToString() ?? "—",
                Name = p.Name,
                ChipName = p.Chip?.ModelName ?? "—",
                InlineFunctionCount = p.InlineFunctionCount,
                RelatedFiles = p.RelatedFilesJson ?? "尚未解析",
                Instances = p.InstancesJson ?? "尚未解析",
                DetectionStatus = p.DetectionStatus ?? "—",
                Confidence = p.Confidence ?? "—"
            });
        }

        RebuildStatusFilters();
        ApplyFilter();
    }

    [RelayCommand]
    private void Search() => ApplyFilter();

    partial void OnSelectedStatusFilterChanged(string value) => ApplyFilter();

    private void RebuildStatusFilters()
    {
        var keep = SelectedStatusFilter;
        StatusFilterOptions.Clear();
        StatusFilterOptions.Add("全部状态");
        foreach (var s in _all.Select(x => x.DetectionStatus).Where(x => !string.IsNullOrWhiteSpace(x) && x != "—").Distinct().OrderBy(x => x))
            StatusFilterOptions.Add(s);
        SelectedStatusFilter = StatusFilterOptions.Contains(keep) ? keep : "全部状态";
    }

    private void ApplyFilter()
    {
        Items.Clear();
        var term = string.IsNullOrWhiteSpace(SearchText) ? null : SearchText.Trim();
        var status = string.IsNullOrWhiteSpace(SelectedStatusFilter) || SelectedStatusFilter == "全部状态"
            ? null
            : SelectedStatusFilter;
        foreach (var row in _all)
        {
            if (status is not null && !string.Equals(row.DetectionStatus, status, StringComparison.OrdinalIgnoreCase))
                continue;
            if (term is not null
                && !row.Name.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !row.ChipName.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !row.DetectionStatus.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !row.RelatedFiles.Contains(term, StringComparison.OrdinalIgnoreCase))
                continue;
            Items.Add(row);
        }
    }

    public sealed class PeripheralRow
    {
        public string SerialNumber { get; set; } = "";
        public string Name { get; set; } = "";
        public string ChipName { get; set; } = "";
        public int InlineFunctionCount { get; set; }
        public string RelatedFiles { get; set; } = "";
        public string Instances { get; set; } = "";
        public string DetectionStatus { get; set; } = "";
        public string Confidence { get; set; } = "";
    }
}
