using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text.RegularExpressions;
using Microsoft.Extensions.Logging;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Core.Sdk;

namespace TAE32.LLVirtualTest.SDK.Scan;

/// <summary>
/// C# port of Phase-1 LL directory scan. Reads real headers and emits import-compatible JSON.
/// </summary>
public sealed class LlSdkScanService : ISdkScanService
{
    private static readonly Regex ReInclude = new(@"^\s*#\s*include\s+[<\""]([^>\""]+)[>\""]", RegexOptions.Multiline | RegexOptions.Compiled);
    private static readonly Regex ReBriefHeader = new(@"@brief\s+Header file (?:of|for)\s+(.+?)\s+LL\s+module", RegexOptions.IgnoreCase | RegexOptions.Compiled);
    private static readonly Regex ReDefgroup = new(@"@defgroup\s+(\S+)\s+([^\r\n*]+)", RegexOptions.Compiled);
    private static readonly Regex ReAddtogroup = new(@"@addtogroup\s+(\S+)", RegexOptions.Compiled);
    private static readonly Regex ReGuard = new(@"#\s*ifndef\s+(_TAE32[A-Za-z0-9_]+_H_)", RegexOptions.Compiled);
    private static readonly Regex ReVersionMacro = new(@"#\s*define\s+(__TAE32[A-Za-z0-9_]*VERSION[A-Za-z0-9_]*)", RegexOptions.Compiled);
    private static readonly Regex ReIfdefMultiline = new(
        @"#\s*if\s*\(?\s*((?:defined\s*\(\s*[A-Za-z_][A-Za-z0-9_]*\s*\)\s*(?:\|\|\s*)?(?:\\\s*\r?\n\s*)?)+)\)?",
        RegexOptions.Multiline | RegexOptions.Compiled);
    private static readonly Regex ReDefinedToken = new(@"defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)", RegexOptions.Compiled);
    private static readonly Regex ReTypeDef = new(@"\b([A-Za-z_][A-Za-z0-9_]*)_TypeDef\b", RegexOptions.Compiled);
    private static readonly Regex ReSimpleFunc = new(
        @"^(?<prefix>\s*(?:__STATIC_INLINE|static\s+inline|inline)\s+)(?<ret>.+?)\s+(?<name>[A-Za-z_][A-Za-z0-9_]*)\s*\(",
        RegexOptions.Multiline | RegexOptions.Compiled);
    private static readonly Regex ReOrdinaryDecl = new(
        @"^(?<ret>(?:(?:const|volatile|unsigned|signed|struct|enum)\s+)*[A-Za-z_][A-Za-z0-9_]*(?:\s*\*+)?(?:\s+[A-Za-z_][A-Za-z0-9_]*(?:\s*\*+)?)*)\s+(?<name>LL_[A-Za-z0-9_]+)\s*\((?<params>[^;{]*)\)\s*;",
        RegexOptions.Multiline | RegexOptions.Compiled);
    private static readonly Regex ReMacroFunc = new(
        @"#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)\s*(.*)$",
        RegexOptions.Multiline | RegexOptions.Compiled);
    private static readonly Regex ReFileModule = new(@"tae32[a-z0-9]+_ll_([a-z0-9]+)\.h$", RegexOptions.IgnoreCase | RegexOptions.Compiled);

    private static readonly JsonSerializerOptions JsonOpts = new()
    {
        WriteIndented = true,
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
        Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping
    };

    private readonly ILogger<LlSdkScanService> _logger;

    public LlSdkScanService(ILogger<LlSdkScanService> logger) => _logger = logger;

