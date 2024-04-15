set(XD_ENGINE_GRAPHICS_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Graphics)

set(XD_GRAPHICS_SRC
#OpenGL
Graphics/GraphicsApi/OpenGL/XD_OpenGLGraphicsApi.cpp

Graphics/XD_GraphicsApi_Interface.cpp
Graphics/XD_Renderer.cpp
Graphics/XD_Shader.cpp
Graphics/XD_BufferLayout.cpp)

set(XD_GRAPHICS_HEADERS
    ${XD_ENGINE_GRAPHICS_DIRECTORY}
)
