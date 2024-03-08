#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

include(XDCommon)

set(XD_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${XD_ROOT_PATH}/Engine)