    public async Task<SdkScanResult> ScanAsync(string sdkRootPath, string outputDirectory, CancellationToken cancellationToken = default)
    {
        var errors = new List<string>();
        if (string.IsNullOrWhiteSpace(sdkRootPath) || !Directory.Exists(sdkRootPath))
            return Fail($"SDK 路径不存在: {sdkRootPath}");

        var packageRoot = ResolvePackageRoot(Path.GetFullPath(sdkRootPath));
        var llRoot = ResolveLlRoot(packageRoot);
        if (llRoot is null)
            return Fail($"在 {packageRoot} 下未找到 LL 目录或 .h 文件。");

        Directory.CreateDirectory(outputDirectory);
        outputDirectory = Path.GetFullPath(outputDirectory);

        var files = Directory.EnumerateFiles(llRoot, "*.*", SearchOption.AllDirectories)
            .OrderBy(f => f, StringComparer.OrdinalIgnoreCase)
            .ToList();
        var hFiles = files.Where(f => f.EndsWith(".h", StringComparison.OrdinalIgnoreCase)).ToList();
        if (hFiles.Count == 0)
            return Fail($"LL 目录无头文件: {llRoot}");

        var fileDatas = new List<FileData>();
        foreach (var path in hFiles)
        {
            cancellationToken.ThrowIfCancellationRequested();
            var text = await ReadTextAsync(path, cancellationToken);
            var rel = ToRel(packageRoot, path);
            fileDatas.Add(new FileData(path, rel, Path.GetFileName(path), text));
        }

        var chipModel = DiscoverChip(fileDatas) ?? "UNKNOWN";
        var peripherals = DiscoverPeripherals(fileDatas, chipModel);
        var functions = ExtractFunctions(fileDatas, chipModel, peripherals, cancellationToken);

        var generated = new List<string>();
        var now = DateTime.UtcNow.ToString("yyyy-MM-ddTHH:mm:ssZ");

        var chipDoc = new Dictionary<string, object?>
        {
            ["generated_at"] = now,
            ["discovery_policy"] = "仅依据 LL 目录内源码证据；不以 SDK 包名单独推断全部芯片型号",
            ["chips"] = new[]
            {
                new Dictionary<string, object?>
                {
                    ["chip_model"] = chipModel,
                    ["related_files"] = fileDatas.Select(f => f.RelPath).ToList(),
                    ["detection_status"] = "自动识别",
                    ["confidence"] = "高",
                    ["notes"] = "由应用内 LL 扫描器根据源码证据识别。"
                }
            },
            ["chip_count"] = 1
        };
        var chipPath = Path.Combine(outputDirectory, "03_ChipDiscovery.json");
        await File.WriteAllTextAsync(chipPath, JsonSerializer.Serialize(chipDoc, JsonOpts), Encoding.UTF8, cancellationToken);
        generated.Add(chipPath);

        var periList = peripherals.Select((p, i) => new Dictionary<string, object?>
        {
            ["序号"] = i + 1,
            ["外设名称"] = p.Name,
            ["相关文件"] = p.RelatedFiles,
            ["LL函数数量"] = functions.Count(f => f.Peripheral == p.Name && f.Form == "inline_definition"),
            ["LL函数数量_全形式"] = functions.Count(f => f.Peripheral == p.Name),
            ["LL函数数量明细"] = new Dictionary<string, int>
            {
                ["inline_definition"] = functions.Count(f => f.Peripheral == p.Name && f.Form == "inline_definition"),
                ["function_macro"] = functions.Count(f => f.Peripheral == p.Name && f.Form == "function_macro"),
                ["declaration"] = functions.Count(f => f.Peripheral == p.Name && f.Form == "declaration")
            },
            ["外设实例"] = p.Instances,
            ["TypeDef"] = p.Typedefs.Select(t => t.EndsWith("_TypeDef", StringComparison.Ordinal) ? t : t + "_TypeDef").ToList(),
            ["置信度"] = p.Confidence,
            ["识别状态"] = p.Status,
            ["所属芯片"] = chipModel,
            ["notes"] = p.Notes,
            ["is_common_driver"] = false
        }).ToList();

        var periDoc = new Dictionary<string, object?>
        {
            ["generated_at"] = now,
            ["discovery_policy"] = "综合 @brief/@defgroup/实例宏/TypeDef/LL_ 前缀/文件名；禁止仅用文件名定论",
            ["peripheral_count"] = periList.Count,
            ["peripherals"] = periList
        };
        var periPath = Path.Combine(outputDirectory, "04_PeripheralDiscovery.json");
        await File.WriteAllTextAsync(periPath, JsonSerializer.Serialize(periDoc, JsonOpts), Encoding.UTF8, cancellationToken);
        generated.Add(periPath);

        var inlineCount = functions.Count(f => f.Form == "inline_definition");
        var funcDoc = new Dictionary<string, object?>
        {
            ["generated_at"] = now,
            ["extraction_policy"] = "提取 __STATIC_INLINE / static inline / inline / 普通声明 / 函数宏；区分声明与定义",
            ["function_count_total"] = functions.Count,
            ["function_count_inline_definition"] = inlineCount,
            ["function_count_macro_function"] = functions.Count(f => f.Form == "function_macro"),
            ["function_count_declaration"] = functions.Count(f => f.Form == "declaration"),
            ["functions"] = functions.Select(f => new Dictionary<string, object?>
            {
                ["FunctionName"] = f.Name,
                ["ReturnType"] = f.ReturnType,
                ["Parameters"] = f.Parameters,
                ["FunctionType"] = f.FunctionType,
                ["Form"] = f.Form,
                ["Peripheral"] = f.Peripheral,
                ["Chip"] = f.Chip,
                ["FilePath"] = f.FilePath,
                ["StartLine"] = f.StartLine,
                ["EndLine"] = f.EndLine,
                ["DetectionStatus"] = f.Status
            }).ToList()
        };
        var funcPath = Path.Combine(outputDirectory, "05_LLFunctionDiscovery.json");
        await File.WriteAllTextAsync(funcPath, JsonSerializer.Serialize(funcDoc, JsonOpts), Encoding.UTF8, cancellationToken);
        generated.Add(funcPath);

        // Lightweight summary for UI verification
        var summaryPath = Path.Combine(outputDirectory, "07_ScanSummary.md");
        var summary = new StringBuilder();
        summary.AppendLine("# SDK 扫描摘要（应用内自动生成）");
        summary.AppendLine();
        summary.AppendLine($"- 生成时间: {now}");
        summary.AppendLine($"- SDK: `{packageRoot}`");
        summary.AppendLine($"- LL: `{llRoot}`");
        summary.AppendLine($"- 芯片: **{chipModel}**");
        summary.AppendLine($"- 外设: **{periList.Count}**");
        summary.AppendLine($"- 函数全形式: **{functions.Count}**");
        summary.AppendLine($"- inline 定义: **{inlineCount}**");
        summary.AppendLine($"- 头文件: **{hFiles.Count}**");
        await File.WriteAllTextAsync(summaryPath, summary.ToString(), Encoding.UTF8, cancellationToken);
        generated.Add(summaryPath);

        _logger.LogInformation(
            "SDK scan complete: chip={Chip}, peri={Peri}, funcs={Funcs}, out={Out}",
            chipModel, periList.Count, functions.Count, outputDirectory);

        return new SdkScanResult
        {
            Success = true,
            Message = $"扫描完成：芯片 {chipModel}，外设 {periList.Count}，函数 {functions.Count}（inline {inlineCount}）。JSON 已写入 {outputDirectory}",
            SdkRootPath = packageRoot,
            LlRootPath = llRoot,
            OutputDirectory = outputDirectory,
            ChipCount = 1,
            PeripheralCount = periList.Count,
            FunctionCount = functions.Count,
            InlineFunctionCount = inlineCount,
            FileCount = hFiles.Count,
            GeneratedFiles = generated,
            Errors = errors
        };
    }

