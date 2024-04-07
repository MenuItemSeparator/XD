#include "XDApplication_PlatformSelector.h"


#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsWidget.cpp"
#else
    // Unknown platform
#endif
