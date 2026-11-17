using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class HrpwmMstBitOpGenerateTests
{
    private static string? FindLlHrpwmHeader()
    {
        var relative = Path.Combine(
            "SDKContent", "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0",
            "SDK", "Drivers", "TAE32G58xx_Driver", "LL", "tae32g58xx_ll_hrpwm.h");
        var dir = new DirectoryInfo(AppContext.BaseDirectory);
        for (var i = 0; i < 10 && dir is not null; i++, dir = dir.Parent)
        {
            var probe = Path.Combine(dir.FullName, relative);
            if (File.Exists(probe)) return probe;
        }

        var cwd = Path.Combine(Directory.GetCurrentDirectory(), relative);
        return File.Exists(cwd) ? cwd : null;
    }

    [Theory]
    [InlineData("LL_HRPWM_MST_AssertBurstDMADisable", "assert-check", "MCR1")]
    [InlineData("LL_HRPWM_MST_ReleaseBurstDMADisable", "release-check", "MCR1")]
    public async Task Generate_Mst_SetClear_Emits_BitOp_Checks(
        string functionName, string expectedSuffix, string member)
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

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
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            foreach (var name in new[] { "HRPWM_COM", "HRPWM_MST" })
            {
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = Guid.NewGuid(), SdkProjectId = projectId, Name = name,
                    ModuleName = "HRPWM", NaturalKey = name
                });
            }

            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx",
                Signature = $"void {functionName}(HRPWM_TypeDef *HRPWMx)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var semantic = cases.Where(c =>
            c.Name.Contains(expectedSuffix, StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase)).ToList();

        semantic.Should().NotBeEmpty(
            because: "Names=" + string.Join("; ", cases.Select(c => c.Name + " | " + c.Notes)));
        semantic.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue && a.MemberName == member));
        semantic.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.MemberName == member));
        semantic.Should().Contain(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase),
            because: "Assert↔Release complementary pair must be emitted");
        semantic.Should().Contain(c => c.PreludeCalls.Count > 0,
            because: "pair-check uses companion as prelude");

        // Pair must have Initial != Expected so host delta sync emits a Write (not net-zero).
        var pair = semantic.First(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase));
        var initHex = pair.InitialRegisters.Single(r => r.MemberName == member).ValueHex;
        var finalExpect = pair.Assertions.First(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && (a.RuleSourceDetail ?? "").Contains("成对", StringComparison.Ordinal)).ExpectedHex;
        initHex.Should().NotBe(finalExpect,
            because: "Assert→Release with same initial/final yields empty trace / false RegisterWrite fail");

        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_DisablePWM2_Uses_Body_CEN2_Not_CEN1_And_Emits_Pair()
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        const string functionName = "LL_HRPWM_MST_DisablePWM2";

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM_MST", ModuleName = "HRPWM", NaturalKey = "HRPWM_MST"
            });
            // DB poison: CEN1 field + stale access expr claiming CEN1 — must not win over body/name PWM2.
            var regId = Guid.NewGuid();
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, MemberName = "MCR1",
                StructName = "HRPWM_TypeDef", OffsetBytes = 4, WidthBits = 32, NaturalKey = "t|MCR1"
            });
            init.RegisterFields.Add(new RegisterField
            {
                Id = Guid.NewGuid(), RegisterDefinitionId = regId, Name = "CEN1",
                Mask = 0x40000u, BitPosition = 18, BitWidth = 1,
                MskMacroName = "HRPWM_MST_MCR1_CEN1_Msk", NaturalKey = "t|MCR1|CEN1"
            });
            init.RegisterFields.Add(new RegisterField
            {
                Id = Guid.NewGuid(), RegisterDefinitionId = regId, Name = "CEN2",
                Mask = 0x80000u, BitPosition = 19, BitWidth = 1,
                MskMacroName = "HRPWM_MST_MCR1_CEN2_Msk", NaturalKey = "t|MCR1|CEN2"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId, SdkProjectId = projectId, FunctionName = functionName,
                PeripheralName = "HRPWM", ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx",
                Signature = $"void {functionName}(HRPWM_TypeDef *HRPWMx)",
                Form = "inline", FilePath = path!, NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0, IsPointer = true
                    }
                },
                RegisterAccesses =
                {
                    new LlRegisterAccess
                    {
                        AccessKind = "Write",
                        MacroName = "CLEAR_BIT",
                        Expression =
                            "CLEAR_BIT(HRPWMx->Master.MCR1, HRPWM_MST_MCR1_CEN1_Msk)"
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        cases.Should().NotBeEmpty(because: "Names=" + string.Join("; ", cases.Select(c => c.Name)));

        var disable = cases.Where(c =>
            c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase)).ToList();
        disable.Should().NotBeEmpty();
        disable.Should().OnlyContain(c =>
            c.Name.Contains("CEN2", StringComparison.OrdinalIgnoreCase)
            || (c.Notes ?? "").Contains("CEN2", StringComparison.OrdinalIgnoreCase)
            || c.Assertions.Any(a => (a.RuleSourceDetail ?? "")
                .Contains("CEN2", StringComparison.OrdinalIgnoreCase)));
        disable.Should().OnlyContain(c =>
            !c.Name.Contains("CEN1", StringComparison.OrdinalIgnoreCase)
            && !(c.Notes ?? "").Contains("CEN1", StringComparison.OrdinalIgnoreCase)
            && c.Assertions.All(a => !(a.RuleSourceDetail ?? "")
                .Contains("CEN1", StringComparison.OrdinalIgnoreCase)),
            because: "DisablePWM2 body uses CEN2_Msk; CEN1 would be a false-pass trap");

        // Expected clear mask must be 0x80000 (CEN2), not 0x40000 (CEN1).
        var targetBitAssert = disable.SelectMany(c => c.Assertions)
            .First(a => a.Kind == LlAssertionKind.RegisterValue
                        && a.ExpectedMask == 0x80000u
                        && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase));
        targetBitAssert.Should().NotBeNull();

        cases.Should().Contain(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase),
            because: "DisablePWM2 ↔ EnablePWM2 pair must also be generated");
        cases.Count.Should().BeGreaterThanOrEqualTo(2);

        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ClearFlag_MREP_Targets_HrpwmMst_Misr_Not_Bare_Hrpwm()
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        const string functionName = "LL_HRPWM_MST_ClearFlag_MREP";

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            // Bare module instance first — must still resolve Master.MISR → HRPWM_MST.
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM", ModuleName = "HRPWM", NaturalKey = "HRPWM"
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = Guid.NewGuid(), SdkProjectId = projectId,
                Name = "HRPWM_MST", ModuleName = "HRPWM", NaturalKey = "HRPWM_MST"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId, SdkProjectId = projectId, FunctionName = functionName,
                PeripheralName = "HRPWM", ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx",
                Signature = $"void {functionName}(HRPWM_TypeDef *HRPWMx)",
                Form = "inline", FilePath = path!, NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0, IsPointer = true
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var clear = cases.Where(c =>
            c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        clear.Should().NotBeEmpty(because: "Names=" + string.Join("; ", cases.Select(c => c.Name)));
        clear.Should().OnlyContain(c =>
            c.Name.Contains("HRPWM_MST", StringComparison.OrdinalIgnoreCase)
            && c.Name.Contains("MISR", StringComparison.OrdinalIgnoreCase),
            because: "WRITE_REG(Master.MISR) must assert HRPWM_MST.MISR, not bare HRPWM.MISR");
        clear.Should().OnlyContain(c =>
            c.InitialRegisters.All(r =>
                r.InstanceName == "HRPWM_MST" && r.MemberName == "MISR"));
        clear.Should().OnlyContain(c =>
            c.Assertions.Where(a =>
                    a.Kind == LlAssertionKind.RegisterValue || a.Kind == LlAssertionKind.RegisterWrite)
                .All(a => a.InstanceName == "HRPWM_MST" && a.MemberName == "MISR"));
        // W1C: target bit cleared, not whole-register == written mask.
        clear.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue
                                  && a.ExpectedMask == 0x100u
                                  && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)));

        await conn.DisposeAsync();
    }

    [Theory]
    [InlineData("LL_HRPWM_MST_EnableIT", "enable-check")]
    [InlineData("LL_HRPWM_MST_DisableIT", "disable-check")]
    public async Task Generate_Mst_EnableDisableIT_MaskParam_Emits_BitOp_On_Mdier(
        string functionName, string expectedSuffix)
    {
        var path = FindLlHrpwmHeader();
        path.Should().NotBeNull();

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
                Id = projectId, Name = "t", SdkRootPath = Path.GetDirectoryName(path!)!,
                ScanResultsPath = Path.GetDirectoryName(path!)!, IsActive = true
            });
            foreach (var name in new[] { "HRPWM", "HRPWM_MST" })
            {
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = Guid.NewGuid(), SdkProjectId = projectId, Name = name,
                    ModuleName = "HRPWM", NaturalKey = name
                });
            }

            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = "HRPWM",
                ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx, uint32_t Mask",
                Signature = $"void {functionName}(HRPWM_TypeDef *HRPWMx, uint32_t Mask)",
                Form = "inline",
                FilePath = path!,
                NaturalKey = path + "|" + functionName,
                ParseParameters =
                {
                    new LlFunctionParameter
                    {
                        Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0, IsPointer = true
                    },
                    new LlFunctionParameter
                    {
                        Name = "Mask", Type = "uint32_t", Position = 1, IsPointer = false
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var semantic = cases.Where(c =>
            c.Name.Contains(expectedSuffix, StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase)).ToList();
        semantic.Should().NotBeEmpty(
            because: "Names=" + string.Join("; ", cases.Select(c => c.Name + " | " + c.Notes)));
        semantic.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName == "HRPWM_MST" && r.MemberName == "MDIER"));
        semantic.Should().Contain(c =>
            c.Parameters.Any(p =>
                p.Name.Equals("Mask", StringComparison.OrdinalIgnoreCase)
                && !string.Equals(p.ValueExpression, "0", StringComparison.Ordinal)));
        semantic.Should().Contain(c => c.Name.Contains("pair-check", StringComparison.OrdinalIgnoreCase));

        await conn.DisposeAsync();
    }

    [Theory]
    [InlineData("LL_HRPWM_MST_AssertBurstDMADisable", "LL_HRPWM_MST_ReleaseBurstDMADisable")]
    [InlineData("LL_HRPWM_MST_ReleaseBurstDMADisable", "LL_HRPWM_MST_AssertBurstDMADisable")]
    [InlineData("LL_ADC_Enable", "LL_ADC_Disable")]
    [InlineData("LL_HRPWM_MST_DisablePWM2", "LL_HRPWM_MST_EnablePWM2")]
    public void SuggestComplementFunctionName_Maps_Pairs(string input, string expected)
    {
        LlTestCaseGenerator.SuggestComplementFunctionName(input).Should().Be(expected);
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
