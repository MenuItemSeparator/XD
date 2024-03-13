#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

include(XDCommon)

set(XD_ROOT_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(XD_ROOT_BINARY_PATH ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${XD_ROOT_SOURCE_PATH}/Engine)
add_subdirectory(${XD_ROOT_SOURCE_PATH}/Framework)
add_subdirectory(${XD_ROOT_SOURCE_PATH}/Game)
