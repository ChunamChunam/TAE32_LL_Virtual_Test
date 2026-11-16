using System.Text.RegularExpressions;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

var root = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", ".."));
var dbPath = Path.Combine(root, "Publish", "data", "tae32_ll_virtual_test.db");
var sdk = Path.Combine(root, "Publish", "SDKContent", "Tai-Action.TAE32G580x_DFP.2.0.0");
var llRoot = Path.Combine(sdk, "SDK", "Drivers", "TAE32G58xx_Driver", "LL");
var mode = args.ElementAtOrDefault(0) ?? "scan"; // scan | smoke | scan-all

Console.WriteLine($"mode={mode} db={dbPath}");
EnsureNativeRunner(root);

var services = new ServiceCollection();
services.AddLogging();
services.AddInfrastructure(dbPath);
var sp = services.BuildServiceProvider();
var dbFactory = sp.GetRequiredService<IDbContextFactory<AppDbContext>>();
var gen = sp.GetRequiredService<LlTestCaseGenerator>();
var store = sp.GetRequiredService<ILlTestCaseStore>();
var engine = sp.GetRequiredService<ILLTestEngine>();

await using (var db = await dbFactory.CreateDbContextAsync())
{
    var project = await db.SdkProjects.FirstAsync();
    project.SdkRootPath = sdk;
    await db.SaveChangesAsync();
}

if (mode == "smoke")
{
    await RunSmokeAsync(dbFactory, gen, store, engine, sdk);
    return;
}

var includeAll = mode is "scan-all" or "scan";
var headerFns = ScanHeaderOps(llRoot, includeReads: includeAll, includeModify: includeAll);
Console.WriteLine($"header macro functions: {headerFns.Count}");

Dictionary<string, Guid> dbMap;
await using (var db = await dbFactory.CreateDbContextAsync())
{
    var rows = await db.LlFunctions.AsNoTracking()
        .Where(f => f.Form == null || f.Form.Contains("inline"))
        .Select(f => new { f.Id, f.FunctionName })
        .ToListAsync();
    dbMap = rows
        .GroupBy(f => f.FunctionName)
        .ToDictionary(g => g.Key, g => g.First().Id);
}

// Point FilePath to Publish LL headers for live-body reads.
await using (var db = await dbFactory.CreateDbContextAsync())
{
    var touched = 0;
    foreach (var h in headerFns)
    {
        if (!dbMap.TryGetValue(h.Function, out var id)) continue;
        var fn = await db.LlFunctions.FirstOrDefaultAsync(f => f.Id == id);
        if (fn is null) continue;
        var want = h.HeaderPath.Replace('\\', '/');
        if (!string.Equals(fn.FilePath, want, StringComparison.OrdinalIgnoreCase))
        {
            fn.FilePath = want;
            touched++;
        }
    }

    if (touched > 0)
    {
        await db.SaveChangesAsync();
        Console.WriteLine($"updated FilePath for {touched} functions → Publish LL");
    }
}

var trusted = 0;
var weak = 0;
var none = 0;
var missingDb = 0;
var errors = 0;
var weakList = new List<string>();
var noneList = new List<string>();
var byOp = new Dictionary<string, (int Trusted, int Weak, int None)>(StringComparer.OrdinalIgnoreCase);
var reportPath = Path.Combine(root, "tools", "_verify_adc_set", "bitop_trust_report.csv");
await using var report = new StreamWriter(reportPath);
await report.WriteLineAsync("function,file,op,bodyMask,status,caseName,expectedHex,expectedMask,ruleDetail");

