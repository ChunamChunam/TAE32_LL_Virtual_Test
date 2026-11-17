using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

public sealed class LlTestEngine : ILLTestEngine
{
    private readonly ICompilerService _compiler;
    private readonly ILlTestCaseStore _store;
    private readonly IVirtualMcuService _mcu;
    private readonly ISdkProjectService _projects;
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly LlTestCaseGenerator _generator;
    private readonly LlShiftStaticAnalyzer _staticAnalyzer;
    private readonly string _workRoot;

    public LlTestEngine(
        ICompilerService compiler,
        ILlTestCaseStore store,
        IVirtualMcuService mcu,
        ISdkProjectService projects,
        IDbContextFactory<AppDbContext> dbFactory,
        LlTestCaseGenerator generator,
        LlShiftStaticAnalyzer? staticAnalyzer = null)
    {
        _compiler = compiler;
        _store = store;
        _mcu = mcu;
        _projects = projects;
        _dbFactory = dbFactory;
        _generator = generator;
        _staticAnalyzer = staticAnalyzer ?? new LlShiftStaticAnalyzer();
        _workRoot = Path.Combine(Path.GetTempPath(), "tae32_ll_test_work");
        Directory.CreateDirectory(_workRoot);
    }

    public Task<CompilerEnvironmentInfo> CheckCompilerAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
        => _compiler.CheckEnvironmentAsync(sdkProjectId, cancellationToken);

    public Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesAsync(
        Guid llFunctionId, CancellationToken cancellationToken = default)
        => _generator.GenerateAsync(llFunctionId, cancellationToken);

    public Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesForPeripheralAsync(
        Guid sdkProjectId, string peripheralName, CancellationToken cancellationToken = default)
        => _generator.GenerateForPeripheralAsync(sdkProjectId, peripheralName, cancellationToken);

    public async Task<(int FunctionsProcessed, int CasesSaved)> GenerateAndSaveForPeripheralAsync(
        Guid sdkProjectId,
        string peripheralName,
        IProgress<(int FunctionIndex, int FunctionTotal, int CasesSaved, string PeripheralName)>? progress = null,
        CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var functionIds = await db.LlFunctions.AsNoTracking()
            .Where(x => x.SdkProjectId == sdkProjectId
                        && x.PeripheralName == peripheralName
                        && (x.Form == null || x.Form.Contains("inline")))
            .OrderBy(x => x.FunctionName)
            .Select(x => x.Id)
            .ToListAsync(cancellationToken);

        var pending = new List<LlTestCaseEditModel>(32);
        var casesSaved = 0;
        var processed = 0;

        async Task FlushAsync()
        {
            if (pending.Count == 0) return;
            casesSaved += await _store.InsertManyAsync(pending, cancellationToken);
            pending.Clear();
        }

        for (var i = 0; i < functionIds.Count; i++)
        {
            cancellationToken.ThrowIfCancellationRequested();
            processed++;
            IReadOnlyList<LlTestCaseEditModel> generated;
            try
            {
                generated = await _generator.GenerateAsync(functionIds[i], cancellationToken);
            }
            catch
            {
                progress?.Report((i + 1, functionIds.Count, casesSaved, peripheralName));
                if (i % 4 == 0)
                    await Task.Yield();
                continue;
            }

            pending.AddRange(generated);
            if (pending.Count >= 24)
                await FlushAsync();

            progress?.Report((i + 1, functionIds.Count, casesSaved, peripheralName));
            if (i % 3 == 0)
                await Task.Yield();
        }

        await FlushAsync();
        progress?.Report((functionIds.Count, functionIds.Count, casesSaved, peripheralName));
        return (processed, casesSaved);
    }

    public async Task RunAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
    {
        var cases = await _store.ListAsync(sdkProjectId, cancellationToken: cancellationToken);
        var ready = cases.Where(c => c.Status == "Ready").Select(c => c.Id).ToList();
        await RunManyAsync(ready, null, cancellationToken);
    }

