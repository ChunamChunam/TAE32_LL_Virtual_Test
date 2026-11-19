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

        // Assert* SET_BIT → assert-check (legacy set-check also accepted).
        cases.Should().Contain(c =>
            c.Name.Contains("assert-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        var setCase = cases.First(c =>
            c.Name.Contains("assert-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        setCase.Status.Should().Be(nameof(LlTestCaseStatus.Ready));
        // Write-back: baseline 0 → SET → read-back target mask bits.
        const uint mask = 0xBu;
        setCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CFGR1" && string.Equals(r.ValueHex, "0x0", StringComparison.OrdinalIgnoreCase));
        setCase.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.MemberName == "CFGR1"
            && a.ExpectedMask == mask
            && string.Equals(a.ExpectedHex, $"0x{mask:X}", StringComparison.OrdinalIgnoreCase));
        setCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.RegisterWrite);
        setCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.PreserveBits);
        setCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.Timeout);

        // Mutate body to wrong mask, then REGENERATE — trusted expected must stay PREPARING_START.
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
        var regenCase = regenerated.First(c =>
            c.Name.Contains("assert-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase));
        var expected = regenCase.Assertions.First(a => a.Kind == LlAssertionKind.RegisterValue);
        expected.ExpectedHex.Should().BeEquivalentTo($"0x{mask:X}");
        expected.ExpectedMask.Should().Be(mask);
        expected.RuleSourceDetail.Should().Contain("PREPARING_START");
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
        reg.ExpectedMask.Should().Be(mask);
        reg.ExpectedHex.Should().BeEquivalentTo("0x0");
        clearCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "IER"
            && string.Equals(r.ValueHex, $"0x{mask:X}", StringComparison.OrdinalIgnoreCase));
        reg.RuleSourceDetail.Should().Contain("AWD2");
        reg.RuleSourceDetail.Should().NotContain("AWD1IE_Msk");
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.RegisterWrite);
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.PreserveBits);
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
        clearCase.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "CFGR1"
            && string.Equals(r.ValueHex, $"0x{mask:X}", StringComparison.OrdinalIgnoreCase));
        clearCase.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == mask
            && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase));
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.RegisterWrite);
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.PreserveBits);
        clearCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
        setCase.Assertions.Should().Contain(a => a.Kind == LlAssertionKind.RegisterValue);
        setCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.RegisterWrite);
        setCase.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.NoUnexpectedWrite);

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
        writes.Should().ContainSingle("one representative write-check from LL body");
        writes.Should().Contain(c => c.Name.Contains("/seed/", StringComparison.OrdinalIgnoreCase));

        const uint clearMask = 0xFFFFu;
        var write = writes.Single();
        var initial = TestHarnessGenerator.ParseUIntExpression(
            write.InitialRegisters.Single(r => r.MemberName == "PSCR").ValueHex);
        initial.Should().Be(0u);
        var param = TestHarnessGenerator.ParseUIntExpression(
            write.Parameters.First(p => p.Name == "Prescaler").ValueExpression);
        var setMask = (param << 0) & clearMask;

        var target = write.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue && a.ExpectedMask == clearMask).Subject;
        TestHarnessGenerator.ParseUIntExpression(target.ExpectedHex!)
            .Should().Be(setMask, because: write.Name);
        write.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.BitField);
        write.Assertions.Should().NotContain(a => a.Kind == LlAssertionKind.RegisterWrite);

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
        const uint flag = 0x1u;
        clear.InitialRegisters.Should().ContainSingle(r =>
            r.MemberName == "ISR"
            && string.Equals(r.ValueHex, $"0x{flag:X}", StringComparison.OrdinalIgnoreCase));

        var flagAssert = clear.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue
            && a.ExpectedMask == flag
            && string.Equals(a.ExpectedHex, "0x0", StringComparison.OrdinalIgnoreCase)).Subject;
        flagAssert.RuleSourceDetail.Should().Contain("目标位");

        // Only target-bit read-back — no invented all-ones preserve assertions.
        clear.Assertions.Where(a => a.Kind == LlAssertionKind.RegisterValue)
            .Should().ContainSingle();

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
        reads.Should().ContainSingle("one representative read-check: write then Get");
        reads.Should().Contain(c => c.Name.Contains("/seed/", StringComparison.OrdinalIgnoreCase));

        const uint mask = 0xFFFFu;
        var read = reads.Single();
        var initial = TestHarnessGenerator.ParseUIntExpression(read.InitialRegisters.Single(r => r.MemberName == "PSCR").ValueHex);
        var expected = TestHarnessGenerator.ParseUIntExpression(
            read.Assertions.First(a => a.Kind == LlAssertionKind.ReturnValue).ExpectedHex!);
        expected.Should().Be((initial & mask) >> 0,
            because: $"case {read.Name}: expected must derive from initial write");

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

    [Fact]
    public async Task Generate_ClearBit_ChannelBit_Produces_DisableCheck_Not_Draft()
    {
        // LL_ADC_DisableIT_HLFIEx: CLEAR_BIT(ADCx->HIER, BIT(((Ch)%LL_ADC_CH_NUMS)))
        // Named-mask regex cannot match BIT(...) → previously timeout-only /draft → Skipped.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_chbit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
            #define LL_ADC_CH_NUMS (20UL)
            __STATIC_INLINE void LL_ADC_DisableIT_HLFIEx(ADC_TypeDef *ADCx, uint32_t Ch)
            {
                CLEAR_BIT(ADCx->HIER, BIT(((Ch) % LL_ADC_CH_NUMS)));
            }
            """);

        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.Parse("aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaa01");
        var fnId = Guid.Parse("bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbb01");
        var instId = Guid.Parse("cccccccc-cccc-cccc-cccc-cccccccccc01");
        var regId = Guid.Parse("dddddddd-dddd-dddd-dddd-dddddddddd01");

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
                MemberName = "HIER",
                DefinitionFile = path,
                NaturalKey = "ADC.HIER"
            });
            init.LlFunctions.Add(new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = "LL_ADC_DisableIT_HLFIEx",
                PeripheralName = "ADC",
                ReturnType = "void",
                Parameters = "ADC_TypeDef *ADCx, uint32_t Ch",
                Signature = "void LL_ADC_DisableIT_HLFIEx(ADC_TypeDef *ADCx, uint32_t Ch)",
                Form = "inline",
                FilePath = path,
                NaturalKey = path + "|LL_ADC_DisableIT_HLFIEx",
                ParseParameters =
                {
                    new LlFunctionParameter { Name = "ADCx", Type = "ADC_TypeDef *", Position = 0, IsPointer = true },
                    new LlFunctionParameter { Name = "Ch", Type = "uint32_t", Position = 1, IsPointer = false }
                }
            });
            await init.SaveChangesAsync();
        }

        var generator = new LlTestCaseGenerator(new SharedConnectionFactory(options));
        var cases = await generator.GenerateAsync(fnId);

        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        var disable = cases.Where(c =>
            c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase)).ToList();
        disable.Should().NotBeEmpty();
        disable.Should().OnlyContain(c => c.Status == nameof(LlTestCaseStatus.Ready));
        disable.Should().Contain(c => c.Name.Contains("HIER", StringComparison.OrdinalIgnoreCase));
        disable.Should().OnlyContain(c =>
            c.Assertions.Any(a => a.Kind == LlAssertionKind.RegisterValue)
            && c.InitialRegisters.Any(r => r.MemberName == "HIER"));
        disable.First().Parameters.Should().Contain(p =>
            p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase)
            && !string.IsNullOrWhiteSpace(p.ValueExpression));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Hrpwm_Nested_ScalePos_ChannelBit_Produces_EnableCheck()
    {
        // SET_BIT(HRPWMx->Common.OENR, BIT(((Pwmx)%N)*2 + OEN0A_Pos))
        var dir = Path.Combine(Path.GetTempPath(), "tae32_hrpwm_bit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_hrpwm.h");
        File.WriteAllText(path, """
            #define LL_HRPWM_PWMx_NUMS (5UL)
            #define HRPWM_COM_OENR_OEN0A_Pos (1UL)
            #define HRPWM_COM_OENR_OEN0A_Msk (0x2UL)
            __STATIC_INLINE void LL_HRPWM_EnableOutputA(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx)
            {
                SET_BIT(HRPWMx->Common.OENR, BIT(((Pwmx) % LL_HRPWM_PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos));
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "HRPWM", "HRPWM", "HRPWM_COM", "OENR",
            "LL_HRPWM_EnableOutputA", "void",
            "HRPWM_TypeDef *HRPWMx, uint32_t Pwmx",
            ("HRPWMx", "HRPWM_TypeDef *", true),
            ("Pwmx", "uint32_t", false));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        var enable = cases.Where(c => c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase)).ToList();
        enable.Should().NotBeEmpty();
        enable.Should().Contain(c =>
            c.Name.Contains("OENR", StringComparison.OrdinalIgnoreCase)
            && c.InitialRegisters.Any(r => r.InstanceName.Contains("COM", StringComparison.OrdinalIgnoreCase)
                                           || r.MemberName == "OENR"));
        // Pwmx=0 → bit = 0*2+1 = 1 → mask 0x2
        enable.Should().Contain(c =>
            c.Assertions.Any(a =>
                a.Kind == LlAssertionKind.RegisterValue
                && a.ExpectedMask == 0x2u));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Hrpwm_DualIndex_PwmArray_And_Fltx_Bit_Produces_EnableCheck()
    {
        // SET_BIT(HRPWMx->PWM[(Pwmx)%N].REG.FLTR, BIT((Fltx)%M)) — two distinct indices.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_hrpwm_flt_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_hrpwm.h");
        File.WriteAllText(path, """
            #define LL_HRPWM_PWMx_NUMS (5UL)
            #define LL_HRPWM_FLT_NUMS (6UL)
            __STATIC_INLINE void LL_HRPWM_EnableFault(HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Fltx)
            {
                SET_BIT(HRPWMx->PWM[(Pwmx) % LL_HRPWM_PWMx_NUMS].REG.FLTR, BIT((Fltx) % LL_HRPWM_FLT_NUMS));
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "HRPWM", "HRPWM", "HRPWM_SLV0", "FLTR",
            "LL_HRPWM_EnableFault", "void",
            "HRPWM_TypeDef *HRPWMx, uint32_t Pwmx, uint32_t Fltx",
            ("HRPWMx", "HRPWM_TypeDef *", true),
            ("Pwmx", "uint32_t", false),
            ("Fltx", "uint32_t", false));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        var enable = cases.Where(c => c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase)).ToList();
        enable.Should().NotBeEmpty();
        enable.Should().Contain(c =>
            c.Parameters.Any(p => p.Name.Equals("Pwmx", StringComparison.OrdinalIgnoreCase))
            && c.Parameters.Any(p => p.Name.Equals("Fltx", StringComparison.OrdinalIgnoreCase)
                                     && !string.IsNullOrWhiteSpace(p.ValueExpression)));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Eflash_LiteralBit_Produces_SetCheck()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_eflash_bit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_eflash.h");
        File.WriteAllText(path, """
            __STATIC_INLINE void LL_EFLASH_EnableSomething(EFLASH_TypeDef *EFLASHx)
            {
                SET_BIT(EFLASHx->LPR, BIT(2));
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "EFLASH", "EFLASH", "EFLASH", "LPR",
            "LL_EFLASH_EnableSomething", "void",
            "EFLASH_TypeDef *EFLASHx",
            ("EFLASHx", "EFLASH_TypeDef *", true));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        var set = cases.Where(c =>
            c.Name.Contains("set-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase)
            || c.Name.Contains("BIT2", StringComparison.OrdinalIgnoreCase)).ToList();
        set.Should().NotBeEmpty();
        set.Should().Contain(c =>
            c.Assertions.Any(a =>
                a.Kind == LlAssertionKind.RegisterValue && a.ExpectedMask == 0x4u));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Can_FilNum_Bit_Produces_EnableCheck()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_can_bit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_can.h");
        File.WriteAllText(path, """
            #define LL_CAN_ACCEPT_FILT_SLOT_NUMS (16UL)
            __STATIC_INLINE void LL_CAN_EnableAcceptFilter(CAN_TypeDef *CANx, uint32_t Fil_num)
            {
                SET_BIT(CANx->ACFEN, BIT(Fil_num % LL_CAN_ACCEPT_FILT_SLOT_NUMS));
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "CAN", "CAN", "CAN0", "ACFEN",
            "LL_CAN_EnableAcceptFilter", "void",
            "CAN_TypeDef *CANx, uint32_t Fil_num",
            ("CANx", "CAN_TypeDef *", true),
            ("Fil_num", "uint32_t", false));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        cases.Should().Contain(c => c.Name.Contains("enable-check", StringComparison.OrdinalIgnoreCase));
        cases.Should().Contain(c =>
            c.Parameters.Any(p => p.Name.Equals("Fil_num", StringComparison.OrdinalIgnoreCase)
                                  && !string.IsNullOrWhiteSpace(p.ValueExpression)));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_Adc_RegOffset_ChannelBit_Produces_DisableCheck()
    {
        var dir = Path.Combine(Path.GetTempPath(), "tae32_awd_bit_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32g58xx_ll_adc.h");
        File.WriteAllText(path, """
            #define LL_ADC_CH_NUMS (20UL)
            #define LL_ADC_AWDG_NUMS (3UL)
            #define LL_ADC_REG_OFFSET(__REG__, offset) (*((volatile uint32_t *)((uint32_t)((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))
            __STATIC_INLINE void LL_ADC_DisableAWDChannel(ADC_TypeDef *ADCx, uint32_t Num, uint32_t Ch)
            {
                CLEAR_BIT(LL_ADC_REG_OFFSET(ADCx->AWD0CR, ((Num) % LL_ADC_AWDG_NUMS)), BIT(((Ch) % LL_ADC_CH_NUMS)));
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "ADC", "ADC", "ADC0", "AWD0CR",
            "LL_ADC_DisableAWDChannel", "void",
            "ADC_TypeDef *ADCx, uint32_t Num, uint32_t Ch",
            ("ADCx", "ADC_TypeDef *", true),
            ("Num", "uint32_t", false),
            ("Ch", "uint32_t", false));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        cases.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));
        var disable = cases.Where(c => c.Name.Contains("disable-check", StringComparison.OrdinalIgnoreCase)).ToList();
        disable.Should().NotBeEmpty();
        disable.Should().Contain(c =>
            c.InitialRegisters.Any(r =>
                r.MemberName == "AWD0CR"
                || r.MemberName == "AWD1CR"
                || r.MemberName == "AWD2CR"));
        disable.Should().Contain(c =>
            c.Parameters.Any(p => p.Name.Equals("Ch", StringComparison.OrdinalIgnoreCase))
            && c.Parameters.Any(p => p.Name.Equals("Num", StringComparison.OrdinalIgnoreCase)));

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    [Fact]
    public async Task Generate_SetPLL0GVCO_LiteralClearField_Produces_WriteCheck()
    {
        // F561/G58 style: MODIFY_REG(reg, 0xc000UL, (((vco)) & 0x3UL) << 14UL) — no named _Msk.
        var dir = Path.Combine(Path.GetTempPath(), "tae32_pll_gvco_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(dir);
        var path = Path.Combine(dir, "tae32f561x_ll_rcu.h");
        File.WriteAllText(path, """
            __STATIC_INLINE void LL_RCU_SetPLL0GVCO(RCU_TypeDef *RCUx, uint32_t vco)
            {
                MODIFY_REG(RCUx->PLLCR, 0xc000UL, (((vco)) & 0x3UL) << 14UL);
            }
            """);

        var (options, conn, fnId) = await SeedBitOpFnAsync(
            dir, path, "RCU", "RCU", "RCU", "PLLCR",
            "LL_RCU_SetPLL0GVCO", "void",
            "RCU_TypeDef *RCUx, uint32_t vco",
            ("RCUx", "RCU_TypeDef *", true),
            ("vco", "uint32_t", false));

        var cases = await new LlTestCaseGenerator(new SharedConnectionFactory(options)).GenerateAsync(fnId);
        var writes = cases.Where(c => c.Name.Contains("write-check", StringComparison.OrdinalIgnoreCase)).ToList();
        writes.Should().ContainSingle("literal clear+shift MODIFY must emit write-check, not draft");
        writes.Should().NotContain(c => c.Name.Contains("/draft", StringComparison.OrdinalIgnoreCase));

        const uint clearMask = 0xc000u;
        var write = writes.Single();
        write.Status.Should().Be(nameof(LlTestCaseStatus.Ready));
        write.InitialRegisters.Should().ContainSingle(r => r.MemberName == "PLLCR");
        var vco = TestHarnessGenerator.ParseUIntExpression(
            write.Parameters.First(p => p.Name.Equals("vco", StringComparison.OrdinalIgnoreCase)).ValueExpression);
        var setMask = ((vco & 0x3u) << 14) & clearMask;
        setMask.Should().NotBe(0u);

        var target = write.Assertions.Should().Contain(a =>
            a.Kind == LlAssertionKind.RegisterValue && a.ExpectedMask == clearMask).Subject;
        TestHarnessGenerator.ParseUIntExpression(target.ExpectedHex!)
            .Should().Be(setMask, because: write.Name);
        (target.RuleSourceDetail ?? "").Should().Contain("lit-clear");

        Directory.Delete(dir, true);
        await conn.DisposeAsync();
    }

    private static async Task<(DbContextOptions<AppDbContext> Options, Microsoft.Data.Sqlite.SqliteConnection Conn, Guid FnId)>
        SeedBitOpFnAsync(
            string dir,
            string headerPath,
            string module,
            string periName,
            string instanceName,
            string memberName,
            string functionName,
            string returnType,
            string parametersCsv,
            params (string Name, string Type, bool IsPointer)[] parms)
    {
        var conn = new Microsoft.Data.Sqlite.SqliteConnection("Data Source=:memory:");
        await conn.OpenAsync();
        var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(conn).Options;
        var projectId = Guid.NewGuid();
        var fnId = Guid.NewGuid();
        var instId = Guid.NewGuid();
        var regId = Guid.NewGuid();

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
                Name = instanceName,
                ModuleName = module,
                NaturalKey = instanceName
            });
            init.RegisterDefinitions.Add(new RegisterDefinition
            {
                Id = regId,
                SdkProjectId = projectId,
                PeripheralInstanceId = instId,
                StructName = periName + "_TypeDef",
                MemberName = memberName,
                DefinitionFile = headerPath,
                NaturalKey = $"{module}.{memberName}"
            });
            var fn = new LlFunction
            {
                Id = fnId,
                SdkProjectId = projectId,
                FunctionName = functionName,
                PeripheralName = periName,
                ReturnType = returnType,
                Parameters = parametersCsv,
                Signature = $"{returnType} {functionName}({parametersCsv})",
                Form = "inline",
                FilePath = headerPath,
                NaturalKey = headerPath + "|" + functionName
            };
            for (var i = 0; i < parms.Length; i++)
            {
                fn.ParseParameters.Add(new LlFunctionParameter
                {
                    Name = parms[i].Name,
                    Type = parms[i].Type,
                    Position = i,
                    IsPointer = parms[i].IsPointer
                });
            }

            init.LlFunctions.Add(fn);
            await init.SaveChangesAsync();
        }

        return (options, conn, fnId);
    }

    private sealed class SharedConnectionFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public SharedConnectionFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
