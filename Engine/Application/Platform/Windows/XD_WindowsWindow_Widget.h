#pragma once

#define NOWINBASEINTERLOCK

#include <Windows.h>
#include "XDApplication_Minimal.h"
#include "XD_Window_Widget.h"

namespace XD
{

    class XD_ENGINE_API XD_WindowsWindow_Widget: public XD_Window_Widget
    {
    public:
        XD_WindowsWindow_Widget(const XD_WindowConfig& _config);

        virtual XD_Result fInitialize() override;
        virtual XD_Result fTerminate() override;
        virtual void fUpdate() override;
        virtual void* fGetWindowRawPtr() override;
        virtual bool fIsValid() override;

        LRESULT fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    private:
        HWND m_hwnd{};
        void fProcessEvents();

        static LRESULT fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    };

}
