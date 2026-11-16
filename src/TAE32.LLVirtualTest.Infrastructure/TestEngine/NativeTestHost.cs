using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text.Json;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

/// <summary>
/// Loads compiled harness DLL and executes against a host RAM peripheral image,
/// then syncs memory back into an isolated virtual MCU instance.
/// Native execution runs in a child process so AccessViolation cannot kill the UI.
/// </summary>
internal sealed class NativeTestHost : IDisposable
{
    private string? _dllPath;

    public void Load(string dllPath)
    {
        if (!File.Exists(dllPath))
            throw new FileNotFoundException("Harness DLL 不存在", dllPath);
        _dllPath = dllPath;
    }

    /// <summary>
    /// Execute harness in an isolated child process. On native crash the child dies;
    /// this method returns an error instead of crashing the WPF host.
    /// </summary>
    public uint Execute(
        IntPtr periBase,
        uint periSize,
        byte[] argsBlob,
        out int nativeRc)
    {
        if (string.IsNullOrWhiteSpace(_dllPath))
            throw new InvalidOperationException("Harness DLL 未加载");
        if (periBase == IntPtr.Zero || periSize == 0)
            throw new InvalidOperationException("外设映像无效");

        var work = Path.Combine(Path.GetTempPath(), "tae32_ll_native_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(work);
        var periIn = Path.Combine(work, "peri_in.bin");
        var periOut = Path.Combine(work, "peri_out.bin");
        var argsPath = Path.Combine(work, "args.bin");
        var resultPath = Path.Combine(work, "result.json");

        try
        {
            var periBytes = new byte[periSize];
            Marshal.Copy(periBase, periBytes, 0, (int)periSize);
            File.WriteAllBytes(periIn, periBytes);
            File.WriteAllBytes(argsPath, argsBlob.Length == 0 ? new byte[8] : argsBlob);

            var (runner, prefixArgs) = ResolveRunner();
            var psi = new ProcessStartInfo
            {
                FileName = runner,
                UseShellExecute = false,
                CreateNoWindow = true,
                RedirectStandardError = true,
                RedirectStandardOutput = true
            };
            foreach (var a in prefixArgs) psi.ArgumentList.Add(a);
            psi.ArgumentList.Add(_dllPath!);
            psi.ArgumentList.Add(periIn);
            psi.ArgumentList.Add(periOut);
            psi.ArgumentList.Add(argsPath);
            psi.ArgumentList.Add(resultPath);

            using var proc = new Process { StartInfo = psi };

            if (!proc.Start())
                throw new InvalidOperationException("无法启动 NativeRunner 子进程");

            // Hard cap: native AVE / hang must not block UI forever.
            if (!proc.WaitForExit(60_000))
            {
                try { proc.Kill(entireProcessTree: true); } catch { /* ignore */ }
                throw new TimeoutException("原生执行子进程超时（可能死循环/挂死）");
            }

            var stderr = proc.StandardError.ReadToEnd();
            if (!File.Exists(resultPath))
            {
                nativeRc = -1000;
                throw new InvalidOperationException(
                    "原生执行子进程异常退出（常见于 AccessViolation）。" +
                    $" exit={proc.ExitCode}. {Truncate(stderr, 400)}");
            }

            using var doc = JsonDocument.Parse(File.ReadAllText(resultPath));
            var root = doc.RootElement;
            nativeRc = root.TryGetProperty("rc", out var rcEl) ? rcEl.GetInt32() : -1;
            var ret = root.TryGetProperty("ret", out var retEl) ? retEl.GetUInt32() : 0u;
            var error = root.TryGetProperty("error", out var errEl) ? errEl.GetString() : null;

            if (proc.ExitCode != 0 && nativeRc == -999)
                throw new InvalidOperationException("原生执行失败：" + (error ?? stderr));

            if (proc.ExitCode is not (0 or 3) && !File.Exists(periOut))
            {
                throw new InvalidOperationException(
                    "原生执行子进程崩溃（疑似 AccessViolation / 非法指针）。" +
                    $" exit={proc.ExitCode}. 该用例已隔离，未导致主程序闪退。{Truncate(stderr, 300)}");
            }

            if (File.Exists(periOut))
            {
                var outBytes = File.ReadAllBytes(periOut);
                var copyLen = Math.Min(outBytes.Length, (int)periSize);
                if (copyLen > 0)
                    Marshal.Copy(outBytes, 0, periBase, copyLen);
            }

            if (nativeRc != 0 && nativeRc != -999)
            {
                // Caller treats non-zero harness rc as soft failure.
            }

            return ret;
        }
        finally
        {
            try { Directory.Delete(work, recursive: true); } catch { /* ignore */ }
        }
    }

    public static async Task<(IntPtr ptr, int size, Dictionary<int, string> offsetToMember)> AllocateAndFillAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        CancellationToken ct,
        string? moduleName = null)
    {
        var regs = await mcu.GetRegistersAsync(mcuId, moduleName, instanceName, ct);
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

        // Larger pad: some LL paths touch adjacent/reserved offsets; AVE was taking down the UI process.
        const int minSize = 512 * 1024;
        var structMin = HostPeripheralImageSizes.MinBytes(instanceName, moduleName);

        if (withOff.Count == 0)
        {
            var list = regs.ToList();
            var size = Math.Max(Math.Max(minSize, structMin), list.Count * 4 + 256);
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
        var bufSize = Math.Max(Math.Max(minSize, structMin), maxOff + 1024);
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

    /// <summary>
    /// BSR/BSRR writes on host RAM do not update data-out; mirror into DOR before sync.
    /// TAE32: DOR = data output, ODR = open-drain config — never treat ODR as DOR when both exist.
    /// </summary>
    public static void ApplyHostGpioBsrToDor(IntPtr periBase, IReadOnlyDictionary<int, string> offsetToMember)
    {
        var bsrOff = -1;
        var dorOff = -1;
        var odrOff = -1;
        foreach (var (offset, member) in offsetToMember)
        {
            var m = member.ToUpperInvariant();
            if (m is "BSR" or "BSRR") bsrOff = offset;
            else if (m == "DOR") dorOff = offset;
            else if (m == "ODR") odrOff = offset;
        }

        // Prefer DOR; only fall back to ODR for STM32-style layouts without DOR.
        var dataOutOff = dorOff >= 0 ? dorOff : odrOff;
        if (dataOutOff < 0 || bsrOff < 0) return;

        var bsr = unchecked((uint)Marshal.ReadInt32(periBase, bsrOff));
        var dataOut = unchecked((uint)Marshal.ReadInt32(periBase, dataOutOff));
        var merged = GpioBsrDorLogic.MergeBsrIntoDor(bsr, dataOut);
        if (merged != dataOut)
            Marshal.WriteInt32(periBase, dataOutOff, unchecked((int)merged));
    }

    /// <summary>Capture peripheral image words before native execute (for delta sync).</summary>
    public static Dictionary<int, uint> SnapshotBuffer(
        IntPtr periBase,
        IReadOnlyDictionary<int, string> offsetToMember)
    {
        var map = new Dictionary<int, uint>(offsetToMember.Count);
        foreach (var offset in offsetToMember.Keys)
            map[offset] = unchecked((uint)Marshal.ReadInt32(periBase, offset));
        return map;
    }

    /// <summary>
    /// Sync harness RAM → virtual MCU. Only members whose buffer word changed since
    /// <paramref name="beforeExecute"/> are written and attributed to the LL function.
    /// Unchanged slots are skipped so native-harness-sync is not recorded as LL access.
    /// </summary>
    public static async Task SyncBufferToVirtualMcuAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        IntPtr periBase,
        Dictionary<int, string> offsetToMember,
        VirtualAccessContext ctx,
        CancellationToken ct,
        IReadOnlyDictionary<int, uint>? beforeExecute = null)
    {
        foreach (var (offset, member) in offsetToMember)
        {
            var value = unchecked((uint)Marshal.ReadInt32(periBase, offset));
            if (beforeExecute is not null
                && beforeExecute.TryGetValue(offset, out var before)
                && before == value)
            {
                continue;
            }

            await mcu.WriteAsync(mcuId, instanceName, member, value, ctx, ct);
        }
    }

    public static byte[] PackArgs(IReadOnlyList<uint> values)
    {
        using var ms = new MemoryStream();
        using var bw = new BinaryWriter(ms);
        foreach (var v in values)
            bw.Write(v);
        bw.Write(0u);
        return ms.ToArray();
    }

    public void Dispose()
    {
        _dllPath = null;
    }

    private static (string FileName, string[] PrefixArgs) ResolveRunner()
    {
        var probes = new[]
        {
            AppContext.BaseDirectory,
            Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", "TAE32.LLVirtualTest.NativeRunner", "bin", "Debug", "net8.0")),
            Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", "TAE32.LLVirtualTest.NativeRunner", "bin", "Release", "net8.0")),
        };

        foreach (var dir in probes)
        {
            var exe = Path.Combine(dir, "TAE32.LLVirtualTest.NativeRunner.exe");
            if (File.Exists(exe))
                return (exe, Array.Empty<string>());
        }

        foreach (var dir in probes)
        {
            var dll = Path.Combine(dir, "TAE32.LLVirtualTest.NativeRunner.dll");
            if (File.Exists(dll))
                return ("dotnet", new[] { dll });
        }

        throw new FileNotFoundException(
            "未找到 TAE32.LLVirtualTest.NativeRunner.exe。请重新生成解决方案（App 会复制 NativeRunner 到输出目录）。");
    }

    private static string Truncate(string? s, int max)
        => string.IsNullOrEmpty(s) ? "" : s.Length <= max ? s : s[..max] + "…";
}
