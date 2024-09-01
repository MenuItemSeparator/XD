set(XD_ENGINE_GRAPHICS_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Graphics)

set(XD_GRAPHICS_SRC
#OpenGL
Graphics/GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.cpp
Graphics/GraphicsApi/OpenGL/XD_OpenGLShader.cpp

Graphics/XD_GraphicsSystem.cpp
Graphics/XD_BufferLayout.cpp)

set(XD_GRAPHICS_HEADERS
    ${XD_ENGINE_GRAPHICS_DIRECTORY}
)
