#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_ENGINE LANGUAGES CXX)

include(GNUInstallDirs)
include(XDCommon)

#Options block
option(XD_ENGINE_BUILD_TESTS "Build engine tests" OFF)

#Variables block
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XD_ENGINE_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(XD_ENGINE_SOURCE_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Source)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

#Including source modules
include(${XD_ENGINE_SOURCE_DIRECTORY}/Core/CMakeLists.txt)

list(APPEND XD_ENGINE_SRC ${XD_CORE_SRC})
list(APPEND XD_ENGINE_HEADERS ${XD_CORE_HEADERS})

add_library(XDEngine SHARED ${XD_ENGINE_SRC})

#Headers
target_include_directories(XDEngine PRIVATE ${XD_ENGINE_HEADERS})

#Definitions
target_compile_definitions(XDEngine PRIVATE -DXD_EXPORTING=1)

if(${XD_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(XDEngine PRIVATE -DXD_BUILD_TYPE_DEBUG=1)
endif()

if(DEFINED XD_ENGINE_BUILD_TESTS)
    message("Started to build tests")
endif()

install(TARGETS XDEngine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
