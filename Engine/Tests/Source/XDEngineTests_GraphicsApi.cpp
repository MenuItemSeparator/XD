#include "XDEngine_Minimal.h"
#include "XDTest_Minimal.h"
#include "Graphics/GraphicsApi/OpenGL/XD_OpenGLGraphicsApi.h"

namespace XD
{
    X
    Test_OpenGLInterfaceValidness()
    {
        UPtr<XD_GraphicsApi> graphicsApiInterface = std::make_unique<XD_OpenGLGraphicsApi>();
        X_Call(graphicsApiInterface->fInitializeX(), "OpenGl graphics api initialization failed");
        X_Call(graphicsApiInterface->fShutdownX(), "OpenGl graphics api shutdown failed");
        return A_A;
    }

}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_OpenGLInterfaceValidness(), "OpenGL interface validness test failed");
    return 0;
}
