#include "XD_OpenGL_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsOpenGLRenderer.cpp"
#else
//Unknown platform
#endif
