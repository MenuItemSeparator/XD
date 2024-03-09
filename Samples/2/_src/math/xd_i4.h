#ifndef _XD_I4_H_INCLUDED
#define _XD_I4_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Author: UCKUHT
// Date: 2014-05-04
// Desc: int_32 quad
//============================================================================//
#include "base/xd.h"

#include "xd_i2.h"

namespace nXD{
struct I4
{
	union{
		struct {si4 l; si4 t; si4 r; si4 d;};
		si4 data[4];
	};

	I4() {}
	I4(si4 _s) { fSet(_s,_s,_s,_s); }
	I4(si4 _l, si4 _t, si4 _r, si4 _d) { fSet(_l,_t,_r,_d); }

	void
	fSet(si4 _l, si4 _t, si4 _r, si4 _d)
	{
		l = _l;
		t = _t;
		r = _r;
		d = _d;
	}

	I2
	fSize()
	{
		return I2(r-l, d-t);
	}
};
}//nXD

#endif // XD_I4_H_INCLUDED
