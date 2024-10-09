#include "Graphics/XD_Graphics_Minimal.h"
#include "Application/XD_Application.h"
#include "XD_Test_Minimal.h"

namespace XD
{
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
            X_Call(fGetTimerManager()->fStartTimerX(timerHandle, 0.5, this, &SetClearColorApplication::fStopApplication), "Can't start app stopper timer");
            
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
        XD::XD_ApplicationConfig applicationConfig{};
        tUptr<SetClearColorApplication> application = std::make_unique<SetClearColorApplication>(applicationConfig);
        mLOG("Test clear color initialization started");
        X_Call(application->fvInitializeX(), "Set clear color test application initialization error");
        mLOG("Test clear color initialization ended");

        mLOG("Test clear color loop started");
        X_Call(application->fLoopX(), "Application loop error");
        mLOG("Test clear color loop ended");
        return A_A;
    }

    class DrawQuadApplication : public XD_Application
    {
    public:
        DrawQuadApplication(const XD_ApplicationConfig& _config) :
            XD_Application(_config)
        {}

        XD::VertexBufferObjectHandle m_vboHandle;
        XD::IndexBufferObjectHandle m_iboHandle;
        XD::ShaderProgramHandle m_programHandle;

        virtual X fvInitializeX() override
        {
            X_Call(XD_Application::fvInitializeX(), "Super initialization fail");

            TimerHandle timerHandle{};
            X_Call(fGetTimerManager()->fStartTimerX(timerHandle, 0.4, this, &DrawQuadApplication::fStopApplication), "Can't start app stopper timer");

            XD::VertexBufferLayoutHandle layoutHandle;
            static std::vector<XD::eShaderDataType> shaderTypes{ XD::eShaderDataType::Float3 };
            X_Call(fGetGraphicsSystem()->fCreateVertexBufferLayoutX(layoutHandle, shaderTypes), "Can't create vb layout");

            static float vboRawData[] = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };
            static XD::Memory vboMem{vboRawData, sizeof(vboRawData)};
            X_Call(fGetGraphicsSystem()->fCreateVertexBufferObjectX(m_vboHandle, &vboMem, layoutHandle), "Can't create vbo");

            static int iboRawData[] = {
                0, 1, 3,   // first triangle
                1, 2, 3 
            };
            static XD::Memory iboMem{iboRawData, sizeof(iboRawData)};
            X_Call(fGetGraphicsSystem()->fCreateIndexBufferX(m_iboHandle, &iboMem), "Can't create ibo");

            XD::ShaderHandle vsHandle;
            static std::string vsFilePath = cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestVS.vs";
            X_Call(fGetGraphicsSystem()->fCreateShaderX(vsHandle, vsFilePath), "Can't create vertex shader");

            XD::ShaderHandle fsHandle;
            static std::string fsFilePath = cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestFS.fs";
            X_Call(fGetGraphicsSystem()->fCreateShaderX(fsHandle, fsFilePath), "Can't create fragment shader");

            X_Call(fGetGraphicsSystem()->fCreateShaderProgramX(m_programHandle, vsHandle, fsHandle), "Can't create shader program");

            XD_Color col{1.0f, 0.2f, 0.2f, 1.0f};
            X_Call(fGetGraphicsSystem()->fSetClearColorX(col), "");
                
            return A_A;
        }

    protected:
        virtual X fvLoopX_Internal(f8 _deltaTime) override
        {
            X_Call(fGetGraphicsSystem()->fBindVertexBufferObjectX(m_vboHandle), "");
            X_Call(fGetGraphicsSystem()->fBindIndexBufferObjectX(m_iboHandle), "");
            X_Call(fGetGraphicsSystem()->fBindShaderProgramX(m_programHandle), "");
            X_Call(fGetGraphicsSystem()->fSubmitPrimitiveX(), "");

            return A_A;
        }

    private:
        void fStopApplication()
        {
            fvTerminateX().fCheck();
        }
    };

    X
    Test_DrawQuad()
    {
        XD::XD_ApplicationConfig applicationConfig{};
        applicationConfig.m_displayName = "Draw quad";
        tUptr<DrawQuadApplication> application = std::make_unique<DrawQuadApplication>(applicationConfig);
        X_Call(application->fvInitializeX(), "Draw quad test application initialization error");
        X_Call(application->fLoopX(), "Application loop error");
        return A_A;
    }
}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_DrawQuad(), "Drawing test quad was failed");
    mLOG("Test draw quad completed successfully");
    X_Call(XD::Test_SetClearColor(), "Change clear color test was failed");
    mLOG("Test clear color completed successfully");

    return 0;
}
