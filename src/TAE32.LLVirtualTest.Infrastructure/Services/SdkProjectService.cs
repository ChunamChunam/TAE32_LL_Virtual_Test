using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.Services;

public sealed class SdkProjectService : ISdkProjectService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ILogger<SdkProjectService> _logger;

    public SdkProjectService(IDbContextFactory<AppDbContext> dbFactory, ILogger<SdkProjectService> logger)
    {
        _dbFactory = dbFactory;
        _logger = logger;
    }

    public async Task<IReadOnlyList<SdkProject>> GetAllAsync(CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.SdkProjects
            .AsNoTracking()
            .Where(x => x.IsActive)
            .OrderBy(x => x.Name)
            .ToListAsync(cancellationToken);
    }

    public async Task<SdkProject?> GetByIdAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.SdkProjects.AsNoTracking().FirstOrDefaultAsync(x => x.Id == id, cancellationToken);
    }

    public async Task<SdkProject> AddAsync(string name, string sdkRootPath, string scanResultsPath, CancellationToken cancellationToken = default)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new ArgumentException("项目名称不能为空。", nameof(name));
        if (string.IsNullOrWhiteSpace(sdkRootPath) || !Directory.Exists(sdkRootPath))
            throw new DirectoryNotFoundException($"SDK 路径不存在: {sdkRootPath}");
        if (string.IsNullOrWhiteSpace(scanResultsPath) || !Directory.Exists(scanResultsPath))
            throw new DirectoryNotFoundException($"扫描结果目录不存在: {scanResultsPath}");

        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var entity = new SdkProject
        {
            Name = name.Trim(),
            SdkRootPath = Path.GetFullPath(sdkRootPath),
            ScanResultsPath = Path.GetFullPath(scanResultsPath),
            ScanStatus = ScanStatus.NotScanned,
            CreatedAtUtc = DateTime.UtcNow,
            IsActive = true
        };

        db.SdkProjects.Add(entity);
        await db.SaveChangesAsync(cancellationToken);
        _logger.LogInformation("Added SDK project {Name} ({Id}). Original SDK files are never deleted by this app.", entity.Name, entity.Id);
        return entity;
    }

    public async Task RemoveAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var entity = await db.SdkProjects.FirstOrDefaultAsync(x => x.Id == id, cancellationToken)
            ?? throw new InvalidOperationException("SDK 项目不存在。");

        _logger.LogWarning(
            "Removing SDK project metadata {Name} ({Id}). SdkRootPath kept on disk: {Path}",
            entity.Name, entity.Id, entity.SdkRootPath);

        db.SdkProjects.Remove(entity);
        await db.SaveChangesAsync(cancellationToken);
    }

    public async Task UpdatePathsAsync(Guid id, string sdkRootPath, string scanResultsPath, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var entity = await db.SdkProjects.FirstOrDefaultAsync(x => x.Id == id, cancellationToken)
            ?? throw new InvalidOperationException("SDK 项目不存在。");

        if (!Directory.Exists(sdkRootPath))
            throw new DirectoryNotFoundException($"SDK 路径不存在: {sdkRootPath}");
        if (!Directory.Exists(scanResultsPath))
            throw new DirectoryNotFoundException($"扫描结果目录不存在: {scanResultsPath}");

        entity.SdkRootPath = Path.GetFullPath(sdkRootPath);
        entity.ScanResultsPath = Path.GetFullPath(scanResultsPath);
        entity.UpdatedAtUtc = DateTime.UtcNow;
        await db.SaveChangesAsync(cancellationToken);
    }
}
