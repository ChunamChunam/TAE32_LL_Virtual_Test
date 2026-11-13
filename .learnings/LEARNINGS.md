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
