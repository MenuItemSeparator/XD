# Here XD tryed to select toolchain automatically.
if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
	message("Toolset will be selected automatically")
        set(CMAKE_TOOLCHAIN_FILE ${XD_ROOT}/CMake/Modules/Toolsets/Windows_Clang_Toolchain.cmake)
endif()
