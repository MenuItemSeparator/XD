#include "Graphics/XD_Graphics_Minimal.h"
#include "Application/XD_Application.h"
#include "XD_Test_Minimal.h"


namespace XD
{
    XD::VertexBufferObjectHandle vboHandle;
    XD::IndexBufferObjectHandle iboHandle;
    XD::ShaderProgramHandle programHandle;

    XD::XD_ApplicationConfig applicationConfig{};

    class SetClearColorApplication : public XD_Application
    {
    public:
        SetClearColorApplication(const XD_ApplicationConfig& _config) :
            XD_Application(_config)
        {}

        virtual X fvInitializeX() override
        {
            X_Call(XD_Application::fvInitializeX(), "Super initialization fail");

            TimerHandle timerHandle{};
            X_Call(fGetTimerManager()->fStartTimerX(timerHandle, 1.0, *this, &SetClearColorApplication::fStopApplication), "Can't start app stopper timer");
            
            return A_A;
        }

    protected:
        virtual X fvLoopX_Internal(f8 _deltaTime) override
        {
            static XD_Color clearColor{1.0f, 0.5f, 0.0f, 1.0f};
            clearColor.m_r = fmod(clearColor.m_r + 0.03f, 1.0f);
            clearColor.m_g = fmod(clearColor.m_g + 0.06f, 1.0f);
            clearColor.m_b = fmod(clearColor.m_b + 0.09f, 1.0f);

            X_Call(m_graphicsSystem.fSetClearColorX(clearColor), "Error while setting clear color.");
            return A_A;
        }

    private:
        void fStopApplication()
        {
            fvTerminateX().fCheck();
        }
    };

    X
    Test_SetClearColor()
    {
        tUptr<SetClearColorApplication> application = std::make_unique<SetClearColorApplication>(applicationConfig);
        X_Call(application->fvInitializeX(), "Set clear color test application initialization error");
        X_Call(application->fLoopX(), "Application loop error");
        return A_A;
    }

/*
    X
    Test_DrawQuad()
    {
        //Application initialization

        TestWrapper wrapper{};

        X_Call(application->fvInitializeX(), "Application initialization error");

        TimerHandle timerHandle{};
        X_Call(application->fGetTimerManager()->fStartTimerX(timerHandle, 1.0, wrapper, &TestWrapper::fStopApplication), "Can't start app stopper timer");

        //Application initialization end

        //Graphics objects setup

        XD::VertexBufferLayoutHandle layoutHandle;
        std::vector<XD::eShaderDataType> shaderTypes{ XD::eShaderDataType::Float3 };
        X_Call(application->fGetGraphicsSystem()->fCreateVertexBufferLayoutX(layoutHandle, shaderTypes), "Can't create vb layout");

        float vboRawData[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        XD::Memory vboMem{vboRawData, sizeof(vboRawData)};
        X_Call(application->fGetGraphicsSystem()->fCreateVertexBufferObjectX(vboHandle, &vboMem, layoutHandle), "Can't create vbo");

        int iboRawData[] = {
            0, 1, 3,   // first triangle
            1, 2, 3 
        };
        XD::Memory iboMem{iboRawData, sizeof(iboRawData)};
        X_Call(application->fGetGraphicsSystem()->fCreateIndexBufferX(iboHandle, &iboMem), "Can't create ibo");

        XD::ShaderHandle vsHandle;
        X_Call(application->fGetGraphicsSystem()->fCreateShaderX(vsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestVS.vs"), "Can't create vertex shader");
        XD::ShaderHandle fsHandle;
        X_Call(application->fGetGraphicsSystem()->fCreateShaderX(fsHandle, cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestFS.fs"), "Can't create fragment shader");

        X_Call(application->fGetGraphicsSystem()->fCreateShaderProgramX(programHandle, vsHandle, fsHandle), "Can't create shader program");

        //Graphics objects setup end

        mLOG("Test main loop started");
        X_Call(application->fLoopX(), "Application loop error");
        mLOG("Test main loop end");

        return A_A;
    }
*/
}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_SetClearColor(), "Change clear color test was failed");
    //X_Call(XD::Test_DrawQuad(), "Drawing test quad was failed");
    return 0;
}
