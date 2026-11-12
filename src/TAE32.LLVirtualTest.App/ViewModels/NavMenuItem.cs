using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.App.ViewModels;

/// <summary>侧栏导航项（Segoe MDL2 Assets 字形）。</summary>
public sealed class NavMenuItem
{
    public required NavigationItem Item { get; init; }
    public required string Title { get; init; }
    /// <summary>Segoe MDL2 Assets 单字符。</summary>
    public required string Glyph { get; init; }
    public required string Group { get; init; }
}
