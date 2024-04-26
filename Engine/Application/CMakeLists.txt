set(XD_APPLICATION_SOURCE_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Application)

set(XD_APPLICATION_SRC
    Application/XD_Widget.cpp
    Application/XD_Application.cpp
    Application/Platform/XD_Application_PlatformSelector.cpp
)

set(XD_APPLICATION_HEADERS
    ${XD_APPLICATION_SOURCE_DIRECTORY}
    ${XD_APPLICATION_SOURCE_DIRECTORY}/Platform/
)
