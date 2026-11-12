using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TAE32.LLVirtualTest.Infrastructure.Data.Migrations
{
    /// <inheritdoc />
    public partial class Phase3_LlDeepParse : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "BodyEndLine",
                table: "LlFunctions",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "BodyStartLine",
                table: "LlFunctions",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "ClangVersion",
                table: "LlFunctions",
                type: "TEXT",
                maxLength: 64,
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "EndColumn",
                table: "LlFunctions",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<bool>(
                name: "IsInline",
                table: "LlFunctions",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<bool>(
                name: "IsStatic",
                table: "LlFunctions",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "Modifiers",
                table: "LlFunctions",
                type: "TEXT",
                maxLength: 128,
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "ParseStatus",
                table: "LlFunctions",
                type: "TEXT",
                maxLength: 32,
                nullable: true);

            migrationBuilder.AddColumn<DateTime>(
                name: "ParsedAtUtc",
                table: "LlFunctions",
                type: "TEXT",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "Signature",
                table: "LlFunctions",
                type: "TEXT",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "SourceText",
                table: "LlFunctions",
                type: "TEXT",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "LlFunctionCalls",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    CalleeName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: false),
                    CalleeKind = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    CallFile = table.Column<string>(type: "TEXT", nullable: true),
                    CallLine = table.Column<int>(type: "INTEGER", nullable: false),
                    CallCount = table.Column<int>(type: "INTEGER", nullable: false),
                    CalleeChip = table.Column<string>(type: "TEXT", nullable: true),
                    CalleePeripheral = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlFunctionCalls", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlFunctionCalls_LlFunctions_LlFunctionId",
                        column: x => x.LlFunctionId,
                        principalTable: "LlFunctions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "LlFunctionOperations",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    OpKind = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    Sequence = table.Column<int>(type: "INTEGER", nullable: false),
                    SourceText = table.Column<string>(type: "TEXT", nullable: true),
                    StartLine = table.Column<int>(type: "INTEGER", nullable: false),
                    EndLine = table.Column<int>(type: "INTEGER", nullable: false),
                    AstKind = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    ParentOpId = table.Column<Guid>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlFunctionOperations", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlFunctionOperations_LlFunctions_LlFunctionId",
                        column: x => x.LlFunctionId,
                        principalTable: "LlFunctions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "LlFunctionParameters",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    Name = table.Column<string>(type: "TEXT", maxLength: 128, nullable: false),
                    Type = table.Column<string>(type: "TEXT", maxLength: 256, nullable: false),
                    Position = table.Column<int>(type: "INTEGER", nullable: false),
                    IsConst = table.Column<bool>(type: "INTEGER", nullable: false),
                    IsPointer = table.Column<bool>(type: "INTEGER", nullable: false),
                    RawText = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlFunctionParameters", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlFunctionParameters_LlFunctions_LlFunctionId",
                        column: x => x.LlFunctionId,
                        principalTable: "LlFunctions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "LlMacroInfos",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    Name = table.Column<string>(type: "TEXT", maxLength: 256, nullable: false),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    DefinitionLine = table.Column<int>(type: "INTEGER", nullable: false),
                    Expansion = table.Column<string>(type: "TEXT", nullable: true),
                    Category = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlMacroInfos", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "LlParseDiagnostics",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Severity = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Category = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    Message = table.Column<string>(type: "TEXT", maxLength: 2000, nullable: false),
                    FilePath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    Line = table.Column<int>(type: "INTEGER", nullable: false),
                    Column = table.Column<int>(type: "INTEGER", nullable: false),
                    Detail = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlParseDiagnostics", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "LlRegisterAccesses",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    AccessKind = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Expression = table.Column<string>(type: "TEXT", nullable: true),
                    RegisterPath = table.Column<string>(type: "TEXT", maxLength: 512, nullable: true),
                    MacroName = table.Column<string>(type: "TEXT", maxLength: 128, nullable: true),
                    StartLine = table.Column<int>(type: "INTEGER", nullable: false),
                    EndLine = table.Column<int>(type: "INTEGER", nullable: false),
                    AstKind = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlRegisterAccesses", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlRegisterAccesses_LlFunctions_LlFunctionId",
                        column: x => x.LlFunctionId,
                        principalTable: "LlFunctions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "LlRegisterReferences",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    LlFunctionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    MacroInfoId = table.Column<Guid>(type: "TEXT", nullable: true),
                    MacroName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    ReferenceFile = table.Column<string>(type: "TEXT", nullable: true),
                    ReferenceLine = table.Column<int>(type: "INTEGER", nullable: false),
                    ExpansionSnippet = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LlRegisterReferences", x => x.Id);
                    table.ForeignKey(
                        name: "FK_LlRegisterReferences_LlFunctions_LlFunctionId",
                        column: x => x.LlFunctionId,
                        principalTable: "LlFunctions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_LlRegisterReferences_LlMacroInfos_MacroInfoId",
                        column: x => x.MacroInfoId,
                        principalTable: "LlMacroInfos",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctionCalls_LlFunctionId",
                table: "LlFunctionCalls",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctionOperations_LlFunctionId",
                table: "LlFunctionOperations",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlFunctionParameters_LlFunctionId",
                table: "LlFunctionParameters",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlMacroInfos_SdkProjectId_Name",
                table: "LlMacroInfos",
                columns: new[] { "SdkProjectId", "Name" });

            migrationBuilder.CreateIndex(
                name: "IX_LlParseDiagnostics_LlFunctionId",
                table: "LlParseDiagnostics",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlParseDiagnostics_SdkProjectId",
                table: "LlParseDiagnostics",
                column: "SdkProjectId");

            migrationBuilder.CreateIndex(
                name: "IX_LlRegisterAccesses_LlFunctionId",
                table: "LlRegisterAccesses",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlRegisterReferences_LlFunctionId",
                table: "LlRegisterReferences",
                column: "LlFunctionId");

            migrationBuilder.CreateIndex(
                name: "IX_LlRegisterReferences_MacroInfoId",
                table: "LlRegisterReferences",
                column: "MacroInfoId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "LlFunctionCalls");

            migrationBuilder.DropTable(
                name: "LlFunctionOperations");

            migrationBuilder.DropTable(
                name: "LlFunctionParameters");

            migrationBuilder.DropTable(
                name: "LlParseDiagnostics");

            migrationBuilder.DropTable(
                name: "LlRegisterAccesses");

            migrationBuilder.DropTable(
                name: "LlRegisterReferences");

            migrationBuilder.DropTable(
                name: "LlMacroInfos");

            migrationBuilder.DropColumn(
                name: "BodyEndLine",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "BodyStartLine",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "ClangVersion",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "EndColumn",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "IsInline",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "IsStatic",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "Modifiers",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "ParseStatus",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "ParsedAtUtc",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "Signature",
                table: "LlFunctions");

            migrationBuilder.DropColumn(
                name: "SourceText",
                table: "LlFunctions");
        }
    }
}
