@echo off
REM Script to clean up CMake generated files and folders
REM This will delete all build artifacts and CMake cache
REM First, let CMake clean up after itself, then perform manual cleanup

cd /d "%~dp0"
echo Cleaning CMake build artifacts...

REM Step 1: Let CMake clean up its build artifacts
echo.
echo Step 1: Running CMake clean targets...
if exist *.sln (
    cmake --build . --target clean --config Debug 2>nul
    cmake --build . --target clean --config Release 2>nul
    echo CMake clean completed.
) else (
    echo (CMake not yet configured)
)

REM Step 2: Manual cleanup of remaining CMake files
echo.
echo Step 2: Removing CMake cache and generated files...

REM Delete CMake cache and generated files
if exist CMakeCache.txt del /f /q CMakeCache.txt
if exist cmake_install.cmake del /f /q cmake_install.cmake
if exist generate.stamp del /f /q generate.stamp
if exist generate.stamp.depend del /f /q generate.stamp.depend
if exist generate.stamp.list del /f /q generate.stamp.list

REM Delete CMakeFiles directory
if exist CMakeFiles rmdir /s /q CMakeFiles
echo Deleted CMakeFiles directory

REM Delete Visual Studio project files and filters
if exist *.vcxproj del /f /q *.vcxproj
if exist *.vcxproj.filters del /f /q *.vcxproj.filters
if exist cmake_install.cmake del /f /q cmake_install.cmake
echo Deleted Visual Studio project files

REM Delete build configuration directories
if exist ALL_BUILD.dir rmdir /s /q ALL_BUILD.dir
if exist ZERO_CHECK.dir rmdir /s /q ZERO_CHECK.dir
if exist XD.dir rmdir /s /q XD.dir
echo Deleted build directories

REM Delete platform-specific directories
if exist x64 rmdir /s /q x64
echo Deleted x64 directory

REM Delete solution file
if exist *.sln del /f /q *.sln
echo Deleted solution file

echo.
echo Step 2 completed!
echo.
echo ============================================
echo Cleanup finished in 2 stages:
echo - Stage 1: CMake clean targets executed
echo - Stage 2: Manual cleanup of remaining files
echo ============================================
pause
