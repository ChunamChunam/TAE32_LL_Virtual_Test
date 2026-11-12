# 第五阶段验证清单

**执行日期：2026-11-12**

## 自动化测试

```powershell
dotnet test tests\TAE32.LLVirtualTest.Tests\TAE32.LLVirtualTest.Tests.csproj --filter VirtualMcu
```

期望：18 通过 / 0 失败。

覆盖：

- [x] 寄存器读写
- [x] 位掩码（Set/Clear/Modify）
- [x] 位域修改
- [x] 复位值
- [x] 写 1 清零
- [x] 写 0 清零
- [x] 只读保护
- [x] 多实例隔离
- [x] 快照恢复
- [x] 访问追踪过滤
- [x] 地址越界 / 宽度不匹配
- [x] 保留位（WritableMask）保护

## 手工 UI 抽查

1. 启动应用 →「虚拟 MCU」
2. 选择 TAE32G58xx →「创建并初始化」（需已解析寄存器）
3. 选择 GPIOA，写 ODR，确认当前值与追踪更新
4. 写 IDR（若为 Ro）应拒绝
5. 快照 → 改值 → 恢复，值回到快照
6. 再创建第二个 MCU，确认互不影响
7. 确认「寄存器管理」数据库定义未被改写

## 明确未验证 / 未交付

- 完整 UART/ADC/TMR/DMA 硬件行为
- LL 函数自动驱动虚拟寄存器（自动化测试引擎）
- 真实引脚 / 中断 / DMA 传输时序
