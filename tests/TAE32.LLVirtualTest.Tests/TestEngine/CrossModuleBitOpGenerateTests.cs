using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

/// <summary>
/// Real-SDK smoke: CLEAR_BIT/SET_BIT + Enable/Disable/Assert/Release pairs across modules
/// (not HRPWM-only). No RegisterFields in DB — relies on chip-header mask resolution.
/// </summary>
public class CrossModuleBitOpGenerateTests
{
    private static string? FindLlHeader(string fileName)
    {
        var relative = Path.Combine(
            "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0",
            "SDK", "Drivers", "TAE32G58xx_Driver", "LL", fileName);
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        for (var i = 0; i < 10 && dir is not null; i++, dir = dir.Parent)
        {
            var probe = Path.Combine(dir.FullName, relative);
            if (File.Exists(probe)) return probe;
        }

        var cwd = Path.Combine(Directory.GetCurrentDirectory(), relative);
        return File.Exists(cwd) ? cwd : null;
    }

    public static IEnumerable<object[]> ComplementaryPairs()
    {
        yield return
        [
            "tae32g58xx_ll_uart.h", "UART", "UART0",
            "LL_UART_Enable", "LL_UART_Disable", "CR0", true
        ];
        yield return
        [
            "tae32g58xx_ll_i2c.h", "I2C", "I2C0",
            "LL_I2C_Enable", "LL_I2C_Disable", "ENABLE", true
        ];
        yield return
        [
            "tae32g58xx_ll_spi.h", "SPI", "SPI0",
            "LL_SPI_Enable", "LL_SPI_Disable", "ENABLE", true
        ];
        yield return
        [
            "tae32g58xx_ll_can.h", "CAN", "CAN0",
            "LL_CAN_AssertProtocolExceptionDetectDisable",
            "LL_CAN_ReleaseProtocolExceptionDetectDisable",
            "CTRL", true
        ];
        // ADC Disable uses SET_BIT(ADDIS), not CLEAR of ADEN — solo enable-check only, no false pair.
        yield return
        [
            "tae32g58xx_ll_adc.h", "ADC", "ADC0",
            "LL_ADC_Enable", null!, "CR", false
        ];
    }

    [Theory]
    [MemberData(nameof(ComplementaryPairs))]
    public async Task Generate_CrossModule_BitOp_And_Pairs(
        string headerFile,
        string module,
        string instance,
        string functionName,
        string? companionName,
        string member,
        bool expectPair)
    {
        var path = FindLlHeader(headerFile);
        path.Should().NotBeNull(because: headerFile);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t",
                SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!,
                IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = instance, ModuleName = module, NaturalKey = instance
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = module,
                ReturnType = "void",
                Parameters = $"{module}_TypeDef *PERIx",
                Signature = $"void {functionName}({module}_TypeDef *PERIx)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "PERIx", Type = $"{module}_TypeDef *", Position = 0, IsPointer = true
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);

        var semantic = cases.Where(c =>
                !c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase)
                && c.Assertions.Any(a => a.Kind is not LlAssertionKind.Timeout))
            .ToList();

        semantic.Should().NotBeEmpty(
            because: $"{functionName} Names=" + string.Join("; ", cases.Select(c => c.Name)));
        semantic.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue && a.MemberName == member));
        semantic.Should().Contain(c => c.InitialRegisters.Any(r => r.MemberName == member));

        if (expectPair)
        {
            companionName.Should().NotBeNullOrWhiteSpace();
            LlTestCaseGenerator.SuggestComplementFunctionName(functionName).Should().Be(companionName);
            semantic.Should().Contain(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase));
            semantic.Should().Contain(c => c.PreludeCalls.Count > 0
                                           && c.PreludeCalls[0].FunctionName == companionName);

            // Same net-zero bug as HRPWM Assert→Release: Initial must differ from final Expected.
            var pair = semantic.First(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase));
            var initHex = pair.InitialRegisters.Single(r => r.MemberName == member).ValueHex;
            var finalExpect = pair.Assertions.First(a =>
                a.Kind == LlAssertionKind.RegisterValue
                && (a.RuleSourceDetail ?? "").Contains("成对", StringComparison.Ordinal)).ExpectedHex;
            initHex.Should().NotBe(finalExpect,
                because: $"{module} pair-check must leave a host delta for RegisterWrite sync");
        }
        else
        {
            semantic.Should().NotContain(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase),
                because: "ADC Enable/Disable are not complementary CLEAR/SET on the same mask");
        }

        await conn.DisposeAsync();
    }

    [Theory]
    [InlineData("LL_UART_Enable", "LL_UART_Disable")]
    [InlineData("LL_I2C_Disable", "LL_I2C_Enable")]
    [InlineData("LL_SPI_Enable", "LL_SPI_Disable")]
    [InlineData("LL_CAN_AssertProtocolExceptionDetectDisable",
        "LL_CAN_ReleaseProtocolExceptionDetectDisable")]
    [InlineData("LL_RCU_EnableHSE", "LL_RCU_DisableHSE")]
    public void SuggestComplement_Works_Across_Modules(string input, string expected)
        => LlTestCaseGenerator.SuggestComplementFunctionName(input).Should().Be(expected);

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
