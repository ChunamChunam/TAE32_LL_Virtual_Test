using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Models;

public sealed class LlTestParameterValue
{
    public string Name { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    /// <summary>C expression or literal from real SDK (e.g. LL_GPIO_PIN_0, GPIOA, 0x1).</summary>
    public string ValueExpression { get; set; } = string.Empty;
    public string? RuleSource { get; set; }
}

public sealed class LlTestInitialRegister
{
    public string InstanceName { get; set; } = string.Empty;
    public string MemberName { get; set; } = string.Empty;
    public string ValueHex { get; set; } = "0x0";
}

public sealed class LlTestAssertionSpec
{
    public string Id { get; set; } = Guid.NewGuid().ToString("N");
    public LlAssertionKind Kind { get; set; }
    public LlAssertionRuleSource RuleSource { get; set; } = LlAssertionRuleSource.Manual;
    public string? RuleSourceDetail { get; set; }
    public string? InstanceName { get; set; }
    public string? MemberName { get; set; }
    public string? BitFieldName { get; set; }
    public string? ExpectedExpression { get; set; }
    public string? ExpectedHex { get; set; }
    public uint? ExpectedMask { get; set; }
    public IReadOnlyList<string>? ExpectedAccessOrder { get; set; }
    public int? TimeoutMs { get; set; }
}

public sealed class LlTestAssertionResult
{
    public string AssertionId { get; set; } = string.Empty;
    public LlAssertionKind Kind { get; set; }
    public bool Passed { get; set; }
    public string? Expected { get; set; }
    public string? Actual { get; set; }
    public string? Message { get; set; }
    public LlAssertionRuleSource RuleSource { get; set; }
    public string? RuleSourceDetail { get; set; }
}

public sealed class LlTestStageResult
{
    public LlTestExecutionStage Stage { get; set; }
    public bool Succeeded { get; set; }
    public string Message { get; set; } = string.Empty;
}

public sealed class CompilerEnvironmentInfo
{
    public bool ClangFound { get; set; }
    public string? ClangPath { get; set; }
    public string? ClangVersion { get; set; }
    public IReadOnlyList<string> IncludePaths { get; set; } = Array.Empty<string>();
    public IReadOnlyList<string> Defines { get; set; } = Array.Empty<string>();
    public IReadOnlyList<string> Missing { get; set; } = Array.Empty<string>();
    public string Summary { get; set; } = string.Empty;
}

public sealed class CompileJobResult
{
    public bool Succeeded { get; set; }
    public int ExitCode { get; set; }
    public string Log { get; set; } = string.Empty;
    public string? OutputDllPath { get; set; }
    public string? HarnessPath { get; set; }
    public IReadOnlyList<string> Errors { get; set; } = Array.Empty<string>();
}

public sealed class EmbeddedClangResult
{
    public bool Succeeded { get; set; }
    public string? ClangPath { get; set; }
    public string Message { get; set; } = string.Empty;
    public bool AlreadyPresent { get; set; }
}

public sealed class LlTestRunRequest
{
    public Guid TestCaseId { get; set; }
    public int? TimeoutMs { get; set; }
    public bool SkipNativeIfNoCompiler { get; set; } = true;
}

public sealed class LlTestRunResult
{
    public Guid RunId { get; set; }
    public Guid TestCaseId { get; set; }
    public LlTestRunStatus Status { get; set; }
    public bool CompileSucceeded { get; set; }
    public bool ExecuteCompleted { get; set; }
    public bool AssertionsPassed { get; set; }
    public bool HardwareBehaviorSimulated { get; set; }
    public string? FailureReason { get; set; }
    public string? ReturnValueText { get; set; }
    public string CompileLog { get; set; } = string.Empty;
    public string ExecutionLog { get; set; } = string.Empty;
    public string StaticAnalysisJson { get; set; } = string.Empty;
    public IReadOnlyList<LlTestAssertionResult> AssertionResults { get; set; } = Array.Empty<LlTestAssertionResult>();
    public IReadOnlyList<LlTestStageResult> Stages { get; set; } = Array.Empty<LlTestStageResult>();
    public IReadOnlyList<VirtualAccessRecord> AccessTrace { get; set; } = Array.Empty<VirtualAccessRecord>();
    public IReadOnlyList<StaticAnalysisDiagnostic> StaticAnalysisDiagnostics { get; set; } = Array.Empty<StaticAnalysisDiagnostic>();
    public int DurationMs { get; set; }
}

/// <summary>One LL call step (used as write prelude before a read, etc.).</summary>
public sealed class LlTestCallStep
{
    public string FunctionName { get; set; } = string.Empty;
    public List<LlTestParameterValue> Parameters { get; set; } = new();
}

public sealed class LlTestCaseEditModel
{
    public Guid? Id { get; set; }
    public Guid SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public Guid? LlFunctionId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? ChipModelName { get; set; }
    public string? PeripheralName { get; set; }
    public string FunctionName { get; set; } = string.Empty;
    public string? FunctionSignature { get; set; }
    public string? SourceFile { get; set; }
    public string Status { get; set; } = "Draft";
    public List<LlTestParameterValue> Parameters { get; set; } = new();
    /// <summary>Optional calls executed before FunctionName in the same harness (e.g. Write then Read).</summary>
    public List<LlTestCallStep> PreludeCalls { get; set; } = new();
    public List<LlTestInitialRegister> InitialRegisters { get; set; } = new();
    public List<LlTestAssertionSpec> Assertions { get; set; } = new();
    public string? Notes { get; set; }
    public bool IsAutoGenerated { get; set; }
}
