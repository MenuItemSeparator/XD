#include "XD_Renderer.h"

namespace XD
{
    SPtr<XD_Window> XD_Renderer::fCreateWindow_Internal(const XD_WindowConfig& _config)
    {
        return std::make_shared<XD_Window>(_config);
    }

    X XD_Renderer::fTerminateWindow_Internal(XD_Window* _window)
    {
        X_Call(_window->fvTerminateX(), "Can't terminate window");
        return A_A;
    }

}
