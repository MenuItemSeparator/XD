@echo off
REM Bat file for building XD project with MinGW 32-bit (Debug)
REM This script must be run from the _cmake folder

cd /d "%~dp0"
echo Cleaning previous build...
if exist build_mingw32_debug rmdir /s /q build_mingw32_debug
echo Building XD project with MinGW 32-bit toolchain (Debug)...
cmake -DCMAKE_TOOLCHAIN_FILE="%cd%\MinGW32.cmake" -S ./.. -B ./build_mingw32_debug
cmake --build ./build_mingw32_debug --config Debug
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)
echo Build completed successfully!
echo Cleaning up...
call clear_all.bat
if exist build_mingw32_debug rmdir /s /q build_mingw32_debug
pause
