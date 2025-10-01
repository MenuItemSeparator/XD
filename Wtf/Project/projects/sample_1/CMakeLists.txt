set(target ${wtf_project_name}_s1)
project(${target})

set(sources
    main.cpp
)

set(target_libraries
    xcall
)
add_executable(${target} ${sources})

foreach(i IN LISTS target_libraries)
    target_link_libraries(${target} ${wtf_project_name}_${i})
endforeach()
