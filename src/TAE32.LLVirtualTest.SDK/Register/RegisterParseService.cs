using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class RegisterParseService : IRegisterParser
{
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ILogger<RegisterParseService> _logger;
    private readonly ILlStaticAnalysisPersistService _staticAnalysis;

    public RegisterParseService(
        IDbContextFactory<AppDbContext> dbFactory,
        ILogger<RegisterParseService> logger,
        ILlStaticAnalysisPersistService staticAnalysis)
    {
        _dbFactory = dbFactory;
        _logger = logger;
        _staticAnalysis = staticAnalysis;
    }

    public async Task<RegisterParseSummary> ParseAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
    {
        string sdkRoot;
        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            var project = await db.SdkProjects.AsNoTracking()
                .FirstOrDefaultAsync(x => x.Id == sdkProjectId, cancellationToken);
            if (project is null)
                return new RegisterParseSummary { SdkProjectId = sdkProjectId, Message = "SDK project not found" };
            sdkRoot = project.SdkRootPath;
        }

        var probe = new RegisterEnvironmentProbe().Probe(sdkRoot);
        if (!Directory.Exists(probe.LlRoot))
        {
            return new RegisterParseSummary
            {
                SdkProjectId = sdkProjectId,
                Message = $"LL root not found under {sdkRoot}",
                MissingHeaders = probe.MissingExpected
            };
        }

        var scan = new RegisterLlEvidenceScanner().Scan(probe.LlRoot);

        List<Chip> chips;
        List<Peripheral> peripherals;
        await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
        {
            chips = await db.Chips.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId).ToListAsync(cancellationToken);
            peripherals = await db.Peripherals.AsNoTracking().Where(x => x.SdkProjectId == sdkProjectId).ToListAsync(cancellationToken);
        }

        var chipId = chips.FirstOrDefault()?.Id;
        var periByModule = peripherals
            .GroupBy(p => p.Name, StringComparer.OrdinalIgnoreCase)
            .ToDictionary(g => g.Key, g => g.First(), StringComparer.OrdinalIgnoreCase);

        var instances = new List<PeripheralInstance>();
        var registers = new List<RegisterDefinition>();
        var fields = new List<RegisterField>();
        var enums = new List<RegisterEnumValue>();
        var macros = new List<RegisterMacroReference>();
        var diagnostics = new List<RegisterParseDiagnostic>();
        var usedDevice = false;

        if (probe.HasAuthoritativeDeviceHeader
            && probe.AuthoritativeDeviceHeader is not null
            && probe.ChipHeader is not null)
        {
            usedDevice = true;
            var device = new RegisterDeviceHeaderParser().Parse(
                sdkProjectId,
                probe.AuthoritativeDeviceHeader,
                probe.ChipHeader,
                scan,
                chipId);

            registers.AddRange(device.Registers);
            fields.AddRange(device.Fields);
            macros.AddRange(device.Macros);
            diagnostics.AddRange(device.Diagnostics);

            // Instances from LL evidence + confirmed bases from device header.
            foreach (var ev in scan.Instances)
            {
                periByModule.TryGetValue(ev.ModuleName, out var peri);
                var td = ev.TypeDefName
                         ?? (scan.InstanceToTypeDef.TryGetValue(ev.Name, out var t) ? t : null)
                         ?? scan.ModuleToPrimaryTypeDef.GetValueOrDefault(ev.ModuleName);

                uint? baseAddr = null;
                var baseStatus = AddressConfirmationStatus.PendingConfirmation.ToString();
                if (device.InstanceBaseAddresses.TryGetValue(ev.Name, out var ba))
                {
                    baseAddr = ba;
                    baseStatus = AddressConfirmationStatus.Confirmed.ToString();
                }

                instances.Add(new PeripheralInstance
                {
                    SdkProjectId = sdkProjectId,
                    ChipId = chipId,
                    PeripheralId = peri?.Id,
                    Name = ev.Name,
                    ModuleName = ev.ModuleName,
                    TypeDefName = td,
                    BaseAddress = baseAddr,
                    BaseAddressStatus = baseStatus,
                    DefinitionFile = ev.SourceFile,
                    DefinitionLine = ev.Line,
                    NaturalKey = RegisterNaturalKeys.Instance(sdkProjectId, ev.Name)
                });
            }

            // Fill absolute address = instance base + offset when both known (per primary instance of module).
            ApplyAbsoluteAddresses(registers, instances, device);

            if (!string.IsNullOrWhiteSpace(probe.SvdPath))
            {
                diagnostics.Add(new RegisterParseDiagnostic
                {
                    SdkProjectId = sdkProjectId,
                    Severity = RegisterParseDiagnosticSeverity.Info.ToString(),
                    Category = RegisterParseDiagnosticCategory.DeviceHeader.ToString(),
                    Message = $"SVD available for future import: {probe.SvdPath}",
                    FilePath = probe.SvdPath
                });
            }
        }
        else
        {
            var fallback = new RegisterParseBridgeFallback().Build(sdkProjectId, scan, peripherals, chips, probe);
            instances.AddRange(fallback.Instances);
            registers.AddRange(fallback.Registers);
            fields.AddRange(fallback.Fields);
            macros.AddRange(fallback.MacroReferences);
            diagnostics.AddRange(fallback.Diagnostics);
        }

        diagnostics.Add(new RegisterParseDiagnostic
        {
            SdkProjectId = sdkProjectId,
            Severity = "Info",
            Category = "LlEvidence",
            Message = $"LL evidence scan: instances={scan.Instances.Count}, register members={scan.RegisterMembers.Count}, macro refs={scan.MacroReferences.Count}",
            Detail = $"LlRoot={probe.LlRoot}; Device={probe.AuthoritativeDeviceHeader}; Chip={probe.ChipHeader}"
        });

        await PersistAsync(sdkProjectId, instances, registers, fields, enums, macros, diagnostics, cancellationToken);

        // Macros just refreshed — invalidate stamp by re-analyzing all LL bodies that have SourceText.
        string saMsg;
        try
        {
            // Clear stamps so AnalyzeProject re-runs against new macro catalog.
            await using (var db = await _dbFactory.CreateDbContextAsync(cancellationToken))
            {
                await db.LlFunctions
                    .Where(x => x.SdkProjectId == sdkProjectId && x.StaticAnalysisStamp != null)
                    .ExecuteUpdateAsync(s => s
                            .SetProperty(f => f.StaticAnalysisStamp, (string?)null)
                            .SetProperty(f => f.StaticAnalysisJson, (string?)null),
                        cancellationToken)
                    .ConfigureAwait(false);
            }

            TAE32.LLVirtualTest.Infrastructure.TestEngine.SdkMacroSemanticCatalog
                .InvalidateProject(sdkProjectId);
            var sa = await _staticAnalysis.AnalyzeProjectAsync(sdkProjectId, cancellationToken)
                .ConfigureAwait(false);
            saMsg = sa.Message;
        }
        catch (Exception ex)
        {
            _logger.LogWarning(ex, "Static analysis after register parse failed for {ProjectId}", sdkProjectId);
            saMsg = "静态分析跳过：" + ex.Message;
        }

        _logger.LogInformation(
            "Register parse project {ProjectId}: device={Device} instances={Instances}, registers={Registers}, macros={Macros}, diagnostics={Diag}",
            sdkProjectId, usedDevice, instances.Count, registers.Count, macros.Count, diagnostics.Count);

        return new RegisterParseSummary
        {
            SdkProjectId = sdkProjectId,
            UsedDeviceHeader = usedDevice,
            UsedParseBridgeEvidenceOnly = !usedDevice,
            InstanceCount = instances.Count,
            RegisterCount = registers.Count,
            FieldCount = fields.Count,
            MacroReferenceCount = macros.Count,
            ResolvedMacroCount = macros.Count(m => m.Resolved),
            DiagnosticCount = diagnostics.Count,
            FoundHeaders = probe.FoundDeviceIncludes.Concat(probe.ChipHeader is null ? Array.Empty<string>() : new[] { probe.ChipHeader }).ToList(),
            MissingHeaders = probe.MissingExpected,
            Message = (usedDevice
                ? "Parsed with authoritative device/chip headers (CMSIS @offset + __IOM/__IM/__OM)."
                : "Parsed from LL evidence only (device header still missing).")
                + " " + saMsg
        };
    }

    private static void ApplyAbsoluteAddresses(
        List<RegisterDefinition> registers,
        List<PeripheralInstance> instances,
        RegisterDeviceParseResult device)
    {
        // For GPIOA_Type.ODR use GPIOA_BASE + offset; for GPIO_TypeDef use first matching instance base of module.
        foreach (var reg in registers)
        {
            if (reg.OffsetBytes is null) continue;

            string? instanceName = null;
            if (reg.StructName.EndsWith("_Type", StringComparison.Ordinal))
                instanceName = reg.StructName[..^5]; // GPIOA_Type -> GPIOA
            else if (reg.StructName.EndsWith("_TypeDef", StringComparison.Ordinal))
            {
                var module = reg.StructName[..^8]; // GPIO
                instanceName = instances.FirstOrDefault(i =>
                    string.Equals(i.ModuleName, module, StringComparison.OrdinalIgnoreCase)
                    || i.Name.StartsWith(module, StringComparison.OrdinalIgnoreCase))?.Name;
            }

            if (instanceName is null) continue;
            if (!device.InstanceBaseAddresses.TryGetValue(instanceName, out var baseAddr)) continue;

            reg.AbsoluteAddress = baseAddr + (uint)reg.OffsetBytes.Value;
            reg.AbsoluteAddressStatus = AddressConfirmationStatus.Confirmed.ToString();

            var inst = instances.FirstOrDefault(i => i.Name == instanceName);
            if (inst is not null)
                reg.PeripheralInstanceId = inst.Id;
        }
    }

    private async Task PersistAsync(
        Guid sdkProjectId,
        List<PeripheralInstance> instances,
        List<RegisterDefinition> registers,
        List<RegisterField> fields,
        List<RegisterEnumValue> enumValues,
        List<RegisterMacroReference> macros,
        List<RegisterParseDiagnostic> diagnostics,
        CancellationToken cancellationToken)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);

        var regIds = await db.RegisterDefinitions.Where(x => x.SdkProjectId == sdkProjectId).Select(x => x.Id).ToListAsync(cancellationToken);
        var fieldIds = regIds.Count == 0
            ? new List<Guid>()
            : await db.RegisterFields.Where(x => regIds.Contains(x.RegisterDefinitionId)).Select(x => x.Id).ToListAsync(cancellationToken);

        if (fieldIds.Count > 0)
            await db.RegisterEnumValues.Where(x => x.RegisterFieldId != null && fieldIds.Contains(x.RegisterFieldId.Value))
                .ExecuteDeleteAsync(cancellationToken);
        if (regIds.Count > 0)
            await db.RegisterEnumValues.Where(x => x.RegisterDefinitionId != null && regIds.Contains(x.RegisterDefinitionId.Value))
                .ExecuteDeleteAsync(cancellationToken);

        await db.RegisterMacroReferences.Where(x => x.SdkProjectId == sdkProjectId).ExecuteDeleteAsync(cancellationToken);
        if (regIds.Count > 0)
            await db.RegisterFields.Where(x => regIds.Contains(x.RegisterDefinitionId)).ExecuteDeleteAsync(cancellationToken);
        await db.RegisterDefinitions.Where(x => x.SdkProjectId == sdkProjectId).ExecuteDeleteAsync(cancellationToken);
        await db.PeripheralInstances.Where(x => x.SdkProjectId == sdkProjectId).ExecuteDeleteAsync(cancellationToken);
        await db.RegisterParseDiagnostics.Where(x => x.SdkProjectId == sdkProjectId).ExecuteDeleteAsync(cancellationToken);

        // Ensure instance Ids exist before FK from registers.
        if (instances.Count > 0) await db.PeripheralInstances.AddRangeAsync(instances, cancellationToken);
        await db.SaveChangesAsync(cancellationToken);

        // Re-link PeripheralInstanceId after instances have stable Ids (already set in ApplyAbsoluteAddresses).
        if (registers.Count > 0) await db.RegisterDefinitions.AddRangeAsync(registers, cancellationToken);
        await db.SaveChangesAsync(cancellationToken);

        // Fields reference RegisterDefinition.Id — dedupe NaturalKey per register.
        if (fields.Count > 0)
        {
            var uniqueFields = fields
                .GroupBy(f => (f.RegisterDefinitionId, f.NaturalKey))
                .Select(g => g.First())
                .ToList();
            await db.RegisterFields.AddRangeAsync(uniqueFields, cancellationToken);
        }
        if (enumValues.Count > 0) await db.RegisterEnumValues.AddRangeAsync(enumValues, cancellationToken);
        if (macros.Count > 0) await db.RegisterMacroReferences.AddRangeAsync(macros, cancellationToken);
        if (diagnostics.Count > 0) await db.RegisterParseDiagnostics.AddRangeAsync(diagnostics, cancellationToken);

        await db.SaveChangesAsync(cancellationToken);
    }
}
