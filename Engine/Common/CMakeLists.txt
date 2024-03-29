set(XD_ENGINE_COMMON_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Common)

set(XD_COMMON_SRC
    Common/Windows/XD_LibraryWindows_Implementation.cpp
)

if(WIN32)
    list(APPEND XD_COMMON_SRC ${XD_ENGINE_COMMON_DIRECTORY}/Windows/XD_LibraryWindows_Implementation.cpp)
endif()

set(XD_COMMON_HEADERS
    ${XD_ENGINE_COMMON_DIRECTORY}
)
