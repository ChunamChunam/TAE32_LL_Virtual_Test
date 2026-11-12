using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Core.Interfaces;

public interface ITestReportService
{
    Task<TestReportResult> GenerateAsync(TestReportRequest request, CancellationToken cancellationToken = default);

    /// <summary>Legacy single-run entry used by early stubs.</summary>
    Task GenerateAsync(Guid runId, CancellationToken cancellationToken = default);

    Task<IReadOnlyList<TestReportArtifact>> ListArtifactsAsync(Guid sdkProjectId, int take = 50, CancellationToken ct = default);
}
