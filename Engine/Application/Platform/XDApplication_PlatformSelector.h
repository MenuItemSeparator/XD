#pragma once
#include "XDEngine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #define NOWINBASEINTERLOCK
    #include <Windows.h>
    #include <wingdi.h>
    #include "Windows/XD_WindowsWidget.h"
    #include "Windows/XD_WindowsApplication.h"
#else
    //Unknown platform
#endif
