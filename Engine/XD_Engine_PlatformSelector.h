#pragma once

#ifdef _WIN32
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


