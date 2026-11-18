using System.Collections.Concurrent;
using System.Globalization;
using System.Text;
using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Pre-compile static checks for LL inline bodies: shift counts, Mask-as-Pos, Pos-as-Mask,
/// and register-field macro mismatches against real SDK define values.
/// </summary>
public sealed class LlShiftStaticAnalyzer
{
    private static readonly ConcurrentDictionary<string, StaticAnalysisResult> ResultCache =
        new(StringComparer.OrdinalIgnoreCase);

    private static readonly Regex ModifyRegFull = new(
        @"MODIFY_REG\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<path>[^,]+?)\s*,\s*(?<msk>[^,]+?)\s*,\s*(?<rhs>[^;]+?)\)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);


    // NOTE: Do NOT use a nested-quantifier regex for << / >> — it catastrophically
    // backtracks even on tiny bodies and freezes batch runs at "静态分析".

    private static readonly Regex Ident = new(
        @"\b(?<id>[A-Za-z_][A-Za-z0-9_]*)\b",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

    private static readonly Regex UintType = new(
        @"\b(?<t>uint(?:8|16|32|64)_t|int(?:8|16|32|64)_t|unsigned\s+long|unsigned\s+int|unsigned|long\s+long|long|int)\b",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    /// <summary>
    /// Analyze a function from live source. Does not modify SDK files.
    /// Optional <paramref name="sourceOverride"/> injects body text for regression tests
    /// (still uses real SDK macros from <paramref name="sdkRoot"/>).
    /// </summary>
    public StaticAnalysisResult Analyze(
        string? sdkRoot,
        string? sourceFile,
        string functionName,
        string? sourceOverride = null)
        => AnalyzeCore(sdkRoot, sourceFile, functionName, sourceOverride, catalogOverride: null);

    /// <summary>Same as <see cref="Analyze"/> but reuses a preloaded (usually SQLite) macro catalog.</summary>
    internal StaticAnalysisResult AnalyzeWithCatalog(
        string? sdkRoot,
        string? sourceFile,
        string functionName,
        SdkMacroSemanticCatalog? catalog,
        string? sourceOverride = null)
        => AnalyzeCore(sdkRoot, sourceFile, functionName, sourceOverride, catalog);

    private StaticAnalysisResult AnalyzeCore(
        string? sdkRoot,
        string? sourceFile,
        string functionName,
        string? sourceOverride,
        SdkMacroSemanticCatalog? catalogOverride)
    {
        if (string.IsNullOrWhiteSpace(functionName))
            return StaticAnalysisResult.Empty;

        string? cacheKey = null;
        if (!string.IsNullOrWhiteSpace(sourceFile) && File.Exists(sourceFile))
        {
            var writeUtc = File.GetLastWriteTimeUtc(sourceFile!);
            var srcTag = catalogOverride?.Source ?? sdkRoot ?? "";
            var bodyTag = string.IsNullOrWhiteSpace(sourceOverride)
                ? "file"
                : Convert.ToHexString(
                    System.Security.Cryptography.SHA256.HashData(
                        System.Text.Encoding.UTF8.GetBytes(sourceOverride)))[..12];
            // Analyzer rule version — bump when diagnostic rules change to drop stale mem cache.
            cacheKey = $"v4|{Path.GetFullPath(sourceFile!)}|{functionName}|{writeUtc.Ticks}|{srcTag}|{bodyTag}";
            if (ResultCache.TryGetValue(cacheKey, out var cached))
                return cached;
        }

        // Prefer caller-supplied catalog (SQLite RegisterMacroReferences). File parse is last resort.
        var catalog = catalogOverride ?? SdkMacroSemanticCatalog.TryLoad(sdkRoot);
        if (catalog is null)
            return StaticAnalysisResult.Empty;

        // SQLite catalog has chip Pos/Msk; still light-ingest LL_* helper #defines from the
        // current header (single-line numeric only). Skip full-file ingest of chip-sized headers.
        if (!string.IsNullOrWhiteSpace(sourceFile) && File.Exists(sourceFile))
        {
            if (string.Equals(catalog.Source, "sqlite", StringComparison.OrdinalIgnoreCase))
                catalog.IngestLlHelperDefines(sourceFile!);
            else
                catalog.IngestFile(sourceFile!);
        }

        string? body;
        string fileLabel;
        int bodyStartLine;
        if (!string.IsNullOrWhiteSpace(sourceOverride))
        {
            body = sourceOverride;
            fileLabel = sourceFile ?? "(override)";
            bodyStartLine = 1;
        }
        else
        {
            var extracted = TryExtractBody(sourceFile, functionName, out bodyStartLine);
            body = extracted;
            fileLabel = sourceFile ?? "";
        }

        if (string.IsNullOrWhiteSpace(body))
            return StaticAnalysisResult.Empty;

        var diagnostics = new List<StaticAnalysisDiagnostic>();

        // MODIFY_REG / SET_BIT / CLEAR_BIT contexts for register-field matching.
        foreach (Match mod in ModifyRegFull.Matches(body))
        {
            var mem = LeafMemberFromPath(mod.Groups["path"].Success ? mod.Groups["path"].Value : mod.Groups["mem"].Value);
            var mskExpr = mod.Groups["msk"].Value.Trim();
            var rhs = mod.Groups["rhs"].Value.Trim();
            var line = bodyStartLine + CountNewlines(body, mod.Index);
            AnalyzeMaskOperand(catalog, functionName, fileLabel, line, mem, mskExpr, "MODIFY_REG.mask", diagnostics);
            AnalyzeShiftsInExpression(catalog, functionName, fileLabel, line, rhs, mem, diagnostics);
        }

        foreach (var sc in FindSetClearBitCalls(body))
        {
            var mem = LeafMemberFromPath(sc.Path);
            var line = bodyStartLine + CountNewlines(body, sc.Index);
            AnalyzeMaskOperand(catalog, functionName, fileLabel, line, mem, sc.MaskExpr, sc.Op, diagnostics);
        }

        // Bare shifts elsewhere in the body (avoid double-counting ones already inside MODIFY_REG rhs).
        var covered = new HashSet<(int, int)>();
        foreach (Match mod in ModifyRegFull.Matches(body))
        {
            var rhsGroup = mod.Groups["rhs"];
            covered.Add((rhsGroup.Index, rhsGroup.Index + rhsGroup.Length));
        }

        foreach (var sh in FindShiftOperations(body))
        {
            var inside = covered.Any(r => sh.Index >= r.Item1 && sh.Index < r.Item2);
            if (inside) continue;
            var line = bodyStartLine + CountNewlines(body, sh.Index);
            var memCtx = InferNearbyMember(body, sh.Index);
            AnalyzeOneShift(
                catalog, functionName, fileLabel, line,
                sh.Left, sh.Op, sh.Right, memCtx, diagnostics);
        }

        // Deduplicate identical rule+expression+line
        diagnostics = diagnostics
            .GroupBy(d => $"{d.RuleId}|{d.LineNumber}|{d.Expression}|{d.RightOperand}")
            .Select(g => g.First())
            .ToList();

        var result = new StaticAnalysisResult
        {
            HasBlockingError = diagnostics.Any(d =>
                string.Equals(d.Severity, "Error", StringComparison.OrdinalIgnoreCase)),
            HasWarning = diagnostics.Any(d =>
                string.Equals(d.Severity, "Warning", StringComparison.OrdinalIgnoreCase)),
            Diagnostics = diagnostics
        };
        if (cacheKey is not null)
            ResultCache[cacheKey] = result;
        return result;
    }

    private static void AnalyzeMaskOperand(
        SdkMacroSemanticCatalog catalog,
        string functionName,
        string sourceFile,
        int line,
        string targetMember,
        string maskExpr,
        string context,
        List<StaticAnalysisDiagnostic> diagnostics)
    {
        var trimmed = maskExpr.Trim();
        // Dynamic channel/bit masks: BIT(Ch % N) / BIT(x + Pos) — intentional, not a chip field macro.
        if (trimmed.StartsWith("BIT(", StringComparison.OrdinalIgnoreCase)
            || trimmed.StartsWith("(BIT(", StringComparison.OrdinalIgnoreCase))
            return;

        var id = FirstMaskMacroIdent(maskExpr);
        if (id is null) return;

        // LL helper masks (often multi-line OR of chip _Msk bits) are intentional.
        // Example: LL_ADC_CFGR1_PREPARING_START_MSK — not present as a single #define uint.
        if (IsLlHelperMaskName(id) || IsNonFieldMacro(id))
            return;

        var info = catalog.GetOrNull(id);
        if (info is null)
        {
            // _Val used as field mask (equals low contiguous mask) is common and often absent from
            // RegisterMacroReferences (only Pos/Msk are stored).
            if (id.EndsWith("_Val", StringComparison.OrdinalIgnoreCase)
                || id.EndsWith("_VAL", StringComparison.OrdinalIgnoreCase))
                return;

            diagnostics.Add(Make(
                "UnknownMaskOperand", "Warning", functionName, sourceFile, line,
                maskExpr, context, targetMember, id,
                null, "bit-field mask", "unresolved macro",
                $"无法解析掩码宏 {id} 的数值定义。",
                "确认寄存器解析已导入该宏，或使用 chip 头中的 _Msk。"));
            return;
        }

        if (info.Kind == SdkMacroSemanticKind.BitFieldPosition)
        {
            diagnostics.Add(Make(
                "PositionUsedAsMask", "Warning", functionName, sourceFile, line,
                maskExpr, context, targetMember, id,
                FormatValue(info), "bit-field mask", "bit-field position",
                $"将位置宏 {id}(= {FormatValue(info)}) 用作掩码操作数。",
                SuggestMaskFor(info)));
        }

        if (!string.IsNullOrWhiteSpace(info.RegisterHint)
            && !RegisterHintsMatch(targetMember, info.RegisterHint, id))
        {
            diagnostics.Add(Make(
                "RegisterFieldMismatch", "Error", functionName, sourceFile, line,
                maskExpr, context, targetMember, id,
                FormatValue(info), $"register {targetMember}", $"register {info.RegisterHint}",
                $"目标寄存器为 {targetMember}，但宏 {id} 归属寄存器 {info.RegisterHint}" +
                (string.IsNullOrWhiteSpace(info.FieldHint) ? "" : $" 字段 {info.FieldHint}") + "。",
                SuggestMatchingMacro(targetMember, info)));
        }
    }

    private readonly record struct SetClearHit(int Index, string Op, string Path, string MaskExpr);

    /// <summary>Parse SET_BIT/CLEAR_BIT with nested parentheses in the mask (e.g. BIT(Ch % N)).</summary>
    private static List<SetClearHit> FindSetClearBitCalls(string body)
    {
        var hits = new List<SetClearHit>();
        for (var i = 0; i < body.Length; i++)
        {
            if (!TryMatchKeywordAt(body, i, "SET_BIT", out var opLen)
                && !TryMatchKeywordAt(body, i, "CLEAR_BIT", out opLen))
                continue;
            var op = body.Substring(i, opLen);
            var p = i + opLen;
            while (p < body.Length && char.IsWhiteSpace(body[p])) p++;
            if (p >= body.Length || body[p] != '(') continue;
            var close = FindMatchingParen(body, p);
            if (close < 0) continue;
            var inner = body[(p + 1)..close];
            var arrow = inner.IndexOf("->", StringComparison.Ordinal);
            if (arrow < 0) continue;
            var comma = IndexOfTopLevelComma(inner, arrow + 2);
            if (comma < 0) continue;
            var path = inner[(arrow + 2)..comma].Trim();
            var mask = inner[(comma + 1)..].Trim();
            hits.Add(new SetClearHit(i, op, path, mask));
            i = close;
        }
        return hits;
    }

    private static bool TryMatchKeywordAt(string text, int index, string keyword, out int length)
    {
        length = 0;
        if (index + keyword.Length > text.Length) return false;
        if (!text.AsSpan(index, keyword.Length).Equals(keyword, StringComparison.OrdinalIgnoreCase))
            return false;
        if (index > 0 && (char.IsLetterOrDigit(text[index - 1]) || text[index - 1] == '_'))
            return false;
        var after = index + keyword.Length;
        if (after < text.Length && (char.IsLetterOrDigit(text[after]) || text[after] == '_'))
            return false;
        length = keyword.Length;
        return true;
    }

    private static int FindMatchingParen(string text, int openIndex)
    {
        var depth = 0;
        for (var i = openIndex; i < text.Length; i++)
        {
            if (text[i] == '(') depth++;
            else if (text[i] == ')')
            {
                depth--;
                if (depth == 0) return i;
            }
        }
        return -1;
    }

    private static int IndexOfTopLevelComma(string text, int start)
    {
        var depth = 0;
        for (var i = start; i < text.Length; i++)
        {
            var ch = text[i];
            if (ch == '(') depth++;
            else if (ch == ')') depth = Math.Max(0, depth - 1);
            else if (ch == ',' && depth == 0) return i;
        }
        return -1;
    }

    /// <summary>LL layer helper mask names, e.g. <c>LL_ADC_CFGR1_PREPARING_START_MSK</c>.</summary>
    internal static bool IsLlHelperMaskName(string id)
    {
        if (string.IsNullOrWhiteSpace(id) || !id.StartsWith("LL_", StringComparison.OrdinalIgnoreCase))
            return false;
        return id.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase)
               || id.EndsWith("_MASK", StringComparison.OrdinalIgnoreCase)
               || id.EndsWith("_BIT", StringComparison.OrdinalIgnoreCase);
    }

    /// <summary>
    /// Match leaf register member to macro RegisterHint (CFGR1 vs ADC0_CFGR1-style leftovers).
    /// Also accepts macros whose name embeds <c>_{member}_</c> when name-split RegisterHint
    /// is wrong for multi-token fields (e.g. CAN0_BITTIME_S_SJW_Msk → hint "S", member BITTIME).
    /// </summary>
    internal static bool RegisterHintsMatch(
        string targetMember, string registerHint, string? macroName = null)
    {
        if (string.IsNullOrWhiteSpace(targetMember) || string.IsNullOrWhiteSpace(registerHint))
            return true; // cannot prove mismatch
        if (string.Equals(targetMember, registerHint, StringComparison.OrdinalIgnoreCase))
            return true;
        // Hint sometimes keeps instance prefix: ADC0_CFGR1 vs CFGR1
        if (registerHint.EndsWith("_" + targetMember, StringComparison.OrdinalIgnoreCase))
            return true;
        if (targetMember.EndsWith("_" + registerHint, StringComparison.OrdinalIgnoreCase))
            return true;
        // Embedded register token in macro name beats a bad split RegisterHint.
        if (!string.IsNullOrWhiteSpace(macroName)
            && macroName.Contains("_" + targetMember + "_", StringComparison.OrdinalIgnoreCase))
            return true;
        return false;
    }

    private static void AnalyzeShiftsInExpression(
        SdkMacroSemanticCatalog catalog,
        string functionName,
        string sourceFile,
        int line,
        string expression,
        string? targetMember,
        List<StaticAnalysisDiagnostic> diagnostics)
    {
        foreach (var sh in FindShiftOperations(expression))
        {
            AnalyzeOneShift(
                catalog, functionName, sourceFile, line,
                sh.Left, sh.Op, sh.Right, targetMember, diagnostics);
        }
    }

    private readonly record struct ShiftHit(int Index, string Left, string Op, string Right);

    /// <summary>
    /// Linear scan for <c>&lt;&lt;</c> / <c>&gt;&gt;</c>. Avoids Regex catastrophic backtracking.
    /// </summary>
    private static List<ShiftHit> FindShiftOperations(string text)
    {
        var hits = new List<ShiftHit>();
        if (string.IsNullOrEmpty(text)) return hits;
        for (var i = 0; i < text.Length - 1; i++)
        {
            var c0 = text[i];
            var c1 = text[i + 1];
            if (!((c0 == '<' && c1 == '<') || (c0 == '>' && c1 == '>')))
                continue;
            var op = text.Substring(i, 2);
            var left = TakeOperandLeft(text, i);
            var right = TakeOperandRight(text, i + 2);
            if (left.Length == 0 || right.Length == 0)
                continue;
            hits.Add(new ShiftHit(i, left, op, right));
            i++; // skip second char of operator
        }
        return hits;
    }

    private static string TakeOperandLeft(string text, int opIndex)
    {
        var end = opIndex;
        while (end > 0 && char.IsWhiteSpace(text[end - 1])) end--;
        if (end == 0) return "";
        var start = end - 1;
        var depth = 0;
        for (; start >= 0; start--)
        {
            var ch = text[start];
            if (ch == ')') { depth++; continue; }
            if (ch == '(')
            {
                depth--;
                if (depth < 0) { start++; break; }
                continue;
            }
            if (depth > 0) continue;
            if (char.IsLetterOrDigit(ch) || ch == '_') continue;
            if (char.IsWhiteSpace(ch)) continue;
            start++;
            break;
        }
        if (start < 0) start = 0;
        return text[start..end].Trim();
    }

    private static string TakeOperandRight(string text, int afterOp)
    {
        var start = afterOp;
        while (start < text.Length && char.IsWhiteSpace(text[start])) start++;
        if (start >= text.Length) return "";
        var end = start;
        var depth = 0;
        for (; end < text.Length; end++)
        {
            var ch = text[end];
            if (ch == '(') { depth++; continue; }
            if (ch == ')')
            {
                if (depth == 0) break;
                depth--;
                continue;
            }
            if (depth > 0) continue;
            if (char.IsLetterOrDigit(ch) || ch == '_') continue;
            if (char.IsWhiteSpace(ch)) continue;
            break;
        }
        return text[start..end].Trim();
    }

    private static void AnalyzeOneShift(
        SdkMacroSemanticCatalog catalog,
        string functionName,
        string sourceFile,
        int line,
        string left,
        string op,
        string right,
        string? targetMember,
        List<StaticAnalysisDiagnostic> diagnostics)
    {
        var expr = $"{left} {op} {right}";
        var leftWidth = InferLeftOperandBitWidth(left);
        var rightId = FirstMacroIdent(right);
        uint? shiftCount = null;
        SdkMacroSemanticInfo? rightInfo = null;
        string? actualType = null;

        // Channel/count helpers inside arithmetic shifts: (Channel - LL_xxx_CH_0N) % 4 * 4
        if (rightId is not null && IsNonFieldMacro(rightId))
            return;

        if (rightId is not null && catalog.TryGet(rightId, out var info))
        {
            rightInfo = info;
            shiftCount = info.NumericValue;
            actualType = info.Kind.ToString();
        }
        else if (TryParseUintLiteral(right, out var lit))
        {
            shiftCount = lit;
            actualType = "integer-literal";
        }
        else if (rightId is not null)
        {
            diagnostics.Add(Make(
                "UnknownShiftOperand", "Warning", functionName, sourceFile, line,
                expr, op, left, right,
                null, $"shift count 0..{leftWidth - 1}", "unresolved",
                $"无法解析移位量操作数 {right}。",
                "使用已定义的 _Pos 宏或字面移位量。"));
            return;
        }
        else
        {
            // Variable / arithmetic shift amount — cannot prove UB statically.
            return;
        }

        // Only flag mask-as-position when the *immediate* right operand is a mask macro,
        // not when a _Msk is on the left being shifted by a computed channel stride.
        if (rightInfo is not null
            && rightInfo.Kind == SdkMacroSemanticKind.BitFieldMask
            && string.Equals(right.Trim(), rightId, StringComparison.OrdinalIgnoreCase))
        {
            diagnostics.Add(Make(
                "MaskUsedAsShiftPosition", "Error", functionName, sourceFile, line,
                expr, op, left, right,
                FormatValue(rightInfo), "bit-field position", "bit-field mask",
                $"将位域掩码 {rightId}(= {FormatValue(rightInfo)}) 误用为移位位置。",
                SuggestPosFor(rightInfo)));
        }

        if (rightInfo is not null
            && !string.IsNullOrWhiteSpace(targetMember)
            && !string.IsNullOrWhiteSpace(rightInfo.RegisterHint)
            && !RegisterHintsMatch(targetMember, rightInfo.RegisterHint, rightId)
            && string.Equals(right.Trim(), rightId, StringComparison.OrdinalIgnoreCase))
        {
            diagnostics.Add(Make(
                "RegisterFieldMismatch", "Error", functionName, sourceFile, line,
                expr, op, left, right,
                FormatValue(rightInfo), $"register {targetMember}", $"register {rightInfo.RegisterHint}",
                $"移位宏 {rightId} 归属寄存器 {rightInfo.RegisterHint}，与当前目标 {targetMember} 不一致。",
                SuggestPosForMember(targetMember, rightInfo)));
        }

        if (shiftCount is uint sc && sc >= leftWidth)
        {
            diagnostics.Add(Make(
                "InvalidShiftCount", "Error", functionName, sourceFile, line,
                expr, op, left, right,
                shiftCount is null ? null : $"0x{sc:X} ({sc})",
                $"shift count 0..{leftWidth - 1} for {leftWidth}-bit left operand",
                actualType ?? "numeric",
                $"移位量 {sc} 超出 {leftWidth} 位整数允许范围 0~{leftWidth - 1}，属于 C 语言未定义行为风险。",
                rightInfo?.Kind == SdkMacroSemanticKind.BitFieldMask
                    ? SuggestPosFor(rightInfo)
                    : $"使用合法位置宏（0~{leftWidth - 1}）。"));
        }
    }

    private static int InferLeftOperandBitWidth(string left)
    {
        var m = UintType.Match(left);
        if (m.Success)
        {
            var t = m.Groups["t"].Value.ToLowerInvariant().Replace(" ", "");
            if (t.Contains("64")) return 64;
            if (t.Contains("16")) return 16;
            if (t.Contains("8")) return 8;
            if (t.Contains("32")) return 32;
        }

        // LL field writes typically promote to unsigned int / uint32_t after integer promotions.
        return 32;
    }

    private static string? FirstMacroIdent(string expr)
    {
        foreach (Match m in Ident.Matches(expr))
        {
            var id = m.Groups["id"].Value;
            if (IsNoiseIdent(id)) continue;
            if (id.Contains('_', StringComparison.Ordinal))
                return id;
        }

        return null;
    }

    /// <summary>Prefer field macros (_Msk/_Pos/_Val) over count helpers (_NUMS) inside mask expressions.</summary>
    private static string? FirstMaskMacroIdent(string expr)
    {
        string? fallback = null;
        foreach (Match m in Ident.Matches(expr))
        {
            var id = m.Groups["id"].Value;
            if (IsNoiseIdent(id) || IsNonFieldMacro(id)) continue;
            if (!id.Contains('_', StringComparison.Ordinal)) continue;
            if (id.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
                || id.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase)
                || id.EndsWith("_Pos", StringComparison.OrdinalIgnoreCase)
                || id.EndsWith("_Val", StringComparison.OrdinalIgnoreCase)
                || id.EndsWith("_VAL", StringComparison.OrdinalIgnoreCase))
                return id;
            fallback ??= id;
        }

        return fallback;
    }

    private static bool IsNoiseIdent(string id)
        => id is "UL" or "U" or "L" or "uint32_t" or "uint16_t" or "uint8_t" or "uint64_t"
            or "BIT" or "SET_BIT" or "CLEAR_BIT" or "MODIFY_REG" or "READ_BIT" or "WRITE_REG";

    /// <summary>Count/slot/channel-index helpers — not chip bit-field macros.</summary>
    internal static bool IsNonFieldMacro(string id)
    {
        if (string.IsNullOrWhiteSpace(id)) return false;
        if (id.EndsWith("_NUMS", StringComparison.OrdinalIgnoreCase)) return true;
        if (id.EndsWith("_NUM", StringComparison.OrdinalIgnoreCase)) return true;
        // LL_ADTMR_CAP_CMP_CH_0N / LL_ADC_CH_... style enumerators used in % / - arithmetic.
        if (id.StartsWith("LL_", StringComparison.OrdinalIgnoreCase)
            && id.Contains("_CH_", StringComparison.OrdinalIgnoreCase))
            return true;
        return false;
    }

    private static string? InferNearbyMember(string body, int index)
    {
        var before = body[..Math.Min(index, body.Length)];
        var arrowIdx = before.LastIndexOf("->", StringComparison.Ordinal);
        if (arrowIdx < 0) return null;
        var start = arrowIdx + 2;
        while (start < before.Length && char.IsWhiteSpace(before[start])) start++;
        var end = start;
        while (end < before.Length)
        {
            var ch = before[end];
            if (char.IsLetterOrDigit(ch) || ch is '_' or '.' or '[' or ']')
            {
                end++;
                continue;
            }
            if (char.IsWhiteSpace(ch))
            {
                end++;
                continue;
            }
            break;
        }

        // DMAx->CH[i].REG.CTR / HRPWMx->Master.MCR1 → leaf register member.
        return LeafMemberFromPath(before[start..end]);
    }

    /// <summary>Flat MEM or nested/array path → leaf register member (e.g. PWM[i].REG.PWMCR0 → PWMCR0).</summary>
    private static string LeafMemberFromPath(string? path)
    {
        if (string.IsNullOrWhiteSpace(path)) return "";
        var p = path.Trim();
        var ids = Regex.Matches(p, @"[A-Za-z_][A-Za-z0-9_]*");
        return ids.Count == 0 ? p : ids[^1].Value;
    }

    private static string? SuggestPosFor(SdkMacroSemanticInfo mask)
    {
        if (mask.Name.EndsWith("_Msk", StringComparison.OrdinalIgnoreCase)
            || mask.Name.EndsWith("_MSK", StringComparison.OrdinalIgnoreCase))
            return $"使用 {mask.Name[..^4]}_Pos。";
        if (!string.IsNullOrWhiteSpace(mask.PeripheralHint)
            && !string.IsNullOrWhiteSpace(mask.RegisterHint)
            && !string.IsNullOrWhiteSpace(mask.FieldHint))
            return $"使用 {mask.PeripheralHint}_{mask.RegisterHint}_{mask.FieldHint}_Pos。";
        return "使用对应字段的 _Pos 宏。";
    }

    private static string? SuggestMaskFor(SdkMacroSemanticInfo pos)
    {
        if (pos.Name.EndsWith("_Pos", StringComparison.OrdinalIgnoreCase))
            return $"使用 {pos.Name[..^4]}_Msk。";
        return "使用对应字段的 _Msk 宏。";
    }

    private static string? SuggestMatchingMacro(string targetMember, SdkMacroSemanticInfo info)
    {
        if (!string.IsNullOrWhiteSpace(info.PeripheralHint) && !string.IsNullOrWhiteSpace(info.FieldHint))
            return $"改用 {info.PeripheralHint}_{targetMember}_{info.FieldHint}_Msk（或正确字段宏）。";
        return $"改用归属寄存器 {targetMember} 的字段宏。";
    }

    private static string? SuggestPosForMember(string targetMember, SdkMacroSemanticInfo info)
    {
        if (!string.IsNullOrWhiteSpace(info.PeripheralHint) && !string.IsNullOrWhiteSpace(info.FieldHint))
            return $"改用 {info.PeripheralHint}_{targetMember}_*_Pos（匹配当前寄存器）。";
        return $"改用归属寄存器 {targetMember} 的 _Pos 宏。";
    }

    private static string? FormatValue(SdkMacroSemanticInfo info)
        => info.NumericValue is uint v ? $"0x{v:X} ({v})" : info.Expansion;

    private static StaticAnalysisDiagnostic Make(
        string ruleId, string severity, string functionName, string sourceFile, int line,
        string expression, string op, string left, string right,
        string? resolved, string? expected, string? actual,
        string description, string? fix)
        => new()
        {
            RuleId = ruleId,
            Severity = severity,
            FunctionName = functionName,
            SourceFile = Path.GetFileName(sourceFile),
            LineNumber = line,
            Expression = Compact(expression),
            Operator = op,
            LeftOperand = Compact(left),
            RightOperand = Compact(right),
            ResolvedMacroValue = resolved,
            ExpectedOperandType = expected,
            ActualOperandType = actual,
            Description = description,
            SuggestedFix = fix
        };

    private static string Compact(string s)
        => Regex.Replace(s, @"\s+", " ").Trim();

    private static int CountNewlines(string text, int index)
    {
        var n = 0;
        var lim = Math.Min(index, text.Length);
        for (var i = 0; i < lim; i++)
            if (text[i] == '\n') n++;
        return n;
    }

    private static bool TryParseUintLiteral(string text, out uint value)
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

    private static string? TryExtractBody(string? filePath, string functionName, out int startLine)
    {
        startLine = 1;
        try
        {
            if (string.IsNullOrWhiteSpace(filePath) || !File.Exists(filePath))
                return null;
            var text = File.ReadAllText(filePath);
            var fnIdx = text.IndexOf(functionName + "(", StringComparison.Ordinal);
            if (fnIdx < 0) return null;
            startLine = 1;
            for (var i = 0; i < fnIdx; i++)
                if (text[i] == '\n') startLine++;
            var brace = text.IndexOf('{', fnIdx);
            if (brace < 0) return null;
            var depth = 0;
            for (var i = brace; i < text.Length; i++)
            {
                if (text[i] == '{') depth++;
                else if (text[i] == '}')
                {
                    depth--;
                    if (depth == 0)
                        return text.Substring(brace, i - brace + 1);
                }
            }
        }
        catch
        {
            /* ignore */
        }

        return null;
    }

    public static string FormatReport(string functionName, StaticAnalysisResult result)
    {
        if (result.Diagnostics.Count == 0)
            return $"函数：{functionName}\n\n<Static Analysis: Passed>\n";

        var sb = new StringBuilder();
        sb.AppendLine($"函数：{functionName}");
        sb.AppendLine();
        sb.AppendLine(result.HasBlockingError
            ? "<Static Analysis: Failed>"
            : "<Static Analysis: Warning>");
        sb.AppendLine();
        foreach (var d in result.Diagnostics)
        {
            sb.AppendLine($"规则：{d.RuleId} ({d.Severity})");
            sb.AppendLine($"位置：{d.SourceFile}" + (d.LineNumber > 0 ? $":{d.LineNumber}" : ""));
            sb.AppendLine();
            sb.AppendLine("表达式：");
            sb.AppendLine(d.Expression);
            sb.AppendLine();
            if (!string.IsNullOrWhiteSpace(d.ResolvedMacroValue))
            {
                sb.AppendLine("宏解析：");
                sb.AppendLine($"{d.RightOperand} = {d.ResolvedMacroValue}");
            }

            if (!string.IsNullOrWhiteSpace(d.ExpectedOperandType) || !string.IsNullOrWhiteSpace(d.ActualOperandType))
            {
                sb.AppendLine($"预期操作数类型：{d.ExpectedOperandType ?? "—"}");
                sb.AppendLine($"实际操作数类型：{d.ActualOperandType ?? "—"}");
            }

            sb.AppendLine();
            sb.AppendLine("问题：");
            sb.AppendLine(d.Description);
            if (!string.IsNullOrWhiteSpace(d.SuggestedFix))
            {
                sb.AppendLine();
                sb.AppendLine("建议：");
                sb.AppendLine(d.SuggestedFix);
            }

            sb.AppendLine();
            sb.AppendLine("---");
            sb.AppendLine();
        }

        return sb.ToString();
    }
}
