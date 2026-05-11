cmake_minimum_required(VERSION 3.5)

project(XD LANGUAGES CXX)

# Verify C++ compiler is found
if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR
        "C++ compiler not found!\n"
        "Make sure the toolchain is properly installed and configured.\n"
        "For MinGW 32-bit: C:\\MinGW\\bin\\g++.exe\n"
        "For MinGW 64-bit: C:\\MinGWx64\\bin\\g++.exe")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(XD_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories
include_directories(${XD_ROOT_PATH}/_mod)
include_directories(${XD_ROOT_PATH}/_mod/_app)
include_directories(${XD_ROOT_PATH}/_mod/_data)
include_directories(${XD_ROOT_PATH}/_mod/_os)
include_directories(${XD_ROOT_PATH}/_mod/_os/Win)

# Source files for the application
set(SOURCES
    src/Win/main.cpp
   _mod/_app/Result.cpp
   _mod/_app/App.cpp
   _mod/_app/Log.cpp
   _mod/_data/Data.cpp
   _mod/_data/String.cpp
   _mod/_os/Widget.cpp
   _mod/_os/Win/WindowsWidget.cpp
)

# Create executable
add_executable(XD ${SOURCES})

# Add preprocessor definitions requested by user
target_compile_definitions(XD PRIVATE 
    XD 
    B2D 
    XML2
)

# Add compiler flags requested by user for non-MSVC compilers
if(NOT MSVC)
    # Use older C++ standard switch and enable pthreads where available
    target_compile_options(XD PRIVATE -std=c++0x -pthread)
else()
    # MSVC does not recognize -std or -pthread; leave defaults or adjust as needed
    # Example alternative for MSVC (uncomment to enable):
    # target_compile_options(XD PRIVATE /std:c++14)
endif()

# Link Windows libraries if on Windows
if(WIN32)
    target_link_libraries(XD PRIVATE user32)
endif()

# Set output directory
set_target_properties(XD PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)


