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
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.RegisterWrite);
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.PreserveBits);
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);
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
        var clearCase = cases.First(c => c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase));
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
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.RegisterWrite);
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.PreserveBits);
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
        cases.Should().Contain(c => c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase));
        var clearCase = cases.First(c => c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase));
        const uint mask = 0x1u;
        const uint preserve = 0xA5A55A5Au & ~mask;
        clearCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CFGR1"
            && string.Equals(r.ValueHex, $"0x{preserve | mask:X}", StringComparison.OrdinalIgnoreCase));
        clearCase.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == (preserve | mask)
            && string.Equals(a.ExpectedHex, $"0x{preserve:X}", StringComparison.OrdinalIgnoreCase));
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.RegisterWrite);
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.PreserveBits);
        clearCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
        var setCase = cases.First(c => c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase));
        setCase.Name.Should().Contain("/CR.");
        setCase.InitialRegisters.Should().ContainSingle(r => r.MemberName == "CR");
        var reg = setCase.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        reg.MemberName.Should().Be("CR");
        reg.RuleSourceDetail.Should().Contain("成员/掩码不一致");
        reg.RuleSourceDetail.Should().Contain("->SR");
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.RegisterWrite);
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
    public async Task Generate_SetPrescaler_ModifyReg_Uses_Cmsis_Formula()
    {
        // Bug repro: clearMask wrongly narrow → expected became initial|7 (0xA5A55A5F) instead of 0xA5A50007.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_setpsc_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_wwdg.h");
        File.WriteAllText(path, """
            #define WWDG_PSCR_PSC_Msk (0xFFFFUL)
            #define WWDG_PSCR_PSC_Pos (0UL)
            __STATIC_INLINE void LL_WWDG_SetPrescaler(WWDG_TypeDef *WWDGx, uint32_t Prescaler)
            {
                MODIFY_REG(WWDGx->PSCR, WWDG_PSCR_PSC_Msk, ((Prescaler) << WWDG_PSCR_PSC_Pos));
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
                Id = instId, SdkProjectId = projectId, Name = "WWDG", ModuleName = "WWDG", NaturalKey = "WWDG"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "WWDG_TypeDef", MemberName = "PSCR", DefinitionFile = path, NaturalKey = "WWDG.PSCR"
            });
            // Intentionally wrong DB mask — generator must prefer header 0xFFFF.
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "PSC", BitPosition = 0, Mask = 0x7, NaturalKey = "PSC",
                DefinitionFile = path, MskMacroName = "WWDG_PSCR_PSC_Msk", PosMacroName = "WWDG_PSCR_PSC_Pos"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_WWDG_SetPrescaler",
                PeripheralName = "WWDG",
                ReturnType = "void",
                Parameters = "WWDG_TypeDef *WWDGx, uint32_t Prescaler",
                Signature = "void LL_WWDG_SetPrescaler(WWDG_TypeDef *WWDGx, uint32_t Prescaler)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_WWDG_SetPrescaler",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "WWDGx", Type = "WWDG_TypeDef *", Position = 0, IsPointer = true },
                    new LlFunctionParameter { Name = "Prescaler", Type = "uint32_t", Position = 1, IsPointer = false }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var writes = cases.Where(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        writes.Should().HaveCountGreaterThan(1);
        writes.Should().Contain(c => c.Name.Contains("/one/", StringComparison.OrdinalIgnoreCase));
        writes.Should().Contain(c => c.Name.Contains("/max/", StringComparison.OrdinalIgnoreCase));

        const uint clearMask = 0xFFFFu;
        foreach (var write in writes)
        {
            var initial = TestHarnessGenerator.ParseUIntExpression(
                write.InitialRegisters.Single(r => r.MemberName == "PSCR").ValueHex);
            var param = TestHarnessGenerator.ParseUIntExpression(
                write.Parameters.First(p => p.Name == "Prescaler").ValueExpression);
            var setMask = (param << 0) & clearMask;
            var expected = (initial & ~clearMask) | setMask;

            var full = write.Assertions.First(a =>
                a.Kind == LlAssertionKind.RegisterValue && a.ExpectedMask == 0xFFFFFFFFu);
            TestHarnessGenerator.ParseUIntExpression(full.ExpectedHex!)
                .Should().Be(expected, because: write.Name);

            // Must never be the old bug pattern initial|param when low bits were not cleared.
            if ((initial & clearMask) != 0 && setMask != (initial & clearMask))
            {
                var wrongOr = initial | setMask;
                TestHarnessGenerator.ParseUIntExpression(full.ExpectedHex!).Should().NotBe(wrongOr);
            }

            write.Assertions.Should().Contain(a =>
                a.Kind == LlAssertionKind.RegisterValue
                && a.ExpectedMask == clearMask
                && (a.RuleSourceDetail ?? "").Contains("目标位域", StringComparison.Ordinal));

            // BitField must use chip 0xFFFF, NOT stale DB 0x7 → Expected 6/7.
            var bf = write.Assertions.Should().Contain(a =>
                a.Kind == LlAssertionKind.BitField && a.BitFieldName == "PSC").Subject;
            bf.ExpectedMask.Should().Be(clearMask);
            TestHarnessGenerator.ParseUIntExpression(bf.ExpectedHex!)
                .Should().Be((setMask & clearMask) >> 0, because: write.Name);
            (bf.RuleSourceDetail ?? "").Should().Contain("已忽略 DB.Mask=0x7");
        }

        // Concrete user case: Prescaler=7 with interference preload shape.
        var seven = writes.FirstOrDefault(w =>
            TestHarnessGenerator.ParseUIntExpression(
                w.Parameters.First(p => p.Name == "Prescaler").ValueExpression) == 7u);
        if (seven is not null)
        {
            var initial = TestHarnessGenerator.ParseUIntExpression(seven.InitialRegisters.Single().ValueHex);
            var expected = (initial & ~clearMask) | 7u;
            TestHarnessGenerator.ParseUIntExpression(
                    seven.Assertions.First(a => a.ExpectedMask == 0xFFFFFFFFu).ExpectedHex!)
                .Should().Be(expected);
        }

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ClearFlag_W1C_Asserts_Flag_Zero_And_Others_Preserved()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_wwdg_w1c_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_wwdg.h");
        File.WriteAllText(path, """
            #define WWDG_ISR_EWIF_Msk (0x1UL)
            #define WWDG_ISR_EWIF_Pos (0U)
            __STATIC_INLINE void LL_WWDG_ClearFlag_EWIF(WWDG_TypeDef *WWDGx)
            {
                ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));
                WRITE_REG(WWDGx->ISR, WWDG_ISR_EWIF_Msk);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("10101010-1010-1010-1010-101010101010");
        var fnId = Guid.Parse("20202020-2020-2020-2020-202020202020");
        var instId = Guid.Parse("30303030-3030-3030-3030-303030303030");
        var regId = Guid.Parse("40404040-4040-4040-4040-404040404040");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "WWDG", ModuleName = "WWDG", NaturalKey = "WWDG"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "WWDG_TypeDef", MemberName = "ISR", DefinitionFile = path, NaturalKey = "WWDG.ISR",
                AccessAttribute = "Rw"
            });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "EWIF", BitPosition = 0, Mask = 0x1, NaturalKey = "EWIF",
                AccessAttribute = "Rw"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_WWDG_ClearFlag_EWIF",
                PeripheralName = "WWDG",
                ReturnType = "void",
                Parameters = "WWDG_TypeDef *WWDGx",
                Signature = "void LL_WWDG_ClearFlag_EWIF(WWDG_TypeDef *WWDGx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_WWDG_ClearFlag_EWIF",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "WWDGx", Type = "WWDG_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var clear = cases.Should().ContainSingle(c =>
            c.Name.Contains("clear-check", StringComparison.OrdinalIgnoreCase)).Subject;
        clear.Status.Should().Be(nameof(LlTestCaseStatus.Ready));
        clear.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "ISR"
            && string.Equals(r.ValueHex, "0xFFFFFFFF", StringComparison.OrdinalIgnoreCase));

        const uint flag = 0x1u;
        const uint preserve = 0xFFFFFFFFu & ~flag;
        var flagAssert = clear.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == flag
            && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)).Subject;
        flagAssert.RuleSourceDetail.Should().Contain("目标位");

        var keepAssert = clear.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == preserve
            && string.Equals(a.ExpectedHex, $"0x{preserve:X}", StringComparison.OrdinalIgnoreCase)).Subject;
        keepAssert.RuleSourceDetail.Should().Contain("非目标位");

        // Must NOT expect whole register == 0 under a wide mask.
        clear.Assertions.Where(a => a.Kind == LlAssertionKind.RegisterValue)
            .Should().NotContain(a =>
                a.ExpectedMask.HasValue
                && a.ExpectedMask.Value >= 0xFFFFu
                && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ReadBit_Then_Shift_Pos_Produces_ReadCheck()
    {
        // WWDG/IWDG style: (READ_BIT(reg->MEM, Msk) >> Pos) — not READ_BIT_SHIFT macro.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_readbitpos_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_wwdg.h");
        File.WriteAllText(path, """
            #define WWDG_WVR_WV_Msk (0x7FU)
            #define WWDG_WVR_WV_Pos (0U)
            __STATIC_INLINE uint32_t LL_WWDG_GetWindow(const WWDG_TypeDef *WWDGx)
            {
                ASSERT_INLINE_PARAM(IS_WWDG_ALL_INSTANCE(WWDGx));
                return (uint32_t)(READ_BIT(WWDGx->WVR, WWDG_WVR_WV_Msk) >> WWDG_WVR_WV_Pos);
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
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "WWDG", ModuleName = "WWDG", NaturalKey = "WWDG"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "WWDG_TypeDef", MemberName = "WVR", DefinitionFile = path, NaturalKey = "WWDG.WVR"
            });
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "WV", BitPosition = 0, Mask = 0x7F, NaturalKey = "WV"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_WWDG_GetWindow",
                PeripheralName = "WWDG",
                ReturnType = "uint32_t",
                Parameters = "const WWDG_TypeDef *WWDGx",
                Signature = "uint32_t LL_WWDG_GetWindow(const WWDG_TypeDef *WWDGx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_WWDG_GetWindow",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "WWDGx", Type = "const WWDG_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().NotBeEmpty();
        reads.Should().Contain(c => c.Name.Contains("WV", StringComparison.OrdinalIgnoreCase));
        foreach (var read in reads)
        {
            read.Status.Should().Be(nameof(LlTestCaseStatus.Ready));
            var initial = TestHarnessGenerator.ParseUIntExpression(read.InitialRegisters.Single().ValueHex);
            var expected = TestHarnessGenerator.ParseUIntExpression(
                read.Assertions.First(a => a.Kind == LlAssertionKind.ReturnValue).ExpectedHex!);
            // Must match (initial & 0x7F) >> 0
            expected.Should().Be(initial & 0x7Fu);
        }
        cases.Should().NotContain(c => c.Name.EndsWith("/draft", StringComparison.OrdinalIgnoreCase));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_GetPrescaler_Expected_Matches_Initial_And_Mask()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_getpsc_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_wwdg.h");
        File.WriteAllText(path, """
            #define WWDG_PSCR_PSC_Msk (0xFFFFUL)
            #define WWDG_PSCR_PSC_Pos (0UL)
            __STATIC_INLINE uint32_t LL_WWDG_GetPrescaler(const WWDG_TypeDef *WWDGx)
            {
                return (uint32_t)(READ_BIT(WWDGx->PSCR, WWDG_PSCR_PSC_Msk) >> WWDG_PSCR_PSC_Pos);
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("51515151-5151-5151-5151-515151515151");
        var fnId = Guid.Parse("52525252-5252-5252-5252-525252525252");
        var instId = Guid.Parse("53535353-5353-5353-5353-535353535353");
        var regId = Guid.Parse("54545454-5454-5454-5454-545454545454");

        await using (var init = new AppDbContext(options))
        {
            await init.Database.EnsureCreatedAsync();
            init.SdkProjects.Add(new SdkProject
            {
                Id = projectId, Name = "t", SdkRootPath = dir, ScanResultsPath = dir, IsActive = true
            });
            init.PeripheralInstances.Add(new PeripheralInstance
            {
                Id = instId, SdkProjectId = projectId, Name = "WWDG", ModuleName = "WWDG", NaturalKey = "WWDG"
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId, SdkProjectId = projectId, PeripheralInstanceId = instId,
                StructName = "WWDG_TypeDef", MemberName = "PSCR", DefinitionFile = path, NaturalKey = "WWDG.PSCR"
            });
            // Intentionally wrong narrow mask in DB — generator must prefer header #define 0xFFFF.
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "PSC", BitPosition = 0, Mask = 0x1, NaturalKey = "PSC",
                DefinitionFile = path, MskMacroName = "WWDG_PSCR_PSC_Msk", PosMacroName = "WWDG_PSCR_PSC_Pos"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_WWDG_GetPrescaler",
                PeripheralName = "WWDG",
                ReturnType = "uint32_t",
                Parameters = "const WWDG_TypeDef *WWDGx",
                Signature = "uint32_t LL_WWDG_GetPrescaler(const WWDG_TypeDef *WWDGx)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_WWDG_GetPrescaler",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "WWDGx", Type = "const WWDG_TypeDef *", Position = 0, IsPointer = true }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().HaveCountGreaterThan(1); // min/one/max/…
        reads.Should().Contain(c => c.Name.Contains("/min/", StringComparison.OrdinalIgnoreCase));
        reads.Should().Contain(c => c.Name.Contains("/max/", StringComparison.OrdinalIgnoreCase));

        const uint mask = 0xFFFFu;
        foreach (var read in reads)
        {
            var initial = TestHarnessGenerator.ParseUIntExpression(read.InitialRegisters.Single(r => r.MemberName == "PSCR").ValueHex);
            var expected = TestHarnessGenerator.ParseUIntExpression(
                read.Assertions.First(a => a.Kind == LlAssertionKind.ReturnValue).ExpectedHex!);
            expected.Should().Be((initial & mask) >> 0,
                because: $"case {read.Name}: expected must derive from initial");
            // Must not be the old bug: expected=1 while low 16 bits are pattern noise.
            if ((initial & mask) != 1)
                expected.Should().NotBe(1u);
        }

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_ReadBitShift_Uses_Body_Mask_And_Derives_Expected_From_Initial()
    {
        // Get/Read must follow the body macros the compiled LL actually uses.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_readshift_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
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
            init.RegisterFields.Add(new RegisterField
            {
                RegisterDefinitionId = regId, Name = "ADCAL", BitPosition = 3, Mask = 0x8, NaturalKey = "ADCAL",
                DefinitionFile = path
            });
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
        var reads = cases.Where(c => c.Name.Contains("read-check", StringComparison.OrdinalIgnoreCase)).ToList();
        reads.Should().NotBeEmpty();
        reads.Should().OnlyContain(c => c.Name.Contains("ADCAL", StringComparison.OrdinalIgnoreCase));
        const uint mask = 0x8u;
        const int pos = 3;
        foreach (var read in reads)
        {
            var initial = TestHarnessGenerator.ParseUIntExpression(read.InitialRegisters.Single().ValueHex);
            var expected = TestHarnessGenerator.ParseUIntExpression(
                read.Assertions.First(a => a.Kind == LlAssertionKind.ReturnValue).ExpectedHex!);
            expected.Should().Be((initial & mask) >> pos);
            read.Assertions.Should().Contain(a =>
                a.Kind == LlAssertionKind.RegisterValue
                && a.MemberName == "CR"
                && string.Equals(a.ExpectedHex, $"0x{initial:X}", StringComparison.OrdinalIgnoreCase));
        }

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
