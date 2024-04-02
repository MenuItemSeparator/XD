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
        XD_WindowsWindow_Widget();

        virtual XD_Result fInitialize() override;
        virtual void fUpdate() override;
        virtual void* fGetWindowRawPtr() override;
        virtual XD_Result fCloseWindow() override;
        static LRESULT fPreHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    protected:
        virtual bool fWindowShouldClose() override;

    private:
        HWND m_hwnd{};
        bool m_isWindowCloseRequested{};

        XD_Result fProcessEvents();

        static LRESULT fSetupMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
        LRESULT fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
    };

}
