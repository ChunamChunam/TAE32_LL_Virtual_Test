namespace TAE32.LLVirtualTest.Core.Entities;

public class LlRegisterAccess
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid LlFunctionId { get; set; }
    public string AccessKind { get; set; } = string.Empty;
    public string? Expression { get; set; }
    public string? RegisterPath { get; set; }
    public string? MacroName { get; set; }
    public int StartLine { get; set; }
    public int EndLine { get; set; }
    public string? AstKind { get; set; }

    public LlFunction? LlFunction { get; set; }
}
