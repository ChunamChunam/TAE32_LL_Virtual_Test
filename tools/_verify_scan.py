# -*- coding: utf-8 -*-
import json
from pathlib import Path
from collections import Counter

p = Path(r"d:\Code\12_TAE32_LL_Virtual_Test\ScanResults")
peri = json.loads((p / "04_PeripheralDiscovery.json").read_text(encoding="utf-8"))
for x in peri["peripherals"]:
    print(
        f"{x['序号']:02d} {x['外设名称']:8s} inline={x['LL函数数量']:4d} "
        f"inst={x.get('外设实例')} td={x.get('TypeDef')} "
        f"status={x['识别状态']} conf={x['置信度']}"
    )
print("--- common ---")
for c in peri["common_or_non_peripheral_modules"]:
    print(c["peripheral_name"], c.get("detection_status"), c.get("notes"))
funcs = json.loads((p / "05_LLFunctionDiscovery.json").read_text(encoding="utf-8"))
print("Form", Counter(f.get("Form") for f in funcs["functions"]))
print("Status", Counter(f.get("DetectionStatus") for f in funcs["functions"]))
cs = [f for f in funcs["functions"] if "cortex" in f["FilePath"].lower()]
print("cortex entries", len(cs), Counter(f.get("Peripheral") for f in cs))
gs = [f for f in funcs["functions"] if f["Peripheral"] == "GPIO" and f["Form"] == "inline_definition"][:2]
print("gpio sample", gs)
unc = json.loads((p / "06_Unclassified.json").read_text(encoding="utf-8"))
print("missing includes", len(unc["missing_includes"]))
print("pending funcs", len(unc["functions"]))
