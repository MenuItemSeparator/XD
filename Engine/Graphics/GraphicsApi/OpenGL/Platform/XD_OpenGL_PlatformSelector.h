#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include <Windows.h>
    #include <wingdi.h>


    typedef HGLRC (tWGLCreateContextProcPtr)(HDC);
    typedef PROC (tGLGetProcAddress)(LPCSTR);
#else
//Unknown platform
#endif
