#pragma once

#ifdef XD_EXPORTING
    #define XD_API __declspec(dllexport)
#else
    #define XD_API __declspec(dllimport)
#endif

#ifdef XD_BUILD_TYPE_DEBUG
    #define XD_DEBUG
#endif

class XD_API FooClass
{
public:
    void SayHello();
};
