#pragma once

#ifdef XD_EXPORTING
    #define XD_ENGINE_API __declspec(dllexport)
#else
    #define XD_ENGINE_API __declspec(dllimport)
#endif

#ifdef XD_BUILD_TYPE_DEBUG
    #define dXD_DEBUG
#endif

#ifdef dXD_DEBUG
    #define mXD_ASSERTM(cond, msg)  if (!(cond)) { std::cout << ">> [Assert " << #cond << " fail] [ " << __FILE__ << " | " << __func__ << " | " << __LINE__ << " ] : " msg << std::endl; __debugbreak(); }
    #define mXD_ASSERT(cond)  if (!(cond)) mXD_ASSERTM(cond, "<<");
    #define mXD_NOT_IMPLEMENTED() mXD_ASSERTM(false, "Not implemented function reached");
#else
    #define mXD_ASSERT(x, msg);
    #define mXD_ASSERT_S(x);
    #define mXD_NOT_IMPLEMENTED();
#endif