var i = 0;
foreach (var h in headerFns.OrderBy(x => x.Function))
{
    i++;
    if (i % 80 == 0) Console.WriteLine($"… {i}/{headerFns.Count} trusted={trusted} weak={weak} none={none}");

    if (!byOp.ContainsKey(h.Op))
        byOp[h.Op] = (0, 0, 0);

    if (!dbMap.TryGetValue(h.Function, out var fnId))
    {
        missingDb++;
        await report.WriteLineAsync($"{h.Function},{Path.GetFileName(h.HeaderPath)},{h.Op},{h.BodyMask},MISSING_DB,,,,");
        continue;
    }

    try
    {
        var models = await gen.GenerateAsync(fnId);
        var bitCase = PickSemanticCase(models, h.Op);

        if (bitCase is null)
        {
            none++;
            byOp[h.Op] = byOp[h.Op] with { None = byOp[h.Op].None + 1 };
            noneList.Add($"{h.Function} [{h.Op} {h.BodyMask}]");
            await report.WriteLineAsync($"{h.Function},{Path.GetFileName(h.HeaderPath)},{h.Op},{h.BodyMask},NONE,,,,");
            continue;
        }

        var (expectedHex, expectedMask, detail) = ExtractExpectation(bitCase);
        var isTrusted = IsTrustedDetail(detail);

        if (isTrusted)
        {
            trusted++;
            byOp[h.Op] = byOp[h.Op] with { Trusted = byOp[h.Op].Trusted + 1 };
            await report.WriteLineAsync($"{h.Function},{Path.GetFileName(h.HeaderPath)},{h.Op},{h.BodyMask},TRUSTED,{bitCase.Name},{expectedHex},{expectedMask},\"{Esc(detail)}\"");
        }
        else
        {
            weak++;
            byOp[h.Op] = byOp[h.Op] with { Weak = byOp[h.Op].Weak + 1 };
            weakList.Add($"{h.Function} | {h.Op} body={h.BodyMask} | {detail}");
            await report.WriteLineAsync($"{h.Function},{Path.GetFileName(h.HeaderPath)},{h.Op},{h.BodyMask},WEAK,{bitCase.Name},{expectedHex},{expectedMask},\"{Esc(detail)}\"");
        }
    }
    catch (Exception ex)
    {
        errors++;
        await report.WriteLineAsync($"{h.Function},{Path.GetFileName(h.HeaderPath)},{h.Op},{h.BodyMask},ERROR,,,,\"{Esc(ex.Message)}\"");
    }
}

Console.WriteLine();
Console.WriteLine($"TRUSTED={trusted} WEAK={weak} NONE={none} MISSING_DB={missingDb} ERROR={errors} HEADER={headerFns.Count}");
Console.WriteLine("by-op:");
foreach (var kv in byOp.OrderByDescending(x => x.Value.Trusted + x.Value.Weak + x.Value.None))
    Console.WriteLine($"  {kv.Key}: TRUSTED={kv.Value.Trusted} WEAK={kv.Value.Weak} NONE={kv.Value.None}");
Console.WriteLine($"report={reportPath}");
File.WriteAllLines(Path.Combine(root, "tools", "_verify_adc_set", "bitop_weak.txt"), weakList);
File.WriteAllLines(Path.Combine(root, "tools", "_verify_adc_set", "bitop_none.txt"), noneList);
Console.WriteLine("\n--- WEAK sample ---");
foreach (var w in weakList.Take(40)) Console.WriteLine(w);
Console.WriteLine("\n--- NONE sample ---");
foreach (var n in noneList.Take(40)) Console.WriteLine(n);

static string Esc(string s) => s.Replace('\"', '\'');

static bool IsTrustedDetail(string detail)
{
    // Must not match the substring inside “未找到函数名关联…弱可信”.
    if (detail.Contains("弱可信", StringComparison.Ordinal))
        return false;
    return detail.Contains("期望掩码来自函数名关联的可信源", StringComparison.Ordinal)
           || detail.Contains("清掩码来自函数名关联可信源", StringComparison.Ordinal)
           || detail.Contains("函数名关联可信源", StringComparison.Ordinal)
           || detail.Contains("不以错误 clear-mask 为准", StringComparison.Ordinal)
           || detail.Contains("不以错误读掩码为准", StringComparison.Ordinal)
           || detail.Contains("不以错误读成员为准", StringComparison.Ordinal)
           || detail.Contains("不以错误 RHS 为准", StringComparison.Ordinal);
}

static LlTestCaseEditModel? PickSemanticCase(IReadOnlyList<LlTestCaseEditModel> models, string op)
{
    var isRead = op.StartsWith("READ", StringComparison.OrdinalIgnoreCase);
    if (isRead)
    {
        return models.FirstOrDefault(m =>
            m.Assertions.Any(a => a.Kind == LlAssertionKind.ReturnValue)
            && (m.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)
                || m.Name.Contains("set-get", StringComparison.OrdinalIgnoreCase)));
    }

    return models.FirstOrDefault(m =>
               m.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue)
               && (m.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase)
                   || m.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)
                   || m.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)))
           ?? models.FirstOrDefault(m =>
               m.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue)
               && m.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase));
}

