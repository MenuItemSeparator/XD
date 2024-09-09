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

    tGLGenVertexArrays* gGLGenVertexArraysProc;
    tGLDeleteVertexArrays* gGLDeleteVertexArraysProc;
    tGLBindVertexArray* gGLBindVertexArrayProc;
    tGLEnableVertexAttribArray* gGLEnableVertexAttribArrayProc;
    tGLDisableVertexAttribArray* gGLDisableVertexAttribArrayProc;
    tGLVertexAttribPointer* gGLVertexAttribPointerProc;
    tGLVertexAttribDivisor* gGLVertexAttribDivisorProc;

    tGLCreateShader* gGLCreateShaderProc;
    tGLDeleteShader* gGLDeleteShaderProc;
    tGLShaderSource* gGLShaderSourceProc;
    tGLAttachShader* gGLAttachShaderProc;
    tGLDetachShader* gGLDetachShaderProc;
    tGLCompileShader* gGLCompileShaderProc;
    tGLCreateProgram* gGLCreateProgramProc;
    tGLDeleteProgram* gGLDeleteProgramProc;
    tGLLinkProgram* gGLLinkProgramProc;
    tGLUseProgram* gGLUseProgramProc;
    tGLGetShaderiv* gGLGetShaderiv;
    tGLGetShaderInfoLog* gGLGetShaderInfoLog;
    tGLGetProgramiv* gGLGetProgramivProc;
    tGLGetProgramInfoLog* gGLGetProgramInfoLogProc;

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

        gGLGenVertexArraysProc = (tGLGenVertexArrays*)wglGetProcAddress("glGenVertexArrays");
        mXD_ASSERT(gGLGenVertexArraysProc);

        gGLDeleteVertexArraysProc = (tGLDeleteVertexArrays*)wglGetProcAddress("glDeleteVertexArrays");
        mXD_ASSERT(gGLDeleteVertexArraysProc);        

        gGLBindVertexArrayProc = (tGLBindVertexArray*)wglGetProcAddress("glBindVertexArray");
        mXD_ASSERT(gGLBindVertexArrayProc);

        gGLEnableVertexAttribArrayProc = (tGLEnableVertexAttribArray*)wglGetProcAddress("glEnableVertexAttribArray");
        mXD_ASSERT(gGLEnableVertexAttribArrayProc);

        gGLDisableVertexAttribArrayProc = (tGLDisableVertexAttribArray*)wglGetProcAddress("glDisableVertexAttribArray");
        mXD_ASSERT(gGLDisableVertexAttribArrayProc);

        gGLVertexAttribPointerProc = (tGLVertexAttribPointer*)wglGetProcAddress("glVertexAttribPointer");
        mXD_ASSERT(gGLVertexAttribPointerProc);

        gGLVertexAttribDivisorProc = (tGLVertexAttribDivisor*)wglGetProcAddress("glVertexAttribDivisor");
        mXD_ASSERT(gGLVertexAttribDivisorProc);

        gGLCreateShaderProc = (tGLCreateShader*)wglGetProcAddress("glCreateShader");
        mXD_ASSERT(gGLCreateShaderProc);

        gGLDeleteShaderProc = (tGLDeleteShader*)wglGetProcAddress("glDeleteShader");
        mXD_ASSERT(gGLDeleteShaderProc);

        gGLShaderSourceProc = (tGLShaderSource*)wglGetProcAddress("glShaderSource");
        mXD_ASSERT(gGLShaderSourceProc);

        gGLAttachShaderProc = (tGLAttachShader*)wglGetProcAddress("glAttachShader");
        mXD_ASSERT(gGLAttachShaderProc);

        gGLDetachShaderProc = (tGLDetachShader*)wglGetProcAddress("glDetachShader");
        mXD_ASSERT(gGLDetachShaderProc);

        gGLCompileShaderProc = (tGLCompileShader*)wglGetProcAddress("glCompileShader");
        mXD_ASSERT(gGLCompileShaderProc);

        gGLCreateProgramProc = (tGLCreateProgram*)wglGetProcAddress("glCreateProgram");
        mXD_ASSERT(gGLCreateProgramProc);

        gGLDeleteProgramProc = (tGLDeleteProgram*)wglGetProcAddress("glDeleteProgram");
        mXD_ASSERT(gGLDeleteProgramProc);

        gGLLinkProgramProc = (tGLLinkProgram*)wglGetProcAddress("glLinkProgram");
        mXD_ASSERT(gGLLinkProgramProc);

        gGLUseProgramProc = (tGLUseProgram*)wglGetProcAddress("glUseProgram");
        mXD_ASSERT(gGLUseProgramProc);

        gGLGetShaderiv = (tGLGetShaderiv*)wglGetProcAddress("glGetShaderiv");
        mXD_ASSERT(gGLGetShaderiv);

        gGLGetShaderInfoLog = (tGLGetShaderInfoLog*)wglGetProcAddress("glGetShaderInfoLog");
        mXD_ASSERT(gGLGetShaderInfoLog);

        gGLGetProgramivProc = (tGLGetProgramiv*)wglGetProcAddress("glGetProgramiv");
        mXD_ASSERT(gGLGetProgramivProc);

        gGLGetProgramInfoLogProc = (tGLGetProgramInfoLog*)wglGetProcAddress("glGetProgramInfoLog");
        mXD_ASSERT(gGLGetProgramInfoLogProc);

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
