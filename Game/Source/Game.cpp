#include "Game.h"
#include "Application/XD_Application.h"

int Game::fStartup(int argc, const char **argv)
{
    XD::XD_ApplicationConfig applicationConfig{};
    applicationConfig.m_displayName = "XD";

    XD::XD_Application application{applicationConfig};
    X_Call(application.fvInitializeX(), "Application initialization error");

    //==========

    XD::VertexBufferLayoutHandle layoutHandle;
    std::vector<XD::eShaderDataType> shaderTypes{ XD::eShaderDataType::Float2 };
    X_Call(application.fGetGraphicsSystem()->fCreateVertexBufferLayoutX(layoutHandle, shaderTypes), "");

    XD::VertexBufferObjectHandle vboHandle;
    float vboRawData[] = {1.0f, 1.0f, 1.0f};
    XD::Memory vboMem{vboRawData, 3};
    X_Call(application.fGetGraphicsSystem()->fCreateVertexBufferObjectX(vboHandle, &vboMem, layoutHandle), "");

    XD::IndexBufferObjectHandle iboHandle;
    int iboRawData[] = {0, 1, 2};
    XD::Memory iboMem{iboRawData, 3};
    X_Call(application.fGetGraphicsSystem()->fCreateIndexBufferX(iboHandle, &iboMem), "");

    XD::VertexArrayObjectHandle vaoHandle;
    X_Call(application.fGetGraphicsSystem()->fCreateVertexArrayObjectX(vaoHandle, &vboHandle, 1), "");

    XD::ShaderHandle vsHandle;
    X_Call(application.fGetGraphicsSystem()->fCreateShaderX(vsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestVS.vs"), "");

    XD::ShaderHandle fsHandle;
    X_Call(application.fGetGraphicsSystem()->fCreateShaderX(fsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestFS.fs"), "");

    X_Call(application.fGetGraphicsSystem()->fDestroyVertexBufferLayoutX(layoutHandle), "");
    X_Call(application.fGetGraphicsSystem()->fDestroyVertexBufferObjectX(vboHandle), "");
    X_Call(application.fGetGraphicsSystem()->fDestroyIndexBufferX(iboHandle), "");
    X_Call(application.fGetGraphicsSystem()->fDestroyVertexArrayObjectX(vaoHandle), "");
    X_Call(application.fGetGraphicsSystem()->fDestroyShaderX(vsHandle), "");
    X_Call(application.fGetGraphicsSystem()->fDestroyShaderX(fsHandle), "");

    //----------

    mLOG("Main loop started");
    X_Call(application.fLoopX(), "Application loop error");

    return 0;
}

XD::X
Game::fRunX()
{
    return XD::A_A;
}

XD_IMPLEMENT_ENTRY_POINT(Game, fStartup);

