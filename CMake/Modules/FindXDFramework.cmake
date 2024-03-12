include(FindPackageHandleStandardArgs)

find_library(XD_FRAMEWORK_LIBRARY XDFramework HINTS "${CMAKE_PREFIX_PATH}/XDFramework")
find_path(XD_FRAMEWORK_MAIN_HEADER_DIR NAMES "XDFramework.h" PATHS "${XD_ROOT_SOURCE_PATH}/Framework")

if (XDFramework_FOUND)
    message("===| FOUND XD FRAMEWORK LIB |===")
endif()

set(XD_FRAMEWORK_INCLUDE_DIR)

if(XD_ENGINE_MAIN_HEADER_DIR)
    list(APPEND XD_FRAMEWORK_INCLUDE_DIR "${XD_FRAMEWORK_MAIN_HEADER_DIR}/Source")
endif()
