using Microsoft.Extensions.DependencyInjection;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.SDK.Import;
using TAE32.LLVirtualTest.SDK.Parse;
using TAE32.LLVirtualTest.SDK.Register;
using TAE32.LLVirtualTest.SDK.Scan;

namespace TAE32.LLVirtualTest.SDK;

public static class DependencyInjection
{
    public static IServiceCollection AddSdkServices(this IServiceCollection services)
    {
        services.AddSingleton<IScanImportService, ScanImportService>();
        services.AddSingleton<ISdkScanService, LlSdkScanService>();
        services.AddSingleton<ILLFunctionParser, LlFunctionParseService>();
        services.AddSingleton<IRegisterParser, RegisterParseService>();
        return services;
    }
}
