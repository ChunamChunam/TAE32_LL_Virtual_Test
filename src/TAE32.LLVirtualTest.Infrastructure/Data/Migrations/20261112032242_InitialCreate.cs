using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TAE32.LLVirtualTest.Infrastructure.Data.Migrations
{
    /// <inheritdoc />
    public partial class InitialCreate : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "SdkProjects",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    Name = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    SdkRootPath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    ScanResultsPath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    Version = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    Description = table.Column<string>(type: "TEXT", nullable: true),
                    ScanStatus = table.Column<int>(type: "INTEGER", nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true),
                    LastImportedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true),
                    IsActive = table.Column<bool>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SdkProjects", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Chips",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ModelName = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    Level = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    DetectionStatus = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    Confidence = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    Notes = table.Column<string>(type: "TEXT", nullable: true),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Chips", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Chips_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "ScanRecords",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    StartedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    FinishedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true),
                    Status = table.Column<int>(type: "INTEGER", nullable: false),
                    SourceDirectory = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    ChipCount = table.Column<int>(type: "INTEGER", nullable: false),
                    PeripheralCount = table.Column<int>(type: "INTEGER", nullable: false),
                    FunctionCount = table.Column<int>(type: "INTEGER", nullable: false),
                    FileCount = table.Column<int>(type: "INTEGER", nullable: false),
                    InsertedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    UpdatedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    SkippedCount = table.Column<int>(type: "INTEGER", nullable: false),
                    ErrorCount = table.Column<int>(type: "INTEGER", nullable: false),
                    SummaryJson = table.Column<string>(type: "TEXT", nullable: true),
                    ErrorSummary = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_ScanRecords", x => x.Id);
                    table.ForeignKey(
                        name: "FK_ScanRecords_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Peripherals",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ChipId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Name = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    SerialNumber = table.Column<int>(type: "INTEGER", nullable: true),
                    InlineFunctionCount = table.Column<int>(type: "INTEGER", nullable: false),
                    AllFormsFunctionCount = table.Column<int>(type: "INTEGER", nullable: true),
                    InstancesJson = table.Column<string>(type: "TEXT", nullable: true),
                    TypedefsJson = table.Column<string>(type: "TEXT", nullable: true),
                    RelatedFilesJson = table.Column<string>(type: "TEXT", nullable: true),
                    Confidence = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    DetectionStatus = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    Notes = table.Column<string>(type: "TEXT", nullable: true),
                    IsCommonDriver = table.Column<bool>(type: "INTEGER", nullable: false),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Peripherals", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Peripherals_Chips_ChipId",
                        column: x => x.ChipId,
                        principalTable: "Chips",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_Peripherals_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "SdkFiles",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    PeripheralId = table.Column<Guid>(type: "TEXT", nullable: true),
                    RelativePath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    FileName = table.Column<string>(type: "TEXT", maxLength: 260, nullable: false),
                    Extension = table.Column<string>(type: "TEXT", maxLength: 20, nullable: false),
                    Role = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    SizeBytes = table.Column<long>(type: "INTEGER", nullable: true),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SdkFiles", x => x.Id);
                    table.ForeignKey(
                        name: "FK_SdkFiles_Peripherals_PeripheralId",
                        column: x => x.PeripheralId,
                        principalTable: "Peripherals",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_SdkFiles_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "LlFunctions",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ChipId = table.Column<Guid>(type: "TEXT", nullable: true),
                    PeripheralId = table.Column<Guid>(type: "TEXT", nullable: true),
                    SdkFileId = table.Column<Guid>(type: "TEXT", nullable: true),
                    FunctionName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: false),
                    ReturnType = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    Parameters = table.Column<string>(type: "TEXT", nullable: true),
                    FunctionType = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    Form = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    PeripheralName = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    ChipName = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    FilePath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    StartLine = table.Column<int>(type: "INTEGER", nullable: false),
                    EndLine = table.Column<int>(type: "INTEGER", nullable: false),
                    DetectionStatus = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 1200, nullable: false),
                    CreatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: false),
                    UpdatedAtUtc = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlFunctions", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlFunctions_Chips_ChipId",
                        column: x => x.ChipId,
                        principalTable: "Chips",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_LlFunctions_Peripherals_PeripheralId",
                        column: x => x.PeripheralId,
                        principalTable: "Peripherals",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_LlFunctions_SdkFiles_SdkFileId",
                        column: x => x.SdkFileId,
                        principalTable: "SdkFiles",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_LlFunctions_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Chips_SdkProjectId_NaturalKey",
                table: "Chips",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_ChipId",
                table: "LlFunctions",
                column: "ChipId");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_FilePath_StartLine",
                table: "LlFunctions",
                columns: new[] { "FilePath", "StartLine" });

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_Form",
                table: "LlFunctions",
                column: "Form");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_FunctionName",
                table: "LlFunctions",
                column: "FunctionName");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_PeripheralId",
                table: "LlFunctions",
                column: "PeripheralId");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_PeripheralName",
                table: "LlFunctions",
                column: "PeripheralName");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_SdkFileId",
                table: "LlFunctions",
                column: "SdkFileId");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctions_SdkProjectId_NaturalKey",
                table: "LlFunctions",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_Peripherals_ChipId",
                table: "Peripherals",
                column: "ChipId");

            migrationBuilder.CreateIndex(
                name: "IX_Peripherals_Name",
                table: "Peripherals",
                column: "Name");

            migrationBuilder.CreateIndex(
                name: "IX_Peripherals_SdkProjectId_NaturalKey",
                table: "Peripherals",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_ScanRecords_SdkProjectId",
                table: "ScanRecords",
                column: "SdkProjectId");

            migrationBuilder.CreateIndex(
                name: "IX_ScanRecords_StartedAtUtc",
                table: "ScanRecords",
                column: "StartedAtUtc");

            migrationBuilder.CreateIndex(
                name: "IX_SdkFiles_PeripheralId",
                table: "SdkFiles",
                column: "PeripheralId");

            migrationBuilder.CreateIndex(
                name: "IX_SdkFiles_SdkProjectId_NaturalKey",
                table: "SdkFiles",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_SdkProjects_IsActive",
                table: "SdkProjects",
                column: "IsActive");

            migrationBuilder.CreateIndex(
                name: "IX_SdkProjects_Name",
                table: "SdkProjects",
                column: "Name");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "LlFunctions");

            migrationBuilder.DropTable(
                name: "ScanRecords");

            migrationBuilder.DropTable(
                name: "SdkFiles");

            migrationBuilder.DropTable(
                name: "Peripherals");

            migrationBuilder.DropTable(
                name: "Chips");

            migrationBuilder.DropTable(
                name: "SdkProjects");
        }
    }
}
