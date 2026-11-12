using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface IScanImportService
{
    Task<ImportResult> ImportAsync(Guid sdkProjectId, CancellationToken cancellationToken = default);
}
