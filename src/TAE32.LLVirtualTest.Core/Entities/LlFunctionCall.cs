namespace TAE32.LLVirtualTest.Core.Entities;

public class LlFunctionCall
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid LlFunctionId { get; set; }
    public string CalleeName { get; set; } = string.Empty;
    public string CalleeKind { get; set; } = "Unknown";
    public string? CallFile { get; set; }
    public int CallLine { get; set; }
    public int CallCount { get; set; } = 1;
    public string? CalleeChip { get; set; }
    public string? CalleePeripheral { get; set; }

    public LlFunction? LlFunction { get; set; }
}