static (string? Hex, uint? Mask, string Detail) ExtractExpectation(LlTestCaseEditModel model)
{
    // Prefer ReturnValue for read-checks; prefer the semantic RegisterValue (not "只读校验" side assert).
    var ret = model.Assertions.FirstOrDefault(a => a.Kind == LlAssertionKind.ReturnValue);
    if (ret is not null)
        return (ret.ExpectedHex, null, ret.RuleSourceDetail ?? "");

    var reg = model.Assertions.FirstOrDefault(a =>
        a.Kind == LlAssertionKind.RegisterValue
        && !(a.RuleSourceDetail ?? "").Contains("读不得改写", StringComparison.Ordinal));
    reg ??= model.Assertions.FirstOrDefault(a => a.Kind == LlAssertionKind.RegisterValue);
    if (reg is not null)
        return (reg.ExpectedHex, reg.ExpectedMask, reg.RuleSourceDetail ?? "");

    return (null, null, "");
}

static List<HeaderBitFn> ScanHeaderOps(string llRoot, bool includeReads, bool includeModify)
{
    var bitRe = new Regex(
        @"\b(?<op>SET_BIT|CLEAR_BIT|WRITE_REG)\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[^)]+)\)",
        RegexOptions.Compiled);
    var modifyRe = new Regex(
        @"\bMODIFY_REG\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_(?:Msk|MSK))\s*,",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);
    var readShiftRe = new Regex(
        @"\bREAD_BIT_SHIFT\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[^,]+),",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);
    var readBitRe = new Regex(
        @"\bREAD_BIT(?!_SHIFT)\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*,\s*(?<msk>[A-Za-z0-9_]+_Msk)\s*\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);
    var readRegRe = new Regex(
        @"\bREAD_REG\s*\(\s*[A-Za-z0-9_]+\s*->\s*(?<mem>[A-Za-z0-9_]+)\s*\)",
        RegexOptions.Compiled | RegexOptions.IgnoreCase);

    var list = new List<HeaderBitFn>();
    foreach (var h in Directory.EnumerateFiles(llRoot, "tae32g58xx_ll_*.h"))
    {
        var name = Path.GetFileName(h);
        if (name is "tae32g58xx_ll.h" || name.EndsWith("_def.h", StringComparison.OrdinalIgnoreCase))
            continue;
        var text = File.ReadAllText(h);
        foreach (Match fm in Regex.Matches(text, @"__STATIC_INLINE[\s\S]*?\n\}"))
        {
            var body = fm.Value;
            var nm = Regex.Match(body, @"\b(LL_[A-Za-z0-9_]+)\s*\(");
            if (!nm.Success) continue;
            var fn = nm.Groups[1].Value;

            var bm = bitRe.Match(body);
            if (bm.Success)
            {
                list.Add(new HeaderBitFn(fn, bm.Groups["op"].Value, bm.Groups["mem"].Value,
                    bm.Groups["msk"].Value.Trim(), h));
                continue;
            }

            if (includeModify)
            {
                var mm = modifyRe.Match(body);
                if (mm.Success)
                {
                    list.Add(new HeaderBitFn(fn, "MODIFY_REG", mm.Groups["mem"].Value,
                        mm.Groups["msk"].Value.Trim(), h));
                    continue;
                }
            }

            if (includeReads)
            {
                var rs = readShiftRe.Match(body);
                if (rs.Success)
                {
                    list.Add(new HeaderBitFn(fn, "READ_BIT_SHIFT", rs.Groups["mem"].Value,
                        rs.Groups["msk"].Value.Trim(), h));
                    continue;
                }

                var rb = readBitRe.Match(body);
                if (rb.Success)
                {
                    list.Add(new HeaderBitFn(fn, "READ_BIT", rb.Groups["mem"].Value,
                        rb.Groups["msk"].Value.Trim(), h));
                    continue;
                }

                var rr = readRegRe.Match(body);
                if (rr.Success && !body.Contains("OFFSET", StringComparison.Ordinal))
                {
                    list.Add(new HeaderBitFn(fn, "READ_REG", rr.Groups["mem"].Value, "", h));
                }
            }
        }
    }

    return list
        .GroupBy(x => x.Function)
        .Select(g => g.First())
        .ToList();
}

static async Task RunSmokeAsync(
    IDbContextFactory<AppDbContext> dbFactory,
    LlTestCaseGenerator gen,
    ILlTestCaseStore store,
    ILLTestEngine engine,
    string sdk)
{
    var samples = new (string Header, string Fn, string CorrectMask, string WrongMask)[]
    {
        ("tae32g58xx_ll_adc.h", "LL_ADC_AssertPreparingStart", "LL_ADC_CFGR1_PREPARING_START_MSK", "ADC0_CFGR1_BIASEN_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_DisableIT_AWDG2", "ADC0_IER_AWD2IE_Msk", "ADC0_IER_AWD1IE_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_EnableIT_AWDG1", "ADC0_IER_AWD1IE_Msk", "ADC0_IER_AWD0IE_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_DisableBias", "ADC0_CFGR1_BIASEN_Msk", "ADC0_CFGR1_REFEN_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_EnableBias", "ADC0_CFGR1_BIASEN_Msk", "ADC0_CFGR1_CHEN_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_DisableIT_OVR", "ADC0_IER_OVRIE_Msk", "ADC0_IER_EOCIE_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_EnableChannel", "ADC0_CFGR1_CHEN_Msk", "ADC0_CFGR1_REFEN_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_ClearFlag_AWD1", "ADC0_ISR_AWD0_Msk", "ADC0_ISR_AWD1_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_SetCalibrationMode", "ADC0_CR_ADCALDIF_Msk", "ADC0_CR_ADCAL_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_GetCalibrationMode", "ADC0_CR_ADCALDIF_Msk", "ADC0_CR_ADCAL_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_SetOverSamplingRightShift", "ADC0_CFGR0_OVSS_Msk", "ADC0_CFGR0_OVSR_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_StartCalibration", "ADC0_CR_ADCAL_Msk", "ADC0_CR_ADEN_Msk"),
        ("tae32g58xx_ll_adc.h", "LL_ADC_IsEnabled", "ADC0_CR_ADEN_Msk", "ADC0_CR_ADDIS_Msk"),
        ("tae32g58xx_ll_can.h", "LL_CAN_EnableLoopBackModeExternal", "CAN0_CTRL_LBME_Msk", "CAN0_CTRL_LBMI_Msk"),
        ("tae32g58xx_ll_can.h", "LL_CAN_DisableLoopBackModeInternal", "CAN0_CTRL_LBMI_Msk", "CAN0_CTRL_LBME_Msk"),
        ("tae32g58xx_ll_can.h", "LL_CAN_EnableContinuousCountTimeout", "CAN0_CTOP_CTOE_Msk", "CAN0_CTRL_LBME_Msk"),
        ("tae32g58xx_ll_can.h", "LL_CAN_DisableStandardRemoteFrameReject", "CAN0_GFCR_SRFR_Msk", "CAN0_GFCR_ERFR_Msk"),
        ("tae32g58xx_ll_rcu.h", "LL_RCU_HSE_Enable", "RCU_XOSCCR_XEN_Msk", "RCU_XOSCCR_HEN_Msk"),
        ("tae32g58xx_ll_cmp.h", "LL_CMP_EnableOutputInvert", "CMP0_CR_OPOL_Msk", "CMP0_CR_ODEB_Msk"),
        ("tae32g58xx_ll_dac.h", "LL_DAC_EnableBufferOutput", "DAC0_CR_OEN_Msk", "DAC0_CR_BEN_Msk"),
    };

    var llDir = Path.Combine(sdk, "SDK", "Drivers", "TAE32G58xx_Driver", "LL");
    var originals = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
    var okCount = 0;
    var failCount = 0;
    try
    {
        foreach (var (headerName, fnName, correct, wrong) in samples)
        {
            var header = Path.Combine(llDir, headerName);
            if (!originals.ContainsKey(header))
                originals[header] = await File.ReadAllTextAsync(header);

            Console.WriteLine($"\n==== SMOKE {fnName} ====");
            Guid fnId;
            await using (var db = await dbFactory.CreateDbContextAsync())
            {
                var fn = await db.LlFunctions.FirstAsync(f => f.FunctionName == fnName);
                fnId = fn.Id;
                fn.FilePath = header.Replace('\\', '/');
                await db.SaveChangesAsync();
                var old = await db.LlTestCases.Where(c => c.LlFunctionId == fnId).Select(c => c.Id).ToListAsync();
                if (old.Count > 0) await store.DeleteManyAsync(old);
            }

            PatchFnMask(header, fnName, correct, wrong);
            var correctPos = correct.Replace("_Msk", "_Pos", StringComparison.Ordinal);
            var wrongPos = wrong.Replace("_Msk", "_Pos", StringComparison.Ordinal);
            var correctVal = correct.Replace("_Msk", "_Val", StringComparison.Ordinal);
            var wrongVal = wrong.Replace("_Msk", "_Val", StringComparison.Ordinal);
            if (!string.Equals(correctPos, correct, StringComparison.Ordinal))
                PatchFnMask(header, fnName, correctPos, wrongPos);
            if (!string.Equals(correctVal, correct, StringComparison.Ordinal))
                PatchFnMask(header, fnName, correctVal, wrongVal);

            var models = await gen.GenerateAsync(fnId);
            var opHint = fnName.Contains("Get", StringComparison.Ordinal) || fnName.Contains("Is", StringComparison.Ordinal)
                ? "READ_BIT_SHIFT"
                : "MODIFY_REG";
            var primary = PickSemanticCase(models, opHint)
                          ?? models.First(m => m.Assertions.Any(a =>
                              a.Kind is LlAssertionKind.RegisterValue or LlAssertionKind.ReturnValue));
            var saved = await store.UpsertAsync(primary);
            var wrongRun = await engine.RunCaseAsync(new LlTestRunRequest { TestCaseId = saved.Id });

            PatchFnMask(header, fnName, wrong, correct);
            if (!string.Equals(correctPos, correct, StringComparison.Ordinal))
                PatchFnMask(header, fnName, wrongPos, correctPos);
            if (!string.Equals(correctVal, correct, StringComparison.Ordinal))
                PatchFnMask(header, fnName, wrongVal, correctVal);

            var okRun = await engine.RunCaseAsync(new LlTestRunRequest { TestCaseId = saved.Id });
            var detail = ExtractExpectation(primary).Detail;
            Console.WriteLine($"wrong=>{wrongRun.Status} correct=>{okRun.Status} detail={detail}");
            if (wrongRun.Status != LlTestRunStatus.Failed || okRun.Status != LlTestRunStatus.Passed)
            {
                failCount++;
                Console.WriteLine("SMOKE FAIL");
            }
            else
            {
                okCount++;
                Console.WriteLine("OK");
            }
        }
    }
    finally
    {
        foreach (var (path, text) in originals)
            await File.WriteAllTextAsync(path, text);
        Console.WriteLine($"headers restored; smoke OK={okCount} FAIL={failCount}");
    }
}

static void PatchFnMask(string header, string fnName, string fromMask, string toMask)
{
    var text = File.ReadAllText(header);
    var marker = fnName + "(";
    var idx = text.IndexOf(marker, StringComparison.Ordinal);
    if (idx < 0) throw new InvalidOperationException("fn not found " + fnName);
    var brace = text.IndexOf('{', idx);
    var end = text.IndexOf('}', brace);
    var body = text[brace..(end + 1)];
    if (!body.Contains(fromMask, StringComparison.Ordinal))
        return; // optional companion token
    body = body.Replace(fromMask, toMask, StringComparison.Ordinal);
    File.WriteAllText(header, text[..brace] + body + text[(end + 1)..]);
}

static void EnsureNativeRunner(string root)
{
    var dest = AppContext.BaseDirectory;
    var srcDir = Path.Combine(root, "src", "TAE32.LLVirtualTest.NativeRunner", "bin", "Debug", "net8.0");
    foreach (var name in new[]
             {
                 "TAE32.LLVirtualTest.NativeRunner.exe", "TAE32.LLVirtualTest.NativeRunner.dll",
                 "TAE32.LLVirtualTest.NativeRunner.runtimeconfig.json", "TAE32.LLVirtualTest.NativeRunner.deps.json"
             })
    {
        var src = Path.Combine(srcDir, name);
        if (File.Exists(src)) File.Copy(src, Path.Combine(dest, name), true);
    }
}

internal sealed record HeaderBitFn(string Function, string Op, string Member, string BodyMask, string HeaderPath);
