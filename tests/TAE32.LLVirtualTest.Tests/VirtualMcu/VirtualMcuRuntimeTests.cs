using FluentAssertions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Tests.VirtualMcu;

public class RegisterSemanticsEngineTests
{
    [Theory]
    [InlineData(8, 0xFFu)]
    [InlineData(16, 0xFFFFu)]
    [InlineData(32, 0xFFFFFFFFu)]
    public void WidthMask_Supports_8_16_32(int bits, uint expected)
        => RegisterSemanticsEngine.WidthMask(bits).Should().Be(expected);

    [Fact]
    public void UnknownAccess_DefaultsToRw_WithLimitation()
    {
        var b = RegisterSemanticsEngine.ResolveBehavior("Unknown", true, out var lim, out _);
        b.Should().Be(VirtualRegisterBehavior.ReadWrite);
        lim.Should().Be(SimulationLimitationKind.UnknownAccessDefaultedToRw);
    }

    [Fact]
    public void Write1Clear_ClearsMatchingBits()
    {
        RegisterSemanticsEngine.TryApplyWrite(
            VirtualRegisterBehavior.Write1Clear, current: 0xFF, written: 0x0F,
            writableMask: 0xFF, widthMask: 0xFF, out var next, out var result, out _)
            .Should().BeTrue();
        next.Should().Be(0xF0u);
        result.Should().Be(VirtualAccessResult.Ok);
    }

    [Fact]
    public void Write0Clear_ClearsZeroBits()
    {
        RegisterSemanticsEngine.TryApplyWrite(
            VirtualRegisterBehavior.Write0Clear, current: 0xFF, written: 0xF0,
            writableMask: 0xFF, widthMask: 0xFF, out var next, out _, out _)
            .Should().BeTrue();
        next.Should().Be(0xF0u);
    }

    [Fact]
    public void ReadOnly_RejectsWrite()
    {
        RegisterSemanticsEngine.TryApplyWrite(
            VirtualRegisterBehavior.ReadOnly, 1, 2, 0xFF, 0xFF, out _, out var result, out _)
            .Should().BeFalse();
        result.Should().Be(VirtualAccessResult.RejectedReadOnly);
    }

    [Fact]
    public void ReadClear_ZerosStorageOnRead()
    {
        RegisterSemanticsEngine.TryApplyRead(
            VirtualRegisterBehavior.ReadClear, 0xAB, out var read, out var next, out _, out _)
            .Should().BeTrue();
        read.Should().Be(0xABu);
        next.Should().Be(0u);
    }
}

public class VirtualMcuRuntimeTests
{
    private static VirtualRegisterSlot Slot(
        string instance, string member, VirtualRegisterBehavior behavior,
        uint reset = 0, int width = 32, uint? addr = null, string access = "Rw",
        uint writableMask = 0xFFFFFFFFu, params (string name, int pos, int width)[] fields)
    {
        var slot = new VirtualRegisterSlot
        {
            DefinitionId = Guid.NewGuid(),
            ChipModelName = "TAE32G58xx",
            ModuleName = instance.StartsWith("GPIO") ? "GPIO" : instance,
            InstanceName = instance,
            StructName = instance + "_Type",
            MemberName = member,
            AbsoluteAddress = addr,
            WidthBits = width,
            ResetValue = reset,
            CurrentValue = reset,
            AccessAttribute = access,
            Behavior = behavior,
            WritableMask = writableMask
        };
        foreach (var (name, pos, w) in fields)
        {
            var mask = w >= 32 ? 0xFFFFFFFFu : ((1u << w) - 1u) << pos;
            slot.Fields.Add(new VirtualBitFieldSlot
            {
                Name = name,
                BitPosition = pos,
                BitWidth = w,
                Mask = mask
            });
        }
        return slot;
    }

