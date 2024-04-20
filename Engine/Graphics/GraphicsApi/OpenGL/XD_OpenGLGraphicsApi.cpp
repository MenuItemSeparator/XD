#include "XD_OpenGLGraphicsApi.h"

namespace XD
{
    XD_OpenGLGraphicsApi::XD_OpenGLGraphicsApi()
    {
        XD_GraphicsApi::fBindFunctions_Internal<XD_OpenGLGraphicsApi>();
    }

    X XD_OpenGLGraphicsApi::fInitializeX()
    {
        return A_A;
    }

    X XD_OpenGLGraphicsApi::fShutdownX()
    {
        return A_A;
    }
}
