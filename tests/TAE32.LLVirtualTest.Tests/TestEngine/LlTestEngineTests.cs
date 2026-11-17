using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class TestHarnessGeneratorTests
{
    [Fact]
    public void Generate_Includes_Real_Ll_Header_And_Host_Peri_Ram()
    {
        var src = TestHarnessGenerator.Generate(
            "LL_GPIO_SetPinMode",
            "tae32g58xx_ll_gpio.h",
            new[]
            {
                new LlTestParameterValue { Name = "GPIOx", Type = "GPIO_TypeDef*", ValueExpression = "GPIOA" },
                new LlTestParameterValue { Name = "Pin", Type = "uint32_t", ValueExpression = "0x1" },
                new LlTestParameterValue { Name = "Mode", Type = "uint32_t", ValueExpression = "0x0" }
            },
            "void",
            "GPIOA");

        src.Should().Contain("#include \"tae32g58xx_ll_gpio.h\"");
        src.Should().Contain("#include \"tae32_ll_host_shim.h\"");
        src.Should().Contain("#define __GNUC__ 4");
        src.Should().Contain("#define __STATIC_INLINE static inline");
        src.Should().Contain("tae32_peri_img");
        src.Should().Contain("tae32_run");
        src.Should().Contain("GPIO_TypeDef* PERIx = (GPIO_TypeDef*)peri->base");
        src.Should().Contain("LL_GPIO_SetPinMode(PERIx");
        src.Should().Contain("args->m_Pin");
        src.Should().NotContain("0x400");
    }

    [Fact]
    public void Generate_WriteThenRead_Prelude_Pair()
    {
        var src = TestHarnessGenerator.Generate(
            "LL_GPIO_ReadOutputPort",
            "tae32g58xx_ll_gpio.h",
            new[]
            {
                new LlTestParameterValue { Name = "GPIOx", Type = "const GPIO_TypeDef*", ValueExpression = "GPIOA" }
            },
            "uint32_t",
            "GPIOA",
            preludeCalls: new[]
            {
                new LlTestCallStep
                {
                    FunctionName = "LL_GPIO_WriteOutputPort",
                    Parameters =
                    {
                        new LlTestParameterValue { Name = "GPIOx", Type = "GPIO_TypeDef*", ValueExpression = "GPIOA" },
                        new LlTestParameterValue { Name = "PortValue", Type = "uint32_t", ValueExpression = "0x5" }
                    }
                }
            });

        src.Should().Contain("LL_GPIO_WriteOutputPort(PERIx");
        src.Should().Contain("LL_GPIO_ReadOutputPort(PERIx)");
        src.Should().Contain("args->p0_PortValue");
    }

    [Theory]
    [InlineData("0x10", 0x10u)]
    [InlineData("16", 16u)]
    [InlineData("0xABu", 0xABu)]
    [InlineData("100UL", 100u)]
    [InlineData("0x100 /* LL_HRPWM_MST_MDIER_MREPIE */", 0x100u)]
    [InlineData("0x80 // comment", 0x80u)]
    public void ParseUIntExpression_Parses_Literals(string expr, uint expected)
        => TestHarnessGenerator.ParseUIntExpression(expr).Should().Be(expected);

    [Fact]
    public void Generate_Recovers_WWDG_Param_From_Signature_When_Empty()
    {
        var src = TestHarnessGenerator.Generate(
            "LL_WWDG_ClearFlag_EWIF",
            "tae32g58xx_ll_wwdg.h",
            Array.Empty<LlTestParameterValue>(),
            "void",
            "WWDG",
            "void LL_WWDG_ClearFlag_EWIF(WWDG_TypeDef * WWDGx)");

        src.Should().Contain("WWDG_TypeDef* PERIx");
        src.Should().Contain("LL_WWDG_ClearFlag_EWIF(PERIx)");
        src.Should().NotContain("LL_WWDG_ClearFlag_EWIF()");
    }

    [Fact]
    public void ParseParametersFromSignature_Reads_TypeDef_Pointer()
    {
        var ps = TestHarnessGenerator.ParseParametersFromSignature(
            "void LL_WWDG_ClearFlag_EWIF(WWDG_TypeDef * WWDGx)");
        ps.Should().ContainSingle();
        ps[0].Name.Should().Be("WWDGx");
        ps[0].Type.Should().Contain("WWDG_TypeDef");
    }

    [Fact]
    public void Generate_Uses_Host_Pointer_Buffer_For_Uint32_Star()
    {
        var src = TestHarnessGenerator.Generate(
            "LL_CAN_SetTxBuffer",
            "tae32g58xx_ll_can.h",
            new[]
            {
                new LlTestParameterValue { Name = "CANx", Type = "CAN_TypeDef*", ValueExpression = "CAN0" },
                new LlTestParameterValue { Name = "Buf", Type = "uint32_t*", ValueExpression = "0" }
            },
            "void",
            "CAN0");

        src.Should().Contain("uint32_t host_ptr_m_Buf");
        src.Should().Contain("host_ptr_m_Buf");
        src.Should().NotContain("return -2;");
    }

    [Fact]
    public void Generate_Can_Wait_Uses_Host_Ack_Without_Infinite_Loop()
    {
        var src = TestHarnessGenerator.Generate(
            "LL_CAN_ETB_WaitBufferRelease",
            "tae32g58xx_ll_can.h",
            new[]
            {
                new LlTestParameterValue { Name = "CANx", Type = "CAN_TypeDef*", ValueExpression = "CAN0" }
            },
            "void",
            "CAN0");

        src.Should().Contain("CAN0_CTRL_EREL_Msk");
        src.Should().Contain("break; /* host: buffer release ack");
        src.Should().NotContain("LL_CAN_ETB_WaitBufferRelease(PERIx)");
    }
}

