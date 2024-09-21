#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include <Windows.h>
    #include <wingdi.h>
    #include "Windows/XD_WindowsWindow.h"
#else
    //Unknown platform
#endif
