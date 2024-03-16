#Comment me later
cmake_minimum_required(VERSION 3.5)

project(XD_GAME LANGUAGES CXX)

include(XDCommon)

set(XD_GAME_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(XD_GAME_SOURCE_DIRECTORY ${XD_GAME_ROOT_DIRECTORY}/Source)

#Including source modules
include(${XD_GAME_SOURCE_DIRECTORY}/CMakeLists.txt)

add_executable(XDGame ${XD_GAME_SRC})

#Headers
target_include_directories(XDGame PRIVATE ${XD_GAME_HEADERS})

#Libs
find_package(XDFramework MODULE REQUIRED)
target_include_directories(XDGame PRIVATE ${XD_FRAMEWORK_INCLUDE_DIR})
target_link_libraries(XDGame PRIVATE XDFramework)

if(${CMAKE_BUILD_TYPE})
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_compile_definitions(XDGame PRIVATE -DXD_BUILD_TYPE_DEBUG=1)
    endif()
endif()

install(TARGETS XDGame XDFramework XDEngine DESTINATION ${CMAKE_PREFIX_PATH}/XDGame)
