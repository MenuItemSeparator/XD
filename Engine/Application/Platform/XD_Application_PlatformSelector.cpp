#include "XD_Application_PlatformSelector.h"


#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsWindow.cpp"
    #include "Windows/XD_WindowsApplication.cpp"
#else
    // Unknown platform
#endif
