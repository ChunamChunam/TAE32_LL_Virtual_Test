namespace TAE32.LLVirtualTest.Core.Entities;

public class LlFunctionParameter
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid LlFunctionId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public int Position { get; set; }
    public bool IsConst { get; set; }
    public bool IsPointer { get; set; }
    public string? RawText { get; set; }

    public LlFunction? LlFunction { get; set; }
}
