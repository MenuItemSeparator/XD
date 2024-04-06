#pragma once

#define NOWINBASEINTERLOCK

#include <Windows.h>
#include "XDApplication_Minimal.h"
#include "XD_Widget.h"

namespace XD
{

class XD_ENGINE_API XD_WindowsWidget: public XD_Widget
    {
    public:
        XD_WindowsWidget(const XD_WidgetConfig& _config);

        virtual X fInitializeX() override;
        virtual X fTerminateX() override;
        virtual X fUpdateX() override;
        virtual void* fGetWidgetRawPtr() override;
        virtual bool fIsValid() override;

        LRESULT fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    private:
        HWND m_hwnd{};
        X fProcessEventsX();

        static LRESULT fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    };

}
