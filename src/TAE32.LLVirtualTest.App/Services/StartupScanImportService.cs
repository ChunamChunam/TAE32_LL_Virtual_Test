using System.IO;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.App.Services;

/// <summary>
/// On startup: if DB has no function data and default SDK exists,
/// automatically scan SDK → write JSON → import.
/// </summary>
public sealed class StartupScanImportService
{
    private readonly ISdkProjectService _projects;
    private readonly IScanImportService _import;
    private readonly ISdkScanService _scan;
    private readonly IAppDataService _data;
    private readonly ILogger<StartupScanImportService> _logger;

    public StartupScanImportService(
        ISdkProjectService projects,
        IScanImportService import,
        ISdkScanService scan,
        IAppDataService data,
        ILogger<StartupScanImportService> logger)
    {
        _projects = projects;
        _import = import;
        _scan = scan;
        _data = data;
        _logger = logger;
    }

    public async Task<string> EnsureProjectAndImportAsync(CancellationToken cancellationToken = default)
    {
        var stats = await _data.GetDashboardStatsAsync(cancellationToken);
        if (stats.LlFunctionCount > 0)
            return $"已有导入数据（函数 {stats.LlFunctionCount}），跳过启动自动扫描。可在 SDK 管理中重新「扫描并生成 JSON」。";

        if (!Directory.Exists(AppPaths.DefaultSdkRoot))
            return "默认 SDK 路径不存在。请在 SDK 管理中浏览选择 SDK 并点击「扫描并生成 JSON」。";

        var outDir = Directory.Exists(AppPaths.DefaultScanResults)
            ? AppPaths.DefaultScanResults
            : Path.Combine(AppPaths.DataDirectory, "scan", "default");

        _logger.LogInformation("Startup: scanning default SDK {Sdk} → {Out}", AppPaths.DefaultSdkRoot, outDir);
        var scan = await _scan.ScanAsync(AppPaths.DefaultSdkRoot, outDir, cancellationToken);
        if (!scan.Success)
            return $"启动自动扫描失败：{scan.Message}";

        var projects = (await _projects.GetAllAsync(cancellationToken)).ToList();
        Core.Entities.SdkProject project;
        if (projects.Count == 0)
        {
            project = await _projects.AddAsync("TAE32G58xx DFP LL", scan.SdkRootPath, scan.OutputDirectory, cancellationToken);
        }
        else
        {
            project = projects[0];
            await _projects.UpdatePathsAsync(project.Id, scan.SdkRootPath, scan.OutputDirectory, cancellationToken);
        }

        ImportResult import;
        try
        {
            import = await _import.ImportAsync(project.Id, cancellationToken);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Startup import failed");
            return $"扫描成功，但导入失败：{ex.Message}";
        }

        return import.Success
            ? $"启动自动扫描+导入完成：芯片 {import.ChipCount}，外设 {import.PeripheralCount}，函数 {import.FunctionCount}。JSON：{scan.OutputDirectory}"
            : $"扫描成功，导入失败：{import.Message}";
    }

    public static bool HasRequiredScanFiles(string scanResultsPath)
    {
        if (string.IsNullOrWhiteSpace(scanResultsPath) || !Directory.Exists(scanResultsPath))
            return false;
        return File.Exists(Path.Combine(scanResultsPath, "03_ChipDiscovery.json"))
            && File.Exists(Path.Combine(scanResultsPath, "04_PeripheralDiscovery.json"))
            && File.Exists(Path.Combine(scanResultsPath, "05_LLFunctionDiscovery.json"));
    }
}
