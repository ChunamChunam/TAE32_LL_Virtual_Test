using FluentAssertions;
using TAE32.LLVirtualTest.SDK.Import;

namespace TAE32.LLVirtualTest.Tests.Persistence;

public class NaturalKeyTests
{
    [Fact]
    public void FunctionNaturalKey_UsesPathLineNameForm_NotNameAlone()
    {
        var a = ScanImportService.BuildFunctionNaturalKey("a/b.h", 10, "LL_FOO", "inline_definition");
        var b = ScanImportService.BuildFunctionNaturalKey("a/b.h", 20, "LL_FOO", "inline_definition");
        var c = ScanImportService.BuildFunctionNaturalKey("a/b.h", 10, "LL_FOO", "function_macro");

        a.Should().NotBe(b);
        a.Should().NotBe(c);
        a.Should().Contain("10");
        a.Should().Contain("LL_FOO");
    }
}
