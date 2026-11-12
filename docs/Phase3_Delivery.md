# 第三阶段交付说明：Clang AST LL 深度解析

**状态：已实现，等待人工确认**

## 架构概览

```
ILLFunctionParser (Core)
    └── LlFunctionParseService (SDK/Parse)
            ├── ClangEnvironment — include 路径、缺失头检测、libclang 版本
            ├── ParseBridgeBuilder — 生成 Parse Bridge（非权威设备环境）
            ├── ClangAstSession — CXTranslationUnit + 包装 .c
            ├── LlFunctionAstExtractor — FunctionDecl 定义体
            ├── LlOperationAnalyzer / LlRegisterAccessAnalyzer / LlCallGraphAnalyzer / LlMacroReferenceCollector
            └── EF 持久化（LlFunction 扩展字段 + 子表）
```

- **NaturalKey** 不变：`FilePath|StartLine|FunctionName|Form`
- 仅提取 **定义体**（`IsDefinition`），声明不计入解析成功
- 解析失败或未匹配 → `LlParseDiagnostic`，**不**标记 Success
- 本阶段**不**实现虚拟 MCU / 函数执行

## Clang / libclang 版本

| 组件 | 版本 |
|------|------|
| ClangSharp | 18.1.0.2 |
| libclang.runtime.win-x64 | 18.1.3.2 |
| libClangSharp.runtime.win-x64 | 18.1.3.1 |
| 实测 `clang version` 字符串 | `clang version 18.1.3 (llvm-project c13b7485…)` |

编译参数（要点）：`-x c -std=c11`、`-I <LL>`、`-I <bridge>`、`-D__GNUC__=1` 等；优先探测 SDK 旁真实 Device/CMSIS 头，缺失则启用 Parse Bridge。

## Parse Bridge 声明（重要）

当前 SDK LL 根目录**没有**真实 `tae32g58xx.h` / `tae32g58xx_ll_conf.h`（Phase-1 已确认）。

当探测不到真实设备头时：

- 临时目录生成 **明确标注** 的桥接头（`/* PARSE BRIDGE */`）
- 外设实例宏来自 LL 头 `#if defined(GPIOA)||…` 扫描证据
- 结构体成员来自 LL 头 `ptr->MEMBER` 文本证据（**偏移/布局非权威**）
- `__STATIC_INLINE` → `static inline`（CMSIS 桩）
- 每次使用写入 `MissingSdkHeader` / `ParseBridge` 诊断，**不得当作真实 SDK 环境**

## 解析数量（实测，2026-11-12）

对 23 个 `tae32g58xx_ll_*.h`（排除 `ll.h` / `ll_def.h`）逐文件建 TU：

| 指标 | 数量 |
|------|------|
| 头文件成功提取 | 23 / 23 |
| AST 函数定义 | **3623** |
| Phase-1 扫描 inline_definition | ~3628 |
| 差额 | 约 5（行号/条件编译/边缘定义差异，以诊断记录为准） |
| Parse Bridge | 启用（instances≈71，typedefs≈24） |

按外设头文件抽样：GPIO 35、ADC 213、RCU 503、CAN 401、HRPWM 695 等。

应用内对已导入项目点「深度解析」后，以 DB 匹配数 `FunctionsMatched/FunctionsParsed` 为准（按 NaturalKey / 文件名+行号回退匹配）。

## 寄存器宏分析策略

真实 SDK 宏（`tae32g58xx_ll_def.h`）：`SET_BIT` / `CLEAR_BIT` / `READ_BIT` / `READ_BIT_SHIFT` / `CLEAR_REG` / `WRITE_REG` / `READ_REG` / `MODIFY_REG`。

识别路径：

1. AST `CallExpr`（宏未完全消解时）
2. 展开后的成员赋值 / `|=` `&=`（AST Binary/CompoundAssign）
3. **原始源码行**中的宏 token（展开前证据），并要求与 `Type->Reg` 或赋值形态一致

不把 `POSITION_VAL` 等辅助宏记为寄存器访问。

## 数据库（迁移 `Phase3_LlDeepParse`）

新增表（保留原有数据）：

- `LlFunctionParameters`
- `LlFunctionOperations`
- `LlFunctionCalls`
- `LlRegisterAccesses`
- `LlRegisterReferences`
- `LlMacroInfos`
- `LlParseDiagnostics`

`LlFunctions` 增加可空字段：`Signature`、`SourceText`、`Modifiers`、`IsStatic`、`IsInline`、`ParseStatus`、`ClangVersion`、`ParsedAtUtc` 等。

## WPF

LL 函数库：芯片/外设/名称筛选、分页、**深度解析**按钮、`ParseStatus` 列；详情含基本信息、参数、返回值、源码、操作、寄存器、宏、调用、诊断。

## 测试

```powershell
dotnet test tests\TAE32.LLVirtualTest.Tests
```

详见 [Phase3_Validation.md](Phase3_Validation.md)

## 失败 / 限制案例

| 场景 | 行为 |
|------|------|
| 缺失真实设备头 | Parse Bridge + Warning 诊断，不伪装为完整 SDK |
| Clang TU 失败 | Error 诊断，该头不计 Success |
| AST 行号与扫描 JSON 不一致 | Match 警告，跳过或回退匹配 |
| 大型头文件 Clang Warning | 保留诊断，仍尝试提取 |
| 宏完全展开后无 CallExpr | 依赖源码 token + 赋值 AST 交叉验证 |

## 本阶段明确不做

- 虚拟 MCU
- LL 函数执行 / 仿真
- 以 Bridge 冒充真实寄存器布局权威数据
