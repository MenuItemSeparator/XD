#pragma once

#ifdef XD_PLATFORM_WINDOWS
    #define NOWINBASEINTERLOCK
    #define dXD_PLATFORM_WINDOWS
    #define dFORCEINLINE __forceinline

    #define XD_IMPLEMENT_ENTRY_POINT(ClassName, FuncName) \
        int main(int argc, const char** argv) \
        { \
            ClassName entryPointClass{}; \
            entryPointClass.FuncName(argc, argv); \
            return 0; \
        }
#else
    //Unknown platofrm
#endif


