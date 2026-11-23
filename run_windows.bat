@echo off
setlocal
cd /d "%~dp0"
where cmake >nul 2>nul
if errorlevel 1 (
    echo CMake is not installed or is not available in PATH.
    echo Install CMake and a C++17 compiler, such as Visual Studio's Desktop development with C++ workload.
    pause
    exit /b 1
)
cmake -S . -B build
if errorlevel 1 (
    echo Configuration failed. Make sure you have a C++ compiler installed.
    pause
    exit /b 1
)
cmake --build build --config Release
if errorlevel 1 (
    echo Build failed. Review the compiler output above.
    pause
    exit /b 1
)
if exist "build\Release\sudoku.exe" (
    "build\Release\sudoku.exe"
) else if exist "build\sudoku.exe" (
    "build\sudoku.exe"
) else (
    echo Could not locate sudoku.exe after building.
    pause
    exit /b 1
)
echo.
echo Press any key to close this window.
pause >nul
