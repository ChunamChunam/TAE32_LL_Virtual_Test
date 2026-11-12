# 第四阶段交付说明：SDK 寄存器定义解析引擎

**状态：已实现（Phase 4）。不实现虚拟寄存器运行时 / 虚拟 MCU。**

> **2026-11-12 更新**：完整 DFP 已放入 `SDKContent/...`。探测器可找到  
> `SDK/Drivers/TAE32G58xx_Device/Inc/tae32g58xx.h` + `tae32g58xx_chip.h`、`SVD/TAE32G58xx.svd`、  
> `SDK/Drivers/TAE32G58xx_Driver/LL`。请在 UI 重新「解析寄存器」以写入 Confirmed 偏移/地址与 `__IOM` 访问属性。

## 架构

```text
TAE32.LLVirtualTest.SDK/Register/
├── RegisterEnvironmentProbe      — 在 SdkRoot 及父目录探测 tae32g58xx.h / *reg*.h（区分 Parse Bridge 桩）
├── RegisterLlEvidenceScanner     — 扫描 tae32g58xx_ll_*.h（排除 ll.h / ll_def.h）
├── RegisterDeviceHeaderParser    — 权威设备头存在时的 typedef / #define 解析（偏移仍须 offsetof 确认）
├── RegisterParseBridgeFallback   — 无设备头时的 LL 证据路径（当前 DFP 默认路径）
└── RegisterParseService          — IRegisterParser 实现，按项目清空并写入寄存器表

Core/Entities: PeripheralInstance, RegisterDefinition, RegisterField,
               RegisterEnumValue, RegisterMacroReference, RegisterParseDiagnostic

Infrastructure: AppDbContext + 迁移 Phase4_RegisterParse（自 SdkProject 级联）

App: RegisterManagementPage + RegisterManagementViewModel（「解析寄存器」）
```

## 硬约束落实

| 约束 | 实现 |
|---|---|
| 不臆造芯片/外设/寄存器 | 实例/成员/宏均来自真实 LL 头文本或权威设备头（若存在） |
| 不修改 SDKContent | 只读扫描 |
| 无权威 `tae32g58xx.h` | 偏移/绝对地址一律 `PendingConfirmation`；显著 `MissingSdkHeader` 诊断 |
| 访问属性 / 复位值 | 默认 `Unknown` / null，仅设备头有明确文本时才填充 |
| Phase 1–3 表保留 | 仅新增寄存器相关表；解析前 `ExecuteDelete` 仅作用 Phase 4 表 |

## 接口

- `IRegisterParser.ParseAsync` → `RegisterParseSummary`
- `IAppDataService`: 实例/寄存器列表、`GetRegisterDetailAsync`、项目级寄存器诊断

## DI

- `AddSdkServices`: `IRegisterParser` → `RegisterParseService`
- 已移除 Infrastructure 中 `NotImplementedRegisterParser`

## 使用

1. 导入扫描 JSON（与 Phase 2 相同）
2. 打开「寄存器管理」→「解析寄存器」
3. 筛选芯片/外设/实例，查看列表与详情（字段、宏、诊断）

## 测试

`tests/TAE32.LLVirtualTest.Tests/Register/RegisterParseTests.cs`

- 无设备头：实例/寄存器来自 LL 证据，`MissingSdkHeader`，无 `Confirmed` 偏移
- `GPIOA_BSR_BSn_Pos` 等宏引用入库且 `Resolved=false`
