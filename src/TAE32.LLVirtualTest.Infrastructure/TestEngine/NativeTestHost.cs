using System.Runtime.InteropServices;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Loads compiled harness DLL and executes against a host RAM peripheral image,
/// then syncs memory back into an isolated virtual MCU instance.
/// </summary>
internal sealed class NativeTestHost : IDisposable
{
    private IntPtr _module;

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate int Tae32RunDelegate(ref PeriImg peri, IntPtr args, out uint outRet);

    [StructLayout(LayoutKind.Sequential)]
    private struct PeriImg
    {
        public IntPtr Base;
        public uint Size;
    }

    public void Load(string dllPath)
    {
        Dispose();
        _module = NativeLibrary.Load(dllPath);
    }

    public uint Execute(
        IntPtr periBase,
        uint periSize,
        byte[] argsBlob,
        out int nativeRc)
    {
        if (_module == IntPtr.Zero)
            throw new InvalidOperationException("Harness DLL 未加载");

        if (!NativeLibrary.TryGetExport(_module, "tae32_run", out var fn))
            throw new InvalidOperationException("DLL 缺少导出 tae32_run");

        var del = Marshal.GetDelegateForFunctionPointer<Tae32RunDelegate>(fn);
        var peri = new PeriImg { Base = periBase, Size = periSize };
        var argsPtr = Marshal.AllocHGlobal(Math.Max(argsBlob.Length, 8));
        try
        {
            Marshal.Copy(argsBlob, 0, argsPtr, argsBlob.Length);
            nativeRc = del(ref peri, argsPtr, out var ret);
            return ret;
        }
        finally
        {
            Marshal.FreeHGlobal(argsPtr);
        }
    }

    public static async Task<(IntPtr ptr, int size, Dictionary<int, string> offsetToMember)> AllocateAndFillAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        CancellationToken ct)
    {
        var regs = await mcu.GetRegistersAsync(mcuId, instanceName: instanceName, cancellationToken: ct);
        var withOff = regs
            .Where(r => r.AbsoluteAddress is not null)
            .Select(r => new
            {
                r.MemberName,
                Offset = (int)(r.AbsoluteAddress!.Value
                               - regs.Where(x => x.AbsoluteAddress is not null)
                                   .Min(x => x.AbsoluteAddress!.Value)),
                r.CurrentValue,
                r.WidthBits
            })
            .ToList();

        // If absolute addresses missing, pack by enumeration order (4-byte stride) — marked unsafe for HW fidelity.
        if (withOff.Count == 0)
        {
            var list = regs.ToList();
            var size = Math.Max(4096, list.Count * 4 + 64);
            var ptr = Marshal.AllocHGlobal(size);
            unsafe
            {
                new Span<byte>((void*)ptr, size).Clear();
            }
            var map = new Dictionary<int, string>();
            for (var i = 0; i < list.Count; i++)
            {
                var off = i * 4;
                map[off] = list[i].MemberName;
                Marshal.WriteInt32(ptr, off, unchecked((int)list[i].CurrentValue));
            }
            return (ptr, size, map);
        }

        var maxOff = withOff.Max(x => x.Offset + Math.Max(4, x.WidthBits / 8));
        var bufSize = Math.Max(4096, maxOff + 64);
        var basePtr = Marshal.AllocHGlobal(bufSize);
        unsafe
        {
            new Span<byte>((void*)basePtr, bufSize).Clear();
        }
        var offsetMap = new Dictionary<int, string>();
        foreach (var r in withOff)
        {
            offsetMap[r.Offset] = r.MemberName;
            Marshal.WriteInt32(basePtr, r.Offset, unchecked((int)r.CurrentValue));
        }
        return (basePtr, bufSize, offsetMap);
    }

    public static async Task SyncBufferToVirtualMcuAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        IntPtr periBase,
        Dictionary<int, string> offsetToMember,
        VirtualAccessContext ctx,
        CancellationToken ct)
    {
        foreach (var (offset, member) in offsetToMember)
        {
            var value = unchecked((uint)Marshal.ReadInt32(periBase, offset));
            await mcu.WriteAsync(mcuId, instanceName, member, value, ctx, ct);
        }
    }

    public static byte[] PackArgs(IReadOnlyDictionary<string, uint> named)
    {
        // Layout matches tae32_args: sequence of uint32 fields + pad.
        // Caller must use same order as harness generator (non-TypeDef params).
        using var ms = new MemoryStream();
        using var bw = new BinaryWriter(ms);
        foreach (var kv in named)
            bw.Write(kv.Value);
        bw.Write(0u); // _pad
        return ms.ToArray();
    }

    public void Dispose()
    {
        if (_module != IntPtr.Zero)
        {
            NativeLibrary.Free(_module);
            _module = IntPtr.Zero;
        }
    }
}