    private static string ResolvePackageRoot(string path)
    {
        // If user picked LL folder, package is parent.
        if (string.Equals(Path.GetFileName(path), "LL", StringComparison.OrdinalIgnoreCase)
            && Directory.Exists(path))
            return Path.GetDirectoryName(path)!;

        // If path contains LL subdir, it's package root.
        if (Directory.Exists(Path.Combine(path, "LL")))
            return path;

        // If headers are directly in path, treat as LL and package=parent or self.
        if (Directory.EnumerateFiles(path, "*.h").Any())
            return Directory.GetParent(path)?.FullName ?? path;

        // Search one level for */LL
        var nested = Directory.EnumerateDirectories(path)
            .Select(d => Path.Combine(d, "LL"))
            .FirstOrDefault(Directory.Exists);
        if (nested is not null)
            return Path.GetDirectoryName(nested)!;

        return path;
    }

    private static string? ResolveLlRoot(string packageRoot)
    {
        var layout = SdkSeriesLayout.Discover(packageRoot);
        if (!string.IsNullOrWhiteSpace(layout?.LlRoot) && Directory.Exists(layout.LlRoot))
            return layout.LlRoot;

        var ll = Path.Combine(packageRoot, "LL");
        if (Directory.Exists(ll)) return ll;
        if (Directory.EnumerateFiles(packageRoot, "*.h").Any()) return packageRoot;
        try
        {
            return Directory.EnumerateDirectories(packageRoot, "LL", SearchOption.AllDirectories)
                .FirstOrDefault(d => Directory.EnumerateFiles(d, "tae32*_ll_*.h").Any())
                   ?? Directory.EnumerateDirectories(packageRoot, "LL", SearchOption.AllDirectories).FirstOrDefault();
        }
        catch
        {
            return null;
        }
    }

