#include "Widget.h"
#include "../_app/Result.h"

namespace nXD {

Widget::Widget() 
    : Var_PositionX(0), Var_PositionY(0), Var_Width(100), Var_Height(100),
      Var_IsVisible(true), Var_IsEnabled(true) {
}

Widget::~Widget() {
}

nXD::Result 
Widget::fn_Show() 
{
    Var_IsVisible = true;
    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result 
Widget::fn_Hide() 
{
    Var_IsVisible = false;
    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result 
Widget::fn_Enable() 
{
    Var_IsEnabled = true;
    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result Widget::fn_Disable() {
    Var_IsEnabled = false;
    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result Widget::fn_SetPosition(int _x, int _y) {
    Var_PositionX = _x;
    Var_PositionY = _y;
    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

std::pair<int, int> Widget::fn_GetPosition() const {
    return std::make_pair(Var_PositionX, Var_PositionY);
}

nXD::Result Widget::fn_SetSize(int _width, int _height) {
    if (_width <= 0 || _height <= 0) {
        XD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        result.fn_AddErrorMessage("Invalid widget size");
        return result;
    }

    Var_Width = _width;
    Var_Height = _height;
    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

std::pair<int, int> Widget::fn_GetSize() const {
    return std::make_pair(Var_Width, Var_Height);
}

bool Widget::fn_IsVisible() const {
    return Var_IsVisible;
}

bool Widget::fn_IsEnabled() const {
    return Var_IsEnabled;
}

} // namespace nXD
