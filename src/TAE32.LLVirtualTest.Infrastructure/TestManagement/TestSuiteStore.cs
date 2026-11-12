using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestManagement;

public sealed class TestSuiteStore : ITestSuiteStore
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    public TestSuiteStore(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task<IReadOnlyList<TestSuite>> ListAsync(Guid sdkProjectId, Guid? planId = null, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var q = db.TestSuites.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId);
        if (planId is Guid pid) q = q.Where(x => x.TestPlanId == pid);
        return await q.OrderBy(x => x.Name).ToListAsync(ct);
    }

    public async Task<TestSuite?> GetAsync(Guid id, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        return await db.TestSuites.AsNoTracking()
            .Include(x => x.Cases)
            .FirstOrDefaultAsync(x => x.Id == id, ct);
    }

    public async Task<TestSuite> UpsertAsync(TestSuiteEditModel model, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);

        // Only attach real existing cases.
        var validCaseIds = await db.LlTestCases.AsNoTracking()
            .Where(c => c.SdkProjectId == model.SdkProjectId && model.TestCaseIds.Contains(c.Id))
            .Select(c => c.Id)
            .ToListAsync(ct);

        TestSuite entity;
        if (model.Id is Guid id)
        {
            entity = await db.TestSuites.Include(x => x.Cases).FirstOrDefaultAsync(x => x.Id == id, ct)
                     ?? throw new KeyNotFoundException("测试套件不存在");
            db.TestSuiteCases.RemoveRange(entity.Cases);
            entity.Cases.Clear();
        }
        else
        {
            entity = new TestSuite { Id = Guid.NewGuid() };
            db.TestSuites.Add(entity);
        }

        entity.SdkProjectId = model.SdkProjectId;
        entity.TestPlanId = model.TestPlanId;
        entity.Name = model.Name.Trim();
        entity.Description = model.Description;
        entity.PeripheralName = model.PeripheralName;
        entity.Status = string.IsNullOrWhiteSpace(model.Status) ? "Active" : model.Status;
        entity.UpdatedAtUtc = DateTime.UtcNow;

        var order = 0;
        foreach (var caseId in model.TestCaseIds.Where(validCaseIds.Contains))
        {
            entity.Cases.Add(new TestSuiteCase
            {
                Id = Guid.NewGuid(),
                TestSuiteId = entity.Id,
                LlTestCaseId = caseId,
                SortOrder = order++
            });
        }

        await db.SaveChangesAsync(ct);
        return entity;
    }

    public async Task DeleteAsync(Guid id, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        await db.TestSuites.Where(x => x.Id == id).ExecuteDeleteAsync(ct);
    }

    public async Task<IReadOnlyList<Guid>> GetCaseIdsAsync(Guid suiteId, CancellationToken ct = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        return await db.TestSuiteCases.AsNoTracking()
            .Where(x => x.TestSuiteId == suiteId)
            .OrderBy(x => x.SortOrder)
            .Select(x => x.LlTestCaseId)
            .ToListAsync(ct);
    }
}
