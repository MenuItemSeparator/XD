set(target ${wtf_project_name}_xml)

set(sources
    xml.h
    xml.cpp
)

include_directories(${root_dir}/include/)

add_library(${target} STATIC ${sources})
