using System.Runtime.InteropServices;
using FluentAssertions;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;

namespace TAE32.LLVirtualTest.Tests.TestEngine;

public class NativeTestHostAdcImageTests
{
    [Fact]
    public async Task AllocateAndFill_Adc_Hisr_Maps_At_Offset_0x180_With_Preload()
    {
        var sdkRoot = FindSdkRoot();
        if (sdkRoot is null) return;

        const uint adc0Base = 0x40038000u;
        const uint hisrAbs = adc0Base + 0x180u;
        const uint preload = 0xFFFFFFFFu;

        // Simulate the failure mode: GetAll returns nameless-address slots; only GetRegister has abs.
        var hisrLive = new VirtualRegisterView
        {
            InstanceName = "ADC0",
            ModuleName = "ADC",
            StructName = "ADC0_Type",
            MemberName = "HISR",
            AbsoluteAddress = hisrAbs,
            WidthBits = 32,
            CurrentValue = preload
        };
        var nameless = new VirtualRegisterView
        {
            InstanceName = "ADC0",
            ModuleName = "ADC0",
            StructName = "ADC_TypeDef",
            MemberName = "HISR",
            AbsoluteAddress = null,
            WidthBits = 32,
            CurrentValue = preload
        };

        var mcu = new StubMcu(new[] { nameless }, hisrLive);
        var mcuId = Guid.NewGuid();

        var (ptr, size, map, layout) = await NativeTestHost.AllocateAndFillAsync(
            mcu, mcuId, "ADC0", CancellationToken.None, "ADC", sdkRoot);
        try
        {
            layout.UsedSequentialFallback.Should().BeFalse();
            layout.ImageBase.Should().Be(adc0Base);
            map.Should().ContainKey(0x180);
            map[0x180].Should().Be("HISR");
            size.Should().BeGreaterThan(0x180 + 4);
            unchecked((uint)Marshal.ReadInt32(ptr, 0x180)).Should().Be(preload);
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
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

    private sealed class StubMcu : IVirtualMcuService
    {
        private readonly IReadOnlyList<VirtualRegisterView> _list;
        private readonly VirtualRegisterView _hisr;

        public StubMcu(IReadOnlyList<VirtualRegisterView> list, VirtualRegisterView hisr)
        {
            _list = list;
            _hisr = hisr;
        }

        public Task<IReadOnlyList<VirtualRegisterView>> GetRegistersAsync(
            Guid mcuId, string? moduleName = null, string? instanceName = null,
            CancellationToken cancellationToken = default)
            => Task.FromResult(_list);

        public Task<VirtualRegisterView?> GetRegisterAsync(
            Guid mcuId, string instanceOrStruct, string memberName,
            CancellationToken cancellationToken = default)
        {
            if (memberName.Equals("HISR", StringComparison.OrdinalIgnoreCase))
                return Task.FromResult<VirtualRegisterView?>(_hisr);
            return Task.FromResult<VirtualRegisterView?>(null);
        }

        public Task<VirtualMcuInfo> CreateAsync(VirtualMcuCreateOptions options, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task InitializeAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task InitializeForChipAsync(Guid chipId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task ResetAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task DestroyAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<IReadOnlyList<VirtualMcuInfo>> ListAsync(CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualMcuInfo?> GetInfoAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualMcuSnapshotInfo> TakeSnapshotAsync(Guid mcuId, string? label = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task RestoreSnapshotAsync(Guid mcuId, Guid snapshotId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<IReadOnlyList<VirtualMcuSnapshotInfo>> ListSnapshotsAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<IReadOnlyList<VirtualPeripheralTreeNode>> GetPeripheralTreeAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<IReadOnlyList<VirtualPeripheralView>> GetPeripheralStatesAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> ReadAsync(Guid mcuId, string instanceOrStruct, string memberName, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> ReadByAddressAsync(Guid mcuId, uint address, int widthBits = 32, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> WriteAsync(Guid mcuId, string instanceOrStruct, string memberName, uint value, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> WriteByAddressAsync(Guid mcuId, uint address, uint value, int widthBits = 32, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> SeedRegisterAsync(Guid mcuId, string instanceOrStruct, string memberName, uint value, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> WriteBitFieldAsync(Guid mcuId, string instanceOrStruct, string memberName, string fieldName, uint fieldValue, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> ClearBitsAsync(Guid mcuId, string instanceOrStruct, string memberName, uint mask, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> SetBitsAsync(Guid mcuId, string instanceOrStruct, string memberName, uint mask, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> ModifyBitsAsync(Guid mcuId, string instanceOrStruct, string memberName, uint clearMask, uint setMask, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<VirtualAccessResultDto> ResetRegisterAsync(Guid mcuId, string instanceOrStruct, string memberName, VirtualAccessContext? context = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task<IReadOnlyList<VirtualAccessRecord>> GetAccessTraceAsync(Guid mcuId, VirtualAccessFilter? filter = null, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public Task ClearAccessTraceAsync(Guid mcuId, CancellationToken cancellationToken = default)
            => throw new NotSupportedException();
        public void DiscardAllInMemoryInstances() { }
    }
}
