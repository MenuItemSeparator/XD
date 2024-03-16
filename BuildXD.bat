@echo off

set root=%~dp0..
set source_directory=XD
set build_directory=XD_Build
set install_directory=XD_Install
set build_type=Release
set toolchain_file=Windows_GCC_Toolchain.cmake
set cmake_generator="MinGW Makefiles"

echo "==================================================="
echo "===| Cleaning up build and install directories |==="
echo "==================================================="

cd %root%

if exist %build_directory% (
	rmdir %build_directory% /s /q
)

mkdir %build_directory%

cd %root%

if exist %install_directory% (
	rmdir %install_directory% /s /q
)

mkdir %install_directory%

cd %root%/%build_directory%

echo "====================================="
echo "===| Started cmake configuration |==="
echo "====================================="

cmake.exe %root%/%source_directory% ^
-DCMAKE_PREFIX_PATH="%root%/%install_directory%" ^
-DCMAKE_GENERATOR=%cmake_generator% ^
-DCMAKE_BUILD_TYPE=%build_type% ^
-DCMAKE_TOOLCHAIN_FILE="%root%/%source_directory%/CMake/%toolchain_file%"

echo "===================================="
echo "===| Started project generation |==="
echo "===================================="

if %cmake_generator% == "Visual Studio 17 2022" (
	cmake.exe --build %root%/%build_directory% --target ALL_BUILD --config %build_type%
) else (
	cmake.exe --build %root%/%build_directory% --target all --config %build_type%
)

echo "===================================="
echo "===| Started build installation |==="
echo "===================================="

cmake.exe --install . --prefix %root%/%install_directory%