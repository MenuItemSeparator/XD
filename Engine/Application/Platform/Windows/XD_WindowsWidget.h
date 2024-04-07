#pragma once

#define NOWINBASEINTERLOCK
#include <Windows.h>
#include "XDEngine_Minimal.h"
#include "../../XD_Widget.h"

namespace XD
{
    class XD_ENGINE_API XD_Widget
    {
    public:
        XD_Widget(const XD_WidgetConfig& _config);
        XD_Widget(const XD_Widget&) = delete;
        XD_Widget& operator=(const XD_Widget&) = delete;

        X fInitializeX();
        X fTerminateX();
        X fUpdateX();
        void* fGetWidgetRawPtr();
        bool fIsValid();

        const std::string& fGetWidgetTitleName() const { return m_config.m_widgetName; }

        tOnWidgetResizedDelegate& fOnWidgetResized() { return m_onWidgetResizedX; }
        tOnWidgetWantsToClose& fOnWidgetWantsToCloseX() { return m_onWidgetWantsToCloseX; }

        LRESULT fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

    private:
        HWND m_hwnd{};
        XD_WidgetConfig m_config;
        tOnWidgetResizedDelegate m_onWidgetResizedX;
        tOnWidgetWantsToClose m_onWidgetWantsToCloseX;

        X fProcessEventsX();
        static LRESULT fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    };

}
