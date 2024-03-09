#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: 2d space vector. Out dated file.
//============================================================================//

#include "base/xd.h"
#include "xd_f2.h"

//============================================================================//
namespace nXD {

struct XD_VECTOR2 : public nXD::F2
{
	void
	fSet(fl4 _x, fl4 _y)
	{
		x = _x;
		y = _y;
	}

	void
	fDrop()
	{
		x = y = 0;
	}

	void
	fMove(fl4 _x, fl4 _y)
	{
		x += _x;
		y += _y;
	}
};

}
//============================================================================//
