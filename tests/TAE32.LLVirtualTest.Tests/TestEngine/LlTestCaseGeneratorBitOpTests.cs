using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class LlTestCaseGeneratorBitOpTests
{
    [Fact]
    public async Task Generate_SetBit_CompositeMask_Produces_Register_Assertion()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_bitop_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
            #define ADC0_CFGR1_BIASEN_Msk (0x1U)
            #define ADC0_CFGR1_REFEN_Msk  (0x2U)
            #define ADC0_CFGR1_CHEN_Msk   (0x8U)
            #define LL_ADC_CFGR1_PREPARING_START_MSK ((ADC0_CFGR1_BIASEN_Msk | ADC0_CFGR1_REFEN_Msk | \
                                                      ADC0_CFGR1_CHEN_Msk))
            __STATIC_INLINE void LL_ADC_AssertPreparingStart(ADC_TypeDef *ADCx)
            {
                SET_BIT(ADCx->CFGR1, LL_ADC_CFGR1_PREPARING_START_MSK);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa");
        var fnId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb");
        var instId = Guid.Parse("cccccccc-cccc-cccc-cccc-cccccccccccc");
        var regId = Guid.Parse("dddddddd-dddd-dddd-dddd-dddddddddddd");

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
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId,
                SdkProjectId = projectId,
                Name = "ADC0",
                ModuleName = "ADC",
                NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId,
                SdkProjectId = projectId,
                PeripheralInstanceId = instId,
                StructName = "ADC_TypeDef",
                MemberName = "CFGR1",
                DefinitionFile = path,
                NaturalKey = "ADC.CFGR1"
            });
            init.RegisterFields.AddRange(
                new RegisterField { RegisterDefinitionId = regId, Name = "BIASEN", BitPosition = 0, Mask = 0x1, NaturalKey = "BIASEN" },
                new RegisterField { RegisterDefinitionId = regId, Name = "REFEN", BitPosition = 1, Mask = 0x2, NaturalKey = "REFEN" },
                new RegisterField { RegisterDefinitionId = regId, Name = "CHEN", BitPosition = 3, Mask = 0x8, NaturalKey = "CHEN" });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_AssertPreparingStart",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx",
                Signature = "void LL_ADC_AssertPreparingStart(ADC_TypeDef *ADCx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_AssertPreparingStart",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true }
                },
                RegisterAccesses =
                {
                    // Stale/wrong DB evidence must NOT override live body (PREPARING_START).
                    new LlRegisterAccess
                    {
                        MacroName = "SET_BIT",
                        AccessKind = "Write",
                        Expression = "SET_BIT(ADCx->CFGR1, ADC0_CFGR1_BIASEN_Msk);",
                        RegisterPath = "ADCx->CFGR1"
                    }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);

        cases.Should().ContainSingle(c => c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        var setCase = cases.First(c => c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        setCase.Status.Should().Be(nameof(LlTestCaseStatus.Ready));
        // RMW: preload unrelated bits 0xA5A55A50, after SET expect 0xA5A55A5B (preserve|0xB).
        const uint mask = 0xBu;
        const uint preserve = 0xA5A55A5Au & ~mask;
        const uint expectedAfter = preserve | mask;
        setCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CFGR1" && string.Equals(r.ValueHex, $"0x{preserve:X}", StringComparison.OrdinalIgnoreCase));
        setCase.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.MemberName == "CFGR1"
            && a.ExpectedMask == expectedAfter
            && string.Equals(a.ExpectedHex, $"0x{expectedAfter:X}", StringComparison.OrdinalIgnoreCase));
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.Timeout);

        // Mutate body to wrong mask, then REGENERATE — trusted expected must stay PREPARING_START RMW.
        File.WriteAllText(path, """
            #define ADC0_CFGR1_BIASEN_Msk (0x1U)
            #define ADC0_CFGR1_REFEN_Msk  (0x2U)
            #define ADC0_CFGR1_CHEN_Msk   (0x8U)
            #define LL_ADC_CFGR1_PREPARING_START_MSK ((ADC0_CFGR1_BIASEN_Msk | ADC0_CFGR1_REFEN_Msk | \
                                                      ADC0_CFGR1_CHEN_Msk))
            __STATIC_INLINE void LL_ADC_AssertPreparingStart(ADC_TypeDef *ADCx)
            {
                SET_BIT(ADCx->CFGR1, ADC0_CFGR1_BIASEN_Msk);
            }
            """);

        var regenerated = await generator.GenerateAsync(fnId);
        var regenCase = regenerated.First(c => c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        var expected = regenCase.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        expected.ExpectedHex.Should().BeEquivalentTo($"0x{expectedAfter:X}");
        expected.ExpectedMask.Should().Be(expectedAfter);
        expected.RuleSourceDetail.Should().Contain("PREPARING_START");
        expected.RuleSourceDetail.Should().Contain("RMW");
        expected.RuleSourceDetail.Should().NotContain("BIASEN_Msk");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_DisableIT_AWDG2_TrustedMask_Survives_Wrong_Body_Regen()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_awdg2_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        // Wrong body from the start (AWD1IE instead of AWD2IE); trusted expect via LL_ADC_IER_AWD2IE.
        File.WriteAllText(path, """
            #define ADC0_IER_AWD2IE_Msk (0x80U)
            #define ADC0_IER_AWD1IE_Msk (0x40U)
            #define LL_ADC_IER_AWD2IE (ADC0_IER_AWD2IE_Msk)
            #define LL_ADC_IER_AWD1IE (ADC0_IER_AWD1IE_Msk)
            __STATIC_INLINE void LL_ADC_DisableIT_AWDG2(ADC_TypeDef *ADCx)
            {
                CLEAR_BIT(ADCx->IER, ADC0_IER_AWD1IE_Msk);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("a1a1a1a1-a1a1-a1a1-a1a1-a1a1a1a1a1a1");
        var fnId = Guid.Parse("b2b2b2b2-b2b2-b2b2-b2b2-b2b2b2b2b2b2");
        var instId = Guid.Parse("c3c3c3c3-c3c3-c3c3-c3c3-c3c3c3c3c3c3");
        var regId = Guid.Parse("d4d4d4d4-d4d4-d4d4-d4d4-d4d4d4d4d4d4");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "ADC0", ModuleName = "ADC", NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "ADC_TypeDef", MemberName = "IER", DefinitionFile = path, NaturalKey = "ADC.IER"
            });
            init.RegisterFields.AddRange(
                new RegisterField { RegisterDefinitionId = regId, Name = "AWD2IE", BitPosition = 7, Mask = 0x80, NaturalKey = "AWD2IE" },
                new RegisterField { RegisterDefinitionId = regId, Name = "AWD1IE", BitPosition = 6, Mask = 0x40, NaturalKey = "AWD1IE" });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_DisableIT_AWDG2",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx",
                Signature = "void LL_ADC_DisableIT_AWDG2(ADC_TypeDef *ADCx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_DisableIT_AWDG2",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var clearCase = cases.First(c => c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase));
        var reg = clearCase.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        const uint mask = 0x80u;
        const uint preserve = 0xA5A55A5Au & ~mask;
        reg.ExpectedMask.Should().Be(preserve | mask);
        reg.ExpectedHex.Should().BeEquivalentTo($"0x{preserve:X}");
        clearCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "IER"
            && string.Equals(r.ValueHex, $"0x{preserve | mask:X}", StringComparison.OrdinalIgnoreCase));
        reg.RuleSourceDetail.Should().Contain("AWD2");
        reg.RuleSourceDetail.Should().Contain("RMW");
        reg.RuleSourceDetail.Should().NotContain("AWD1IE_Msk");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ClearBit_Preloads_And_Expects_Zero()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_clearbit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
            #define ADC0_CFGR1_BIASEN_Msk (0x1U)
            __STATIC_INLINE void LL_ADC_DisableBias(ADC_TypeDef *ADCx)
            {
                CLEAR_BIT(ADCx->CFGR1, ADC0_CFGR1_BIASEN_Msk);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("eeeeeeee-eeee-eeee-eeee-eeeeeeeeeeee");
        var fnId = Guid.Parse("ffffffff-ffff-ffff-ffff-ffffffffffff");
        var instId = Guid.Parse("12121212-1212-1212-1212-121212121212");
        var regId = Guid.Parse("34343434-3434-3434-3434-343434343434");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "ADC0", ModuleName = "ADC", NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "ADC_TypeDef", MemberName = "CFGR1", DefinitionFile = path, NaturalKey = "ADC.CFGR1"
            });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "BIASEN", BitPosition = 0, Mask = 0x1, NaturalKey = "BIASEN"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_DisableBias",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx",
                Signature = "void LL_ADC_DisableBias(ADC_TypeDef *ADCx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_DisableBias",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        cases.Should().Contain(c => c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase));
        var clearCase = cases.First(c => c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase));
        const uint mask = 0x1u;
        const uint preserve = 0xA5A55A5Au & ~mask;
        clearCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CFGR1"
            && string.Equals(r.ValueHex, $"0x{preserve | mask:X}", StringComparison.OrdinalIgnoreCase));
        clearCase.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == (preserve | mask)
            && string.Equals(a.ExpectedHex, $"0x{preserve:X}", StringComparison.OrdinalIgnoreCase));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_SetBit_MaskRegister_Must_Match_Arrow_Member()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_mskmem_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_dac.h");
        // Wrong: mask declares CR but arrow targets SR — assert must stay on CR.OEN.
        File.WriteAllText(path, """
            #define DAC0_CR_OEN_Msk (0x4U)
            #define DAC0_SR_OEN_Msk (0x4U)
            __STATIC_INLINE void LL_DAC_EnableBufferOutput(DAC_TypeDef *DACx)
            {
                SET_BIT(DACx->SR, DAC0_CR_OEN_Msk);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("99999999-9999-9999-9999-999999999999");
        var fnId = Guid.Parse("88888888-8888-8888-8888-888888888888");
        var instId = Guid.Parse("77777777-7777-7777-7777-777777777771");
        var crId = Guid.Parse("66666666-6666-6666-6666-666666666661");
        var srId = Guid.Parse("66666666-6666-6666-6666-666666666662");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "DAC0", ModuleName = "DAC", NaturalKey = "DAC0"
            });
            init.RegisterDefinitions.AddRange(
                new RegisterDefinition
                {
                    Id = crId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "DAC_TypeDef", MemberName = "CR", DefinitionFile = path, NaturalKey = "DAC.CR"
                },
                new RegisterDefinition
                {
                    Id = srId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "DAC_TypeDef", MemberName = "SR", DefinitionFile = path, NaturalKey = "DAC.SR"
                });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = crId, Name = "OEN", BitPosition = 2, Mask = 0x4, NaturalKey = "OEN"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_DAC_EnableBufferOutput",
                PeripheralName = "DAC",
                ReturnType = "void",
                Parameters = "DAC_TypeDef *DACx",
                Signature = "void LL_DAC_EnableBufferOutput(DAC_TypeDef *DACx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_DAC_EnableBufferOutput",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "DACx", Type = "DAC_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var setCase = cases.First(c => c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        setCase.Name.Should().Contain("/CR.");
        setCase.InitialRegisters.Should().ContainSingle(r => r.MemberName == "CR");
        var reg = setCase.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        reg.MemberName.Should().Be("CR");
        reg.RuleSourceDetail.Should().Contain("成员/掩码不一致");
        reg.RuleSourceDetail.Should().Contain("->SR");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ModifyReg_MaskRegister_Must_Match_Arrow_Member()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_modmem_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
            #define ADC0_CR_ADCALDIF_Msk (0x10U)
            #define ADC0_CR_ADCALDIF_Val (0x1U)
            #define ADC0_CR_ADCALDIF_Pos (4U)
            __STATIC_INLINE void LL_ADC_SetCalibrationMode(ADC_TypeDef *ADCx, uint32_t Mode)
            {
                MODIFY_REG(ADCx->CFGR0, ADC0_CR_ADCALDIF_Msk, (((Mode) & ADC0_CR_ADCALDIF_Val) << ADC0_CR_ADCALDIF_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee");
        var fnId = Guid.Parse("bbbbbbbb-cccc-dddd-eeee-ffffffffffff");
        var instId = Guid.Parse("cccccccc-dddd-eeee-ffff-000000000001");
        var crId = Guid.Parse("dddddddd-eeee-ffff-0000-000000000001");
        var cfgrId = Guid.Parse("dddddddd-eeee-ffff-0000-000000000002");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "ADC0", ModuleName = "ADC", NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.AddRange(
                new RegisterDefinition
                {
                    Id = crId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "ADC_TypeDef", MemberName = "CR", DefinitionFile = path, NaturalKey = "ADC.CR"
                },
                new RegisterDefinition
                {
                    Id = cfgrId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                    StructName = "ADC_TypeDef", MemberName = "CFGR0", DefinitionFile = path, NaturalKey = "ADC.CFGR0"
                });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = crId, Name = "ADCALDIF", BitPosition = 4, Mask = 0x10, NaturalKey = "ADCALDIF"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_SetCalibrationMode",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx, uint32_t Mode",
                Signature = "void LL_ADC_SetCalibrationMode(ADC_TypeDef *ADCx, uint32_t Mode)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_SetCalibrationMode",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true },
                    new LlFunctionParameter { Name = "Mode", Type = "uint32_t", Position = 1, IsPointer = false }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var write = cases.First(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase));
        write.InitialRegisters.Should().ContainSingle(r => r.MemberName == "CR");
        write.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue).MemberName.Should().Be("CR");
        write.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue)
            .RuleSourceDetail.Should().Contain("成员/掩码不一致");
        (write.Notes ?? "").Should().Contain("体宏成员校验");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ModifyReg_TrustedClearMask_Survives_Wrong_Body_Regen()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_modify_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        // Wrong clear-mask from the start (ADCAL instead of ADCALDIF).
        File.WriteAllText(path, """
            #define ADC0_CR_ADCALDIF_Msk (0x10U)
            #define ADC0_CR_ADCALDIF_Val (0x1U)
            #define ADC0_CR_ADCALDIF_Pos (4U)
            #define ADC0_CR_ADCAL_Msk (0x8U)
            #define ADC0_CR_ADCAL_Val (0x1U)
            #define ADC0_CR_ADCAL_Pos (3U)
            __STATIC_INLINE void LL_ADC_SetCalibrationMode(ADC_TypeDef *ADCx, uint32_t Mode)
            {
                MODIFY_REG(ADCx->CR, ADC0_CR_ADCAL_Msk, (((Mode) & ADC0_CR_ADCAL_Val) << ADC0_CR_ADCAL_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("11111111-1111-1111-1111-111111111111");
        var fnId = Guid.Parse("22222222-2222-2222-2222-222222222222");
        var instId = Guid.Parse("33333333-3333-3333-3333-333333333333");
        var regId = Guid.Parse("44444444-4444-4444-4444-444444444444");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "ADC0", ModuleName = "ADC", NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "ADC_TypeDef", MemberName = "CR", DefinitionFile = path, NaturalKey = "ADC.CR"
            });
            init.RegisterFields.AddRange(
                new RegisterField { RegisterDefinitionId = regId, Name = "ADCALDIF", BitPosition = 4, Mask = 0x10, NaturalKey = "ADCALDIF" },
                new RegisterField { RegisterDefinitionId = regId, Name = "ADCAL", BitPosition = 3, Mask = 0x8, NaturalKey = "ADCAL" });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_SetCalibrationMode",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx, uint32_t Mode",
                Signature = "void LL_ADC_SetCalibrationMode(ADC_TypeDef *ADCx, uint32_t Mode)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_SetCalibrationMode",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true },
                    new LlFunctionParameter { Name = "Mode", Type = "uint32_t", Position = 1, IsPointer = false }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var write = cases.First(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase));
        var reg = write.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        const uint clearMask = 0x10u;
        const uint fieldExpected = 0x10u; // max field value << Pos
        const uint preserve = 0xA5A55A5Au & ~clearMask;
        const uint expectedAfter = preserve | fieldExpected;
        write.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CR"
            && !string.Equals(r.ValueHex, "0x0", StringComparison.OrdinalIgnoreCase));
        reg.ExpectedMask.Should().Be(preserve | clearMask);
        reg.ExpectedHex.Should().BeEquivalentTo($"0x{expectedAfter:X}");
        reg.RuleSourceDetail.Should().Contain("可信源");
        reg.RuleSourceDetail.Should().Contain("ADCALDIF");
        reg.RuleSourceDetail.Should().Contain("RMW");
        reg.RuleSourceDetail.Should().NotContain("ADCAL_Msk");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ReadBitShift_TrustedField_Survives_Wrong_Body_Regen()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_readshift_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        // Wrong read field from the start (ADCAL instead of ADCALDIF).
        File.WriteAllText(path, """
            #define ADC0_CR_ADCALDIF_Msk (0x10U)
            #define ADC0_CR_ADCALDIF_Pos (4U)
            #define ADC0_CR_ADCAL_Msk (0x8U)
            #define ADC0_CR_ADCAL_Pos (3U)
            __STATIC_INLINE uint32_t LL_ADC_GetCalibrationMode(const ADC_TypeDef *ADCx)
            {
                return (uint32_t)(READ_BIT_SHIFT(ADCx->CR, ADC0_CR_ADCAL_Msk, ADC0_CR_ADCAL_Pos));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("55555555-5555-5555-5555-555555555555");
        var fnId = Guid.Parse("66666666-6666-6666-6666-666666666666");
        var instId = Guid.Parse("77777777-7777-7777-7777-777777777777");
        var regId = Guid.Parse("88888888-8888-8888-8888-888888888888");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "ADC0", ModuleName = "ADC", NaturalKey = "ADC0"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "ADC_TypeDef", MemberName = "CR", DefinitionFile = path, NaturalKey = "ADC.CR"
            });
            init.RegisterFields.AddRange(
                new RegisterField { RegisterDefinitionId = regId, Name = "ADCALDIF", BitPosition = 4, Mask = 0x10, NaturalKey = "ADCALDIF" },
                new RegisterField { RegisterDefinitionId = regId, Name = "ADCAL", BitPosition = 3, Mask = 0x8, NaturalKey = "ADCAL" });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_GetCalibrationMode",
                PeripheralName = "ADC",
                ReturnType = "uint32_t",
                Parameters = "const ADC_TypeDef *ADCx",
                Signature = "uint32_t LL_ADC_GetCalibrationMode(const ADC_TypeDef *ADCx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_GetCalibrationMode",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "const ADC_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var read = cases.First(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase));
        read.Name.Should().Contain("ADCALDIF");
        const uint fieldBits = 0x10u;
        const uint bodyWrong = 0x8u; // ADCAL in wrong body — excluded from preserve
        const uint preserve = 0xA5A55A5Au & ~(fieldBits | bodyWrong);
        const uint preload = fieldBits | preserve;
        read.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CR" && string.Equals(r.ValueHex, $"0x{preload:X}", StringComparison.OrdinalIgnoreCase));
        var ret = read.Assertions.First(a => a.Kind == LlAssertionKind.ReturnValue);
        ret.ExpectedHex.Should().BeEquivalentTo("0x1");
        ret.RuleSourceDetail.Should().Contain("可信源");
        ret.RuleSourceDetail.Should().Contain("ADCALDIF");
        read.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.MemberName == "CR"
            && string.Equals(a.ExpectedHex, $"0x{preload:X}", StringComparison.OrdinalIgnoreCase)
            && (a.RuleSourceDetail ?? "").Contains("读不得改写", StringComparison.Ordinal));

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
