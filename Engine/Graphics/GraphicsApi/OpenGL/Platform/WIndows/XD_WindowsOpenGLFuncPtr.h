#pragma once
#include <Windows.h>
#include <wingdi.h>

#include "Common/XD_Types.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

namespace XD
{
    //Core
    #define GL_FALSE 0
    #define GL_TRUE 1

    #define GL_DYNAMIC_DRAW 0x88E8
    #define GL_STATIC_DRAW 0x88E4
    //Core End

    //Extensions setup
    #define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
    #define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
    #define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

    #define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

    #define WGL_DRAW_TO_WINDOW_ARB                    0x2001
    #define WGL_ACCELERATION_ARB                      0x2003
    #define WGL_SUPPORT_OPENGL_ARB                    0x2010
    #define WGL_DOUBLE_BUFFER_ARB                     0x2011
    #define WGL_PIXEL_TYPE_ARB                        0x2013
    #define WGL_COLOR_BITS_ARB                        0x2014
    #define WGL_DEPTH_BITS_ARB                        0x2022
    #define WGL_STENCIL_BITS_ARB                      0x2023

    #define WGL_FULL_ACCELERATION_ARB                 0x2027
    #define WGL_TYPE_RGBA_ARB                         0x202B

    #define GL_DEPTH_BUFFER_BIT 0x00000100
    #define GL_STENCIL_BUFFER_BIT 0x00000400
    #define GL_COLOR_BUFFER_BIT 0x00004000
    //Extensions setup End

    //Primitives
    #define GL_POINTS                         0x0000
    #define GL_LINES                          0x0001
    #define GL_LINE_LOOP                      0x0002
    #define GL_LINE_STRIP                     0x0003
    #define GL_TRIANGLES                      0x0004
    #define GL_TRIANGLE_STRIP                 0x0005
    #define GL_TRIANGLE_FAN                   0x0006
    #define GL_QUADS                          0x0007
    #define GL_QUAD_STRIP                     0x0008
    #define GL_POLYGON                        0x0009
    //Primitives End



    //Buffers
    #define GL_ARRAY_BUFFER 0x8892
    //Buffers End

    //Types
    using GLenum = u8;
    using GLuint = u8;
    using GLfloat = f4;
    using GLsizei = i8;
    using GLsizeiptr = i8;
    using GLintptr = intptr_t;
    //Types End

    typedef HGLRC WINAPI tWGLCreateContextAttribsARB(HDC hdc, HGLRC hShareContext, const int *attribList);
    extern XD_ENGINE_API tWGLCreateContextAttribsARB* gWGLCreateContextAttribsARBProc;

    typedef BOOL WINAPI tWGLChoosePixelFormatARB(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
    extern XD_ENGINE_API tWGLChoosePixelFormatARB* gWGLChoosePixelFormatARBProc;
    
    typedef void tGLSetClearColor(f4 red, f4 green, f4 blue, f4 alpha);
    extern XD_ENGINE_API tGLSetClearColor* gSetClearColorProc;
    
    typedef void tGLClear(u4 mask);
    extern XD_ENGINE_API tGLClear* gClearProc;

    typedef GLenum tGLGetError(void);
    extern XD_ENGINE_API tGLGetError* gGLGetErrorProc;

    typedef void tGLGenBuffers(GLsizei n, GLuint* buffers);
    extern XD_ENGINE_API tGLGenBuffers* gGLGenBuffersProc;

    typedef void tGLDeleteBuffers(GLsizei n, const GLuint *buffers);
    extern XD_ENGINE_API tGLDeleteBuffers* gGLDeleteBuffersProc;

    typedef void tGLBindBuffer(GLenum target, GLuint buffer);
    extern XD_ENGINE_API tGLBindBuffer* gGLBindBufferProc;

    typedef void tGLBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    extern XD_ENGINE_API tGLBufferData* gGLBufferDataProc;

    typedef void tGLBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
    extern XD_ENGINE_API tGLBufferSubData* gGLBufferSubDataProc;

    X XD_ENGINE_API fLoadOpenGLInitialProcPtrX();
    X XD_ENGINE_API fLoadOpenGLExtensionProcPtrX(XD_Library& _library);
}