    private static string? DiscoverChip(List<FileData> files)
    {
        foreach (var f in files)
        {
            foreach (Match m in ReAddtogroup.Matches(f.Text))
            {
                var g = m.Groups[1].Value;
                if (g.StartsWith("TAE32", StringComparison.OrdinalIgnoreCase))
                    return NormalizeChip(g);
            }
            foreach (Match m in ReGuard.Matches(f.Text))
            {
                var g = m.Groups[1].Value;
                var mm = Regex.Match(g, @"TAE32[A-Z0-9]+", RegexOptions.IgnoreCase);
                if (mm.Success) return NormalizeChip(mm.Value);
            }
            foreach (Match m in ReVersionMacro.Matches(f.Text))
            {
                var mm = Regex.Match(m.Groups[1].Value, @"TAE32[A-Za-z0-9]+");
                if (mm.Success) return NormalizeChip(mm.Value);
            }
        }
        var nameHint = files.Select(f => f.Name).FirstOrDefault(n => n.StartsWith("tae32", StringComparison.OrdinalIgnoreCase));
        if (nameHint is not null)
        {
            var mm = Regex.Match(nameHint, @"tae32[a-z0-9]+", RegexOptions.IgnoreCase);
            if (mm.Success) return NormalizeChip(mm.Value);
        }
        return null;
    }

    private static string NormalizeChip(string token)
    {
        var up = token.ToUpperInvariant();
        // Keep established G58 series spelling from baseline / Doxygen.
        if (up.Contains("G58")) return SdkSeriesLayout.FallbackChipModel;
        return token;
    }

    private static List<PeripheralInfo> DiscoverPeripherals(List<FileData> files, string chip)
    {
        var list = new List<PeripheralInfo>();
        foreach (var f in files)
        {
            if (f.Name.EndsWith("_ll.h", StringComparison.OrdinalIgnoreCase)
                || f.Name.EndsWith("_ll_def.h", StringComparison.OrdinalIgnoreCase))
                continue;

            string? name = null;
            var brief = ReBriefHeader.Match(f.Text);
            if (brief.Success)
                name = brief.Groups[1].Value.Split('(')[0].Trim();

            if (name is null)
            {
                foreach (Match m in ReDefgroup.Matches(f.Text))
                {
                    var g = m.Groups[1].Value;
                    if (Regex.IsMatch(g, @"^[A-Za-z][A-Za-z0-9]*_LL$"))
                    {
                        name = g[..^3];
                        break;
                    }
                }
            }

            if (name is null)
            {
                var fm = ReFileModule.Match(f.Name);
                if (fm.Success)
                {
                    var token = fm.Groups[1].Value.ToUpperInvariant();
                    if (token is "DEF") continue;
                    name = token;
                }
            }

            if (string.IsNullOrWhiteSpace(name)) continue;
            name = name.Trim().ToUpperInvariant();

            var instances = ExtractEarlyInstances(f.Text);
            var typedefs = ReTypeDef.Matches(f.Text)
                .Select(m => m.Groups[1].Value)
                .Where(t => !t.StartsWith("LL_", StringComparison.Ordinal) && Regex.IsMatch(t, @"^[A-Z]"))
                .Distinct(StringComparer.Ordinal)
                .Where(t => t.StartsWith(name, StringComparison.OrdinalIgnoreCase) || name.StartsWith(t, StringComparison.OrdinalIgnoreCase) || files.Count == 1)
                .Take(8)
                .ToList();

            // Prefer related typedefs containing peripheral name
            typedefs = ReTypeDef.Matches(f.Text)
                .Select(m => m.Groups[1].Value)
                .Where(t => !t.StartsWith("LL_", StringComparison.Ordinal))
                .Where(t => t.Contains(name, StringComparison.OrdinalIgnoreCase) || name.Contains(t, StringComparison.OrdinalIgnoreCase))
                .Distinct(StringComparer.OrdinalIgnoreCase)
                .ToList();

            list.Add(new PeripheralInfo
            {
                Name = name,
                RelatedFiles = new List<string> { f.RelPath },
                Instances = FilterInstances(name, instances),
                Typedefs = typedefs,
                Confidence = brief.Success ? "高" : "中",
                Status = brief.Success ? "自动识别" : "待确认",
                Notes = name == "LPTMR" && instances.Any(i => i.StartsWith("TMR"))
                    ? "模块名 LPTMR 与实例宏可能为 TMRn"
                    : null
            });
        }

        return list
            .GroupBy(p => p.Name, StringComparer.OrdinalIgnoreCase)
            .Select(g => g.First())
            .OrderBy(p => p.Name, StringComparer.OrdinalIgnoreCase)
            .ToList();
    }

