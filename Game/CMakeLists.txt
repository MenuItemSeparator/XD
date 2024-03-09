#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_GAME LANGUAGES CXX)

include(GNUInstallDirs)
include(XDCommon)

#Variables block
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XD_GAME_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(XD_GAME_SOURCE_DIRECTORY ${XD_GAME_ROOT_DIRECTORY}/Source)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

#Including source modules
include(${XD_GAME_SOURCE_DIRECTORY}/CMakeLists.txt)

add_executable(XDGame ${XD_GAME_SRC})

#Headers
target_include_directories(XDGame PRIVATE ${XD_GAME_HEADERS})

#Libs
find_package(XDEngine REQUIRED)
target_include_directories(XDGame PRIVATE ${XD_ENGINE_INCLUDE_DIR})
target_link_libraries(XDGame PRIVATE XDEngine)

if(${XD_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(XDGame PRIVATE -DXD_BUILD_TYPE_DEBUG=1)
endif()

install(TARGETS XDGame XDEngine DESTINATION XDGame)
