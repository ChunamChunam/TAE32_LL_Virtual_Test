# Learnings

---


## 2026-11-12
- **Category**: best_practice
- **Pattern-Key**: isolate-native-harness
- **Insight**: Never call compiled LL harness DLL in the UI process; AccessViolation kills the host. Always isolate with a child process.
- **Source**: user crash report


## Learning: App icon redesign preference
- **Date**: 2026-11-13
- **Category**: correction
- **Summary**: Busy AI-generated icons (chip + dashboard bars + waveform) were rejected as ugly. Clean geometric monogram (teal gradient + white T) reads better at taskbar sizes.
- **Action**: Prefer precise vector drawing over photoreal/AI collage for Windows .ico assets.

---

## [LRN-20261113-gpio-dor] insight
**Logged**: 2026-11-13
**Summary**: 9 non-Passed were host harness bugs, not SDK or bad history. (1) ApplyHostGpioBsrToDor treated ODR as DOR; (2) BSR→DOR mirror ran after native Read so Set→Read failed; (3) __DSB/__ISB missing on x64 for EFLASH.
**Action**: Prefer DOR over ODR; mirror BSR→DOR in harness after GPIO preludes; stub barriers in cmsis_override.

---

## [LRN-20261116-bitop-assert] insight
**Logged**: 2026-11-16T09:30:00+08:00
**Category**: insight
**Summary**: Empty semantic assertions for SET_BIT LL helpers came from generator only supporting MODIFY_REG write-check + `IsLikelyRegisterSetter` missing Assert*. Trust model: resolve expected mask bits from `#define`/chip fields at generation (prefer live body over stale DB Expression), persist ExpectedHex; never re-derive expectation from mutated LL at run time. Wrong-mask verify = generate on good SDK → mutate → run same case.
**Action**: Use `TryBuildBitOpWriteCaseAsync`; do not regenerate after intentional corruption.

---

## [LRN-20261116-bitop-assert-trusted] correction
**Logged**: 2026-11-16T09:46:00+08:00
**Category**: correction
**Summary**: User regenerated after mutating SET_BIT to BIASEN → expected became 0x1 → false Passed. Body-derived expected is not trusted.
**Action**: Prefer function-name ↔ independent `LL_*_MSK` #define (e.g. AssertPreparingStart → LL_ADC_CFGR1_PREPARING_START_MSK=0xB). Regenerate after corruption still Failed (exp 0xB act 0x1). App uses Publish\SDKContent\G580x path.

---

## [LRN-20261116-disableit-awdg2] correction
**Logged**: 2026-11-16T10:00:00+08:00
**Category**: correction
**Summary**: `LL_ADC_DisableIT_AWDG2` with CLEAR_BIT AWD1IE still Passed — trusted lookup only matched `LL_*_MSK`, missed `LL_ADC_IER_AWD2IE` aliases; fell back to wrong body mask.
**Action**: Match `AWDG2`→`AWD2IE` via LL aliases + chip `*_Msk`; clear-check expects IER&0x80==0. Wrong AWD1 → Failed (act 0x80).

---

## [LRN-20261116-bitop-fullscan] insight
**Logged**: 2026-11-16T10:15:00+08:00
**Category**: insight
**Summary**: Full LL scan 691 SET/CLEAR/WRITE: TRUSTED≈350, WEAK≈228 (mostly CAN long names / body fallback), NONE≈113 (Mask/BIT(Ch)/Value params). Fixed RCU draft-only path; WRITE_REG ClearFlag trusted+W1C; ClearFlag_AWDn→AWD{n-1}; field aliases Channel→CHEN, HSE→XEN, etc. Smoke 8/8 ADC wrong-mask Failed→correct Passed.
**Action**: Prefer function-name↔#define/RegisterFields; never body arg for expected. Parametric Mask/Ch cases stay NONE by design.

---

