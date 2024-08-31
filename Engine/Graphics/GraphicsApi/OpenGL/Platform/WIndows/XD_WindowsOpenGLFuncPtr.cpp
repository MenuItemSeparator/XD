#include "XD_WindowsOpenGLFuncPtr.h"

namespace XD
{
    tWGLCreateContextAttribsARB* gWGLCreateContextAttribsARBProc;
    tWGLChoosePixelFormatARB* gWGLChoosePixelFormatARBProc;
    tGLSetClearColor* gSetClearColorProc;
    tGLClear* gClearProc;

    X 
    fLoadOpenGLInitialProcPtrX()
    {
        gWGLCreateContextAttribsARBProc = (tWGLCreateContextAttribsARB*)wglGetProcAddress("wglCreateContextAttribsARB");
        mXD_ASSERT(gWGLCreateContextAttribsARBProc);

        gWGLChoosePixelFormatARBProc = (tWGLChoosePixelFormatARB*)wglGetProcAddress("wglChoosePixelFormatARB");
        mXD_ASSERT(gWGLChoosePixelFormatARBProc);

        return A_A;
    }

    X 
    fLoadOpenGLExtensionProcPtrX(XD_Library& _library)
    {
        gSetClearColorProc = _library.fvGetProcAddress("glClearColor");
        mXD_ASSERT(gSetClearColorProc);

        gClearProc = _library.fvGetProcAddress("glClear");
        mXD_ASSERT(gClearProc);

        return A_A;
    }
}
