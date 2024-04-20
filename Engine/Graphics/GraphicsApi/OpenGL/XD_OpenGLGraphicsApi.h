#pragma once
#include "XDEngine_Minimal.h"
#include "../../XD_GraphicsApi.h"

namespace XD
{
class XD_ENGINE_API XD_OpenGLGraphicsApi : public XD_GraphicsApi
    {
    friend class XD_GraphicsApi;
    public:
        XD_OpenGLGraphicsApi();
        X fInitializeX();
        X fShutdownX();
    };
}
