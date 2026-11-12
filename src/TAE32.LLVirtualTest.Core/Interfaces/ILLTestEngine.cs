using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>
/// Phase-6 LL automated test engine: compile real SDK LL into a host harness and execute against virtual MCU.
/// Results are virtual-environment verification — never claim real hardware validation.
/// </summary>
public interface ILLTestEngine
{
    Task<CompilerEnvironmentInfo> CheckCompilerAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesAsync(
        Guid llFunctionId,
        CancellationToken cancellationToken = default);

    /// <summary>Generate cases for all inline LL functions under a peripheral (capped).</summary>
    Task<IReadOnlyList<LlTestCaseEditModel>> GenerateCasesForPeripheralAsync(
        Guid sdkProjectId,
        string peripheralName,
        int maxFunctions = 40,
        CancellationToken cancellationToken = default);

    Task<LlTestRunResult> RunCaseAsync(
        LlTestRunRequest request,
        IProgress<string>? log = null,
        CancellationToken cancellationToken = default);

    Task<IReadOnlyList<LlTestRunResult>> RunManyAsync(
        IEnumerable<Guid> testCaseIds,
        IProgress<string>? log = null,
        CancellationToken cancellationToken = default);

    /// <summary>Legacy Phase-2 stub: run all Ready cases for a project.</summary>
    Task RunAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);
}
