using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.Services;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;
using TAE32.LLVirtualTest.Infrastructure.TestManagement;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Infrastructure;

public static class DependencyInjection
{
    public static IServiceCollection AddInfrastructure(
        this IServiceCollection services,
        string sqliteDbPath,
        string? logDirectory = null)
    {
        var dir = Path.GetDirectoryName(sqliteDbPath);
        if (!string.IsNullOrWhiteSpace(dir))
            Directory.CreateDirectory(dir);

        services.AddDbContextFactory<AppDbContext>(options =>
            options.UseSqlite($"Data Source={sqliteDbPath};Cache=Shared")
                .AddInterceptors(new SqlitePragmaInterceptor()));

        services.AddScoped(sp => sp.GetRequiredService<IDbContextFactory<AppDbContext>>().CreateDbContext());

        services.AddSingleton<ISdkProjectService, SdkProjectService>();
        services.AddSingleton<IAppDataService, AppDataService>();

        services.AddSingleton<IVirtualMcuService, VirtualMcuService>();
        services.AddSingleton<ICompilerService, ClangCompilerService>();
        services.AddSingleton<ILlTestCaseStore, LlTestCaseStore>();
        services.AddSingleton<LlTestCaseGenerator>();
        services.AddSingleton<LlShiftStaticAnalyzer>();
        services.AddSingleton<ILLTestEngine, LlTestEngine>();

        services.AddSingleton<ITestPlanStore, TestPlanStore>();
        services.AddSingleton<ITestSuiteStore, TestSuiteStore>();
        services.AddSingleton<ITestBatchService, TestBatchService>();
        services.AddSingleton<ITestAnalyticsService, TestAnalyticsService>();
        services.AddSingleton<ITestReportService, TestReportService>();
        services.AddSingleton<ISystemMaintenanceService>(sp =>
            new SystemMaintenanceService(
                sp.GetRequiredService<IDbContextFactory<AppDbContext>>(),
                sqliteDbPath,
                logDirectory ?? Path.Combine(Path.GetTempPath(), "tae32_ll_logs")));

        return services;
    }
}
