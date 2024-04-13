# Here XD tried to select toolchain automatically.
if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
    message(">> Toolset will be selected automatically")
    set(CMAKE_TOOLCHAIN_FILE ${XD_ROOT}/CMake/Toolsets/Windows_Clang_Toolchain.cmake)
    message(">> Selected clang as toolchain")
endif()
