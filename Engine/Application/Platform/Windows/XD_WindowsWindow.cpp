#include "./XD_WindowsWindow.h"
#include "XD_WindowsWindow.h"

namespace
{
    const char* XD_WINDOW_CLASS_NAME = "XD Window";
}

namespace XD
{

    XD_Window::XD_Window(const XD_WindowConfig& _config) :
        XD_Window_Base(_config),
        m_hwnd(NULL)
    {

    }

    X
    XD_Window::fvInitializeX()
    {
        WNDCLASSEX wc{};
        MSG msg{};
        HMODULE hInstance = GetModuleHandle(NULL);

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_OWNDC;
        wc.lpfnWndProc   = fHandleMessage;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = m_config.m_windowName.c_str();
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if(!RegisterClassEx(&wc))
        {
            mLOG("Window class registration failed!");
            MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X::fFail();
        }

        m_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                m_config.m_windowName.c_str(),
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
            mLOG("Window Creation Failed!");
            MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X::fFail();
        }

        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);

        mLOG("Created window with title: " << m_config.m_windowName);

        return X::fSuccess();
    }

    X
    XD_Window::fvTerminateX()
    {
        if(m_hwnd == NULL) return X::fFail();

        mLOG("Window with title: " << m_config.m_windowName << " was terminated");

        HDC hdc = GetDC(m_hwnd);
        ReleaseDC(m_hwnd, hdc);
        DeleteDC(hdc);
        DestroyWindow(m_hwnd);
        m_hwnd = NULL;

        return X::fSuccess();
    }

    X
    XD_Window::fUpdateX()
    {
        X_Call(fProcessEventsX(), "Can't process window events");
        return X::fSuccess();
    }

    void*
    XD_Window::fvGetWindowRawPtr()
    {
        return m_hwnd;
    }

    bl
    XD_Window::fIsValid()
    {
        return m_hwnd != 0;
    }

    LRESULT
    XD_Window::fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        switch (_msg)
        {
        case WM_CLOSE:
            X_Call(m_onWindowWantsToCloseX.fInvoke(this), "Error while terminating window with title " << m_config.m_windowName);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(NULL);
            break;
        }

        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }

    i4 
    XD_Window::fSetPixelFormatToWindow(const PIXELFORMATDESCRIPTOR &_pfd) const
    {
        HDC dc = GetDC(m_hwnd);
        i4 pixelFormat = ChoosePixelFormat(dc, &_pfd);

        if(!pixelFormat)
        {
            mXD_ASSERTM(false, "Failed to find a suitable pixel format")
            return 0;
        }

        if(!SetPixelFormat(dc, pixelFormat, &_pfd))
        {
            mXD_ASSERTM(false, "Failed to set pixel format")
            return 0;
        }

        return pixelFormat;
    }

    X 
    XD_Window::fProcessEventsX()
    {
        mXD_ASSERT(m_hwnd != 0);

        MSG msg{};

        while (PeekMessage(&msg, m_hwnd, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return X::fSuccess();
    }

    LRESULT
    XD_Window::fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        XD_Window* windowInstance = nullptr;

        if (_msg == WM_NCCREATE)
        {
            windowInstance = static_cast<XD_Window*>(reinterpret_cast<CREATESTRUCT*>(_lParam)->lpCreateParams);

            SetLastError(0);
            if (!SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowInstance)))
            {
                if (GetLastError() != 0) return FALSE;
            }
        }
        else
        {
            windowInstance = reinterpret_cast<XD_Window*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
        }

        return windowInstance->fHandleMessage_Internal(_hwnd, _msg, _wParam, _lParam);
    }
}
