#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsOpenGLContext.h"
    #include "Windows/XD_WindowsOpenGLRenderer.h"
#else
//Unknown platform
#endif
