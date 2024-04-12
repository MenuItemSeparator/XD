macro(select_toolchain)
    include(SelectToolchain)
endmacro()

macro(select_exe_entry_point target_name)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_link_options(${target_name} PUBLIC -Xlinker -entry:mainCRTStartup)
    endif()
endmacro()
