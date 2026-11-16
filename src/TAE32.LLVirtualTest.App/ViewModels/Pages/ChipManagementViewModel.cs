using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class ChipManagementViewModel : ObservableObject
{
    private readonly IAppDataService _data;
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly List<ChipRow> _all = new();

    public ObservableCollection<ChipRow> Items { get; } = new();
    public ObservableCollection<string> StatusFilterOptions { get; } = new() { "全部状态" };

    [ObservableProperty] private string _searchText = string.Empty;
    [ObservableProperty] private string _selectedStatusFilter = "全部状态";

    public ChipManagementViewModel(IAppDataService data, IDbContextFactory<AppDbContext> dbFactory)
    {
        _data = data;
        _dbFactory = dbFactory;
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        _all.Clear();
        var chips = await _data.GetChipsAsync();
        await using var db = await _dbFactory.CreateDbContextAsync();
        foreach (var c in chips)
        {
            var peri = await db.Peripherals.AsNoTracking().CountAsync(x => x.ChipId == c.Id);
            var funcs = await db.LlFunctions.AsNoTracking().CountAsync(x => x.ChipId == c.Id);
            var project = await db.SdkProjects.AsNoTracking().FirstOrDefaultAsync(x => x.Id == c.SdkProjectId);
            _all.Add(new ChipRow
            {
                ModelName = c.ModelName,
                Level = c.Level ?? "—",
                DetectionStatus = c.DetectionStatus ?? "—",
                Confidence = c.Confidence ?? "—",
                PeripheralCount = peri,
                FunctionCount = funcs,
                SdkPath = project?.SdkRootPath ?? "—",
                Notes = c.Notes ?? "—"
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
                && !row.ModelName.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !row.DetectionStatus.Contains(term, StringComparison.OrdinalIgnoreCase)
                && !row.SdkPath.Contains(term, StringComparison.OrdinalIgnoreCase))
                continue;
            Items.Add(row);
        }
    }

    public sealed class ChipRow
    {
        public string ModelName { get; set; } = "";
        public string Level { get; set; } = "";
        public string DetectionStatus { get; set; } = "";
        public string Confidence { get; set; } = "";
        public int PeripheralCount { get; set; }
        public int FunctionCount { get; set; }
        public string SdkPath { get; set; } = "";
        public string Notes { get; set; } = "";
    }
}
