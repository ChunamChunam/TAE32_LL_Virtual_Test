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

