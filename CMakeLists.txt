#Comment me later
cmake_minimum_required(VERSION 3.5)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(XD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(XD_ROOT_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(XD_ROOT_BINARY_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_PREFIX_PATH ${XD_ROOT})

list(APPEND CMAKE_MODULE_PATH ${XD_ROOT}/CMake/ ${XD_ROOT}/CMake/Modules ${XD_ROOT}/CMake/Toolsets)

include(XDCommon)

select_toolchain()

project(XD LANGUAGES CXX)

add_subdirectory(${XD_ROOT_SOURCE_PATH}/Thirdparty)
add_subdirectory(${XD_ROOT_SOURCE_PATH}/Engine)
add_subdirectory(${XD_ROOT_SOURCE_PATH}/Framework)
add_subdirectory(${XD_ROOT_SOURCE_PATH}/Game)

