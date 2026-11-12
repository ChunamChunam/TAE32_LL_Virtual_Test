using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;

namespace TAE32.LLVirtualTest.Infrastructure.Data;

/// <summary>Design-time factory for EF migrations.</summary>
public sealed class AppDbContextFactory : IDesignTimeDbContextFactory<AppDbContext>
{
    public AppDbContext CreateDbContext(string[] args)
    {
        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite("Data Source=tae32_ll_virtual_test.db")
            .Options;
        return new AppDbContext(options);
    }
}
