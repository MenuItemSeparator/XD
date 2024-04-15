#pragma once
#include "XDEngine_Minimal.h"
#include "../../XD_GraphicsApi_Interface.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLGraphicsApi : public XD_GraphicsApi_Interface
    {
        friend class XD_GraphicsApi_Interface;
    public:
        XD_OpenGLGraphicsApi();
        X fInitializeX();
        X fShutdownX();
    };
}
