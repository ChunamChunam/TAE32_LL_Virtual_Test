using System.Diagnostics;
using System.Net.Http;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Core.Models;
using TAE32.LLVirtualTest.Infrastructure.Data;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

public sealed class ClangCompilerService : ICompilerService
{
    // Align with Phase3 libclang 18.1.x — official NSIS installer (silent /S /D=).
    private const string LlvmVersion = "18.1.8";
    private const string DownloadUrl =
        "https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/LLVM-18.1.8-win64.exe";
    private const string ExpectedSha256 = "94af030060d88cc17e9f00ef1663ebdc1126b35e16bebdfa1e807984b70abd8f";

    private static readonly HttpClient Http = new() { Timeout = TimeSpan.FromMinutes(45) };
    private readonly IDbContextFactory<AppDbContext> _dbFactory;
    private readonly ISdkProjectService _projects;
    private static readonly SemaphoreSlim EmbedLock = new(1, 1);

    public ClangCompilerService(IDbContextFactory<AppDbContext> dbFactory, ISdkProjectService projects)
    {
        _dbFactory = dbFactory;
        _projects = projects;
    }

    public static string EmbeddedLlvmRoot =>
        Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
            "TAE32.LLVirtualTest", "toolchain", "llvm");

    public static string EmbeddedClangPath => Path.Combine(EmbeddedLlvmRoot, "bin", "clang.exe");

    public async Task<CompilerEnvironmentInfo> CheckEnvironmentAsync(
        Guid sdkProjectId, CancellationToken cancellationToken = default)
    {
        var project = await _projects.GetByIdAsync(sdkProjectId, cancellationToken)
                      ?? throw new InvalidOperationException("SDK 项目不存在");
        var profile = await GetOrCreateProfileAsync(sdkProjectId, cancellationToken);
        var clang = ResolveClangPath(profile.ClangPath);
        var missing = new List<string>();
        if (clang is null)
            missing.Add("clang 可执行文件（可点「获取内置 Clang」或手动配置）");

        var includes = ResolveIncludePaths(project.SdkRootPath, missing);

        string? version = null;
        if (clang is not null)
        {
            version = await RunCaptureAsync(clang, "--version", cancellationToken);
            version = version.Split('\n', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
                .FirstOrDefault();
        }

        var defines = SplitCsv(profile.ExtraDefines);
        if (defines.Count == 0) defines.Add("TAE32G58xx");

        foreach (var extra in SplitCsv(profile.ExtraIncludes))
            if (Directory.Exists(extra) && !includes.Contains(extra, StringComparer.OrdinalIgnoreCase))
                includes.Add(extra);

        return new CompilerEnvironmentInfo
        {
            ClangFound = clang is not null,
            ClangPath = clang,
            ClangVersion = version,
            IncludePaths = includes,
            Defines = defines,
            Missing = missing,
            Summary = clang is null
                ? "未找到 Clang：无法编译真实 LL 函数。请点「获取内置 Clang」或手动配置 clang.exe。"
                : $"Clang OK: {clang} | includes={includes.Count} | missing={missing.Count}"
        };
    }

    public async Task SaveClangPathAsync(string? clangPath, CancellationToken cancellationToken = default)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var profile = await db.LlCompilerProfiles.FirstOrDefaultAsync(cancellationToken)
                      ?? new LlCompilerProfile { Name = "default" };
        if (profile.Id == Guid.Empty || !await db.LlCompilerProfiles.AnyAsync(x => x.Id == profile.Id, cancellationToken))
            db.LlCompilerProfiles.Add(profile);
        profile.ClangPath = string.IsNullOrWhiteSpace(clangPath) ? null : clangPath.Trim();
        profile.UpdatedAtUtc = DateTime.UtcNow;
        await db.SaveChangesAsync(cancellationToken);
    }

    public async Task<EmbeddedClangResult> EnsureEmbeddedClangAsync(
        IProgress<string>? progress = null,
        CancellationToken cancellationToken = default)
    {
        await EmbedLock.WaitAsync(cancellationToken);
        try
        {
            var existing = ResolveClangPath(null);
            if (existing is not null && existing.StartsWith(EmbeddedLlvmRoot, StringComparison.OrdinalIgnoreCase))
            {
                await SaveClangPathAsync(existing, cancellationToken);
                return new EmbeddedClangResult
                {
                    Succeeded = true,
                    AlreadyPresent = true,
                    ClangPath = existing,
                    Message = "已存在内置 Clang：" + existing
                };
            }

            if (File.Exists(EmbeddedClangPath))
            {
                await SaveClangPathAsync(EmbeddedClangPath, cancellationToken);
                return new EmbeddedClangResult
                {
                    Succeeded = true,
                    AlreadyPresent = true,
                    ClangPath = EmbeddedClangPath,
                    Message = "已找到本机内置工具链：" + EmbeddedClangPath
                };
            }

            if (!OperatingSystem.IsWindows())
            {
                return new EmbeddedClangResult
                {
                    Succeeded = false,
                    Message = "当前仅支持 Windows 自动获取 LLVM 安装包。"
                };
            }

            var cacheDir = Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
                "TAE32.LLVirtualTest", "toolchain", "cache");
            Directory.CreateDirectory(cacheDir);
            Directory.CreateDirectory(EmbeddedLlvmRoot);

            var installerPath = Path.Combine(cacheDir, $"LLVM-{LlvmVersion}-win64.exe");
            progress?.Report($"下载 LLVM {LlvmVersion}（约 350MB，需联网）…");

            if (!File.Exists(installerPath) || !await VerifySha256Async(installerPath, ExpectedSha256, cancellationToken))
            {
                await DownloadFileAsync(DownloadUrl, installerPath, progress, cancellationToken);
                if (!await VerifySha256Async(installerPath, ExpectedSha256, cancellationToken))
                {
                    return new EmbeddedClangResult
                    {
                        Succeeded = false,
                        Message = "下载文件 SHA256 校验失败，已中止安装。"
                    };
                }
            }
            else
            {
                progress?.Report("使用已缓存的安装包…");
            }

            progress?.Report("静默安装到本机数据目录…");
            // NSIS: /S silent, /D= must be last and unquoted.
            var installArgs = $"/S /D={EmbeddedLlvmRoot}";
            var (exit, stdout, stderr) = await RunAsync(installerPath, installArgs, cancellationToken);
            if (exit != 0)
            {
                return new EmbeddedClangResult
                {
                    Succeeded = false,
                    Message = $"LLVM 安装失败 (exit={exit}). {stderr} {stdout}".Trim()
                };
            }

            // Installer may finish before files flush.
            for (var i = 0; i < 30 && !File.Exists(EmbeddedClangPath); i++)
                await Task.Delay(500, cancellationToken);

            if (!File.Exists(EmbeddedClangPath))
            {
                return new EmbeddedClangResult
                {
                    Succeeded = false,
                    Message = "安装完成但未找到 clang.exe：" + EmbeddedClangPath
                };
            }

            await SaveClangPathAsync(EmbeddedClangPath, cancellationToken);
            progress?.Report("内置 Clang 就绪");
            return new EmbeddedClangResult
            {
                Succeeded = true,
                AlreadyPresent = false,
                ClangPath = EmbeddedClangPath,
                Message = $"已安装 LLVM {LlvmVersion} → {EmbeddedClangPath}"
            };
        }
        catch (OperationCanceledException)
        {
            throw;
        }
        catch (Exception ex)
        {
            return new EmbeddedClangResult
            {
                Succeeded = false,
                Message = "获取内置 Clang 失败：" + ex.Message
            };
        }
        finally
        {
            EmbedLock.Release();
        }
    }

    public async Task<CompileJobResult> CompileHarnessAsync(
        Guid sdkProjectId,
        string harnessCPath,
        string outputDllPath,
        IReadOnlyList<string>? extraDefines = null,
        CancellationToken cancellationToken = default)
    {
        var env = await CheckEnvironmentAsync(sdkProjectId, cancellationToken);
        if (!env.ClangFound || string.IsNullOrWhiteSpace(env.ClangPath))
        {
            return new CompileJobResult
            {
                Succeeded = false,
                ExitCode = -1,
                Log = env.Summary,
                Errors = new[] { "Clang 未配置或未找到" },
                HarnessPath = harnessCPath
            };
        }

        Directory.CreateDirectory(Path.GetDirectoryName(outputDllPath)!);
        var args = new StringBuilder();
        // Windows MSVC target rejects -fPIC; PIC is implied for DLL on that triple.
        args.Append("-shared -O0 -g -std=c11 ");
        if (OperatingSystem.IsWindows())
            args.Append("-fuse-ld=lld ");
        else
            args.Append("-fPIC ");

        // Same host-compile macros as Phase3 ClangEnvironment: CMSIS picks gcc path via __GNUC__.
        var hostDefines = new List<string>
        {
            "TAE32G58xx",
            "__GNUC__=4",
            "__STDC__=1"
        };
        foreach (var d in hostDefines
                     .Concat(env.Defines)
                     .Concat(extraDefines ?? Array.Empty<string>())
                     .Distinct(StringComparer.Ordinal))
            args.Append("-D").Append(d).Append(' ');

        foreach (var inc in env.IncludePaths)
            args.Append("-I\"").Append(inc).Append("\" ");
        args.Append("-Wno-everything ");
        args.Append("-o \"").Append(outputDllPath).Append("\" ");
        args.Append('"').Append(harnessCPath).Append('"');

        var profile = await GetOrCreateProfileAsync(sdkProjectId, cancellationToken);
        if (!string.IsNullOrWhiteSpace(profile.ExtraArgs))
            args.Append(' ').Append(profile.ExtraArgs);

        var clangDir = Path.GetDirectoryName(env.ClangPath!)!;
        var (code, stdout, stderr) = await RunAsync(env.ClangPath!, args.ToString(), cancellationToken, extraPath: clangDir);
        var log = $"CMD: {env.ClangPath} {args}\n\nSTDOUT:\n{stdout}\n\nSTDERR:\n{stderr}";
        var errors = Regex.Matches(stderr + "\n" + stdout, @"error:.*", RegexOptions.IgnoreCase)
            .Select(m => m.Value.Trim()).Distinct().Take(40).ToList();
        if (code != 0 && errors.Count == 0)
            errors.Add($"clang exit code {code}");

        return new CompileJobResult
        {
            Succeeded = code == 0 && File.Exists(outputDllPath),
            ExitCode = code,
            Log = log,
            OutputDllPath = File.Exists(outputDllPath) ? outputDllPath : null,
            HarnessPath = harnessCPath,
            Errors = errors
        };
    }

    private async Task<LlCompilerProfile> GetOrCreateProfileAsync(Guid sdkProjectId, CancellationToken ct)
    {
        await using var db = await _dbFactory.CreateDbContextAsync(ct);
        var profile = await db.LlCompilerProfiles
            .FirstOrDefaultAsync(x => x.SdkProjectId == null || x.SdkProjectId == sdkProjectId, ct);
        if (profile is not null) return profile;
        profile = new LlCompilerProfile
        {
            SdkProjectId = sdkProjectId,
            Name = "default",
            ExtraDefines = "TAE32G58xx",
            DefaultTimeoutMs = 10000
        };
        db.LlCompilerProfiles.Add(profile);
        await db.SaveChangesAsync(ct);
        return profile;
    }

    internal static string? ResolveClangPath(string? configured)
    {
        if (!string.IsNullOrWhiteSpace(configured) && File.Exists(configured))
            return Path.GetFullPath(configured);

        if (File.Exists(EmbeddedClangPath))
            return EmbeddedClangPath;

        var appTools = Path.Combine(AppContext.BaseDirectory, "tools", "llvm", "bin", "clang.exe");
        if (File.Exists(appTools))
            return appTools;

        var fromPath = FindOnPath("clang.exe") ?? FindOnPath("clang");
        if (fromPath is not null) return fromPath;

        foreach (var candidate in new[]
                 {
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "LLVM", "bin", "clang.exe"),
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86), "LLVM", "bin", "clang.exe"),
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Programs", "LLVM", "bin", "clang.exe")
                 })
        {
            if (File.Exists(candidate)) return candidate;
        }
        return null;
    }

    private static string? FindOnPath(string name)
    {
        var path = Environment.GetEnvironmentVariable("PATH") ?? "";
        foreach (var dir in path.Split(Path.PathSeparator, StringSplitOptions.RemoveEmptyEntries))
        {
            try
            {
                var full = Path.Combine(dir.Trim('"'), name);
                if (File.Exists(full)) return full;
            }
            catch { /* ignore */ }
        }
        return null;
    }

    private static List<string> SplitCsv(string? text)
        => string.IsNullOrWhiteSpace(text)
            ? new List<string>()
            : text.Split(new[] { ';', ',', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
                .ToList();

    private static List<string> ResolveIncludePaths(string sdkRootPath, List<string> missing)
    {
        var sdkRoot = Path.GetFullPath(sdkRootPath);
        var includes = new List<string>();
        foreach (var rel in new[]
                 {
                     "SDK/Drivers/TAE32G58xx_Driver/LL",
                     "LL",
                     "SDK/Drivers/TAE32G58xx_Device/Inc",
                     "SDK/ProjectTemplateLL/User/Inc",
                     "SDK/Drivers/CMSISv5/Core/Include",
                     "SDK/Drivers/CMSISv6/Core/Include",
                     "Drivers/CMSIS/Core/Include"
                 })
        {
            var p = Path.Combine(sdkRoot, rel.Replace('/', Path.DirectorySeparatorChar));
            if (Directory.Exists(p) && !includes.Contains(p, StringComparer.OrdinalIgnoreCase))
                includes.Add(p);
        }

        // Also probe parent of LL root (common DFP layout).
        var parent = Directory.GetParent(sdkRoot)?.FullName;
        if (parent is not null)
        {
            foreach (var rel in new[]
                     {
                         "SDK/Drivers/TAE32G58xx_Device/Inc",
                         "SDK/Drivers/CMSISv5/Core/Include",
                         "SDK/ProjectTemplateLL/User/Inc"
                     })
            {
                var p = Path.Combine(parent, rel.Replace('/', Path.DirectorySeparatorChar));
                if (Directory.Exists(p) && !includes.Contains(p, StringComparer.OrdinalIgnoreCase))
                    includes.Add(p);
            }
        }

        if (!includes.Any(p => File.Exists(Path.Combine(p, "tae32g58xx_ll_gpio.h"))
                               || File.Exists(Path.Combine(p, "tae32g58xx_ll.h"))))
            missing.Add("LL headers (tae32g58xx_ll_*.h)");
        if (!includes.Any(p => File.Exists(Path.Combine(p, "tae32g58xx.h"))))
            missing.Add("tae32g58xx.h");
        return includes;
    }

    private static async Task DownloadFileAsync(
        string url, string destPath, IProgress<string>? progress, CancellationToken ct)
    {
        Directory.CreateDirectory(Path.GetDirectoryName(destPath)!);
        var tmp = destPath + ".partial";
        if (File.Exists(tmp)) File.Delete(tmp);

        using var response = await Http.GetAsync(url, HttpCompletionOption.ResponseHeadersRead, ct);
        response.EnsureSuccessStatusCode();
        var total = response.Content.Headers.ContentLength;
        await using var input = await response.Content.ReadAsStreamAsync(ct);
        await using var output = new FileStream(tmp, FileMode.Create, FileAccess.Write, FileShare.None, 1024 * 128, true);

        var buffer = new byte[1024 * 128];
        long read = 0;
        int n;
        var lastPct = -1;
        while ((n = await input.ReadAsync(buffer.AsMemory(0, buffer.Length), ct)) > 0)
        {
            await output.WriteAsync(buffer.AsMemory(0, n), ct);
            read += n;
            if (total is > 0)
            {
                var pct = (int)(read * 100 / total.Value);
                if (pct != lastPct && pct % 5 == 0)
                {
                    lastPct = pct;
                    progress?.Report($"下载中 {pct}% ({read / (1024 * 1024)} / {total.Value / (1024 * 1024)} MB)");
                }
            }
        }

        await output.FlushAsync(ct);
        output.Close();
        if (File.Exists(destPath)) File.Delete(destPath);
        File.Move(tmp, destPath);
    }

    private static async Task<bool> VerifySha256Async(string path, string expectedHex, CancellationToken ct)
    {
        await using var stream = File.OpenRead(path);
        var hash = await SHA256.HashDataAsync(stream, ct);
        var actual = Convert.ToHexString(hash).ToLowerInvariant();
        return string.Equals(actual, expectedHex, StringComparison.OrdinalIgnoreCase);
    }

    private static async Task<(int code, string stdout, string stderr)> RunAsync(
        string file, string args, CancellationToken ct, string? extraPath = null)
    {
        var psi = new ProcessStartInfo
        {
            FileName = file,
            Arguments = args,
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            UseShellExecute = false,
            CreateNoWindow = true
        };
        if (!string.IsNullOrWhiteSpace(extraPath))
        {
            var path = Environment.GetEnvironmentVariable("PATH") ?? "";
            psi.Environment["PATH"] = extraPath + Path.PathSeparator + path;
        }

        using var p = new Process { StartInfo = psi };
        p.Start();
        var stdoutTask = p.StandardOutput.ReadToEndAsync(ct);
        var stderrTask = p.StandardError.ReadToEndAsync(ct);
        await p.WaitForExitAsync(ct);
        return (p.ExitCode, await stdoutTask, await stderrTask);
    }

    private static async Task<string> RunCaptureAsync(string file, string args, CancellationToken ct)
    {
        var (_, stdout, stderr) = await RunAsync(file, args, ct);
        return string.IsNullOrWhiteSpace(stdout) ? stderr : stdout;
    }
}
