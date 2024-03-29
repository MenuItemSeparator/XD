#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_FRAMEWORK LANGUAGES CXX)

#include(XDCommon)

#Options block
option(XD_FRAMEWORK_BUILD_TESTS "Build framework tests" ON)

set(XD_FRAMEWORK_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(XD_FRAMEWORK_SOURCE_DIRECTORY ${XD_FRAMEWORK_ROOT_DIRECTORY}/Source)

#Including modules
include(${XD_FRAMEWORK_SOURCE_DIRECTORY}/CMakeLists.txt)

add_library(XDFramework SHARED ${XD_FRAMEWORK_SRC})

#Headers
target_include_directories(XDFramework PRIVATE ${XD_FRAMEWORK_HEADERS})
target_include_directories(XDFramework PUBLIC ${XD_FRAMEWORK_ROOT_DIRECTORY})

#Libs
find_package(XDEngine REQUIRED)
target_include_directories(XDFramework PUBLIC ${XD_ENGINE_INCLUDE_DIR})
target_link_libraries(XDFramework PUBLIC XDEngine)

#Definitions
target_compile_definitions(XDFramework PRIVATE -DXD_EXPORTING=1)

if(${CMAKE_BUILD_TYPE})
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_compile_definitions(XDFramework PRIVATE -DXD_BUILD_TYPE_DEBUG=1)
    endif()
endif()

if(DEFINED XD_FRAMEWORK_BUILD_TESTS)
    message("Started to build framework tests")
    add_subdirectory(Tests)
endif()

install(TARGETS XDFramework DESTINATION ${CMAKE_INSTALL_PREFIX}/XDFramework)
