include(FindPackageHandleStandardArgs)

find_library(XD_FRAMEWORK_LIBRARY XDFramework HINTS "${XD_ROOT_BINARY_PATH}/Framework")
find_path(XD_FRAMEWORK_MAIN_HEADER_DIR NAMES "XDFramework.h" PATHS "${XD_ROOT_SOURCE_PATH}/Framework")

find_package_handle_standard_args(XDFramework REQUIRED_VARS XD_FRAMEWORK_LIBRARY XD_FRAMEWORK_MAIN_HEADER_DIR)

if (XDFramework_FOUND)
    message("===| FOUND XD FRAMEWORK LIB |===")
endif()

set(XD_FRAMEWORK_INCLUDE_DIR)

if(XD_ENGINE_MAIN_HEADER_DIR)
    list(APPEND XD_FRAMEWORK_INCLUDE_DIR "${XD_FRAMEWORK_MAIN_HEADER_DIR}/Source")
endif()
