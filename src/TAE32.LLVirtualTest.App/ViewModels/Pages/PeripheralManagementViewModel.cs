using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.Core.Interfaces;

namespace TAE32.LLVirtualTest.App.ViewModels.Pages;

public partial class PeripheralManagementViewModel : ObservableObject
{
    private readonly IAppDataService _data;

    public ObservableCollection<PeripheralRow> Items { get; } = new();

    [ObservableProperty] private string _searchText = string.Empty;

    public PeripheralManagementViewModel(IAppDataService data) => _data = data;

    [RelayCommand]
    public async Task RefreshAsync()
    {
        Items.Clear();
        var list = await _data.GetPeripheralsAsync(search: string.IsNullOrWhiteSpace(SearchText) ? null : SearchText);
        foreach (var p in list)
        {
            Items.Add(new PeripheralRow
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
