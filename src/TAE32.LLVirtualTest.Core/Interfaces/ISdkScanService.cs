using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

/// <summary>
/// Scans a real TAE32 LL SDK directory and writes Phase-1 compatible JSON reports.
/// Does not invent chip/peripheral/function data.
/// </summary>
public interface ISdkScanService
{
    /// <param name="sdkRootPath">SDK package root or LL folder.</param>
    /// <param name="outputDirectory">Where to write 03/04/05 JSON files.</param>
    Task<SdkScanResult> ScanAsync(string sdkRootPath, string outputDirectory, CancellationToken cancellationToken = default);
}
