#include "Graphics/XDGraphics_Minimal.h"
#include "XDTest_Minimal.h"
#include "Graphics/GraphicsApi/OpenGL/XD_OpenGLRenderer.h"

namespace XD
{
    X
    Test_OpenGLInterfaceValidness()
    {
        UPtr<XD_OpenGLRenderer> renderer = std::make_unique<XD_OpenGLRenderer>();
        //X_Call(graphicsApiInterface->fInitializeX(), "OpenGl graphics api initialization failed");
        //X_Call(graphicsApiInterface->fShutdownX(), "OpenGl graphics api shutdown failed");
        return A_A;
    }

}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_OpenGLInterfaceValidness(), "OpenGL interface validness test failed");
    return 0;
}
