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

    protected override async void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);

        DispatcherUnhandledException += (_, args) =>
        {
            Log.Error(args.Exception, "Dispatcher unhandled exception");
            MessageDialog.Show("TAE32 LL Virtual Test", args.Exception.Message);
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

        Directory.CreateDirectory(AppPaths.DataDirectory);
        Directory.CreateDirectory(AppPaths.LogDirectory);
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
        services.AddSingleton<StartupScanImportService>();
        services.AddSingleton<MainViewModel>();
        services.AddSingleton<MainWindow>();

        _services = services.BuildServiceProvider();

        string? autoImportSummary = null;
        try
        {
            var dbFactory = _services.GetRequiredService<IDbContextFactory<AppDbContext>>();
            await using (var db = await dbFactory.CreateDbContextAsync())
            {
                await db.Database.MigrateAsync();
            }

            // Auto-create default project (if needed) and import ScanResults JSON into SQLite.
            var startupImport = _services.GetRequiredService<StartupScanImportService>();
            autoImportSummary = await startupImport.EnsureProjectAndImportAsync();
            Log.Information("Startup auto-import: {Summary}", autoImportSummary);
        }
        catch (Exception ex)
        {
            Log.Error(ex, "Database initialization / auto-import failed");
            MessageDialog.Show("TAE32 LL Virtual Test", $"数据库初始化或自动导入失败：{ex.Message}");
            Shutdown(-1);
            return;
        }

        var window = _services.GetRequiredService<MainWindow>();
        if (!string.IsNullOrWhiteSpace(autoImportSummary))
            window.Tag = autoImportSummary;
        window.Show();
    }

    protected override void OnExit(ExitEventArgs e)
    {
        _services?.Dispose();
        Log.CloseAndFlush();
        base.OnExit(e);
    }
}
