using System.IO;
using System.Windows;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Serilog;
using TAE32.LLVirtualTest.App.Services;
using TAE32.LLVirtualTest.App.Views.Dialogs;
using TAE32.LLVirtualTest.App.ViewModels;
using TAE32.LLVirtualTest.App.ViewModels.Pages;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.Logging;
using TAE32.LLVirtualTest.SDK;

namespace TAE32.LLVirtualTest.App;

public partial class App : Application
{
    private ServiceProvider? _services;
    private SingleInstanceGuard? _singleInstance;

    protected override async void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);

        _singleInstance = new SingleInstanceGuard();
        if (!_singleInstance.IsPrimary)
        {
            _singleInstance.RequestActivatePrimary();
            MessageBox.Show(
                "程序已在运行，不能同时打开两个实例。\n已切换到现有窗口。",
                "TAE32 LL Virtual Test",
                MessageBoxButton.OK,
                MessageBoxImage.Information);
            _singleInstance.Dispose();
            _singleInstance = null;
            Shutdown();
            return;
        }

        _singleInstance.BeginListenForActivate(() =>
        {
            Dispatcher.BeginInvoke(() => ActivateMainWindow());
        });

        DispatcherUnhandledException += (_, args) =>
        {
            Log.Error(args.Exception, "Dispatcher unhandled exception: {Detail}", args.Exception.ToString());
            try
            {
                var detail = string.IsNullOrWhiteSpace(args.Exception.Message)
                    ? args.Exception.ToString()
                    : args.Exception.Message;
                MessageDialog.Show("TAE32 LL Virtual Test", detail);
            }
            catch (Exception showEx)
            {
                Log.Error(showEx, "Failed to show exception dialog");
            }
            args.Handled = true;
        };
        AppDomain.CurrentDomain.UnhandledException += (_, args) =>
        {
            if (args.ExceptionObject is Exception ex)
                Log.Fatal(ex, "Unhandled domain exception");
        };
        TaskScheduler.UnobservedTaskException += (_, args) =>
        {
            Log.Error(args.Exception, "Unobserved task exception");
            args.SetObserved();
        };

        try
        {
            Directory.CreateDirectory(AppPaths.DataDirectory);
            Directory.CreateDirectory(AppPaths.LogDirectory);
        }
        catch (Exception ex)
        {
            MessageBox.Show(
                $"无法创建数据目录（请以管理员身份运行）：\n{AppPaths.DataDirectory}\n\n{ex.Message}",
                "TAE32 LL Virtual Test",
                MessageBoxButton.OK,
                MessageBoxImage.Error);
            Shutdown(-1);
            return;
        }

        SerilogConfigurator.Configure(AppPaths.LogDirectory);

        var services = new ServiceCollection();
        services.AddLogging(b =>
        {
            b.ClearProviders();
            b.AddSerilog(dispose: true);
        });
        services.AddInfrastructure(AppPaths.DatabasePath, AppPaths.LogDirectory);
        services.AddSdkServices();
        services.AddSingleton<UiScaleService>();
        services.AddSingleton<NavigationService>();
        services.AddSingleton<DashboardViewModel>();
        services.AddSingleton<SdkManagementViewModel>();
        services.AddTransient<ChipManagementViewModel>();
        services.AddTransient<PeripheralManagementViewModel>();
        services.AddTransient<LlFunctionLibraryViewModel>();
        services.AddTransient<FunctionCallGraphViewModel>();
        services.AddTransient<RegisterManagementViewModel>();
        services.AddTransient<VirtualMcuViewModel>();
        services.AddSingleton<AutomationTestViewModel>();
        services.AddTransient<TestManagementViewModel>();
        services.AddSingleton<SettingsViewModel>();
        services.AddSingleton<MainViewModel>();
        services.AddSingleton<MainWindow>();

        _services = services.BuildServiceProvider();

        try
        {
            var dbFactory = _services.GetRequiredService<IDbContextFactory<AppDbContext>>();
            await using (var db = await dbFactory.CreateDbContextAsync())
            {
                await db.Database.MigrateAsync();
                // Idempotent indexes for list/filter hot paths (avoid waiting on a new migration for existing installs).
                await db.Database.ExecuteSqlRawAsync(
                    """
                    CREATE INDEX IF NOT EXISTS "IX_LlTestRuns_SdkProjectId_StartedAtUtc"
                    ON "LlTestRuns" ("SdkProjectId", "StartedAtUtc");
                    CREATE INDEX IF NOT EXISTS "IX_LlTestRuns_SdkProjectId_Status"
                    ON "LlTestRuns" ("SdkProjectId", "Status");
                    """);
            }
        }
        catch (Exception ex)
        {
            Log.Error(ex, "Database initialization failed");
            MessageDialog.Show("TAE32 LL Virtual Test", $"数据库初始化失败：{ex.Message}");
            Shutdown(-1);
            return;
        }

        var window = _services.GetRequiredService<MainWindow>();
        window.Show();
    }

    protected override void OnExit(ExitEventArgs e)
    {
        _services?.Dispose();
        _singleInstance?.Dispose();
        _singleInstance = null;
        Log.CloseAndFlush();
        base.OnExit(e);
    }

    private static void ActivateMainWindow()
    {
        if (Current.MainWindow is not { } window) return;

        if (!window.IsVisible)
            window.Show();

        if (window.WindowState == WindowState.Minimized)
            window.WindowState = WindowState.Normal;

        window.Activate();
        // Briefly toggle Topmost to steal focus from the second-instance MessageBox / shell.
        window.Topmost = true;
        window.Topmost = false;
        window.Focus();
    }

}
