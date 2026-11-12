using FluentAssertions;
using TAE32.LLVirtualTest.SDK.Parse;

namespace TAE32.LLVirtualTest.Tests.Parse;

public class LlGpioParseTests
{
    private static string WorkspaceRoot
    {
        get
        {
            var dir = new DirectoryInfo(AppContext.BaseDirectory);
            while (dir is not null)
            {
                if (Directory.Exists(Path.Combine(dir.FullName, "SDKContent")))
                    return dir.FullName;
                dir = dir.Parent;
            }
            return Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", ".."));
        }
    }

    private static string PackageRoot =>
        Path.Combine(WorkspaceRoot, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");

    private static string ResolveLlRoot()
    {
        var candidates = new[]
        {
            Path.Combine(PackageRoot, "LL"),
            Path.Combine(PackageRoot, "SDK", "Drivers", "TAE32G58xx_Driver", "LL")
        };
        return candidates.FirstOrDefault(Directory.Exists)
               ?? Directory.EnumerateDirectories(PackageRoot, "LL", SearchOption.AllDirectories).First();
    }

    [Fact]
    public void ParseBridge_builds_for_real_ll_root()
    {
        var llRoot = ResolveLlRoot();
        Directory.Exists(llRoot).Should().BeTrue();
        var bridgeRoot = Path.Combine(Path.GetTempPath(), "tae32_test_bridge", Guid.NewGuid().ToString("N"));
        var result = new ParseBridgeBuilder().Build(llRoot, bridgeRoot, Guid.NewGuid());
        result.InstanceCount.Should().BeGreaterThan(0);
        result.TypedefCount.Should().BeGreaterThan(0);
        File.Exists(Path.Combine(bridgeRoot, "tae32g58xx.h")).Should().BeTrue();
        File.Exists(Path.Combine(bridgeRoot, "tae32g58xx_ll_conf.h")).Should().BeTrue();
    }

    [Fact]
    public void Clang_extracts_GPIO_inline_functions()
    {
        var llRoot = ResolveLlRoot();
        var bridgeRoot = Path.Combine(Path.GetTempPath(), "tae32_test_bridge", Guid.NewGuid().ToString("N"));
        _ = new ParseBridgeBuilder().Build(llRoot, bridgeRoot, Guid.NewGuid());

        var env = ClangEnvironment.Resolve(PackageRoot, bridgeRoot);

        var header = "tae32g58xx_ll_gpio.h";
        var wrapperDir = Path.Combine(bridgeRoot, "wrappers");
        using var session = new ClangAstSession();
        var wrapper = ClangAstSession.CreateWrapperFile(wrapperDir, header);
        var parse = session.ParseHeader(wrapper, env.BuildClangArgs(), header);

        var extractor = new LlFunctionAstExtractor(Guid.NewGuid(), $"LL/{header}", header,
            Path.Combine(llRoot, header));
        var functions = extractor.Extract(parse);

        functions.Should().NotBeEmpty();
        functions.Should().Contain(f => f.FunctionName == "LL_GPIO_GetPinOutputType");
        functions.Should().Contain(f => f.FunctionName == "LL_GPIO_SetPinOutputType");
        functions.Should().Contain(f => f.FunctionName == "LL_GPIO_SetPinPull");

        var getOut = functions.First(f => f.FunctionName == "LL_GPIO_GetPinOutputType");
        getOut.ParseSucceeded.Should().BeTrue();
        getOut.IsInline.Should().BeTrue();
        getOut.Modifiers.Should().Be("static inline");
        getOut.Operations.Should().Contain(o => o.OpKind == "Return");
        getOut.RegisterAccesses.Should().Contain(r => r.MacroName == "READ_BIT");
        getOut.RegisterAccesses.Should().Contain(r => r.RegisterPath != null && r.RegisterPath.Contains("ODR"));

        var setPull = functions.First(f => f.FunctionName == "LL_GPIO_SetPinPull");
        setPull.ParseSucceeded.Should().BeTrue();
        setPull.Parameters.Should().HaveCount(3);
        setPull.RegisterAccesses.Should().Contain(r => r.MacroName == "MODIFY_REG");
        setPull.RegisterAccesses.Should().Contain(r => r.AccessKind == "Modify");

        var setOut = functions.First(f => f.FunctionName == "LL_GPIO_SetPinOutputType");
        setOut.Operations.Should().Contain(o => o.OpKind == "If");
        setOut.RegisterAccesses.Should().Contain(r => r.MacroName == "SET_BIT");
        setOut.RegisterAccesses.Should().Contain(r => r.MacroName == "CLEAR_BIT");

        foreach (var fn in functions.Where(f => f.ParseSucceeded))
            fn.Parameters.Count.Should().BeGreaterThan(0);
    }
}