    private static List<string> ExtractEarlyInstances(string text)
    {
        var lines = text.Split('\n');
        var head = string.Join("\n", lines.Take(Math.Min(80, lines.Length)));
        foreach (Match m in ReIfdefMultiline.Matches(head))
        {
            var tokens = ReDefinedToken.Matches(m.Groups[1].Value)
                .Select(x => x.Groups[1].Value)
                .Where(t => !t.StartsWith("TAE32_USE", StringComparison.Ordinal) && !t.StartsWith("__", StringComparison.Ordinal))
                .Distinct(StringComparer.Ordinal)
                .ToList();
            if (tokens.Count > 0) return tokens;
        }
        return new List<string>();
    }

    private static List<string> FilterInstances(string module, List<string> instances)
    {
        var matched = new List<string>();
        foreach (var inst in instances)
        {
            if (inst.StartsWith(module, StringComparison.OrdinalIgnoreCase)) matched.Add(inst);
            else if (module == "GPIO" && Regex.IsMatch(inst, @"^GPIO[A-Z]$")) matched.Add(inst);
            else if ((module is "LPTMR" or "GPTMRX" or "GPTMRY" or "ADTMR" or "BSTMR") && Regex.IsMatch(inst, @"^TMR\d+$")) matched.Add(inst);
            else if ((module is "DMA" or "EFLASH" or "HRPWM" or "IWDG" or "RCU" or "SYSCTRL" or "WWDG")
                     && string.Equals(inst, module, StringComparison.OrdinalIgnoreCase)) matched.Add(inst);
        }
        if (matched.Count == 0 && instances.Count > 0
            && module is "GPTMRX" or "GPTMRY" or "ADTMR" or "BSTMR" or "LPTMR"
            && instances.All(i => Regex.IsMatch(i, @"^TMR\d+$")))
            matched.AddRange(instances);
        if (matched.Count == 0 && instances.Count > 0) matched.AddRange(instances);
        return matched.Distinct(StringComparer.Ordinal).ToList();
    }

    private static List<FuncInfo> ExtractFunctions(List<FileData> files, string chip, List<PeripheralInfo> peris, CancellationToken ct)
    {
        var periByFile = peris
            .SelectMany(p => p.RelatedFiles.Select(rf => (rf, p.Name)))
            .GroupBy(x => x.rf, StringComparer.OrdinalIgnoreCase)
            .ToDictionary(g => g.Key, g => g.First().Name, StringComparer.OrdinalIgnoreCase);

        var result = new List<FuncInfo>();
        foreach (var f in files)
        {
            ct.ThrowIfCancellationRequested();
            periByFile.TryGetValue(f.RelPath, out var periHint);
            ExtractInline(f, chip, periHint, result);
            ExtractDecls(f, chip, periHint, result);
            ExtractMacros(f, chip, periHint, result);
        }
        return result;
    }

