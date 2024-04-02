#pragma once
#include "XDApplication_Minimal.h"
#include "XD_Widget.h"

namespace XD
{

    class XD_ENGINE_API XD_Window_Widget : public XD_Widget
    {
    public:
        XD_Window_Widget() = default;

        virtual XD_Result fInitialize() = 0;
        virtual void fUpdate() = 0;
        virtual void* fGetWindowRawPtr() = 0;
        virtual XD_Result fCloseWindow() = 0;
        virtual bool fWindowShouldClose() = 0;

        static SPtr<XD_Window_Widget> fCreatePlatformWindow();
    };

}
