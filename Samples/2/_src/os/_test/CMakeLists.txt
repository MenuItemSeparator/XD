cmake_minimum_required(VERSION 3.5)

project(xd_os LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../../_module/Module.cmake)

import_module(base)
import_module(math)
import_module(os)

add_library(os_lib STATIC ${all_headers} ${all_sources})
set_target_properties(os_lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(os_lib PUBLIC ./../ ./../../ ${all_directories})

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT IS_SUBPROJECT)
	add_executable(testing_os main.cpp ${os_sources})
	target_link_libraries(testing_os os_lib)
endif()

if(IS_SUBPROJECT)
	message("OS Subproject detected")
endif()
