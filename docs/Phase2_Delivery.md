# 第二阶段交付说明：WPF 桌面应用基础框架

**状态：已完成，等待人工确认。不得自动进入第三阶段。**

## 解决方案

- 解决方案：`TAE32.LLVirtualTest.sln`
- 技术栈：.NET 8、WPF、CommunityToolkit.Mvvm、MS.DI、EF Core + SQLite、Serilog

| 项目 | 职责 |
|---|---|
| `TAE32.LLVirtualTest.App` | WPF 界面 / ViewModel |
| `TAE32.LLVirtualTest.Core` | 实体、枚举、接口 |
| `TAE32.LLVirtualTest.Infrastructure` | EF Core、Repository/服务、Serilog |
| `TAE32.LLVirtualTest.SDK` | 扫描 JSON 导入 |
| `TAE32.LLVirtualTest.Tests` | 真实 ScanResults 集成测试 |

## 运行方式

```powershell
cd D:\Code\12_TAE32_LL_Virtual_Test
dotnet run --project src\TAE32.LLVirtualTest.App\TAE32.LLVirtualTest.App.csproj
```

数据库：`data/tae32_ll_virtual_test.db`  
日志：`data/logs/app-*.log`

启动后会自动：

1. 执行 EF 迁移
2. 若无项目则添加默认 SDK 项目（指向 `SDKContent/...` 与 `ScanResults/`）
3. 打开主窗口（左侧导航 + 顶部工具栏 + 工作区 + 状态栏）

**首次使用请到「SDK 管理」选择项目并点击「导入扫描 JSON」。**

## 主界面导航

1. 工作台  
2. SDK 管理（添加/查看/移除；移除不删原始 SDK）  
3. 芯片管理  
4. 外设管理  
5. LL 函数库（含详情区；未解析项显示「尚未解析」）  
6. 函数调用关系（占位）  
7. 寄存器管理（占位）  
8. 自动化测试（占位）  
9. 测试报告（占位）  
10. 系统设置  

## 数据导入

读取真实文件：

- `ScanResults/03_ChipDiscovery.json`
- `ScanResults/04_PeripheralDiscovery.json`
- `ScanResults/05_LLFunctionDiscovery.json`

函数唯一键：`FilePath|StartLine|FunctionName|Form`（**不以函数名单独唯一**）。支持重复导入 upsert。

期望导入结果（与第一阶段基线一致）：

| 项 | 数量 |
|---|---:|
| 芯片 | 1（TAE32G58xx） |
| 外设 | 23 |
| 函数全形式 | 6879 |
| inline 定义 | 3628 |

## 预留扩展接口（未实现业务）

- `ILLFunctionParser`
- `IRegisterParser`
- `IVirtualMcuService`
- `ILLTestEngine`
- `ITestReportService`

## 测试结果（真实数据）

```text
dotnet test tests\TAE32.LLVirtualTest.Tests
测试总数: 3
通过数: 3
```

覆盖：真实 JSON 导入、SQLite 持久化、芯片/外设/函数计数、搜索、重复导入、移除项目不删 SDK 文件、NaturalKey 设计。

## 运行截图

请本地启动应用后自行截取主窗口 / SDK 导入 / 外设与函数库页面。  
本阶段自动化环境未强制生成 GUI 截图文件。

## 未完成 / 不做事项（有意为之）

- Clang AST 深度解析  
- 虚拟寄存器 / MCU 仿真  
- 调用关系图真实分析  
- 自动化测试引擎与报告生成  
- 大量源码正文入库（按设计不入库）  

## 确认清单（请人工确认）

- [ ] 解决方案可编译、应用可启动  
- [ ] 导航 10 项可用  
- [ ] SDK 添加/导入/移除行为符合预期  
- [ ] 导入后芯片=1、外设=23、函数=6879 / inline=3628  
- [ ] 函数详情未解析字段显示「尚未解析」  
- [ ] 可进入下一阶段前需你明确指令  
