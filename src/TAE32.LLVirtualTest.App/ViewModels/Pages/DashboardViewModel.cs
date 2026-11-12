using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
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
    }
}
