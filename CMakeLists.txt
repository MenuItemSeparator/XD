cmake_minimum_required(VERSION 3.5)

project(XD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(XD_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${XD_ROOT_PATH}/Engine)
