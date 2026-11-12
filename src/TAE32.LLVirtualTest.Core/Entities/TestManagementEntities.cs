namespace TAE32.LLVirtualTest.Core.Entities;

public class TestPlan
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? ChipId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? Description { get; set; }
    public string? SdkVersion { get; set; }
    public string? ChipModelName { get; set; }
    public string? PeripheralFilter { get; set; }
    public string? FunctionFilter { get; set; }
    public string? TestType { get; set; }
    public string Status { get; set; } = "Active"; // Active / Archived
    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }
    public DateTime? ArchivedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public Chip? Chip { get; set; }
    public ICollection<TestSuite> Suites { get; set; } = new List<TestSuite>();
    public ICollection<TestBatchRun> BatchRuns { get; set; } = new List<TestBatchRun>();
}

public class TestSuite
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? TestPlanId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? Description { get; set; }
    public string? PeripheralName { get; set; }
    public string Status { get; set; } = "Active";
    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? UpdatedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public TestPlan? TestPlan { get; set; }
    public ICollection<TestSuiteCase> Cases { get; set; } = new List<TestSuiteCase>();
}

public class TestSuiteCase
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid TestSuiteId { get; set; }
    public Guid LlTestCaseId { get; set; }
    public int SortOrder { get; set; }

    public TestSuite? TestSuite { get; set; }
    public LlTestCase? TestCase { get; set; }
}

public class TestBatchRun
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? TestPlanId { get; set; }
    public Guid? TestSuiteId { get; set; }
    public string ScopeKind { get; set; } = "Manual"; // Peripheral / Chip / Suite / Plan / FailedRetry / Listed
    public string? ScopeValue { get; set; }
    public string Status { get; set; } = "Pending";
    public string? ToolVersion { get; set; }
    public string? CompilerVersion { get; set; }
    public string? SdkVersion { get; set; }
    public string? ChipModelName { get; set; }
    public int TotalCount { get; set; }
    public int PassedCount { get; set; }
    public int FailedCount { get; set; }
    public int ErrorCount { get; set; }
    public int SkippedCount { get; set; }
    public int TimeoutCount { get; set; }
    public int CancelledCount { get; set; }
    public int CompileFailCount { get; set; }
    public double AverageDurationMs { get; set; }
    public string? LogDirectory { get; set; }
    public string? Notes { get; set; }
    public string CaseRunIdsJson { get; set; } = "[]";
    public DateTime StartedAtUtc { get; set; } = DateTime.UtcNow;
    public DateTime? FinishedAtUtc { get; set; }

    public SdkProject? SdkProject { get; set; }
    public TestPlan? TestPlan { get; set; }
    public TestSuite? TestSuite { get; set; }
}

public class TestReportArtifact
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? TestBatchRunId { get; set; }
    public string Format { get; set; } = "Html"; // Html / Pdf / Excel / Csv
    public string FilePath { get; set; } = string.Empty;
    public string Title { get; set; } = string.Empty;
    public DateTime CreatedAtUtc { get; set; } = DateTime.UtcNow;
    public string Disclaimer { get; set; } =
        "本报告基于虚拟 MCU 软件测试，不等同于真实硬件测试。";

    public SdkProject? SdkProject { get; set; }
    public TestBatchRun? BatchRun { get; set; }
}
