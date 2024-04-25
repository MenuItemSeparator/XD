#include "XD_GraphicsContext.h"
#include "GraphicsApi/OpenGL/XD_OpenGLRenderer.h"

namespace XD
{
    XD_GraphicsContext::XD_GraphicsContext() :
        m_renderer()
    {

    }

    X
    XD_GraphicsContext::fInitializeX(const XD_GraphicsConfig& _config)
    {
        switch(_config.m_rendererType)
        {
        case eRendererType::OpenGL:
            m_renderer = XD_OpenGLRenderer::CreateRenderer(); break;
        default:
            mLOG("Unknown type of renderer")
            return X_X;
        }

        X_Call(m_renderer->fvInitializeX(), "Can't initialize target renderer");
        return A_A;
    }
    
    X
    XD_GraphicsContext::fShutdownX()
    {
        return A_A;
    }
}
