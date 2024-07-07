#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include <Windows.h>
    #include <wingdi.h>

    typedef PROC(tGLGetProcAddress)(LPCSTR);

    #include "Windows/XD_WindowsOpenGLContext.h"
#else
//Unknown platform
#endif
