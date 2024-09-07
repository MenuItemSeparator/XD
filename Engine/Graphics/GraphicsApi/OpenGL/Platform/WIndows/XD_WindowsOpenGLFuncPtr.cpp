#include "XD_WindowsOpenGLFuncPtr.h"

namespace XD
{
    tWGLCreateContextAttribsARB* gWGLCreateContextAttribsARBProc;
    tWGLChoosePixelFormatARB* gWGLChoosePixelFormatARBProc;
    tGLSetClearColor* gSetClearColorProc;
    tGLClear* gClearProc;
    tGLGetError* gGLGetErrorProc;

    tGLGenBuffers* gGLGenBuffersProc;
    tGLDeleteBuffers* gGLDeleteBuffersProc;
    tGLBindBuffer* gGLBindBufferProc;
    tGLBufferData* gGLBufferDataProc;
    tGLBufferSubData* gGLBufferSubDataProc;


    X 
    fLoadOpenGLInitialProcPtrX()
    {
        gWGLCreateContextAttribsARBProc = (tWGLCreateContextAttribsARB*)wglGetProcAddress("wglCreateContextAttribsARB");
        mXD_ASSERT(gWGLCreateContextAttribsARBProc);

        gWGLChoosePixelFormatARBProc = (tWGLChoosePixelFormatARB*)wglGetProcAddress("wglChoosePixelFormatARB");
        mXD_ASSERT(gWGLChoosePixelFormatARBProc);

        gGLGenBuffersProc = (tGLGenBuffers*)wglGetProcAddress("glGenBuffers");
        mXD_ASSERT(gGLGenBuffersProc);

        gGLDeleteBuffersProc = (tGLDeleteBuffers*)wglGetProcAddress("glDeleteBuffers");
        mXD_ASSERT(gGLDeleteBuffersProc);

        gGLBindBufferProc = (tGLBindBuffer*)wglGetProcAddress("glBindBuffer");
        mXD_ASSERT(gGLBindBufferProc);

        gGLBufferDataProc = (tGLBufferData*)wglGetProcAddress("glBufferData");
        mXD_ASSERT(gGLBufferDataProc);

        gGLBufferSubDataProc = (tGLBufferSubData*)wglGetProcAddress("glBufferSubData");
        mXD_ASSERT(gGLBufferSubDataProc);

        return A_A;
    }

    X 
    fLoadOpenGLExtensionProcPtrX(XD_Library& _library)
    {
        gGLGetErrorProc = _library.fvGetProcAddress("glGetError");
        mXD_ASSERT(gGLGetErrorProc);

        gSetClearColorProc = _library.fvGetProcAddress("glClearColor");
        mXD_ASSERT(gSetClearColorProc);

        gClearProc = _library.fvGetProcAddress("glClear");
        mXD_ASSERT(gClearProc);

        return A_A;
    }
}
