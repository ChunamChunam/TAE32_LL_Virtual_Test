using System.Text.Json;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Register;

public sealed class RegisterFallbackBuildResult
{
    public List<PeripheralInstance> Instances { get; } = new();
    public List<RegisterDefinition> Registers { get; } = new();
    public List<RegisterField> Fields { get; } = new();
    public List<RegisterMacroReference> MacroReferences { get; } = new();
    public List<RegisterParseDiagnostic> Diagnostics { get; } = new();
}

public sealed class RegisterParseBridgeFallback
{
    public RegisterFallbackBuildResult Build(
        Guid sdkProjectId,
        RegisterLlScanResult scan,
        IReadOnlyList<Peripheral> peripherals,
        IReadOnlyList<Chip> chips,
        RegisterEnvironmentProbeResult env)
    {
        var result = new RegisterFallbackBuildResult();
        var chipId = chips.FirstOrDefault()?.Id;
        var periByModule = BuildPeripheralLookup(peripherals);

        result.Diagnostics.Add(new RegisterParseDiagnostic
        {
            SdkProjectId = sdkProjectId,
            Severity = RegisterParseDiagnosticSeverity.Error.ToString(),
            Category = RegisterParseDiagnosticCategory.MissingSdkHeader.ToString(),
            Message = "Authoritative SDK device header (tae32g58xx.h) not found under SDK tree. Register offsets/addresses cannot be confirmed from definitions.",
            Detail = string.Join("; ", env.MissingExpected)
        });

        result.Diagnostics.Add(new RegisterParseDiagnostic
        {
            SdkProjectId = sdkProjectId,
            Severity = RegisterParseDiagnosticSeverity.Warning.ToString(),
            Category = RegisterParseDiagnosticCategory.PendingConfirmation.ToString(),
            Message = "All register offsets and absolute addresses are PendingConfirmation — derived only from LL member-access evidence.",
            RelatedEntity = "RegisterDefinition"
        });

        foreach (var ev in scan.Instances)
        {
            periByModule.TryGetValue(ev.ModuleName, out var peri);
            var td = ev.TypeDefName
                     ?? (scan.InstanceToTypeDef.TryGetValue(ev.Name, out var t) ? t : null)
                     ?? scan.ModuleToPrimaryTypeDef.GetValueOrDefault(ev.ModuleName);

            result.Instances.Add(new PeripheralInstance
            {
                SdkProjectId = sdkProjectId,
                ChipId = chipId,
                PeripheralId = peri?.Id,
                Name = ev.Name,
                ModuleName = ev.ModuleName,
                TypeDefName = td,
                BaseAddress = null,
                BaseAddressStatus = AddressConfirmationStatus.PendingConfirmation.ToString(),
                DefinitionFile = ev.SourceFile,
                DefinitionLine = ev.Line,
                NaturalKey = RegisterNaturalKeys.Instance(sdkProjectId, ev.Name)
            });
        }

        var registerIds = new Dictionary<string, RegisterDefinition>(StringComparer.Ordinal);
        foreach (var mem in scan.RegisterMembers)
        {
            var key = RegisterNaturalKeys.Register(sdkProjectId, mem.StructName, mem.MemberName);
            if (registerIds.ContainsKey(key)) continue;

            periByModule.TryGetValue(mem.ModuleName, out var peri);
            var reg = new RegisterDefinition
            {
                SdkProjectId = sdkProjectId,
                ChipId = chipId,
                PeripheralId = peri?.Id,
                StructName = mem.StructName,
                MemberName = mem.MemberName,
                MemberType = "unknown (LL evidence)",
                OffsetBytes = null,
                OffsetStatus = AddressConfirmationStatus.PendingConfirmation.ToString(),
                AbsoluteAddress = null,
                AbsoluteAddressStatus = AddressConfirmationStatus.PendingConfirmation.ToString(),
                WidthBits = null,
                ResetValue = null,
                AccessAttribute = RegisterAccessAttributeKind.Unknown.ToString(),
                DefinitionFile = mem.SourceFile,
                StartLine = mem.Line,
                EndLine = mem.Line,
                ParseStatus = RegisterEntityParseStatus.Partial.ToString(),
                NaturalKey = key
            };
            registerIds[key] = reg;
            result.Registers.Add(reg);
        }

        foreach (var macro in scan.MacroReferences)
        {
            RegisterDefinition? linked = TryLinkMacroToRegister(macro.MacroName, registerIds);
            Guid? fieldId = null;
            RegisterField? field = null;
            if (linked is not null && TryInferFieldName(macro.MacroName, out var fieldName))
            {
                field = EnsureField(result, linked, fieldName, macro);
                fieldId = field.Id;
            }

            result.MacroReferences.Add(new RegisterMacroReference
            {
                SdkProjectId = sdkProjectId,
                RegisterDefinitionId = linked?.Id,
                RegisterFieldId = fieldId,
                MacroName = macro.MacroName,
                MacroKind = macro.MacroKind,
                ReferenceFile = macro.SourceFile,
                ReferenceLine = macro.Line,
                Resolved = false
            });
        }

        return result;
    }

