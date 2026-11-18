using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text.Json;
using System.Text.RegularExpressions;
using TAE32.LLVirtualTest.Core.Enums;
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
    /// Uses async wait so the WPF UI thread is not frozen by <c>WaitForExit</c>.
    /// </summary>
    public async Task<(uint ReturnValue, int NativeRc)> ExecuteAsync(
        IntPtr periBase,
        uint periSize,
        byte[] argsBlob,
        CancellationToken cancellationToken = default)
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
            await File.WriteAllBytesAsync(periIn, periBytes, cancellationToken).ConfigureAwait(false);
            await File.WriteAllBytesAsync(
                    argsPath, argsBlob.Length == 0 ? new byte[8] : argsBlob, cancellationToken)
                .ConfigureAwait(false);

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

            // Drain stdout/stderr concurrently so a full pipe cannot deadlock WaitForExitAsync.
            var stdoutTask = proc.StandardOutput.ReadToEndAsync(cancellationToken);
            var stderrTask = proc.StandardError.ReadToEndAsync(cancellationToken);

            // Hard safety cap 60s, plus caller timeout/cancel via linked token.
            using var hardCap = CancellationTokenSource.CreateLinkedTokenSource(cancellationToken);
            hardCap.CancelAfter(TimeSpan.FromSeconds(60));
            try
            {
                await proc.WaitForExitAsync(hardCap.Token).ConfigureAwait(false);
            }
            catch (OperationCanceledException)
            {
                try { proc.Kill(entireProcessTree: true); } catch { /* ignore */ }
                try { await proc.WaitForExitAsync(CancellationToken.None).ConfigureAwait(false); }
                catch { /* ignore */ }
                if (cancellationToken.IsCancellationRequested)
                    throw;
                throw new TimeoutException("原生执行子进程超时（可能死循环/挂死）");
            }

            var stderr = await stderrTask.ConfigureAwait(false);
            _ = await stdoutTask.ConfigureAwait(false);

            if (!File.Exists(resultPath))
            {
                throw new InvalidOperationException(
                    "原生执行子进程异常退出（常见于 AccessViolation）。" +
                    $" exit={proc.ExitCode}. {Truncate(stderr, 400)}");
            }

            await using var resultStream = File.OpenRead(resultPath);
            using var doc = await JsonDocument.ParseAsync(resultStream, cancellationToken: CancellationToken.None)
                .ConfigureAwait(false);
            var root = doc.RootElement;
            var nativeRc = root.TryGetProperty("rc", out var rcEl) ? rcEl.GetInt32() : -1;
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
                var outBytes = await File.ReadAllBytesAsync(periOut, CancellationToken.None)
                    .ConfigureAwait(false);
                var copyLen = Math.Min(outBytes.Length, (int)periSize);
                if (copyLen > 0)
                    Marshal.Copy(outBytes, 0, periBase, copyLen);
            }

            return (ret, nativeRc);
        }
        finally
        {
            try { Directory.Delete(work, recursive: true); } catch { /* ignore */ }
        }
    }

    /// <summary>Host peri image layout used for Native Execute ↔ virtual MCU sync.</summary>
    public sealed class HostImageLayout
    {
        public uint ImageBase { get; init; }
        public int SizeBytes { get; init; }
        public bool MultiBank { get; init; }
        public bool UsedSequentialFallback { get; init; }
        public string? ModuleName { get; init; }
        public string? InstanceName { get; init; }
        public IReadOnlyList<string> OffsetCollisions { get; init; } = Array.Empty<string>();
        public IReadOnlyList<string> Warnings { get; init; } = Array.Empty<string>();

        public string FormatDebug(string? focusInstance = null, string? focusMember = null)
        {
            var sb = new System.Text.StringBuilder();
            sb.AppendLine($"Peripheral: {ModuleName ?? InstanceName ?? "—"}");
            sb.AppendLine($"HostImageBase: 0x{ImageBase:X8}");
            sb.AppendLine($"HostImageSize: 0x{SizeBytes:X} ({SizeBytes})");
            sb.AppendLine($"MultiBank: {MultiBank}");
            sb.AppendLine($"SequentialFallback: {UsedSequentialFallback}");
            if (!string.IsNullOrWhiteSpace(focusInstance) && !string.IsNullOrWhiteSpace(focusMember))
            {
                sb.AppendLine($"Focus: {focusInstance}.{focusMember}");
            }

            foreach (var w in Warnings.Take(12))
                sb.AppendLine("Warn: " + w);
            foreach (var c in OffsetCollisions.Take(8))
                sb.AppendLine("Collision: " + c);
            return sb.ToString().TrimEnd();
        }
    }

    /// <summary>
    /// Map value: <c>Member</c> or <c>Instance::Member</c> (multi-bank TypeDef images e.g. HRPWM).
    /// Image base is the aggregate TypeDef base (HRPWM→MST bank), not an arbitrary min that can
    /// desync nested <c>Master.MCR0</c> / <c>PWM[i]</c> offsetof from AbsoluteAddress packing.
    /// </summary>
    public static async Task<(IntPtr ptr, int size, Dictionary<int, string> offsetToMember, HostImageLayout layout)> AllocateAndFillAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        CancellationToken ct,
        string? moduleName = null,
        string? sdkRootPath = null)
    {
        var multiBank = IsMultiBankModule(moduleName, instanceName);
        var moduleKey = moduleName ?? (multiBank ? "HRPWM" : null);
        var warnings = new List<string>();
        var collisions = new List<string>();

        // Collect candidates: preferred filter first, then always enrich AbsoluteAddress.
        // Flat ADC/UART: GetRegister(ADC0,HISR) may have AbsoluteAddress while GetAll filters
        // return nameless-address copies — never SequentialFallback when chip.h / GetRegister can recover.
        var regs = await CollectHostImageRegistersAsync(
            mcu, mcuId, instanceName, moduleKey, multiBank, ct);

        // Larger pad: some LL paths touch adjacent/reserved offsets; AVE was taking down the UI process.
        const int minSize = 512 * 1024;
        var structMin = HostPeripheralImageSizes.MinBytes(instanceName, moduleName);

        // Always enrich (partial AbsoluteAddress lists used to skip Recover → HISR @+0x180 MISSING).
        var addressed = await RecoverAbsoluteAddressesAsync(
            mcu, mcuId, regs, instanceName, moduleKey, sdkRootPath, warnings, ct);

        if (addressed.Count == 0)
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
                map[off] = multiBank
                    ? $"{list[i].InstanceName}::{list[i].MemberName}"
                    : list[i].MemberName;
                Marshal.WriteInt32(ptr, off, unchecked((int)list[i].CurrentValue));
            }

            warnings.Add(
                "寄存器缺少 AbsoluteAddress，回退顺序打包；嵌套 TypeDef（如 HRPWM Master.MCR0）" +
                "与宿主 offsetof 可能不一致，写入可能无法同步回虚拟 MCU。");
            var layoutFb = new HostImageLayout
            {
                ImageBase = 0,
                SizeBytes = size,
                MultiBank = multiBank,
                UsedSequentialFallback = true,
                ModuleName = moduleName,
                InstanceName = instanceName,
                Warnings = warnings
            };
            return (ptr, size, map, layoutFb);
        }

        var imageBase = ResolveAggregateImageBase(moduleName, instanceName, addressed, structMin);
        // ADC HISR is at +0x180; keep at least structMin (ADC=0x400) so high offsets stay mapped.
        var imageWindow = Math.Max(structMin > 0 ? structMin : 0x1000, 0x1000);
        var inWindow = addressed
            .Where(r =>
            {
                var abs = r.AbsoluteAddress!.Value;
                return abs >= imageBase && abs < imageBase + (uint)imageWindow;
            })
            .ToList();

        if (inWindow.Count == 0)
        {
            // Fall back to all addressed regs relative to computed base (may be large).
            inWindow = addressed;
            warnings.Add(
                $"没有寄存器落在 TypeDef 窗口 [0x{imageBase:X8}, 0x{imageBase + (uint)imageWindow:X8})；" +
                "使用全部带地址寄存器，偏移可能与 HRPWM_TypeDef 不一致。");
        }
        else if (inWindow.Count < addressed.Count)
        {
            warnings.Add(
                $"已排除 {addressed.Count - inWindow.Count} 个窗口外寄存器（基址 0x{imageBase:X8}，窗口 0x{imageWindow:X}）。");
        }

        var withOff = inWindow
            .Select(r => new
            {
                Key = multiBank ? $"{r.InstanceName}::{r.MemberName}" : r.MemberName!,
                Offset = (int)(r.AbsoluteAddress!.Value - imageBase),
                r.CurrentValue,
                r.WidthBits,
                Abs = r.AbsoluteAddress!.Value
            })
            .Where(x => x.Offset >= 0)
            .ToList();

        var maxOff = withOff.Count == 0
            ? structMin
            : withOff.Max(x => x.Offset + Math.Max(4, x.WidthBits / 8));
        var bufSize = Math.Max(Math.Max(minSize, structMin), maxOff + 1024);
        var basePtr = Marshal.AllocHGlobal(bufSize);
        unsafe
        {
            new Span<byte>((void*)basePtr, bufSize).Clear();
        }

        var offsetMap = new Dictionary<int, string>();
        foreach (var r in withOff.OrderBy(x => x.Offset))
        {
            if (offsetMap.TryGetValue(r.Offset, out var existing) &&
                !string.Equals(existing, r.Key, StringComparison.OrdinalIgnoreCase))
            {
                collisions.Add($"offset 0x{r.Offset:X}: {existing} vs {r.Key} (abs 0x{r.Abs:X8})");
            }

            offsetMap[r.Offset] = r.Key;
            Marshal.WriteInt32(basePtr, r.Offset, unchecked((int)r.CurrentValue));
        }

        if (multiBank && IsHostAggregateModule(moduleName))
        {
            // HRPWM_TypeDef.Master.MCR0 is at offsetof 0; missing map entry ⇒ native writes are lost.
            if (!offsetMap.ContainsKey(0))
            {
                warnings.Add(
                    "多 bank 映像缺少 offset 0 映射（HRPWM Master.MCR0 / TypeDef 首寄存器）。" +
                    "Native 对 Master.MCR0 的写入将无法同步到虚拟 MCU。");
            }
            else if (!offsetMap[0].Contains("MCR0", StringComparison.OrdinalIgnoreCase)
                     && string.Equals(moduleName, "HRPWM", StringComparison.OrdinalIgnoreCase))
            {
                warnings.Add($"offset 0 当前映射为 {offsetMap[0]}，期望 HRPWM_MST::MCR0。");
            }
        }

        var layout = new HostImageLayout
        {
            ImageBase = imageBase,
            SizeBytes = bufSize,
            MultiBank = multiBank,
            UsedSequentialFallback = false,
            ModuleName = moduleName,
            InstanceName = instanceName,
            OffsetCollisions = collisions,
            Warnings = warnings
        };
        return (basePtr, bufSize, offsetMap, layout);
    }

    private static async Task<IReadOnlyList<VirtualRegisterView>> CollectHostImageRegistersAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        string instanceName,
        string? moduleKey,
        bool multiBank,
        CancellationToken ct)
    {
        IReadOnlyList<VirtualRegisterView> regs = multiBank
            ? await mcu.GetRegistersAsync(mcuId, moduleKey, null, ct)
            : await mcu.GetRegistersAsync(mcuId, moduleKey, instanceName, ct);

        if (regs.Count > 0 && regs.Any(r => r.AbsoluteAddress is not null))
            return regs;

        if (!string.IsNullOrWhiteSpace(instanceName))
        {
            var byInst = await mcu.GetRegistersAsync(mcuId, null, instanceName, ct);
            if (byInst.Count > 0)
                regs = byInst;
            if (regs.Any(r => r.AbsoluteAddress is not null))
                return regs;
        }

        // Universe dump — last resort when module/instance filters disagree with slot metadata.
        var all = await mcu.GetRegistersAsync(mcuId, null, null, ct);
        var scoped = all.Where(r => MatchesHostImageScope(r, instanceName, moduleKey, multiBank)).ToList();
        return scoped.Count > 0 ? scoped : regs;
    }

    private static bool MatchesHostImageScope(
        VirtualRegisterView r, string? instanceName, string? moduleKey, bool multiBank)
    {
        if (!string.IsNullOrWhiteSpace(moduleKey))
        {
            var modOk =
                string.Equals(
                    VirtualMcu.VirtualMcuDefinitionLoader.NormalizeModuleToken(r.ModuleName),
                    moduleKey, StringComparison.OrdinalIgnoreCase)
                || string.Equals(
                    VirtualMcu.VirtualMcuDefinitionLoader.NormalizeModuleToken(r.InstanceName),
                    moduleKey, StringComparison.OrdinalIgnoreCase)
                || (r.InstanceName?.StartsWith(moduleKey, StringComparison.OrdinalIgnoreCase) ?? false)
                || (r.StructName?.StartsWith(moduleKey, StringComparison.OrdinalIgnoreCase) ?? false);
            if (!modOk) return false;
        }

        if (multiBank || string.IsNullOrWhiteSpace(instanceName))
            return true;

        return string.Equals(r.InstanceName, instanceName, StringComparison.OrdinalIgnoreCase)
               || string.Equals(r.StructName, instanceName + "_Type", StringComparison.OrdinalIgnoreCase)
               || string.Equals(r.StructName, instanceName + "_TypeDef", StringComparison.OrdinalIgnoreCase)
               || string.IsNullOrWhiteSpace(r.InstanceName);
    }

    private static async Task<List<VirtualRegisterView>> RecoverAbsoluteAddressesAsync(
        IVirtualMcuService mcu,
        Guid mcuId,
        IReadOnlyList<VirtualRegisterView> regs,
        string instanceName,
        string? moduleKey,
        string? sdkRootPath,
        List<string> warnings,
        CancellationToken ct)
    {
        var recovered = new List<VirtualRegisterView>();
        var seenMembers = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
        var catalog = VirtualMcu.ChipHeaderAddressCatalog.TryLoad(sdkRootPath);
        var enriched = 0;

        async Task TryAddAsync(VirtualRegisterView r, string? instOverride = null)
        {
            var inst = !string.IsNullOrWhiteSpace(instOverride)
                ? instOverride!
                : (!string.IsNullOrWhiteSpace(r.InstanceName) ? r.InstanceName! : instanceName);
            if (string.IsNullOrWhiteSpace(inst) || string.IsNullOrWhiteSpace(r.MemberName))
                return;
            var key = $"{inst}.{r.MemberName}";
            if (seenMembers.Contains(key))
                return;

            if (r.AbsoluteAddress is not null)
            {
                seenMembers.Add(key);
                recovered.Add(r);
                return;
            }

            var one = await mcu.GetRegisterAsync(mcuId, inst, r.MemberName, ct);
            if (one?.AbsoluteAddress is not null)
            {
                seenMembers.Add(key);
                recovered.Add(one);
                enriched++;
                return;
            }

            if (catalog is not null
                && catalog.TryResolveAbsolute(inst, r.StructName, r.MemberName,
                    out var abs, out _, out _))
            {
                seenMembers.Add(key);
                recovered.Add(CloneWithAbsoluteAddress(one ?? r, abs));
                enriched++;
            }
            // Leave unseen on failure so chip.h last-resort can still attach AbsoluteAddress.
        }

        // Fast path: collected regs already carry AbsoluteAddress (normal after MCU init from chip.h).
        if (regs.Count > 0 && regs.All(r => r.AbsoluteAddress is not null))
        {
            return regs
                .Where(r => r.AbsoluteAddress is not null)
                .GroupBy(r => r.AbsoluteAddress!.Value)
                .Select(g => g.First())
                .ToList();
        }

        foreach (var r in regs)
        {
            ct.ThrowIfCancellationRequested();
            await TryAddAsync(r);
        }

        // Broaden: same instance from MCU (filters may have dropped HISR / AbsoluteAddress copies).
        if (!string.IsNullOrWhiteSpace(instanceName))
        {
            var byInst = await mcu.GetRegistersAsync(mcuId, null, instanceName, ct);
            foreach (var r in byInst)
            {
                ct.ThrowIfCancellationRequested();
                await TryAddAsync(r, instanceName);
            }

            // Universe dump only when instance filter still yielded no absolute addresses.
            if (recovered.Count == 0 || recovered.All(r => r.AbsoluteAddress is null))
            {
                var universe = await mcu.GetRegistersAsync(mcuId, null, null, ct);
                foreach (var r in universe.Where(x => MatchesHostImageScope(x, instanceName, moduleKey, false)))
                {
                    ct.ThrowIfCancellationRequested();
                    await TryAddAsync(r, instanceName);
                }
            }
        }

        var withAbs = recovered
            .Where(r => r.AbsoluteAddress is not null)
            .GroupBy(r => r.AbsoluteAddress!.Value)
            .Select(g => g.First())
            .ToList();

        // Last resort only when still empty — full EnumerateMembers was O(all ADC regs) per case.
        if (withAbs.Count == 0
            && catalog is not null
            && !string.IsNullOrWhiteSpace(instanceName))
        {
            foreach (var member in catalog.EnumerateMembers(instanceName))
            {
                ct.ThrowIfCancellationRequested();
                var key = $"{instanceName}.{member}";
                if (seenMembers.Contains(key))
                    continue;
                if (!catalog.TryResolveAbsolute(instanceName, null, member, out var abs, out _, out _))
                    continue;
                var live = await mcu.GetRegisterAsync(mcuId, instanceName, member, ct);
                seenMembers.Add(key);
                if (live is not null)
                {
                    recovered.Add(live.AbsoluteAddress is not null
                        ? live
                        : CloneWithAbsoluteAddress(live, abs));
                    enriched++;
                }
                else
                {
                    recovered.Add(new VirtualRegisterView
                    {
                        InstanceName = instanceName,
                        MemberName = member,
                        AbsoluteAddress = abs,
                        WidthBits = 32,
                        CurrentValue = 0
                    });
                    enriched++;
                }
            }

            withAbs = recovered
                .Where(r => r.AbsoluteAddress is not null)
                .GroupBy(r => r.AbsoluteAddress!.Value)
                .Select(g => g.First())
                .ToList();
        }

        if (enriched > 0)
            warnings.Add("已通过 GetRegister/chip.h 补齐 AbsoluteAddress（避免 SequentialFallback）。");

        return withAbs;
    }

    private static VirtualRegisterView CloneWithAbsoluteAddress(VirtualRegisterView src, uint abs)
        => new()
        {
            DefinitionId = src.DefinitionId,
            ChipModelName = src.ChipModelName,
            ModuleName = src.ModuleName,
            InstanceName = src.InstanceName,
            StructName = src.StructName,
            MemberName = src.MemberName,
            AbsoluteAddress = abs,
            WidthBits = src.WidthBits,
            CurrentValue = src.CurrentValue,
            ResetValue = src.ResetValue,
            AccessAttribute = src.AccessAttribute,
            Behavior = src.Behavior,
            WritableMask = src.WritableMask,
            Limitation = src.Limitation,
            LimitationNote = src.LimitationNote,
            Fields = src.Fields
        };

    /// <summary>
    /// Aggregate TypeDef base: prefer known bank bases (HRPWM_MST), else min AbsoluteAddress
    /// among coherent banks (exclude outliers that would shift nested offsetof).
    /// </summary>
    internal static uint ResolveAggregateImageBase(
        string? moduleName,
        string? instanceName,
        IReadOnlyList<VirtualRegisterView> addressed,
        int structMin = 0)
    {
        if (addressed.Count == 0) return 0;

        if (string.Equals(moduleName, "HRPWM", StringComparison.OrdinalIgnoreCase)
            || (instanceName?.StartsWith("HRPWM", StringComparison.OrdinalIgnoreCase) ?? false))
        {
            // SDK: HRPWM ((HRPWM_TypeDef*)HRPWM_MST_BASE); Master at 0, PWM[0] at 0x100.
            var mst = addressed
                .Where(r => r.InstanceName?.StartsWith("HRPWM_MST", StringComparison.OrdinalIgnoreCase) == true)
                .Select(r => r.AbsoluteAddress!.Value)
                .DefaultIfEmpty()
                .Min();
            if (mst != 0) return mst;

            // Fallback: round down to 0x100-aligned bank that looks like MST (…B000).
            var min = addressed.Min(r => r.AbsoluteAddress!.Value);
            return min & ~0xFFu;
        }

        // Generic: use min, but if spread > 64KB prefer dense cluster around mode/min.
        var sorted = addressed.Select(r => r.AbsoluteAddress!.Value).OrderBy(x => x).ToList();
        var minAll = sorted[0];
        var maxAll = sorted[^1];
        if (maxAll - minAll > 0x10000u)
        {
            var cluster = sorted.Where(a => a < minAll + 0x1000u).ToList();
            minAll = cluster.Count > 0 ? cluster[0] : minAll;
        }

        // Flat peri (ADC/UART…): if only high-offset members were recovered (e.g. HISR @+0x180),
        // align down to TypeDef size so ADCx pointer matches chip BASE (ADC0_BASE), not HISR abs.
        if (structMin >= 0x40)
        {
            var align = (uint)structMin;
            if ((align & (align - 1)) == 0)
                return minAll & ~(align - 1u);
        }

        return minAll;
    }

    private static bool IsHostAggregateModule(string? module)
        => string.Equals(module, "HRPWM", StringComparison.OrdinalIgnoreCase);

    /// <summary>
    /// Compare host buffer before/after native execute. Returns mapped deltas and unmapped dirties
    /// (native wrote where AbsoluteAddress packing had no slot — root cause of empty traces).
    /// </summary>
    public static HostBufferDeltaReport AnalyzeBufferDeltas(
        IntPtr periBase,
        int sizeBytes,
        IReadOnlyDictionary<int, string> offsetToMember,
        IReadOnlyDictionary<int, uint> beforeExecute,
        uint imageBase)
    {
        var mapped = new List<HostBufferMappedDelta>();
        var unmapped = new List<HostBufferUnmappedDelta>();
        var mappedOff = offsetToMember.Keys.ToHashSet();

        foreach (var (offset, key) in offsetToMember)
        {
            if (offset < 0 || offset + 4 > sizeBytes) continue;
            var after = unchecked((uint)Marshal.ReadInt32(periBase, offset));
            beforeExecute.TryGetValue(offset, out var before);
            if (before == after) continue;
            var (inst, member) = SplitSlotKey(key, "");
            mapped.Add(new HostBufferMappedDelta(offset, imageBase + (uint)offset, key, inst, member, before, after));
        }

        // Scan TypeDef-sized prefix for dirties not in the map (lost native writes).
        var scan = Math.Min(sizeBytes, Math.Max(0x1000, mappedOff.Count == 0 ? 0x100 : mappedOff.Max() + 0x100));
        for (var off = 0; off + 4 <= scan; off += 4)
        {
            if (mappedOff.Contains(off)) continue;
            var after = unchecked((uint)Marshal.ReadInt32(periBase, off));
            var before = beforeExecute.TryGetValue(off, out var b) ? b : 0u;
            // Unmapped slots were cleared at alloc; treat any non-zero or changed word as dirty.
            if (after == before && after == 0) continue;
            if (after == before) continue;
            unmapped.Add(new HostBufferUnmappedDelta(off, imageBase + (uint)off, before, after));
        }

        return new HostBufferDeltaReport(mapped, unmapped);
    }

    public readonly record struct HostBufferMappedDelta(
        int Offset, uint AbsoluteAddress, string Key, string Instance, string Member, uint Before, uint After);

    public readonly record struct HostBufferUnmappedDelta(
        int Offset, uint AbsoluteAddress, uint Before, uint After);

    public sealed record HostBufferDeltaReport(
        IReadOnlyList<HostBufferMappedDelta> MappedChanges,
        IReadOnlyList<HostBufferUnmappedDelta> UnmappedChanges)
    {
        public bool HasUnmappedWrites => UnmappedChanges.Count > 0;
        public bool HasMappedWrites => MappedChanges.Count > 0;

        public string FormatDebug()
        {
            var sb = new System.Text.StringBuilder();
            sb.AppendLine($"MappedDeltas: {MappedChanges.Count}");
            foreach (var d in MappedChanges.Take(16))
            {
                sb.AppendLine(
                    $"  [map] +0x{d.Offset:X} abs=0x{d.AbsoluteAddress:X8} {d.Key}: " +
                    $"0x{d.Before:X8} → 0x{d.After:X8}");
            }

            sb.AppendLine($"UnmappedDeltas: {UnmappedChanges.Count}");
            foreach (var d in UnmappedChanges.Take(16))
            {
                sb.AppendLine(
                    $"  [lost] +0x{d.Offset:X} abs=0x{d.AbsoluteAddress:X8}: " +
                    $"0x{d.Before:X8} → 0x{d.After:X8}（无虚拟寄存器槽，写入无法回读）");
            }

            return sb.ToString().TrimEnd();
        }
    }

    /// <summary>
    /// Multi-bank = one host TypeDef image covering several chip bases (e.g. HRPWM MST/SLVn/COM).
    /// Not ADC0/ADC1 (separate TypeDefs / separate host casts).
    /// </summary>
    private static bool IsMultiBankModule(string? moduleName, string? instanceName)
    {
        if (string.Equals(moduleName, "HRPWM", StringComparison.OrdinalIgnoreCase))
            return true;
        if (string.IsNullOrWhiteSpace(instanceName))
            return false;
        // Module_SUBBANK: HRPWM_SLV0, FOO_MST, BAR_COM, BAZ_CH3 (not FOO0/FOO1 numbered peripherals).
        return Regex.IsMatch(instanceName,
            @"^[A-Za-z]+_(MST|COM|SLV\d+|CH\d+|UNIT\d+|TIM\d+)$",
            RegexOptions.IgnoreCase);
    }

    internal static (string Instance, string Member) SplitSlotKey(string key, string fallbackInstance)
    {
        var idx = key.IndexOf("::", StringComparison.Ordinal);
        if (idx <= 0)
            return (fallbackInstance, key);
        return (key[..idx], key[(idx + 2)..]);
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
        foreach (var (offset, key) in offsetToMember)
        {
            var member = SplitSlotKey(key, "").Member.ToUpperInvariant();
            if (member is "BSR" or "BSRR") bsrOff = offset;
            else if (member == "DOR") dorOff = offset;
            else if (member == "ODR") odrOff = offset;
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
    /// Unchanged slots are skipped so native-harness-sync is not recorded as LL access —
    /// except W1C/W0C status registers: host is plain RAM so ClearFlag WRITE_REG(seed)
    /// leaves the word unchanged, yet virtual MCU still needs WriteAsync to apply clear.
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
        foreach (var (offset, key) in offsetToMember)
        {
            var value = unchecked((uint)Marshal.ReadInt32(periBase, offset));
            var (inst, member) = SplitSlotKey(key, instanceName);
            var unchanged = beforeExecute is not null
                            && beforeExecute.TryGetValue(offset, out var before)
                            && before == value;
            if (unchanged)
            {
                // W1C ClearFlag: seed==WRITE_REG leaves host RAM identical; still replay WriteAsync.
                // Never force this on read/IsActiveFlag — WriteAsync would clear the preloaded flags.
                if (value == 0 || !IsLikelyW1cClearWrite(ctx.LlFunctionName))
                    continue;
                var slot = await mcu.GetRegisterAsync(mcuId, inst, member, ct);
                if (slot is null)
                    continue;
                if (slot.Behavior is not (VirtualRegisterBehavior.Write1Clear
                        or VirtualRegisterBehavior.Write0Clear
                        or VirtualRegisterBehavior.Write1Set
                        or VirtualRegisterBehavior.Toggle))
                    continue;
            }

            await mcu.WriteAsync(mcuId, inst, member, value, ctx, ct);
        }
    }

    /// <summary>
    /// True when the LL call is expected to WRITE status flags (ClearFlag / Clear*Flag),
    /// so an unchanged host word may still need W1C WriteAsync replay.
    /// </summary>
    private static bool IsLikelyW1cClearWrite(string? llFunctionName)
    {
        if (string.IsNullOrWhiteSpace(llFunctionName))
            return false;
        var n = llFunctionName;
        if (n.Contains("IsActive", StringComparison.OrdinalIgnoreCase)
            || n.Contains("IsEnabled", StringComparison.OrdinalIgnoreCase)
            || n.Contains("Get", StringComparison.OrdinalIgnoreCase)
               && !n.Contains("Clear", StringComparison.OrdinalIgnoreCase))
            return false;
        return n.Contains("ClearFlag", StringComparison.OrdinalIgnoreCase)
               || n.Contains("ClearDataFlag", StringComparison.OrdinalIgnoreCase)
               || n.Contains("ClearAll", StringComparison.OrdinalIgnoreCase)
               || n.Contains("ClearInt", StringComparison.OrdinalIgnoreCase)
               || n.Contains("ClearPending", StringComparison.OrdinalIgnoreCase)
               // RCU ClearMCLRResetPending / Clear*ResetPending (Clear…Pending, not ClearPending).
               || (n.Contains("Clear", StringComparison.OrdinalIgnoreCase)
                   && n.Contains("Pending", StringComparison.OrdinalIgnoreCase))
               || (n.Contains("Clear", StringComparison.OrdinalIgnoreCase)
                   && (n.Contains("Flag", StringComparison.OrdinalIgnoreCase)
                       || n.Contains("Intr", StringComparison.OrdinalIgnoreCase)
                       || n.Contains("Status", StringComparison.OrdinalIgnoreCase)));
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
