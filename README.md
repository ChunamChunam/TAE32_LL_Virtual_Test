# TAE32 LL Virtual Test

嵌入式 LL 驱动虚拟测试与分析工具（C# / WPF / MVVM）。

## 阶段状态

| 阶段 | 状态 |
|---|---|
| 第一阶段：真实 LL SDK 扫描 | 已完成并人工确认 → 见 `KnowledgeBase/` |
| 第二阶段：WPF 基础框架 | 已完成 → 见 `docs/Phase2_Delivery.md` |
| 第三阶段：LL 函数深度解析（Clang AST） | 已完成 → 见 `docs/Phase3_Delivery.md` |
| 第四阶段：寄存器定义解析 | 已完成 → 见 `docs/Phase4_Delivery.md` |
| 第五阶段：虚拟 MCU / 寄存器模拟 | 已完成 → 见 `docs/Phase5_Delivery.md` |
| 第六阶段：LL 自动化测试引擎 | 已完成 → 见 `docs/Phase6_Delivery.md` |
| 第七阶段：测试管理与报告 | 已完成，等待人工确认 → 见 `docs/Phase7_Delivery.md` |

## 快速开始

```powershell
dotnet build TAE32.LLVirtualTest.sln
dotnet test tests\TAE32.LLVirtualTest.Tests
dotnet run --project src\TAE32.LLVirtualTest.App
```

启动后：SDK 管理 → 导入扫描；LL 函数库 → 深度解析；寄存器管理 → 解析寄存器；虚拟 MCU → 创建并初始化；**自动化测试** →「获取内置 Clang」→ 生成/运行用例；**测试管理** → 计划/套件/批量/统计/失败分析/导出报告（结果为虚拟环境，非真实硬件）。系统设置支持数据库备份/恢复与日志清理。

## 目录

- `SDKContent/` — 原始 SDK（只读）
- `ScanResults/` — 第一阶段扫描报告
- `KnowledgeBase/` — 已确认结构基线
- `src/` — 应用源码
- `tests/` — 测试
- `data/` — SQLite 与日志（运行后生成）
- `docs/` — 各阶段交付与验收
