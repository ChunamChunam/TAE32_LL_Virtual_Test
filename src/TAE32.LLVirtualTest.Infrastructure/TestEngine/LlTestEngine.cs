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
    private readonly string _workRoot;

    public LlTestEngine(
        ICompilerService compiler,
        ILlTestCaseStore store,
        IVirtualMcuService mcu,
        ISdkProjectService projects,
        IDbContextFactory<AppDbContext> dbFactory,
        LlTestCaseGenerator generator)
    {
        _compiler = compiler;
        _store = store;
        _mcu = mcu;
        _projects = projects;
        _dbFactory = dbFactory;
        _generator = generator;
        _workRoot = Path.Combine(Path.GetTempPath(), "tae32_ll_test_work");
        Directory.CreateDirectory(_workRoot);
    }

    public Task<CompilerEnvironmentInfo> CheckCompilerAsync(Guid sdkProjectId, CancellationToken cancellationToken = default)
        => _compiler.CheckEnvironmentAsync(sdkProjectId, cancellationToken);

    public Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesAsync(
        Guid llFunctionId, CancellationToken cancellationToken = default)
        => _generator.GenerateAsync(llFunctionId, cancellationToken);

    public Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesForPeripheralAsync(
        Guid sdkProjectId, string peripheralName, int maxFunctions = 40, CancellationToken cancellationToken = default)
        => _generator.GenerateForPeripheralAsync(sdkProjectId, peripheralName, maxFunctions, cancellationToken);

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
            results.Add(await RunCaseAsync(new LlTestRunRequest { TestCaseId = id }, log, cancellationToken));
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
                await _mcu.WriteAsync(mcuId.Value, init.InstanceName, init.MemberName, v,
                    new VirtualAccessContext { LlFunctionName = "(init)", Note = "测试初始寄存器" }, cancellationToken);
            }

            var header = Path.GetFileName(entity.SourceFile ?? "tae32g58xx_ll_gpio.h");
            if (string.IsNullOrWhiteSpace(header)) header = "tae32g58xx_ll_gpio.h";

            // Recover params from signature when case JSON left them empty (old drafts).
            var defaultPeri = entity.PeripheralName ?? "PERI";
            edit.Parameters = TestHarnessGenerator.EnsureParameters(
                edit.Parameters, edit.FunctionSignature ?? entity.FunctionSignature, defaultPeri).ToList();
            foreach (var p in edit.Parameters.Where(TestHarnessGenerator.IsPeripheralTypeDefPointer))
            {
                if (string.IsNullOrWhiteSpace(p.ValueExpression) || p.ValueExpression == "0")
                    p.ValueExpression = defaultPeri;
            }

            var periHint = edit.Parameters.FirstOrDefault(TestHarnessGenerator.IsPeripheralTypeDefPointer)?.ValueExpression
                           ?? defaultPeri;

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
                run.Status = nameof(LlTestRunStatus.Skipped);
                run.FailureReason = "函数签名含宿主无法安全物化的指针参数，已拒绝原生执行。";
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
            try
            {
                using var host = new NativeTestHost();
                host.Load(compile.OutputDllPath!);
                var (ptr, size, map) = await NativeTestHost.AllocateAndFillAsync(_mcu, mcuId.Value, periHint, timeoutCts.Token);
                try
                {
                    var ordered = TestHarnessGenerator.BuildArgsBlob(edit.Parameters, edit.PreludeCalls);
                    var blob = NativeTestHost.PackArgs(ordered);
                    L($"原生执行 {entity.FunctionName} @ virtual {periHint} …");
                    ret = host.Execute(ptr, (uint)size, blob, out var nrc);
                    if (nrc != 0)
                        throw new InvalidOperationException($"harness tae32_run 返回 {nrc}");

                    var ctx = new VirtualAccessContext
                    {
                        LlFunctionName = entity.FunctionName,
                        SourceFile = entity.SourceFile,
                        Note = "native-harness-sync"
                    };
                    await NativeTestHost.SyncBufferToVirtualMcuAsync(_mcu, mcuId.Value, periHint, ptr, map, ctx, timeoutCts.Token);
                    run.ExecuteCompleted = true;
                    run.HardwareBehaviorSimulated = true;
                    stages.Add(new LlTestStageResult
                    {
                        Stage = LlTestExecutionStage.NativeExecute,
                        Succeeded = true,
                        Message = $"原生执行完成 return=0x{ret:X8}"
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
                run.Status = nameof(LlTestRunStatus.Timeout);
                run.FailureReason = $"执行超过 {timeout} ms";
                stages.Add(new LlTestStageResult { Stage = LlTestExecutionStage.NativeExecute, Succeeded = false, Message = run.FailureReason });
                return await FinishAsync(run, stages, execLog, sw, ret, Array.Empty<LlTestAssertionResult>(), Array.Empty<VirtualAccessRecord>());
            }
            catch (Exception ex)
            {
                execEx = ex;
                L("执行异常: " + ex.Message);
                stages.Add(new LlTestStageResult { Stage = LlTestExecutionStage.NativeExecute, Succeeded = false, Message = ex.Message });
            }

            var trace = mcuId is Guid mid
                ? await _mcu.GetAccessTraceAsync(mid, new VirtualAccessFilter { Take = 500 }, cancellationToken)
                : Array.Empty<VirtualAccessRecord>();

            var assertions = await AssertionEvaluator.EvaluateAsync(
                _mcu, mcuId ?? Guid.Empty, edit.Assertions, ret, trace, execEx, (int)sw.ElapsedMilliseconds, cancellationToken);
            run.AssertionsPassed = assertions.Count == 0 || assertions.All(a => a.Passed);
            stages.Add(new LlTestStageResult
            {
                Stage = LlTestExecutionStage.Assert,
                Succeeded = run.AssertionsPassed,
                Message = run.AssertionsPassed ? "断言全部通过（虚拟环境）" : "存在失败断言（虚拟环境）"
            });

            if (execEx is not null)
            {
                run.Status = nameof(LlTestRunStatus.Error);
                run.FailureReason = execEx.Message;
            }
            else if (!run.AssertionsPassed)
            {
                run.Status = nameof(LlTestRunStatus.Failed);
                run.FailureReason = string.Join("; ", assertions.Where(a => !a.Passed).Select(a => a.Message));
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
        IReadOnlyList<VirtualAccessRecord> trace)
    {
        sw.Stop();
        run.DurationMs = (int)sw.ElapsedMilliseconds;
        run.FinishedAtUtc = DateTime.UtcNow;
        run.ExecutionLog = execLog.ToString();
        run.StagesJson = LlTestJson.Serialize(stages);
        run.AssertionResultsJson = LlTestJson.Serialize(assertions);
        run.AccessTraceJson = LlTestJson.Serialize(trace);
        run.ReturnValueText ??= ret is uint r ? $"0x{r:X8}" : run.ReturnValueText;
        await _store.SaveRunAsync(run);

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
            AssertionResults = assertions,
            Stages = stages,
            AccessTrace = trace,
            DurationMs = run.DurationMs
        };
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
