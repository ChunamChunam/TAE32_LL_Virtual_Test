using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

public sealed class LlTestCaseStore : ILlTestCaseStore
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;

    public LlTestCaseStore(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task<IReadOnlyList<LlTestCase>> ListAsync(
        Guid? sdkProjectId = null, string? peripheralName = null, string? functionName = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.LlTestCases.AsNoTracking().AsQueryable();
        if (sdkProjectId is Guid pid) q = q.Where(x => x.SdkProjectId == pid);
        if (!string.IsNullOrWhiteSpace(peripheralName)) q = q.Where(x => x.PeripheralName == peripheralName);
        if (!string.IsNullOrWhiteSpace(functionName))
            q = q.Where(x => x.FunctionName.Contains(functionName));
        return await q.OrderBy(x => x.PeripheralName).ThenBy(x => x.FunctionName).ThenBy(x => x.Name)
            .ToListAsync(cancellationToken);
    }

    public async Task<(IReadOnlyList<LlTestCase> Items, int TotalCount)> ListPagedAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        int skip = 0,
        int take = 100,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = ApplyCaseFilters(db.LlTestCases.AsNoTracking(), sdkProjectId, peripheralName, searchText);
        var total = await q.CountAsync(cancellationToken);
        take = Math.Max(1, take);
        skip = Math.Max(0, skip);
        var items = await q.OrderBy(x => x.PeripheralName).ThenBy(x => x.FunctionName).ThenBy(x => x.Name)
            .Skip(skip).Take(take).ToListAsync(cancellationToken);
        return (items, total);
    }

    public async Task<IReadOnlyList<LlTestCase>> ListFilteredAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = ApplyCaseFilters(db.LlTestCases.AsNoTracking(), sdkProjectId, peripheralName, searchText);
        return await q.OrderBy(x => x.PeripheralName).ThenBy(x => x.FunctionName).ThenBy(x => x.Name)
            .ToListAsync(cancellationToken);
    }

    private static IQueryable<LlTestCase> ApplyCaseFilters(
        IQueryable<LlTestCase> q,
        Guid sdkProjectId,
        string? peripheralName,
        string? searchText)
    {
        q = q.Where(x => x.SdkProjectId == sdkProjectId);
        if (!string.IsNullOrWhiteSpace(peripheralName))
            q = q.Where(x => x.PeripheralName == peripheralName);
        if (!string.IsNullOrWhiteSpace(searchText))
        {
            var term = searchText.Trim();
            q = q.Where(x =>
                x.Name.Contains(term) ||
                x.FunctionName.Contains(term) ||
                (x.PeripheralName != null && x.PeripheralName.Contains(term)) ||
                x.Status.Contains(term));
        }

        return q;
    }

    public async Task<LlTestCase?> GetAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.LlTestCases.AsNoTracking().FirstOrDefaultAsync(x => x.Id == id, cancellationToken);
    }

    public async Task<LlTestCase> UpsertAsync(LlTestCaseEditModel model, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        LlTestCase entity;
        if (model.Id is Guid id)
        {
            entity = await db.LlTestCases.FirstOrDefaultAsync(x => x.Id == id, cancellationToken)
                     ?? throw new KeyNotFoundException("测试用例不存在");
        }
        else
        {
            entity = new LlTestCase { Id = Guid.NewGuid() };
            db.LlTestCases.Add(entity);
        }

        ApplyEditModel(entity, model);
        await db.SaveChangesAsync(cancellationToken);
        return entity;
    }

    public async Task<int> CountFilteredNotReadyAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = ApplyCaseFilters(db.LlTestCases.AsNoTracking(), sdkProjectId, peripheralName, searchText)
            .Where(x => x.Status == nameof(LlTestCaseStatus.Draft)
                        || x.Status == nameof(LlTestCaseStatus.Unsupported));
        return await q.CountAsync(cancellationToken);
    }

    public async Task<int> MarkFilteredReadyAsync(
        Guid sdkProjectId,
        string? peripheralName = null,
        string? searchText = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = ApplyCaseFilters(db.LlTestCases, sdkProjectId, peripheralName, searchText)
            .Where(x => x.Status == nameof(LlTestCaseStatus.Draft)
                        || x.Status == nameof(LlTestCaseStatus.Unsupported));
        var now = DateTime.UtcNow;
        return await q.ExecuteUpdateAsync(
            s => s.SetProperty(c => c.Status, nameof(LlTestCaseStatus.Ready))
                  .SetProperty(c => c.UpdatedAtUtc, now),
            cancellationToken);
    }

    public async Task<int> InsertManyAsync(IReadOnlyList<LlTestCaseEditModel> models, CancellationToken cancellationToken = default)
    {
        if (models.Count == 0) return 0;
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        foreach (var model in models)
        {
            if (model.Id is Guid)
                throw new InvalidOperationException("InsertManyAsync 仅用于新建用例（Id 应为 null）。");
            var entity = new LlTestCase { Id = Guid.NewGuid() };
            ApplyEditModel(entity, model);
            db.LlTestCases.Add(entity);
        }

        await db.SaveChangesAsync(cancellationToken);
        return models.Count;
    }

    private static void ApplyEditModel(LlTestCase entity, LlTestCaseEditModel model)
    {
        entity.SdkProjectId = model.SdkProjectId;
        entity.ChipId = model.ChipId;
        entity.LlFunctionId = model.LlFunctionId;
        entity.Name = model.Name;
        entity.ChipModelName = model.ChipModelName;
        entity.PeripheralName = model.PeripheralName;
        entity.FunctionName = model.FunctionName;
        entity.FunctionSignature = model.FunctionSignature;
        entity.SourceFile = model.SourceFile;
        entity.Status = model.Status;
        entity.ParametersJson = LlTestJson.SerializeParametersEnvelope(model.Parameters, model.PreludeCalls);
        entity.InitialRegistersJson = LlTestJson.SerializeInitial(model.InitialRegisters);
        entity.AssertionsJson = LlTestJson.SerializeAssertions(model.Assertions);
        entity.Notes = model.Notes;
        entity.IsAutoGenerated = model.IsAutoGenerated;
        entity.UpdatedAtUtc = DateTime.UtcNow;
    }

    public async Task DeleteAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await DeleteManyAsync(new[] { id }, cancellationToken);
    }

    public async Task<int> DeleteManyAsync(IEnumerable<Guid> ids, CancellationToken cancellationToken = default)
    {
        var idList = ids.Distinct().ToList();
        if (idList.Count == 0) return 0;
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        await db.LlTestRuns.Where(x => idList.Contains(x.LlTestCaseId)).ExecuteDeleteAsync(cancellationToken);
        return await db.LlTestCases.Where(x => idList.Contains(x.Id)).ExecuteDeleteAsync(cancellationToken);
    }

    public async Task<LlTestCase> DuplicateAsync(Guid id, CancellationToken cancellationToken = default)
    {
        var src = await GetAsync(id, cancellationToken) ?? throw new KeyNotFoundException("测试用例不存在");
        var model = ToEdit(src);
        model.Id = null;
        model.Name = src.Name + " (副本)";
        model.IsAutoGenerated = false;
        return await UpsertAsync(model, cancellationToken);
    }

    public async Task<string> ExportJsonAsync(IEnumerable<Guid> ids, CancellationToken cancellationToken = default)
    {
        var idList = ids.ToList();
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var rows = await db.LlTestCases.AsNoTracking().Where(x => idList.Contains(x.Id)).ToListAsync(cancellationToken);
        var models = rows.Select(ToEdit).ToList();
        return LlTestJson.Serialize(models);
    }

    public async Task<int> ImportJsonAsync(Guid sdkProjectId, string json, CancellationToken cancellationToken = default)
    {
        var models = LlTestJson.Deserialize<List<LlTestCaseEditModel>>(json) ?? new();
        var n = 0;
        foreach (var m in models)
        {
            m.Id = null;
            m.SdkProjectId = sdkProjectId;
            await UpsertAsync(m, cancellationToken);
            n++;
        }
        return n;
    }

    public async Task<IReadOnlyList<LlTestRun>> ListRunsAsync(
        Guid? sdkProjectId = null,
        Guid? testCaseId = null,
        int take = 200,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.LlTestRuns.AsNoTracking().Include(x => x.TestCase).AsQueryable();
        if (sdkProjectId is Guid pid) q = q.Where(x => x.SdkProjectId == pid);
        if (testCaseId is Guid id) q = q.Where(x => x.LlTestCaseId == id);
        var limit = take <= 0 ? 200 : Math.Min(take, 1000);
        return await q.OrderByDescending(x => x.StartedAtUtc).Take(limit).ToListAsync(cancellationToken);
    }

    public async Task<(IReadOnlyList<LlTestRun> Items, int TotalCount)> ListRunsPagedAsync(
        Guid sdkProjectId,
        string? searchText = null,
        int skip = 0,
        int take = 50,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.LlTestRuns.AsNoTracking().Include(x => x.TestCase)
            .Where(x => x.SdkProjectId == sdkProjectId);
        if (!string.IsNullOrWhiteSpace(searchText))
        {
            var term = searchText.Trim();
            q = q.Where(x =>
                x.Status.Contains(term) ||
                (x.TestCase != null &&
                 (x.TestCase.Name.Contains(term) || x.TestCase.FunctionName.Contains(term))));
        }

        var total = await q.CountAsync(cancellationToken);
        take = Math.Max(1, take);
        skip = Math.Max(0, skip);
        var items = await q.OrderByDescending(x => x.StartedAtUtc).Skip(skip).Take(take).ToListAsync(cancellationToken);
        return (items, total);
    }

    public async Task<int> DeleteRunsAsync(IEnumerable<Guid> runIds, CancellationToken cancellationToken = default)
    {
        var idList = runIds.Distinct().ToList();
        if (idList.Count == 0) return 0;
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.LlTestRuns.Where(x => idList.Contains(x.Id)).ExecuteDeleteAsync(cancellationToken);
    }

    public async Task<LlTestRun?> GetRunAsync(Guid runId, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.LlTestRuns.AsNoTracking().FirstOrDefaultAsync(x => x.Id == runId, cancellationToken);
    }

    public async Task SaveRunAsync(LlTestRun run, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var existing = await db.LlTestRuns.FirstOrDefaultAsync(x => x.Id == run.Id, cancellationToken);
        if (existing is null) db.LlTestRuns.Add(run);
        else db.Entry(existing).CurrentValues.SetValues(run);
        await db.SaveChangesAsync(cancellationToken);
    }

    public static LlTestCaseEditModel ToEdit(LlTestCase c)
    {
        var (parameters, prelude) = LlTestJson.DeserializeParametersEnvelope(c.ParametersJson);
        return new LlTestCaseEditModel
        {
            Id = c.Id,
            SdkProjectId = c.SdkProjectId,
            ChipId = c.ChipId,
            LlFunctionId = c.LlFunctionId,
            Name = c.Name,
            ChipModelName = c.ChipModelName,
            PeripheralName = c.PeripheralName,
            FunctionName = c.FunctionName,
            FunctionSignature = c.FunctionSignature,
            SourceFile = c.SourceFile,
            Status = c.Status,
            Parameters = parameters,
            PreludeCalls = prelude,
            InitialRegisters = LlTestJson.DeserializeInitial(c.InitialRegistersJson),
            Assertions = LlTestJson.DeserializeAssertions(c.AssertionsJson),
            Notes = c.Notes,
            IsAutoGenerated = c.IsAutoGenerated
        };
    }
}
