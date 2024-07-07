#pragma once
#include "XD_Engine_Minimal.h"
#include "../../XD_Renderer.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLRenderer final : public XD_Renderer
    {
    public:
        XD_OpenGLRenderer();

    public:
        virtual X fvInitializeX() override;
        virtual X fvShutdownX() override;

        static UPtr<XD_OpenGLRenderer> CreateRenderer();
    private:
        XD_Library m_library;
    };

}
