include(FindPackageHandleStandardArgs)

find_library(XD_ENGINE_LIBRARY XDEngine HINTS "${XD_ROOT_BINARY_PATH}/Engine")
find_path(XD_ENGINE_INCLUDE_DIR NAMES "XDEngine.h" PATHS "${XD_ROOT_SOURCE_PATH}/Engine/Source")

find_package_handle_standard_args(XDEngine REQUIRED_VARS XD_ENGINE_LIBRARY XD_ENGINE_INCLUDE_DIR)

if (XDEngine_FOUND)
    message("===| FOUND XD ENGINE LIB |===")
endif()
