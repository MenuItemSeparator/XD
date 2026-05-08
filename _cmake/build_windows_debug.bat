@echo off
REM Bat file for building XD project in Debug configuration
REM This script must be run from the _cmake folder -DCMAKE_TOOLCHAIN_FILE="%cd%\MinGW32.cmake"

cd /d "%~dp0"
echo Building XD project in Debug configuration...
cmake -G "MinGW Makefiles" -S ./.. -B ./build -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)
echo Build completed successfully!
pause
