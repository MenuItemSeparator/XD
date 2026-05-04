#include "WindowsWidget.h"
#include "../../_app/Result.h"

namespace XD {

WindowsWidget::WindowsWidget() : Widget(), Var_WindowHandle(nullptr) {
}

WindowsWidget::~WindowsWidget() {
    if (Var_WindowHandle != nullptr) {
        DestroyWindow(Var_WindowHandle);
        Var_WindowHandle = nullptr;
    }
}

XD::Result WindowsWidget::fn_Show() {
    if (Var_WindowHandle != nullptr) {
        ShowWindow(Var_WindowHandle, SW_SHOW);
    }
    Var_IsVisible = true;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result WindowsWidget::fn_Hide() {
    if (Var_WindowHandle != nullptr) {
        ShowWindow(Var_WindowHandle, SW_HIDE);
    }
    Var_IsVisible = false;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result WindowsWidget::fn_Enable() {
    if (Var_WindowHandle != nullptr) {
        EnableWindow(Var_WindowHandle, TRUE);
    }
    Var_IsEnabled = true;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result WindowsWidget::fn_Disable() {
    if (Var_WindowHandle != nullptr) {
        EnableWindow(Var_WindowHandle, FALSE);
    }
    Var_IsEnabled = false;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result WindowsWidget::fn_SetPosition(int _x, int _y) {
    Var_PositionX = _x;
    Var_PositionY = _y;

    if (Var_WindowHandle != nullptr) {
        SetWindowPos(Var_WindowHandle, nullptr, _x, _y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

std::pair<int, int> WindowsWidget::fn_GetPosition() const {
    return std::make_pair(Var_PositionX, Var_PositionY);
}

XD::Result WindowsWidget::fn_SetSize(int _width, int _height) {
    if (_width <= 0 || _height <= 0) {
        XD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        result.fn_AddErrorMessage("Invalid widget size");
        return result;
    }

    Var_Width = _width;
    Var_Height = _height;

    if (Var_WindowHandle != nullptr) {
        SetWindowPos(Var_WindowHandle, nullptr, 0, 0, _width, _height, SWP_NOMOVE | SWP_NOZORDER);
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

std::pair<int, int> WindowsWidget::fn_GetSize() const {
    return std::make_pair(Var_Width, Var_Height);
}

HWND WindowsWidget::fn_GetHandle() const {
    return Var_WindowHandle;
}

XD::Result WindowsWidget::fn_SetHandle(HWND _handle) {
    Var_WindowHandle = _handle;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

} // namespace XD