    private static RegisterField EnsureField(
        RegisterFallbackBuildResult result,
        RegisterDefinition reg,
        string fieldName,
        LlMacroEvidence macro)
    {
        var existing = result.Fields.FirstOrDefault(f =>
            f.RegisterDefinitionId == reg.Id && f.Name == fieldName);
        if (existing is not null) return existing;

        var field = new RegisterField
        {
            RegisterDefinitionId = reg.Id,
            Name = fieldName,
            AccessAttribute = RegisterAccessAttributeKind.Unknown.ToString(),
            ParseStatus = RegisterEntityParseStatus.Unconfirmed.ToString(),
            NaturalKey = RegisterNaturalKeys.Field(reg.Id, fieldName),
            DefinitionFile = macro.SourceFile,
            DefinitionLine = macro.Line,
            PosMacroName = macro.MacroKind == RegisterMacroKind.Pos.ToString() ? macro.MacroName : null,
            MskMacroName = macro.MacroKind == RegisterMacroKind.Msk.ToString() ? macro.MacroName : null
        };
        result.Fields.Add(field);
        reg.Fields.Add(field);
        return field;
    }

    private static RegisterDefinition? TryLinkMacroToRegister(string macro, Dictionary<string, RegisterDefinition> registers)
    {
        // Heuristic: GPIOA_BSR_BSn_Pos -> register member BSR
        var parts = macro.Split('_');
        for (var i = parts.Length - 1; i >= 1; i--)
        {
            if (parts[i] is "Pos" or "Msk" or "Shift" or "BIT")
                continue;
            if (parts[i].EndsWith('n'))
                continue;
            var candidate = parts[i];
            var hit = registers.Values.FirstOrDefault(r =>
                string.Equals(r.MemberName, candidate, StringComparison.OrdinalIgnoreCase));
            if (hit is not null) return hit;
        }
        return null;
    }

    private static bool TryInferFieldName(string macro, out string fieldName)
    {
        fieldName = string.Empty;
        var parts = macro.Split('_');
        if (parts.Length < 3) return false;
        var tail = parts[^2];
        if (tail.Length == 0) return false;
        fieldName = tail;
        return true;
    }

    private static Dictionary<string, Peripheral> BuildPeripheralLookup(IReadOnlyList<Peripheral> peripherals)
    {
        var map = new Dictionary<string, Peripheral>(StringComparer.OrdinalIgnoreCase);
        foreach (var p in peripherals)
        {
            map.TryAdd(p.Name, p);
            if (!string.IsNullOrWhiteSpace(p.InstancesJson))
            {
                try
                {
                    var inst = JsonSerializer.Deserialize<List<string>>(p.InstancesJson);
                    if (inst is not null)
                        foreach (var name in inst)
                        {
                            var mod = RegisterTimerModuleMap.ResolveModuleForInstance(name) ?? p.Name;
                            map.TryAdd(mod, p);
                        }
                }
                catch
                {
                    // ignore bad json
                }
            }
        }
        return map;
    }
}
