#pragma once

#ifdef XD_EXPORTING
    #define XD_FRAMEWORK_API __declspec(dllexport)
#else
    #define XD_FRAMEWORK_API __declspec(dllimport)
#endif

