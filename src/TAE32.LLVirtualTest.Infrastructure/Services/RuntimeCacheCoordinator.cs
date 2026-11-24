using Microsoft.Data.Sqlite;
using TAE32.LLVirtualTest.Core.Interfaces;
using TAE32.LLVirtualTest.Infrastructure.TestEngine;
using TAE32.LLVirtualTest.Infrastructure.VirtualMcu;

namespace TAE32.LLVirtualTest.Infrastructure.Services;

public sealed class RuntimeCacheCoordinator : IRuntimeCacheCoordinator
{
    private readonly IVirtualMcuService _virtualMcu;

    public RuntimeCacheCoordinator(IVirtualMcuService virtualMcu) => _virtualMcu = virtualMcu;

    public void InvalidateAfterDatabaseMutation()
    {
        SqliteConnection.ClearAllPools();
        SdkMacroSemanticCatalog.ClearMemoryCacheForTests();
        ChipHeaderAddressCatalog.ClearMemoryCacheForTests();
        ClangCompilerService.InvalidateEnvironmentCache();
        _virtualMcu.DiscardAllInMemoryInstances();
    }
}