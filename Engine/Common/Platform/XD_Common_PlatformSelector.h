#pragma once
#include "XD_Engine_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsLibrary.h"
    #include "Windows/XD_WindowsThread.h"
#else
//Unknown platform
#endif
