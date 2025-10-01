set(target ${wtf_project_name}_m1)

set(sources
    module_1.h
    module_1.cpp
)

include_directories(${root_dir}/include/)

add_library(${target} STATIC ${sources})
