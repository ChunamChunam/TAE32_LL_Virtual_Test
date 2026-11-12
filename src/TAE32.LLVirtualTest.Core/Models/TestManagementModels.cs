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
}

public sealed class TestReportRequest
{
    public Guid SdkProjectId { get; set; }
    public Guid? BatchRunId { get; set; }
    public TestReportFormat Format { get; set; } = TestReportFormat.Html;
    public string? OutputDirectory { get; set; }
    public string? Title { get; set; }
}

public sealed class TestReportResult
{
    public Guid ArtifactId { get; set; }
    public string Format { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public string Message { get; set; } = string.Empty;
}

public enum TestReportFormat
{
    Html,
    Pdf,
    Excel,
    Csv
}
