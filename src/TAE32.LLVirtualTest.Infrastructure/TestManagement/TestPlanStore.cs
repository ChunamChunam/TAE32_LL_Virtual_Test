using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class TestPlanStore : ITestPlanStore
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    public TestPlanStore(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task<IReadOnlyList<TestPlan>> ListAsync(Guid sdkProjectId, bool includeArchived = false, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = db.TestPlans.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId);
        if (!includeArchived) q = q.Where(x => x.Status != "Archived");
        return await q.OrderByDescending(x => x.UpdatedAtUtc ?? x.CreatedAtUtc).ToListAsync(ct);
    }

    public async Task<TestPlan?> GetAsync(Guid id, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        return await db.TestPlans.AsNoTracking().FirstOrDefaultAsync(x => x.Id == id, ct);
    }

    public async Task<TestPlan> UpsertAsync(TestPlanEditModel model, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        TestPlan entity;
        if (model.Id is Guid id)
        {
            entity = await db.TestPlans.FirstOrDefaultAsync(x => x.Id == id, ct)
                     ?? throw new KeyNotFoundException("测试计划不存在");
        }
        else
        {
            entity = new TestPlan { Id = Guid.NewGuid() };
            db.TestPlans.Add(entity);
        }

        entity.SdkProjectId = model.SdkProjectId;
        entity.ChipId = model.ChipId;
        entity.Name = model.Name.Trim();
        entity.Description = model.Description;
        entity.SdkVersion = model.SdkVersion;
        entity.ChipModelName = model.ChipModelName;
        entity.PeripheralFilter = model.PeripheralFilter;
        entity.FunctionFilter = model.FunctionFilter;
        entity.TestType = model.TestType;
        entity.Status = string.IsNullOrWhiteSpace(model.Status) ? "Active" : model.Status;
        entity.UpdatedAtUtc = DateTime.UtcNow;
        await db.SaveChangesAsync(ct);
        return entity;
    }

    public async Task<TestPlan> DuplicateAsync(Guid id, CancellationToken ct = default)
    {
        var src = await GetAsync(id, ct) ?? throw new KeyNotFoundException("测试计划不存在");
        return await UpsertAsync(new TestPlanEditModel
        {
            SdkProjectId = src.SdkProjectId,
            ChipId = src.ChipId,
            Name = src.Name + " (副本)",
            Description = src.Description,
            SdkVersion = src.SdkVersion,
            ChipModelName = src.ChipModelName,
            PeripheralFilter = src.PeripheralFilter,
            FunctionFilter = src.FunctionFilter,
            TestType = src.TestType,
            Status = "Active"
        }, ct);
    }

    public async Task ArchiveAsync(Guid id, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var entity = await db.TestPlans.FirstOrDefaultAsync(x => x.Id == id, ct)
                     ?? throw new KeyNotFoundException("测试计划不存在");
        entity.Status = "Archived";
        entity.ArchivedAtUtc = DateTime.UtcNow;
        entity.UpdatedAtUtc = DateTime.UtcNow;
        await db.SaveChangesAsync(ct);
    }

    public async Task DeleteAsync(Guid id, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        await db.TestPlans.Where(x => x.Id == id).ExecuteDeleteAsync(ct);
    }
}
