#include "XD_WindowsWindow_Widget.h"

namespace
{
    const char* XD_WINDOW_CLASS_NAME = "XD Window";
}

namespace XD
{

    XD_WindowsWindow_Widget::XD_WindowsWindow_Widget(const XD_WindowConfig& _config) :
        XD_Window_Widget(_config),
        m_hwnd(NULL)
    {

    }

    XD_Result XD_WindowsWindow_Widget::fInitialize()
    {
        WNDCLASSEX wc{};
        MSG msg{};
        HMODULE hInstance = GetModuleHandle(NULL);

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = fHandleMessage;
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
            this
        );

        if(m_hwnd == NULL)
        {
            MessageBox(NULL, "Window Creation Failed!", "Error!",
                       MB_ICONEXCLAMATION | MB_OK);
            return XD_Result::Fail();
        }

        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);

        mLOG("Created window with title: " << m_config.m_windowName);

        return XD_Result::Success();
    }

    XD_Result XD_WindowsWindow_Widget::fTerminate()
    {
        if(m_hwnd == NULL) return XD_Result::Fail();

        DestroyWindow(m_hwnd);
        m_hwnd = NULL;

        return XD_Result::Success();
    }

    void XD_WindowsWindow_Widget::fUpdate()
    {
        fProcessEvents();
    }

    void* XD_WindowsWindow_Widget::fGetWindowRawPtr()
    {
        return &m_hwnd;
    }

    bool XD_WindowsWindow_Widget::fIsValid()
    {
        return m_hwnd != 0;
    }

    void XD_WindowsWindow_Widget::fOnWindowRequestedClosing_Internal()
    {
        m_hwnd = NULL;
    }

    void XD_WindowsWindow_Widget::fProcessEvents()
    {
        mXD_ASSERT(m_hwnd != 0);

        MSG msg{};

        while (PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT XD_WindowsWindow_Widget::fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        XD_WindowsWindow_Widget* windowInstance = nullptr;

        if (_msg == WM_NCCREATE)
        {
            windowInstance = static_cast<XD_WindowsWindow_Widget*>(reinterpret_cast<CREATESTRUCT*>(_lParam)->lpCreateParams);

            SetLastError(0);
            if (!SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowInstance)))
            {
                if (GetLastError() != 0) return FALSE;
            }
        }
        else
        {
            windowInstance = reinterpret_cast<XD_WindowsWindow_Widget*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
        }

        switch (_msg)
        {
        case WM_CLOSE:
            windowInstance->fOnWindowRequestedClosing_Internal();
            break;
        case WM_DESTROY:
            PostQuitMessage(NULL);
            break;
        }

        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }
}
