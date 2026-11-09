$ErrorActionPreference = 'Stop'

$projectDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectDir = Join-Path $projectDir 'LibraryManagement'

function Find-Compiler {
    $candidates = @(
        'C:\msys64\mingw64\bin\g++.exe',
        'C:\msys64\mingw64\bin\gcc.exe',
        'C:\mingw64\bin\g++.exe',
        'C:\MinGW\bin\g++.exe',
        'C:\tools\mingw64\bin\g++.exe'
    )

    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            return $candidate
        }
    }

    $roots = @(
        'C:\msys64',
        'C:\mingw64',
        'C:\MinGW',
        'C:\tools'
    )

    foreach ($root in $roots) {
        if (Test-Path $root) {
            $hit = Get-ChildItem -Path $root -Recurse -Filter 'g++.exe' -ErrorAction SilentlyContinue | Select-Object -First 1
            if ($hit) {
                return $hit.FullName
            }
        }
    }

    return $null
}

$compiler = Find-Compiler
if (-not $compiler) {
    Write-Host 'C++ compiler not found. Installing MSYS2 + MinGW...' -ForegroundColor Yellow

    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        throw 'winget is not installed or not in PATH. Please install App Installer / winget first.'
    }

    winget install --id MSYS2.MSYS2 -e --accept-source-agreements --accept-package-agreements

    $msysRoot = 'C:\msys64'
    if (-not (Test-Path $msysRoot)) {
        throw "MSYS2 was not installed to $msysRoot. Please install it manually and rerun this script."
    }

    $bash = Join-Path $msysRoot 'usr\bin\bash.exe'
    & $bash -lc 'pacman -S --noconfirm --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make'

    $compiler = Find-Compiler
    if (-not $compiler) {
        throw 'Compiler installation finished but g++ could not be found. Please restart PowerShell and rerun this script.'
    }
}

$compilerDir = Split-Path -Parent $compiler
$userPath = [Environment]::GetEnvironmentVariable('Path', 'User')
if (-not ($userPath -split ';' | Where-Object { $_ -eq $compilerDir })) {
    [Environment]::SetEnvironmentVariable('Path', (($userPath.TrimEnd(';') + ';' + $compilerDir).Trim(';')), 'User')
}

$env:Path = $env:Path + ';' + $compilerDir

Write-Host "Using compiler: $compiler" -ForegroundColor Green

$cmd = @(
    $compiler,
    '-std=c++11',
    '-Wall',
    '-Wextra',
    '-Iinclude',
    '-Iinclude/models',
    '-Iinclude/datastructures',
    '-Iinclude/managers',
    '-Iinclude/ui',
    'src/main.cpp',
    'src/models/Book.cpp',
    'src/datastructures/AVLTree.cpp',
    'src/datastructures/BSTree.cpp',
    'src/managers/LibraryManager.cpp',
    '-o',
    'library_management.exe'
)

Push-Location $projectDir
& $cmd[0] $cmd[1..($cmd.Length-1)]
$buildExit = $LASTEXITCODE
Pop-Location

if ($buildExit -ne 0) {
    throw "Build failed with exit code $buildExit"
}

Write-Host ''
Write-Host 'Build successful. Running program...' -ForegroundColor Green
Push-Location $projectDir
& '.\library_management.exe'
$runExit = $LASTEXITCODE
Pop-Location

exit $runExit
