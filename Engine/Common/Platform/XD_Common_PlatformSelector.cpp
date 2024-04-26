#include "XD_Common_PlatformSelector.h"

#ifdef dXD_PLATFORM_WINDOWS
    #include "Windows/XD_WindowsLibrary.cpp"
#else
// Unknown platform
#endif