    private static void ExtractInline(FileData f, string chip, string? periHint, List<FuncInfo> result)
    {
        foreach (Match m in ReSimpleFunc.Matches(f.Text))
        {
            var name = m.Groups["name"].Value;
            var ret = m.Groups["ret"].Value.Trim();
            var prefix = m.Groups["prefix"].Value.Trim();
            var paren = f.Text.IndexOf('(', m.Index + m.Length - 1);
            if (paren < 0) continue;
            var (parameters, close) = ExtractParens(f.Text, paren);
            if (close < 0) continue;
            var j = close + 1;
            while (j < f.Text.Length && char.IsWhiteSpace(f.Text[j])) j++;
            string form;
            int endLine;
            var startLine = LineOf(f.Text, m.Index);
            if (j < f.Text.Length && f.Text[j] == '{')
            {
                var endBrace = FindMatchingBrace(f.Text, j);
                endLine = endBrace < 0 ? startLine : LineOf(f.Text, endBrace);
                form = "inline_definition";
            }
            else if (j < f.Text.Length && f.Text[j] == ';')
            {
                endLine = LineOf(f.Text, j);
                form = "inline_declaration";
            }
            else continue;

            var ftype = prefix.Contains("__STATIC_INLINE", StringComparison.Ordinal) ? "__STATIC_INLINE"
                : Regex.IsMatch(prefix, @"static\s+inline") ? "static_inline" : "inline";
            var peri = ResolvePeripheral(name, periHint);
            result.Add(new FuncInfo(name, ret, Collapse(parameters), ftype, form, peri, chip, f.RelPath, startLine, endLine, "自动识别"));
        }
    }

    private static void ExtractDecls(FileData f, string chip, string? periHint, List<FuncInfo> result)
    {
        foreach (Match m in ReOrdinaryDecl.Matches(f.Text))
        {
            var name = m.Groups["name"].Value;
            if (result.Any(x => x.Name == name && Math.Abs(x.StartLine - LineOf(f.Text, m.Index)) < 2)) continue;
            var ret = m.Groups["ret"].Value.Trim();
            if (ret.StartsWith('#') || ret.Contains("typedef", StringComparison.Ordinal)) continue;
            var start = LineOf(f.Text, m.Index);
            result.Add(new FuncInfo(name, ret, Collapse(m.Groups["params"].Value), "ordinary_declaration", "declaration",
                ResolvePeripheral(name, periHint), chip, f.RelPath, start, LineOf(f.Text, m.Index + m.Length), "自动识别"));
        }
    }

    private static void ExtractMacros(FileData f, string chip, string? periHint, List<FuncInfo> result)
    {
        foreach (Match m in ReMacroFunc.Matches(f.Text))
        {
            var name = m.Groups[1].Value;
            if (!name.StartsWith("LL_", StringComparison.Ordinal)) continue;
            if (result.Any(x => x.Name == name && x.Form is "inline_definition" or "declaration")) continue;
            var start = LineOf(f.Text, m.Index);
            var end = start;
            var pos = m.Index;
            while (true)
            {
                var lineEnd = f.Text.IndexOf('\n', pos);
                if (lineEnd < 0) { end = LineOf(f.Text, f.Text.Length - 1); break; }
                var line = f.Text[pos..lineEnd];
                end = LineOf(f.Text, lineEnd);
                if (line.TrimEnd().EndsWith('\\')) { pos = lineEnd + 1; continue; }
                break;
            }
            result.Add(new FuncInfo(name, "(macro)", Collapse(m.Groups[2].Value), "macro_function", "function_macro",
                ResolvePeripheral(name, periHint), chip, f.RelPath, start, end, "自动识别"));
        }
    }

    private static string? ResolvePeripheral(string functionName, string? hint)
    {
        if (hint is not null &&
            (Regex.IsMatch(functionName, @"^LL_(NVIC_|Init|Delay_)") || string.Equals(hint, "CORTEX", StringComparison.OrdinalIgnoreCase)))
        {
            if (string.Equals(hint, "CORTEX", StringComparison.OrdinalIgnoreCase)
                && Regex.IsMatch(functionName, @"^LL_(NVIC_|Init|Delay_)"))
                return "CORTEX";
        }
        var m = Regex.Match(functionName, @"^LL_([A-Za-z0-9]+)_");
        if (m.Success) return m.Groups[1].Value.ToUpperInvariant();
        return hint?.ToUpperInvariant();
    }