    public async Task<IReadOnlyList<LlTestRunResult>> RunManyAsync(
        IEnumerable<Guid> testCaseIds,
        IProgress<string>? log = null,
        CancellationToken cancellationToken = default)
    {
        var results = new List<LlTestRunResult>();
        foreach (var id in testCaseIds)
        {
            cancellationToken.ThrowIfCancellationRequested();
            log?.Report($"运行用例 {id}");
            // Off WPF sync context: compile/static-analysis/native wait must not freeze the UI.
            var result = await Task.Run(
                    () => RunCaseAsync(new LlTestRunRequest { TestCaseId = id }, log, cancellationToken),
                    cancellationToken)
                .ConfigureAwait(false);
            results.Add(result);
        }
        return results;
    }

    public async Task<LlTestRunResult> RunCaseAsync(
        LlTestRunRequest request,
        IProgress<string>? log = null,
        CancellationToken cancellationToken = default)
    {
        var sw = Stopwatch.StartNew();
        var stages = new List<LlTestStageResult>();
        var execLog = new StringBuilder();
        void L(string m) { execLog.AppendLine(m); log?.Report(m); }

        var entity = await _store.GetAsync(request.TestCaseId, cancellationToken)
                     ?? throw new KeyNotFoundException("测试用例不存在");
        var edit = LlTestCaseStore.ToEdit(entity);
        var run = new LlTestRun
        {
            Id = Guid.NewGuid(),
            SdkProjectId = entity.SdkProjectId,
            LlTestCaseId = entity.Id,
            Status = nameof(LlTestRunStatus.Compiling),
            StartedAtUtc = DateTime.UtcNow
        };

        Guid? mcuId = null;
        try
        {
            var env = await _compiler.CheckEnvironmentAsync(entity.SdkProjectId, cancellationToken);
            stages.Add(new LlTestStageResult
            {
                Stage = LlTestExecutionStage.EnvironmentCheck,
                Succeeded = env.ClangFound,
                Message = env.Summary
            });
            L(env.Summary);

            if (!env.ClangFound)
            {
                if (request.SkipNativeIfNoCompiler)
                {
                    run.Status = nameof(LlTestRunStatus.Skipped);
                    run.FailureReason = "未配置 Clang，跳过本地原生执行（非硬件验证）。";
                    stages.Add(new LlTestStageResult
                    {
                        Stage = LlTestExecutionStage.Compile,
                        Succeeded = false,
                        Message = run.FailureReason
                    });
                    return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
                }

                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = "Clang 不可用，拒绝执行（避免访问真实物理地址）。";
                return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }

            // Pre-compile LL source static analysis (shift / Mask-as-Pos / register-field mismatch).
            // Blocking Errors stop Native Execute even if Clang would accept the code.
            var project = await _projects.GetByIdAsync(entity.SdkProjectId, cancellationToken);
            var resolvedSource = ResolveLlSourcePath(entity.SourceFile, project?.SdkRootPath);
            var staticResult = _staticAnalyzer.Analyze(
                project?.SdkRootPath, resolvedSource, entity.FunctionName);
            run.StaticAnalysisJson = LlTestJson.Serialize(staticResult.Diagnostics);
            var staticReport = LlShiftStaticAnalyzer.FormatReport(entity.FunctionName, staticResult);
            stages.Add(new LlTestStageResult
            {
                Stage = LlTestExecutionStage.StaticAnalysis,
                Succeeded = !staticResult.HasBlockingError,
                Message = staticResult.Diagnostics.Count == 0
                    ? "静态分析通过（未发现位移/宏误用）"
                    : staticResult.HasBlockingError
                        ? $"静态分析失败：{staticResult.Diagnostics.Count} 条诊断"
                        : $"静态分析警告：{staticResult.Diagnostics.Count} 条诊断"
            });
            L(stages[^1].Message);
            if (staticResult.HasBlockingError)
            {
                run.Status = nameof(LlTestRunStatus.StaticAnalysisFailed);
                run.FailureReason = staticResult.Diagnostics
                    .Where(d => string.Equals(d.Severity, "Error", StringComparison.OrdinalIgnoreCase))
                    .Select(d => $"{d.RuleId}: {d.Description}")
                    .FirstOrDefault() ?? "静态分析失败";
                execLog.AppendLine(staticReport);
                return await FinishAsync(
                    run, stages, execLog, sw, null,
                    Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>(),
                    staticResult.Diagnostics);
            }

            if (staticResult.HasWarning)
                execLog.AppendLine(staticReport);

            // Isolated virtual MCU
            var mcuInfo = await _mcu.CreateAsync(new VirtualMcuCreateOptions
            {
                SdkProjectId = entity.SdkProjectId,
                ChipId = entity.ChipId,
                ChipModelName = entity.ChipModelName,
                DisplayName = $"TEST-{entity.Name}-{run.Id.ToString()[..8]}",
                ProtectUnmappedBitsAsReserved = false
            }, cancellationToken);
            await _mcu.InitializeAsync(mcuInfo.Id, cancellationToken);
            mcuId = mcuInfo.Id;
            run.VirtualMcuId = mcuId;

            foreach (var init in edit.InitialRegisters)
            {
                var v = TestHarnessGenerator.ParseUIntExpression(init.ValueHex);
                // Seed bypasses W1C (DISR/ISR etc.): normal Write would clear bits we intend to preload.
                await _mcu.SeedRegisterAsync(mcuId.Value, init.InstanceName, init.MemberName, v,
                    new VirtualAccessContext { LlFunctionName = "(init)", Note = "测试初始寄存器" }, cancellationToken);
            }

            var header = Path.GetFileName(entity.SourceFile ?? "tae32g58xx_ll_gpio.h");
            if (string.IsNullOrWhiteSpace(header)) header = "tae32g58xx_ll_gpio.h";

            // Recover params from signature when case JSON left them empty (old drafts).
            var defaultPeri = entity.PeripheralName ?? "PERI";
            edit.Parameters = TestHarnessGenerator.EnsureParameters(
                edit.Parameters, edit.FunctionSignature ?? entity.FunctionSignature, defaultPeri,
                entity.FunctionName).ToList();
            foreach (var p in edit.Parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
            {
                if (string.IsNullOrWhiteSpace(p.ValueExpression) || p.ValueExpression == "0")
                    p.ValueExpression = defaultPeri;
            }

            var periHint = edit.Parameters.FirstOrDefault(TestHarnessGenerator.IsPeripheralTypeDefPointer)?.ValueExpression
                           ?? defaultPeri;
            var virtualInstance = await VirtualMcuInstanceResolver.ResolveAsync(
                _mcu, mcuId!.Value, periHint, entity.PeripheralName, cancellationToken,
                entity.FunctionName);

            var harness = TestHarnessGenerator.Generate(
                entity.FunctionName,
                header,
                edit.Parameters,
                ReturnTypeOf(entity.FunctionSignature),
                periHint,
                edit.FunctionSignature ?? entity.FunctionSignature,
                edit.PreludeCalls);

            // Reject unsafe harness (unsupported pointer params)
            if (harness.Contains("return -2;"))
            {
                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = "Harness 无法物化指针参数（引擎缺陷，非被测 LL 语义）。";
                stages.Add(new LlTestStageResult
                {
                    Stage = LlTestExecutionStage.Compile,
                    Succeeded = false,
                    Message = run.FailureReason
                });
                return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }

            var work = Path.Combine(_workRoot, run.Id.ToString("N"));
            Directory.CreateDirectory(work);
            var harnessPath = Path.Combine(work, "harness.c");
            var dllPath = Path.Combine(work, "harness.dll");
            await File.WriteAllTextAsync(harnessPath, harness, cancellationToken);

            L("开始编译真实 LL 头文件内联函数…");
            var compile = await _compiler.CompileHarnessAsync(entity.SdkProjectId, harnessPath, dllPath,
                cancellationToken: cancellationToken);
            run.CompileLog = compile.Log;
            run.CompilerPath = env.ClangPath;
            run.CompileSucceeded = compile.Succeeded;
            stages.Add(new LlTestStageResult
            {
                Stage = LlTestExecutionStage.Compile,
                Succeeded = compile.Succeeded,
                Message = compile.Succeeded ? "编译通过" : string.Join("; ", compile.Errors)
            });
            L(compile.Succeeded ? "编译通过" : "编译失败: " + string.Join("; ", compile.Errors));

            if (!compile.Succeeded)
            {
                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = "编译失败：" + string.Join("; ", compile.Errors);
                return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }

            run.Status = nameof(LlTestRunStatus.Running);
            var timeout = request.TimeoutMs
                          ?? edit.Assertions.FirstOrDefault(a => a.Kind == LlAssertionKind.Timeout)?.TimeoutMs
                          ?? 10000;

            using var timeoutCts = CancellationTokenSource.CreateLinkedTokenSource(cancellationToken);
            timeoutCts.CancelAfter(timeout);

            uint? ret = null;
            Exception? execEx = null;
            // Timeout assertion must measure native execute (+ sync), not clang compile wall time.
            var nativeSw = Stopwatch.StartNew();
            try
            {
                using var host = new NativeTestHost();
                host.Load(compile.OutputDllPath!);
                var (ptr, size, map, layout) = await NativeTestHost.AllocateAndFillAsync(
                    _mcu, mcuId.Value, virtualInstance, timeoutCts.Token, entity.PeripheralName);
                try
                {
                    var focusInit = edit.InitialRegisters.FirstOrDefault();
                    var focusInst = focusInit?.InstanceName ?? virtualInstance;
                    var focusMem = focusInit?.MemberName ?? "";
                    L(layout.FormatDebug(focusInst, focusMem));

                    // Resolve expected absolute address for the focus register (SDK TypeDef path).
                    if (!string.IsNullOrWhiteSpace(focusMem))
                    {
                        var focusReg = await _mcu.GetRegisterAsync(
                            mcuId.Value, focusInst, focusMem, timeoutCts.Token);
                        if (focusReg?.AbsoluteAddress is uint abs)
                        {
                            var hostOff = (int)(abs - layout.ImageBase);
                            L($"Expected MCR0/Focus Address: 0x{abs:X8}");
                            L($"Native HRPWMx/PERIx Pointer: host image base (child peri buffer)");
                            L($"Native Focus Offset: +0x{hostOff:X} (abs=0x{abs:X8})");
                            L($"Virtual Register Address: 0x{abs:X8}");
                            L($"Virtual Initial Value: 0x{focusReg.CurrentValue:X8}");
                            if (hostOff >= 0 && map.TryGetValue(hostOff, out var slotKey))
                                L($"Host Map Slot: +0x{hostOff:X} → {slotKey}");
                            else
                                L($"Host Map Slot: MISSING for +0x{hostOff:X}（Native 写入将无法回读）");
                        }
                        else
                        {
                            L($"Virtual Register Address: （缺失 AbsoluteAddress）{focusInst}.{focusMem}");
                        }
                    }

                    var argValues = TestHarnessGenerator.BuildArgsValuesInHarnessOrder(
                        edit.Parameters, edit.PreludeCalls);
                    var blob = NativeTestHost.PackArgs(argValues);
                    var beforeExecute = NativeTestHost.SnapshotBuffer(ptr, map);
                    // Also snapshot TypeDef prefix so unmapped dirties are visible.
                    for (var off = 0; off < Math.Min(size, 0x1000); off += 4)
                    {
                        if (!beforeExecute.ContainsKey(off))
                            beforeExecute[off] = unchecked((uint)Marshal.ReadInt32(ptr, off));
                    }

                    L($"原生执行 {entity.FunctionName} @ virtual {virtualInstance} (hint={periHint}) …");
                    var (execRet, nrc) = await host.ExecuteAsync(
                            ptr, (uint)size, blob, timeoutCts.Token)
                        .ConfigureAwait(false);
                    ret = execRet;
                    if (nrc != 0)
                        throw new InvalidOperationException($"harness tae32_run 返回 {nrc}");

                    NativeTestHost.ApplyHostGpioBsrToDor(ptr, map);

                    var deltas = NativeTestHost.AnalyzeBufferDeltas(
                        ptr, size, map, beforeExecute, layout.ImageBase);
                    L(deltas.FormatDebug());
                    if (deltas.HasUnmappedWrites)
                    {
                        L("原因：Native 写入落在未映射偏移（宿主映像与 AbsoluteAddress 打包不一致）。");
                    }
                    else if (!deltas.HasMappedWrites)
                    {
                        L("原因：宿主缓冲区内映射槽位无变化（可能参数未生效，或读写偏移错误）。");
                    }

                    if (!string.IsNullOrWhiteSpace(focusMem))
                    {
                        var focusRegAfterHost = await _mcu.GetRegisterAsync(
                            mcuId.Value, focusInst, focusMem, timeoutCts.Token);
                        if (focusRegAfterHost?.AbsoluteAddress is uint abs2)
                        {
                            var hostOff = (int)(abs2 - layout.ImageBase);
                            if (hostOff >= 0 && hostOff + 4 <= size)
                            {
                                var hostVal = unchecked((uint)Marshal.ReadInt32(ptr, hostOff));
                                L($"Native Focus Word After: +0x{hostOff:X} = 0x{hostVal:X8}");
                            }
                        }
                    }

                    var ctx = new VirtualAccessContext
                    {
                        LlFunctionName = entity.FunctionName,
                        SourceFile = entity.SourceFile,
                        Note = "ll-native-write"
                    };
                    await NativeTestHost.SyncBufferToVirtualMcuAsync(
                        _mcu, mcuId.Value, virtualInstance, ptr, map, ctx, timeoutCts.Token, beforeExecute);

                    if (!string.IsNullOrWhiteSpace(focusMem))
                    {
                        var focusFinal = await _mcu.GetRegisterAsync(
                            mcuId.Value, focusInst, focusMem, timeoutCts.Token);
                        if (focusFinal is not null)
                            L($"Virtual Final Value: 0x{focusFinal.CurrentValue:X8}");
                    }

                    run.ExecuteCompleted = true;
                    run.HardwareBehaviorSimulated = true;
                    var execMsg = $"原生执行完成 return=0x{ret:X8}";
                    if (deltas.HasUnmappedWrites)
                        execMsg += $"；检测到 {deltas.UnmappedChanges.Count} 处未映射写入";
                    stages.Add(new LlTestStageResult
                    {
                        Stage = LlTestExecutionStage.NativeExecute,
                        Succeeded = true,
                        Message = execMsg
                    });
                    stages.Add(new LlTestStageResult
                    {
                        Stage = LlTestExecutionStage.HardwareBehaviorSimulated,
                        Succeeded = true,
                        Message = "寄存器已同步到虚拟 MCU（含 GPIO BSR→DOR 等已实现行为）"
                    });
                }
                finally
                {
                    Marshal.FreeHGlobal(ptr);
                }
            }
            catch (OperationCanceledException) when (!cancellationToken.IsCancellationRequested)
            {
                nativeSw.Stop();
                run.Status = nameof(LlTestRunStatus.Timeout);
                run.FailureReason = $"原生执行超过 {timeout} ms";
                stages.Add(new LlTestStageResult { Stage = LlTestExecutionStage.NativeExecute, Succeeded = false, Message = run.FailureReason });
                return await FinishAsync(run, stages, execLog, sw, ret, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }
            catch (TimeoutException tex)
            {
                nativeSw.Stop();
                run.Status = nameof(LlTestRunStatus.Timeout);
                run.FailureReason = tex.Message;
                stages.Add(new LlTestStageResult
                {
                    Stage = LlTestExecutionStage.NativeExecute,
                    Succeeded = false,
                    Message = run.FailureReason
                });
                return await FinishAsync(
                    run, stages, execLog, sw, ret,
                    Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }
            catch (Exception ex)
            {
                execEx = ex;
                L("执行异常: " + ex.Message);
                stages.Add(new LlTestStageResult { Stage = LlTestExecutionStage.NativeExecute, Succeeded = false, Message = ex.Message });
            }
            finally
            {
                nativeSw.Stop();
            }

            // Prefer LL-attributed accesses for the run report (exclude test preload / unchanged sync).
            var trace = mcuId is Guid mid
                ? await _mcu.GetAccessTraceAsync(mid, new VirtualAccessFilter
                {
                    LlFunctionName = entity.FunctionName,
                    Take = 500
                }, cancellationToken)
                : Array.Empty<VirtualAccessRecord>();

            var assertions = await AssertionEvaluator.EvaluateAsync(
                _mcu, mcuId ?? Guid.Empty, edit.Assertions, ret, trace, execEx,
                (int)nativeSw.ElapsedMilliseconds, cancellationToken);

            // Timeout is recorded but alone never counts as semantic Pass
            // (DISR=0 / empty preload can make buggy LL also "succeed" on Timeout-only drafts).
            var hasSemanticAssert = assertions.Any(a => a.Kind != LlAssertionKind.Timeout);
            var timeoutOnly = assertions.Count == 0 || !hasSemanticAssert;
            var allAssertOk = assertions.Count > 0 && assertions.All(a => a.Passed);
            run.AssertionsPassed = allAssertOk && hasSemanticAssert;

            stages.Add(new LlTestStageResult
            {
                Stage = LlTestExecutionStage.Assert,
                Succeeded = run.AssertionsPassed || (timeoutOnly && allAssertOk),
                Message = timeoutOnly && allAssertOk
                    ? "仅超时断言通过（无语义断言，不计 Passed）"
                    : run.AssertionsPassed
                        ? "断言全部通过（虚拟环境）"
                        : "存在失败断言（虚拟环境）"
            });

            if (execEx is not null && LlNativeEligibility.IsHostAddressFault(execEx))
            {
                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = "宿主执行故障（AccessViolation/非法地址），非断言失败。"
                    + " 需补 host shim 或虚拟映像；" + execEx.Message;
            }
            else if (execEx is not null)
            {
                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = execEx.Message;
            }
            else if (!allAssertOk)
            {
                run.Status = nameof(LlTestRunStatus.Failed);
                run.FailureReason = string.Join("; ", assertions.Where(a => !a.Passed).Select(a => a.Message));
            }
            else if (timeoutOnly)
            {
                run.Status = nameof(LlTestRunStatus.Skipped);
                run.FailureReason =
                    "仅超时断言通过，无返回值/寄存器等语义校验，不计 Passed。请重新生成用例（read/write/enable/disable-check）。";
            }
            else
            {
                run.Status = nameof(LlTestRunStatus.Passed);
            }

            run.ReturnValueText = ret is uint r ? $"0x{r:X8}" : null;
            L($"结果 {run.Status}");
            return await FinishAsync(run, stages, execLog, sw, ret, assertions, trace);
        }
        catch (OperationCanceledException) when (cancellationToken.IsCancellationRequested)
        {
            run.Status = nameof(LlTestRunStatus.Cancelled);
            run.FailureReason = "用户取消";
            return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
        }
        catch (Exception ex)
        {
            run.Status = nameof(LlTestRunStatus.Error);
            run.FailureReason = ex.Message;
            L(ex.ToString());
            return await FinishAsync(run, stages, execLog, sw, null, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
        }
        finally
        {
            if (mcuId is Guid id)
            {
                try { await _mcu.DestroyAsync(id, CancellationToken.None); } catch { /* ignore */ }
            }
        }
    }

    private async Task<LlTestRunResult> FinishAsync(
        LlTestRun run,
        List<LlTestStageResult> stages,
        StringBuilder execLog,
        Stopwatch sw,
        uint? ret,
        IReadOnlyList<LlTestAssertionResult> assertions,
        IReadOnlyList<VirtualAccessRecord> trace,
        IReadOnlyList<StaticAnalysisDiagnostic>? staticDiagnostics = null)
    {
        sw.Stop();
        run.DurationMs = (int)sw.ElapsedMilliseconds;
        run.FinishedAtUtc = DateTime.UtcNow;
        run.ExecutionLog = execLog.ToString();
        run.StagesJson = LlTestJson.Serialize(stages);
        run.AssertionResultsJson = LlTestJson.Serialize(assertions);
        run.AccessTraceJson = LlTestJson.Serialize(trace);
        if (staticDiagnostics is { Count: > 0 } && string.IsNullOrWhiteSpace(run.StaticAnalysisJson))
            run.StaticAnalysisJson = LlTestJson.Serialize(staticDiagnostics);
        run.ReturnValueText ??= ret is uint r ? $"0x{r:X8}" : run.ReturnValueText;
        await _store.SaveRunAsync(run);

        var diags = staticDiagnostics
                    ?? (string.IsNullOrWhiteSpace(run.StaticAnalysisJson)
                        ? Array.Empty<StaticAnalysisDiagnostic>()
                        : LlTestJson.Deserialize<List<StaticAnalysisDiagnostic>>(run.StaticAnalysisJson!)
                          ?? new List<StaticAnalysisDiagnostic>());

        return new LlTestRunResult
        {
            RunId = run.Id,
            TestCaseId = run.LlTestCaseId,
            Status = Enum.TryParse<LlTestRunStatus>(run.Status, out var st) ? st : LlTestRunStatus.Error,
            CompileSucceeded = run.CompileSucceeded,
            ExecuteCompleted = run.ExecuteCompleted,
            AssertionsPassed = run.AssertionsPassed,
            HardwareBehaviorSimulated = run.HardwareBehaviorSimulated,
            FailureReason = run.FailureReason,
            ReturnValueText = run.ReturnValueText,
            CompileLog = run.CompileLog ?? "",
            ExecutionLog = run.ExecutionLog ?? "",
            StaticAnalysisJson = run.StaticAnalysisJson ?? "",
            AssertionResults = assertions,
            Stages = stages,
            AccessTrace = trace,
            StaticAnalysisDiagnostics = diags,
            DurationMs = run.DurationMs
        };
    }

    private static string? ResolveLlSourcePath(string? filePath, string? sdkRoot)
    {
        if (string.IsNullOrWhiteSpace(filePath)) return null;
        if (File.Exists(filePath)) return Path.GetFullPath(filePath);

        var normalized = filePath.Replace('/', Path.DirectorySeparatorChar);
        if (!string.IsNullOrWhiteSpace(sdkRoot))
        {
            var underSdk = Path.GetFullPath(Path.Combine(sdkRoot, normalized));
            if (File.Exists(underSdk)) return underSdk;
            var byName = Path.GetFileName(normalized);
            try
            {
                var hit = Directory.EnumerateFiles(sdkRoot, byName, SearchOption.AllDirectories)
                    .FirstOrDefault(p => p.Contains($"{Path.DirectorySeparatorChar}LL{Path.DirectorySeparatorChar}",
                        StringComparison.OrdinalIgnoreCase));
                if (hit is not null) return hit;
            }
            catch
            {
                /* ignore */
            }
        }

        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 10; i++)
        {
            var cand = Path.GetFullPath(Path.Combine(dir, normalized));
            if (File.Exists(cand)) return cand;
            var sdkContent = Path.Combine(dir, "SDKContent");
            if (Directory.Exists(sdkContent))
            {
                try
                {
                    var hit = Directory.EnumerateFiles(sdkContent, Path.GetFileName(normalized), SearchOption.AllDirectories)
                        .FirstOrDefault(p => p.Contains($"{Path.DirectorySeparatorChar}LL{Path.DirectorySeparatorChar}",
                            StringComparison.OrdinalIgnoreCase));
                    if (hit is not null) return hit;
                }
                catch
                {
                    /* ignore */
                }
            }

            var parent = Path.GetDirectoryName(dir);
            if (string.IsNullOrEmpty(parent) || parent == dir) break;
            dir = parent;
        }

        return null;
    }

    private static string? ReturnTypeOf(string? signature)
    {
        if (string.IsNullOrWhiteSpace(signature)) return null;
        var idx = signature.IndexOf('(');
        if (idx <= 0) return null;
        var left = signature[..idx].Trim();
        var parts = left.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        return parts.Length >= 2 ? string.Join(' ', parts.Take(parts.Length - 1)) : parts.FirstOrDefault();
    }
}
