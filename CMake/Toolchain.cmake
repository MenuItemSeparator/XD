if(WIN32)
    set(CMAKE_SYSTEM_NAME Windows)
ELSE()
    message("Unknown platform")
ENDIF()

#??? Мб я что-то не докачал, но cygwin'овский gcc не хочет компилить проект
#set(CMAKE_C_COMPILER "D:/Programms/Cygwin/bin/x86_64-w64-mingw32-gcc.exe")
#set(CMAKE_CXX_COMPILER "D:/Programms/Cygwin/bin/x86_64-w64-mingw32-g++.exe")

set(CMAKE_C_COMPILER "$ENV{PATH}/gcc.exe")
set(CMAKE_CXX_COMPILER "$ENV{PATH}/g++.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--static")
