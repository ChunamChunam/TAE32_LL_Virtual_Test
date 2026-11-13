# -*- coding: utf-8 -*-
import sqlite3
from collections import Counter, defaultdict

DB = r"d:\Code\12_TAE32_LL_Virtual_Test\Publish\data\tae32_ll_virtual_test.db"

con = sqlite3.connect(DB)
con.row_factory = sqlite3.Row
cur = con.cursor()
cur.execute(
    """
    WITH latest AS (
      SELECT r.*, c.PeripheralName, c.FunctionName,
        ROW_NUMBER() OVER (PARTITION BY r.LlTestCaseId ORDER BY r.StartedAtUtc DESC) rn
      FROM LlTestRuns r JOIN LlTestCases c ON c.Id = r.LlTestCaseId
    )
    SELECT * FROM latest WHERE rn = 1 AND Status = 'Error'
    ORDER BY PeripheralName, FunctionName
    """
)
rows = cur.fetchall()
print("latest Error count:", len(rows))
by_kind = Counter()
by_fn = Counter()
for r in rows:
    fr = r["FailureReason"] or ""
    if "编译失败" in fr:
        by_kind["compile"] += 1
        by_fn[(r["FunctionName"], "compile")] += 1
    elif "AccessViolation" in fr or "宿主执行故障" in fr or "-1073741819" in fr:
        by_kind["ave"] += 1
        by_fn[(r["FunctionName"], r["PeripheralName"])] += 1
    else:
        by_kind["other"] += 1
        print("OTHER:", r["FunctionName"], fr[:150])
print("by_kind", dict(by_kind))
print("\n=== AVE functions (count) ===")
ave_cnt = Counter(
    (r["FunctionName"], r["PeripheralName"])
    for r in rows
    if "AccessViolation" in (r["FailureReason"] or "") or "宿主执行故障" in (r["FailureReason"] or "")
)
for (fn, peri), n in ave_cnt.most_common(30):
    print(f"  {n}x {fn} ({peri})")
print("\n=== compile errors ===")
for r in rows:
    if "编译失败" in (r["FailureReason"] or ""):
        print(r["FunctionName"], (r["FailureReason"] or "")[:140])
con.close()
