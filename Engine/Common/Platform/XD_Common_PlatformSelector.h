#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #define NOWINBASEINTERLOCK
    #include <Windows.h>
    #include "Windows/XD_WindowsLibrary.h"
#else
//Unknown platform
#endif
