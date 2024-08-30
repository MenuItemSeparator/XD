#include "XD_GraphicsSystem.h"
#include "./GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.h"

namespace XD
{
    XD_GraphicsSystem::XD_GraphicsSystem() :
        m_renderer()
    {

    }

    X
    XD_GraphicsSystem::fInitializeX(const XD_GraphicsConfig& _config)
    {
        switch(_config.m_rendererType)
        {
        case eRendererType::OpenGL:
            m_renderer = std::make_unique<XD_OpenGLRenderer>();
            break;
        default:
            mLOG("Unknown type of renderer")
            return X_X;
        }

        X_Call(m_renderer->fvInitializeX(), "Can't initialize target renderer");
        return A_A;
    }

    X XD_GraphicsSystem::fSetCurrentContextX(SPtr<XD_Window> _window)
    {
        X_Call(m_renderer->fvSetCurrentContextX(_window), "Failed when setting context to renderer");
        return A_A;
    }

    X
    XD_GraphicsSystem::fShutdownX()
    {
        return A_A;
    }
}
