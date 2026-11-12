# Phase 3 Validation — Clang AST LL Deep Parse

**Date:** 2026-11-12  
**Toolchain:** ClangSharp 18.1.0.2 / libclang 18.1.3.2 (win-x64)  
**Clang string:** `clang version 18.1.3`

## Full-header AST extraction (no DB)

| Metric | Value |
|--------|-------|
| Headers | 23/23 with ≥1 definition |
| Function definitions extracted | **3623** |
| Phase-1 inline_definition baseline | ~3628 |
| Parse Bridge | Required (device headers absent) |

## Manual / automated GPIO checks

| Case | Real function | Expectation | Result |
|------|---------------|-------------|--------|
| Simple read | `LL_GPIO_GetPinOutputType` | `READ_BIT` + `GPIOx->ODR` | Pass (strict assert) |
| Simple write / branch | `LL_GPIO_SetPinOutputType` | `If` + `SET_BIT`/`CLEAR_BIT` | Pass |
| Bit-field modify | `LL_GPIO_SetPinPull` | `MODIFY_REG` + AccessKind=Modify | Pass |
| Multi-param | `LL_GPIO_SetPinPull` (3 params) | AST parameters = 3 | Pass |
| Condition | `LL_GPIO_SetPinOutputType` | OpKind=If | Pass |
| static inline | GPIO LL bodies | Modifiers=`static inline` | Pass |
| Macro involved | above + `READ_BIT`/`MODIFY_REG` | SourceMacroToken / CallExpr | Pass |

```text
dotnet test tests\TAE32.LLVirtualTest.Tests
已通过! - 失败: 0，通过: 6，已跳过: 0，总计: 6
```

## Accuracy notes

- GPIO 抽样与真实头文件源码一致（参数个数、分支、寄存器宏名、`static inline`）。
- 全量 3623 vs Phase-1 ~3628：差额约 5，归因于条件编译边界/行号对齐；入库时以 Match 诊断暴露，不将失败标为 Success。
- 寄存器宏在 Clang 中常被展开；解析器同时使用 **展开后 AST** 与 **原始源码宏 token**，避免仅凭宏名臆造。

## Known limitations

1. Parse Bridge 非权威：成员存在性来自 LL 访问证据，偏移未知。
2. 提供真实 `tae32g58xx.h` 后应关闭 Bridge，以提高类型与实例地址一致性。
3. 间接调用单独记为 Indirect/Unknown（见 `LlFunctionCall.CalleeKind`）。
