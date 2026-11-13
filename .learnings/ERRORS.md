# Errors

---


## 2026-11-12 AccessViolation in NativeTestHost
- **Error**: System.AccessViolationException in NativeTestHost.Execute / tae32_run
- **Effect**: WPF process terminated (闪退)
- **Cause**: In-process native harness AVE is not catchable in .NET 8
- **Fix**: Out-of-process NativeRunner + larger peri buffer; mark case Error instead of killing UI
- **Tags**: native, crash, test-engine

