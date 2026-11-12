namespace TAE32.LLVirtualTest.Core.Entities;

public class LlRegisterReference
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid LlFunctionId { get; set; }
    public Guid? MacroInfoId { get; set; }
    public string? MacroName { get; set; }
    public string? ReferenceFile { get; set; }
    public int ReferenceLine { get; set; }
    public string? ExpansionSnippet { get; set; }

    public LlFunction? LlFunction { get; set; }
    public LlMacroInfo? MacroInfo { get; set; }
}