## [LRN-20261116-modify-read-trusted] correction
**Logged**: 2026-11-16T10:35:00+08:00
**Category**: correction
**Summary**: User asked to audit READ_BIT_SHIFT/MODIFY_REG/all macros. Same false-Pass risk: clear-mask / read field / READ_REG member taken from live body. Header macros ~3598 calls: READ_BIT_SHIFT 923, SET 806, CLEAR 677, MODIFY 491, WRITE 368, READ_BIT 237, READ_REG 158, POSITION_VAL 24, CLEAR_REG 1.
**Action**: Extend trusted resolve to MODIFY clear-mask + READ_* field/member (name↔#define/RegisterFields/aliases e.g. CalibrationMode→ADCALDIF, OVSS); live-body fallback when DB empty. Scan 1494 fns: MODIFY TRUSTED=187/193, READ_BIT_SHIFT 393/403; smoke Set/GetCalibrationMode + SetOVSS wrong→Failed correct→Passed. POSITION_VAL/CLEAR_REG not case types; parametric Mask/BIT(Ch) stay NONE/WEAK.

---

## [LRN-20261116-trust-boost] best_practice
**Logged**: 2026-11-16T10:45:00+08:00
**Category**: best_practice
**Summary**: To raise trust coverage: CamelCase acronym + trailing-verb strip + CAN/CMP/DAC aliases; emit SET/CLEAR even when MODIFY already built; expand smoke across ADC/CAN/RCU/CMP/DAC.
**Action**: After boost scan TRUSTED 1006→1097, WEAK 293→202; smoke 20/20 OK. Remaining WEAK mostly param Mask/Ch, SDK quirk ClearFlag≠field name, READ_REG obscure members.

---

## [LRN-20261116-rmw-readonly] best_practice
**Logged**: 2026-11-16T10:50:00+08:00
**Category**: best_practice
**Summary**: SET/CLEAR/MODIFY/WRITE_REG(W1C) need preload unrelated bits (RMW). READ_* must assert register unchanged after call. Do not emit SET/CLEAR case alongside MODIFY on same member (SetParity CLEAR+MODIFY would false-fail CLEAR-only expect).
**Action**: PickUnrelatedPreserveBits + RegisterUnchangedAfterReadAssertion; skip overlapping bitOp when MODIFY write-check exists.

---

## [LRN-20261116-mask-member-align] correction
**Logged**: 2026-11-16T11:40:00+08:00
**Category**: correction
**Summary**: `SET_BIT(DACx->SR, DAC0_CR_OEN_Msk)` must fail: chip mask embeds register CR. Assert on mask's register, not body's wrong arrow. Apply to SET/CLEAR/MODIFY/WRITE/READ_BIT(_SHIFT); scan whole body for combo mismatches into Notes.
**Action**: `ResolveMemberAlignedToMask` + `CollectBodyMaskMemberMismatchNotes` on every generated case.

---

## [LRN-20261116-readbit-then-pos] insight
**Logged**: 2026-11-16T14:25:00+08:00
**Category**: insight
**Summary**: Many Get APIs use `(READ_BIT(reg->MEM, Xxx_Msk) >> Xxx_Pos)` (WWDG/IWDG/UART…), not `READ_BIT_SHIFT`. Generator only matched READ_BIT_SHIFT / bool READ_BIT / READ_REG → timeout-only draft → Skipped.
**Action**: Treat `READ_BIT(..._Msk) >> ..._Pos` same as READ_BIT_SHIFT for read-check; regenerate Get cases after fix.

---

## [LRN-20261116-w1c-clearflag] correction
**Logged**: 2026-11-16T14:40:00+08:00
**Category**: correction
**Summary**: LL_WWDG_ClearFlag_EWIF failed because legacy clear-check used flagMask=0xFFFF + Expected=0 (whole ISR). Virtual W1C correctly produced 0xFFFE from 0xFFFF write 1. SVD marks EWIF read-write; W1C inferred from ClearFlag WRITE_REG idiom + host override. Same pattern across ADC/CMP/IWDG/DAC/TMR/HRPWM/UART ClearFlag.
**Action**: Bit-level W1C model; clear asserts = (actual&flag)==0 AND preserve ~flag; delta sync so only changed regs attributed to LL; regenerate ClearFlag cases.

---

## [LRN-20261116-get-expected-from-initial] correction
**Logged**: 2026-11-16T14:55:00+08:00
**Category**: correction
**Summary**: GetPrescaler Failed: expected=1 but PSCR preload 0xA5A55A59 → LL returned 0x5A59. Generator invented sample=1 separately from preserve-contaminated preload; DB mask could be wrong vs header 0xFFFF.
**Action**: For all Get/Read: expected=(initial&mask)>>pos from SAME initial; prefer body #define Mask/Pos; multi samples min/one/mid/max; gen-time consistency check. Affects all READ_BIT>>Pos getters.

---

## [LRN-20261116-modify-cmsis-expected] correction
**Logged**: 2026-11-16T15:10:00+08:00
**Category**: correction
**Summary**: SetPrescaler Failed: expected 0xA5A55A5F (=initial|7) vs correct 0xA5A50007. Cause: clearMask from wrong/narrow DB/trusted mask so preserve leaked into field; OR-style expectation. CMSIS needs (initial&~clearMask)|setMask with clearMask from body+chip.h 0xFFFF.
**Action**: TryBuildModifyRegWriteCasesAsync: body Mask/Pos from chip.h; multi samples; full/field/preserve asserts; gen-time CMSIS check. Same for all MODIFY_REG Set* across peripherals.

---

## [LRN-20261116-chip-header-address] best_practice
**Logged**: 2026-11-16T15:20:00+08:00
**Category**: best_practice
**Summary**: User requires all register absolute addresses from chip headers, not stale DB. Virtual MCU now loads ChipHeaderAddressCatalog (BASE from chip.h + (@ offset) from chip_struct.h) and overrides slot AbsoluteAddress.
**Action**: Prefer chip.h for Mask/Pos (generator) and BASE+offset (VirtualMcuDefinitionLoader).

---

## [LRN-20261116-bitfield-stale-db-mask] correction
**Logged**: 2026-11-16T15:25:00+08:00
**Category**: correction
**Summary**: SetPrescaler BitField Expected=6/7/7 while Actual=65534/32767/65535. Root: BitField used DB RegisterField.Mask=0x7 (3-bit) → param&0x7; RegisterValue already used chip clearMask=0xFFFF. 0x7 came from stale DB field metadata, not SDK.
**Action**: BitField Expected=(setMask&clearMask)>>pos with ExpectedMask=clearMask; EvalBitField extracts via ExpectedMask from CurrentValue; loader overrides field Mask from chip.h.

---




## 2026-11-17 - Flat peri host image AbsoluteAddress packing
- **Category**: best_practice
- **Pattern-Key**: host-image-absolute-address-flat-peri
- **Summary**: ADC/UART 等扁平外设若落入 SequentialFallback（ImageBase=0 顺序打包），Native 按 TypeDef offsetof 读（如 HISR @+0x180）会读到 0，导致 pattern/ones 读用例 Fail、zero 假 Pass。必须始终用 chip.h BASE+offset 打包，且 ImageBase 对齐 peri BASE（不可把高偏移寄存器绝对地址当基址）。读用例须先写/预置，写用例须回读；掩码/地址以 LL+chip.h 为准。
- **See Also**: NativeTestHost.AllocateAndFillAsync / RecoverAbsoluteAddressesAsync / ResolveAggregateImageBase(structMin)

## 2026-11-17 - Channel BIT(Ch) Enable/Disable drafts → Skipped
- **Category**: insight
- **Pattern-Key**: set-clear-bit-channel-bit-generation
- **Summary**: LL 形如 CLEAR_BIT(ADCx->HIER, BIT(((Ch)%LL_ADC_CH_NUMS))) 无法被命名掩码 SET/CLEAR 正则匹配，生成器落入仅超时 /draft，引擎故意标 Skipped。需单独解析 BIT(Ch%N[+Pos])，预置目标位后再校验清/置，并赋 Ch 参数。

## 2026-11-17 - Static analysis must use SQLite macros, not re-parse chip.h
- **Category**: correction
- **Pattern-Key**: static-analysis-sqlite-first
- **Summary**: User asked why chip.h was re-parsed when DB already has RegisterMacroReferences (18k Pos/Msk + Expansion) and RegisterFields. Also ShiftExpr regex catastrophic backtracking froze Analyze for minutes. Fix: load macros from SQLite; skip LL header IngestFile when source=sqlite; replace ShiftExpr with linear FindShiftOperations; cache diagnostics on LlFunctions.StaticAnalysisJson/Stamp. Smoke: 3 ADC cases ~3.9s (was stuck at case 1 for 4+ min).
- **Action**: Prefer DB RegisterMacroReferences for semantic catalog; persist per-function StaticAnalysisJson; never use nested-quantifier shift regex.

## 2026-11-17 - Deep-parse persists static analysis; fix false positives
- **Category**: correction
- **Pattern-Key**: static-analysis-deep-parse-persist
- **Summary**: Wired LlStaticAnalysisPersistService after LL deep parse and register parse. Fixed false positives: LL_*_MSK helpers, BIT(Ch%N) masks, SET_BIT nested parens, _NUMS/_CH_ non-field macros, _Val as mask, RegisterHint prefix match, ShiftExpr catastrophic backtracking (earlier). Remaining ~31 Error / 12 Warning functions need continued review.
## [LRN-20261118-001] correction

**Logged**: 2026-11-18T11:30:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
11248 用例里 Failed=1642 / Skipped=480 主因是生成策略，不是静态分析。

### Details
- Skipped 全部为「仅超时断言」草稿。
- Failed 桶：return-mismatch 670、reg-assert-fail 541、wrong-write-target 234、reg-missing 194。
- StaticAnalysisFailed 仅 1 条：`LL_WWDG_EnableIT_EWIE` 体里 `SET_BIT(CR, WWDG_CVR_CV_Msk)` 是 SDK 真问题，不是误报。
- 旧策略用 min/one/mid/max/nearmax/one-clean、A5A5 干扰位、RegisterWrite/NoUnexpectedWrite/成对 companion，导致用例膨胀与假失败。

### Suggested Action
按 LL 函数体每函数一条代表性用例；读=先写寄存器再 Get；写=先读基线再写后回读目标位；去掉发明的多样本/轨迹断言。用户需重新生成用例后再跑。

### Metadata
- Source: user_feedback
- Related Files: src/TAE32.LLVirtualTest.Infrastructure/TestEngine/LlTestCaseGenerator.cs
- Tags: test-generation, read-write-protocol, static-analysis
- Pattern-Key: ll-one-case-writeback-protocol

---

## [LRN-20261118-002] correction

**Logged**: 2026-11-18T13:50:00+08:00
**Priority**: high
**Status**: resolved
**Area**: tests

### Summary
最新保留跑批（3635）：Passed 2590 / Failed 620 / Skipped 424。主因仍是生成器与虚拟 MCU，不是大量 SDK 缺陷。

### Details
- Skipped=424：仅 Timeout，draft 无语义断言。
- Fail 桶：W1C 清不掉 186（SVD RO 字段未继承 W1C）、返回值不匹配 137（ADTMR 参数 TMR10 vs 预置 TMR9）、SET/CLEAR 154（含跨外设可信掩码误绑 UE/DIR）、寄存器缺失 41、MODIFY 63。
- 典型生成器 bug：UpdateEvent→UART0_CR0_UE（体实为 UDIS）；UART Direction→TMR10_CR0_DIR（体为 TE/RE）；ClearFlag_FULx/HLFx 断言 DISR 但写入 FISR/HISR；ClearFlag Mask=0。
- SDK 真问题仍极少（如先前 WWDG EWIE→CVR）。

### Suggested Action
已修：W1C RO 继承、跨外设可信掩码过滤、实例指针对齐、ClearFlag 映射/Mask、draft 内部 RegisterWrite。需重新生成用例后再全量跑。

### Metadata
- Source: user_feedback
- Related Files: LlTestCaseGenerator.cs, VirtualRegisterSemanticsOverrides.cs, LlClearStatusRegisterResolver.cs
- Tags: test-triage, w1c, trusted-mask, draft-enrichment
- Pattern-Key: reject-cross-peri-trusted-mask

---

## [LRN-20261118-003] insight

**Logged**: 2026-11-18T14:45:00+08:00
**Priority**: high
**Status**: resolved
**Area**: tests

### Summary
全量重生+跑批 3635：Pass 2785 / Fail 563 / Skip 287。相对旧跑批 Pass+195、Skip-137。W1C 仍 186 条，根因是宿主纯 RAM：`WRITE_REG(ISR, mask)` 在 seed==mask 时前后值不变 → delta sync 跳过 → 虚拟 MCU 未走 W1C Write。

### Suggested Action
对 W1C/ClearFlag：宿主写旁路或 seed==after 时仍按 written 值调用 `WriteAsync` 触发 W1C；补 CAN0_CTRL/ADC0_CDR 等缺失实例。

### Metadata
- Source: regen_all_and_run
- Related Files: NativeTestHost.cs SyncBufferToVirtualMcuAsync, VirtualRegisterSemanticsOverrides.cs
- Pattern-Key: w1c-host-delta-no-change

---

## [LRN-20261118-004] correction

**Logged**: 2026-11-18T15:20:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
按桶修复生成器/宿主（非 SDK）：W1C seed==write 强制 WriteAsync；多 token 掩码字段（CTRL_FD_EN / CDR_RDATA_MST）；扁平路径禁止 CAN0_CTRL 当实例；`!READ_BIT_SHIFT` 取反期望；WRITE_REG `_Val`；READ_REG 体成员优先于 PRESC；EnableIT/Break 拒绝 SR/UGR 错绑；draft 补 RegisterWrite + 非零 Val。

### Details — 确认的 SDK 问题（须记录，勿当生成器假失败）
1. **`LL_WWDG_EnableIT_EWIE`**：`SET_BIT(WWDGx->CR, WWDG_CVR_CV_Msk)` — 目标 CR 却用 CVR.CV 掩码。静态分析 RegisterFieldMismatch。**真 SDK bug**。
2. **`LL_ADC_ClearFlag_AWD1` / `IsActiveFlag_AWD1`**：注释写 AWDG0，体用 `AWD0_Msk`（编号相对函数名偏一）。属 SDK 命名/注释 quirks，生成器已按体宏对齐；不改 SDK。

### Suggested Action
重新生成全部用例后全量跑批，对比 Skip/W1C/MODIFY/RETURN/MISSING/SET-CLEAR 桶下降；SDK 两项保持 Failed/StaticAnalysis 直至厂商修头文件。

### Metadata
- Source: user_ordered_bucket_fix
- Related Files: LlTestCaseGenerator.cs, NativeTestHost.cs
- Tags: w1c-sync, mask-parse, trusted-role, invert-shift, write-reg-val
- Pattern-Key: ordered-fail-bucket-fix

---

## [LRN-20261118-005] correction

**Logged**: 2026-11-18T15:50:00+08:00
**Priority**: high
**Status**: resolved
**Area**: tests

### Summary
二轮 regen+run：Pass **3093** / Fail **257** / Skip **285**（基线 2785/563/287）。W1C 186→40；SET+CLEAR 75→21；MISSING 74→39；MODIFY 148→86；RETURN 72→61；FAIL_OTHER 221→0（限制 Clear* 才强制 W1C）。EnableChannel AWDG 错绑已按 Label 拒绝。

### Suggested Action
下一轮优先：SKIP DMA REG_OFFSET/BIT(Ch) 草稿；剩余 40 W1C（ADTMR CC*OIF 信任掩码 vs 体）；EFLASH/DMA 实例名缺失。

### Metadata
- Source: post_fix_regression
- Related Files: NativeTestHost.cs IsLikelyW1cClearWrite
- Pattern-Key: w1c-force-sync-reads-only-clear

---

## [LRN-20261118-006] correction

**Logged**: 2026-11-18T17:00:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
剩余桶修复：W1C ClearFlag 体宏优先（CC0MIF≠OIF、UIF≠UGR）；orphan `FLASH_Type`/`DMA0_Type`/`EFLASH_TypeDef` 推断实例；DMA CH→DMA0；ADC `REG_OFFSET.TCR`/`TAR`；`READ_BIT==0` 布尔；WaitBufferRelease/SetCounter 宿主旁路期望；AutoReload→ARE、BTO→TOSEL、IT_CMP→CIE。

### Confirmed SDK-only
`LL_WWDG_EnableIT_EWIE`：`SET_BIT(CR, WWDG_CVR_CV_Msk)` 应为 `WWDG_CR_EWIE_Msk`（位图 WEN/EWIE 本身正确）。

### Metadata
- Source: user_remaining_buckets
- Related Files: LlTestCaseGenerator.cs, VirtualMcuDefinitionLoader.cs
- Pattern-Key: orphan-struct-instance-infer

---

## [LRN-20261118-007] correction

**Logged**: 2026-11-18T18:20:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
`LL_EFLASH_ClearFlag` body clamps `(Mask)&LL_EFLASH_SR_ERROR_IT_FLAG_MSK`，但 `TryParseChipMaskRegAndField` 对 `LL_*` 复合宏直接失败，导致 ClearFlag 可信源回落到 `ERROR_FLAG_MSK=0x737`，W1C 预置全错误位后只清 IT 子集 → 断言失败。用户要求 fail-fast：非 Passed 即停改。

### Fix
- `LL_` 前缀剥掉再解析；`EFLASH` 视为 peri；ClearFlag 未解析字段时要求宏名全等；拒绝 `ERROR_IT_FLAG`≠`ERROR_FLAG`。
- `(Mask)&LL_*_MSK` ClearFlag 需 AssignRuntimeMask（否则 Mask=0 W1C 空写）。
- `!!READ_BIT` 勿判为 invert；MODIFY 解析 `LL_* << Pos` 命名常量与 `(Num)&0x3f`；`Area & Xxx_Val` SET/CLEAR；SetKey Key&Val<<Pos；纯算术对齐 / Refresh READ_REG。
- EFLASH fail-fast：**99/99 Passed**。

### Metadata
- Source: fail_fast_eflash
- Related Files: LlTestCaseGenerator.cs
- Pattern-Key: ll-composite-mask-parse-clearflag

---

## [LRN-20261118-008] correction

**Logged**: 2026-11-18T22:25:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
HRPWM 生成在 ~615 `GetCompareA` 卡住（CPU≈0）：`TryResolveTrustedMemberAsync` 对每次 READ_REG 全表 Distinct `RegisterDefinitions`；叠加 `#define` 正则 `(?:.*\\n)*.*` 吞掉 chip_struct 全文。外层 DbContext 跨 Flush 持有也会 SQLite 锁死。

### Fix
- `#define` 改为行级 Index 扫描 + 文件缓存；外层 DB 读完即释放；trusted member 按 token 过滤/截断，body 已有叶子成员则跳过。

### Metadata
- Source: fail_fast_hrpwm_hang
- Related Files: LlTestCaseGenerator.cs, LlTestEngine.cs
- Pattern-Key: hrpwm-gen-hang-trusted-member

---

## [LRN-20261118-009] correction

**Logged**: 2026-11-18T23:50:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
HRPWM fail-fast：`GetCompareA` 卡死于 `READ_REG…&_Val` 灾难性回溯；`Prd`/`Evt` 未赋 WRITE 载荷；`LL_*_MSK` 误推 `LL_COM`；`BIT(Fltx%N+Pos)` 被当成 BIT0；`((Pwmxs)&MASK)>>1`/`<<Pos` 未匹配；`Common.EECR0` REG_OFFSET 路径/字面移位；`Pol=0x4` 误传已移位掩码导致 `(Pol&1)<<Pos=0`。

### Fix
- 门控+有界 `_Val` 正则；payload 从 `((Name)&…)` 提取；拒绝 `LL_` 假实例；BIT lane 用 Pos；Pwmxs 复合 SET/CLEAR+移位；REG_OFFSET 支持 `Common.*`；字段参数传 unshifted 值。

### Metadata
- Source: fail_fast_hrpwm
- Related Files: LlTestCaseGenerator.cs
- Pattern-Key: hrpwm-write-payload-regoffset

---

## [LRN-20261119-010] correction

**Logged**: 2026-11-19T01:52:00+08:00
**Priority**: high
**Status**: resolved
**Area**: tests

### Summary
HRPWM 收尾：双 MODIFY 贪婪 rhs；`Common.BDUPR0`/`PWM[…].REG` REG_OFFSET；Pwmxs 复合读；`_Val` 被当成 sticky mask 导致 SetPeriod draft；双字段 MODIFY 只赋 Last 参数（Pol=0）；SysDMA 指针需宿主 offsetof。

### Fix
- MODIFY/WRITE REG_OFFSET 支持嵌套/数组路径；Pwmxs READ 复合掩码；WRITE `_Val` 走 sibling `_Msk`；双 payload 全赋；GetSysDMADataAddr 宿主 offsetof。HRPWM **695/695 Passed**。

### Metadata
- Source: fail_fast_hrpwm_finish
- Related Files: LlTestCaseGenerator.cs, TestHarnessGenerator.cs
- Pattern-Key: hrpwm-695-passed

---

## [LRN-20261119-011] correction

**Logged**: 2026-11-19T02:20:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
I2C 剩 3 个非 Passed：`IsEnabledIT` draft、`ReceiveData8` draft、`SetRxSCLStretchMode` 错绑 MSTCH。根因：(1) `IndexOf(name+"(")` 命中注释 `See LL_I2C_SetRxSCLStretchMode()` → 取到 EnableMasterClockStretching 的 SET_BIT MSTCH；(2) `IsLikelyGetter` 不含 Receive；(3) 无 @ref 时 peri 用 `^LL_([A-Za-z]+)` 把 `I2C` 截成 `I` → 搜 `I0_INTREN_`；且对 multi-MB chip.h 跑 Regex.Matches 不可靠。

### Fix
- `IndexOfInlineFunctionDefinition` 优先 `__STATIC_INLINE` 定义、跳过块注释引用。
- Getter 含 Receive；runtime mask 用 IndexOf 扫 `_Msk`；peri `^LL_([A-Za-z][A-Za-z0-9]*)`；可回退 EnableIT 注释族。

### Metadata
- Source: fail_fast_i2c
- Related Files: LlTestCaseGenerator.cs
- Pattern-Key: i2c-body-index-peri-digit

---

## [LRN-20261119-011] correction

**Logged**: 2026-11-19T02:20:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
I2C 剩 3 个非 Passed：`IsEnabledIT` draft、`ReceiveData8` draft、`SetRxSCLStretchMode` 错绑 MSTCH。根因：(1) `IndexOf(name+"(")` 命中注释 `See LL_I2C_SetRxSCLStretchMode()` → 取到 EnableMasterClockStretching 的 SET_BIT MSTCH；(2) `IsLikelyGetter` 不含 Receive；(3) 无 @ref 时 peri 用 `^LL_([A-Za-z]+)` 把 `I2C` 截成 `I` → 搜 `I0_INTREN_`；且对 multi-MB chip.h 跑 Regex.Matches 不可靠。

### Fix
- `IndexOfInlineFunctionDefinition` 优先 `__STATIC_INLINE` 定义、跳过块注释引用。
- Getter 含 Receive；runtime mask 用 IndexOf 扫 `_Msk`；peri `^LL_([A-Za-z][A-Za-z0-9]*)`；可回退 EnableIT 注释族。

### Metadata
- Source: fail_fast_i2c
- Related Files: LlTestCaseGenerator.cs
- Pattern-Key: i2c-body-index-peri-digit

---

## [LRN-20261119-012] correction

**Logged**: 2026-11-19T04:00:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
Fail-fast 收尾 SPI→WWDG：SYSCTRL ClearFlag PSR 未建模 W1C；UnlockSpecialRegister KEY1→KEY2 断言了首写；SetDMARequestControl 的 (1<<(Pos&0x1f))&Msk 与 HSI/LSI 哨兵默认频率未覆盖。UART：IntIt/IntPnd TypeDef 仅为 uint32_t；^0x1 反相、Direction/Parity 枚举、BaudRateHz 换算、RDR ReceiveData、Config 包装。

### Fix
- W1C 成员加 `PSR`；多 `WRITE_REG` 同路径取末次；Pos&0x1f 移位 SET/CLEAR；HSI/LSI 哨兵→默认 Hz。
- UART：`LL_*_IT_`/`FLAG_` 别名解析；`IntPnd` ClearFlag；`^0x1` 作 invert；Direction/Parity/Baud/Config/RDR/IsOnAPB1 专用用例；`eq0` 需 `?1`。

### Result
SPI 155、SYSCTRL 196、UART 137 Passed；WWDG 13 Passed + 1 已知 SDK `EnableIT_EWIE`（SdkAllowed）。

### Metadata
- Source: fail_fast_spi_wwdg
- Related Files: LlTestCaseGenerator.cs, VirtualRegisterSemanticsOverrides.cs
- Pattern-Key: sysctrl-psr-uart-enum-baud

---

## [LRN-20261119-013] correction

**Logged**: 2026-11-19T05:30:00+08:00
**Priority**: high
**Status**: pending
**Area**: tests

### Summary
全量 `--no-fail-fast` 首轮：3635/3627，7 blockers。根因：(1) `TryParseUintDefineFromFile` 对 OR 复合宏抓 `TMR9`→9；(2) `IsLikelyPeripheralInstanceName` 把 `LL_ADC_CSR_MST` 当实例；(3) UART Direction 特判误伤 SPI；(4) `SetSequencerRanks` 把 `Ch` 当 lane 强制 0。

### Fix
- 复合宏/`*_Msk` 体拒绝裸数字；实例名拒 `LL_`、收紧 `_MST/_SLV/_COM`；Direction 限 `LL_UART_*`；Seq 场景下 `Ch` 作字段载荷。

### Result
复跑全量：**Total=3635 Passed=3634 SdkAllowed=1（WWDG EWIE）Blockers=0**。

### Metadata
- Source: full_no_fail_fast
- Related Files: LlTestCaseGenerator.cs, tools/_regen_all_and_run/Program.cs
- Pattern-Key: composite-mask-digit-and-uart-dir-gate

---

## [LRN-20261119-014] correction

**Logged**: 2026-11-19T08:55:00+08:00
**Priority**: high
**Status**: resolved
**Area**: tests

### Summary
`LL_WWDG_EnableIT_EWIE` 官方正确写法是 `SET_BIT(WWDGx->CR, WWDG_CR_EWIE_Msk)`，不是 SDK bug。

### Details
- Git HEAD / 官方源已是 `WWDG_CR_EWIE_Msk`。
- 工作区曾被误改成 `WWDG_CVR_CV_Msk`，DB `LlFunctions.SourceText` 也缓存了错误体；引擎优先用 DB SourceText，故一直报 RegisterFieldMismatch。
- 还原头文件并刷新 SourceText 后，WWDG **14/14 Passed**。

### Suggested Action
禁止改 `SDKContent`；发现静态分析与磁盘不一致时先 `git diff` SDK + 重解析/刷新 SourceText，勿把本地脏副本当 vendor bug。

### Metadata
- Source: user_feedback
- Related Files: SDKContent/.../LL/tae32g58xx_ll_wwdg.h, LlTestEngine.cs
- Tags: wwdg, sdk, source-text-stale
- See Also: LRN-20261119-013
- Pattern-Key: prefer-git-sdk-over-dirty-workspace

---
