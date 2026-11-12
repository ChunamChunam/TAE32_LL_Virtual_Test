using System.Runtime.InteropServices;
using System.Text.Json;

namespace TAE32.LLVirtualTest.NativeRunner;

/// <summary>
/// Out-of-process harness runner. Native AccessViolation only kills this child process,
/// not the WPF UI host.
/// Usage: NativeRunner.exe &lt;dll&gt; &lt;periIn.bin&gt; &lt;periOut.bin&gt; &lt;args.bin&gt; &lt;result.json&gt;
/// </summary>
internal static class Program
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate int Tae32RunDelegate(ref PeriImg peri, IntPtr args, out uint outRet);

    [StructLayout(LayoutKind.Sequential)]
    private struct PeriImg
    {
        public IntPtr Base;
        public uint Size;
    }

    private static int Main(string[] args)
    {
        if (args.Length < 5)
        {
            Console.Error.WriteLine("usage: NativeRunner <dll> <periIn> <periOut> <argsBlob> <resultJson>");
            return 2;
        }

        var dllPath = args[0];
        var periInPath = args[1];
        var periOutPath = args[2];
        var argsPath = args[3];
        var resultPath = args[4];

        try
        {
            if (!File.Exists(dllPath)) throw new FileNotFoundException("DLL missing", dllPath);
            var periBytes = File.ReadAllBytes(periInPath);
            var argBytes = File.ReadAllBytes(argsPath);
            if (periBytes.Length == 0) throw new InvalidOperationException("empty peri image");

            var periPtr = Marshal.AllocHGlobal(periBytes.Length);
            var argsPtr = Marshal.AllocHGlobal(Math.Max(argBytes.Length, 8));
            IntPtr module = IntPtr.Zero;
            try
            {
                Marshal.Copy(periBytes, 0, periPtr, periBytes.Length);
                if (argBytes.Length > 0) Marshal.Copy(argBytes, 0, argsPtr, argBytes.Length);
                else Marshal.WriteInt32(argsPtr, 0);

                module = NativeLibrary.Load(dllPath);
                if (!NativeLibrary.TryGetExport(module, "tae32_run", out var fn))
                    throw new InvalidOperationException("export tae32_run missing");

                var del = Marshal.GetDelegateForFunctionPointer<Tae32RunDelegate>(fn);
                var peri = new PeriImg { Base = periPtr, Size = (uint)periBytes.Length };
                var rc = del(ref peri, argsPtr, out var ret);

                var outBytes = new byte[periBytes.Length];
                Marshal.Copy(periPtr, outBytes, 0, outBytes.Length);
                File.WriteAllBytes(periOutPath, outBytes);
                WriteResult(resultPath, rc, ret, crash: false, error: null);
                return rc == 0 ? 0 : 3;
            }
            finally
            {
                if (module != IntPtr.Zero) NativeLibrary.Free(module);
                Marshal.FreeHGlobal(argsPtr);
                Marshal.FreeHGlobal(periPtr);
            }
        }
        catch (Exception ex)
        {
            try
            {
                WriteResult(resultPath, -999, 0, crash: false, error: ex.Message);
            }
            catch { /* ignore */ }
            Console.Error.WriteLine(ex);
            return 1;
        }
    }

    private static void WriteResult(string path, int rc, uint ret, bool crash, string? error)
    {
        var json = JsonSerializer.Serialize(new
        {
            rc,
            ret,
            crash,
            error
        });
        File.WriteAllText(path, json);
    }
}
