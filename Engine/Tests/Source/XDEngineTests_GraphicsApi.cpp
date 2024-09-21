#include "Graphics/XD_Graphics_Minimal.h"
#include "Application/XD_Application.h"
#include "XD_Test_Minimal.h"


namespace XD
{
    XD::VertexBufferObjectHandle vboHandle;
    XD::IndexBufferObjectHandle iboHandle;
    XD::ShaderProgramHandle programHandle;

    XD::XD_ApplicationConfig applicationConfig{};
    XD::XD_Application application{applicationConfig};

    class TestWrapper
    {
    public:
        X fRenderLoopCallbackX()
        {
            X_Call(application.fGetGraphicsSystem()->fBindVertexBufferObjectX(vboHandle), "");
            X_Call(application.fGetGraphicsSystem()->fBindIndexBufferObjectX(iboHandle), "");
            X_Call(application.fGetGraphicsSystem()->fBindShaderProgramX(programHandle), "");
            X_Call(application.fGetGraphicsSystem()->fRenderX(), "");

            return A_A;
        }
    };

    X
    Test_DrawQuad()
    {
        //Application initialization

        TestWrapper wrapper{};

        X_Call(application.fvInitializeX(), "Application initialization error");
        application.fOnRenderLoopCallback().fBind(wrapper, &TestWrapper::fRenderLoopCallbackX);

        //Application initialization end

        //Graphics objects setup

        XD::VertexBufferLayoutHandle layoutHandle;
        std::vector<XD::eShaderDataType> shaderTypes{ XD::eShaderDataType::Float3 };
        X_Call(application.fGetGraphicsSystem()->fCreateVertexBufferLayoutX(layoutHandle, shaderTypes), "Can't create vb layout");

        float vboRawData[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        XD::Memory vboMem{vboRawData, sizeof(vboRawData)};
        X_Call(application.fGetGraphicsSystem()->fCreateVertexBufferObjectX(vboHandle, &vboMem, layoutHandle), "Can't create vbo");

        int iboRawData[] = {
            0, 1, 3,   // first triangle
            1, 2, 3 
        };
        XD::Memory iboMem{iboRawData, sizeof(iboRawData)};
        X_Call(application.fGetGraphicsSystem()->fCreateIndexBufferX(iboHandle, &iboMem), "Can't create ibo");

        XD::ShaderHandle vsHandle;
        X_Call(application.fGetGraphicsSystem()->fCreateShaderX(vsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestVS.vs"), "Can't create vertex shader");
        XD::ShaderHandle fsHandle;
        X_Call(application.fGetGraphicsSystem()->fCreateShaderX(fsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestFS.fs"), "Can't create fragment shader");

        X_Call(application.fGetGraphicsSystem()->fCreateShaderProgramX(programHandle, vsHandle, fsHandle), "Can't create shader program");

        //Graphics objects setup end

        mLOG("Test main loop started");
        X_Call(application.fLoopX(), "Application loop error");
        mLOG("Test main loop end");

        return A_A;
    }
}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_DrawQuad(), "Drawing test quad was failed");
    return 0;
}
