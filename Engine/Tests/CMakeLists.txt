#XD Engine tests
cmake_minimum_required(VERSION 3.5)

project(XD_ENGINE_TESTS LANGUAGES CXX)

set(XD_ENGINE_TESTS_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(XD_ENGINE_TESTS_SOURCE_PATH ${XD_ENGINE_TESTS_ROOT_PATH}/Source)

set(XD_ENGINE_TESTS_SRC
    ${XD_ENGINE_TESTS_SOURCE_PATH}/Main.cpp
)

add_executable(XDEngineTests ${XD_ENGINE_TESTS_SRC})

target_include_directories(XDEngineTests PUBLIC "${XD_ENGINE_TESTS_SOURCE_PATH}")

install(TARGETS XDEngineTests XDEngine DESTINATION XDEngine/Tests)
