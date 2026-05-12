// Base widget class representing a user interface element.
// Provides basic functionality for display, interaction, and state management.
#pragma once

#include <utility>

namespace nXD{

class Widget
{
public:
    Widget();
    virtual ~Widget();

    virtual nXD::Result fn_Show();
    virtual nXD::Result fn_Hide();
    virtual nXD::Result fn_Enable();
    virtual nXD::Result fn_Disable();
    
    virtual nXD::Result fn_SetPosition(int _x, int _y);
    virtual std::pair<int, int> fn_GetPosition() const;
    
    virtual nXD::Result fn_SetSize(int _width, int _height);
    virtual std::pair<int, int> fn_GetSize() const;

    bool fn_IsVisible() const;
    bool fn_IsEnabled() const;

protected:
    int Var_PositionX;
    int Var_PositionY;
    int Var_Width;
    int Var_Height;
    bool Var_IsVisible;
    bool Var_IsEnabled;
};

}