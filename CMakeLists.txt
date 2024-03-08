# XD is an eXperience Digital, the game framework based on c++.

# This file arc:
# 1. All build config
# 2. Build targets loop
# 3. Link

# Ussage: ***

# Terms of use:
# *
# *

cmake_minimum_required(VERSION 3.5)
#set (CMAKE_TOOLCHAIN_FILE ./cygwin_gcc_toolchain.cmake)

project(XD LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(XDCommon)

#include(XD_ConfigurateThisEnvironment.txt)

set(XD_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${XD_ROOT_PATH}/Engine)
