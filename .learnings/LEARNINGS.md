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




