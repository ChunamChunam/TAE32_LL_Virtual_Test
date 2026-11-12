namespace TAE32.LLVirtualTest.Core.Entities;

public class LlParseDiagnostic
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public Guid? LlFunctionId { get; set; }
    public string Severity { get; set; } = "Warning";
    public string Category { get; set; } = "General";
    public string Message { get; set; } = string.Empty;
    public string? FilePath { get; set; }
    public int Line { get; set; }
    public int Column { get; set; }
    public string? Detail { get; set; }
}
