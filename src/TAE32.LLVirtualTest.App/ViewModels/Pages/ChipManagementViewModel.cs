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

    public ObservableCollection<ChipRow> Items { get; } = new();

    public ChipManagementViewModel(IAppDataService data, IDbContextFactory<AppDbContext> dbFactory)
    {
        _data = data;
        _dbFactory = dbFactory;
    }

    [RelayCommand]
    public async Task RefreshAsync()
    {
        Items.Clear();
        var chips = await _data.GetChipsAsync();
        await using var db = await _dbFactory.CreateDbContextAsync();
        foreach (var c in chips)
        {
            var peri = await db.Peripherals.AsNoTracking().CountAsync(x => x.ChipId == c.Id);
            var funcs = await db.LlFunctions.AsNoTracking().CountAsync(x => x.ChipId == c.Id);
            var project = await db.SdkProjects.AsNoTracking().FirstOrDefaultAsync(x => x.Id == c.SdkProjectId);
            Items.Add(new ChipRow
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
