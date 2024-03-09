#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Author: UCKUHT
// Date: 2014-02-24
// Desc: float pair data container
//============================================================================//
#include "base/xd.h"

namespace nXD{
struct F2
{
	union {
		struct {fl4 x; fl4 y;};
		struct {fl4 a; fl4 b;};
	};
	F2() : a(0), b(0) {}
	F2(fl4 s) : a(s), b(s) {}
	F2(fl4 _x, fl4 _y) { x = _x; y = _y; }

	void
	fSet(fl4 _x, fl4 _y)
	{
		x = _x;
		y = _y;
	}
};

}//nXD