    private static VirtualMcuRuntime CreateRuntime(params VirtualRegisterSlot[] slots)
    {
        var rt = new VirtualMcuRuntime(Guid.NewGuid(), new VirtualMcuCreateOptions
        {
            ChipModelName = "TAE32G58xx",
            DisplayName = "test"
        }, "TAE32G58xx");
        rt.LoadSlots(slots);
        return rt;
    }

    [Fact]
    public void ReadWrite_BitMask_And_BitField()
    {
        var rt = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite, addr: 0x40020014,
            fields: ("ODR0", 0, 1)));

        rt.Write("GPIOA", "ODR", 0x5A5A5A5A, null).Result.Should().Be(VirtualAccessResult.Ok);
        rt.Read("GPIOA", "ODR", null).Value.Should().Be(0x5A5A5A5Au);

        rt.SetBits("GPIOA", "ODR", 0x1, null).ValueAfter.Should().Be(0x5A5A5A5Bu);
        rt.ClearBits("GPIOA", "ODR", 0x1, null).ValueAfter.Should().Be(0x5A5A5A5Au);

        rt.WriteBitField("GPIOA", "ODR", "ODR0", 1, null).Result.Should().Be(VirtualAccessResult.Ok);
        rt.Read("GPIOA", "ODR", null).Value.Should().Be(0x5A5A5A5Bu);

        rt.ModifyBits("GPIOA", "ODR", clearMask: 0xFF, setMask: 0x11, null)
            .ValueAfter.Should().Be((0x5A5A5A5Bu & ~0xFFu) | 0x11u);
    }

    [Fact]
    public void ResetValue_RestoresOnReset()
    {
        var rt = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite, reset: 0x1234));
        rt.Write("GPIOA", "ODR", 0xFFFF, null);
        rt.ResetRegister("GPIOA", "ODR", null).ValueAfter.Should().Be(0x1234u);
        rt.Write("GPIOA", "ODR", 0x1, null);
        rt.Reset();
        rt.Read("GPIOA", "ODR", null).Value.Should().Be(0x1234u);
    }

    [Fact]
    public void Write1Clear_And_Write0Clear()
    {
        var rt = CreateRuntime(
            Slot("UART0", "ICR", VirtualRegisterBehavior.Write1Clear, reset: 0xFF, access: "W1c"),
            Slot("UART0", "SR", VirtualRegisterBehavior.Write0Clear, reset: 0xFF, access: "W0c"));

        rt.Write("UART0", "ICR", 0x0F, null).ValueAfter.Should().Be(0xF0u);
        rt.Write("UART0", "SR", 0xF0, null).ValueAfter.Should().Be(0xF0u);
    }

    [Fact]
    public void ReadOnly_IsProtected()
    {
        var rt = CreateRuntime(Slot("ADC0", "DR", VirtualRegisterBehavior.ReadOnly, reset: 0x42, access: "Ro"));
        var w = rt.Write("ADC0", "DR", 0x99, null);
        w.Result.Should().Be(VirtualAccessResult.RejectedReadOnly);
        rt.Read("ADC0", "DR", null).Value.Should().Be(0x42u);
    }

    [Fact]
    public void AddressOutOfRange_And_WidthMismatch()
    {
        var rt = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite, addr: 0x40020014, width: 32));
        rt.ReadByAddress(0xDEADBEEF, 32, null).Result.Should().Be(VirtualAccessResult.AddressOutOfRange);
        rt.WriteByAddress(0x40020014, 1, 16, null).Result.Should().Be(VirtualAccessResult.WidthMismatch);
        rt.ReadByAddress(0x40020014, 32, null).Result.Should().Be(VirtualAccessResult.Ok);
    }

    [Fact]
    public void MultiInstance_Isolation()
    {
        var a = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite));
        var b = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite));
        a.Write("GPIOA", "ODR", 0x1111, null);
        b.Write("GPIOA", "ODR", 0x2222, null);
        a.Read("GPIOA", "ODR", null).Value.Should().Be(0x1111u);
        b.Read("GPIOA", "ODR", null).Value.Should().Be(0x2222u);
        a.Id.Should().NotBe(b.Id);
    }

    [Fact]
    public void Snapshot_Restore()
    {
        var rt = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite, reset: 0));
        rt.Write("GPIOA", "ODR", 0xABCDu, null);
        var snap = rt.TakeSnapshot("s1");
        rt.Write("GPIOA", "ODR", 0, null);
        rt.RestoreSnapshot(snap.SnapshotId);
        rt.Read("GPIOA", "ODR", null).Value.Should().Be(0xABCDu);
    }

    [Fact]
    public void AccessTrace_FilterByRegisterAndFunction()
    {
        var rt = CreateRuntime(Slot("GPIOA", "ODR", VirtualRegisterBehavior.ReadWrite));
        var ctx = new VirtualAccessContext { LlFunctionName = "LL_GPIO_SetPin", SourceFile = "gpio.h", SourceLine = 10 };
        rt.Write("GPIOA", "ODR", 1, ctx);
        rt.Read("GPIOA", "ODR", ctx);

        var all = rt.Trace.Query(new VirtualAccessFilter { Take = 50 });
        all.Should().NotBeEmpty();

        var byFn = rt.Trace.Query(new VirtualAccessFilter { LlFunctionName = "LL_GPIO_SetPin", Take = 50 });
        byFn.Should().OnlyContain(x => x.LlFunctionName == "LL_GPIO_SetPin");

        var byReg = rt.Trace.Query(new VirtualAccessFilter { RegisterName = "ODR", Take = 50 });
        byReg.Should().OnlyContain(x => x.RegisterName.Contains("ODR"));
    }

    [Fact]
    public void ReservedBits_ProtectedByWritableMask()
    {
        // only bit0 writable
        var rt = CreateRuntime(Slot("GPIOA", "MODER", VirtualRegisterBehavior.ReadWrite,
            writableMask: 0x1, fields: ("MODE0", 0, 1)));
        rt.Write("GPIOA", "MODER", 0xFFFFFFFF, null).ValueAfter.Should().Be(0x1u);
    }
}

