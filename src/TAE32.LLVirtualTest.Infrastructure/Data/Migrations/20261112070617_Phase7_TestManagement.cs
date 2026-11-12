using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TAE32.LLVirtualTest.Infrastructure.Data.Migrations
{
    /// <inheritdoc />
    public partial class Phase7_TestManagement : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "TestPlans",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ChipId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Name = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    Description = table.Column<string>(type: "TEXT", nullable: true),
                    SdkVersion = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    ChipModelName = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    PeripheralFilter = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    FunctionFilter = table.Column<string>(type: "TEXT", nullable: true),
                    TestType = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    Status = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true),
                    ArchivedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestPlans", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TestPlans_Chips_ChipId",
                        column: x => x.ChipId,
                        principalTable: "Chips",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_TestPlans_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "TestSuites",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    TestPlanId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Name = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    Description = table.Column<string>(type: "TEXT", nullable: true),
                    PeripheralName = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    Status = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestSuites", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TestSuites_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_TestSuites_TestPlans_TestPlanId",
                        column: x => x.TestPlanId,
                        principalTable: "TestPlans",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateTable(
                name: "TestBatchRuns",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    TestPlanId = table.Column<Guid>(type: "TEXT", nullable: true),
                    TestSuiteId = table.Column<Guid>(type: "TEXT", nullable: true),
                    ScopeKind = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    ScopeValue = table.Column<string>(type: "TEXT", nullable: true),
                    Status = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    ToolVersion = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    CompilerVersion = table.Column<string>(type: "TEXT", maxLength: 200, nullable: true),
                    SdkVersion = table.Column<string>(type: "TEXT", nullable: true),
                    ChipModelName = table.Column<string>(type: "TEXT", nullable: true),
                    TotalCount = table.Column<int>(type: "INTEGER", nullable: false),
                    PassedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    FailedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    ErrorCount = table.Column<int>(type: "INTEGER", nullable: false),
                    SkippedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    TimeoutCount = table.Column<int>(type: "INTEGER", nullable: false),
                    CancelledCount = table.Column<int>(type: "INTEGER", nullable: false),
                    CompileFailCount = table.Column<int>(type: "INTEGER", nullable: false),
                    AverageDurationMs = table.Column<double>(type: "REAL", nullable: false),
                    LogDirectory = table.Column<string>(type: "TEXT", nullable: true),
                    Notes = table.Column<string>(type: "TEXT", nullable: true),
                    CaseRunIdsJson = table.Column<string>(type: "TEXT", nullable: false),
                    StartedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    FinishedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestBatchRuns", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TestBatchRuns_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_TestBatchRuns_TestPlans_TestPlanId",
                        column: x => x.TestPlanId,
                        principalTable: "TestPlans",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_TestBatchRuns_TestSuites_TestSuiteId",
                        column: x => x.TestSuiteId,
                        principalTable: "TestSuites",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateTable(
                name: "TestSuiteCases",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    TestSuiteId = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlTestCaseId = table.Column<Guid>(type: "TEXT", nullable: false),
                    SortOrder = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestSuiteCases", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TestSuiteCases_LlTestCases_LlTestCaseId",
                        column: x => x.LlTestCaseId,
                        principalTable: "LlTestCases",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_TestSuiteCases_TestSuites_TestSuiteId",
                        column: x => x.TestSuiteId,
                        principalTable: "TestSuites",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "TestReportArtifacts",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    TestBatchRunId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Format = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    FilePath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    Title = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    Disclaimer = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestReportArtifacts", x => x.Id);
                    table.ForeignKey(
                        name: "FK_TestReportArtifacts_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_TestReportArtifacts_TestBatchRuns_TestBatchRunId",
                        column: x => x.TestBatchRunId,
                        principalTable: "TestBatchRuns",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateIndex(
                name: "IX_TestBatchRuns_SdkProjectId",
                table: "TestBatchRuns",
                column: "SdkProjectId");

            migrationBuilder.CreateIndex(
                name: "IX_TestBatchRuns_TestPlanId",
                table: "TestBatchRuns",
                column: "TestPlanId");

            migrationBuilder.CreateIndex(
                name: "IX_TestBatchRuns_TestSuiteId",
                table: "TestBatchRuns",
                column: "TestSuiteId");

            migrationBuilder.CreateIndex(
                name: "IX_TestPlans_ChipId",
                table: "TestPlans",
                column: "ChipId");

            migrationBuilder.CreateIndex(
                name: "IX_TestPlans_SdkProjectId_Name",
                table: "TestPlans",
                columns: new[] { "SdkProjectId", "Name" });

            migrationBuilder.CreateIndex(
                name: "IX_TestReportArtifacts_SdkProjectId",
                table: "TestReportArtifacts",
                column: "SdkProjectId");

            migrationBuilder.CreateIndex(
                name: "IX_TestReportArtifacts_TestBatchRunId",
                table: "TestReportArtifacts",
                column: "TestBatchRunId");

            migrationBuilder.CreateIndex(
                name: "IX_TestSuiteCases_LlTestCaseId",
                table: "TestSuiteCases",
                column: "LlTestCaseId");

            migrationBuilder.CreateIndex(
                name: "IX_TestSuiteCases_TestSuiteId_LlTestCaseId",
                table: "TestSuiteCases",
                columns: new[] { "TestSuiteId", "LlTestCaseId" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_TestSuites_SdkProjectId_Name",
                table: "TestSuites",
                columns: new[] { "SdkProjectId", "Name" });

            migrationBuilder.CreateIndex(
                name: "IX_TestSuites_TestPlanId",
                table: "TestSuites",
                column: "TestPlanId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "TestReportArtifacts");

            migrationBuilder.DropTable(
                name: "TestSuiteCases");

            migrationBuilder.DropTable(
                name: "TestBatchRuns");

            migrationBuilder.DropTable(
                name: "TestSuites");

            migrationBuilder.DropTable(
                name: "TestPlans");
        }
    }
}
