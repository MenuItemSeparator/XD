cmake_minimum_required(VERSION 3.0.0)
project(XD_EngineApp VERSION 0.1.0 LANGUAGES C CXX)

include_directories(../)
include_directories(../../)
set(src XD_App.cpp)

set(SOURCE_LIB ${src})

add_library(XD_EngineApp STATIC ${SOURCE_LIB})
