using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TAE32.LLVirtualTest.App.Services;
using TAE32.LLVirtualTest.App.ViewModels.Pages;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.App.ViewModels;

public partial class MainViewModel : ObservableObject
{
    private readonly NavigationService _navigation;
    private readonly DashboardViewModel _dashboard;
    private readonly SdkManagementViewModel _sdk;
    private readonly ChipManagementViewModel _chips;
    private readonly PeripheralManagementViewModel _peripherals;
    private readonly LlFunctionLibraryViewModel _functions;
    private readonly RegisterManagementViewModel _registers;
    private readonly VirtualMcuViewModel _virtualMcu;
    private readonly AutomationTestViewModel _automationTest;
    private readonly TestManagementViewModel _testManagement;
    private readonly SettingsViewModel _settings;

    [ObservableProperty] private object? _currentPage;
    [ObservableProperty] private string _title = "工作台";
    [ObservableProperty] private string _statusText = "就绪";
    [ObservableProperty] private NavigationItem _selectedNav = NavigationItem.Dashboard;

    public MainViewModel(
        NavigationService navigation,
        DashboardViewModel dashboard,
        SdkManagementViewModel sdk,
        ChipManagementViewModel chips,
        PeripheralManagementViewModel peripherals,
        LlFunctionLibraryViewModel functions,
        RegisterManagementViewModel registers,
        VirtualMcuViewModel virtualMcu,
        AutomationTestViewModel automationTest,
        TestManagementViewModel testManagement,
        SettingsViewModel settings)
    {
        _navigation = navigation;
        _dashboard = dashboard;
        _sdk = sdk;
        _chips = chips;
        _peripherals = peripherals;
        _functions = functions;
        _registers = registers;
        _virtualMcu = virtualMcu;
        _automationTest = automationTest;
        _testManagement = testManagement;
        _settings = settings;
        _navigation.Navigated += OnNavigated;
        CurrentPage = _dashboard;
    }

    public async Task InitializeAsync(string? startupImportSummary = null)
    {
        StatusText = "正在加载工作台…";
        await _dashboard.RefreshAsync();
        StatusText = string.IsNullOrWhiteSpace(startupImportSummary)
            ? "就绪"
            : startupImportSummary;
    }

    [RelayCommand]
    private async Task NavigateAsync(string key)
    {
        if (!Enum.TryParse<NavigationItem>(key, out var item)) return;
        SelectedNav = item;
        _navigation.Navigate(item);
        await LoadPageAsync(item);
    }

    private async void OnNavigated(NavigationItem item) => await LoadPageAsync(item);

    private async Task LoadPageAsync(NavigationItem item)
    {
        StatusText = "加载中…";
        switch (item)
        {
            case NavigationItem.Dashboard:
                Title = "工作台";
                CurrentPage = _dashboard;
                await _dashboard.RefreshAsync();
                break;
            case NavigationItem.SdkManagement:
                Title = "SDK 管理";
                CurrentPage = _sdk;
                await _sdk.RefreshAsync();
                break;
            case NavigationItem.ChipManagement:
                Title = "芯片管理";
                CurrentPage = _chips;
                await _chips.RefreshAsync();
                break;
            case NavigationItem.PeripheralManagement:
                Title = "外设管理";
                CurrentPage = _peripherals;
                await _peripherals.RefreshAsync();
                break;
            case NavigationItem.LlFunctionLibrary:
                Title = "LL 函数库";
                CurrentPage = _functions;
                await _functions.RefreshAsync();
                break;
            case NavigationItem.FunctionCallGraph:
                Title = "函数调用关系";
                CurrentPage = new PlaceholderPageViewModel(
                    "函数调用关系",
                    "第三阶段已将调用关系写入每函数详情（LL 函数库 → 深度解析 → 调用 Tab）。",
                    "独立调用图页面可在后续阶段扩展为全局图可视化。");
                break;
            case NavigationItem.RegisterManagement:
                Title = "寄存器管理";
                CurrentPage = _registers;
                await _registers.RefreshAsync();
                break;
            case NavigationItem.VirtualMcu:
                Title = "虚拟 MCU";
                CurrentPage = _virtualMcu;
                await _virtualMcu.RefreshAsync();
                break;
            case NavigationItem.AutomationTest:
                Title = "自动化测试";
                CurrentPage = _automationTest;
                await _automationTest.RefreshAsync();
                break;
            case NavigationItem.TestReport:
                Title = "测试管理与报告";
                CurrentPage = _testManagement;
                await _testManagement.RefreshAsync();
                break;
            case NavigationItem.Settings:
                Title = "系统设置";
                CurrentPage = _settings;
                await _settings.RefreshDiagnosticsCommand.ExecuteAsync(null);
                break;
        }
        StatusText = "就绪";
    }
}
