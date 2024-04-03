#include "XD_WindowsWindow_Widget.h"

namespace
{
    const char* XD_WINDOW_CLASS_NAME = "XD Window";

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch(msg)
        {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }
}

namespace XD
{

XD_WindowsWindow_Widget::XD_WindowsWindow_Widget(const XD_WindowConfig& _config) :
        XD_Window_Widget(_config),
        m_hwnd(NULL),
        m_isWindowCloseRequested(false)
    {

    }

    XD_Result XD_WindowsWindow_Widget::fInitialize()
    {
        WNDCLASSEX wc{};
        MSG msg{};
        HMODULE hInstance = GetModuleHandle(NULL);

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = fSetupMessage;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = XD_WINDOW_CLASS_NAME;
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if(!RegisterClassEx(&wc))
        {
            MessageBox(NULL, "Window Registration Failed!", "Error!",
                       MB_ICONEXCLAMATION | MB_OK);
            return XD_Result::Fail();
        }

        m_hwnd = CreateWindowEx
        (
            WS_EX_CLIENTEDGE,
            XD_WINDOW_CLASS_NAME,
            m_config.m_windowName.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            640,
            360,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if(m_hwnd == NULL)
        {
            MessageBox(NULL, "Window Creation Failed!", "Error!",
                       MB_ICONEXCLAMATION | MB_OK);
            return XD_Result::Fail();
        }

        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);

        return XD_Result::Success();
    }

    XD_Result XD_WindowsWindow_Widget::fDeinitialize()
    {
        return XD_Result::Success();
    }

    LRESULT XD_WindowsWindow_Widget::fSetupMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        if (_msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* creationClass = reinterpret_cast<CREATESTRUCTW*>(_lParam);
            XD_WindowsWindow_Widget* window = static_cast<XD_WindowsWindow_Widget*>(creationClass->lpCreateParams);
            SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            SetWindowLongPtr(_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&XD_WindowsWindow_Widget::fPreHandleMessage));
            return window->fHandleMessage(_hwnd, _msg, _wParam, _lParam);
        }
        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }

    LRESULT XD_WindowsWindow_Widget::fPreHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        XD_WindowsWindow_Widget* const window = reinterpret_cast<XD_WindowsWindow_Widget*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
        return window->fHandleMessage(_hwnd, _msg, _wParam, _lParam);
    }

    void XD_WindowsWindow_Widget::fUpdate()
    {
        //@TODO: process result
        bool result = fProcessEvents();
    }

    void* XD_WindowsWindow_Widget::fGetWindowRawPtr()
    {
        return nullptr;
    }

    XD_Result XD_WindowsWindow_Widget::fCloseWindow()
    {
        m_isWindowCloseRequested = true;
        return XD_Result::Success();
    }

    bool XD_WindowsWindow_Widget::fWindowShouldClose()
    {
        return m_isWindowCloseRequested;
    }

    XD_Result XD_WindowsWindow_Widget::fProcessEvents()
    {
        MSG msg{};
        BOOL result = PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE);

        if (result > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            return XD_Result::Success();
        }

        return XD_Result::Fail();
    }

    LRESULT XD_WindowsWindow_Widget::fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        switch (_msg)
        {
        case WM_DESTROY:
            PostQuitMessage(NULL);
            return 0;
        }

        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }
}
