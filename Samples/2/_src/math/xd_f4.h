#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: float 4 base class.
//============================================================================//
#include <math.h>
#include "base/xd_type.h"
#include "base/xd_code.h"

namespace nXD{
struct F4
{
	union {
		struct{fl4 x,y,z,w;};
		struct{fl4 r,g,b,a;};
		struct{fl4 left, right, top, bot;};
		fl4 data[4];
	};
	fl4 operator() (szt num)
	{
		mDEBUGONLY()
		{
			if(num > 3)
			mERRORF("bad index");
		}
		return data[num];
	}

	F4() {}

	F4(fl4 s) : x(s), y(s), z(s), w(s) {}

	F4(fl4 _x, fl4 _y, fl4 _z)
	{
		fSet(_x,_y,_z, 1);
	}

	F4(fl4 _x, fl4 _y, fl4 _z, fl4 _w)
	{
		fSet(_x,_y,_z,_w);
	}

	void
	fSet(fl4 _x, fl4 _y, fl4 _z, fl4 _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	fl4*
	fGet()
	{
		return data;
	}

	fl4
	fDistanceXY(const F4& _point)
	{
		fl4 A = (x - _point.x);
		fl4 B = (y - _point.y);
		return sqrtf( A*A + B*B );
	}
};

struct F4_Scaler : public F4 {
	F4_Scaler(fl4 _x, fl4 _y, fl4 _z) : F4(_x, _y, _z, 1) {}
};
struct F4_Rotator : public F4 {
	F4_Rotator(fl4 _x, fl4 _y, fl4 _z) : F4(_x, _y, _z, 1) {}
};
struct F4_Translator : public F4 {
	F4_Translator(fl4 _x, fl4 _y, fl4 _z) : F4(_x, _y, _z, 1) {}
};

}
