#pragma once

#ifdef XD_EXPORTING
    #define XD_ENGINE_API __declspec(dllexport)
#else
    #define XD_ENGINE_API __declspec(dllimport)
#endif

#ifdef XD_BUILD_TYPE_DEBUG
    #define XD_DEBUG
#endif
