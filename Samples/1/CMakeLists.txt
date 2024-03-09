cmake_minimum_required(VERSION 3.0.0)
project(XD_Engine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

target_sources(Continuous
  PRIVATE
    Engine/Base/XD_Code.h
    Engine/Base/Log.h
    Engine/Base/Log.cpp
)
enable_testing()

set(exec_sources Engine/main.cpp)
include_directories(Engine/App/)
add_subdirectory(Engine/App/)

add_executable(XD_Engine ${exec_sources})
target_include_directories(XD_Engine PUBLIC .)

# Linking section
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} Plugins/tinyxml2/)

target_link_libraries(XD_Engine XD_EngineApp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# External Statics Libs
# add_library(netutil STATIC IMPORTED)
# set_property(TARGET netutil PROPERTY IMPORTED_LOCATION Binary/game_client/libnetutil.a)

