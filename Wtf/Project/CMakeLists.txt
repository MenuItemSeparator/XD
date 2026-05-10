cmake_minimum_required(VERSION 3.9)

#=== Project config ===#
set(wtf_project_name wtf)
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
project(${wtf_project_name})

include(./CMakeLists_Config_Project.txt)
include(./CMakeLists_Config_Cpp.txt)
include(./CMakeLists_Config_Build.txt)
include(./CMakeLists_Config_Includes.txt)
include(./CMakeLists_Config_Modules.txt)
include(./CMakeLists_Config_Projects.txt)

#------
