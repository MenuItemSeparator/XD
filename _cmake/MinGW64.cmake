# CMake Toolchain for MinGW 64-bit
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=_cmake/MinGW64.cmake ..

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Set MinGW installation path
set(MINGW_ROOT "C:/MinGWx64")

# Specify the cross compiler
set(CMAKE_C_COMPILER "${MINGW_ROOT}/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "${MINGW_ROOT}/bin/g++.exe")
set(CMAKE_RC_COMPILER "${MINGW_ROOT}/bin/windres.exe")
set(CMAKE_AR "${MINGW_ROOT}/bin/ar.exe")
set(CMAKE_RANLIB "${MINGW_ROOT}/bin/ranlib.exe")

# Configure compiler flags
set(CMAKE_C_FLAGS "-m64" CACHE STRING "C compiler flags")
set(CMAKE_CXX_FLAGS "-m64" CACHE STRING "C++ compiler flags")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-m64 -static" CACHE STRING "Linker flags for executables")
set(CMAKE_SHARED_LINKER_FLAGS "-m64" CACHE STRING "Linker flags for shared libraries")
set(CMAKE_MODULE_LINKER_FLAGS "-m64" CACHE STRING "Linker flags for modules")

# Skip compiler checks for cross-compilation
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Search for programs, libraries and include files
set(CMAKE_FIND_ROOT_PATH "${MINGW_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
