using FluentAssertions;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class ChipHeaderAddressCatalogTests
{
    [Fact]
    public void Load_From_SdkContent_Resolves_Wwdg_Pscr_Absolute()
    {
        var sdkRoot = FindSdkRoot();
        if (sdkRoot is null)
        {
            // CI / sparse checkout without SDKContent — skip rather than fail the suite.
            return;
        }

        var catalog = ChipHeaderAddressCatalog.TryLoad(sdkRoot);
        catalog.Should().NotBeNull();
        catalog!.TryGetBase("WWDG", out var bas).Should().BeTrue();
        bas.Should().Be(0x4000D000u);

        catalog.TryResolveAbsolute("WWDG", "WWDG_Type", "PSCR", out var abs, out var b, out var off)
            .Should().BeTrue();
        b.Should().Be(0x4000D000u);
        off.Should().Be(0x0C);
        abs.Should().Be(0x4000D00Cu);

        catalog.TryResolveAbsolute("WWDG", "WWDG_TypeDef", "ISR", out var isr, out _, out var isrOff)
            .Should().BeTrue();
        isrOff.Should().Be(0x10);
        isr.Should().Be(0x4000D010u);
    }

    [Fact]
    public void Load_Temp_Headers_Prefers_Chip_File_Literals()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_chipaddr_" + Guid.NewGuid().ToString("N"));
        var inc = Path.Combine(dir, "SDK", "Drivers", "TAE32G58xx_Device", "Inc");
        Directory.CreateDirectory(inc);
        File.WriteAllText(Path.Combine(inc, "tae32g58xx.h"), """
            typedef WWDG_Type WWDG_TypeDef;
            #define WWDG_BASE 0x4000D000UL
            """);
        File.WriteAllText(Path.Combine(inc, "tae32g58xx_chip.h"), """
            #define WWDG_BASE 0x4000D000UL
            """);
        File.WriteAllText(Path.Combine(inc, "tae32g58xx_chip_struct.h"), """
            typedef struct {
              __IOM uint32_t CR;    /*!< (@ 0x00000000) */
              __IOM uint32_t WVR;   /*!< (@ 0x00000004) */
              __IOM uint32_t CVR;   /*!< (@ 0x00000008) */
              __IOM uint32_t PSCR;  /*!< (@ 0x0000000C) */
              __IOM uint32_t ISR;   /*!< (@ 0x00000010) */
            } WWDG_Type;
            """);

        var catalog = ChipHeaderAddressCatalog.TryLoad(dir);
        catalog.Should().NotBeNull();
        catalog!.TryResolveAbsolute("WWDG", "WWDG_TypeDef", "PSCR", out var abs, out _, out _)
            .Should().BeTrue();
        abs.Should().Be(0x4000D00Cu);

        Directory.Delete(dir, true);
    }

    private static string? FindSdkRoot()
    {
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        while (dir is not null)
        {
            var cand = Path.Combine(dir.FullName, "SDKContent",
                "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0");
            if (Directory.Exists(cand))
                return cand;
            dir = dir.Parent;
        }

        return null;
    }
}