public class VirtualMcuServiceIsolationTests
{
    private static async Task<(VirtualMcuService svc, Guid projectId, Guid chipId)> SeedAsync()
    {
        var dbPath = Path.Combine(Path.GetTempPath(), "tae32_vmcu_" + Guid.NewGuid().ToString("N") + ".db");
        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite($"Data Source={dbPath}")
            .Options;

        await using (var db = new AppDbContext(options))
        {
            await db.Database.EnsureCreatedAsync();
            var project = new SdkProject
            {
                Id = Guid.NewGuid(),
                Name = "t",
                SdkRootPath = ".",
                ScanResultsPath = ".",
                IsActive = true
            };
            var chip = new Chip
            {
                Id = Guid.NewGuid(),
                SdkProjectId = project.Id,
                ModelName = "TAE32G58xx"
            };
            var inst = new PeripheralInstance
            {
                Id = Guid.NewGuid(),
                SdkProjectId = project.Id,
                ChipId = chip.Id,
                Name = "GPIOA",
                ModuleName = "GPIO",
                TypeDefName = "GPIO_TypeDef",
                BaseAddress = 0x40020000,
                BaseAddressStatus = "Confirmed"
            };
            var regRw = new RegisterDefinition
            {
                Id = Guid.NewGuid(),
                SdkProjectId = project.Id,
                ChipId = chip.Id,
                PeripheralInstanceId = inst.Id,
                StructName = "GPIOA_Type",
                MemberName = "ODR",
                OffsetBytes = 0x14,
                OffsetStatus = "Confirmed",
                AbsoluteAddress = 0x40020014,
                AbsoluteAddressStatus = "Confirmed",
                WidthBits = 32,
                ResetValue = "0x0",
                AccessAttribute = "Rw",
                ParseStatus = "Complete",
                NaturalKey = "GPIOA.ODR",
                DefinitionFile = "chip.h"
            };
            var regRo = new RegisterDefinition
            {
                Id = Guid.NewGuid(),
                SdkProjectId = project.Id,
                ChipId = chip.Id,
                PeripheralInstanceId = inst.Id,
                StructName = "GPIOA_Type",
                MemberName = "IDR",
                OffsetBytes = 0x10,
                OffsetStatus = "Confirmed",
                AbsoluteAddress = 0x40020010,
                AbsoluteAddressStatus = "Confirmed",
                WidthBits = 32,
                ResetValue = "0x0",
                AccessAttribute = "Ro",
                ParseStatus = "Complete",
                NaturalKey = "GPIOA.IDR",
                DefinitionFile = "chip.h"
            };
            var field = new RegisterField
            {
                Id = Guid.NewGuid(),
                RegisterDefinitionId = regRw.Id,
                Name = "ODR0",
                BitPosition = 0,
                BitWidth = 1,
                Mask = 1,
                NaturalKey = "GPIOA.ODR.ODR0"
            };
            db.SdkProjects.Add(project);
            db.Chips.Add(chip);
            db.PeripheralInstances.Add(inst);
            db.RegisterDefinitions.AddRange(regRw, regRo);
            db.RegisterFields.Add(field);
            await db.SaveChangesAsync();
        }

        var factory = new TestDbFactory(options);
        var svc = new VirtualMcuService(factory);
        // re-open to get ids
        await using var db2 = new AppDbContext(options);
        var chipId = await db2.Chips.Select(c => c.Id).FirstAsync();
        var projectId = await db2.SdkProjects.Select(p => p.Id).FirstAsync();
        return (svc, projectId, chipId);
    }

