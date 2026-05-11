@echo off
REM Bat file for building XD project in Debug configuration
REM This script must be run from the _cmake folder -DCMAKE_TOOLCHAIN_FILE="%cd%\MinGW32.cmake"

cd /d "%~dp0"
echo Building XD project in Debug configuration...
cmake -G "MinGW Makefiles" -S ./.. -B ./build -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b 1
)
echo ============================================
echo Build completed successfully!
echo - Stage 1: Makefiles generated
echo - Stage 2: Exec writed in XD/bin/XD.exe
echo ============================================
call clear_all.bat
if exist build_mingw32_debug rmdir /s /q build_mingw32_debug
if exist Release rmdir /s /q Release
if exist Debug rmdir /s /q Debug
if exist build rmdir /s /q build
