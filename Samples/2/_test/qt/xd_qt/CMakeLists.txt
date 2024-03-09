cmake_minimum_required(VERSION 3.5)

project(saber LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp List.cpp)
set(HEADERS RemoveDups.h List.h)

add_executable(mukshin_saber ${SOURCES} ${HEADERS})
