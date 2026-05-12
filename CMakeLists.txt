cmake_minimum_required(VERSION 3.5)

#== User Configuration Start ==#
set(SOURCES
    src/Win/main.cpp
)

set(INCLUDES

)

set(DEPENDENCIES

)
#== User Configuration End ==#

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

# ==================================================== #
# ==== Include solution and module configurations ====
if(XD_SOLUTION)
    include(Solution_${XD_TARGET}.cmake)
else()
    #set(XD_TARGET "Engine")
    #set(XD_TARGET "Editor")
    #set(XD_TARGET "Feature")
    set(XD_SOLUTION "Test")
    include(Solution_${XD_SOLUTION}.cmake)
endif()
message(====================================)
message("Solution : ${XD_SOLUTION}")
message("LIST : ${XD_SOLUTION_LIST}")
foreach(solution ${XD_SOLUTION_LIST}) # Solution
    message("Solution : ${solution}")
    include(${solution}/_module.cmake)

    set(SOURCES ${SOURCES} ${Module${solution}_Sources})
    set(INCLUDES ${INCLUDES} ${Module${solution}_Includes})
    set (DEPENDENCIES ${DEPENDENCIES} ${Module${solution}_Dependencies})

endforeach() # Solution

list(REMOVE_DUPLICATES DEPENDENCIES)

message("Dependencies: ${DEPENDENCIES}")
foreach(dep ${DEPENDENCIES})
    include(Modules/${dep}/_module.cmake)
    set(SOURCES ${SOURCES} ${Module${dep}_Sources})
    set(INCLUDES ${INCLUDES} ${Module${dep}_Includes})
endforeach()

list(REMOVE_DUPLICATES XD_SOURCES)

message("Sources: ${SOURCES}")
message("Includes: ${INCLUDES}")
message(====================================)

# ==================================================== #
# TARGET
add_executable(XD ${SOURCES})

list(REMOVE_DUPLICATES INCLUDES)
target_include_directories(XD PUBLIC ${INCLUDES})

# Add preprocessor definitions requested by user
target_compile_definitions(XD PRIVATE 
    XD_ENABLED
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


