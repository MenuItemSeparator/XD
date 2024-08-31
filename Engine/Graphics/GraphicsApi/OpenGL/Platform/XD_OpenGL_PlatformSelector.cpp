#include "XD_OpenGL_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsOpenGLRenderer.cpp"
    #include "Windows/XD_WindowsOpenGLFuncPtr.cpp"
#else
//Unknown platform
#endif