    private static (string paramsText, int closeIdx) ExtractParens(string text, int openIdx)
    {
        var depth = 0;
        for (var i = openIdx; i < text.Length; i++)
        {
            if (text[i] == '(') depth++;
            else if (text[i] == ')')
            {
                depth--;
                if (depth == 0) return (text[(openIdx + 1)..i].Trim(), i);
            }
        }
        return (text[(openIdx + 1)..].Trim(), -1);
    }

    private static int FindMatchingBrace(string text, int openIdx)
    {
        var depth = 0;
        var inStr = false;
        var inChar = false;
        var lineComment = false;
        var blockComment = false;
        for (var i = openIdx; i < text.Length; i++)
        {
            var c = text[i];
            var n = i + 1 < text.Length ? text[i + 1] : '\0';
            if (lineComment) { if (c == '\n') lineComment = false; continue; }
            if (blockComment) { if (c == '*' && n == '/') { blockComment = false; i++; } continue; }
            if (inStr) { if (c == '\\') { i++; continue; } if (c == '"') inStr = false; continue; }
            if (inChar) { if (c == '\\') { i++; continue; } if (c == '\'') inChar = false; continue; }
            if (c == '/' && n == '/') { lineComment = true; i++; continue; }
            if (c == '/' && n == '*') { blockComment = true; i++; continue; }
            if (c == '"') { inStr = true; continue; }
            if (c == '\'') { inChar = true; continue; }
            if (c == '{') depth++;
            else if (c == '}')
            {
                depth--;
                if (depth == 0) return i;
            }
        }
        return -1;
    }

    private static int LineOf(string text, int idx) => text.AsSpan(0, Math.Clamp(idx, 0, text.Length)).Count('\n') + 1;
    private static string Collapse(string s) => Regex.Replace(s ?? "", @"\s+", " ").Trim();
    private static string ToRel(string packageRoot, string full)
    {
        var workspace = FindWorkspace(packageRoot);
        var rel = Path.GetRelativePath(workspace, full).Replace('\\', '/');
        if (!rel.StartsWith("..", StringComparison.Ordinal))
            return rel;
        // Outside workspace: keep path relative to package parent (e.g. SDKContent/...)
        var parent = Directory.GetParent(packageRoot)?.FullName ?? packageRoot;
        return Path.GetRelativePath(parent, full).Replace('\\', '/');
    }

    private static string FindWorkspace(string packageRoot)
    {
        var dir = new DirectoryInfo(packageRoot);
        while (dir is not null)
        {
            if (Directory.Exists(Path.Combine(dir.FullName, "SDKContent"))
                || Directory.Exists(Path.Combine(dir.FullName, "ScanResults")))
                return dir.FullName;
            dir = dir.Parent;
        }
        return Directory.GetParent(packageRoot)?.FullName ?? packageRoot;
    }

    private static async Task<string> ReadTextAsync(string path, CancellationToken ct)
    {
        Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
        Encoding[] encodings;
        try
        {
            encodings = new[] { Encoding.UTF8, Encoding.GetEncoding("GBK"), Encoding.Latin1 };
        }
        catch
        {
            encodings = new[] { Encoding.UTF8, Encoding.Latin1 };
        }

        foreach (var enc in encodings)
        {
            try
            {
                await using var fs = File.OpenRead(path);
                using var reader = new StreamReader(fs, enc, detectEncodingFromByteOrderMarks: true);
                return await reader.ReadToEndAsync(ct);
            }
            catch (DecoderFallbackException) { }
            catch (ArgumentException) { }
        }
        return await File.ReadAllTextAsync(path, Encoding.UTF8, ct);
    }

    private static SdkScanResult Fail(string message) => new()
    {
        Success = false,
        Message = message,
        Errors = new[] { message }
    };

    private sealed record FileData(string FullPath, string RelPath, string Name, string Text);

    private sealed class PeripheralInfo
    {
        public string Name { get; set; } = "";
        public List<string> RelatedFiles { get; set; } = new();
        public List<string> Instances { get; set; } = new();
        public List<string> Typedefs { get; set; } = new();
        public string Confidence { get; set; } = "中";
        public string Status { get; set; } = "自动识别";
        public string? Notes { get; set; }
    }

    private sealed record FuncInfo(
        string Name, string ReturnType, string Parameters, string FunctionType, string Form,
        string? Peripheral, string Chip, string FilePath, int StartLine, int EndLine, string Status);
}
