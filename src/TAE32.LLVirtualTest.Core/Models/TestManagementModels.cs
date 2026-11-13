using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.Core.Models;

public sealed class TestPlanEditModel
{
    public Guid? Id { get; set; }
    public Guid SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? Description { get; set; }
    public string? SdkVersion { get; set; }
    public string? ChipModelName { get; set; }
    public string? PeripheralFilter { get; set; }
    public string? FunctionFilter { get; set; }
    public string? TestType { get; set; }
    public string Status { get; set; } = "Active";
}

public sealed class TestSuiteEditModel
{
    public Guid? Id { get; set; }
    public Guid SdkProjectId { get; set; }
    public Guid? TestPlanId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? Description { get; set; }
    public string? PeripheralName { get; set; }
    public string Status { get; set; } = "Active";
    public List<Guid> TestCaseIds { get; set; } = new();
}

public sealed class TestBatchRunRequest
{
    public Guid SdkProjectId { get; set; }
    public Guid? TestPlanId { get; set; }
    public Guid? TestSuiteId { get; set; }
    public string ScopeKind { get; set; } = "Listed";
    public string? ScopeValue { get; set; }
    public IReadOnlyList<Guid>? ExplicitCaseIds { get; set; }
    public bool RetryFailedOnly { get; set; }
    public Guid? SourceBatchRunId { get; set; }
}

public sealed class TestBatchProgress
{
    public Guid BatchRunId { get; set; }
    public int Total { get; set; }
    public int Completed { get; set; }
    public string CurrentCaseName { get; set; } = string.Empty;
    public string Message { get; set; } = string.Empty;
    public double Percent => Total <= 0 ? 0 : Completed * 100.0 / Total;
}

public sealed class TestStatistics
{
    public int CaseTotal { get; set; }
    public int ExecutedRuns { get; set; }
    public int Passed { get; set; }
    public int Failed { get; set; }
    public int Error { get; set; }
    public int Skipped { get; set; }
    public int Timeout { get; set; }
    public int Cancelled { get; set; }
    public int CompileFailed { get; set; }
    public double PassRate { get; set; }
    public double CompileFailRate { get; set; }
    public double AverageDurationMs { get; set; }
}

public sealed class CoverageStats
{
    /// <summary>Denominator source, e.g. "inline LL functions in project".</summary>
    public string FunctionCoverageDenomination { get; set; } = string.Empty;
    public int FunctionsTotal { get; set; }
    public int FunctionsCoveredByCases { get; set; }
    public double? FunctionCoveragePercent { get; set; }

    public string PeripheralCoverageDenomination { get; set; } = string.Empty;
    public int PeripheralsTotal { get; set; }
    public int PeripheralsCoveredByCases { get; set; }
    public double? PeripheralCoveragePercent { get; set; }

    public string RegisterAccessCoverageDenomination { get; set; } = string.Empty;
    public int RegistersReferencedInParse { get; set; }
    public int RegistersTouchedInRuns { get; set; }
    public double? RegisterAccessCoveragePercent { get; set; }

    public string BitFieldCoverageDenomination { get; set; } = string.Empty;
    public int BitFieldsTotal { get; set; }
    public int BitFieldsAsserted { get; set; }
    public double? BitFieldCoveragePercent { get; set; }

    public string CaseCoverageDenomination { get; set; } = string.Empty;
    public int CasesTotal { get; set; }
    public int CasesExecutedAtLeastOnce { get; set; }
    public double? CaseCoveragePercent { get; set; }

    public string Notes { get; set; } =
        "覆盖率仅基于数据库中已有真实数据；缺失解析/执行证据时对应项为 null，不伪造。";
}

/// <summary>报告页：所选批次将导出的内容预览（非全量，仅前若干条）。</summary>
public sealed class BatchExportPreviewModel
{
    public Guid BatchRunId { get; set; }
    public int RegisteredRunCount { get; set; }
    public int RunsFoundInDb { get; set; }
    public string Status { get; set; } = string.Empty;
    public string ScopeKind { get; set; } = string.Empty;
    public string? ScopeValue { get; set; }
    public DateTime StartedAtUtc { get; set; }
    public int PassedCount { get; set; }
    public int FailedCount { get; set; }
    public int ErrorCount { get; set; }
    public int SkippedCount { get; set; }
    public int TimeoutCount { get; set; }
    public IReadOnlyList<BatchExportPreviewRow> PreviewRows { get; set; } = Array.Empty<BatchExportPreviewRow>();
}

public sealed class BatchExportPreviewRow
{
    public int Index { get; set; }
    public string CaseName { get; set; } = string.Empty;
    public string FunctionName { get; set; } = string.Empty;
    public string Status { get; set; } = string.Empty;
    public int DurationMs { get; set; }
}

public sealed class FailureAnalysisItem
{
    public Guid RunId { get; set; }
    public Guid TestCaseId { get; set; }
    public string CaseName { get; set; } = string.Empty;
    public string FunctionName { get; set; } = string.Empty;
    public string? SourceFile { get; set; }
    public string Status { get; set; } = string.Empty;
    public string? FailureReason { get; set; }
    public bool CompileSucceeded { get; set; }
    public string? CompileLogExcerpt { get; set; }
    public string? AssertionResultsJson { get; set; }
    public string? AccessTraceJson { get; set; }
    public string? RelatedRegisters { get; set; }
    public DateTime StartedAtUtc { get; set; }
    public int DurationMs { get; set; }
    public string? ReturnValueText { get; set; }
    public bool AssertionsPassed { get; set; }
    public string? ExecutionLogExcerpt { get; set; }
    /// <summary>用例调用参数 JSON（含 prelude）。</summary>
    public string? ParametersJson { get; set; }
    /// <summary>运行前预置寄存器 JSON。</summary>
    public string? InitialRegistersJson { get; set; }
    /// <summary>可读：每次写/改位的值（before→after）。</summary>
    public string? RegisterWritesSummary { get; set; }
}

public sealed class TestReportRequest
{
    public Guid SdkProjectId { get; set; }
    public Guid? BatchRunId { get; set; }
    public TestReportFormat Format { get; set; } = TestReportFormat.Html;
    /// <summary>默认跟批次选择：有 BatchRunId 则导出该批全部运行；否则每用例最新。</summary>
    public TestReportRunScope RunScope { get; set; } = TestReportRunScope.Auto;
    public string? OutputDirectory { get; set; }
    public string? Title { get; set; }
}

public sealed class TestReportResult
{
    public Guid ArtifactId { get; set; }
    public string Format { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public string Message { get; set; } = string.Empty;
    /// <summary>本次报告内嵌的运行明细条数（与汇总表一致）。</summary>
    public int RunDetailCount { get; set; }
    /// <summary>选中批次登记的 TotalCount（仅批次导出时有值）。</summary>
    public int? BatchExpectedRunCount { get; set; }
    public TestReportRunScope EffectiveRunScope { get; set; }
}

public enum TestReportRunScope
{
    /// <summary>有 BatchRunId 则用批次，否则每用例最新。</summary>
    Auto,
    /// <summary>忽略批次，导出项目内每个用例最新一次运行（推荐全量验收）。</summary>
    ProjectLatestPerCase,
    /// <summary>仅当前 BatchRunId 内的运行（需已选批次）。</summary>
    SelectedBatchOnly,
    /// <summary>项目内全部运行记录（含历史重复，体积大）。</summary>
    ProjectAllRuns
}

public enum TestReportFormat
{
    Html,
    Pdf,
    Excel,
    Csv
}
