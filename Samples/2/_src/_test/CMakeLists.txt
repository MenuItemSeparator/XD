cmake_minimum_required(VERSION 3.5)

project(xd_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(functional.cmake)

set(sources)
set(headers)
set(dlibs)
set(libs)
set(dirs)
set(options)

add_module(base sources headers dlibs libs dirs options)
add_module(os sources headers dlibs libs dirs options)

add_executable(xd_engine main.cpp)

print_var(sources)
print_var(headers)
print_var(dlibs)
print_var(libs)
print_var(dirs)
print_var(options)

target_include_directories(xd_engine PUBLIC ${dirs})
target_sources(xd_engine PUBLIC ${headers})
target_link_libraries(xd_engine ${libs})
#target_link_directories(xd_engine dirs)
#target_link_options(xd_engine options)
