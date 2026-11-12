# 第六阶段交付说明：LL 函数自动化测试引擎

**状态：已实现（Phase 6）。等待人工确认。不自动进入全外设深度模拟 / 完整回归产品化。**

## 目标落实

| 目标 | 实现 |
|---|---|
| 编译真实 SDK LL | Clang/LLVM：`ICompilerService` / `ClangCompilerService`；支持「获取内置 Clang」静默安装到 LocalAppData |
| Harness 调用真实函数 | `TestHarnessGenerator` `#include` 真实 LL 头，调用真实 inline |
| 虚拟硬件接入 | 外设映像为宿主 RAM；执行后同步回独立虚拟 MCU |
| 测试用例 CRUD/导入导出 | `ILlTestCaseStore` + SQLite `LlTestCases` / `LlTestRuns` |
| 自动生成（可编辑） | `LlTestCaseGenerator`（基于真实签名/宏候选，GPIO/RCU 优先） |
| 断言系统 | 返回值 / 寄存器 / 位域 / 访问顺序 / 函数上下文 / 异常 / 超时；含 `RuleSource` |
| 执行管理 | 单例/批量、取消、超时、每用例独立 MCU、日志与失败定位 |
| WPF | 「自动化测试」页：芯片/外设/函数/用例/参数 JSON/执行/日志/结果 |
| 不连真实硬件 | 拒绝裸 MCU 绝对地址访问宿主；无 Clang 时 Skipped/Error |

## 架构

```text
Core/
  Interfaces/ICompilerService, ILlTestCaseStore, ILLTestEngine
  Models/LlTestModels.cs · Enums/LlTestEnums.cs · Entities/LlTestEntities.cs

Infrastructure/TestEngine/
  ClangCompilerService     — 路径/宏/头文件/编译/错误解析/日志
  TestHarnessGenerator     — 真实 LL include + tae32_run
  NativeTestHost           — 加载 DLL，RAM peri，回写虚拟 MCU
  AssertionEvaluator       — 断言求值
  LlTestCaseStore          — 用例/运行持久化
  LlTestCaseGenerator      — 从解析签名辅助生成
  LlTestEngine             — 编排：检查→编译→执行→断言→记录

App/
  AutomationTestPage + AutomationTestViewModel
```

## 执行阶段区分（必须）

每次运行结果拆分记录：

1. **编译通过** — `CompileSucceeded`
2. **函数执行完成** — `ExecuteCompleted`（宿主 RAM + 虚拟 MCU，非真实板级）
3. **断言通过** — `AssertionsPassed`
4. **硬件行为已模拟** — `HardwareBehaviorSimulated`（虚拟外设侧效应，**不是**真实硬件验证）

状态：`Passed` / `Failed` / `Error` / `Skipped` / `Timeout`（另有 `Cancelled` / `Compiling` / `Running` 过程态）。

## 安全约束

- 被测对象必须是 SDK 原始 LL（通过头文件 include），禁止用自写模拟函数冒充。
- 寄存器访问走虚拟 MCU / 宿主 peri RAM，不得把 `0x4000_0000` 等 MCU 地址当宿主指针解引用。
- 无法安全物化的复杂指针参数：编译或运行阶段明确拒绝（harness `return -2` / Error）。
- 未配置 Clang：环境检查失败 → **Skipped**（可配置），不假装通过。

## 使用

1. 完成 Phase 4 寄存器解析 + Phase 5 虚拟 MCU 可用
2. 打开「自动化测试」→「获取内置 Clang」（首次联网下载 LLVM 18.1.8 到 LocalAppData）或手动配置路径 →「检查编译环境」
3. 选择外设 / LL 函数 →「根据真实签名生成用例」→ 人工编辑 JSON → 保存
4. 「运行选中」或「批量 Ready」；查看实时日志与结果详情中的四项阶段标志

## 测试

`tests/.../TestEngine/LlTestEngineTests.cs`：harness 生成、字面量解析、断言、用例导入导出。

## DI

- `ICompilerService` → `ClangCompilerService`
- `ILlTestCaseStore` → `LlTestCaseStore`
- `ILLTestEngine` → `LlTestEngine`
- Migration：`Phase6_LlTestEngine`

## 明确未做 / 限制

| 限制 | 说明 |
|---|---|
| 无 Clang / 下载失败 | 只能到 Skipped/Error；可用「获取内置 Clang」自动安装到 `%LocalAppData%\TAE32.LLVirtualTest\toolchain\llvm` |
| UART/ADC/TMR 等 | 生成与断言覆盖弱于 GPIO/RCU；外设多为 Passthrough |
| 符号宏未预解析 | 部分参数表达式依赖生成器已解析的字面量/候选 |
| 非真实硬件结论 | UI/报告必须标注「虚拟环境结果」 |
