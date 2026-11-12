# 第七阶段交付说明：测试管理与报告系统

**状态：已实现（Phase 7）。等待人工确认。**

## 目标落实

| 目标 | 实现 |
|---|---|
| 测试计划 | `ITestPlanStore`：创建/编辑/复制/归档；维度含 SDK 版本、芯片、外设、函数过滤、测试类型 |
| 测试套件 | `ITestSuiteStore`：关联真实 `LlTestCase` Id，禁止空壳用例 |
| 批量执行 | `ITestBatchService`：按外设/芯片/套件/计划/失败重试；可取消；进度回调；每用例走独立虚拟 MCU（引擎隔离） |
| 统计 | `ITestAnalyticsService.GetStatisticsAsync`：总数/执行/通过/失败/错误/跳过/超时/通过率/编译失败率/平均耗时 |
| 覆盖率 | 明确分母口径；无真实数据时百分比为 `null`，不伪造 |
| 失败分析 | 关联用例、函数、源码路径、编译摘录、断言 JSON、寄存器轨迹 |
| 历史 | `TestBatchRun` 持久化时间、SDK/工具/编译器版本、计划/套件、结果计数、日志目录 |
| 报告 | HTML / CSV(Excel) / 可打印 PDF-HTML；含免责声明「虚拟 MCU ≠ 真实硬件」 |
| WPF | 「测试管理」页：计划/套件/历史/统计/失败/报告 |
| 系统完善 | 设置页：备份/恢复 DB、清理旧日志、诊断摘要 |

## 架构

```text
Core/
  Entities/TestManagementEntities.cs
  Models/TestManagementModels.cs
  Interfaces/ITestManagementServices.cs · ITestReportService.cs

Infrastructure/TestManagement/
  TestPlanStore · TestSuiteStore · TestBatchService
  TestAnalyticsService · TestReportService · SystemMaintenanceService

App/
  TestManagementPage + TestManagementViewModel
  SettingsPage 备份/恢复/日志清理
```

## 覆盖率口径（必须）

| 指标 | 分子 | 分母 | 无数据时 |
|---|---|---|---|
| LL 函数覆盖率 | 有用例绑定的函数数 | Form 含 inline 的 LL 函数 | null |
| 外设覆盖率 | 用例涉及的外设名去重 | Peripherals 表 | null |
| 寄存器访问覆盖率 | 运行轨迹中寄存器名（抽样≤200 次运行） | 解析得到的 RegisterPath 去重 | null |
| 位域覆盖率 | 用例中 BitField 断言条数 | RegisterFields 总数 | null |
| 用例覆盖率 | 至少执行过一次的用例 | LlTestCases 总数 | null |

## 报告内容

1. 基本信息与标题  
2. SDK 版本  
3. 芯片/范围（批次 Scope）  
4. 测试范围说明  
5. 用例总数与执行统计  
6. 通过率  
7. 失败清单  
8. 编译错误摘录  
9. 断言失败信息  
10. 关键寄存器访问（失败分析关联）  
11. 工具/编译器版本等环境信息  
12. 测试结论 + **虚拟 MCU 免责声明**

PDF：导出为 `.pdf.html`，浏览器打开后「打印为 PDF」。

## DI / Migration

- `ITestPlanStore` → `TestPlanStore`
- `ITestSuiteStore` → `TestSuiteStore`
- `ITestBatchService` → `TestBatchService`
- `ITestAnalyticsService` → `TestAnalyticsService`
- `ITestReportService` → `TestReportService`
- `ISystemMaintenanceService` → `SystemMaintenanceService`
- Migration：`Phase7_TestManagement`

## 测试

`tests/.../TestManagement/TestManagementTests.cs`：计划/套件 CRUD、空数据覆盖率、报告免责声明、备份与日志清理。

## 明确限制

| 限制 | 说明 |
|---|---|
| Excel | 当前为 UTF-8 CSV（可用 Excel 打开），非 XLSX |
| PDF | 可打印 HTML，非原生 PDF 引擎 |
| 批量上限 | 单次解析范围最多 500 用例 |
| 寄存器覆盖 | 轨迹抽样与名称匹配，非指令级精确覆盖 |
| Phase 6 门禁 | 全外设深度模拟 / 完整产品化回归仍需人工确认后推进 |
