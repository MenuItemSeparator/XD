set(XD_APPLICATION_SOURCE_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Application)

set(XD_APPLICATION_SRC
    Application/XD_Widget.cpp
    Application/XD_Application.cpp
)

if(WIN32)
    list(APPEND XD_APPLICATION_SRC Application/Platform/Windows/XD_WindowsWidget.cpp)
endif()

set(XD_APPLICATION_HEADERS
    ${XD_APPLICATION_SOURCE_DIRECTORY}
)
