using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class LlShiftStaticAnalyzerTests
{
    private static string? FindSdkRoot()
    {
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        while (dir is not null)
        {
            var candidate = Path.Combine(dir.FullName, "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
            if (Directory.Exists(candidate))
                return candidate;
            dir = dir.Parent;
        }

        return null;
    }

    private static string? FindWwdgHeader(string sdkRoot)
    {
        var path = Path.Combine(
            sdkRoot, "SDK", "Drivers", "TAE32G58xx_Driver", "LL", "tae32g58xx_ll_wwdg.h");
        return File.Exists(path) ? path : null;
    }

    [Fact]
    public void Correct_SetPrescaler_Pos_Is_Not_Flagged()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;
        var header = FindWwdgHeader(sdk);
        if (header is null) return;

        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(sdk, header, "LL_WWDG_SetPrescaler");

        result.HasBlockingError.Should().BeFalse(
            because: string.Join("; ", result.Diagnostics.Select(d => $"{d.RuleId}:{d.Description}")));
        result.Diagnostics.Should().NotContain(d =>
            d.RuleId == "InvalidShiftCount"
            || d.RuleId == "MaskUsedAsShiftPosition"
            || d.RuleId == "RegisterFieldMismatch");
    }

    [Fact]
    public void Wrong_Mask_As_Shift_Is_Detected_Even_When_Prescaler_Is_Zero()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;

        // Injected wrong body — does not modify formal SDK files.
        const string wrongBody = """
            {
                ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));
                MODIFY_REG(
                    WWDGx->PSCR,
                    WWDG_PSCR_PSC_Msk,
                    ((Prescaler) << WWDG_WVR_WV_Msk)
                );
            }
            """;

        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(
            sdk,
            sourceFile: "tae32g58xx_ll_wwdg.h",
            functionName: "LL_WWDG_SetPrescaler",
            sourceOverride: wrongBody);

        result.HasBlockingError.Should().BeTrue();
        result.Diagnostics.Should().Contain(d => d.RuleId == "InvalidShiftCount");
        result.Diagnostics.Should().Contain(d => d.RuleId == "MaskUsedAsShiftPosition");
        result.Diagnostics.Should().Contain(d => d.RuleId == "RegisterFieldMismatch");

        var invalid = result.Diagnostics.First(d => d.RuleId == "InvalidShiftCount");
        invalid.ResolvedMacroValue.Should().Contain("65535");
        invalid.Description.Should().Contain("未定义行为");
    }

    [Fact]
    public void Wrong_Mask_As_Shift_On_Iwdg_Is_Detected()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;

        // Real SDK macros: RLR field vs KEYR mask (0xFFFF) used as shift — UB + register mismatch.
        const string wrongBody = """
            {
                MODIFY_REG(IWDGx->RLR, IWDG_RLR_RLV_Msk, ((Counter) << IWDG_KEYR_KEY_Msk));
            }
            """;

        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(sdk, "tae32g58xx_ll_iwdg.h", "LL_IWDG_SetReloadCounter", wrongBody);

        result.HasBlockingError.Should().BeTrue(
            because: string.Join("; ", result.Diagnostics.Select(d => $"{d.RuleId}:{d.Description}")));
        result.Diagnostics.Any(d =>
                d.RuleId == "MaskUsedAsShiftPosition"
                || d.RuleId == "InvalidShiftCount"
                || d.RuleId == "RegisterFieldMismatch")
            .Should().BeTrue();
    }

    [Fact]
    public void Position_Used_As_Mask_Is_Warning()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;

        const string body = """
            {
                MODIFY_REG(WWDGx->PSCR, WWDG_PSCR_PSC_Pos, ((Prescaler) << WWDG_PSCR_PSC_Pos));
            }
            """;

        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(sdk, "tae32g58xx_ll_wwdg.h", "LL_WWDG_SetPrescaler", body);

        result.Diagnostics.Should().Contain(d => d.RuleId == "PositionUsedAsMask");
        result.Diagnostics.First(d => d.RuleId == "PositionUsedAsMask").Severity.Should().Be("Warning");
    }

    [Fact]
    public void Correct_SetWindow_Does_Not_False_Positive()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;
        var header = FindWwdgHeader(sdk);
        if (header is null) return;

        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(sdk, header, "LL_WWDG_SetWindow");

        result.HasBlockingError.Should().BeFalse(
            because: string.Join("; ", result.Diagnostics.Select(d => $"{d.RuleId}:{d.Description}")));
    }

    [Fact]
    public void FormatReport_Contains_Required_Sections()
    {
        var sdk = FindSdkRoot();
        if (sdk is null) return;

        const string wrongBody = """
            {
                MODIFY_REG(WWDGx->PSCR, WWDG_PSCR_PSC_Msk, ((Prescaler) << WWDG_WVR_WV_Msk));
            }
            """;
        var analyzer = new LlShiftStaticAnalyzer();
        var result = analyzer.Analyze(sdk, "tae32g58xx_ll_wwdg.h", "LL_WWDG_SetPrescaler", wrongBody);
        var report = LlShiftStaticAnalyzer.FormatReport("LL_WWDG_SetPrescaler", result);

        report.Should().Contain("<Static Analysis: Failed>");
        report.Should().Contain("InvalidShiftCount");
        report.Should().Contain("WWDG_WVR_WV_Msk");
        report.Should().Contain("建议");
    }
}
