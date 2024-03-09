#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: integer point of 2 values.
//============================================================================//
#include "base/xd.h"
#include "xd_i2.h"
//============================================================================//
struct XD_POINT2 : public nXD::I2
{
	void
	fSet(si4 v_x, si4 v_y) {
		x = v_x;
		y = v_y;
	}

	void
	fDrop() {
		x = y = 0;
	}

	void
	fMove(si4 v_x, si4 v_y) {
		x += v_x;
		y += v_y;
	}
};
//============================================================================//
