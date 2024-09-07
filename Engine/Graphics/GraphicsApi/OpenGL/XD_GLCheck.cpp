#include "XD_GLCheck.h"

namespace XD
{
    X 
    fCheckOpenGLErrorX(const std::string& filename, const std::uint_fast32_t line)
    {
        GLenum error = gGLGetErrorProc();
        if (error == GL_NO_ERROR) return A_A;

        switch (error)
        {
        case GL_STACK_OVERFLOW:
            mLOG("GL_STACK_OVERFLOW: This command would cause a stack overflow. " << filename.c_str() << " " << line);
            break;
        case GL_STACK_UNDERFLOW:
            mLOG("GL_STACK_UNDERFLOW: This command would cause a stack underflow. " << filename.c_str() << " " << line);
            break;
        case GL_INVALID_ENUM:
            mLOG("GL_INVALID_ENUM: an invalid enum value was passed to an OpenGL function " << filename.c_str() << " " << line);
            break;
        case GL_INVALID_VALUE:
            mLOG("GL_INVALID_VALUE: an invalid value was passed to an OpenGL function " << filename.c_str() << " " << line);
            break;
        case GL_INVALID_OPERATION:
            mLOG("GL_INVALID_OPERATION: the requested operation is not valid " << filename.c_str() << " " << line);
            break;
        case GL_OUT_OF_MEMORY:
            mLOG("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory " << filename.c_str() << " " << line);
            break;
        default:
            mLOG("GL UNKNOWN_ERROR " << filename.c_str() << " " << line);
        }

        return X_X;
    }
}