using System.ComponentModel;
using System.Windows.Data;
using CommunityToolkit.Mvvm.ComponentModel;
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
    private readonly FunctionCallGraphViewModel _callGraph;
    private readonly RegisterManagementViewModel _registers;
    private readonly VirtualMcuViewModel _virtualMcu;
    private readonly AutomationTestViewModel _automationTest;
    private readonly TestManagementViewModel _testManagement;
    private readonly SettingsViewModel _settings;
    private bool _navReady;

    [ObservableProperty] private object? _currentPage;
    [ObservableProperty] private string _title = "工作台";
    [ObservableProperty] private string _statusText = "就绪";
    [ObservableProperty] private NavigationItem _selectedNav = NavigationItem.Dashboard;

    public IReadOnlyList<NavMenuItem> NavItems { get; }
    public ICollectionView NavItemsView { get; }
    public UiScaleService Ui { get; }

    public MainViewModel(
        UiScaleService ui,
        NavigationService navigation,
        DashboardViewModel dashboard,
        SdkManagementViewModel sdk,
        ChipManagementViewModel chips,
        PeripheralManagementViewModel peripherals,
        LlFunctionLibraryViewModel functions,
        FunctionCallGraphViewModel callGraph,
        RegisterManagementViewModel registers,
        VirtualMcuViewModel virtualMcu,
        AutomationTestViewModel automationTest,
        TestManagementViewModel testManagement,
        SettingsViewModel settings)
    {
        Ui = ui;
        Ui.PropertyChanged += (_, e) =>
        {
            if (e.PropertyName is nameof(UiScaleService.Scale) or nameof(UiScaleService.ScaleTransform))
                OnPropertyChanged(nameof(ClientScaleTransform));
        };
        _navigation = navigation;
        _dashboard = dashboard;
        _sdk = sdk;
        _chips = chips;
        _peripherals = peripherals;
        _functions = functions;
        _callGraph = callGraph;
        _registers = registers;
        _virtualMcu = virtualMcu;
        _automationTest = automationTest;
        _testManagement = testManagement;
        _settings = settings;
        var list = new List<NavMenuItem>
        {
            new() { Item = NavigationItem.Dashboard, Title = "工作台", Glyph = "\uE80F", Group = "概览" },
            new() { Item = NavigationItem.SdkManagement, Title = "SDK 管理", Glyph = "\uE8B7", Group = "数据与建模" },
            new() { Item = NavigationItem.ChipManagement, Title = "芯片管理", Glyph = "\uE964", Group = "数据与建模" },
            new() { Item = NavigationItem.PeripheralManagement, Title = "外设管理", Glyph = "\uE8C8", Group = "数据与建模" },
            new() { Item = NavigationItem.LlFunctionLibrary, Title = "LL 函数库", Glyph = "\uE8A5", Group = "数据与建模" },
            new() { Item = NavigationItem.FunctionCallGraph, Title = "函数调用关系", Glyph = "\uE81E", Group = "数据与建模" },
            new() { Item = NavigationItem.RegisterManagement, Title = "寄存器管理", Glyph = "\uE8BE", Group = "数据与建模" },
            new() { Item = NavigationItem.VirtualMcu, Title = "虚拟 MCU", Glyph = "\uE8B0", Group = "验证" },
            new() { Item = NavigationItem.AutomationTest, Title = "自动化测试", Glyph = "\uE768", Group = "验证" },
            new() { Item = NavigationItem.TestReport, Title = "测试管理", Glyph = "\uE9D9", Group = "验证" },
            new() { Item = NavigationItem.Settings, Title = "系统设置", Glyph = "\uE713", Group = "系统" }
        };
        NavItems = list;
        var view = CollectionViewSource.GetDefaultView(list);
        view.GroupDescriptions?.Add(new PropertyGroupDescription(nameof(NavMenuItem.Group)));
        NavItemsView = view;
        CurrentPage = _dashboard;
        _navReady = true;
    }

    public System.Windows.Media.Transform ClientScaleTransform => Ui.ScaleTransform;

    partial void OnSelectedNavChanged(NavigationItem value)
    {
        if (!_navReady) return;
        _navigation.Navigate(value);
        _ = LoadPageAsync(value);
    }

    public async Task InitializeAsync(string? startupImportSummary = null)
    {
        StatusText = "正在加载工作台…";
        await _dashboard.RefreshAsync();
        StatusText = string.IsNullOrWhiteSpace(startupImportSummary)
            ? "就绪"
            : startupImportSummary;
    }

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
                CurrentPage = _callGraph;
                await _callGraph.RefreshAsync();
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
                await _automationTest.EnsureLoadedAsync();
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
