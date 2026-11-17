using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class LlTestCaseGeneratorNestedWriteTests
{
    [Fact]
    public async Task Generate_Hrpwm_Slv_SetCounterMode_Produces_WriteCheck_Without_Get()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_hrpwm_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var chip = Path.Combine(dir, "tae32g58xx_chip.h");
        File.WriteAllText(chip, """
            #define HRPWM_SLV0_PWMCR0_CONT_Pos        (3UL)
            #define HRPWM_SLV0_PWMCR0_CONT_Msk        (0x8UL)
            #define HRPWM_SLV0_PWMCR0_CONT_Val        (0x1UL)
            """);
        var path = Path.Combine(dir, "tae32g58xx_ll_hrpwm.h");
        File.WriteAllText(path, """
            #include "tae32g58xx_chip.h"
            #define LL_HRPWM_PWMx_NUMS (8U)
            __STATIC_INLINE void LL_HRPWM_SLV_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)
            {
                MODIFY_REG(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.PWMCR0,
                        HRPWM_SLV0_PWMCR0_CONT_Msk, (((Mode) & HRPWM_SLV0_PWMCR0_CONT_Val) << HRPWM_SLV0_PWMCR0_CONT_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaa01");
        var fnId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb01");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId,
                Name = "t",
                SdkRootPath = dir,
                ScanResultsPath = dir,
                IsActive = true
            });
            for (var i = 0; i < 8; i++)
            {
                var instId = Guid.Parse($"cccccccc-cccc-cccc-cccc-cccccccccc{i:D2}");
                var regId = Guid.Parse($"dddddddd-dddd-dddd-dddd-dddddddddd{i:D2}");
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = instId,
                    SdkProjectId = projectId,
                    Name = $"HRPWM_SLV{i}",
                    ModuleName = "HRPWM",
                    NaturalKey = $"HRPWM_SLV{i}",
                    BaseAddress = 0x4003B100u + (uint)i * 0x100u
                });
                init.RegisterDefinitions.Add(new RegisterDefinition
                {
                    Id = regId,
                    SdkProjectId = projectId,
                    PeripheralInstanceId = instId,
                    StructName = "HRPWM_SLV_Type",
                    MemberName = "PWMCR0",
                    DefinitionFile = chip,
                    NaturalKey = $"HRPWM_SLV{i}.PWMCR0",
                    AbsoluteAddress = 0x4003B100u + (uint)i * 0x100u
                });
                init.RegisterFields.Add(new RegisterField
                {
                    RegisterDefinitionId = regId,
                    Name = "CONT",
                    BitPosition = 3,
                    Mask = 0x8,
                    NaturalKey = "CONT"
                });
            }

            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_HRPWM_SLV_SetCounterMode",
                PeripheralName = "HRPWM",
                ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode",
                Signature = "void LL_HRPWM_SLV_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Mode)",
                Form = "inline",
                FilePath = path,
                ParseParameters =
                [
                    new LlFunctionParameter { Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0 },
                    new LlFunctionParameter { Name = "Pwmx", Type = "uint32_t", Position = 1 },
                    new LlFunctionParameter { Name = "Mode", Type = "uint32_t", Position = 2 }
                ]
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);

        var writeChecks = cases
            .Where(c => c.Name.Contains("/write-check", StringComparison.OrdinalIgnoreCase))
            .ToList();
        writeChecks.Should().NotBeEmpty("nested PWM[i].REG.PWMCR0 must produce write-check without Get");
        writeChecks.Should().OnlyContain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue));
        writeChecks.Should().OnlyContain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterWrite));
        writeChecks.Should().Contain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.ArrayIndex));
        writeChecks.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName.StartsWith("HRPWM_SLV", StringComparison.OrdinalIgnoreCase)
                                         && r.MemberName == "PWMCR0"));
        writeChecks.Should().Contain(c =>
            c.Parameters.Any(p => p.Name == "Pwmx" && (p.ValueExpression == "8" || p.ValueExpression == "9")));
        writeChecks.Should().NotContain(c =>
            c.Assertions.All(a => a.Kind == LlAssertionKind.Timeout));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Hrpwm_Mst_SetCounterMode_Nested_Master_Path()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_hrpwm_mst_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var chip = Path.Combine(dir, "tae32g58xx_chip.h");
        File.WriteAllText(chip, """
            #define HRPWM_MST_MCR0_CONT_Pos        (3UL)
            #define HRPWM_MST_MCR0_CONT_Msk        (0x8UL)
            """);
        var path = Path.Combine(dir, "tae32g58xx_ll_hrpwm.h");
        File.WriteAllText(path, """
            #include "tae32g58xx_chip.h"
            __STATIC_INLINE void LL_HRPWM_MST_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)
            {
                MODIFY_REG(HRPWMx->Master.MCR0, HRPWM_MST_MCR0_CONT_Msk,
                        (((Mode) & HRPWM_MST_MCR0_CONT_Msk) << HRPWM_MST_MCR0_CONT_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaa02");
        var fnId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb02");
        var instId = Guid.Parse("cccccccc-cccc-cccc-cccc-cccccccccc90");
        var regId = Guid.Parse("dddddddd-dddd-dddd-dddd-dddddddddd90");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "HRPWM_MST", ModuleName = "HRPWM",
                NaturalKey = "HRPWM_MST", BaseAddress = 0x4003B000
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "HRPWM_MST_Type", MemberName = "MCR0", DefinitionFile = chip,
                NaturalKey = "HRPWM_MST.MCR0", AbsoluteAddress = 0x4003B000
            });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "CONT", BitPosition = 3, Mask = 0x8, NaturalKey = "CONT"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId, SdkProjectId = projectId, FunctionName = "LL_HRPWM_MST_SetCounterMode",
                PeripheralName = "HRPWM", ReturnType = "void",
                Parameters = "HRPWM_TypeDef *HRPWMx, uint32_t Mode",
                Signature = "void LL_HRPWM_MST_SetCounterMode(HRPWM_TypeDef *HRPWMx, uint32_t Mode)",
                Form = "inline", FilePath = path,
                ParseParameters =
                [
                    new LlFunctionParameter { Name = "HRPWMx", Type = "HRPWM_TypeDef *", Position = 0 },
                    new LlFunctionParameter { Name = "Mode", Type = "uint32_t", Position = 1 }
                ]
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var writeChecks = cases.Where(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        writeChecks.Should().NotBeEmpty();
        writeChecks.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName == "HRPWM_MST" && r.MemberName == "MCR0"));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Generic_Module_ArrayPath_Uses_Mask_Peri_Not_Hrpwm_Only()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_genarr_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var chip = Path.Combine(dir, "tae32g58xx_chip.h");
        File.WriteAllText(chip, """
            #define FOO_CH0_CR_EN_Pos (0UL)
            #define FOO_CH0_CR_EN_Msk (0x1UL)
            #define FOO_CH0_CR_EN_Val (0x1UL)
            """);
        var path = Path.Combine(dir, "tae32g58xx_ll_foo.h");
        File.WriteAllText(path, """
            #include "tae32g58xx_chip.h"
            #define LL_FOO_CHx_NUMS (4U)
            __STATIC_INLINE void LL_FOO_CH_SetEnable(FOO_TypeDef *FOOx, uint32_t Chx, uint32_t Mode)
            {
                MODIFY_REG(FOOx->CH[(Chx) % LL_FOO_CHx_NUMS].REG.CR,
                        FOO_CH0_CR_EN_Msk, (((Mode) & FOO_CH0_CR_EN_Val) << FOO_CH0_CR_EN_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaa03");
        var fnId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb03");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            for (var i = 0; i < 4; i++)
            {
                var instId = Guid.Parse($"cccccccc-cccc-cccc-cccc-cccccccccd{i:D2}");
                var regId = Guid.Parse($"dddddddd-dddd-dddd-dddd-ddddddddde{i:D2}");
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = instId, SdkProjectId = projectId, Name = $"FOO_CH{i}", ModuleName = "FOO",
                    NaturalKey = $"FOO_CH{i}", BaseAddress = 0x40010000u + (uint)i * 0x100u
                });
                init.RegisterDefinitions.Add(new RegisterDefinition
                {
                    Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "FOO_CH_Type", MemberName = "CR", DefinitionFile = chip,
                    NaturalKey = $"FOO_CH{i}.CR", AbsoluteAddress = 0x40010000u + (uint)i * 0x100u
                });
                init.RegisterFields.Add(new RegisterField
                {
                    RegisterDefinitionId = regId, Name = "EN", BitPosition = 0, Mask = 0x1, NaturalKey = "EN"
                });
            }

            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId, SdkProjectId = projectId, FunctionName = "LL_FOO_CH_SetEnable",
                PeripheralName = "FOO", ReturnType = "void",
                Parameters = "FOO_TypeDef *FOOx, uint32_t Chx, uint32_t Mode",
                Signature = "void LL_FOO_CH_SetEnable(FOO_TypeDef *FOOx, uint32_t Chx, uint32_t Mode)",
                Form = "inline", FilePath = path,
                ParseParameters =
                [
                    new LlFunctionParameter { Name = "FOOx", Type = "FOO_TypeDef *", Position = 0 },
                    new LlFunctionParameter { Name = "Chx", Type = "uint32_t", Position = 1 },
                    new LlFunctionParameter { Name = "Mode", Type = "uint32_t", Position = 2 }
                ]
            });
            await init.SaveChangesAsync();
        }

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        var writeChecks = cases.Where(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        writeChecks.Should().NotBeEmpty("generic CH[i].REG.CR must generate write-check");
        writeChecks.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName.StartsWith("FOO_CH", StringComparison.OrdinalIgnoreCase)));
        writeChecks.Should().Contain(c =>
            c.Parameters.Any(p => p.Name == "Chx"));
        writeChecks.Should().NotContain(c =>
            c.InitialRegisters.Any(r => r.InstanceName.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase)));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Enable_Disable_ArrayPath_Produces_Full_Write_Monitoring()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_enarr_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var chip = Path.Combine(dir, "tae32g58xx_chip.h");
        File.WriteAllText(chip, """
            #define FOO_CH0_CR_EN_Pos (0UL)
            #define FOO_CH0_CR_EN_Msk (0x1UL)
            """);
        var path = Path.Combine(dir, "tae32g58xx_ll_foo.h");
        File.WriteAllText(path, """
            #include "tae32g58xx_chip.h"
            #define LL_FOO_CHx_NUMS (4U)
            __STATIC_INLINE void LL_FOO_CH_Enable(FOO_TypeDef *FOOx, uint32_t Chx)
            {
                SET_BIT(FOOx->CH[(Chx) % LL_FOO_CHx_NUMS].REG.CR, FOO_CH0_CR_EN_Msk);
            }
            __STATIC_INLINE void LL_FOO_CH_Disable(FOO_TypeDef *FOOx, uint32_t Chx)
            {
                CLEAR_BIT(FOOx->CH[(Chx) % LL_FOO_CHx_NUMS].REG.CR, FOO_CH0_CR_EN_Msk);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaa04");
        var enableId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb04");
        var disableId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb05");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            for (var i = 0; i < 4; i++)
            {
                var instId = Guid.Parse($"cccccccc-cccc-cccc-cccc-ccccccccce{i:D2}");
                var regId = Guid.Parse($"dddddddd-dddd-dddd-dddd-dddddddddf{i:D2}");
                init.PeripheralInstances.Add(new PeripheralInstance
                {
                    Id = instId, SdkProjectId = projectId, Name = $"FOO_CH{i}", ModuleName = "FOO",
                    NaturalKey = $"FOO_CH{i}", BaseAddress = 0x40020000u + (uint)i * 0x100u
                });
                init.RegisterDefinitions.Add(new RegisterDefinition
                {
                    Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "FOO_CH_Type", MemberName = "CR", DefinitionFile = chip,
                    NaturalKey = $"FOO_CH{i}.CR", AbsoluteAddress = 0x40020000u + (uint)i * 0x100u
                });
                init.RegisterFields.Add(new RegisterField
                {
                    RegisterDefinitionId = regId, Name = "EN", BitPosition = 0, Mask = 0x1, NaturalKey = "EN"
                });
            }

            init.LlFunctions.AddRange(
                new LlFunction
                {
                    Id = enableId, SdkProjectId = projectId, FunctionName = "LL_FOO_CH_Enable",
                    PeripheralName = "FOO", ReturnType = "void",
                    Parameters = "FOO_TypeDef *FOOx, uint32_t Chx",
                    Signature = "void LL_FOO_CH_Enable(FOO_TypeDef *FOOx, uint32_t Chx)",
                    Form = "inline", FilePath = path,
                    NaturalKey = path + "|LL_FOO_CH_Enable",
                    ParseParameters =
                    [
                        new LlFunctionParameter { Name = "FOOx", Type = "FOO_TypeDef *", Position = 0 },
                        new LlFunctionParameter { Name = "Chx", Type = "uint32_t", Position = 1 }
                    ]
                },
                new LlFunction
                {
                    Id = disableId, SdkProjectId = projectId, FunctionName = "LL_FOO_CH_Disable",
                    PeripheralName = "FOO", ReturnType = "void",
                    Parameters = "FOO_TypeDef *FOOx, uint32_t Chx",
                    Signature = "void LL_FOO_CH_Disable(FOO_TypeDef *FOOx, uint32_t Chx)",
                    Form = "inline", FilePath = path,
                    NaturalKey = path + "|LL_FOO_CH_Disable",
                    ParseParameters =
                    [
                        new LlFunctionParameter { Name = "FOOx", Type = "FOO_TypeDef *", Position = 0 },
                        new LlFunctionParameter { Name = "Chx", Type = "uint32_t", Position = 1 }
                    ]
                });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var enableCases = await generator.GenerateAsync(enableId);
        var disableCases = await generator.GenerateAsync(disableId);

        var enableChecks = enableCases
            .Where(c => c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase))
            .ToList();
        enableChecks.Should().NotBeEmpty();
        enableChecks.Should().OnlyContain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterWrite)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.PreserveBits)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.NoUnexpectedWrite)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.ArrayIndex));
        enableChecks.Should().Contain(c =>
            c.InitialRegisters.Any(r => r.InstanceName.StartsWith("FOO_CH", StringComparison.OrdinalIgnoreCase)));
        enableChecks.Should().Contain(c => c.Parameters.Any(p => p.Name == "Chx"));

        var disableChecks = disableCases
            .Where(c => c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase))
            .ToList();
        disableChecks.Should().NotBeEmpty();
        disableChecks.Should().OnlyContain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterWrite)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.PreserveBits)
            && c.Assertions.Any(a => a.Kind == LlAssertionKind.NoUnexpectedWrite));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
