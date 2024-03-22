if(WIN32)
    set(CMAKE_SYSTEM_NAME Windows)
ELSE()
    message("Unknown platform")
ENDIF()

set(CMAKE_CXX_COMPILER_ID "Clang")

set(CMAKE_C_COMPILER "C:/LLVM/bin/clang.exe")
set(CMAKE_RC_COMPILER "C:/LLVM/bin/clang++.exe")
set(CMAKE_CXX_COMPILER "C:/LLVM/bin/clang++.exe")

set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
