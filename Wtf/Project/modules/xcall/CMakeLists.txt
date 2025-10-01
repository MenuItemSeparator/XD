set(target ${wtf_project_name}_xcall)

add_library(${target} STATIC ${sources}
    XCall.h
    XCall.cpp
    XCallTests.h
    XCallTests.cpp)
