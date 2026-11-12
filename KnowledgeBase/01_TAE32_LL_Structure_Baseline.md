# TAE32 LL 结构基线（人工确认版）

> **状态：已人工确认（2026-11-12）**  
> **效力：后续所有阶段必须以本文与对应 ScanResults 为准，禁止臆造芯片/外设/函数/寄存器数据。**

## 权威来源

| 项 | 路径 |
|---|---|
| SDK / LL 根目录 | `SDKContent/Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0/LL` |
| 扫描报告目录 | `ScanResults/` |
| 可复现扫描脚本 | `tools/phase1_ll_scan.py` |
| 机器可读基线 | `KnowledgeBase/01_TAE32_LL_Structure_Baseline.json` |

详细证据与全量函数列表以 `ScanResults/03_*.json`～`05_*.json` 为准；本文是经确认后的结构清单摘要。

## 目录结构（已确认）

```text
Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0/
└── LL/          # 扁平；25 个 .h；0 个 .c；无按芯片分子目录
```

| 指标 | 数量 |
|---|---:|
| 总目录 | 2 |
| 总文件 | 25 |
| C | 0 |
| H | 25 |
| 其他 | 0 |

## 芯片（已确认）

| 芯片型号 | 级别 | 说明 |
|---|---|---|
| **TAE32G58xx** | 系列级 | 当前 LL 包内唯一芯片系列标识；无更细订货型号宏 |

- 不根据 SDK 包名另行推断其它芯片。
- 设备头 `tae32g58xx.h`、配置头 `tae32g58xx_ll_conf.h` 不在本 LL 目录（外部依赖）。

## 公共 / 非外设文件（已确认）

| 文件 | 角色 |
|---|---|
| `tae32g58xx_ll.h` | 聚合包含 |
| `tae32g58xx_ll_def.h` | 公共定义（DEFINE），**不计入外设** |

## 外设模块清单（已确认，共 23）

**统计口径（已确认）：** `LL函数数量` = 头文件中的 `__STATIC_INLINE` / `static inline` / `inline` **定义**数量。  
不把 `IS_LL_*` 等函数宏默认计入该主计数（宏另见全量扫描 JSON）。

| 序号 | 外设 | 源文件 | inline 函数数 | 实例宏 | TypeDef |
|---:|---|---|---:|---|---|
| 1 | ADC | `tae32g58xx_ll_adc.h` | 213 | ADC0–ADC3 | `ADC_TypeDef`, `ADC_DMA_TypeDef` |
| 2 | ADTMR | `tae32g58xx_ll_adtmr.h` | 211 | TMR9, TMR10 | `ADTMR_TypeDef` |
| 3 | BSTMR | `tae32g58xx_ll_bstmr.h` | 43 | TMR7, TMR8 | `BSTMR_TypeDef` |
| 4 | CAN | `tae32g58xx_ll_can.h` | 401 | CAN0, CAN1 | `CAN_TypeDef` |
| 5 | CMP | `tae32g58xx_ll_cmp.h` | 40 | CMP0–CMP8 | `CMP_TypeDef` |
| 6 | CORTEX | `tae32g58xx_ll_cortex.h` | 8 | — | —（API：`LL_NVIC_*` / `LL_Init*` / `LL_Delay_*`） |
| 7 | DAC | `tae32g58xx_ll_dac.h` | 48 | DAC0–DAC8 | `DAC_TypeDef` |
| 8 | DMA | `tae32g58xx_ll_dma.h` | 52 | DMA | `DMA_TypeDef` |
| 9 | EFLASH | `tae32g58xx_ll_eflash.h` | 99 | EFLASH | `EFLASH_TypeDef` |
| 10 | GPIO | `tae32g58xx_ll_gpio.h` | 35 | GPIOA–GPIOF | `GPIO_TypeDef` |
| 11 | GPTMRX | `tae32g58xx_ll_gptmrx.h` | 152 | TMR0–TMR2 | `GPTMRx_TypeDef` |
| 12 | GPTMRY | `tae32g58xx_ll_gptmry.h` | 165 | TMR3, TMR4 | `GPTMRy_TypeDef` |
| 13 | HRPWM | `tae32g58xx_ll_hrpwm.h` | 695 | HRPWM | `HRPWM_TypeDef` |
| 14 | I2C | `tae32g58xx_ll_i2c.h` | 232 | I2C0–I2C2 | `I2C_TypeDef` |
| 15 | IIR | `tae32g58xx_ll_iir.h` | 42 | IIR0–IIR5 | `IIR_TypeDef`, `IIR_Coef_TypeDef` |
| 16 | IWDG | `tae32g58xx_ll_iwdg.h` | 19 | IWDG | `IWDG_TypeDef` |
| 17 | LPTMR | `tae32g58xx_ll_lptmr.h` | 70 | TMR6 | `LPTMR_TypeDef` |
| 18 | QEI | `tae32g58xx_ll_qei.h` | 106 | QEI0–QEI2 | `QEI_TypeDef` |
| 19 | RCU | `tae32g58xx_ll_rcu.h` | 503 | RCU | `RCU_TypeDef` |
| 20 | SPI | `tae32g58xx_ll_spi.h` | 155 | SPI0, SPI1 | `SPI_TypeDef` |
| 21 | SYSCTRL | `tae32g58xx_ll_sysctrl.h` | 188 | SYSCTRL | `SYSCTRL_TypeDef` |
| 22 | UART | `tae32g58xx_ll_uart.h` | 137 | UART0–UART4 | `UART_TypeDef` |
| 23 | WWDG | `tae32g58xx_ll_wwdg.h` | 14 | WWDG | `WWDG_TypeDef` |

**合计 inline 定义：3628**

## 模块 ↔ 实例映射（已确认）

| 模块 | 实例 |
|---|---|
| GPTMRX | TMR0, TMR1, TMR2 |
| GPTMRY | TMR3, TMR4 |
| LPTMR | TMR6 |
| BSTMR | TMR7, TMR8 |
| ADTMR | TMR9, TMR10 |

以上 5 个定时器相关模块视为**彼此独立**的外设模块（不是同一模块的别名）。

## 关键约定（后续必须遵守）

1. **区分模块与实例**：例如模块 `UART` vs 实例 `UART0`；模块 `LPTMR` vs 实例 `TMR6`。
2. **禁止硬编码臆造外设列表**；若结构变更，须重新扫描并更新本基线与 ScanResults。
3. **禁止修改原始 SDK**（不删、不改名、不格式化）。
4. **当前阶段后续开发**仍以 C# / WPF / MVVM 为目标架构；Python 仅作辅助扫描。
5. **未提供完整 DFP 其它目录前**：寄存器基地址等以设备头为准的内容不得虚构；可标注外部依赖缺失。
6. **进入 Clang AST / 虚拟寄存器等后续阶段前**：仍以本基线外设与文件映射为准。

## 相关扫描产物

- `ScanResults/01_DirectoryTree.txt`
- `ScanResults/02_FileStatistics.json`
- `ScanResults/03_ChipDiscovery.json`
- `ScanResults/04_PeripheralDiscovery.json`
- `ScanResults/05_LLFunctionDiscovery.json`
- `ScanResults/06_Unclassified.json`
- `ScanResults/07_ScanSummary.md`
- `ScanResults/08_HumanConfirmation.json`
