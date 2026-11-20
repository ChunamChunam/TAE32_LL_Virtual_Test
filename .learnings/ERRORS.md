# Errors

---


## 2026-11-12 AccessViolation in NativeTestHost
- **Error**: System.AccessViolationException in NativeTestHost.Execute / tae32_run
- **Effect**: WPF process terminated (闪退)
- **Cause**: In-process native harness AVE is not catchable in .NET 8
- **Fix**: Out-of-process NativeRunner + larger peri buffer; mark case Error instead of killing UI
- **Tags**: native, crash, test-engine


## [ERR-20261119-001] Plan batch TotalCount=0 after save

**Logged**: 2026-11-19T14:04:00+08:00
**Priority**: high
**Status**: pending
**Area**: TestBatchService.ResolveCaseIds

### Summary
「生成并按计划执行」保存成功但批次 Total=0：计划 ChipModelName=TAE32G58xx，用例 ChipModelName=TAE32F561x_LL_Driver，严格相等过滤掉全部用例。

### Error
Batches Completed with TotalCount=0 for EFLASH/CORTEX/RCU; UI overwrote status as 「计划已保留并执行完成」.

### Context
- Active SDK project cases tagged TAE32F561x_LL_Driver
- PlanChip UI default TAE32G58xx
- ResolveCaseIds Plan branch filtered by chip equality

### Suggested Fix
Remove chip equality filter in Plan scope (SdkProjectId + peripheral enough); surface real batch counts in RunPlan status.

### Metadata
- Related Files: TestBatchService.cs, TestManagementViewModel.cs
- Tags: test-plan, chip-filter, empty-batch

---
