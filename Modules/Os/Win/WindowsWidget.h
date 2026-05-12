// Windows-specific widget class implementing UI element for Windows OS.
// Provides platform-specific functionality for display, interaction, and state management.
#pragma once

#include "../Widget.h"
#include <windows.h>

namespace nXD{

class WindowsWidget : public Widget
{
public:
    WindowsWidget();
    virtual ~WindowsWidget();

    virtual nXD::Result fn_Show() override;
    virtual nXD::Result fn_Hide() override;
    virtual nXD::Result fn_Enable() override;
    virtual nXD::Result fn_Disable() override;
    
    virtual nXD::Result fn_SetPosition(int _x, int _y) override;
    virtual std::pair<int, int> fn_GetPosition() const override;
    
    virtual nXD::Result fn_SetSize(int _width, int _height) override;
    virtual std::pair<int, int> fn_GetSize() const override;

private: // OS specific types.
    HWND fn_GetHandle() const;
    nXD::Result fn_SetHandle(HWND _handle);

private:
    HWND Var_WindowHandle;
};

}