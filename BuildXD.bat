@echo off

set root=%~dp0..

::Folder structure variables
set source_directory=XD
set build_directory=XD_Build
set install_directory=XD_Install

::CMake configuration variables
set build_type=Debug
set toolchain_file=Windows_Clang_Toolchain.cmake
set cmake_generator_path=C:/Ninja/ninja.exe
set cmake_generator="Ninja"

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
-DCMAKE_PREFIX_PATH="%root%/XD" ^
-DCMAKE_INSTALL_PREFIX="%root%/%install_directory%" ^
-DCMAKE_MAKE_PROGRAM=%cmake_generator_path% ^
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
echo "===|      Started XD tests      |==="
echo "===================================="

ctest --test-dir ./Engine/Tests/. --extra-verbose

echo "===================================="
echo "===| Started build installation |==="
echo "===================================="
echo "Installing to " %root%/%install_directory%

cmake.exe --install . --prefix %root%\\%install_directory%


%root%\\%install_directory%\\XDGame\\XDGame.exe