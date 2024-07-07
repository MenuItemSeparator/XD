#include "XD_OpenGL_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
	#include "Windows/XD_WindowsOpenGLContext.cpp"
#else
//Unknown platform
#endif
