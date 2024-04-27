#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include <Windows.h>
    #include <wingdi.h>
    #include "Windows/XD_WindowsWidget.h"
    #include "Windows/XD_WindowsApplication.h"
#else
    //Unknown platform
#endif