public class AssertionEvaluatorTests
{
    [Fact]
    public async Task ReturnValue_Assertion_Passes_On_Match()
    {
        var spec = new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.ReturnValue,
            ExpectedHex = "0x1",
            RuleSource = LlAssertionRuleSource.Manual,
            RuleSourceDetail = "unit-test"
        };
        var results = await AssertionEvaluator.EvaluateAsync(
            mcu: null!,
            mcuId: Guid.Empty,
            specs: new[] { spec },
            returnValue: 1,
            trace: Array.Empty<VirtualAccessRecord>(),
            executionException: null,
            elapsedMs: 10,
            ct: CancellationToken.None);
        results.Should().ContainSingle(r => r.Passed && r.RuleSourceDetail == "unit-test");
    }

    [Fact]
    public async Task Timeout_Assertion_Fails_When_Exceeded()
    {
        var spec = new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.Timeout,
            TimeoutMs = 5,
            RuleSource = LlAssertionRuleSource.Manual
        };
        var results = await AssertionEvaluator.EvaluateAsync(
            null!, Guid.Empty, new[] { spec }, null, Array.Empty<VirtualAccessRecord>(), null, 20, CancellationToken.None);
        results.Single().Passed.Should().BeFalse();
    }

    [Fact]
    public async Task Exception_Assertion_Detects_Throw()
    {
        var spec = new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.Exception,
            ExpectedExpression = "throw",
            RuleSource = LlAssertionRuleSource.Manual
        };
        var results = await AssertionEvaluator.EvaluateAsync(
            null!, Guid.Empty, new[] { spec }, null, Array.Empty<VirtualAccessRecord>(),
            new InvalidOperationException("boom"), 1, CancellationToken.None);
        results.Single().Passed.Should().BeTrue();
    }

    [Fact]
    public async Task RegisterWrite_And_NoUnexpectedWrite_Fail_On_Empty_Trace()
    {
        var write = new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.RegisterWrite,
            InstanceName = "HRPWM_MST",
            MemberName = "MCR0",
            RuleSource = LlAssertionRuleSource.FromRegisterDefinition
        };
        var none = new LlTestAssertionSpec
        {
            Kind = LlAssertionKind.NoUnexpectedWrite,
            InstanceName = "HRPWM_MST",
            MemberName = "MCR0",
            ExpectedAccessOrder = new[] { "HRPWM_MST.MCR0", "MCR0" },
            RuleSource = LlAssertionRuleSource.FromRegisterDefinition
        };

        var results = await AssertionEvaluator.EvaluateAsync(
            null!, Guid.Empty, new[] { write, none }, 0u,
            Array.Empty<VirtualAccessRecord>(), null, 5, CancellationToken.None);

        results.Should().HaveCount(2);
        results.Should().OnlyContain(r => !r.Passed);
        results.Should().OnlyContain(r =>
            (r.Message ?? "").Contains("轨迹", StringComparison.Ordinal)
            || (r.Message ?? "").Contains("不完整", StringComparison.Ordinal));
    }
}

public class LlTestCaseStoreTests
{
    [Fact]
    public async Task Upsert_Export_Import_Roundtrip()
    {
        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite(conn)
            .Options;

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = Guid.Parse("11111111-1111-1111-1111-111111111111"),
                Name = "t",
                SdkRootPath = "x",
                ScanResultsPath = "y",
                IsActive = true
            });
            await init.SaveChangesAsync();
        }

        var projectId = Guid.Parse("11111111-1111-1111-1111-111111111111");
        var factory = new SharedConnectionFactory(options);
        var store = new LlTestCaseStore(factory);

        var saved = await store.UpsertAsync(new LlTestCaseEditModel
        {
            SdkProjectId = projectId,
            Name = "GPIO write PIN0",
            FunctionName = "LL_GPIO_WriteOutputPin",
            PeripheralName = "GPIO",
            ChipModelName = "TAE32G58xx",
            Status = "Ready",
            IsAutoGenerated = true,
            Parameters =
            {
                new LlTestParameterValue
                {
                    Name = "Pin", Type = "uint32_t", ValueExpression = "0x1",
                    RuleSource = "SDK macro candidate"
                }
            },
            Assertions =
            {
                new LlTestAssertionSpec
                {
                    Kind = LlAssertionKind.RegisterValue,
                    InstanceName = "GPIOA",
                    MemberName = "DOR",
                    ExpectedHex = "0x1",
                    RuleSource = LlAssertionRuleSource.FromRegisterDefinition,
                    RuleSourceDetail = "write sets DOR bit"
                }
            }
        });

        saved.Id.Should().NotBeEmpty();
        var json = await store.ExportJsonAsync(new[] { saved.Id });
        json.Should().Contain("LL_GPIO_WriteOutputPin");

        var imported = await store.ImportJsonAsync(projectId, json);
        imported.Should().Be(1);

        var list = await store.ListAsync(projectId, "GPIO");
        list.Should().HaveCount(2);

        await conn.DisposeAsync();
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
