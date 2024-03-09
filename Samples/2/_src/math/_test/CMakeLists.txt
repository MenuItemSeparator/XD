cmake_minimum_required(VERSION 3.5)
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

project(math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../base/_module [EXCLUDE_FROM_ALL])

file(GLOB math_headers ./../*.h)
file(GLOB math_sources ./../*.cpp)

add_library(math_lib STATIC ${math_sources} ${math_headers})
set_target_properties(math_lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(math_lib PUBLIC "../" "../../" "../../../")
target_link_libraries(math_lib base_library)

if(NOT IS_SUBPROJECT)
	add_executable(math_exe main.cpp)
	target_link_libraries(math_exe math_lib)
	target_include_directories(math_exe PUBLIC "../" "../../" "../../../")
endif()
