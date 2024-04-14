cmake_minimum_required(VERSION 3.5)

project(Glad LANGUAGES C)

set(GLAD_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(GLAD_SRC_DIR ${GLAD_ROOT_DIR}/src)
set(GLAD_INCLUDE_DIR ${GLAD_ROOT_DIR}/include)

set(GLAD_SOURCES ${GLAD_SRC_DIR}/glad.c)

add_library(GLAD ${GLAD_SOURCES})

target_include_directories(GLAD PRIVATE ${GLAD_INCLUDE_DIR})

install(TARGETS GLAD DESTINATION "${CMAKE_INSTALL_PREFIX}/Thirdparty")
