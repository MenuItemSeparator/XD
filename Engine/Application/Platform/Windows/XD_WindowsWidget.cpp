#include "XD_WindowsWidget.h"

namespace
{
    const char* XD_WINDOW_CLASS_NAME = "XD Window";
}

namespace XD
{

    XD_Widget::XD_Widget(const XD_WidgetConfig& _config) :
        XD_Widget_Base(_config),
        m_hwnd(NULL)
    {

    }

    X
    XD_Widget::fvInitializeX()
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
        wc.lpszClassName = XD_WINDOW_CLASS_NAME;
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if(!RegisterClassEx(&wc))
        {
            MessageBox(NULL, "Window Registration Failed!", "Error!",
                       MB_ICONEXCLAMATION | MB_OK);
            return X::fFail();
        }

        m_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                XD_WINDOW_CLASS_NAME,
                m_config.m_widgetName.c_str(),
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
            return X::fFail();
        }

        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);

        mLOG("Created window with title: " << m_config.m_widgetName);

        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
            PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
            32,                   // Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                   // Number of bits for the depthbuffer
            8,                    // Number of bits for the stencilbuffer
            0,                    // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        HDC dc = GetDC(m_hwnd);
        i4 pixelFormatNum = ChoosePixelFormat(dc, &pfd);

        if(!pixelFormatNum)
        {
            mLOG("Unable to choose pixel format");
            return X::fFail();
        }

        if(!SetPixelFormat(dc, pixelFormatNum, &pfd))
        {
            mLOG("Can't set pixel format to hdc");
            return X::fFail();
        }

        return X::fSuccess();
    }

    X
    XD_Widget::fvTerminateX()
    {
        if(m_hwnd == NULL) return X::fFail();

        DestroyWindow(m_hwnd);
        m_hwnd = NULL;

        return X::fSuccess();
    }

    X
    XD_Widget::fUpdateX()
    {
        X_Call(fProcessEventsX(), "Can't process window events");
        return X::fSuccess();
    }

    void*
    XD_Widget::fGetWidgetRawPtr()
    {
        return &m_hwnd;
    }

    bl
    XD_Widget::fIsValid()
    {
        return m_hwnd != 0;
    }

    LRESULT
    XD_Widget::fHandleMessage_Internal(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        switch (_msg)
        {
        case WM_CLOSE:
            X_Call(m_onWidgetWantsToCloseX.fInvoke(this), "Error while terminating window with title " << m_config.m_widgetName);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(NULL);
            break;
        }

        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }

    X
    XD_Widget::fProcessEventsX()
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
    XD_Widget::fHandleMessage(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        XD_Widget* windowInstance = nullptr;

        if (_msg == WM_NCCREATE)
        {
            windowInstance = static_cast<XD_Widget*>(reinterpret_cast<CREATESTRUCT*>(_lParam)->lpCreateParams);

            SetLastError(0);
            if (!SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowInstance)))
            {
                if (GetLastError() != 0) return FALSE;
            }
        }
        else
        {
            windowInstance = reinterpret_cast<XD_Widget*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
        }

        return windowInstance->fHandleMessage_Internal(_hwnd, _msg, _wParam, _lParam);
    }
}
