if(WIN32)
    set(CMAKE_SYSTEM_NAME Windows)
ELSE()
    message("Unknown platform")
ENDIF()

set(CMAKE_C_COMPILER "C:/Cygwin/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Cygwin/bin/g++.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--static")
