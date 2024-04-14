#XD Engine tests
cmake_minimum_required(VERSION 3.5)

project(XD_ENGINE_TESTS LANGUAGES CXX)

set(XD_ENGINE_TESTS_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(XD_ENGINE_TESTS_SOURCE_PATH ${XD_ENGINE_TESTS_ROOT_PATH}/Source)

find_package(XDEngine REQUIRED)
set(XD_TEST_MODULE_DEFAULT_INCLUDE_DIRS ${XD_ENGINE_INCLUDE_DIR} ${XD_ENGINE_TESTS_SOURCE_PATH} ${XD_ROOT}/Test)

enable_testing()

macro(setup_test_module target_name test_source)
    add_executable(${target_name} ${test_source})
    target_link_libraries(${target_name} PUBLIC XDEngine)
    target_include_directories(${target_name} PUBLIC ${XD_TEST_MODULE_DEFAULT_INCLUDE_DIRS})
    add_test(NAME ${target_name} COMMAND $<TARGET_FILE:${target_name}>)
    install(TARGETS ${target_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/XDEngine/Tests)
endmacro()

setup_test_module(XDEngineTests_Math ${XD_ENGINE_TESTS_SOURCE_PATH}/XDEngineTests_Math.cpp)
setup_test_module(XDEngineTests_Widget ${XD_ENGINE_TESTS_SOURCE_PATH}/XDEngineTests_Widget.cpp)
setup_test_module(XDEngineTests_BufferLayout ${XD_ENGINE_TESTS_SOURCE_PATH}/XDEngineTests_BufferLayout.cpp)

add_custom_command(TARGET XDEngineTests_Math POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/../XDEngine.dll" "${CMAKE_CURRENT_BINARY_DIR}/")
install(TARGETS XDEngine DESTINATION ${CMAKE_INSTALL_PREFIX}/XDEngine/Tests)


