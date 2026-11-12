using System.Text.Json;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.SDK.Dto;

namespace TAE32.LLVirtualTest.SDK.Import;

public sealed class ScanImportService : IScanImportService
{
    private static readonly JsonSerializerOptions JsonOptions = new()
    {
        PropertyNameCaseInsensitive = true,
        ReadCommentHandling = JsonCommentHandling.Skip,
        AllowTrailingCommas = true
    };

    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ILogger<ScanImportService> _logger;

    public ScanImportService(IDbContextFactory<AppDbContext> dbFactory, ILogger<ScanImportService> logger)
    {
        _dbFactory = dbFactory;
        _logger = logger;
    }

    public async Task<ImportResult> ImportAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);

        var project = await db.SdkProjects.FirstOrDefaultAsync(x => x.Id == sdkProjectId, cancellationToken)
            ?? throw new InvalidOperationException("SDK 项目不存在。");

        var scanDir = project.ScanResultsPath;
        var chipPath = Path.Combine(scanDir, "03_ChipDiscovery.json");
        var periPath = Path.Combine(scanDir, "04_PeripheralDiscovery.json");
        var funcPath = Path.Combine(scanDir, "05_LLFunctionDiscovery.json");

        var errors = new List<string>();
        ValidateRequiredFile(chipPath, errors);
        ValidateRequiredFile(periPath, errors);
        ValidateRequiredFile(funcPath, errors);
        if (errors.Count > 0)
            return Fail(errors, "扫描结果文件缺失或不可读。");

        ChipDiscoveryDocument chipDoc;
        PeripheralDiscoveryDocument periDoc;
        FunctionDiscoveryDocument funcDoc;
        try
        {
            chipDoc = await ReadJsonAsync<ChipDiscoveryDocument>(chipPath, cancellationToken);
            periDoc = await ReadJsonAsync<PeripheralDiscoveryDocument>(periPath, cancellationToken);
            funcDoc = await ReadJsonAsync<FunctionDiscoveryDocument>(funcPath, cancellationToken);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Failed to deserialize scan JSON under {Dir}", scanDir);
            return Fail(new[] { ex.Message }, "JSON 解析失败。");
        }

        var record = new ScanRecord
        {
            SdkProjectId = project.Id,
            StartedAtUtc = DateTime.UtcNow,
            SourceDirectory = scanDir,
            Status = ScanStatus.Imported
        };
        db.ScanRecords.Add(record);

        int inserted = 0, updated = 0, skipped = 0;

        var chipMap = new Dictionary<string, Chip>(StringComparer.OrdinalIgnoreCase);
        var existingChips = await db.Chips.Where(x => x.SdkProjectId == project.Id).ToListAsync(cancellationToken);
        foreach (var c in chipDoc.Chips)
        {
            if (string.IsNullOrWhiteSpace(c.ChipModel))
            {
                skipped++;
                errors.Add("跳过空芯片型号条目。");
                continue;
            }

            var naturalKey = Normalize(c.ChipModel);
            var entity = existingChips.FirstOrDefault(x => x.NaturalKey == naturalKey);
            if (entity is null)
            {
                entity = new Chip
                {
                    SdkProjectId = project.Id,
                    ModelName = c.ChipModel.Trim(),
                    NaturalKey = naturalKey,
                    CreatedAtUtc = DateTime.UtcNow
                };
                db.Chips.Add(entity);
                inserted++;
            }
            else
            {
                updated++;
                entity.UpdatedAtUtc = DateTime.UtcNow;
            }

            entity.ModelName = c.ChipModel.Trim();
            entity.DetectionStatus = c.DetectionStatus;
            entity.Confidence = c.Confidence;
            entity.Notes = c.Notes;
            entity.Level = "series";
            chipMap[entity.ModelName] = entity;

            foreach (var rel in c.RelatedFiles.Distinct(StringComparer.OrdinalIgnoreCase))
                UpsertFile(db, project.Id, rel, null, "chip_related", ref inserted, ref updated);
        }

        await db.SaveChangesAsync(cancellationToken);

        var periMap = new Dictionary<string, Peripheral>(StringComparer.OrdinalIgnoreCase);
        var existingPeris = await db.Peripherals.Where(x => x.SdkProjectId == project.Id).ToListAsync(cancellationToken);
        foreach (var p in periDoc.Peripherals)
        {
            if (string.IsNullOrWhiteSpace(p.Name))
            {
                skipped++;
                errors.Add("跳过空外设名称条目。");
                continue;
            }

            var chipName = string.IsNullOrWhiteSpace(p.ChipName) ? chipMap.Keys.FirstOrDefault() : p.ChipName.Trim();
            Chip? chip = null;
            if (!string.IsNullOrWhiteSpace(chipName) && chipMap.TryGetValue(chipName, out var mapped))
                chip = mapped;

            var naturalKey = $"{chip?.ModelName ?? "_"}|{Normalize(p.Name)}";
            var entity = existingPeris.FirstOrDefault(x => x.NaturalKey == naturalKey);
            if (entity is null)
            {
                entity = new Peripheral
                {
                    SdkProjectId = project.Id,
                    Name = p.Name.Trim(),
                    NaturalKey = naturalKey,
                    CreatedAtUtc = DateTime.UtcNow
                };
                db.Peripherals.Add(entity);
                inserted++;
            }
            else
            {
                updated++;
                entity.UpdatedAtUtc = DateTime.UtcNow;
            }

            entity.ChipId = chip?.Id;
            entity.SerialNumber = p.SerialNumber;
            entity.InlineFunctionCount = p.InlineFunctionCount;
            entity.AllFormsFunctionCount = p.AllFormsFunctionCount;
            entity.InstancesJson = JsonSerializer.Serialize(p.Instances);
            entity.TypedefsJson = JsonSerializer.Serialize(p.Typedefs);
            entity.RelatedFilesJson = JsonSerializer.Serialize(p.RelatedFiles);
            entity.Confidence = p.Confidence;
            entity.DetectionStatus = p.DetectionStatus;
            entity.Notes = p.Notes;
            entity.IsCommonDriver = p.IsCommonDriver;
            periMap[entity.Name] = entity;

            foreach (var rel in p.RelatedFiles.Distinct(StringComparer.OrdinalIgnoreCase))
                UpsertFile(db, project.Id, rel, entity, "peripheral_source", ref inserted, ref updated);
        }

        await db.SaveChangesAsync(cancellationToken);

        periMap = (await db.Peripherals.Where(x => x.SdkProjectId == project.Id).ToListAsync(cancellationToken))
            .ToDictionary(x => x.Name, x => x, StringComparer.OrdinalIgnoreCase);
        chipMap = (await db.Chips.Where(x => x.SdkProjectId == project.Id).ToListAsync(cancellationToken))
            .ToDictionary(x => x.ModelName, x => x, StringComparer.OrdinalIgnoreCase);
        var fileMap = (await db.SdkFiles.Where(x => x.SdkProjectId == project.Id).ToListAsync(cancellationToken))
            .ToDictionary(x => x.NaturalKey, x => x, StringComparer.OrdinalIgnoreCase);

        var existingFuncs = await db.LlFunctions.Where(x => x.SdkProjectId == project.Id)
            .ToDictionaryAsync(x => x.NaturalKey, cancellationToken);
        const int batchSize = 500;
        var buffer = new List<LlFunction>();

        foreach (var f in funcDoc.Functions)
        {
            if (string.IsNullOrWhiteSpace(f.FunctionName) || string.IsNullOrWhiteSpace(f.FilePath) || f.StartLine <= 0)
            {
                skipped++;
                continue;
            }

            var naturalKey = BuildFunctionNaturalKey(f.FilePath, f.StartLine, f.FunctionName, f.Form);
            Chip? chip = null;
            if (!string.IsNullOrWhiteSpace(f.Chip) && chipMap.TryGetValue(f.Chip, out var cEntity))
                chip = cEntity;
            Peripheral? peri = null;
            if (!string.IsNullOrWhiteSpace(f.Peripheral) && periMap.TryGetValue(f.Peripheral, out var pEntity))
                peri = pEntity;
            fileMap.TryGetValue(NormalizePath(f.FilePath), out var sdkFile);

            if (existingFuncs.TryGetValue(naturalKey, out var entity))
            {
                updated++;
                entity.UpdatedAtUtc = DateTime.UtcNow;
                ApplyFunction(entity, f, project.Id, chip, peri, sdkFile);
            }
            else
            {
                inserted++;
                entity = new LlFunction
                {
                    SdkProjectId = project.Id,
                    NaturalKey = naturalKey,
                    CreatedAtUtc = DateTime.UtcNow
                };
                ApplyFunction(entity, f, project.Id, chip, peri, sdkFile);
                buffer.Add(entity);
                existingFuncs[naturalKey] = entity;
            }

            if (buffer.Count >= batchSize)
            {
                db.LlFunctions.AddRange(buffer);
                await db.SaveChangesAsync(cancellationToken);
                buffer.Clear();
            }
        }

        if (buffer.Count > 0)
        {
            db.LlFunctions.AddRange(buffer);
            await db.SaveChangesAsync(cancellationToken);
        }

        record.FinishedAtUtc = DateTime.UtcNow;
        record.ChipCount = await db.Chips.CountAsync(x => x.SdkProjectId == project.Id, cancellationToken);
        record.PeripheralCount = await db.Peripherals.CountAsync(x => x.SdkProjectId == project.Id, cancellationToken);
        record.FunctionCount = await db.LlFunctions.CountAsync(x => x.SdkProjectId == project.Id, cancellationToken);
        record.FileCount = await db.SdkFiles.CountAsync(x => x.SdkProjectId == project.Id, cancellationToken);
        record.InsertedCount = inserted;
        record.UpdatedCount = updated;
        record.SkippedCount = skipped;
        record.ErrorCount = errors.Count;
        record.ErrorSummary = errors.Count == 0 ? null : string.Join(" | ", errors.Take(20));
        record.SummaryJson = JsonSerializer.Serialize(new
        {
            chipDoc.ChipCount,
            periDoc.PeripheralCount,
            funcDoc.FunctionCountTotal,
            funcDoc.InlineDefinitionCount
        });
        record.Status = errors.Count > 0 ? ScanStatus.Partial : ScanStatus.Imported;

        project.ScanStatus = record.Status;
        project.LastImportedAtUtc = DateTime.UtcNow;
        project.UpdatedAtUtc = DateTime.UtcNow;

        await db.SaveChangesAsync(cancellationToken);

        _logger.LogInformation(
            "Import finished for {Project}: chips={Chips}, peri={Peri}, funcs={Funcs}, inserted={Ins}, updated={Upd}, skipped={Skip}, errors={Err}",
            project.Name, record.ChipCount, record.PeripheralCount, record.FunctionCount, inserted, updated, skipped, errors.Count);

        return new ImportResult
        {
            Success = true,
            ScanRecordId = record.Id,
            ChipCount = record.ChipCount,
            PeripheralCount = record.PeripheralCount,
            FunctionCount = record.FunctionCount,
            FileCount = record.FileCount,
            InsertedCount = inserted,
            UpdatedCount = updated,
            SkippedCount = skipped,
            ErrorCount = errors.Count,
            Errors = errors,
            Message = $"导入完成：芯片 {record.ChipCount}，外设 {record.PeripheralCount}，函数 {record.FunctionCount}。"
        };
    }

    private static void UpsertFile(AppDbContext db, Guid projectId, string relativePath, Peripheral? peri, string role, ref int inserted, ref int updated)
    {
        var key = NormalizePath(relativePath);
        var existing = db.SdkFiles.Local.FirstOrDefault(x => x.SdkProjectId == projectId && x.NaturalKey == key)
            ?? db.SdkFiles.FirstOrDefault(x => x.SdkProjectId == projectId && x.NaturalKey == key);

        if (existing is null)
        {
            existing = new SdkFile
            {
                SdkProjectId = projectId,
                RelativePath = relativePath.Replace('\\', '/'),
                FileName = Path.GetFileName(relativePath),
                Extension = Path.GetExtension(relativePath),
                NaturalKey = key,
                Role = role,
                PeripheralId = peri?.Id,
                CreatedAtUtc = DateTime.UtcNow
            };
            db.SdkFiles.Add(existing);
            inserted++;
        }
        else
        {
            updated++;
            existing.UpdatedAtUtc = DateTime.UtcNow;
            existing.Role ??= role;
            if (peri is not null) existing.PeripheralId = peri.Id;
        }
    }

    private static void ApplyFunction(LlFunction entity, FunctionDto f, Guid projectId, Chip? chip, Peripheral? peri, SdkFile? file)
    {
        entity.SdkProjectId = projectId;
        entity.FunctionName = f.FunctionName.Trim();
        entity.ReturnType = f.ReturnType;
        entity.Parameters = f.Parameters;
        entity.FunctionType = f.FunctionType;
        entity.Form = f.Form;
        entity.PeripheralName = f.Peripheral;
        entity.ChipName = f.Chip;
        entity.FilePath = f.FilePath.Replace('\\', '/');
        entity.StartLine = f.StartLine;
        entity.EndLine = f.EndLine;
        entity.DetectionStatus = f.DetectionStatus;
        entity.ChipId = chip?.Id;
        entity.PeripheralId = peri?.Id;
        entity.SdkFileId = file?.Id;
        entity.NaturalKey = BuildFunctionNaturalKey(f.FilePath, f.StartLine, f.FunctionName, f.Form);
    }

    public static string BuildFunctionNaturalKey(string filePath, int startLine, string name, string? form)
        => $"{NormalizePath(filePath)}|{startLine}|{name.Trim()}|{form ?? ""}";

    private static string NormalizePath(string path) => path.Replace('\\', '/').Trim().TrimStart('/');
    private static string Normalize(string value) => value.Trim().ToUpperInvariant();

    private static void ValidateRequiredFile(string path, List<string> errors)
    {
        if (!File.Exists(path))
            errors.Add($"缺少文件: {path}");
    }

    private static async Task<T> ReadJsonAsync<T>(string path, CancellationToken ct)
    {
        await using var stream = File.OpenRead(path);
        var doc = await JsonSerializer.DeserializeAsync<T>(stream, JsonOptions, ct);
        return doc ?? throw new InvalidOperationException($"反序列化结果为空: {path}");
    }

    private static ImportResult Fail(IEnumerable<string> errors, string message) => new()
    {
        Success = false,
        Errors = errors.ToList(),
        Message = message
    };
}
