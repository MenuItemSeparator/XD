cmake_minimum_required(VERSION 3.9)

#=== Project config ===#
set(wtf_project_name wtf)
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
project(${wtf_project_name})

#=== C++ config ===#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=== Build config ===#
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build_cmake/lib)
message("=== Binary files set at: ${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

#=== Configure includes ===#
set(includes ${includes}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
include_directories(${includes})

#=== Configure modules ===#
set(wtf_module_names
    module_1
    xcall
)

foreach(i IN LISTS wtf_module_names)
    add_subdirectory(modules/${i}/)
endforeach()

#=== Configure projects ===#
set(wtf_project_names
    sample_1
)

foreach(i IN LISTS wtf_project_names)
    add_subdirectory(projects/${i})
endforeach()
