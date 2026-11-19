# Feature Requests

Capabilities requested by the user.

---

## FR-20261113-001: App icon + Windows installer
- **Requested**: 2026-11-13
- **Area**: App packaging / branding
- **Problem**: No application icon; distribution only via folder publish
- **Request**: Design a reasonable icon; add installable setup package and verify
- **Status**: shipped
- **Notes**: Icon at `src/TAE32.LLVirtualTest.App/Assets/App.ico`; Inno Setup via `tools/build-installer.ps1`; output `artifacts/installer/TAE32.LLVirtualTest-Setup-1.0.0.exe`; smoke install/launch/uninstall passed

---

## FR-20261113-002: Single-instance app
- **Requested**: 2026-11-13
- **Area**: App runtime
- **Problem**: Multiple concurrent UI instances can conflict (DB/logs/window)
- **Request**: Program must not allow two instances at once
- **Status**: shipped
- **Notes**: `SingleInstanceGuard` mutex + activate event in `App.OnStartup`; second launch activates primary and shows info MessageBox then exits

---

## FR-20261116-001: SET_BIT/CLEAR_BIT register assertion generation
- **Requested**: 2026-11-16
- **Area**: TestEngine / LlTestCaseGenerator
- **Problem**: Functions like `LL_ADC_AssertPreparingStart` only got Timeout drafts (`assertions` empty of semantic checks) → Skipped
- **Request**: Auto-generate register assertions from SET_BIT/CLEAR_BIT/WRITE_REG/MODIFY_REG; catch wrong mask without deriving expected from mutated body
- **Status**: shipped
- **Notes**: `TryBuildBitOpWriteCaseAsync`; expected bits from `#define` + chip RegisterFields at generation time; persist ExpectedHex; verify ADC PREPARING_START Pass / BIASEN Fail

---

## FR-20261116-002: Audit MODIFY_REG / READ_BIT_SHIFT / all macros
- **Requested**: 2026-11-16
- **Area**: TestEngine / LlTestCaseGenerator
- **Problem**: Trusted expectation only hardened for SET/CLEAR/WRITE; MODIFY clear-mask and READ_* field/member still followed wrong body → false Pass after regen
- **Request**: Check and fix all macro paths present in LL headers
- **Status**: shipped
- **Notes**: Trusted clear-mask/field/member for MODIFY_REG + READ_BIT_SHIFT/READ_BIT/READ_REG; scan `tools/_verify_adc_set` mode=scan; smoke includes Set/GetCalibrationMode + SetOverSamplingRightShift

---

## [FEAT-20261118-001] ll_writeback_case_generation

**Logged**: 2026-11-18T11:30:00+08:00
**Priority**: high
**Status**: shipped
**Area**: tests

### Requested Capability
按 LL 库内容生成用例，不要自行加多样本；读先写后读校验；写先读再写再回读对比；去掉无用代码；排查静态检测导致的跳过/错误。

### User Context
测试管理显示 11248 用例、通过率 84.7%、失败 1643、跳过 480。

### Complexity Estimate
medium

### Suggested Implementation
已改 `LlTestCaseGenerator`：每函数一条 seed 用例；去掉 pair/A5A5/RegisterWrite 堆断言；静态分析保留（真 SDK 问题）。

### Metadata
- Frequency: first_time
- Related Features: FR-20261116-001

---

## [FEAT-20261118-002] sdk_defect_tracking

**Logged**: 2026-11-18T15:25:00+08:00
**Priority**: high
**Status**: open
**Area**: SDK (vendor) / static-analysis

### Requested Capability
区分生成器/宿主假失败与真实 SDK 缺陷；SDK 问题单独记录，不改厂商头文件。

### Confirmed SDK defects
1. `LL_ADC_ClearFlag_AWD1` / `IsActiveFlag_AWD1`：函数名 AWD1，注释/体为 AWDG0/`AWD0_Msk`（编号 quirks；测试按体宏对齐）。
（原 `LL_WWDG_EnableIT_EWIE` 误判已撤销：官方为 `WWDG_CR_EWIE_Msk`，本地脏副本/DB SourceText 过期导致。）

### Notes
其余 Fail/Skip 桶优先按宿主 W1C sync、掩码解析、可信掩码角色、取反读、WRITE_REG `_Val` 修复；全量 regen 验证中。

---
