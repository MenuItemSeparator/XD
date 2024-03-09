#pragma once
// LICENSE.txt

#include <math.h>

#include "base/xd.h"
#include "base/xd_lang.h"
#include "base/xd_code.h"
#include "base/xd_cast.h"

#include "xd_bt4.h"
//============================================================================//
namespace nXD{

class Math
{
public xd_functional:
	static
	si4
	iF4Comp(fl4 left, fl4 right, fl4 accuracy = 0.0001f)
	{// Too long operation.
		fl4 res = left - right + accuracy;

		if(res < 0)
		{//2 l < R
			return v_W;
		}//2
		else if(fabs(res) < accuracy * 2)
		{//2
			return W_W;
		}//2
		else
			return W_v;

	}

	static
	si4
	iF4ToSi4(fl4 data4ptr[4], ui1 scalar)
	{
		XD_BT4 result;
		result.r = scalar * data4ptr[0];
		result.g = scalar * data4ptr[1];
		result.b = scalar * data4ptr[2];
		result.a = scalar * data4ptr[3];
		return result.core;
	}

	static
	void
	iSi4ToF4(si4 value, ui1 scalar, fl4* result4ptr)
	{
		mASSERT(scalar, "Zero dividing error");
		XD_BT4 target = value;
		result4ptr[0] = target.r / SCAST(fl4, scalar);
		result4ptr[1] = target.g / SCAST(fl4, scalar);
		result4ptr[2] = target.b / SCAST(fl4, scalar);
		result4ptr[3] = target.a / SCAST(fl4, scalar);
	}
};
//============================================================================//
}//ns

