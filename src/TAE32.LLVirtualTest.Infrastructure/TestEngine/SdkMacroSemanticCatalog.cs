using System.Collections.Concurrent;
using System.Globalization;
using System.Text.RegularExpressions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Classifies SDK numeric macros using real #define values (not suffix alone).
/// Prefer SQLite <c>RegisterMacroReferences</c> / <c>RegisterFields</c> (already parsed at scan);
/// fall back to chip.h only when the DB is empty.
/// </summary>
internal sealed class SdkMacroSemanticCatalog
{
    private static readonly Regex UintDefine = new(
        @"#define\s+(?<name>[A-Za-z_][A-Za-z0-9_]*)\s+(?<val>\(?\s*(?:0x[0-9A-Fa-f]+|\d+)(?:UL|U|L)?\s*\)?)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    /// <summary>Process cache: SDK project id → catalog built from SQLite.</summary>
    private static readonly ConcurrentDictionary<Guid, SdkMacroSemanticCatalog?> ProjectCache = new();

    /// <summary>
    /// Slow path only: chip.h + chip_struct.h (~11MB). Prefer <see cref="TryLoadFromDbAsync"/>.
    /// </summary>
    private static readonly ConcurrentDictionary<string, SdkMacroSemanticCatalog?> RootCache =
        new(StringComparer.OrdinalIgnoreCase);

    private readonly Dictionary<string, SdkMacroSemanticInfo> _macros =
        new(StringComparer.OrdinalIgnoreCase);
    private readonly HashSet<string> _ingestedPaths = new(StringComparer.OrdinalIgnoreCase);
    private readonly object _ingestLock = new();

    public int Count => _macros.Count;
    public string Source { get; private set; } = "empty";

    /// <summary>
    /// Load Pos/Msk macros from Phase-4 SQLite (RegisterMacroReferences + RegisterFields).
    /// This is the preferred path — scan already stored Expansion / BitPosition / Mask.
    /// </summary>
    public static async Task<SdkMacroSemanticCatalog?> TryLoadFromDbAsync(
        IDbContextFactory<AppDbContext> dbFactory,
        Guid sdkProjectId,
        CancellationToken cancellationToken = default)
    {
        if (ProjectCache.TryGetValue(sdkProjectId, out var cached))
            return cached;

        var built = await BuildFromDbAsync(dbFactory, sdkProjectId, cancellationToken)
            .ConfigureAwait(false);
        ProjectCache[sdkProjectId] = built;
        return built;
    }

    /// <summary>Legacy/file fallback when DB has no macro rows (unit tests / incomplete scan).</summary>
    public static SdkMacroSemanticCatalog? TryLoad(string? sdkRoot)
    {
        if (string.IsNullOrWhiteSpace(sdkRoot) || !Directory.Exists(sdkRoot))
            return null;

        var key = Path.GetFullPath(sdkRoot);
        return RootCache.GetOrAdd(key, static root => BuildForRoot(root));
    }

    /// <summary>Test helper: drop process-memory caches.</summary>
    internal static void ClearMemoryCacheForTests()
    {
        RootCache.Clear();
        ProjectCache.Clear();
    }

    /// <summary>Drop SQLite-backed catalog for one project (after register re-parse).</summary>
    internal static void InvalidateProject(Guid sdkProjectId)
        => ProjectCache.TryRemove(sdkProjectId, out _);

    private static async Task<SdkMacroSemanticCatalog?> BuildFromDbAsync(
        IDbContextFactory<AppDbContext> dbFactory,
        Guid sdkProjectId,
        CancellationToken cancellationToken)
    {
        await using var db = await dbFactory.CreateDbContextAsync(cancellationToken)
            .ConfigureAwait(false);

        var macros = await db.RegisterMacroReferences.AsNoTracking()
            .Where(x => x.SdkProjectId == sdkProjectId)
            .Select(x => new { x.MacroName, x.MacroKind, x.Expansion, x.DefinitionFile })
            .ToListAsync(cancellationToken)
            .ConfigureAwait(false);

        if (macros.Count == 0)
            return null;

        var fieldHints = await (
                from f in db.RegisterFields.AsNoTracking()
                join r in db.RegisterDefinitions.AsNoTracking() on f.RegisterDefinitionId equals r.Id
                where r.SdkProjectId == sdkProjectId
                select new
                {
                    f.PosMacroName,
                    f.MskMacroName,
                    f.BitPosition,
                    f.Mask,
                    Register = r.MemberName,
                    Peri = r.PeripheralInstance != null
                        ? r.PeripheralInstance.Name
                        : r.StructName
                })
            .ToListAsync(cancellationToken)
            .ConfigureAwait(false);

        var catalog = new SdkMacroSemanticCatalog { Source = "sqlite" };

        foreach (var m in macros)
        {
            if (string.IsNullOrWhiteSpace(m.MacroName)) continue;
            if (!TryParseUint(m.Expansion ?? "", out var value)
                && !TryParseUint(m.Expansion?.Trim('(', ')') ?? "", out value))
                continue;

            var info = Classify(m.MacroName, value, m.DefinitionFile ?? "RegisterMacroReferences");
            if (string.Equals(m.MacroKind, "Pos", StringComparison.OrdinalIgnoreCase))
                info.Kind = value < 64 ? SdkMacroSemanticKind.BitFieldPosition : info.Kind;
            else if (string.Equals(m.MacroKind, "Msk", StringComparison.OrdinalIgnoreCase)
                     || string.Equals(m.MacroKind, "Mask", StringComparison.OrdinalIgnoreCase))
                info.Kind = SdkMacroSemanticKind.BitFieldMask;

            catalog._macros[m.MacroName] = info;
        }

        foreach (var f in fieldHints)
        {
            void Enrich(string? name, uint? numeric, SdkMacroSemanticKind kind)
            {
                if (string.IsNullOrWhiteSpace(name)) return;
                if (!catalog._macros.TryGetValue(name, out var info))
                {
                    if (numeric is null) return;
                    info = Classify(name, numeric.Value, "RegisterFields");
                    catalog._macros[name] = info;
                }

                info.Kind = kind;
                info.RegisterHint ??= f.Register;
                info.PeripheralHint ??= f.Peri;
                if (numeric is uint nv)
                    info.NumericValue = nv;
            }

            Enrich(f.PosMacroName,
                f.BitPosition is int bp ? (uint)bp : null,
                SdkMacroSemanticKind.BitFieldPosition);
            Enrich(f.MskMacroName, f.Mask, SdkMacroSemanticKind.BitFieldMask);
        }

        catalog.CrossValidatePairs();
        return catalog.Count > 0 ? catalog : null;
    }

    private static SdkMacroSemanticCatalog? BuildForRoot(string sdkRoot)
    {
        var chip = ChipHeaderAddressCatalog.TryLoad(sdkRoot);
        if (chip is null) return null;

        var catalog = new SdkMacroSemanticCatalog { Source = "chip.h" };
        foreach (var path in new[] { chip.DeviceHeaderPath, chip.ChipHeaderPath, chip.ChipStructPath })
        {
            if (string.IsNullOrWhiteSpace(path) || !File.Exists(path)) continue;
            catalog.IngestFile(path);
        }

        catalog.CrossValidatePairs();
        return catalog.Count > 0 ? catalog : null;
    }

    private static readonly Regex LlHelperDefine = new(
        @"#define\s+(?<name>LL_[A-Za-z0-9_]+)\s+(?<val>\(?\s*(?:0x[0-9A-Fa-f]+|\d+)(?:UL|U|L)?\s*\)?)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    /// <summary>Also ingest an LL header so local helper macros are visible (once per path).</summary>
    public void IngestFile(string path)
    {
        if (string.IsNullOrWhiteSpace(path)) return;
        string full;
        try { full = Path.GetFullPath(path); }
        catch { return; }

        lock (_ingestLock)
        {
            if (!_ingestedPaths.Add(full))
                return;

            string text;
            try { text = File.ReadAllText(full); }
            catch
            {
                _ingestedPaths.Remove(full);
                return;
            }

            foreach (Match m in UintDefine.Matches(text))
            {
                var name = m.Groups["name"].Value;
                if (!TryParseUint(m.Groups["val"].Value, out var value)) continue;
                var info = Classify(name, value, full);
                _macros[name] = info;
            }
        }
    }

    /// <summary>
    /// Fast path for SQLite-backed catalogs: only single-line numeric <c>LL_*</c> helpers.
    /// Multi-line composite masks (OR of chip _Msk) are intentionally skipped — analyzer
    /// treats <c>LL_*_MSK</c> names as opaque helper masks.
    /// </summary>
    public void IngestLlHelperDefines(string path)
    {
        if (string.IsNullOrWhiteSpace(path)) return;
        string full;
        try { full = Path.GetFullPath(path); }
        catch { return; }

        var key = "llhelp:" + full;
        lock (_ingestLock)
        {
            if (!_ingestedPaths.Add(key))
                return;

            string text;
            try { text = File.ReadAllText(full); }
            catch
            {
                _ingestedPaths.Remove(key);
                return;
            }

            foreach (Match m in LlHelperDefine.Matches(text))
            {
                var name = m.Groups["name"].Value;
                if (!TryParseUint(m.Groups["val"].Value, out var value)) continue;
                var info = Classify(name, value, full);
                if (name.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase)
                    || name.EndsWith("_MASK", StringComparison.OrdinalIgnoreCase)
                    || name.EndsWith("_BIT", StringComparison.OrdinalIgnoreCase))
                    info.Kind = SdkMacroSemanticKind.BitFieldMask;
                _macros[name] = info;
            }
        }
    }

    public bool TryGet(string name, out SdkMacroSemanticInfo info)
        => _macros.TryGetValue(name, out info!);

    public SdkMacroSemanticInfo? GetOrNull(string name)
        => _macros.TryGetValue(name, out var info) ? info : null;

    private void CrossValidatePairs()
    {
        // Prefer paired evidence: X_Pos + X_Msk → confirm kinds by value shape.
        foreach (var kv in _macros.ToList())
        {
            var name = kv.Key;
            var info = kv.Value;
            if (name.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
                || name.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            {
                var posName = name[..^4] + "_Pos";
                if (_macros.TryGetValue(posName, out var pos) && pos.NumericValue is uint pv)
                {
                    info.Kind = SdkMacroSemanticKind.BitFieldMask;
                    if (pos.Kind is SdkMacroSemanticKind.Unknown or SdkMacroSemanticKind.NumericOther)
                        pos.Kind = pv < 64 ? SdkMacroSemanticKind.BitFieldPosition : pos.Kind;
                    SyncHints(info, pos);
                }
            }
            else if (name.EndsWith("_Pos", StringComparison.OrdinalIgnoreCase))
            {
                var mskName = name[..^4] + "_Msk";
                if (_macros.TryGetValue(mskName, out var msk))
                {
                    if (info.NumericValue is uint pv && pv < 64)
                        info.Kind = SdkMacroSemanticKind.BitFieldPosition;
                    if (msk.Kind is SdkMacroSemanticKind.Unknown or SdkMacroSemanticKind.NumericOther)
                        msk.Kind = SdkMacroSemanticKind.BitFieldMask;
                    SyncHints(msk, info);
                }
            }
        }
    }

    private static void SyncHints(SdkMacroSemanticInfo a, SdkMacroSemanticInfo b)
    {
        a.PeripheralHint ??= b.PeripheralHint;
        a.RegisterHint ??= b.RegisterHint;
        a.FieldHint ??= b.FieldHint;
        b.PeripheralHint ??= a.PeripheralHint;
        b.RegisterHint ??= a.RegisterHint;
        b.FieldHint ??= a.FieldHint;
    }

    private static SdkMacroSemanticInfo Classify(string name, uint value, string path)
    {
        var info = new SdkMacroSemanticInfo
        {
            Name = name,
            NumericValue = value,
            Expansion = $"0x{value:X}",
            DefinitionFile = path
        };
        TryParseNameParts(name, out var peri, out var reg, out var field, out var suffix);
        info.PeripheralHint = peri;
        info.RegisterHint = reg;
        info.FieldHint = field;

        // Value-first heuristics, then name suffix as corroboration.
        var pop = PopCount(value);
        var trailing = CountTrailingZeros(value);

        if (string.Equals(suffix, "BASE", StringComparison.OrdinalIgnoreCase)
            || name.EndsWith("_BASE", StringComparison.OrdinalIgnoreCase))
        {
            info.Kind = SdkMacroSemanticKind.RegisterBase;
            return info;
        }

        if (string.Equals(suffix, "Pos", StringComparison.OrdinalIgnoreCase))
        {
            info.Kind = value < 64
                ? SdkMacroSemanticKind.BitFieldPosition
                : SdkMacroSemanticKind.NumericOther;
            return info;
        }

        if (string.Equals(suffix, "Msk", StringComparison.OrdinalIgnoreCase)
            || string.Equals(suffix, "MSK", StringComparison.OrdinalIgnoreCase))
        {
            // Real masks are typically contiguous (or multi-bit). A "_Msk" with value >= 32 used as Pos is UB.
            info.Kind = SdkMacroSemanticKind.BitFieldMask;
            return info;
        }

        if (string.Equals(suffix, "Val", StringComparison.OrdinalIgnoreCase)
            || string.Equals(suffix, "VAL", StringComparison.OrdinalIgnoreCase))
        {
            info.Kind = SdkMacroSemanticKind.BitFieldValue;
            return info;
        }

        // Unsuffixed numeric: position-like if small; mask-like if multi-bit contiguous.
        if (value < 32 && pop == 1 && trailing == (int)value)
            info.Kind = SdkMacroSemanticKind.NumericOther; // ambiguous single-bit constant
        else if (pop >= 2 && IsContiguousMask(value))
            info.Kind = SdkMacroSemanticKind.BitFieldMask;
        else
            info.Kind = SdkMacroSemanticKind.NumericOther;

        return info;
    }

    /// <summary>
    /// Parse chip field macros. Naming is always
    /// <c>{Peripheral}_{Register}_{Field}_{Suffix}</c> where Peripheral may itself
    /// contain underscores (e.g. <c>HRPWM_MST_MCR0_CONT_Msk</c>,
    /// <c>HRPWM_SLV0_PWMCR0_CONT_Msk</c>, <c>WWDG_PSCR_PSC_Msk</c>).
    /// Last segment before suffix = field; second-last = register; remainder = peripheral.
    /// </summary>
    internal static bool TryParseNameParts(
        string name,
        out string? peripheral,
        out string? register,
        out string? field,
        out string? suffix)
    {
        peripheral = register = field = suffix = null;
        var parts = name.Split('_', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length < 2) return false;

        var last = parts[^1];
        var isSuffix = last is "Msk" or "MSK" or "Pos" or "POS" or "Val" or "VAL" or "BASE" or "Offset" or "OFFSET";
        if (isSuffix)
        {
            suffix = last;
            // PERI_REG_FIELD_Sfx (4+) — Peripheral may be multi-token (HRPWM_MST / HRPWM_SLV0).
            if (parts.Length >= 4)
            {
                field = parts[^2];
                register = parts[^3];
                peripheral = string.Join('_', parts.Take(parts.Length - 3));
                return true;
            }

            // PERI_REG_Sfx (no field token)
            if (parts.Length == 3)
            {
                peripheral = parts[0];
                register = parts[1];
                return true;
            }
        }
        else if (parts.Length >= 2)
        {
            // Unsuffixed: treat last as field when 3+, else PERI_REG.
            if (parts.Length >= 3)
            {
                field = parts[^1];
                register = parts[^2];
                peripheral = string.Join('_', parts.Take(parts.Length - 2));
            }
            else
            {
                peripheral = parts[0];
                register = parts[1];
            }

            return true;
        }

        return false;
    }

    private static bool IsContiguousMask(uint value)
    {
        if (value == 0) return false;
        var v = value >> CountTrailingZeros(value);
        return (v & (v + 1)) == 0;
    }

    private static int PopCount(uint v)
    {
        var n = 0;
        while (v != 0)
        {
            n += (int)(v & 1);
            v >>= 1;
        }

        return n;
    }

    private static int CountTrailingZeros(uint v)
    {
        if (v == 0) return 32;
        var n = 0;
        while ((v & 1) == 0)
        {
            n++;
            v >>= 1;
        }

        return n;
    }

    private static bool TryParseUint(string text, out uint value)
    {
        value = 0;
        var s = text.Trim().Trim('(', ')').Trim();
        if (s.EndsWith("UL", StringComparison.OrdinalIgnoreCase)) s = s[..^2];
        else if (s.EndsWith("U", StringComparison.OrdinalIgnoreCase) || s.EndsWith("L", StringComparison.OrdinalIgnoreCase))
            s = s[..^1];
        if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            return uint.TryParse(s[2..], NumberStyles.HexNumber, CultureInfo.InvariantCulture, out value);
        return uint.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out value);
    }
}
