cmake_minimum_required(VERSION 3.5)

project(xd LANGUAGES CXX)

set(_source_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(_exec engine)
#
# ! === Статические библиотеки ===
#
set(_static_lib_array
    base_lib
)
add_library(base_lib
    ${_source_dir}/_src/base/base.cpp
)
set(_includes_array
    ${_source_dir}/_src/base
)
target_include_directories(base_lib PUBLIC
    ${includes_array}
)

target_sources(base_lib PUBLIC
    ${_source_dir}/_src/base/xd_string.cpp
)
#
# ! === Исполняемый файл ===
#
add_executable(${_exec}
    ${_source_dir}/engine/main.cpp
)

target_include_directories(${_exec} PUBLIC ${_includes_array})
target_link_libraries(${_exec} PUBLIC ${_static_lib_array})

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(os win)
#set(name engine)

#set(modules
#    base)
#set(sources
#    XD/main.cpp)
#set(headers)
#set(dlibs)
#set(libs)
#set(dirs)
#set(options)
# Цикл сборки
#set(_t xd_${name}_${os})
#add_executable(${_t} ${sources})

#Сборка
message(target ${_t})
message(name ${name})
message(os ${os})
message(headers ${headers})
message(sources ${sources})
message(dlibs ${dlibs})
message(libs ${libs})
message(dirs ${dirs})
message(options ${options})
message(modules ${modules})

#target_include_directories(${_t} PUBLIC ${dirs})
#target_sources(${t} PUBLIC ${headers})
#target_link_libraries(${_t} ${libs})
#target_link_directories(xd_engine dirs)
#target_link_options(xd_engine options)
