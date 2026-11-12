using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.Services;

public sealed class AppDataService : IAppDataService
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;

    public AppDataService(IDbContextFactory<AppDbContext> dbFactory) => _dbFactory = dbFactory;

    public async Task EnsureDatabaseCreatedAsync(CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        await db.Database.MigrateAsync(cancellationToken);
    }

    public async Task<DashboardStats> GetDashboardStatsAsync(CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var projects = await db.SdkProjects.AsNoTracking().Where(x => x.IsActive).ToListAsync(cancellationToken);
        var chipCount = await db.Chips.AsNoTracking().CountAsync(cancellationToken);
        var periCount = await db.Peripherals.AsNoTracking().CountAsync(cancellationToken);
        var funcCount = await db.LlFunctions.AsNoTracking().CountAsync(cancellationToken);
        var inlineCount = await db.LlFunctions.AsNoTracking()
            .CountAsync(x => x.Form == "inline_definition", cancellationToken);
        var lastImport = projects.Where(x => x.LastImportedAtUtc != null)
            .Select(x => x.LastImportedAtUtc)
            .DefaultIfEmpty()
            .Max();
        var status = projects.Count == 0
            ? "尚未添加 SDK 项目"
            : projects.Any(x => x.LastImportedAtUtc != null)
                ? "已导入扫描结果"
                : "已添加项目，尚未导入";

        return new DashboardStats
        {
            SdkProjectCount = projects.Count,
            ChipCount = chipCount,
            PeripheralCount = periCount,
            LlFunctionCount = funcCount,
            InlineFunctionCount = inlineCount,
            ScanStatusText = status,
            LastImportedAtUtc = lastImport
        };
    }

    public async Task<IReadOnlyList<Chip>> GetChipsAsync(Guid? sdkProjectId = null, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.Chips.AsNoTracking().AsQueryable();
        if (sdkProjectId is Guid id) q = q.Where(x => x.SdkProjectId == id);
        return await q.OrderBy(x => x.ModelName).ToListAsync(cancellationToken);
    }

    public async Task<IReadOnlyList<Peripheral>> GetPeripheralsAsync(Guid? sdkProjectId = null, string? search = null, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.Peripherals.AsNoTracking().Include(x => x.Chip).AsQueryable();
        if (sdkProjectId is Guid id) q = q.Where(x => x.SdkProjectId == id);
        if (!string.IsNullOrWhiteSpace(search))
        {
            var s = search.Trim();
            q = q.Where(x => x.Name.Contains(s) || (x.Chip != null && x.Chip.ModelName.Contains(s)));
        }
        return await q.OrderBy(x => x.SerialNumber).ThenBy(x => x.Name).ToListAsync(cancellationToken);
    }

    public async Task<IReadOnlyList<LlFunction>> GetFunctionsAsync(
        Guid? sdkProjectId = null,
        string? search = null,
        string? peripheralName = null,
        string? chipName = null,
        string? form = null,
        int skip = 0,
        int take = 200,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = FilterFunctions(db, sdkProjectId, search, peripheralName, chipName, form);
        // Peripheral first so "全部" pages are not dominated by alphabetically-early names (e.g. LL_ADC_*).
        return await q.OrderBy(x => x.PeripheralName).ThenBy(x => x.FunctionName).ThenBy(x => x.StartLine)
            .Skip(skip).Take(take)
            .ToListAsync(cancellationToken);
    }

    public async Task<int> CountFunctionsAsync(
        Guid? sdkProjectId = null,
        string? search = null,
        string? peripheralName = null,
        string? chipName = null,
        string? form = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await FilterFunctions(db, sdkProjectId, search, peripheralName, chipName, form).CountAsync(cancellationToken);
    }

    public async Task<LlFunction?> GetFunctionByIdAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await db.LlFunctions.AsNoTracking().FirstOrDefaultAsync(x => x.Id == id, cancellationToken);
    }

    public async Task<LlFunctionDetailDto?> GetFunctionDetailAsync(Guid id, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var fn = await db.LlFunctions.AsNoTracking().FirstOrDefaultAsync(x => x.Id == id, cancellationToken);
        if (fn is null) return null;

        var parameters = await db.LlFunctionParameters.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.Position).ToListAsync(cancellationToken);
        var operations = await db.LlFunctionOperations.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.Sequence).ToListAsync(cancellationToken);
        var calls = await db.LlFunctionCalls.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.CalleeName).ToListAsync(cancellationToken);
        var registers = await db.LlRegisterAccesses.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.StartLine).ToListAsync(cancellationToken);
        var macroRefs = await db.LlRegisterReferences.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.ReferenceLine).ToListAsync(cancellationToken);
        var diagnostics = await db.LlParseDiagnostics.AsNoTracking()
            .Where(x => x.LlFunctionId == id).OrderBy(x => x.Line).ToListAsync(cancellationToken);

        return new LlFunctionDetailDto
        {
            Function = fn,
            Parameters = parameters,
            Operations = operations,
            Calls = calls,
            RegisterAccesses = registers,
            RegisterReferences = macroRefs,
            Diagnostics = diagnostics
        };
    }

    public async Task<IReadOnlyList<PeripheralInstance>> GetPeripheralInstancesAsync(
        Guid? sdkProjectId = null,
        Guid? peripheralId = null,
        string? search = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.PeripheralInstances.AsNoTracking().AsQueryable();
        if (sdkProjectId is Guid pid) q = q.Where(x => x.SdkProjectId == pid);
        if (peripheralId is Guid periId) q = q.Where(x => x.PeripheralId == periId);
        if (!string.IsNullOrWhiteSpace(search))
        {
            var s = search.Trim();
            q = q.Where(x => x.Name.Contains(s) || (x.ModuleName != null && x.ModuleName.Contains(s)));
        }
        return await q.OrderBy(x => x.ModuleName).ThenBy(x => x.Name).ToListAsync(cancellationToken);
    }

    public async Task<IReadOnlyList<RegisterCatalogDto>> GetRegistersAsync(
        Guid? sdkProjectId = null,
        Guid? chipId = null,
        Guid? peripheralId = null,
        Guid? instanceId = null,
        string? search = null,
        bool hideReserved = true,
        int skip = 0,
        int take = 200,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var rows = await FilterRegisters(db, sdkProjectId, chipId, peripheralId, instanceId, search, hideReserved)
            .OrderBy(x => x.StructName).ThenBy(x => x.OffsetBytes ?? int.MaxValue).ThenBy(x => x.MemberName)
            .Skip(skip).Take(take)
            .ToListAsync(cancellationToken);

        return rows.Select(MapRegisterCatalog).ToList();
    }

    public async Task<int> CountRegistersAsync(
        Guid? sdkProjectId = null,
        Guid? chipId = null,
        Guid? peripheralId = null,
        Guid? instanceId = null,
        string? search = null,
        bool hideReserved = true,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        return await FilterRegisters(db, sdkProjectId, chipId, peripheralId, instanceId, search, hideReserved)
            .CountAsync(cancellationToken);
    }

    private static RegisterCatalogDto MapRegisterCatalog(RegisterDefinition r) => new()
    {
        Register = r,
        InstanceName = r.PeripheralInstance?.Name
                       ?? (r.StructName.EndsWith("_Type", StringComparison.Ordinal)
                           ? r.StructName[..^5]
                           : null),
        ModuleName = r.Peripheral?.Name
                     ?? r.PeripheralInstance?.ModuleName
                     ?? InferModuleFromStruct(r.StructName),
        ChipName = r.Chip?.ModelName
    };

    private static string? InferModuleFromStruct(string structName)
    {
        if (structName.EndsWith("_TypeDef", StringComparison.Ordinal))
            return structName[..^8];
        if (structName.EndsWith("_Type", StringComparison.Ordinal))
        {
            var inst = structName[..^5]; // GPIOA / ADC0 / TMR0
            var m = System.Text.RegularExpressions.Regex.Match(inst, @"^([A-Z]+?)(\d+|[A-F])?$");
            return m.Success ? m.Groups[1].Value : inst;
        }
        return null;
    }

    public async Task<RegisterDetailDto?> GetRegisterDetailAsync(Guid registerId, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var reg = await db.RegisterDefinitions.AsNoTracking()
            .Include(x => x.PeripheralInstance)
            .FirstOrDefaultAsync(x => x.Id == registerId, cancellationToken);
        if (reg is null) return null;

        var fields = await db.RegisterFields.AsNoTracking()
            .Where(x => x.RegisterDefinitionId == registerId).OrderBy(x => x.Name).ToListAsync(cancellationToken);
        var macros = await db.RegisterMacroReferences.AsNoTracking()
            .Where(x => x.RegisterDefinitionId == registerId).OrderBy(x => x.MacroName).ToListAsync(cancellationToken);
        var enums = await db.RegisterEnumValues.AsNoTracking()
            .Where(x => x.RegisterDefinitionId == registerId).ToListAsync(cancellationToken);
        var diag = await db.RegisterParseDiagnostics.AsNoTracking()
            .Where(x => x.SdkProjectId == reg.SdkProjectId)
            .OrderByDescending(x => x.Severity)
            .Take(50)
            .ToListAsync(cancellationToken);

        return new RegisterDetailDto
        {
            Register = reg,
            Instance = reg.PeripheralInstance,
            Fields = fields,
            Macros = macros,
            EnumValues = enums,
            Diagnostics = diag
        };
    }

    public async Task<IReadOnlyList<RegisterParseDiagnostic>> GetRegisterParseDiagnosticsAsync(
        Guid? sdkProjectId = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var q = db.RegisterParseDiagnostics.AsNoTracking().AsQueryable();
        if (sdkProjectId is Guid id) q = q.Where(x => x.SdkProjectId == id);
        return await q.OrderBy(x => x.Category).ThenBy(x => x.Severity).ToListAsync(cancellationToken);
    }

    private static IQueryable<RegisterDefinition> FilterRegisters(
        AppDbContext db,
        Guid? sdkProjectId,
        Guid? chipId,
        Guid? peripheralId,
        Guid? instanceId,
        string? search,
        bool hideReserved)
    {
        var q = db.RegisterDefinitions.AsNoTracking()
            .Include(x => x.Chip)
            .Include(x => x.Peripheral)
            .Include(x => x.PeripheralInstance)
            .AsQueryable();
        if (sdkProjectId is Guid pid) q = q.Where(x => x.SdkProjectId == pid);
        if (chipId is Guid cid) q = q.Where(x => x.ChipId == null || x.ChipId == cid);

        if (peripheralId is Guid periId)
        {
            var periName = db.Peripherals.AsNoTracking()
                .Where(p => p.Id == periId).Select(p => p.Name).FirstOrDefault();
            q = q.Where(x =>
                x.PeripheralId == periId
                || (x.PeripheralInstance != null && x.PeripheralInstance.PeripheralId == periId)
                || (periName != null && x.PeripheralInstance != null && x.PeripheralInstance.ModuleName == periName)
                || (periName != null && x.StructName == periName + "_TypeDef")
                || (periName != null && x.StructName.StartsWith(periName)
                    && (x.StructName.EndsWith("_Type") || x.StructName.EndsWith("_TypeDef"))));
        }

        if (instanceId is Guid iid)
        {
            var instName = db.PeripheralInstances.AsNoTracking()
                .Where(i => i.Id == iid).Select(i => i.Name).FirstOrDefault();
            var moduleName = db.PeripheralInstances.AsNoTracking()
                .Where(i => i.Id == iid).Select(i => i.ModuleName).FirstOrDefault();
            q = q.Where(x =>
                x.PeripheralInstanceId == iid
                || (instName != null && x.StructName == instName + "_Type")
                || (moduleName != null && instName != null
                    && x.StructName == moduleName + "_TypeDef"
                    && (x.PeripheralInstanceId == null || x.PeripheralInstanceId == iid)));
        }

        if (hideReserved)
        {
            q = q.Where(x =>
                !x.MemberName.StartsWith("RESERVED")
                && (x.AccessAttribute == null || x.AccessAttribute != "Reserved"));
        }

        if (!string.IsNullOrWhiteSpace(search))
        {
            var s = search.Trim();
            q = q.Where(x =>
                x.MemberName.Contains(s)
                || x.StructName.Contains(s)
                || (x.PeripheralInstance != null && x.PeripheralInstance.Name.Contains(s)));
        }
        return q;
    }

    private static IQueryable<LlFunction> FilterFunctions(AppDbContext db, Guid? sdkProjectId, string? search, string? peripheralName, string? chipName, string? form)
    {
        var q = db.LlFunctions.AsNoTracking().AsQueryable();
        if (sdkProjectId is Guid id) q = q.Where(x => x.SdkProjectId == id);
        if (!string.IsNullOrWhiteSpace(peripheralName))
            q = q.Where(x => x.PeripheralName == peripheralName);
        if (!string.IsNullOrWhiteSpace(chipName))
            q = q.Where(x => x.ChipName == chipName);
        if (!string.IsNullOrWhiteSpace(form))
            q = q.Where(x => x.Form == form);
        if (!string.IsNullOrWhiteSpace(search))
        {
            var s = search.Trim();
            q = q.Where(x => x.FunctionName.Contains(s) || x.FilePath.Contains(s));
        }
        return q;
    }
}
