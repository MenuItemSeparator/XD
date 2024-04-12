if(WIN32)
    set(CMAKE_SYSTEM_NAME Windows)
    add_definitions(-DXD_PLATFORM_WINDOWS)
    add_definitions(-D_X86_)

ELSE()
    message("Unknown platform")
ENDIF()

set(CMAKE_CXX_COMPILER_ID "Clang")
add_compile_options("-fno-rtti" "-fno-exceptions")

set(CMAKE_C_COMPILER "C:/LLVM/bin/clang.exe")
set(CMAKE_RC_COMPILER "C:/LLVM/bin/clang++.exe")
set(CMAKE_CXX_COMPILER "C:/LLVM/bin/clang++.exe")

set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_LINKER_WRAPPER_FLAG "LINKER:")
