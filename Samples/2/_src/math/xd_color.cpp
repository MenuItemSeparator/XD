#include "xd_color.h"
#include "xd_bt4.h"
#include "base/xd_cast.h"
#include "base/xd.h"

namespace nXD {

XD_COLOR::XD_COLOR(ui4 _color)
{
	XD_BT4& color = RCAST(XD_BT4&, _color);

	this->a = color.a/255.f;
	this->r = color.r/255.f;
	this->g = color.g/255.f;
	this->b = color.b/255.f;
}

}
