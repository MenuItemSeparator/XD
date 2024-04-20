include(FindPackageHandleStandardArgs)

find_library(GLAD_LIBRARY GLAD HINTS "${CMAKE_BINARY_DIR}/Thirdparty/Engine/Glad")
find_path(GLAD_MAIN_HEADER_DIR NAMES "glad.h" PATHS "${XD_ROOT_SOURCE_PATH}/Thirdparty/Engine/Glad/include/glad/")

if(NOT ${GLAD_LIBRARY} STREQUAL "GLAD_LIBRARY-NOTFOUND")
    message("===| FOUND GLAD LIB |===")
endif()

set(GLAD_INCLUDE_DIR)

if(GLAD_MAIN_HEADER_DIR)
    list(APPEND GLAD_INCLUDE_DIR "${GLAD_MAIN_HEADER_DIR}")
endif()
