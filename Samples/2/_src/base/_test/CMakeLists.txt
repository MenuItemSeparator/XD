cmake_minimum_required(VERSION 3.5)

project(xd_base LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

file(GLOB base_headers ../*.h ../win/*.h)
file(GLOB base_sources ../*.cpp ../win/*.cpp)

message(base_sources = ${base_sources})

add_library(base_lib STATIC ${base_sources} ${base_headers})
set_target_properties(base_lib PROPERTIES LINKER_LANGUAGE CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
if(NOT IS_SUBPROJECT)
	add_executable(testing_base main.cpp)
	target_link_libraries(testing_base base_lib)
else()

endif()
