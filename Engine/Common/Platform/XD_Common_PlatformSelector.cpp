#include "XD_Common_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsLibrary.cpp"
    #include "Windows/XD_WindowsThread.cpp"
#else
// Unknown platform
#endif
