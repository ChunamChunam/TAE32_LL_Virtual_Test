using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class LlNativeEligibilityTests
{
    [Fact]
    public void DescribeSkip_Always_Allows_Host_Harness()
    {
        var peri = new LlTestParameterValue { Name = "ADCx", Type = "ADC_TypeDef *", ValueExpression = "ADC0" };
        var buf = new LlTestParameterValue { Name = "Data", Type = "uint32_t *", ValueExpression = "0" };

        LlNativeEligibility.DescribeSkip("LL_DEMO_Wait", "any.h", new[] { peri }).Should().BeNull();
        LlNativeEligibility.DescribeSkip("LL_DEMO_Set", "any.h", new[] { peri }).Should().BeNull();
        LlNativeEligibility.DescribeSkip("LL_DEMO_Plain", "any.h", new[] { peri, buf }).Should().BeNull();
    }

    [Fact]
    public void AutoClearCheck_RegisterMiss_Is_Skipped_Except_Gpio()
    {
        var miss = new LlTestAssertionResult { Passed = false, Message = "寄存器不存在于虚拟 MCU" };
        LlNativeEligibility.IsAutoClearCheckRegisterMiss("LL_ADC_ClearFlag/ADC0/clear-check", "ADC", true, new[] { miss })
            .Should().BeTrue();
        LlNativeEligibility.IsAutoClearCheckRegisterMiss("LL_GPIO_Clear/GPIOA/PIN/clear-check", "GPIO", true, new[] { miss })
            .Should().BeFalse();
        LlNativeEligibility.IsAutoClearCheckRegisterMiss("LL_ADC_SetMode/ADC0/draft", "ADC", true, new[] { miss })
            .Should().BeFalse();
    }
}

public class LlTestCaseGeneratorPolicyTests
{
    [Fact]
    public async Task Generate_Skips_ClearCheck_Without_Isr_And_Marks_Host_Unsafe()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_gen_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "foo.h");
        File.WriteAllText(path, """
            __STATIC_INLINE void LL_FOO_ClearFlag(FOO_TypeDef *FOOx) { FOOx->ISR = 0; }
            __STATIC_INLINE void LL_FOO_WaitDone(FOO_TypeDef *FOOx) { while (FOOx->SR); }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("22222222-2222-2222-2222-222222222222");
        var clearId = Guid.Parse("33333333-3333-3333-3333-333333333333");
        var waitId = Guid.Parse("44444444-4444-4444-4444-444444444444");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId,
                Name = "t",
                SdkRootPath = "x",
                ScanResultsPath = "y",
                IsActive = true
            });
            init.LlFunctions.Add(MakeFn(clearId, projectId, "LL_FOO_ClearFlag", "void LL_FOO_ClearFlag(FOO_TypeDef *FOOx)", path));
            init.LlFunctions.Add(MakeFn(waitId, projectId, "LL_FOO_WaitDone", "void LL_FOO_WaitDone(FOO_TypeDef *FOOx)", path));
            await init.SaveChangesAsync();
        }

        var factory = new SharedConnectionFactory(options);
        var generator = new LlTestCaseGenerator(factory);

        var clearCases = await generator.GenerateAsync(clearId);
        clearCases.Should().ContainSingle();
        clearCases[0].Status.Should().Be(nameof(LlTestCaseStatus.Draft));
        clearCases[0].Name.Should().NotContain("clear-check");
        clearCases[0].Assertions.Should().OnlyContain(a => a.Kind == Core.Enums.LlAssertionKind.Timeout);

        var waitCases = await generator.GenerateAsync(waitId);
        waitCases.Should().ContainSingle();
        waitCases[0].Status.Should().Be(nameof(LlTestCaseStatus.Draft));

        await using (var db = factory.CreateDbContext())
        {
            var instId = Guid.Parse("55555555-5555-5555-5555-555555555555");
            db.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId,
                SdkProjectId = projectId,
                Name = "FOO",
                ModuleName = "FOO",
                NaturalKey = "FOO"
            });
            db.RegisterDefinitions.Add(new RegisterDefinition
            {
                SdkProjectId = projectId,
                PeripheralInstanceId = instId,
                StructName = "FOO_TypeDef",
                MemberName = "ISR",
                DefinitionFile = path,
                NaturalKey = "FOO.ISR"
            });
            await db.SaveChangesAsync();
        }

        var withIsr = await generator.GenerateAsync(clearId);
        withIsr.Should().HaveCount(2);
        withIsr.Should().Contain(c => c.Name.EndsWith("/clear-check"));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    private static LlFunction MakeFn(Guid id, Guid projectId, string name, string signature, string path) => new()
    {
        Id = id,
        SdkProjectId = projectId,
        FunctionName = name,
        PeripheralName = "FOO",
        ReturnType = "void",
        Parameters = "FOO_TypeDef *FOOx",
        Signature = signature,
        Form = "inline",
        FilePath = path,
        NaturalKey = path + "|" + name,
        ParseParameters =
        {
            new LlFunctionParameter { Name = "FOOx", Type = "FOO_TypeDef *", Position = 0, IsPointer = true }
        }
    };

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
