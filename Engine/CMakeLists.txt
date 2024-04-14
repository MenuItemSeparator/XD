#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_ENGINE LANGUAGES CXX)

include(XDCommon)

#Options block
option(XD_ENGINE_BUILD_TESTS "Build engine tests" ON)

set(XD_ENGINE_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

#Including modules
set(XD_ENGINE_SRC)
set(XD_ENGINE_HEADERS ${XD_ROOT}/Shared)

include(${XD_ENGINE_ROOT_DIRECTORY}/Source/CMakeLists.txt)
include(${XD_ENGINE_ROOT_DIRECTORY}/Graphics/CMakeLists.txt)
include(${XD_ENGINE_ROOT_DIRECTORY}/Application/CMakeLists.txt)
include(${XD_ENGINE_ROOT_DIRECTORY}/Common/CMakeLists.txt)

list(APPEND XD_ENGINE_SRC
    ${XD_SOURCE_SRC}
    ${XD_GRAPHICS_SRC}
    ${XD_APPLICATION_SRC}
    ${XD_COMMON_SRC})

list(APPEND XD_ENGINE_HEADERS
    ${XD_SOURCE_HEADERS}
    ${XD_GRAPHICS_HEADERS}
    ${XD_APPLICATION_HEADERS}
    ${XD_COMMON_HEADERS})

if(BUILD_SHARED_LIBS)
    add_library(XDEngine SHARED ${XD_ENGINE_SRC})
else()
    add_library(XDEngine STATIC ${XD_ENGINE_SRC})
endif()

#Headers
target_include_directories(XDEngine PRIVATE ${XD_ENGINE_HEADERS})
target_include_directories(XDEngine PUBLIC ${XD_ENGINE_ROOT_DIRECTORY} ${XD_ROOT}/Shared)

#Definitions
target_compile_definitions(XDEngine PUBLIC -DXD_EXPORTING=1)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_compile_definitions(XDEngine PUBLIC -DXD_BUILD_TYPE_DEBUG=1)
endif()

if(XD_ENGINE_BUILD_TESTS)
        message("Started to build engine tests")
	add_subdirectory(Tests)
endif()

install(TARGETS XDEngine DESTINATION ${CMAKE_INSTALL_PREFIX}/XDEngine)
