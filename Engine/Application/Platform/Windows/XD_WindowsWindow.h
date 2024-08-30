#pragma once

#define NOWINBASEINTERLOCK
#include <Windows.h>
#include <wingdi.h>

#include "XD_Engine_Minimal.h"
#include "../../XD_Window.h"

namespace XD
{
    class XD_ENGINE_API XD_Window : public XD_Window_Base
    {
    public:
        XD_Window(const XD_WindowConfig& _config);

        virtual X fvInitializeX() override;
        virtual X fvTerminateX() override;

        X fUpdateX();
        virtual void* fvGetWindowRawPtr() override;
        bl fIsValid();

        const std::string& fGetWidgetTitleName() const { return m_config.m_widgetName; }

        tOnWindowResizedDelegate& fOnWidgetResized() { return m_onWidgetResizedX; }
        tOnWindowWantsToClose& fOnWidgetWantsToCloseX() { return m_onWidgetWantsToCloseX; }

        LRESULT fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

    private:
        HWND m_hwnd{};

        X fProcessEventsX();
        static LRESULT __stdcall fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    };

}