    [Fact]
    public async Task Service_CreateInit_Isolate_Snapshot_Trace()
    {
        var (svc, projectId, chipId) = await SeedAsync();

        var a = await svc.CreateAsync(new VirtualMcuCreateOptions
        {
            SdkProjectId = projectId,
            ChipId = chipId,
            ProtectUnmappedBitsAsReserved = false
        });
        await svc.InitializeAsync(a.Id);

        var b = await svc.CreateAsync(new VirtualMcuCreateOptions
        {
            SdkProjectId = projectId,
            ChipId = chipId,
            ProtectUnmappedBitsAsReserved = false
        });
        await svc.InitializeAsync(b.Id);

        await svc.WriteAsync(a.Id, "GPIOA", "ODR", 0x11);
        await svc.WriteAsync(b.Id, "GPIOA", "ODR", 0x22);
        (await svc.ReadAsync(a.Id, "GPIOA", "ODR")).Value.Should().Be(0x11u);
        (await svc.ReadAsync(b.Id, "GPIOA", "ODR")).Value.Should().Be(0x22u);

        (await svc.WriteAsync(a.Id, "GPIOA", "IDR", 0x1)).Result.Should().Be(VirtualAccessResult.RejectedReadOnly);

        var snap = await svc.TakeSnapshotAsync(a.Id, "t");
        await svc.WriteAsync(a.Id, "GPIOA", "ODR", 0);
        await svc.RestoreSnapshotAsync(a.Id, snap.SnapshotId);
        (await svc.ReadAsync(a.Id, "GPIOA", "ODR")).Value.Should().Be(0x11u);

        var trace = await svc.GetAccessTraceAsync(a.Id, new VirtualAccessFilter { Take = 100 });
        trace.Should().NotBeEmpty();
        trace.Any(t => t.AccessKind == VirtualAccessKind.Snapshot).Should().BeTrue();

        await svc.DestroyAsync(a.Id);
        var act = async () => await svc.ReadAsync(a.Id, "GPIOA", "ODR");
        await act.Should().ThrowAsync<KeyNotFoundException>();
    }

    private sealed class TestDbFactory : IDbContextFactory<AppDbContext>
    {
        private readonly DbContextOptions<AppDbContext> _options;
        public TestDbFactory(DbContextOptions<AppDbContext> options) => _options = options;
        public AppDbContext CreateDbContext() => new(_options);
    }
}
