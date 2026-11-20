; TAE32 LL Virtual Test — Inno Setup 6 installer
; Built from artifacts\publish-win-x64\ (self-contained win-x64). Run tools\build-installer.ps1.

#define MyAppName "TAE32 LL Virtual Test"
#ifndef MyAppVersion
  #define MyAppVersion "1.0.0"
#endif
#define MyAppPublisher "Tai-Action"
#define MyAppExeName "TAE32.LLVirtualTest.App.exe"
#define MyNativeExeName "TAE32.LLVirtualTest.NativeRunner.exe"
#define MyLocalDataDir "TAE32.LLVirtualTest"
#ifndef PublishDir
  #define PublishDir "..\artifacts\publish-win-x64"
#endif
#ifndef OutputDir
  #define OutputDir "..\artifacts\installer"
#endif

[Setup]
AppId={{A3F7C2E1-9B4D-4E8A-9F21-6D5C8B0A1E32}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
; Matches SingleInstanceGuard mutex (Local\…) so Setup/Uninstall detect a running instance.
AppMutex=Local\TAE32.LLVirtualTest.App.SingleInstance
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
OutputDir={#OutputDir}
OutputBaseFilename=TAE32.LLVirtualTest-Setup-{#MyAppVersion}
SetupIconFile=App.ico
UninstallDisplayIcon={app}\{#MyAppExeName}
Compression=lzma2/max
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=admin
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
MinVersion=10.0
; force = terminate processes holding files under {app} (not only soft close).
CloseApplications=force
CloseApplicationsFilter=*.exe
RestartApplications=no
DisableDirPage=no
InfoBeforeFile=
LicenseFile=
UninstallDisplayName={#MyAppName}

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "chinesesimplified"; MessagesFile: "ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Entire publish folder (single-file app + NativeRunner sibling + clang runtimes / content)
Source: "{#PublishDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\{#MyAppExeName}"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

; Runtime-created files are not in the install log — delete them explicitly on uninstall.
[UninstallDelete]
; SQLite / logs / scan cache beside the exe
Type: filesandordirs; Name: "{app}\data"
Type: filesandordirs; Name: "{app}\*.pdb"
Type: filesandordirs; Name: "{app}\*.log"
; Anything left under install dir (then remove empty root)
Type: filesandordirs; Name: "{app}\*"
Type: dirifempty; Name: "{app}"
; LocalAppData: chipaddr cache, reports, embedded Clang toolchain
Type: filesandordirs; Name: "{localappdata}\{#MyLocalDataDir}"

[Code]
procedure KillAppProcesses();
var
  ResultCode: Integer;
begin
  { /T = kill child tree (NativeRunner spawned by the app). Ignore non-zero if not running. }
  Exec('taskkill.exe', '/F /IM "{#MyAppExeName}" /T', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
  Exec('taskkill.exe', '/F /IM "{#MyNativeExeName}" /T', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
  Sleep(600);
end;

procedure CleanupTempRuntimeDirs();
var
  ResultCode: Integer;
  Cmd: string;
begin
  { Temp work dirs created during tests / parse / native host. }
  Cmd :=
    'Remove-Item -LiteralPath (Join-Path $env:TEMP ''tae32_ll_test_work'') -Recurse -Force -ErrorAction SilentlyContinue; ' +
    'Remove-Item -LiteralPath (Join-Path $env:TEMP ''tae32_ll_parse_bridge'') -Recurse -Force -ErrorAction SilentlyContinue; ' +
    'Get-ChildItem -LiteralPath $env:TEMP -Directory -Filter ''tae32_ll_native_*'' -ErrorAction SilentlyContinue | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue; ' +
    'Get-ChildItem -LiteralPath $env:TEMP -Directory -Filter ''tae32_ll_*'' -ErrorAction SilentlyContinue | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue';
  Exec('powershell.exe',
    '-NoProfile -NonInteractive -ExecutionPolicy Bypass -Command "' + Cmd + '"',
    '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
end;

function InitializeSetup(): Boolean;
begin
  KillAppProcesses();
  Result := True;
end;

function PrepareToInstall(var NeedsRestart: Boolean): String;
begin
  { Upgrade path: force-close before replacing locked binaries. }
  KillAppProcesses();
  NeedsRestart := False;
  Result := '';
end;

function InitializeUninstall(): Boolean;
begin
  { Running app must not block uninstall — force close, do not wait for user. }
  KillAppProcesses();
  Result := True;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usUninstall then
  begin
    KillAppProcesses();
  end;
  if CurUninstallStep = usPostUninstall then
  begin
    CleanupTempRuntimeDirs();
    { Belt-and-suspenders: LocalAppData may survive if UninstallDelete raced with a locked file. }
    if DirExists(ExpandConstant('{localappdata}\{#MyLocalDataDir}')) then
      DelTree(ExpandConstant('{localappdata}\{#MyLocalDataDir}'), True, True, True);
    if DirExists(ExpandConstant('{app}')) then
      DelTree(ExpandConstant('{app}'), True, True, True);
  end;
end;
