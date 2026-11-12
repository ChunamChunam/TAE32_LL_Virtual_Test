namespace TAE32.LLVirtualTest.Core.Entities;

public class LlMacroInfo
{
    public Guid Id { get; set; } = Guid.NewGuid();
    public Guid SdkProjectId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string? DefinitionFile { get; set; }
    public int DefinitionLine { get; set; }
    public string? Expansion { get; set; }
    public string Category { get; set; } = "Other";

    public ICollection<LlRegisterReference> References { get; set; } = new List<LlRegisterReference>();
}
