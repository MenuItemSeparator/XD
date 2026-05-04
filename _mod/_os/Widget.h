// Base widget class representing a user interface element.
// Provides basic functionality for display, interaction, and state management.
#pragma once

#include <utility>

namespace XD{

class Widget
{
public:
    Widget();
    virtual ~Widget();

    virtual XD::Result fn_Show();
    virtual XD::Result fn_Hide();
    virtual XD::Result fn_Enable();
    virtual XD::Result fn_Disable();
    
    virtual XD::Result fn_SetPosition(int _x, int _y);
    virtual std::pair<int, int> fn_GetPosition() const;
    
    virtual XD::Result fn_SetSize(int _width, int _height);
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