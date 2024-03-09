#ifndef _XD_I2_H_INCLUDED
#define _XD_I2_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Author: UCKUHT
// Date: 2014-02-25
// Desc: int32_t pair
//============================================================================//
#include "base/xd.h"
//============================================================================//
namespace nXD{
struct I2
{
	union{
		struct{si4 x; si4 y;};
		si4 data[2];
	};

	I2() {}
	I2(si4 _s) : x(_s), y(_s) {}
	I2(si4 _x, si4 _y) : x(_x), y(_y) {}

	void
	fSet(si4 _x, si4 _y){
		x = _x;
		y = _y;
	}

	si4
	fDistanceQuad(const I2& _point) const {
		si4 A = x - _point.x;
		si4 B = y - _point.y;
		return A*A + B*B;
	}

	bln
	fZero() {
		return x == y == 0;
	}

	bool operator != (const I2& _r)
	{
		return (x != _r.x) && (y != _r.y);
	}
};
}//nXD
//============================================================================//
#endif // _XD_I2_H_INCLUDED
