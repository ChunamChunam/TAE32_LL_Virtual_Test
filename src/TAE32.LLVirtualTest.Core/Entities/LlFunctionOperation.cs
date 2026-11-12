namespace TAE32.LLVirtualTest.Core.Entities;

public class LlFunctionOperation
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid LlFunctionId { get; set; }
    public string OpKind { get; set; } = string.Empty;
    public int Sequence { get; set; }
    public string? SourceText { get; set; }
    public int StartLine { get; set; }
    public int EndLine { get; set; }
    public string? AstKind { get; set; }
    public Guid? ParentOpId { get; set; }

    public LlFunction? LlFunction { get; set; }
}
