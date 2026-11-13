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
