# Here XD tryed to select toolchain automatically.
if(${CMAKE_TOOLCHAIN_FILE} NOT EXISTS)
	message("Toolset will be selected automatically")
	set(CMAKE_TOOLCHAIN_FILE Windows_Clang_Toolchain.cmake)
endif()
