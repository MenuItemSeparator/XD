#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "./Windows/XD_WindowsOpenGLRenderer.h"
    #include "./Windows/XD_WindowsOpenGLFuncPtr.h"
#else
//Unknown platform
#endif
