#include "XD_GraphicsSystem.h"
#include "./GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.h"

namespace XD
{
    XD_GraphicsSystem::XD_GraphicsSystem() :
        m_renderer()
    {

    }

    XD_GraphicsSystem::~XD_GraphicsSystem()
    {
    }
    

    X XD_GraphicsSystem::fInitializeX(const XD_GraphicsConfig &_config)
    {
        switch(_config.m_rendererType)
        {
        case eRendererType::OpenGL:
            m_renderer = std::make_unique<XD_OpenGLRenderer>();
            break;
        default:
            mXD_ASSERTM(false, "Unknown type of renderer")
            return X_X;
        }

        X_Call(m_renderer->fvInitializeX(_config.m_hwnd), "Can't initialize target renderer");
        return A_A;
    }

    X
    XD_GraphicsSystem::fShutdownX()
    {
        if(!m_renderer) return X_X;
        
        X_Call(m_renderer->fvShutdownX(), "Error while shutdown renderer");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBeginFrameX()
    {
        X_Call(m_renderer->fvBeginFrameX(), "Error while begin frame in renderer");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fEndFrameX()
    {
        X_Call(m_renderer->fvEndFrameX(), "Error while end frame in renderer");
        return A_A;
    }
}
