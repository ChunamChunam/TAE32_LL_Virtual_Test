# 第四阶段验证说明（仅 LL / 源码证据）

**未使用数据手册。无权威 `tae32g58xx.h` 时不得将硬件地址/位宽标为 Confirmed。**

## 环境

- SDK LL 根：`SDKContent/Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0/LL`
- 设备头：仓库内 DFP 包 **未提供** 权威 `tae32g58xx.h`（与 Phase 1 基线 `missing_external_headers` 一致）
- 验证命令：`dotnet test tests/TAE32.LLVirtualTest.Tests --filter RegisterParseTests`

## 解析路径（当前默认）

1. `RegisterEnvironmentProbe`：`HasAuthoritativeDeviceHeader = false`
2. `RegisterLlEvidenceScanner` 全量 LL 头
3. `RegisterParseBridgeFallback` 写入 DB

## 模块抽样（源码证据，非硅片验证）

| 模块 | LL 头 | 预期证据类型 |
|---|---|---|
| GPIO | `tae32g58xx_ll_gpio.h` | 实例 GPIOA…、`->ODR`/`->BSR`、宏如 `GPIOA_BSR_BSn_Pos` |
| UART | `tae32g58xx_ll_uart.h` | UART0–4 实例与成员访问（非 USART 文件名） |
| RCU | `tae32g58xx_ll_rcu.h` | RCU 寄存器成员与时钟门控相关宏引用 |
| ADC | `tae32g58xx_ll_adc.h` | ADC0–3 实例与数据/控制寄存器成员名 |
| TMR | `ll_gptmrx/y`, `lptmr`, `bstmr`, `adtmr` | TMR0–10 与基线定时器映射 |
| DMA | `tae32g58xx_ll_dma.h` | 通道/控制成员与 `*_Pos`/`*_Msk` 引用 |

运行一次解析后，在 SQLite 中可按 `Peripheral.Name` 与 `RegisterDefinitions.StructName` 过滤核对。

## 计数（一次真实解析后填入/核对）

在测试或 UI 解析完成后，典型数量级（随 LL 扫描完整性变化）：

| 指标 | 说明 |
|---:|---|
| PeripheralInstances | LL 中 `#if defined(...)` 去重实例 |
| RegisterDefinitions | 按 `StructName|MemberName` 去重的 `->MEMBER` 证据 |
| RegisterFields | 由宏启发式关联的字段占位 |
| RegisterMacroReferences | `*_Pos`/`*_Msk`/`*_Shift`/`*_BIT` 引用（多未 Resolved） |
| RegisterParseDiagnostics | 含 `MissingSdkHeader`、`PendingConfirmation` |

一次全量 LL 扫描证据（与 `RegisterLlEvidenceScanner` 同口径，2026-11-12）：

| 指标 | 数量 |
|---:|---:|
| 去重外设实例 (`#if defined`) | 66 |
| 去重寄存器成员 (`->MEMBER`) | 182 |
| 去重宏引用 (`*_Pos`/`*_Msk`/…) | 2787 |

解析入库后 `RegisterFields` 数量取决于宏→寄存器启发式关联，通常小于宏引用总数。

## 已知阻塞 / 后续

| 项 | 说明 |
|---|---|
| 权威设备头缺失 | 无法确认偏移、绝对地址、位域 Pos/Msk 数值 |
| Clang offsetof | 设备头到位后应用 `RegisterDeviceHeaderParser` + Clang TU，方可将 `OffsetStatus` 升为 Confirmed |
| Parse Bridge | Phase 3 桥接头 **不** 用于寄存器权威数据 |
| 虚拟 MCU | 本阶段 **未** 实现 |
