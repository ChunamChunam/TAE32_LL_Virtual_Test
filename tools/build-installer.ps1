#Requires -Version 5.1
<#
.SYNOPSIS
  Publish TAE32.LLVirtualTest.App (win-x64 self-contained) and build an Inno Setup installer.

.EXAMPLE
  .\tools\build-installer.ps1
  .\tools\build-installer.ps1 -SkipPublish
  .\tools\build-installer.ps1 -Configuration Release -Version 1.0.0
#>
[CmdletBinding()]
param(
    [string]$Configuration = "Release",
    [string]$Version = "1.0.0",
    [switch]$SkipPublish,
    [switch]$SkipSmokeTest
)

$ErrorActionPreference = "Stop"
$Root = Resolve-Path (Join-Path $PSScriptRoot "..")
$AppProj = Join-Path $Root "src\TAE32.LLVirtualTest.App\TAE32.LLVirtualTest.App.csproj"
# Use a dedicated publish tree so a running desktop instance under .\Publish does not lock files.
$PublishDir = Join-Path $Root "artifacts\publish-win-x64"
$InstallerDir = Join-Path $Root "installer"
$ArtifactsDir = Join-Path $Root "artifacts\installer"
$Iss = Join-Path $InstallerDir "TAE32.LLVirtualTest.iss"
$ExeName = "TAE32.LLVirtualTest.App.exe"

function Find-ISCC {
    $candidates = @(
        (Join-Path $env:LOCALAPPDATA "Programs\Inno Setup 6\ISCC.exe"),
        "C:\Program Files (x86)\Inno Setup 6\ISCC.exe",
        "C:\Program Files\Inno Setup 6\ISCC.exe"
    )
    foreach ($c in $candidates) {
        if (Test-Path $c) { return $c }
    }
    $cmd = Get-Command ISCC.exe -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    return $null
}

Write-Host "==> Root: $Root"

if (-not $SkipPublish) {
    Write-Host "==> Publishing $Configuration win-x64 self-contained to $PublishDir"
    if (Test-Path $PublishDir) {
        Remove-Item $PublishDir -Recurse -Force
    }
    New-Item -ItemType Directory -Force -Path $PublishDir | Out-Null

    & dotnet publish $AppProj `
        -c $Configuration `
        -r win-x64 `
        --self-contained true `
        -p:PublishSingleFile=true `
        -p:IncludeNativeLibrariesForSelfExtract=true `
        -p:EnableCompressionInSingleFile=true `
        -p:DebugType=embedded `
        -p:Version=$Version `
        -p:FileVersion="$Version.0" `
        -o $PublishDir

    if ($LASTEXITCODE -ne 0) {
        throw "dotnet publish failed with exit code $LASTEXITCODE"
    }
}

$appExe = Join-Path $PublishDir $ExeName
if (-not (Test-Path $appExe)) {
    throw "Missing published exe: $appExe (run without -SkipPublish)"
}

$iscc = Find-ISCC
if (-not $iscc) {
    throw "Inno Setup (ISCC.exe) not found. Install with: winget install --id JRSoftware.InnoSetup"
}

New-Item -ItemType Directory -Force -Path $ArtifactsDir | Out-Null
$setupBase = "TAE32.LLVirtualTest-Setup-$Version"
Write-Host "==> Compiling installer with $iscc"
& $iscc `
    "/DMyAppVersion=$Version" `
    "/DPublishDir=$PublishDir" `
    "/DOutputDir=$ArtifactsDir" `
    $Iss

if ($LASTEXITCODE -ne 0) {
    throw "ISCC failed with exit code $LASTEXITCODE"
}

$setupExe = Join-Path $ArtifactsDir "$setupBase.exe"
if (-not (Test-Path $setupExe)) {
    $setupExe = Get-ChildItem $ArtifactsDir -Filter "TAE32.LLVirtualTest-Setup-*.exe" |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}

if (-not $setupExe -or -not (Test-Path $setupExe)) {
    throw "Installer exe not found under $ArtifactsDir"
}

Write-Host "==> Installer ready: $setupExe"
Get-Item $setupExe | Format-List FullName, Length, LastWriteTime

if (-not $SkipSmokeTest) {
    Write-Host "==> Smoke-test: silent install then uninstall"
    $testRoot = Join-Path $env:TEMP "TAE32.LLVirtualTest.InstallSmoke"
    if (Test-Path $testRoot) { Remove-Item $testRoot -Recurse -Force }
    New-Item -ItemType Directory -Force -Path $testRoot | Out-Null

    $logInstall = Join-Path $testRoot "install.log"
    $logUninstall = Join-Path $testRoot "uninstall.log"
    $dest = Join-Path $testRoot "app"

    Write-Host "    Installing to $dest"
    $p = Start-Process -FilePath $setupExe -ArgumentList @(
        "/VERYSILENT",
        "/SUPPRESSMSGBOXES",
        "/NORESTART",
        "/DIR=`"$dest`"",
        "/LOG=`"$logInstall`""
    ) -Wait -PassThru
    if ($p.ExitCode -ne 0) {
        if (Test-Path $logInstall) { Get-Content $logInstall -Tail 40 }
        throw "Silent install failed, exit $($p.ExitCode)"
    }

    $installedExe = Join-Path $dest $ExeName
    if (-not (Test-Path $installedExe)) {
        throw "Install succeeded but exe missing: $installedExe"
    }

    Write-Host "    Launching installed exe (5s smoke)..."
    $app = Start-Process -FilePath $installedExe -PassThru -WorkingDirectory $dest
    Start-Sleep -Seconds 5
    if ($app.HasExited -and $app.ExitCode -ne 0) {
        throw "App exited early with code $($app.ExitCode)"
    }
    if (-not $app.HasExited) {
        Stop-Process -Id $app.Id -Force -ErrorAction SilentlyContinue
        Start-Sleep -Seconds 1
    }
    Write-Host "    App launch smoke OK"

    $uninstallers = Get-ChildItem $dest -Filter "unins*.exe" -ErrorAction SilentlyContinue
    if ($uninstallers) {
        $unins = $uninstallers | Select-Object -First 1
        Write-Host "    Uninstalling via $($unins.Name)"
        $u = Start-Process -FilePath $unins.FullName -ArgumentList @(
            "/VERYSILENT",
            "/SUPPRESSMSGBOXES",
            "/NORESTART",
            "/LOG=`"$logUninstall`""
        ) -Wait -PassThru
        if ($u.ExitCode -ne 0) {
            Write-Warning "Uninstall exit code $($u.ExitCode); see $logUninstall"
        } else {
            Write-Host "    Uninstall OK"
        }
    } else {
        Write-Warning "No unins*.exe found under $dest; skip uninstall smoke"
    }

    Write-Host "==> Smoke test passed"
}

Write-Host "Done."
