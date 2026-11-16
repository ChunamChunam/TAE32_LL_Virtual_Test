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
    private static readonly Regex ModifyRegFull = new(
        @"MODIFY_REG\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[^,]+?)\s*,\s*(?<rhs>[^;]+?)\)\s*;",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase | RegexOptions.Singleline);

    private static readonly Regex SetClearBit = new(
        @"\b(?<op>SET_BIT|CLEAR_BIT)\s*\(\s*(?<inst>[A-Za-z0-9_]+)\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[^)]+?)\)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant | RegexOptions.IgnoreCase);

    private static readonly Regex ShiftExpr = new(
        @"(?<left>(?:\([^()]*\)|[A-Za-z0-9_]+(?:\s*\([^()]*\))?|\([^()]+\))+)\s*(?<op><<|>>)\s*(?<right>(?:\([^()]*\)|[A-Za-z0-9_]+)+)",
        RegexOptions.Compiled | RegexOptions.CultureInvariant);

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
    {
        if (string.IsNullOrWhiteSpace(functionName))
            return StaticAnalysisResult.Empty;

        var catalog = SdkMacroSemanticCatalog.TryLoad(sdkRoot);
        if (catalog is null)
            return StaticAnalysisResult.Empty;

        if (!string.IsNullOrWhiteSpace(sourceFile) && File.Exists(sourceFile))
            catalog.IngestFile(sourceFile!);

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
            var mem = mod.Groups["mem"].Value.Trim();
            var mskExpr = mod.Groups["msk"].Value.Trim();
            var rhs = mod.Groups["rhs"].Value.Trim();
            var line = bodyStartLine + CountNewlines(body, mod.Index);
            AnalyzeMaskOperand(catalog, functionName, fileLabel, line, mem, mskExpr, "MODIFY_REG.mask", diagnostics);
            AnalyzeShiftsInExpression(catalog, functionName, fileLabel, line, rhs, mem, diagnostics);
        }

        foreach (Match sc in SetClearBit.Matches(body))
        {
            var mem = sc.Groups["mem"].Value.Trim();
            var mskExpr = sc.Groups["msk"].Value.Trim();
            var line = bodyStartLine + CountNewlines(body, sc.Index);
            AnalyzeMaskOperand(catalog, functionName, fileLabel, line, mem, mskExpr, sc.Groups["op"].Value, diagnostics);
        }

        // Bare shifts elsewhere in the body (avoid double-counting ones already inside MODIFY_REG rhs by index overlap).
        var covered = new HashSet<(int, int)>();
        foreach (Match mod in ModifyRegFull.Matches(body))
        {
            var rhsGroup = mod.Groups["rhs"];
            covered.Add((rhsGroup.Index, rhsGroup.Index + rhsGroup.Length));
        }

        foreach (Match sh in ShiftExpr.Matches(body))
        {
            var inside = covered.Any(r => sh.Index >= r.Item1 && sh.Index < r.Item2);
            if (inside) continue;
            var line = bodyStartLine + CountNewlines(body, sh.Index);
            var memCtx = InferNearbyMember(body, sh.Index);
            AnalyzeOneShift(
                catalog, functionName, fileLabel, line,
                sh.Groups["left"].Value.Trim(),
                sh.Groups["op"].Value,
                sh.Groups["right"].Value.Trim(),
                memCtx,
                diagnostics);
        }

        // Deduplicate identical rule+expression+line
        diagnostics = diagnostics
            .GroupBy(d => $"{d.RuleId}|{d.LineNumber}|{d.Expression}|{d.RightOperand}")
            .Select(g => g.First())
            .ToList();

        return new StaticAnalysisResult
        {
            HasBlockingError = diagnostics.Any(d =>
                string.Equals(d.Severity, "Error", StringComparison.OrdinalIgnoreCase)),
            HasWarning = diagnostics.Any(d =>
                string.Equals(d.Severity, "Warning", StringComparison.OrdinalIgnoreCase)),
            Diagnostics = diagnostics
        };
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
        var id = FirstMacroIdent(maskExpr);
        if (id is null) return;
        var info = catalog.GetOrNull(id);
        if (info is null)
        {
            diagnostics.Add(Make(
                "UnknownShiftOperand", "Warning", functionName, sourceFile, line,
                maskExpr, context, targetMember, id,
                null, "bit-field mask", "unresolved macro",
                $"无法解析宏 {id} 的数值定义。",
                "确认 chip.h / 设备头中存在该宏。"));
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
            && !string.Equals(info.RegisterHint, targetMember, StringComparison.OrdinalIgnoreCase))
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

    private static void AnalyzeShiftsInExpression(
        SdkMacroSemanticCatalog catalog,
        string functionName,
        string sourceFile,
        int line,
        string expression,
        string? targetMember,
        List<StaticAnalysisDiagnostic> diagnostics)
    {
        foreach (Match sh in ShiftExpr.Matches(expression))
        {
            AnalyzeOneShift(
                catalog, functionName, sourceFile, line,
                sh.Groups["left"].Value.Trim(),
                sh.Groups["op"].Value,
                sh.Groups["right"].Value.Trim(),
                targetMember,
                diagnostics);
        }
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
            // Variable shift amount — cannot prove UB statically.
            return;
        }

        if (rightInfo is not null && rightInfo.Kind == SdkMacroSemanticKind.BitFieldMask)
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
            && !string.Equals(rightInfo.RegisterHint, targetMember, StringComparison.OrdinalIgnoreCase))
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
            if (id is "UL" or "U" or "L" or "uint32_t" or "uint16_t" or "uint8_t" or "uint64_t")
                continue;
            if (id.Contains('_', StringComparison.Ordinal))
                return id;
        }

        return null;
    }

    private static string? InferNearbyMember(string body, int index)
    {
        var before = body[..Math.Min(index, body.Length)];
        var arrow = Regex.Matches(before, @"->\s*(?<mem>[A-Za-z0-9_]+)");
        if (arrow.Count == 0) return null;
        return arrow[^1].Groups["mem"].Value;
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
