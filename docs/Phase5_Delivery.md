# 第五阶段交付说明：虚拟 MCU 与寄存器模拟环境

**状态：已实现（Phase 5）。等待人工确认。不自动进入完整 LL 自动化测试 / 全外设模拟。**

## 目标落实

| 目标 | 实现 |
|---|---|
| 虚拟寄存器空间 | 自 Phase 4 `RegisterDefinition` / `RegisterField` 载入内存槽位 |
| 读写 / 置位 / 清位 / 位域 / 复位 | `IVirtualMcuService` |
| 访问语义 | Rw / Ro / Wo / W1c / W0c / Rc / Reserved；Unknown 可配置默认 |
| 虚拟外设 | 可扩展 `IVirtualPeripheral`；优先 GPIO-Basic、RCU-Basic；其余 Passthrough |
| 访问追踪 | 序号、地址、寄存器、类型、前后值、LL 函数、源位置、结果；可过滤 |
| 实例隔离 | Create / Initialize / Reset / Snapshot / Restore / Destroy |
| WPF | 导航「虚拟 MCU」页；UI 读写只走服务，不改数据库定义 |
| 不连真实硬件 | 无 J-Link / DAP-Link / 板级依赖 |

## 架构

```text
Core/
  Interfaces/IVirtualMcuService.cs, IVirtualPeripheral.cs
  Models/VirtualMcuModels.cs
  Enums/VirtualMcuEnums.cs

Infrastructure/VirtualMcu/
  VirtualMcuService            — 多实例管理
  VirtualMcuRuntime            — 单 MCU 运行时
  VirtualRegisterSpace         — 名称/地址映射
  RegisterSemanticsEngine      — 访问语义
  AccessTraceStore             — 追踪
  VirtualMcuDefinitionLoader   — 从 SQLite 只读载入 Phase 4 定义
  Peripherals/
    GpioPeripheralSimulator    — ODR/BSR/BRR 影子 + IDR 回环（标明限制）
    RcuPeripheralSimulator     — 跟踪 *EN*/*CLK* 写（无时钟树）
    PassthroughPeripheral      — 仅存储

App/
  VirtualMcuPage + VirtualMcuViewModel
```

## 已实现 vs 未模拟（必须区分）

### 已实现

- 8/16/32 位寄存器读写与宽度校验
- 位设置 / 清除 / 修改 / 位域写
- 只读拒绝写、只写拒绝读、保留拒绝访问
- 写 1 清零、写 0 清零、读清零（当 SDK `AccessAttribute` 已声明为 W1c/W0c/Rc）
- 未映射位可按配置当作保留保护
- 地址未映射 → `AddressOutOfRange`
- 多虚拟 MCU 状态隔离、快照恢复、访问追踪过滤
- GPIO / RCU 基础侧效应钩子

### 暂未模拟（Limitation 标记）

| 限制 | 说明 |
|---|---|
| `UnknownAccessDefaultedToRw` | SDK 访问属性 Unknown 时默认 Rw（可关） |
| `MissingResetValueAssumedZero` | 无复位值文本时按 0 |
| `MissingAbsoluteAddress` | 无地址时仅按名称访问 |
| `PeripheralBehaviorNotModeled` | UART/ADC/TMR/DMA 等仅 Passthrough |
| GPIO IDR 回环 | 非真实引脚输入 |
| RCU 无频率/复位树 | 仅记录使能类寄存器写 |
| 不执行完整 LL 自动化测试 | 留待后续阶段 |

## 使用

1. 确保已完成 Phase 4「解析寄存器」
2. 打开「虚拟 MCU」→ 选择芯片 →「创建并初始化」
3. 在外设树中选择实例，查看/手动读写寄存器
4. 底部查看访问追踪；可用快照/恢复/复位/销毁

## 测试

`tests/.../VirtualMcu/VirtualMcuRuntimeTests.cs`（18 项）：语义、位操作、复位、W1C/W0C、只读保护、越界、多实例隔离、快照、追踪、服务层隔离。

## DI

`IVirtualMcuService` → `VirtualMcuService`（已替换 `NotImplementedVirtualMcuService`）。
