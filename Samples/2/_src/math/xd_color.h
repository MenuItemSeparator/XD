#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: color handler struct
//============================================================================//
#include "base/xd.h"
#include "base/xd_code.h"

#include "xd_f4.h"

namespace nXD{
struct XD_COLOR : public nXD::F4
{
	XD_COLOR() : nXD::F4(0,0,0,1) {}
	XD_COLOR(ui4 _color);
	XD_COLOR(fl4 r, fl4 g, fl4 b, fl4 a) : F4(r,g,b,a) {}

	mCOMMENT("ARGB");
	enum COLORS
	{
		eAlpha		= 0xff000000,
		eBlack		= 0x00000000,
		eWhite 		= 0x00ffffff,
		eRed 		= 0x00ff0000,
		eBlue 		= 0x000000ff,
		eGreen		= 0x0000ff00,
		eNiceSky	= 0x0087ceeb,
		eMandarin	= 0xffffa474,
		eEmerald	= 0xff50c878,
		eMint		= 0xff98ff98,
	};
};

}// nXD
