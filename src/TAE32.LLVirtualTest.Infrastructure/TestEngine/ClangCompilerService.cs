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
    private static readonly object EnvCacheLock = new();
    private static Guid? _envCacheProjectId;
    private static CompilerEnvironmentInfo? _envCache;
    private static DateTime _envCacheUtc = DateTime.MinValue;
    private static readonly TimeSpan EnvCacheTtl = TimeSpan.FromMinutes(2);

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
        lock (EnvCacheLock)
        {
            if (_envCache is not null &&
                _envCacheProjectId == sdkProjectId &&
                DateTime.UtcNow - _envCacheUtc < EnvCacheTtl)
            {
                return _envCache;
            }
        }

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

        var layout = Core.Sdk.SdkSeriesLayout.Discover(project.SdkRootPath);
        var seriesDefine = layout?.ChipModel ?? "TAE32G58xx";
        var defines = SplitCsv(profile.ExtraDefines);
        // Stale DB default ExtraDefines=TAE32G58xx must not stick when the active SDK is another series.
        if (defines.Count == 0
            || (defines.Count == 1
                && defines[0].Equals("TAE32G58xx", StringComparison.OrdinalIgnoreCase)
                && !seriesDefine.Equals("TAE32G58xx", StringComparison.OrdinalIgnoreCase)))
        {
            defines = new List<string> { seriesDefine };
        }
        else if (!defines.Any(d => d.Equals(seriesDefine, StringComparison.OrdinalIgnoreCase)))
        {
            defines.Insert(0, seriesDefine);
        }

        foreach (var extra in SplitCsv(profile.ExtraIncludes))
            if (Directory.Exists(extra) && !includes.Contains(extra, StringComparer.OrdinalIgnoreCase))
                includes.Add(extra);

        var hostSdk = TestEnginePaths.HostSdkIncludeDirectory();
        if (Directory.Exists(hostSdk) && !includes.Contains(hostSdk, StringComparer.OrdinalIgnoreCase))
            includes.Add(hostSdk);

        // LLVM clang on Windows does not ship CRT headers; prefer system SDK/MinGW, else app-bundled freestanding CRT.
        foreach (var crt in ResolveHostCrtIncludePaths())
        {
            if (!includes.Contains(crt, StringComparer.OrdinalIgnoreCase))
                includes.Add(crt);
        }

        var usingBundledCrt = false;
        if (!HostCrtHeadersAvailable(includes))
        {
            var bundled = EmbeddedHostCrtIncludeDirectory();
            if (bundled is not null)
            {
                includes.Add(bundled);
                usingBundledCrt = true;
            }
            else if (clang is not null)
            {
                missing.Add(
                    "C 标准库头（string.h）：内置 CRT 不可用。请安装 MinGW-w64（https://winlibs.com/），" +
                    "解压后将 mingw64\\include 配到 ExtraIncludes，或安装到 C:\\mingw64");
            }
        }

        var info = new CompilerEnvironmentInfo
        {
            ClangFound = clang is not null,
            ClangPath = clang,
            ClangVersion = version,
            IncludePaths = includes,
            Defines = defines,
            Missing = missing,
            Summary = clang is null
                ? "未找到 Clang：无法编译真实 LL 函数。请点「获取内置 Clang」或手动配置 clang.exe。"
                : !HostCrtHeadersAvailable(includes)
                    ? $"Clang 已找到，但缺少 C 运行时头文件（string.h）。请安装 MinGW-w64：https://winlibs.com/ （推荐 UCRT 运行时 zip，解压到 C:\\mingw64）。clang={clang}"
                    : usingBundledCrt
                        ? $"Clang OK: {clang} | includes={includes.Count} | CRT=应用内置 | missing={missing.Count}"
                        : $"Clang OK: {clang} | includes={includes.Count} | missing={missing.Count}"
        };
        lock (EnvCacheLock)
        {
            _envCacheProjectId = sdkProjectId;
            _envCache = info;
            _envCacheUtc = DateTime.UtcNow;
        }
        return info;
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

        await using var dbForRoot = await _dbFactory.CreateDbContextAsync(cancellationToken);
        var sdkRootForDefines = await dbForRoot.SdkProjects.AsNoTracking()
            .Where(p => p.Id == sdkProjectId)
            .Select(p => p.SdkRootPath)
            .FirstOrDefaultAsync(cancellationToken);
        var compileLayout = string.IsNullOrWhiteSpace(sdkRootForDefines)
            ? null
            : Core.Sdk.SdkSeriesLayout.Discover(sdkRootForDefines);
        var hostDefines = new List<string>
        {
            compileLayout?.ChipModel ?? "TAE32G58xx",
            "TMR6=1",
            "__GNUC__=4",
            "__STDC__=1"
        };
        var defineArgs = new StringBuilder();
        foreach (var d in hostDefines
                     .Concat(env.Defines)
                     .Concat(extraDefines ?? Array.Empty<string>())
                     .Distinct(StringComparer.Ordinal))
            defineArgs.Append("-D").Append(d).Append(' ');

        // Link strategy (does not change assertion / stage judgment in LlTestEngine):
        // 1) MSVC libs present → normal MSVC link (same as before on VS machines)
        // 2) else → freestanding link + tae32_host_crt.c (memcpy/memset only)
        //    Do NOT override MinGW/system headers with HostSdk/crt when they already exist —
        //    only inject bundled headers when string.h is completely missing.
        var msvcLibs = OperatingSystem.IsWindows()
            ? ResolveMsvcLibraryPaths()
            : Array.Empty<string>();
        var freestanding = OperatingSystem.IsWindows() && msvcLibs.Count == 0;

        var includePaths = env.IncludePaths.ToList();
        if (freestanding && !HostCrtHeadersAvailable(includePaths))
        {
            var bundled = EmbeddedHostCrtIncludeDirectory();
            if (bundled is not null && !includePaths.Contains(bundled, StringComparer.OrdinalIgnoreCase))
                includePaths.Add(bundled);
        }

        var includeArgs = new StringBuilder();
        foreach (var inc in includePaths)
            includeArgs.Append("-I\"").Append(inc).Append("\" ");

        var clangDir = Path.GetDirectoryName(env.ClangPath!)!;
        var compileInput = await TryMaterializePointerFixedHarnessAsync(
            env.ClangPath!, harnessCPath, defineArgs.ToString(), includeArgs.ToString(),
            cancellationToken, extraPath: clangDir)
            ?? harnessCPath;

        var args = new StringBuilder();
        args.Append("-shared -O0 -g -std=c11 ");
        if (OperatingSystem.IsWindows())
            args.Append("-fuse-ld=lld ");
        else
            args.Append("-fPIC ");
        args.Append(defineArgs);
        args.Append(includeArgs);

        string? linkModeNote = null;
        IReadOnlyDictionary<string, string>? extraEnv = null;
        string? freestandingCrtC = null;
        if (OperatingSystem.IsWindows())
        {
            if (!freestanding)
            {
                foreach (var libDir in msvcLibs)
                    args.Append("-L\"").Append(libDir).Append("\" ");
                var libPath = string.Join(";", msvcLibs);
                var existingLib = Environment.GetEnvironmentVariable("LIB");
                if (!string.IsNullOrWhiteSpace(existingLib))
                    libPath = libPath + ";" + existingLib;
                extraEnv = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase)
                {
                    ["LIB"] = libPath
                };
                linkModeNote = "LINK=MSVC libs (" + msvcLibs.Count + " dirs)";
            }
            else
            {
                // No VS/Build Tools: avoid libcmt/oldnames; provide memcpy via tae32_host_crt.c.
                args.Append("-fno-stack-protector -fno-asynchronous-unwind-tables ");
                args.Append("-nostdlib -nodefaultlibs ");
                args.Append("-Xlinker /NODEFAULTLIB ");
                args.Append("-Xlinker /NOENTRY ");
                freestandingCrtC = EmbeddedHostCrtSourcePath();
                linkModeNote = freestandingCrtC is not null
                    ? "LINK=freestanding (+ tae32_host_crt.c for memcpy; headers from system/MinGW/bundled)"
                    : "LINK=freestanding (missing tae32_host_crt.c)";
            }
        }

        args.Append("-Wno-everything ");
        args.Append("-o \"").Append(outputDllPath).Append("\" ");
        args.Append('"').Append(compileInput).Append('"');
        if (freestandingCrtC is not null)
            args.Append(" \"").Append(freestandingCrtC).Append('"');

        var profile = await GetOrCreateProfileAsync(sdkProjectId, cancellationToken);
        if (!string.IsNullOrWhiteSpace(profile.ExtraArgs))
            args.Append(' ').Append(profile.ExtraArgs);

        var (code, stdout, stderr) = await RunAsync(
            env.ClangPath!, args.ToString(), cancellationToken, extraPath: clangDir, extraEnv: extraEnv);
        var log = $"CMD: {env.ClangPath} {args}\n\nSTDOUT:\n{stdout}\n\nSTDERR:\n{stderr}";
        if (!string.IsNullOrWhiteSpace(linkModeNote))
            log += "\n\n" + linkModeNote;
        if (!string.Equals(compileInput, harnessCPath, StringComparison.OrdinalIgnoreCase))
            log += $"\n\nHOSTFIX: {compileInput}";
        var errors = Regex.Matches(stderr + "\n" + stdout, @"error:.*", RegexOptions.IgnoreCase)
            .Select(m => m.Value.Trim()).Distinct().Take(40).ToList();
        if (code != 0 && errors.Count == 0)
            errors.Add($"clang exit code {code}");

        if (errors.Any(e =>
                e.Contains("string.h", StringComparison.OrdinalIgnoreCase)
                || e.Contains("stdlib.h", StringComparison.OrdinalIgnoreCase)
                || e.Contains("stddef.h", StringComparison.OrdinalIgnoreCase)
                || e.Contains("stdint.h", StringComparison.OrdinalIgnoreCase)
                || e.Contains("limits.h", StringComparison.OrdinalIgnoreCase)))
        {
            const string hint =
                "提示：若仍缺 C 标准库头文件，请安装 MinGW-w64（https://winlibs.com/），" +
                "推荐 Win64 + UCRT 运行时 zip，解压到 C:\\mingw64 后重试。";
            if (!errors.Any(e => e.Contains("winlibs.com", StringComparison.OrdinalIgnoreCase)))
                errors.Add(hint);
            log += "\n\n" + hint;
        }

        if (errors.Any(e =>
                e.Contains("libcmt.lib", StringComparison.OrdinalIgnoreCase)
                || e.Contains("oldnames.lib", StringComparison.OrdinalIgnoreCase)
                || e.Contains("vcruntime", StringComparison.OrdinalIgnoreCase)
                || e.Contains("undefined symbol: memcpy", StringComparison.OrdinalIgnoreCase)
                || e.Contains("undefined symbol: memset", StringComparison.OrdinalIgnoreCase)))
        {
            const string hint =
                "提示：缺少 CRT 链接符号。请更新本软件（freestanding 会自动编入 tae32_host_crt.c），" +
                "或安装 MinGW-w64（https://winlibs.com/）到 C:\\mingw64。";
            if (!errors.Any(e => e.Contains("winlibs.com", StringComparison.OrdinalIgnoreCase)
                                 || e.Contains("tae32_host_crt", StringComparison.OrdinalIgnoreCase)))
                errors.Add(hint);
            log += "\n\n" + hint;
        }

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
        var sdkRoot = await db.SdkProjects.AsNoTracking()
            .Where(p => p.Id == sdkProjectId)
            .Select(p => p.SdkRootPath)
            .FirstOrDefaultAsync(ct);
        var defaultDefine = Core.Sdk.SdkSeriesLayout.Discover(sdkRoot ?? "")?.ChipModel ?? "TAE32G58xx";
        profile = new LlCompilerProfile
        {
            SdkProjectId = sdkProjectId,
            Name = "default",
            ExtraDefines = defaultDefine,
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
        var layout = Core.Sdk.SdkSeriesLayout.Discover(sdkRoot);

        void AddDir(string? path)
        {
            if (string.IsNullOrWhiteSpace(path) || !Directory.Exists(path)) return;
            if (!includes.Contains(path, StringComparer.OrdinalIgnoreCase))
                includes.Add(path);
        }

        if (layout is not null)
        {
            AddDir(layout.LlRoot);
            if (layout.DeviceHeaderPath is not null)
                AddDir(Path.GetDirectoryName(layout.DeviceHeaderPath));
            if (layout.LlConfHeaderPath is not null)
                AddDir(Path.GetDirectoryName(layout.LlConfHeaderPath));
        }

        foreach (var rel in new[]
                 {
                     "LL",
                     "SDK/ProjectTemplateLL/User/Inc",
                     "ProjectTemplateHAL/User/Inc",
                     "ProjectTemplateLL/User/Inc",
                     "SDK/Drivers/CMSISv5/Core/Include",
                     "SDK/Drivers/CMSISv6/Core/Include",
                     "Drivers/CMSISv5/Core/Include",
                     "Drivers/CMSISv6/Core/Include",
                     "Drivers/CMSIS/Core/Include"
                 })
        {
            AddDir(Path.Combine(sdkRoot, rel.Replace('/', Path.DirectorySeparatorChar)));
        }

        try
        {
            foreach (var cmsis in Directory.EnumerateDirectories(sdkRoot, "Include", SearchOption.AllDirectories)
                         .Where(d => d.Contains("CMSIS", StringComparison.OrdinalIgnoreCase))
                         .Take(8))
                AddDir(cmsis);
        }
        catch
        {
            // ignore
        }

        var family = layout?.FamilyId;
        var deviceName = layout?.DeviceHeaderFileName ?? "tae32*.h";
        var llGlobHint = family is null ? "tae32*_ll_*.h" : family + "_ll_*.h";
        if (family is null
            || !includes.Any(p => File.Exists(Path.Combine(p, family + "_ll_gpio.h"))
                                  || File.Exists(Path.Combine(p, family + "_ll.h"))
                                  || Directory.Exists(p) && Directory.EnumerateFiles(p, family + "_ll_*.h").Any()))
            missing.Add($"LL headers ({llGlobHint})");
        if (family is null
            || !includes.Any(p => File.Exists(Path.Combine(p, family + ".h"))))
            missing.Add(deviceName);
        return includes;
    }

    /// <summary>
    /// App-bundled freestanding CRT (HostSdk/crt). Ships with the installer — no Windows SDK download.
    /// </summary>
    internal static string? EmbeddedHostCrtIncludeDirectory()
    {
        var hostSdk = TestEnginePaths.HostSdkIncludeDirectory();
        var crt = Path.Combine(hostSdk, "crt");
        return File.Exists(Path.Combine(crt, "string.h")) ? crt : null;
    }

    /// <summary>
    /// Strong memcpy/memset definitions linked in freestanding mode (clang emits external calls at -O0).
    /// </summary>
    internal static string? EmbeddedHostCrtSourcePath()
    {
        var crt = EmbeddedHostCrtIncludeDirectory();
        if (crt is null) return null;
        var src = Path.Combine(crt, "tae32_host_crt.c");
        return File.Exists(src) ? src : null;
    }

    /// <summary>
    /// Locate Windows CRT / UCRT / MSVC / MinGW include dirs so clang can resolve &lt;string.h&gt;.
    /// Official LLVM win64 builds do not bundle these headers. App-bundled HostSdk/crt is added separately
    /// when none of these system paths are present.
    /// </summary>
    internal static IReadOnlyList<string> ResolveHostCrtIncludePaths()
    {
        if (!OperatingSystem.IsWindows())
            return Array.Empty<string>();

        var result = new List<string>();

        // Windows 10/11 SDK: ucrt contains string.h / stdlib.h; um/shared often needed by CRT.
        foreach (var kitsRoot in new[]
                 {
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86), "Windows Kits", "10", "Include"),
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Windows Kits", "10", "Include")
                 })
        {
            if (!Directory.Exists(kitsRoot)) continue;
            var verDir = Directory.GetDirectories(kitsRoot)
                .Select(d => new DirectoryInfo(d))
                .Where(d => File.Exists(Path.Combine(d.FullName, "ucrt", "string.h")))
                .OrderByDescending(d => d.Name, StringComparer.OrdinalIgnoreCase)
                .FirstOrDefault();
            if (verDir is null) continue;
            foreach (var sub in new[] { "ucrt", "shared", "um" })
            {
                var p = Path.Combine(verDir.FullName, sub);
                if (Directory.Exists(p) && !result.Contains(p, StringComparer.OrdinalIgnoreCase))
                    result.Add(p);
            }

            break;
        }

        // MSVC toolset headers (stddef.h / intrin.h companions) — fixed shallow layout only.
        foreach (var editionRoot in EnumerateMsvcToolsRoots())
        {
            try
            {
                var msvcInclude = Directory.GetDirectories(editionRoot)
                    .Select(ver => Path.Combine(ver, "include"))
                    .Where(inc => File.Exists(Path.Combine(inc, "stddef.h")))
                    .OrderByDescending(inc => inc, StringComparer.OrdinalIgnoreCase)
                    .FirstOrDefault();
                if (msvcInclude is not null && !result.Contains(msvcInclude, StringComparer.OrdinalIgnoreCase))
                {
                    result.Add(msvcInclude);
                    break;
                }
            }
            catch
            {
                /* ignore */
            }
        }

        // MinGW-w64 / WinLibs (https://winlibs.com/) common extract locations.
        foreach (var mingw in EnumerateMingwIncludeCandidates())
        {
            if (File.Exists(Path.Combine(mingw, "string.h"))
                && !result.Contains(mingw, StringComparer.OrdinalIgnoreCase))
                result.Add(mingw);
        }

        return result;
    }

    private static IEnumerable<string> EnumerateMingwIncludeCandidates()
    {
        yield return @"C:\mingw64\include";
        yield return @"C:\mingw64\x86_64-w64-mingw32\include";
        yield return @"C:\msys64\mingw64\include";
        yield return Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
            "Programs", "mingw64", "include");
        yield return Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile),
            "mingw64", "include");
        yield return Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile),
            "Downloads", "mingw64", "include");

        // WinLibs zip often extracts as mingw64\ next to the archive name folder.
        foreach (var root in new[]
                 {
                     @"C:\",
                     Environment.GetFolderPath(Environment.SpecialFolder.UserProfile),
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads")
                 })
        {
            if (string.IsNullOrWhiteSpace(root) || !Directory.Exists(root)) continue;
            string[] dirs;
            try { dirs = Directory.GetDirectories(root, "mingw64", SearchOption.TopDirectoryOnly); }
            catch { continue; }
            foreach (var d in dirs)
                yield return Path.Combine(d, "include");
        }
    }

    private static IEnumerable<string> EnumerateMsvcToolsRoots()
    {
        foreach (var programFiles in new[]
                 {
                     Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles),
                     Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86)
                 })
        {
            if (string.IsNullOrWhiteSpace(programFiles)) continue;
            foreach (var year in new[] { "2022", "2019", "2026", "2017" })
            {
                foreach (var edition in new[] { "BuildTools", "Community", "Professional", "Enterprise" })
                {
                    var msvc = Path.Combine(programFiles, "Microsoft Visual Studio", year, edition, "VC", "Tools", "MSVC");
                    if (Directory.Exists(msvc))
                        yield return msvc;
                }
            }
        }
    }

    /// <summary>
    /// MSVC + Windows SDK library dirs containing libcmt.lib / ucrt / um (x64).
    /// Empty when VS Build Tools are not installed — harness then links freestanding.
    /// </summary>
    internal static IReadOnlyList<string> ResolveMsvcLibraryPaths()
    {
        if (!OperatingSystem.IsWindows())
            return Array.Empty<string>();

        var result = new List<string>();

        foreach (var editionRoot in EnumerateMsvcToolsRoots())
        {
            try
            {
                var libX64 = Directory.GetDirectories(editionRoot)
                    .Select(ver => Path.Combine(ver, "lib", "x64"))
                    .Where(p => File.Exists(Path.Combine(p, "libcmt.lib")))
                    .OrderByDescending(p => p, StringComparer.OrdinalIgnoreCase)
                    .FirstOrDefault();
                if (libX64 is not null)
                {
                    result.Add(libX64);
                    break;
                }
            }
            catch
            {
                /* ignore */
            }
        }

        // Without MSVC libcmt/oldnames, Windows SDK um/ucrt alone cannot satisfy the default clang link.
        if (!result.Any(p => File.Exists(Path.Combine(p, "libcmt.lib"))))
            return Array.Empty<string>();

        foreach (var kitsLibRoot in new[]
                 {
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86), "Windows Kits", "10", "Lib"),
                     Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Windows Kits", "10", "Lib")
                 })
        {
            if (!Directory.Exists(kitsLibRoot)) continue;
            var verDir = Directory.GetDirectories(kitsLibRoot)
                .Select(d => new DirectoryInfo(d))
                .Where(d => File.Exists(Path.Combine(d.FullName, "ucrt", "x64", "ucrt.lib"))
                            || File.Exists(Path.Combine(d.FullName, "um", "x64", "kernel32.lib")))
                .OrderByDescending(d => d.Name, StringComparer.OrdinalIgnoreCase)
                .FirstOrDefault();
            if (verDir is null) continue;
            foreach (var sub in new[] { Path.Combine("ucrt", "x64"), Path.Combine("um", "x64") })
            {
                var p = Path.Combine(verDir.FullName, sub);
                if (Directory.Exists(p) && !result.Contains(p, StringComparer.OrdinalIgnoreCase))
                    result.Add(p);
            }

            break;
        }

        return result;
    }

    private static bool HostCrtHeadersAvailable(IEnumerable<string> includes)
        => includes.Any(p => File.Exists(Path.Combine(p, "string.h")));

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

    private static async Task<string?> TryMaterializePointerFixedHarnessAsync(
        string clangPath,
        string harnessCPath,
        string defineArgs,
        string includeArgs,
        CancellationToken ct,
        string? extraPath = null)
    {
        if (!File.Exists(harnessCPath))
            return null;

        var ppArgs = $"-E -std=c11 -P {defineArgs}{includeArgs}-Wno-everything \"{harnessCPath}\"";
        var (code, stdout, stderr) = await RunAsync(clangPath, ppArgs, ct, extraPath: extraPath);
        if (code != 0 || string.IsNullOrEmpty(stdout))
            return null;

        var needsFix = stdout.Contains("((uint32_t) ((uint32_t)(&", StringComparison.Ordinal)
            || stdout.Contains("(uint32_t) ((uint32_t)(&", StringComparison.Ordinal)
            || stdout.Contains("0x40023048UL", StringComparison.Ordinal);
        if (!needsFix)
            return null;

        var fixedSrc = HostHarnessPointerFix.Apply(stdout);
        var outPath = Path.Combine(
            Path.GetDirectoryName(harnessCPath)!,
            Path.GetFileNameWithoutExtension(harnessCPath) + ".hostfix.c");
        await File.WriteAllTextAsync(outPath, fixedSrc, ct);
        return outPath;
    }

    private static async Task<(int code, string stdout, string stderr)> RunAsync(
        string file,
        string args,
        CancellationToken ct,
        string? extraPath = null,
        IReadOnlyDictionary<string, string>? extraEnv = null)
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

        if (extraEnv is not null)
        {
            foreach (var (key, value) in extraEnv)
                psi.Environment[key] = value;
        }

        using var p = new Process { StartInfo = psi };
        p.Start();
        var stdoutTask = p.StandardOutput.ReadToEndAsync(CancellationToken.None);
        var stderrTask = p.StandardError.ReadToEndAsync(CancellationToken.None);
        try
        {
            await p.WaitForExitAsync(ct);
        }
        catch (OperationCanceledException)
        {
            try { p.Kill(entireProcessTree: true); } catch { /* ignore */ }
            try { await p.WaitForExitAsync(CancellationToken.None); } catch { /* ignore */ }
            throw;
        }

        return (p.ExitCode, await stdoutTask, await stderrTask);
    }

    private static async Task<string> RunCaptureAsync(string file, string args, CancellationToken ct)
    {
        var (_, stdout, stderr) = await RunAsync(file, args, ct);
        return string.IsNullOrWhiteSpace(stdout) ? stderr : stdout;
    }
}
