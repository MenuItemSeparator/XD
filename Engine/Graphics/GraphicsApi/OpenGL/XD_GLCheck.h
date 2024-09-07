#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    //Error codes
    #define GL_NO_ERROR 0
    #define GL_INVALID_ENUM 0x0500
    #define GL_INVALID_VALUE 0x0501
    #define GL_INVALID_OPERATION 0x0502
    #define GL_STACK_OVERFLOW 0x0503
    #define GL_STACK_UNDERFLOW 0x0504
    #define GL_OUT_OF_MEMORY 0x0505
    //Error codes End

    using GLenum = unsigned int;

    typedef GLenum tGLGetError(void);
    extern XD_ENGINE_API tGLGetError* gGLGetErrorProc;

    #ifdef dXD_DEBUG
        #define OpenGLCheck(expr) \
            { \
                expr; \
                CheckOpenGLError(__FILE__, __LINE__); \
            }
    #else
        #define OpenGLCheck(expr)  (expr)
    #endif

    void CheckOpenGLError(const std::string& filename, const std::uint_fast32_t line);
}