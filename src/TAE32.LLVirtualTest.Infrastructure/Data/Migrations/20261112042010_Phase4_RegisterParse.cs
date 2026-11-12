using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TAE32.LLVirtualTest.Infrastructure.Data.Migrations
{
    /// <inheritdoc />
    public partial class Phase4_RegisterParse : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "PeripheralInstances",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ChipId = table.Column<Guid>(type: "TEXT", nullable: true),
                    PeripheralId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Name = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    ModuleName = table.Column<string>(type: "TEXT", maxLength: 100, nullable: true),
                    TypeDefName = table.Column<string>(type: "TEXT", maxLength: 128, nullable: true),
                    BaseAddress = table.Column<uint>(type: "INTEGER", nullable: true),
                    BaseAddressStatus = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    DefinitionLine = table.Column<int>(type: "INTEGER", nullable: true),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 300, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_PeripheralInstances", x => x.Id);
                    table.ForeignKey(
                        name: "FK_PeripheralInstances_Chips_ChipId",
                        column: x => x.ChipId,
                        principalTable: "Chips",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_PeripheralInstances_Peripherals_PeripheralId",
                        column: x => x.PeripheralId,
                        principalTable: "Peripherals",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_PeripheralInstances_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "RegisterParseDiagnostics",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    Severity = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Category = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    Message = table.Column<string>(type: "TEXT", maxLength: 2000, nullable: false),
                    FilePath = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    Line = table.Column<int>(type: "INTEGER", nullable: true),
                    Detail = table.Column<string>(type: "TEXT", maxLength: 4000, nullable: true),
                    RelatedEntity = table.Column<string>(type: "TEXT", maxLength: 128, nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_RegisterParseDiagnostics", x => x.Id);
                    table.ForeignKey(
                        name: "FK_RegisterParseDiagnostics_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "RegisterDefinitions",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    ChipId = table.Column<Guid>(type: "TEXT", nullable: true),
                    PeripheralId = table.Column<Guid>(type: "TEXT", nullable: true),
                    PeripheralInstanceId = table.Column<Guid>(type: "TEXT", nullable: true),
                    StructName = table.Column<string>(type: "TEXT", maxLength: 128, nullable: false),
                    MemberName = table.Column<string>(type: "TEXT", maxLength: 128, nullable: false),
                    MemberType = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    OffsetBytes = table.Column<int>(type: "INTEGER", nullable: true),
                    OffsetStatus = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    AbsoluteAddress = table.Column<uint>(type: "INTEGER", nullable: true),
                    AbsoluteAddressStatus = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    WidthBits = table.Column<int>(type: "INTEGER", nullable: true),
                    ResetValue = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    AccessAttribute = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Comment = table.Column<string>(type: "TEXT", maxLength: 2000, nullable: true),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: false),
                    StartLine = table.Column<int>(type: "INTEGER", nullable: false),
                    EndLine = table.Column<int>(type: "INTEGER", nullable: false),
                    ParseStatus = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 400, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_RegisterDefinitions", x => x.Id);
                    table.ForeignKey(
                        name: "FK_RegisterDefinitions_Chips_ChipId",
                        column: x => x.ChipId,
                        principalTable: "Chips",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_RegisterDefinitions_PeripheralInstances_PeripheralInstanceId",
                        column: x => x.PeripheralInstanceId,
                        principalTable: "PeripheralInstances",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_RegisterDefinitions_Peripherals_PeripheralId",
                        column: x => x.PeripheralId,
                        principalTable: "Peripherals",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_RegisterDefinitions_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "RegisterFields",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    RegisterDefinitionId = table.Column<Guid>(type: "TEXT", nullable: false),
                    Name = table.Column<string>(type: "TEXT", maxLength: 128, nullable: false),
                    BitPosition = table.Column<int>(type: "INTEGER", nullable: true),
                    BitWidth = table.Column<int>(type: "INTEGER", nullable: true),
                    Mask = table.Column<uint>(type: "INTEGER", nullable: true),
                    MaskExpression = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    ResetValue = table.Column<string>(type: "TEXT", maxLength: 64, nullable: true),
                    AccessAttribute = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Description = table.Column<string>(type: "TEXT", maxLength: 2000, nullable: true),
                    PosMacroName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    MskMacroName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: true),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    DefinitionLine = table.Column<int>(type: "INTEGER", nullable: true),
                    ParseStatus = table.Column<string>(type: "TEXT", maxLength: 32, nullable: false),
                    NaturalKey = table.Column<string>(type: "TEXT", maxLength: 400, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_RegisterFields", x => x.Id);
                    table.ForeignKey(
                        name: "FK_RegisterFields_RegisterDefinitions_RegisterDefinitionId",
                        column: x => x.RegisterDefinitionId,
                        principalTable: "RegisterDefinitions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "RegisterEnumValues",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    RegisterFieldId = table.Column<Guid>(type: "TEXT", nullable: true),
                    RegisterDefinitionId = table.Column<Guid>(type: "TEXT", nullable: true),
                    Name = table.Column<string>(type: "TEXT", maxLength: 128, nullable: false),
                    Value = table.Column<long>(type: "INTEGER", nullable: true),
                    Description = table.Column<string>(type: "TEXT", maxLength: 2000, nullable: true),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    DefinitionLine = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_RegisterEnumValues", x => x.Id);
                    table.ForeignKey(
                        name: "FK_RegisterEnumValues_RegisterDefinitions_RegisterDefinitionId",
                        column: x => x.RegisterDefinitionId,
                        principalTable: "RegisterDefinitions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_RegisterEnumValues_RegisterFields_RegisterFieldId",
                        column: x => x.RegisterFieldId,
                        principalTable: "RegisterFields",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "RegisterMacroReferences",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "TEXT", nullable: false),
                    SdkProjectId = table.Column<Guid>(type: "TEXT", nullable: false),
                    RegisterDefinitionId = table.Column<Guid>(type: "TEXT", nullable: true),
                    RegisterFieldId = table.Column<Guid>(type: "TEXT", nullable: true),
                    MacroName = table.Column<string>(type: "TEXT", maxLength: 256, nullable: false),
                    MacroKind = table.Column<string>(type: "TEXT", maxLength: 16, nullable: false),
                    Expansion = table.Column<string>(type: "TEXT", maxLength: 512, nullable: true),
                    DefinitionFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    DefinitionLine = table.Column<int>(type: "INTEGER", nullable: true),
                    ReferenceFile = table.Column<string>(type: "TEXT", maxLength: 1000, nullable: true),
                    ReferenceLine = table.Column<int>(type: "INTEGER", nullable: true),
                    Resolved = table.Column<bool>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_RegisterMacroReferences", x => x.Id);
                    table.ForeignKey(
                        name: "FK_RegisterMacroReferences_RegisterDefinitions_RegisterDefinitionId",
                        column: x => x.RegisterDefinitionId,
                        principalTable: "RegisterDefinitions",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_RegisterMacroReferences_RegisterFields_RegisterFieldId",
                        column: x => x.RegisterFieldId,
                        principalTable: "RegisterFields",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.SetNull);
                    table.ForeignKey(
                        name: "FK_RegisterMacroReferences_SdkProjects_SdkProjectId",
                        column: x => x.SdkProjectId,
                        principalTable: "SdkProjects",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_PeripheralInstances_ChipId",
                table: "PeripheralInstances",
                column: "ChipId");

            migrationBuilder.CreateIndex(
                name: "IX_PeripheralInstances_Name",
                table: "PeripheralInstances",
                column: "Name");

            migrationBuilder.CreateIndex(
                name: "IX_PeripheralInstances_PeripheralId",
                table: "PeripheralInstances",
                column: "PeripheralId");

            migrationBuilder.CreateIndex(
                name: "IX_PeripheralInstances_SdkProjectId_NaturalKey",
                table: "PeripheralInstances",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_RegisterDefinitions_ChipId",
                table: "RegisterDefinitions",
                column: "ChipId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterDefinitions_PeripheralId",
                table: "RegisterDefinitions",
                column: "PeripheralId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterDefinitions_PeripheralInstanceId",
                table: "RegisterDefinitions",
                column: "PeripheralInstanceId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterDefinitions_SdkProjectId_NaturalKey",
                table: "RegisterDefinitions",
                columns: new[] { "SdkProjectId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_RegisterDefinitions_StructName_MemberName",
                table: "RegisterDefinitions",
                columns: new[] { "StructName", "MemberName" });

            migrationBuilder.CreateIndex(
                name: "IX_RegisterEnumValues_RegisterDefinitionId",
                table: "RegisterEnumValues",
                column: "RegisterDefinitionId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterEnumValues_RegisterFieldId",
                table: "RegisterEnumValues",
                column: "RegisterFieldId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterFields_RegisterDefinitionId_NaturalKey",
                table: "RegisterFields",
                columns: new[] { "RegisterDefinitionId", "NaturalKey" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_RegisterMacroReferences_RegisterDefinitionId",
                table: "RegisterMacroReferences",
                column: "RegisterDefinitionId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterMacroReferences_RegisterFieldId",
                table: "RegisterMacroReferences",
                column: "RegisterFieldId");

            migrationBuilder.CreateIndex(
                name: "IX_RegisterMacroReferences_SdkProjectId_MacroName",
                table: "RegisterMacroReferences",
                columns: new[] { "SdkProjectId", "MacroName" });

            migrationBuilder.CreateIndex(
                name: "IX_RegisterParseDiagnostics_SdkProjectId",
                table: "RegisterParseDiagnostics",
                column: "SdkProjectId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "RegisterEnumValues");

            migrationBuilder.DropTable(
                name: "RegisterMacroReferences");

            migrationBuilder.DropTable(
                name: "RegisterParseDiagnostics");

            migrationBuilder.DropTable(
                name: "RegisterFields");

            migrationBuilder.DropTable(
                name: "RegisterDefinitions");

            migrationBuilder.DropTable(
                name: "PeripheralInstances");
        }
    }
}
