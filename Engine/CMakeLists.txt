#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_ENGINE LANGUAGES CXX)

include(XDCommon)

#Options block
option(XD_ENGINE_BUILD_TESTS "Build engine tests" ON)

set(XD_ENGINE_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

#Including modules
set(XD_ENGINE_SRC)
set(XD_ENGINE_HEADERS)

include(${XD_ENGINE_ROOT_DIRECTORY}/Source/CMakeLists.txt)
include(${XD_ENGINE_ROOT_DIRECTORY}/Graphics/CMakeLists.txt)

list(APPEND XD_ENGINE_SRC ${XD_SOURCE_SRC} ${XD_GRAPHICS_SRC})
list(APPEND XD_ENGINE_HEADERS ${XD_SOURCE_HEADERS} ${XD_GRAPHICS_HEADERS})

add_library(XDEngine SHARED ${XD_ENGINE_SRC})

#Headers
target_include_directories(XDEngine PRIVATE ${XD_ENGINE_HEADERS})
target_include_directories(XDEngine PUBLIC ${XD_ENGINE_ROOT_DIRECTORY})

#Definitions
target_compile_definitions(XDEngine PRIVATE -DXD_EXPORTING=1)

if(${XD_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(XDEngine PRIVATE -DXD_BUILD_TYPE_DEBUG=1)
endif()

if(DEFINED XD_ENGINE_BUILD_TESTS)
    message("Started to build engine tests")
    add_subdirectory(Tests)
endif()

install(TARGETS XDEngine DESTINATION ${CMAKE_PREFIX_PATH}/XDEngine)
