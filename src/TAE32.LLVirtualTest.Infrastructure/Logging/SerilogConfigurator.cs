using Serilog;

namespace TAE32.LLVirtualTest.Infrastructure.Logging;

public static class SerilogConfigurator
{
    public static void Configure(string logDirectory)
    {
        Directory.CreateDirectory(logDirectory);
        var logFile = Path.Combine(logDirectory, "app-.log");

        Log.Logger = new LoggerConfiguration()
            .MinimumLevel.Information()
            .Enrich.FromLogContext()
            .WriteTo.Console()
            .WriteTo.File(
                logFile,
                rollingInterval: RollingInterval.Day,
                retainedFileCountLimit: 14,
                shared: true)
            .CreateLogger();
    }
}
