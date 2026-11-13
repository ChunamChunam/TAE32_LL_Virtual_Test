using Microsoft.EntityFrameworkCore;
using TAE32.LLVirtualTest.Core.Entities;

namespace TAE32.LLVirtualTest.Infrastructure.Data;

public sealed class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
    {
    }

    public DbSet<SdkProject> SdkProjects => Set<SdkProject>();
    public DbSet<Chip> Chips => Set<Chip>();
    public DbSet<Peripheral> Peripherals => Set<Peripheral>();
    public DbSet<SdkFile> SdkFiles => Set<SdkFile>();
    public DbSet<LlFunction> LlFunctions => Set<LlFunction>();
    public DbSet<LlFunctionParameter> LlFunctionParameters => Set<LlFunctionParameter>();
    public DbSet<LlFunctionOperation> LlFunctionOperations => Set<LlFunctionOperation>();
    public DbSet<LlFunctionCall> LlFunctionCalls => Set<LlFunctionCall>();
    public DbSet<LlRegisterAccess> LlRegisterAccesses => Set<LlRegisterAccess>();
    public DbSet<LlMacroInfo> LlMacroInfos => Set<LlMacroInfo>();
    public DbSet<LlRegisterReference> LlRegisterReferences => Set<LlRegisterReference>();
    public DbSet<LlParseDiagnostic> LlParseDiagnostics => Set<LlParseDiagnostic>();
    public DbSet<ScanRecord> ScanRecords => Set<ScanRecord>();
    public DbSet<PeripheralInstance> PeripheralInstances => Set<PeripheralInstance>();
    public DbSet<RegisterDefinition> RegisterDefinitions => Set<RegisterDefinition>();
    public DbSet<RegisterField> RegisterFields => Set<RegisterField>();
    public DbSet<RegisterEnumValue> RegisterEnumValues => Set<RegisterEnumValue>();
    public DbSet<RegisterMacroReference> RegisterMacroReferences => Set<RegisterMacroReference>();
    public DbSet<RegisterParseDiagnostic> RegisterParseDiagnostics => Set<RegisterParseDiagnostic>();
    public DbSet<LlTestCase> LlTestCases => Set<LlTestCase>();
    public DbSet<LlTestRun> LlTestRuns => Set<LlTestRun>();
    public DbSet<LlCompilerProfile> LlCompilerProfiles => Set<LlCompilerProfile>();
    public DbSet<TestPlan> TestPlans => Set<TestPlan>();
    public DbSet<TestSuite> TestSuites => Set<TestSuite>();
    public DbSet<TestSuiteCase> TestSuiteCases => Set<TestSuiteCase>();
    public DbSet<TestBatchRun> TestBatchRuns => Set<TestBatchRun>();
    public DbSet<TestReportArtifact> TestReportArtifacts => Set<TestReportArtifact>();

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<SdkProject>(e =>
        {
            e.ToTable("SdkProjects");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.Property(x => x.SdkRootPath).HasMaxLength(1000).IsRequired();
            e.Property(x => x.ScanResultsPath).HasMaxLength(1000).IsRequired();
            e.Property(x => x.Version).HasMaxLength(100);
            e.HasIndex(x => x.Name);
            e.HasIndex(x => x.IsActive);
        });

        modelBuilder.Entity<Chip>(e =>
        {
            e.ToTable("Chips");
            e.HasKey(x => x.Id);
            e.Property(x => x.ModelName).HasMaxLength(100).IsRequired();
            e.Property(x => x.NaturalKey).HasMaxLength(200).IsRequired();
            e.Property(x => x.Level).HasMaxLength(50);
            e.Property(x => x.DetectionStatus).HasMaxLength(50);
            e.Property(x => x.Confidence).HasMaxLength(50);
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasOne(x => x.SdkProject).WithMany(p => p.Chips).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<Peripheral>(e =>
        {
            e.ToTable("Peripherals");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(100).IsRequired();
            e.Property(x => x.NaturalKey).HasMaxLength(200).IsRequired();
            e.Property(x => x.Confidence).HasMaxLength(50);
            e.Property(x => x.DetectionStatus).HasMaxLength(50);
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasIndex(x => x.Name);
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany(c => c.Peripherals).HasForeignKey(x => x.ChipId)
                .OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<SdkFile>(e =>
        {
            e.ToTable("SdkFiles");
            e.HasKey(x => x.Id);
            e.Property(x => x.RelativePath).HasMaxLength(1000).IsRequired();
            e.Property(x => x.FileName).HasMaxLength(260).IsRequired();
            e.Property(x => x.Extension).HasMaxLength(20);
            e.Property(x => x.NaturalKey).HasMaxLength(1000).IsRequired();
            e.Property(x => x.Role).HasMaxLength(100);
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasOne(x => x.SdkProject).WithMany(p => p.Files).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Peripheral).WithMany(p => p.Files).HasForeignKey(x => x.PeripheralId)
                .OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<LlFunction>(e =>
        {
            e.ToTable("LlFunctions");
            e.HasKey(x => x.Id);
            e.Property(x => x.FunctionName).HasMaxLength(256).IsRequired();
            e.Property(x => x.NaturalKey).HasMaxLength(1200).IsRequired();
            e.Property(x => x.ReturnType).HasMaxLength(256);
            e.Property(x => x.FunctionType).HasMaxLength(64);
            e.Property(x => x.Form).HasMaxLength(64);
            e.Property(x => x.PeripheralName).HasMaxLength(100);
            e.Property(x => x.ChipName).HasMaxLength(100);
            e.Property(x => x.FilePath).HasMaxLength(1000).IsRequired();
            e.Property(x => x.DetectionStatus).HasMaxLength(50);
            // Do NOT unique on FunctionName alone.
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasIndex(x => x.FunctionName);
            e.HasIndex(x => x.PeripheralName);
            e.HasIndex(x => x.Form);
            e.HasIndex(x => new { x.FilePath, x.StartLine });
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany(c => c.Functions).HasForeignKey(x => x.ChipId)
                .OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.Peripheral).WithMany(p => p.Functions).HasForeignKey(x => x.PeripheralId)
                .OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.SdkFile).WithMany(f => f.Functions).HasForeignKey(x => x.SdkFileId)
                .OnDelete(DeleteBehavior.SetNull);
            e.Property(x => x.Signature);
            e.Property(x => x.SourceText);
            e.Property(x => x.Modifiers).HasMaxLength(128);
            e.Property(x => x.ParseStatus).HasMaxLength(32);
            e.Property(x => x.ClangVersion).HasMaxLength(64);
        });

        ConfigureParseChild<LlFunctionParameter>(modelBuilder, "LlFunctionParameters");
        ConfigureParseChild<LlFunctionOperation>(modelBuilder, "LlFunctionOperations");
        ConfigureParseChild<LlFunctionCall>(modelBuilder, "LlFunctionCalls");
        ConfigureParseChild<LlRegisterAccess>(modelBuilder, "LlRegisterAccesses");
        ConfigureParseChild<LlRegisterReference>(modelBuilder, "LlRegisterReferences");

        modelBuilder.Entity<LlMacroInfo>(e =>
        {
            e.ToTable("LlMacroInfos");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(256).IsRequired();
            e.Property(x => x.DefinitionFile).HasMaxLength(1000);
            e.Property(x => x.Category).HasMaxLength(32);
            e.HasIndex(x => new { x.SdkProjectId, x.Name });
        });

        modelBuilder.Entity<LlParseDiagnostic>(e =>
        {
            e.ToTable("LlParseDiagnostics");
            e.HasKey(x => x.Id);
            e.Property(x => x.Severity).HasMaxLength(16);
            e.Property(x => x.Category).HasMaxLength(32);
            e.Property(x => x.Message).HasMaxLength(2000);
            e.Property(x => x.FilePath).HasMaxLength(1000);
            e.HasIndex(x => x.SdkProjectId);
            e.HasIndex(x => x.LlFunctionId);
        });

        modelBuilder.Entity<ScanRecord>(e =>
        {
            e.ToTable("ScanRecords");
            e.HasKey(x => x.Id);
            e.Property(x => x.SourceDirectory).HasMaxLength(1000).IsRequired();
            e.HasIndex(x => x.SdkProjectId);
            e.HasIndex(x => x.StartedAtUtc);
            e.HasOne(x => x.SdkProject).WithMany(p => p.ScanRecords).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<PeripheralInstance>(e =>
        {
            e.ToTable("PeripheralInstances");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(100).IsRequired();
            e.Property(x => x.ModuleName).HasMaxLength(100);
            e.Property(x => x.TypeDefName).HasMaxLength(128);
            e.Property(x => x.BaseAddressStatus).HasMaxLength(32);
            e.Property(x => x.DefinitionFile).HasMaxLength(1000);
            e.Property(x => x.NaturalKey).HasMaxLength(300).IsRequired();
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasIndex(x => x.Name);
            e.HasOne(x => x.SdkProject).WithMany(p => p.PeripheralInstances).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany().HasForeignKey(x => x.ChipId).OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.Peripheral).WithMany().HasForeignKey(x => x.PeripheralId).OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<RegisterDefinition>(e =>
        {
            e.ToTable("RegisterDefinitions");
            e.HasKey(x => x.Id);
            e.Property(x => x.StructName).HasMaxLength(128).IsRequired();
            e.Property(x => x.MemberName).HasMaxLength(128).IsRequired();
            e.Property(x => x.MemberType).HasMaxLength(256);
            e.Property(x => x.OffsetStatus).HasMaxLength(32);
            e.Property(x => x.AbsoluteAddressStatus).HasMaxLength(32);
            e.Property(x => x.AccessAttribute).HasMaxLength(16);
            e.Property(x => x.ResetValue).HasMaxLength(64);
            e.Property(x => x.Comment).HasMaxLength(2000);
            e.Property(x => x.DefinitionFile).HasMaxLength(1000).IsRequired();
            e.Property(x => x.ParseStatus).HasMaxLength(32);
            e.Property(x => x.NaturalKey).HasMaxLength(400).IsRequired();
            e.HasIndex(x => new { x.SdkProjectId, x.NaturalKey }).IsUnique();
            e.HasIndex(x => new { x.StructName, x.MemberName });
            e.HasOne(x => x.SdkProject).WithMany(p => p.RegisterDefinitions).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany().HasForeignKey(x => x.ChipId).OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.Peripheral).WithMany().HasForeignKey(x => x.PeripheralId).OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.PeripheralInstance).WithMany(i => i.Registers).HasForeignKey(x => x.PeripheralInstanceId)
                .OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<RegisterField>(e =>
        {
            e.ToTable("RegisterFields");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(128).IsRequired();
            e.Property(x => x.MaskExpression).HasMaxLength(256);
            e.Property(x => x.ResetValue).HasMaxLength(64);
            e.Property(x => x.AccessAttribute).HasMaxLength(16);
            e.Property(x => x.Description).HasMaxLength(2000);
            e.Property(x => x.PosMacroName).HasMaxLength(256);
            e.Property(x => x.MskMacroName).HasMaxLength(256);
            e.Property(x => x.DefinitionFile).HasMaxLength(1000);
            e.Property(x => x.ParseStatus).HasMaxLength(32);
            e.Property(x => x.NaturalKey).HasMaxLength(400).IsRequired();
            e.HasIndex(x => new { x.RegisterDefinitionId, x.NaturalKey }).IsUnique();
            e.HasOne(x => x.RegisterDefinition).WithMany(r => r.Fields).HasForeignKey(x => x.RegisterDefinitionId)
                .OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<RegisterEnumValue>(e =>
        {
            e.ToTable("RegisterEnumValues");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(128).IsRequired();
            e.Property(x => x.Description).HasMaxLength(2000);
            e.Property(x => x.DefinitionFile).HasMaxLength(1000);
            e.HasOne(x => x.RegisterField).WithMany(f => f.EnumValues).HasForeignKey(x => x.RegisterFieldId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.RegisterDefinition).WithMany(r => r.EnumValues).HasForeignKey(x => x.RegisterDefinitionId)
                .OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<RegisterMacroReference>(e =>
        {
            e.ToTable("RegisterMacroReferences");
            e.HasKey(x => x.Id);
            e.Property(x => x.MacroName).HasMaxLength(256).IsRequired();
            e.Property(x => x.MacroKind).HasMaxLength(16);
            e.Property(x => x.Expansion).HasMaxLength(512);
            e.Property(x => x.DefinitionFile).HasMaxLength(1000);
            e.Property(x => x.ReferenceFile).HasMaxLength(1000);
            e.HasIndex(x => new { x.SdkProjectId, x.MacroName });
            e.HasOne(x => x.SdkProject).WithMany(p => p.RegisterMacroReferences).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.RegisterDefinition).WithMany(r => r.MacroReferences).HasForeignKey(x => x.RegisterDefinitionId)
                .OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.RegisterField).WithMany(f => f.MacroReferences).HasForeignKey(x => x.RegisterFieldId)
                .OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<RegisterParseDiagnostic>(e =>
        {
            e.ToTable("RegisterParseDiagnostics");
            e.HasKey(x => x.Id);
            e.Property(x => x.Severity).HasMaxLength(16);
            e.Property(x => x.Category).HasMaxLength(32);
            e.Property(x => x.Message).HasMaxLength(2000);
            e.Property(x => x.FilePath).HasMaxLength(1000);
            e.Property(x => x.Detail).HasMaxLength(4000);
            e.Property(x => x.RelatedEntity).HasMaxLength(128);
            e.HasIndex(x => x.SdkProjectId);
            e.HasOne(x => x.SdkProject).WithMany(p => p.RegisterParseDiagnostics).HasForeignKey(x => x.SdkProjectId)
                .OnDelete(DeleteBehavior.Cascade);
        });
    }

    private static void ConfigureParseChild<T>(ModelBuilder modelBuilder, string table) where T : class
    {
        modelBuilder.Entity<T>(e =>
        {
            e.ToTable(table);
            e.HasKey("Id");
            if (typeof(T) == typeof(LlFunctionParameter))
            {
                var p = modelBuilder.Entity<LlFunctionParameter>();
                p.Property(x => x.Name).HasMaxLength(128);
                p.Property(x => x.Type).HasMaxLength(256);
                p.HasOne(x => x.LlFunction).WithMany(f => f.ParseParameters).HasForeignKey(x => x.LlFunctionId)
                    .OnDelete(DeleteBehavior.Cascade);
            }
            else if (typeof(T) == typeof(LlFunctionOperation))
            {
                var p = modelBuilder.Entity<LlFunctionOperation>();
                p.Property(x => x.OpKind).HasMaxLength(32);
                p.Property(x => x.AstKind).HasMaxLength(64);
                p.HasOne(x => x.LlFunction).WithMany(f => f.Operations).HasForeignKey(x => x.LlFunctionId)
                    .OnDelete(DeleteBehavior.Cascade);
            }
            else if (typeof(T) == typeof(LlFunctionCall))
            {
                var p = modelBuilder.Entity<LlFunctionCall>();
                p.Property(x => x.CalleeName).HasMaxLength(256);
                p.Property(x => x.CalleeKind).HasMaxLength(32);
                p.HasOne(x => x.LlFunction).WithMany(f => f.Calls).HasForeignKey(x => x.LlFunctionId)
                    .OnDelete(DeleteBehavior.Cascade);
            }
            else if (typeof(T) == typeof(LlRegisterAccess))
            {
                var p = modelBuilder.Entity<LlRegisterAccess>();
                p.Property(x => x.AccessKind).HasMaxLength(16);
                p.Property(x => x.MacroName).HasMaxLength(128);
                p.Property(x => x.RegisterPath).HasMaxLength(512);
                p.HasOne(x => x.LlFunction).WithMany(f => f.RegisterAccesses).HasForeignKey(x => x.LlFunctionId)
                    .OnDelete(DeleteBehavior.Cascade);
            }
            else if (typeof(T) == typeof(LlRegisterReference))
            {
                var p = modelBuilder.Entity<LlRegisterReference>();
                p.Property(x => x.MacroName).HasMaxLength(256);
                p.HasOne(x => x.LlFunction).WithMany(f => f.RegisterReferences).HasForeignKey(x => x.LlFunctionId)
                    .OnDelete(DeleteBehavior.Cascade);
                p.HasOne(x => x.MacroInfo).WithMany(m => m.References).HasForeignKey(x => x.MacroInfoId)
                    .OnDelete(DeleteBehavior.SetNull);
            }
        });

        modelBuilder.Entity<LlTestCase>(e =>
        {
            e.ToTable("LlTestCases");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.Property(x => x.FunctionName).HasMaxLength(256).IsRequired();
            e.Property(x => x.PeripheralName).HasMaxLength(64);
            e.Property(x => x.ChipModelName).HasMaxLength(64);
            e.Property(x => x.Status).HasMaxLength(32);
            e.Property(x => x.SourceFile).HasMaxLength(1000);
            e.HasIndex(x => new { x.SdkProjectId, x.FunctionName });
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany().HasForeignKey(x => x.ChipId).OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.LlFunction).WithMany().HasForeignKey(x => x.LlFunctionId).OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<LlTestRun>(e =>
        {
            e.ToTable("LlTestRuns");
            e.HasKey(x => x.Id);
            e.Property(x => x.Status).HasMaxLength(32);
            e.Property(x => x.CompilerPath).HasMaxLength(1000);
            e.HasIndex(x => x.LlTestCaseId);
            e.HasIndex(x => new { x.SdkProjectId, x.StartedAtUtc });
            e.HasIndex(x => new { x.SdkProjectId, x.Status });
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.TestCase).WithMany(c => c.Runs).HasForeignKey(x => x.LlTestCaseId).OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<LlCompilerProfile>(e =>
        {
            e.ToTable("LlCompilerProfiles");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(100);
            e.Property(x => x.ClangPath).HasMaxLength(1000);
        });

        modelBuilder.Entity<TestPlan>(e =>
        {
            e.ToTable("TestPlans");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.Property(x => x.Status).HasMaxLength(32);
            e.Property(x => x.SdkVersion).HasMaxLength(100);
            e.Property(x => x.ChipModelName).HasMaxLength(64);
            e.Property(x => x.PeripheralFilter).HasMaxLength(64);
            e.Property(x => x.TestType).HasMaxLength(64);
            e.HasIndex(x => new { x.SdkProjectId, x.Name });
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.Chip).WithMany().HasForeignKey(x => x.ChipId).OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<TestSuite>(e =>
        {
            e.ToTable("TestSuites");
            e.HasKey(x => x.Id);
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.Property(x => x.Status).HasMaxLength(32);
            e.Property(x => x.PeripheralName).HasMaxLength(64);
            e.HasIndex(x => new { x.SdkProjectId, x.Name });
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.TestPlan).WithMany(p => p.Suites).HasForeignKey(x => x.TestPlanId).OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<TestSuiteCase>(e =>
        {
            e.ToTable("TestSuiteCases");
            e.HasKey(x => x.Id);
            e.HasIndex(x => new { x.TestSuiteId, x.LlTestCaseId }).IsUnique();
            e.HasOne(x => x.TestSuite).WithMany(s => s.Cases).HasForeignKey(x => x.TestSuiteId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.TestCase).WithMany().HasForeignKey(x => x.LlTestCaseId).OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<TestBatchRun>(e =>
        {
            e.ToTable("TestBatchRuns");
            e.HasKey(x => x.Id);
            e.Property(x => x.ScopeKind).HasMaxLength(32);
            e.Property(x => x.Status).HasMaxLength(32);
            e.Property(x => x.ToolVersion).HasMaxLength(64);
            e.Property(x => x.CompilerVersion).HasMaxLength(200);
            e.HasIndex(x => x.SdkProjectId);
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.TestPlan).WithMany(p => p.BatchRuns).HasForeignKey(x => x.TestPlanId).OnDelete(DeleteBehavior.SetNull);
            e.HasOne(x => x.TestSuite).WithMany().HasForeignKey(x => x.TestSuiteId).OnDelete(DeleteBehavior.SetNull);
        });

        modelBuilder.Entity<TestReportArtifact>(e =>
        {
            e.ToTable("TestReportArtifacts");
            e.HasKey(x => x.Id);
            e.Property(x => x.Format).HasMaxLength(16);
            e.Property(x => x.FilePath).HasMaxLength(1000);
            e.Property(x => x.Title).HasMaxLength(200);
            e.HasOne(x => x.SdkProject).WithMany().HasForeignKey(x => x.SdkProjectId).OnDelete(DeleteBehavior.Cascade);
            e.HasOne(x => x.BatchRun).WithMany().HasForeignKey(x => x.TestBatchRunId).OnDelete(DeleteBehavior.SetNull);
        });
    }
}

