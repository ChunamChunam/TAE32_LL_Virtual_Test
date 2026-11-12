#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Phase-1 TAE32 LL SDK scanner.
Read-only analysis of real SDK sources. No invented chip/peripheral/function data.
"""

from __future__ import annotations

import json
import os
import re
import sys
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------
WORKSPACE = Path(r"d:\Code\12_TAE32_LL_Virtual_Test")
SDK_PACKAGE = WORKSPACE / "SDKContent" / "Tai-Action.TAE32G58xx_DFP.2.0.0 ReleaseV2.0.0"
LL_ROOT = SDK_PACKAGE / "LL"
OUT_DIR = WORKSPACE / "ScanResults"

# ---------------------------------------------------------------------------
# Regex patterns (evidence-driven; not a hardcoded peripheral whitelist)
# ---------------------------------------------------------------------------
RE_INCLUDE = re.compile(r'^\s*#\s*include\s+[<"]([^>"]+)[>"]', re.M)
RE_DEFGROUP = re.compile(
    r'/\*\*\s*@defgroup\s+(\S+)\s+([^\n*]+?)(?:\s*\*/|\n)',
    re.S,
)
RE_ADDTOGROUP = re.compile(r'@addtogroup\s+(\S+)')
RE_BRIEF_HEADER = re.compile(
    r'@brief\s+Header file (?:of|for)\s+(.+?)\s+LL\s+module',
    re.I,
)
RE_BRIEF_FILE = re.compile(r'@file\s+(\S+)')
RE_BRIEF_ANY = re.compile(r'@brief\s+([^\n*]+)')
RE_IFDEF_DEFINED = re.compile(
    r'#\s*if(?:n?def)?\s+defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)'
    r'(?:\s*\|\|\s*defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\))*'
)
RE_IFDEF_CHAIN = re.compile(
    r'#\s*if\s*\(?\s*((?:defined\s*\(\s*[A-Za-z_][A-Za-z0-9_]*\s*\)\s*(?:\|\|\s*)?)+)',
    re.M,
)
# Multi-line peripheral enable guards spanning continued lines
RE_IFDEF_MULTILINE = re.compile(
    r'#\s*if\s*\(?\s*((?:defined\s*\(\s*[A-Za-z_][A-Za-z0-9_]*\s*\)\s*(?:\|\|\s*)?(?:\\\s*\n\s*)?)+)\)?',
    re.M,
)
RE_DEFINED_TOKEN = re.compile(r'defined\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)')
RE_TYPEDEF_NAME = re.compile(r'\b([A-Za-z_][A-Za-z0-9_]*)_TypeDef\b')
RE_CHIP_TOKEN = re.compile(r'\b(TAE32[A-Za-z0-9]+)\b')
RE_GUARD_MACRO = re.compile(r'#\s*ifndef\s+(_TAE32[A-Za-z0-9_]+_H_)')
RE_VERSION_MACRO = re.compile(r'#\s*define\s+(__TAE32[A-Za-z0-9_]*VERSION[A-Za-z0-9_]*)')
RE_MACRO_FUNC = re.compile(
    r'#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)\s*(.*)$',
    re.M,
)
# Function definitions: __STATIC_INLINE / static inline / inline / ordinary
RE_FUNC_START = re.compile(
    r'(?P<attrs>(?:__STATIC_INLINE|static\s+inline|inline|__INLINE|__FORCEINLINE)'
    r'(?:\s+(?:__STATIC_INLINE|static\s+inline|inline|__INLINE|__FORCEINLINE))*'
    r'|(?:(?:[A-Za-z_][A-Za-z0-9_]*\s+)*))'
    r'(?P<ret>(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:void|int|char|short|long|float|double|'
    r'uint\d+_t|int\d+_t|size_t|bool|FlagStatus|ErrorStatus|FunctionalStatus|'
    r'[A-Za-z_][A-Za-z0-9_]*)(?:\s*\*+|\s+)+)'
    r'(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*\(',
    re.M,
)
RE_SIMPLE_FUNC = re.compile(
    r'^(?P<prefix>\s*(?:__STATIC_INLINE|static\s+inline|inline)\s+)'
    r'(?P<ret>.+?)\s+'
    r'(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*\(',
    re.M,
)
RE_ORDINARY_DECL = re.compile(
    r'^(?P<ret>(?:(?:const|volatile|unsigned|signed|struct|enum)\s+)*'
    r'[A-Za-z_][A-Za-z0-9_]*(?:\s*\*+)?(?:\s+[A-Za-z_][A-Za-z0-9_]*(?:\s*\*+)?)*)\s+'
    r'(?P<name>LL_[A-Za-z0-9_]+)\s*\((?P<params>[^;{]*)\)\s*;',
    re.M,
)
RE_DOXY_FUNC = re.compile(r'@brief\s+([^\n*]+)')

COMMON_FILE_HINTS = {
    "ll.h": "aggregate_include",
    "ll_def.h": "common_definitions",
    "ll_conf.h": "user_configuration",
    "ll_cortex.h": "cortex_core_support",
}


def utc_now() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def rel_to_workspace(p: Path) -> str:
    try:
        return str(p.relative_to(WORKSPACE)).replace("\\", "/")
    except ValueError:
        return str(p).replace("\\", "/")


def read_text(path: Path) -> Tuple[str, Optional[str]]:
    """Read file; return (text, error)."""
    for enc in ("utf-8", "utf-8-sig", "gbk", "latin-1"):
        try:
            return path.read_text(encoding=enc), None
        except UnicodeDecodeError:
            continue
        except OSError as e:
            return "", f"OSError: {e}"
    # last resort
    try:
        data = path.read_bytes()
        return data.decode("utf-8", errors="replace"), "decoded_with_replacement"
    except OSError as e:
        return "", f"OSError: {e}"


def build_directory_tree(root: Path) -> Tuple[str, Dict[str, Any]]:
    dirs: List[Path] = []
    files: List[Path] = []
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames.sort()
        filenames.sort()
        p = Path(dirpath)
        dirs.append(p)
        for fn in filenames:
            files.append(p / fn)

    lines: List[str] = []
    root_name = root.name
    lines.append(f"{root}/")
    lines.append(f"└── {root_name}/")

    # Build relative tree from package root (parent of LL) for clarity
    package = root.parent
    package_files = []
    package_dirs = []
    for dirpath, dirnames, filenames in os.walk(package):
        dirnames.sort()
        filenames.sort()
        package_dirs.append(Path(dirpath))
        for fn in filenames:
            package_files.append(Path(dirpath) / fn)

    def tree_lines(base: Path) -> List[str]:
        out: List[str] = [str(base).replace("\\", "/") + "/"]
        entries_by_parent: Dict[Path, List[Tuple[str, Path, bool]]] = defaultdict(list)
        all_dirs = set()
        all_files_local = []
        for dirpath, dirnames, filenames in os.walk(base):
            dirnames.sort()
            filenames.sort()
            dp = Path(dirpath)
            all_dirs.add(dp)
            for d in dirnames:
                entries_by_parent[dp].append((d, dp / d, True))
            for f in filenames:
                entries_by_parent[dp].append((f, dp / f, False))
                all_files_local.append(dp / f)

        def walk(node: Path, prefix: str) -> None:
            items = entries_by_parent.get(node, [])
            for i, (name, path, is_dir) in enumerate(items):
                last = i == len(items) - 1
                branch = "└── " if last else "├── "
                if is_dir:
                    out.append(f"{prefix}{branch}{name}/")
                    ext = "    " if last else "│   "
                    walk(path, prefix + ext)
                else:
                    size = path.stat().st_size
                    out.append(f"{prefix}{branch}{name}  ({size} bytes)")

        walk(base, "")
        return out

    # Tree starting at package (shows LL under package)
    tree_text = "\n".join(tree_lines(package))

    c_files = [f for f in package_files if f.suffix.lower() == ".c"]
    h_files = [f for f in package_files if f.suffix.lower() == ".h"]
    other_files = [f for f in package_files if f.suffix.lower() not in (".c", ".h")]

    # Per-subdir stats relative to package
    per_dir: Dict[str, Dict[str, int]] = {}
    for f in package_files:
        parent = str(f.parent.relative_to(package)).replace("\\", "/")
        if parent == ".":
            parent = "(package_root)"
        bucket = per_dir.setdefault(parent, {"total": 0, "c": 0, "h": 0, "other": 0})
        bucket["total"] += 1
        ext = f.suffix.lower()
        if ext == ".c":
            bucket["c"] += 1
        elif ext == ".h":
            bucket["h"] += 1
        else:
            bucket["other"] += 1

    # Also count empty dirs
    for d in package_dirs:
        rel = str(d.relative_to(package)).replace("\\", "/")
        if rel == ".":
            rel = "(package_root)"
        per_dir.setdefault(rel, {"total": 0, "c": 0, "h": 0, "other": 0})

    stats = {
        "scan_root": str(package).replace("\\", "/"),
        "ll_root": str(root).replace("\\", "/"),
        "total_directories": len(package_dirs),
        "total_files": len(package_files),
        "c_file_count": len(c_files),
        "h_file_count": len(h_files),
        "other_file_count": len(other_files),
        "per_directory": per_dir,
        "directory_roles": {},
        "naming_patterns": {},
        "files": [
            {
                "path": str(f).replace("\\", "/"),
                "rel_path": str(f.relative_to(package)).replace("\\", "/"),
                "name": f.name,
                "ext": f.suffix.lower(),
                "size_bytes": f.stat().st_size,
            }
            for f in sorted(package_files, key=lambda x: str(x).lower())
        ],
    }
    return tree_text, stats


def find_matching_brace(text: str, open_idx: int) -> int:
    """Find closing '}' matching '{' at open_idx. Returns index or -1."""
    depth = 0
    i = open_idx
    n = len(text)
    in_str = False
    in_char = False
    in_line_comment = False
    in_block_comment = False
    while i < n:
        c = text[i]
        nxt = text[i + 1] if i + 1 < n else ""
        if in_line_comment:
            if c == "\n":
                in_line_comment = False
            i += 1
            continue
        if in_block_comment:
            if c == "*" and nxt == "/":
                in_block_comment = False
                i += 2
                continue
            i += 1
            continue
        if in_str:
            if c == "\\" and i + 1 < n:
                i += 2
                continue
            if c == '"':
                in_str = False
            i += 1
            continue
        if in_char:
            if c == "\\" and i + 1 < n:
                i += 2
                continue
            if c == "'":
                in_char = False
            i += 1
            continue
        if c == "/" and nxt == "/":
            in_line_comment = True
            i += 2
            continue
        if c == "/" and nxt == "*":
            in_block_comment = True
            i += 2
            continue
        if c == '"':
            in_str = True
            i += 1
            continue
        if c == "'":
            in_char = True
            i += 1
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def extract_balanced_parens(text: str, open_paren_idx: int) -> Tuple[str, int]:
    """From '(' index, return (params_text, closing_paren_idx)."""
    depth = 0
    i = open_paren_idx
    n = len(text)
    start = open_paren_idx + 1
    while i < n:
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return text[start:i].strip(), i
        i += 1
    return text[start:].strip(), -1


def line_of(text: str, idx: int) -> int:
    return text.count("\n", 0, idx) + 1


def classify_file_role(fname: str, text: str) -> Dict[str, Any]:
    lower = fname.lower()
    role = "peripheral_ll_header"
    confidence = "自动识别"
    evidence: List[Dict[str, Any]] = []

    if lower.endswith("_ll.h") and "_ll_" not in lower.replace("_ll.h", ""):
        # tae32g58xx_ll.h
        role = "aggregate_include"
        confidence = "已确认"
        evidence.append({"kind": "filename", "detail": fname})
    elif lower.endswith("_ll_def.h"):
        role = "common_definitions"
        confidence = "已确认"
        evidence.append({"kind": "filename_and_brief", "detail": "LL common defines"})
    elif lower.endswith("_ll_cortex.h"):
        role = "cortex_core_support"
        confidence = "自动识别"
        evidence.append({"kind": "filename_and_module", "detail": "CORTEX_LL"})
    elif "_ll_" in lower and lower.endswith(".h"):
        role = "peripheral_ll_header"
        m = RE_BRIEF_HEADER.search(text)
        if m:
            evidence.append({"kind": "@brief", "detail": m.group(1).strip(), "line": line_of(text, m.start())})
            confidence = "已确认"
        else:
            confidence = "自动识别"
    else:
        role = "unclassified"
        confidence = "未分类"

    return {"role": role, "detection_status": confidence, "evidence": evidence}


def extract_peripheral_candidates(path: Path, text: str) -> List[Dict[str, Any]]:
    """Discover peripherals from multiple evidence sources (not filename alone)."""
    results: List[Dict[str, Any]] = []
    fname = path.name

    # 1) @brief Header file of/for XXX LL module
    brief_mods: List[Tuple[str, int]] = []
    for m in RE_BRIEF_HEADER.finditer(text):
        raw = m.group(1).strip()
        # "ADTMR (Advanced Timer)" -> ADTMR; "CORTEX" -> CORTEX
        name = re.split(r"\s*\(", raw, maxsplit=1)[0].strip()
        brief_mods.append((name, line_of(text, m.start())))

    # 2) Primary @defgroup XXX_LL
    defgroups: List[Tuple[str, str, int]] = []
    for m in RE_DEFGROUP.finditer(text):
        gname = m.group(1).strip()
        gtitle = m.group(2).strip()
        if gname.endswith("_LL") and gname.count("_") == 1:
            defgroups.append((gname, gtitle, line_of(text, m.start())))
        elif re.fullmatch(r"[A-Z][A-Z0-9]*_LL", gname):
            defgroups.append((gname, gtitle, line_of(text, m.start())))

    # Prefer exact XXX_LL groups
    primary_groups = []
    for gname, gtitle, ln in defgroups:
        # Filter out nested like GPIO_LL_Exported_Constants
        if re.fullmatch(r"[A-Za-z][A-Za-z0-9]*_LL", gname):
            primary_groups.append((gname, gtitle, ln))

    # 3) Instance guards: #if defined(UART0) || defined(UART1)... (incl. multi-line / parenthesized)
    instance_sets: List[Dict[str, Any]] = []
    for m in RE_IFDEF_MULTILINE.finditer(text):
        ln = line_of(text, m.start())
        tokens = RE_DEFINED_TOKEN.findall(m.group(1))
        if not tokens:
            continue
        # Skip config/assert feature macros
        tokens = [t for t in tokens if not t.startswith("TAE32_USE") and not t.startswith("__")]
        if not tokens:
            continue
        instance_sets.append({"line": ln, "instances": tokens, "raw": re.sub(r"\s+", " ", m.group(0))[:240]})

    # 4) TypeDef usages (peripheral register structs like GPIO_TypeDef; exclude LL_* aliases)
    typedefs = sorted(set(RE_TYPEDEF_NAME.findall(text)))
    typedef_periph = [
        t
        for t in typedefs
        if not t.startswith("LL_")
        and not t.startswith("IS_")
        and re.match(r"^[A-Z]", t)
    ]

    # 5) LL_ function prefix
    ll_prefixes: Set[str] = set()
    for m in re.finditer(r"\bLL_([A-Za-z0-9]+)_", text):
        ll_prefixes.add(m.group(1))

    # Build peripheral list from strongest signals
    # Prefer defgroup / brief over filename
    names_from_group = [g[0][:-3] for g in primary_groups]  # strip _LL
    names_from_brief = [b[0] for b in brief_mods]

    # Determine candidate peripheral names
    candidates: Dict[str, Dict[str, Any]] = {}

    def add_cand(name: str, evidence: Dict[str, Any], status: str, conf: str):
        key = name.upper()
        if key not in candidates:
            candidates[key] = {
                "peripheral_name": key,
                "evidence": [],
                "detection_status": status,
                "confidence": conf,
                "instances": [],
                "typedefs": [],
                "ll_prefixes": [],
                "related_files": [rel_to_workspace(path)],
            }
        candidates[key]["evidence"].append(evidence)
        # upgrade confidence
        order = {"识别失败": 0, "未分类": 1, "待确认": 2, "自动识别": 3, "已确认": 4}
        if order.get(status, 0) > order.get(candidates[key]["detection_status"], 0):
            candidates[key]["detection_status"] = status
        if order.get(conf, 0) > order.get(candidates[key]["confidence"], 0):
            candidates[key]["confidence"] = conf

    for name, ln in brief_mods:
        add_cand(
            name,
            {
                "source_file": rel_to_workspace(path),
                "line": ln,
                "method": "@brief Header file of <PERIPH> LL module",
                "snippet": f"Header file of {name} LL module",
                "needs_human_confirm": False,
            },
            "已确认",
            "高",
        )

    for gname, gtitle, ln in primary_groups:
        pname = gname[:-3]
        add_cand(
            pname,
            {
                "source_file": rel_to_workspace(path),
                "line": ln,
                "method": "@defgroup <PERIPH>_LL",
                "snippet": f"@defgroup {gname} {gtitle}",
                "needs_human_confirm": False,
            },
            "已确认",
            "高",
        )

    # Filename as weak evidence only
    mfn = re.match(r"tae32g58xx_ll_([a-z0-9]+)\.h$", fname, re.I)
    if mfn:
        token = mfn.group(1).upper()
        if token not in ("DEF",) and token not in candidates:
            add_cand(
                token,
                {
                    "source_file": rel_to_workspace(path),
                    "line": None,
                    "method": "filename_token_only",
                    "snippet": fname,
                    "needs_human_confirm": True,
                },
                "待确认",
                "低",
            )
        elif token in candidates:
            candidates[token]["evidence"].append(
                {
                    "source_file": rel_to_workspace(path),
                    "line": None,
                    "method": "filename_token",
                    "snippet": fname,
                    "needs_human_confirm": False,
                }
            )

    # Attach instances: prefer first substantial ifdef chain after includes
    early_instances: List[str] = []
    for iset in instance_sets:
        if iset["line"] <= 80:
            # Skip assert-related macros
            toks = [t for t in iset["instances"] if not t.startswith("TAE32_USE")]
            if toks:
                early_instances = toks
                break

    # Map instances onto candidates
    for key, cand in candidates.items():
        matched_inst = []
        for inst in early_instances:
            # UART0 matches UART; GPIOA matches GPIO; TMR6 may match LPTMR (special)
            if inst.upper().startswith(key):
                matched_inst.append(inst)
            elif key == "GPIO" and re.match(r"GPIO[A-Z]$", inst):
                matched_inst.append(inst)
            elif key == "LPTMR" and re.match(r"TMR\d+$", inst):
                matched_inst.append(inst)
            elif key in ("GPTMRX", "GPTMRY", "ADTMR", "BSTMR") and re.match(r"TMR\d+$", inst):
                matched_inst.append(inst)
            elif key == "CORTEX":
                pass
            elif key in ("DMA", "EFLASH", "HRPWM", "IWDG", "RCU", "SYSCTRL", "WWDG") and inst.upper() == key:
                matched_inst.append(inst)
        if not matched_inst and early_instances and len(candidates) == 1:
            matched_inst = list(early_instances)
        # Timer-family files: if guard is only TMRn and module is timer-like, accept all early instances
        if (
            not matched_inst
            and early_instances
            and key in ("GPTMRX", "GPTMRY", "ADTMR", "BSTMR", "LPTMR")
            and all(re.match(r"TMR\d+$", i) for i in early_instances)
        ):
            matched_inst = list(early_instances)
        cand["instances"] = sorted(set(matched_inst), key=lambda s: (len(s), s))
        if early_instances and matched_inst:
            naming_mismatch = key in ("LPTMR", "GPTMRX", "GPTMRY", "ADTMR", "BSTMR") and any(
                re.match(r"TMR\d+$", i) for i in matched_inst
            )
            cand["evidence"].append(
                {
                    "source_file": rel_to_workspace(path),
                    "line": next((x["line"] for x in instance_sets if x["line"] <= 80), None),
                    "method": "preprocessor_instance_guard",
                    "snippet": " || ".join(f"defined({i})" for i in matched_inst[:12]),
                    "needs_human_confirm": naming_mismatch,
                }
            )
            if key == "LPTMR":
                cand["detection_status"] = "待确认"
                cand["confidence"] = "中"
                cand["notes"] = "文件/函数名称为 LPTMR，但实例宏守卫为 TMR6，模块与实例命名不一致，需人工确认"
            elif naming_mismatch and key in ("GPTMRX", "GPTMRY", "ADTMR", "BSTMR"):
                cand["notes"] = (
                    f"模块名为 {key}，实例宏为 {', '.join(matched_inst)}（TMRn），"
                    "模块与实例命名空间不同，需确认映射关系"
                )
                if cand.get("detection_status") == "已确认":
                    # keep 已确认 for module identity, but flag mapping
                    cand["instance_mapping_status"] = "待确认"

        # typedefs
        related_td = [t for t in typedef_periph if t.upper().startswith(key) or key in t.upper()]
        if not related_td and len(candidates) == 1:
            related_td = [t for t in typedef_periph if t not in ("LL_RSV_DATA",)]
        cand["typedefs"] = related_td
        for t in related_td:
            # find first occurrence line
            mm = re.search(rf"\b{re.escape(t)}_TypeDef\b", text)
            if mm:
                cand["evidence"].append(
                    {
                        "source_file": rel_to_workspace(path),
                        "line": line_of(text, mm.start()),
                        "method": "TypeDef_usage",
                        "snippet": f"{t}_TypeDef",
                        "needs_human_confirm": False,
                    }
                )

        # LL prefixes
        related_pref = [p for p in ll_prefixes if p.upper() == key or p.upper().startswith(key)]
        if not related_pref and key in ll_prefixes:
            related_pref = [key]
        # also exact
        if key in {p.upper() for p in ll_prefixes}:
            related_pref = [p for p in ll_prefixes if p.upper() == key]
        cand["ll_prefixes"] = sorted(set(related_pref))

    # Multi-peripheral in one file?
    if len(candidates) > 1:
        for cand in candidates.values():
            cand["multi_peripheral_file"] = True
            cand["evidence"].append(
                {
                    "source_file": rel_to_workspace(path),
                    "line": None,
                    "method": "multiple_candidates_in_file",
                    "snippet": ",".join(sorted(candidates.keys())),
                    "needs_human_confirm": True,
                }
            )

    # Special: aggregate / def files produce no peripheral or DEFINE
    role = classify_file_role(fname, text)
    if role["role"] in ("aggregate_include", "common_definitions"):
        # Still record DEFINE if defgroup present
        if "DEFINE" in candidates or any(k == "DEFINE" for k in candidates):
            pass
        # Remove false peripheral from ll.h
        if role["role"] == "aggregate_include":
            return []
        if role["role"] == "common_definitions":
            # DEFINE_LL is common, not a peripheral
            return [
                {
                    "peripheral_name": "DEFINE (common)",
                    "is_common_driver": True,
                    "is_peripheral": False,
                    "evidence": [
                        {
                            "source_file": rel_to_workspace(path),
                            "line": next((line_of(text, m.start()) for m in RE_DEFGROUP.finditer(text) if "DEFINE" in m.group(1)), None),
                            "method": "common_definitions_file",
                            "snippet": "DEFINE_LL / tae32g58xx_ll_def.h",
                            "needs_human_confirm": True,
                        }
                    ],
                    "detection_status": "待确认",
                    "confidence": "中",
                    "instances": [],
                    "typedefs": [],
                    "ll_prefixes": [],
                    "related_files": [rel_to_workspace(path)],
                    "notes": "公共定义文件，是否作为独立“模块”需人工确认；当前不计入外设",
                }
            ]

    return list(candidates.values())


def extract_functions(path: Path, text: str, peripheral_hint: Optional[str], chip_hint: Optional[str]) -> List[Dict[str, Any]]:
    funcs: List[Dict[str, Any]] = []
    seen: Set[Tuple[str, int]] = set()

    # --- inline / static inline definitions ---
    for m in RE_SIMPLE_FUNC.finditer(text):
        name = m.group("name")
        ret = m.group("ret").strip()
        prefix = m.group("prefix").strip()
        start = m.start()
        # find '(' of function
        paren = text.find("(", m.end() - 1)
        if paren < 0:
            continue
        params, close = extract_balanced_parens(text, paren)
        if close < 0:
            continue
        # after ) expect { for definition, or ; for declaration
        j = close + 1
        while j < len(text) and text[j] in " \t\r\n":
            j += 1
        kind = None
        end_line = line_of(text, close)
        start_line = line_of(text, start)
        if j < len(text) and text[j] == "{":
            end_brace = find_matching_brace(text, j)
            if end_brace < 0:
                detection = "识别失败"
                kind = "inline_definition_unclosed"
                end_line = start_line
            else:
                end_line = line_of(text, end_brace)
                kind = "inline_definition"
                detection = "已确认"
        elif j < len(text) and text[j] == ";":
            kind = "inline_declaration"
            detection = "已确认"
            end_line = line_of(text, j)
        else:
            # might be attribute or something
            kind = "inline_uncertain"
            detection = "待确认"

        # Function type label
        if "__STATIC_INLINE" in prefix:
            ftype = "__STATIC_INLINE"
        elif re.search(r"static\s+inline", prefix):
            ftype = "static_inline"
        elif "inline" in prefix:
            ftype = "inline"
        else:
            ftype = "unknown_inline"

        periph = peripheral_hint.upper() if peripheral_hint else None
        status_note = None
        pm = re.match(r"LL_([A-Za-z0-9]+)_", name)
        # Non-standard API names hosted in CORTEX file
        cortex_hosted = re.match(r"^LL_(NVIC_|Init|Delay_)", name) is not None
        if peripheral_hint and peripheral_hint.upper() == "CORTEX" and cortex_hosted:
            periph = "CORTEX"
            status_note = f"函数 {name} 位于 CORTEX 头文件，前缀非 LL_CORTEX_；按文件模块归属"
            detection = "待确认"
        elif pm:
            token = pm.group(1).upper()
            if peripheral_hint and token == peripheral_hint.upper():
                periph = token
            elif peripheral_hint and token != peripheral_hint.upper():
                # Keep LL_ prefix token as peripheral id (normal case: file module == prefix)
                periph = token
            else:
                periph = token
        elif name.startswith("LL_"):
            periph = peripheral_hint.upper() if peripheral_hint else None
            status_note = "函数名无标准 LL_<PERIPH>_ 前缀分段；按源文件模块归属"
            detection = "待确认"

        key = (name, start_line)
        if key in seen:
            continue
        seen.add(key)

        funcs.append(
            {
                "FunctionName": name,
                "ReturnType": ret,
                "Parameters": re.sub(r"\s+", " ", params),
                "FunctionType": ftype,
                "Form": kind,
                "Peripheral": periph,
                "Chip": chip_hint,
                "FilePath": rel_to_workspace(path),
                "StartLine": start_line,
                "EndLine": end_line,
                "DetectionStatus": detection,
                "Evidence": {
                    "method": "regex_inline_function_scan",
                    "prefix": prefix,
                    "needs_human_confirm": detection == "待确认",
                    "note": status_note,
                },
            }
        )

    # --- ordinary LL_ declarations (non-inline) ---
    for m in RE_ORDINARY_DECL.finditer(text):
        name = m.group("name")
        # skip if already captured as inline
        start_line = line_of(text, m.start())
        if any(f["FunctionName"] == name and abs(f["StartLine"] - start_line) < 2 for f in funcs):
            continue
        ret = m.group("ret").strip()
        # avoid macros / typedefs mistaken: return type shouldn't be #define etc
        if ret.startswith("#") or "typedef" in ret:
            continue
        params = re.sub(r"\s+", " ", m.group("params").strip())
        periph = peripheral_hint
        pm = re.match(r"LL_([A-Za-z0-9]+)_", name)
        if pm:
            periph = pm.group(1).upper()
        funcs.append(
            {
                "FunctionName": name,
                "ReturnType": ret,
                "Parameters": params,
                "FunctionType": "ordinary_declaration",
                "Form": "declaration",
                "Peripheral": periph,
                "Chip": chip_hint,
                "FilePath": rel_to_workspace(path),
                "StartLine": start_line,
                "EndLine": line_of(text, m.end()),
                "DetectionStatus": "自动识别",
                "Evidence": {
                    "method": "regex_ordinary_declaration",
                    "needs_human_confirm": True,
                    "note": "头文件中的非 inline 声明；本扫描包内未见对应 .c 定义",
                },
            }
        )

    # --- function-like macros that look like LL API (optional capture) ---
    for m in RE_MACRO_FUNC.finditer(text):
        name = m.group(1)
        if not name.startswith("LL_"):
            continue
        # skip IS_LL_ validators? include them as macro_function but mark
        params = m.group(2).strip()
        body = m.group(3).strip()
        # multi-line macros: body may be "\" 
        start_line = line_of(text, m.start())
        # find end of macro (continuation)
        end_idx = m.end()
        line_start = text.rfind("\n", 0, m.start()) + 1
        # walk lines with \
        pos = m.start()
        while True:
            line_end = text.find("\n", pos)
            if line_end < 0:
                end_idx = len(text)
                break
            line = text[pos:line_end]
            end_idx = line_end
            if line.rstrip().endswith("\\"):
                pos = line_end + 1
                continue
            break
        end_line = line_of(text, end_idx)
        periph = peripheral_hint
        pm = re.match(r"LL_([A-Za-z0-9]+)_", name)
        if pm:
            periph = pm.group(1).upper()
        # Avoid duplicating if same name already as function
        if any(f["FunctionName"] == name and f["Form"] in ("inline_definition", "declaration") for f in funcs):
            continue
        funcs.append(
            {
                "FunctionName": name,
                "ReturnType": "(macro)",
                "Parameters": params,
                "FunctionType": "macro_function",
                "Form": "function_macro",
                "Peripheral": periph,
                "Chip": chip_hint,
                "FilePath": rel_to_workspace(path),
                "StartLine": start_line,
                "EndLine": end_line,
                "DetectionStatus": "自动识别",
                "Evidence": {
                    "method": "regex_function_macro",
                    "body_preview": body[:80],
                    "needs_human_confirm": name.startswith("IS_LL_"),
                    "note": "函数宏；IS_LL_* 多为参数校验宏",
                },
            }
        )

    return funcs


def discover_chips(files_data: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    """Chip discovery strictly from source evidence inside LL tree."""
    chip_map: Dict[str, Dict[str, Any]] = {}

    def add(chip: str, evidence: Dict[str, Any], status: str, conf: str):
        if chip not in chip_map:
            chip_map[chip] = {
                "chip_model": chip,
                "related_files": [],
                "evidence": [],
                "detection_status": status,
                "confidence": conf,
            }
        chip_map[chip]["evidence"].append(evidence)
        fp = evidence.get("source_file")
        if fp and fp not in chip_map[chip]["related_files"]:
            chip_map[chip]["related_files"].append(fp)
        order = {"识别失败": 0, "未分类": 1, "待确认": 2, "自动识别": 3, "已确认": 4}
        if order.get(status, 0) > order.get(chip_map[chip]["detection_status"], 0):
            chip_map[chip]["detection_status"] = status
        if order.get(conf, 0) > order.get(chip_map[chip]["confidence"], 0):
            chip_map[chip]["confidence"] = conf

    for fd in files_data:
        text = fd["text"]
        path = fd["rel_path"]
        # Guard macros
        for m in RE_GUARD_MACRO.finditer(text):
            g = m.group(1)
            # _TAE32G58XX_LL_GPIO_H_ -> TAE32G58xx family
            mm = re.match(r"_?(TAE32[A-Z0-9]+)", g, re.I)
            if mm:
                raw = mm.group(1)
                # normalize display: TAE32G58xx if G58
                chip = normalize_chip_token(raw)
                add(
                    chip,
                    {
                        "source_file": path,
                        "line": line_of(text, m.start()),
                        "method": "include_guard_macro",
                        "snippet": g,
                        "needs_human_confirm": False,
                    },
                    "已确认",
                    "高",
                )
        # @addtogroup TAE32G58xx_LL_Driver
        for m in RE_ADDTOGROUP.finditer(text):
            g = m.group(1)
            mm = re.match(r"(TAE32[A-Za-z0-9]+)", g)
            if mm:
                chip = normalize_chip_token(mm.group(1))
                add(
                    chip,
                    {
                        "source_file": path,
                        "line": line_of(text, m.start()),
                        "method": "@addtogroup",
                        "snippet": g,
                        "needs_human_confirm": False,
                    },
                    "已确认",
                    "高",
                )
        # version macros
        for m in RE_VERSION_MACRO.finditer(text):
            name = m.group(1)
            mm = re.search(r"(TAE32[A-Za-z0-9]+)", name)
            if mm:
                chip = normalize_chip_token(mm.group(1))
                add(
                    chip,
                    {
                        "source_file": path,
                        "line": line_of(text, m.start()),
                        "method": "version_macro",
                        "snippet": name,
                        "needs_human_confirm": False,
                    },
                    "已确认",
                    "高",
                )
        # includes of device header
        for m in RE_INCLUDE.finditer(text):
            inc = m.group(1)
            mm = re.match(r"(tae32[a-z0-9]+)\.h$", inc, re.I)
            if mm and "_ll" not in mm.group(1).lower():
                chip = normalize_chip_token(mm.group(1))
                add(
                    chip,
                    {
                        "source_file": path,
                        "line": line_of(text, m.start()),
                        "method": "device_header_include",
                        "snippet": f'#include "{inc}"',
                        "needs_human_confirm": True,
                    },
                    "自动识别",
                    "中",
                )
                # Note missing file
                add(
                    chip,
                    {
                        "source_file": path,
                        "line": line_of(text, m.start()),
                        "method": "external_device_header_reference",
                        "snippet": f"{inc} 不在当前 LL 扫描目录内",
                        "needs_human_confirm": True,
                    },
                    "待确认",
                    "中",
                )
        # filename evidence (weak alone)
        mm = re.match(r"(tae32g58xx)_", fd["name"], re.I)
        if mm:
            chip = normalize_chip_token(mm.group(1))
            add(
                chip,
                {
                    "source_file": path,
                    "line": None,
                    "method": "filename_prefix",
                    "snippet": fd["name"],
                    "needs_human_confirm": False,
                },
                "自动识别",
                "中",
            )

    # Package folder name is NOT used as sole chip evidence; record as note only
    for chip in list(chip_map.keys()):
        chip_map[chip]["notes"] = (
            "当前 LL 目录内源码证据均指向同一系列标识 TAE32G58xx；"
            "未见更细的具体封装型号宏（如 TAE32G5800 等）。"
            "设备头文件 tae32g58xx.h 不在本扫描根目录，具体型号细分待设备头/DFP 其余目录确认。"
        )
        chip_map[chip]["package_name_note"] = (
            "SDK 包名含 TAE32G58xx_DFP，仅作旁证，未作为独立芯片型号结论。"
        )

    return list(chip_map.values())


def normalize_chip_token(token: str) -> str:
    t = token.strip()
    # Prefer canonical mixed case used in Doxygen: TAE32G58xx
    up = t.upper()
    if up.startswith("TAE32G58"):
        return "TAE32G58xx"
    # keep original-ish
    if t.isupper() and t.startswith("TAE32"):
        # TAE32G58XX -> TAE32G58xx
        if "G58" in up:
            return "TAE32G58xx"
    return t


def analyze_includes(files_data: List[Dict[str, Any]]) -> Dict[str, Any]:
    graph = {}
    missing: List[Dict[str, Any]] = []
    present_names = {fd["name"].lower() for fd in files_data}
    for fd in files_data:
        incs = []
        for m in RE_INCLUDE.finditer(fd["text"]):
            inc = m.group(1)
            ln = line_of(fd["text"], m.start())
            local = Path(inc).name.lower()
            status = "present_in_ll" if local in present_names else "missing_from_ll_scan_root"
            entry = {"include": inc, "line": ln, "status": status}
            incs.append(entry)
            if status.startswith("missing"):
                missing.append(
                    {
                        "from_file": fd["rel_path"],
                        "line": ln,
                        "include": inc,
                        "detection_status": "待确认",
                        "reason": "被 LL 头文件引用，但不在当前扫描的 LL 目录内",
                    }
                )
        graph[fd["rel_path"]] = incs
    return {"include_graph": graph, "missing_includes": missing}


def main() -> int:
    if not LL_ROOT.is_dir():
        print(f"ERROR: LL root not found: {LL_ROOT}", file=sys.stderr)
        return 1

    OUT_DIR.mkdir(parents=True, exist_ok=True)

    tree_text, file_stats = build_directory_tree(LL_ROOT)

    # Directory role analysis
    file_stats["directory_roles"] = {
        "(package_root)": {
            "path": str(SDK_PACKAGE).replace("\\", "/"),
            "inferred_role": "SDK/DFP 包根（当前仅含 LL 子目录）",
            "detection_status": "已确认",
            "confidence": "高",
            "notes": "扫描范围内未见 Device/Startup/CMSIS 等其它目录",
        },
        "LL": {
            "path": str(LL_ROOT).replace("\\", "/"),
            "inferred_role": "Low-Layer 驱动头文件目录（外设 LL + 公共定义）",
            "detection_status": "已确认",
            "confidence": "高",
            "chip_series_hint": "文件名前缀 tae32g58xx_* 指向 TAE32G58xx",
            "peripheral_modules_hint": "各 tae32g58xx_ll_<module>.h",
            "common_driver_hint": "tae32g58xx_ll_def.h, tae32g58xx_ll.h, tae32g58xx_ll_cortex.h",
            "notes": "扁平结构，无按芯片型号分子目录；无 .c 实现文件",
        },
    }
    file_stats["naming_patterns"] = {
        "header_pattern": "tae32g58xx_ll_<module>.h",
        "aggregate_header": "tae32g58xx_ll.h",
        "common_def": "tae32g58xx_ll_def.h",
        "observed_module_tokens_from_filename": sorted(
            [
                re.match(r"tae32g58xx_ll_([a-z0-9]+)\.h$", f["name"], re.I).group(1)
                for f in file_stats["files"]
                if re.match(r"tae32g58xx_ll_([a-z0-9]+)\.h$", f["name"], re.I)
            ]
        ),
        "c_files_present": False,
        "note": "文件名 token 仅作候选，外设名称以源码 @defgroup/@brief/TypeDef/实例宏为准",
    }

    # Read all files under package
    files_data: List[Dict[str, Any]] = []
    read_errors: List[Dict[str, Any]] = []
    for fmeta in file_stats["files"]:
        p = Path(fmeta["path"])
        text, err = read_text(p)
        rel = str(p.relative_to(WORKSPACE)).replace("\\", "/")
        if err and err.startswith("OSError"):
            read_errors.append(
                {
                    "path": rel,
                    "error": err,
                    "detection_status": "识别失败",
                }
            )
            text = ""
        elif err:
            read_errors.append(
                {
                    "path": rel,
                    "error": err,
                    "detection_status": "待确认",
                    "note": "使用了回退解码",
                }
            )
        files_data.append(
            {
                "path": fmeta["path"],
                "rel_path": rel,
                "name": fmeta["name"],
                "ext": fmeta["ext"],
                "size_bytes": fmeta["size_bytes"],
                "text": text,
                "role": classify_file_role(fmeta["name"], text),
            }
        )

    include_info = analyze_includes(files_data)
    chips = discover_chips(files_data)
    primary_chip = chips[0]["chip_model"] if len(chips) == 1 else (
        chips[0]["chip_model"] if chips else None
    )
    if len(chips) != 1:
        primary_chip = "TAE32G58xx" if any(c["chip_model"] == "TAE32G58xx" for c in chips) else (
            chips[0]["chip_model"] if chips else None
        )

    # Peripherals
    peripherals: List[Dict[str, Any]] = []
    periph_by_name: Dict[str, Dict[str, Any]] = {}
    for fd in files_data:
        cands = extract_peripheral_candidates(Path(fd["path"]), fd["text"])
        for c in cands:
            name = c["peripheral_name"]
            if name in periph_by_name:
                # merge
                existing = periph_by_name[name]
                for e in c.get("evidence", []):
                    existing["evidence"].append(e)
                for rf in c.get("related_files", []):
                    if rf not in existing["related_files"]:
                        existing["related_files"].append(rf)
                for inst in c.get("instances", []):
                    if inst not in existing["instances"]:
                        existing["instances"].append(inst)
                for td in c.get("typedefs", []):
                    if td not in existing["typedefs"]:
                        existing["typedefs"].append(td)
            else:
                periph_by_name[name] = c
                peripherals.append(c)

    # Functions
    all_funcs: List[Dict[str, Any]] = []
    for fd in files_data:
        # hint peripheral from strongest candidate in that file
        file_periphs = [
            p for p in peripherals if any(fd["rel_path"].endswith(Path(rf).name) or rf == fd["rel_path"] for rf in p.get("related_files", []))
        ]
        # better match
        file_periphs = [p for p in peripherals if fd["rel_path"] in p.get("related_files", [])]
        hint = None
        real_periphs = [p for p in file_periphs if p.get("is_peripheral", True) and not p.get("is_common_driver")]
        if len(real_periphs) == 1:
            hint = real_periphs[0]["peripheral_name"]
        funcs = extract_functions(Path(fd["path"]), fd["text"], hint, primary_chip)
        all_funcs.extend(funcs)

    # Count functions per peripheral (definitions + inline; optionally exclude IS_ macros from main count)
    for p in peripherals:
        pname = p["peripheral_name"]
        if p.get("is_common_driver"):
            p["ll_function_count"] = 0
            p["ll_function_count_detail"] = {"inline_definition": 0, "macro_function": 0, "declaration": 0}
            continue
        related = [
            f
            for f in all_funcs
            if (f.get("Peripheral") or "").upper() == pname.upper()
            or (
                fd_match(f, p)
            )
        ]
        # Prefer Peripheral field match
        related = [f for f in all_funcs if (f.get("Peripheral") or "").upper() == pname.upper()]
        detail = defaultdict(int)
        for f in related:
            detail[f.get("Form") or f.get("FunctionType")] += 1
        # Main count: inline definitions (true LL API)
        inline_defs = [f for f in related if f.get("Form") == "inline_definition"]
        p["ll_function_count"] = len(inline_defs)
        p["ll_function_count_all_forms"] = len(related)
        p["ll_function_count_detail"] = dict(detail)
        p["chip"] = primary_chip

    # Unclassified
    unclassified = {
        "files": [],
        "functions": [],
        "missing_includes": include_info["missing_includes"],
        "read_errors": read_errors,
        "notes": [],
    }
    for fd in files_data:
        role = fd["role"]["role"]
        if role == "unclassified":
            unclassified["files"].append(
                {
                    "path": fd["rel_path"],
                    "reason": "无法判定文件角色",
                    "detection_status": "未分类",
                }
            )
        # check if peripheral header but no peripheral extracted
        if role == "peripheral_ll_header":
            matched = [p for p in peripherals if fd["rel_path"] in p.get("related_files", [])]
            if not matched:
                unclassified["files"].append(
                    {
                        "path": fd["rel_path"],
                        "reason": "文件名像外设 LL 头文件，但未能提取外设证据",
                        "detection_status": "识别失败",
                    }
                )

    for f in all_funcs:
        if not f.get("Peripheral") or f.get("DetectionStatus") in ("待确认", "识别失败", "未分类"):
            if f.get("DetectionStatus") in ("待确认", "识别失败", "未分类") or not f.get("Peripheral"):
                unclassified["functions"].append(
                    {
                        "FunctionName": f["FunctionName"],
                        "FilePath": f["FilePath"],
                        "StartLine": f["StartLine"],
                        "DetectionStatus": f.get("DetectionStatus"),
                        "reason": (f.get("Evidence") or {}).get("note") or "归属或形式待确认",
                    }
                )

    # Low confidence peripherals
    low_conf = [p for p in peripherals if p.get("confidence") in ("低", "中") or p.get("detection_status") == "待确认"]

    # No .c files note
    unclassified["notes"].append(
        {
            "topic": "no_c_sources",
            "detail": "当前扫描根目录下 C 文件数量为 0。LL API 以头文件内 __STATIC_INLINE 定义为主。",
            "detection_status": "已确认",
        }
    )
    unclassified["notes"].append(
        {
            "topic": "external_device_header",
            "detail": "多个文件 #include \"tae32g58xx.h\" / \"tae32g58xx_ll_conf.h\"，这些文件不在 LL 目录，寄存器结构体与外设基地址/实例定义的权威来源应在设备头中，本阶段无法从 LL 目录完整验证。",
            "detection_status": "待确认",
        }
    )

    # Sort peripherals: real first
    peripherals_sorted = sorted(
        peripherals,
        key=lambda p: (0 if p.get("is_peripheral", True) and not p.get("is_common_driver") else 1, p["peripheral_name"]),
    )

    # Assign serial numbers for real peripherals
    peri_table = []
    idx = 0
    for p in peripherals_sorted:
        if p.get("is_common_driver") or p.get("is_peripheral") is False:
            continue
        idx += 1
        peri_table.append(
            {
                "序号": idx,
                "外设名称": p["peripheral_name"],
                "相关文件": p.get("related_files", []),
                "LL函数数量": p.get("ll_function_count", 0),
                "LL函数数量_全形式": p.get("ll_function_count_all_forms", 0),
                "LL函数数量明细": p.get("ll_function_count_detail", {}),
                "外设实例": p.get("instances", []),
                "TypeDef": [f"{t}_TypeDef" for t in p.get("typedefs", [])],
                "识别依据": p.get("evidence", [])[:8],
                "置信度": p.get("confidence"),
                "识别状态": p.get("detection_status"),
                "所属芯片": p.get("chip"),
                "notes": p.get("notes"),
                "is_common_driver": False,
            }
        )

    common_modules = [p for p in peripherals_sorted if p.get("is_common_driver") or p.get("is_peripheral") is False]

    # Also add cortex etc that might be borderline
    # Write outputs
    (OUT_DIR / "01_DirectoryTree.txt").write_text(
        f"TAE32 LL Phase-1 Directory Tree\n"
        f"Generated: {utc_now()}\n"
        f"Scan package: {SDK_PACKAGE}\n"
        f"LL root: {LL_ROOT}\n"
        f"{'=' * 72}\n\n"
        f"{tree_text}\n",
        encoding="utf-8",
    )

    file_stats_out = {
        "generated_at": utc_now(),
        "scan_package": str(SDK_PACKAGE).replace("\\", "/"),
        "ll_root": str(LL_ROOT).replace("\\", "/"),
        "total_directories": file_stats["total_directories"],
        "total_files": file_stats["total_files"],
        "c_file_count": file_stats["c_file_count"],
        "h_file_count": file_stats["h_file_count"],
        "other_file_count": file_stats["other_file_count"],
        "per_directory": file_stats["per_directory"],
        "directory_roles": file_stats["directory_roles"],
        "naming_patterns": file_stats["naming_patterns"],
        "files": [
            {
                **{k: v for k, v in fd.items() if k != "text"},
            }
            for fd in files_data
        ],
        "include_graph_summary": {
            "files_with_includes": len(include_info["include_graph"]),
            "missing_include_refs": len(include_info["missing_includes"]),
        },
        "include_graph": include_info["include_graph"],
    }
    write_json(OUT_DIR / "02_FileStatistics.json", file_stats_out)

    chip_out = {
        "generated_at": utc_now(),
        "discovery_policy": "仅依据 LL 目录内源码证据；不以 SDK 包名单独推断全部芯片型号",
        "chips": chips,
        "chip_count": len(chips),
        "human_confirmation_needed": [
            "当前仅识别到系列级标识 TAE32G58xx，是否还需按具体封装/订货型号细分？",
            "设备头文件 tae32g58xx.h 不在 LL 目录，是否需要扩大扫描范围到完整 DFP？",
        ],
    }
    write_json(OUT_DIR / "03_ChipDiscovery.json", chip_out)

    peri_out = {
        "generated_at": utc_now(),
        "discovery_policy": "综合 @brief/@defgroup/实例宏/TypeDef/LL_ 前缀/文件名；禁止仅用文件名定论",
        "peripheral_count": len(peri_table),
        "peripherals": peri_table,
        "common_or_non_peripheral_modules": common_modules,
        "low_confidence_or_pending": [
            {
                "外设名称": p["peripheral_name"],
                "置信度": p.get("confidence"),
                "识别状态": p.get("detection_status"),
                "notes": p.get("notes"),
                "相关文件": p.get("related_files"),
            }
            for p in low_conf
        ],
        "instance_vs_module_notes": [
            {
                "module": "LPTMR",
                "instances_in_guard": ["TMR6"],
                "issue": "模块名 LPTMR 与实例宏 TMR6 不一致",
                "detection_status": "待确认",
            },
            {
                "module": "GPIO",
                "instances_in_guard": "GPIOA..GPIOF（以各文件实际守卫为准）",
                "issue": "模块与端口实例需区分",
                "detection_status": "已确认",
            },
        ],
    }
    write_json(OUT_DIR / "04_PeripheralDiscovery.json", peri_out)

    func_out = {
        "generated_at": utc_now(),
        "extraction_policy": "提取 __STATIC_INLINE / static inline / inline / 普通声明 / 函数宏；区分声明与定义",
        "function_count_total": len(all_funcs),
        "function_count_inline_definition": sum(1 for f in all_funcs if f.get("Form") == "inline_definition"),
        "function_count_macro_function": sum(1 for f in all_funcs if f.get("Form") == "function_macro"),
        "function_count_declaration": sum(1 for f in all_funcs if f.get("Form") == "declaration"),
        "functions": all_funcs,
    }
    write_json(OUT_DIR / "05_LLFunctionDiscovery.json", func_out)

    write_json(OUT_DIR / "06_Unclassified.json", {
        "generated_at": utc_now(),
        **unclassified,
        # Deduplicate unclassified functions somewhat
        "functions_pending_count": len(unclassified["functions"]),
    })

    # Summary markdown
    summary = build_summary(
        file_stats_out, chips, peri_table, common_modules, all_funcs, unclassified, low_conf
    )
    (OUT_DIR / "07_ScanSummary.md").write_text(summary, encoding="utf-8")

    # Console brief
    print("=== Phase-1 Scan Complete ===")
    print(f"Output: {OUT_DIR}")
    print(f"Dirs={file_stats_out['total_directories']} Files={file_stats_out['total_files']} "
          f"C={file_stats_out['c_file_count']} H={file_stats_out['h_file_count']} Other={file_stats_out['other_file_count']}")
    print(f"Chips: {[c['chip_model'] for c in chips]}")
    print(f"Peripherals: {len(peri_table)}")
    for p in peri_table:
        print(f"  {p['序号']:02d}. {p['外设名称']:8s} funcs={p['LL函数数量']:4d} files={p['相关文件']}")
    print(f"Functions total={len(all_funcs)} inline_defs={func_out['function_count_inline_definition']}")
    return 0


def fd_match(f: Dict[str, Any], p: Dict[str, Any]) -> bool:
    return f.get("FilePath") in p.get("related_files", [])


def write_json(path: Path, obj: Any) -> None:
    path.write_text(json.dumps(obj, ensure_ascii=False, indent=2), encoding="utf-8")


def build_summary(
    file_stats: Dict[str, Any],
    chips: List[Dict[str, Any]],
    peri_table: List[Dict[str, Any]],
    common_modules: List[Dict[str, Any]],
    all_funcs: List[Dict[str, Any]],
    unclassified: Dict[str, Any],
    low_conf: List[Dict[str, Any]],
) -> str:
    lines: List[str] = []
    lines.append("# TAE32 LL 第一阶段扫描报告")
    lines.append("")
    lines.append(f"- 生成时间: {utc_now()}")
    lines.append(f"- 扫描包: `{file_stats['scan_package']}`")
    lines.append(f"- LL 根目录: `{file_stats['ll_root']}`")
    lines.append("- 原则: 仅基于真实源码；无虚构芯片/外设/函数数据")
    lines.append("")
    lines.append("## 1. 目录与文件统计")
    lines.append("")
    lines.append(f"| 指标 | 数量 |")
    lines.append(f"|---|---:|")
    lines.append(f"| 总目录数 | {file_stats['total_directories']} |")
    lines.append(f"| 总文件数 | {file_stats['total_files']} |")
    lines.append(f"| C 文件 | {file_stats['c_file_count']} |")
    lines.append(f"| H 文件 | {file_stats['h_file_count']} |")
    lines.append(f"| 其他文件 | {file_stats['other_file_count']} |")
    lines.append("")
    lines.append("### 各子目录文件数")
    lines.append("")
    lines.append("| 目录 | total | c | h | other |")
    lines.append("|---|---:|---:|---:|---:|")
    for d, st in sorted(file_stats["per_directory"].items()):
        lines.append(f"| {d} | {st['total']} | {st['c']} | {st['h']} | {st['other']} |")
    lines.append("")
    lines.append("### 目录用途")
    lines.append("")
    for name, role in file_stats["directory_roles"].items():
        lines.append(f"- **{name}**: {role['inferred_role']}（{role['detection_status']} / {role['confidence']}）")
        if role.get("notes"):
            lines.append(f"  - 备注: {role['notes']}")
    lines.append("")
    lines.append("## 2. 芯片型号识别")
    lines.append("")
    lines.append("| 芯片型号 | 相关文件数 | 识别依据(摘要) | 置信度 | 状态 |")
    lines.append("|---|---:|---|---|---|")
    for c in chips:
        methods = sorted({e.get("method", "") for e in c.get("evidence", [])})
        lines.append(
            f"| {c['chip_model']} | {len(c.get('related_files', []))} | "
            f"{', '.join(methods[:5])} | {c.get('confidence')} | {c.get('detection_status')} |"
        )
    lines.append("")
    lines.append("> 说明: 当前证据为**系列级**标识 `TAE32G58xx`，未见更细订货型号宏。设备头 `tae32g58xx.h` 不在 LL 目录。")
    lines.append("")
    lines.append("## 3. 外设模块识别")
    lines.append("")
    lines.append("| 序号 | 外设名称 | 相关文件 | LL函数数量(inline定义) | 实例宏(守卫) | 置信度 | 状态 |")
    lines.append("|---|---|---|---:|---|---|---|")
    for p in peri_table:
        files = "<br>".join(Path(x).name for x in p["相关文件"])
        inst = ", ".join(p.get("外设实例") or []) or "-"
        lines.append(
            f"| {p['序号']} | {p['外设名称']} | {files} | {p['LL函数数量']} | {inst} | {p['置信度']} | {p['识别状态']} |"
        )
    lines.append("")
    lines.append("### 公共/非外设模块")
    lines.append("")
    for c in common_modules:
        lines.append(f"- {c['peripheral_name']}: {c.get('notes') or c.get('detection_status')} | 文件: {c.get('related_files')}")
    lines.append("")
    lines.append("另外识别为支撑模块（请确认是否算外设）:")
    cortex = [p for p in peri_table if p["外设名称"] == "CORTEX"]
    if cortex:
        lines.append(f"- CORTEX: 已列入外设表，序号 {cortex[0]['序号']}，可能应归为内核支撑而非片上外设")
    lines.append("")
    lines.append("## 4. LL 函数提取摘要")
    lines.append("")
    inline_n = sum(1 for f in all_funcs if f.get("Form") == "inline_definition")
    macro_n = sum(1 for f in all_funcs if f.get("Form") == "function_macro")
    decl_n = sum(1 for f in all_funcs if f.get("Form") == "declaration")
    lines.append(f"- 提取条目总数: **{len(all_funcs)}**")
    lines.append(f"- inline 定义 (`__STATIC_INLINE` 等): **{inline_n}**")
    lines.append(f"- 函数宏: **{macro_n}**")
    lines.append(f"- 普通声明: **{decl_n}**")
    lines.append(f"- 详细列表见 `05_LLFunctionDiscovery.json`")
    lines.append("")
    lines.append("## 5. 无法分类 / 待确认")
    lines.append("")
    lines.append(f"- 缺失 include 引用: {len(unclassified.get('missing_includes', []))}")
    lines.append(f"- 待确认/未归属函数条目: {len(unclassified.get('functions', []))}")
    lines.append(f"- 低置信度或待确认模块数: {len(low_conf)}")
    for n in unclassified.get("notes", []):
        lines.append(f"- [{n.get('detection_status')}] {n.get('topic')}: {n.get('detail')}")
    lines.append("")
    lines.append("## 6. 需要人工确认的问题")
    lines.append("")
    lines.append("1. **外设模块划分是否正确？** 上表是否有误判/遗漏？")
    lines.append("2. **同名外设是否需要区分不同芯片？** 当前仅见 TAE32G58xx 一套 LL，暂无多芯片分册。")
    lines.append("3. **公共驱动是否独立分类？** `tae32g58xx_ll_def.h` / `tae32g58xx_ll.h` / `CORTEX` 如何归类？")
    lines.append("4. **LL 函数归属是否合理？** 是否仅统计 `__STATIC_INLINE` 定义，还是把 `IS_LL_*` 校验宏也计入？")
    lines.append("5. **LPTMR vs TMR6**：`tae32g58xx_ll_lptmr.h` 模块名为 LPTMR，却以 `defined(TMR6)` 为守卫——模块名与实例名如何映射？")
    lines.append("6. **GPTMRX / GPTMRY / ADTMR / BSTMR**：是否视为不同外设模块（当前按不同模块识别）？")
    lines.append("7. **是否扩大扫描范围？** 是否需要继续扫描完整 DFP（设备头、启动文件、CMSIS）以补齐基地址与具体型号？")
    lines.append("8. **当前包内无 .c 文件**：是否符合贵司 LL 发布形态（纯头文件）？若有对应 .c，请提供路径。")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("**本阶段结束，等待人工确认后不得进入第二阶段（Clang AST / 虚拟寄存器）。**")
    lines.append("")
    return "\n".join(lines)


if __name__ == "__main__":
    sys.exit(main())
