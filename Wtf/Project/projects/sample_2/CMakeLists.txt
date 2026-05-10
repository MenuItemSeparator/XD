set(target ${wtf_project_name}_s2)
project(${target})

set(sources
    main.cpp
)

set(target_libraries
    xcall
    xml
)
add_executable(${target} ${sources})

foreach(i IN LISTS target_libraries)
    target_link_libraries(${target} ${wtf_project_name}_${i})
endforeach()
