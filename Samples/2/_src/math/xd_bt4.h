#pragma once
#include "base/xd.h"
//============================================================================//
namespace nXD {

struct XD_BT4
{
	union{
		struct{ui1 b; ui1 g; ui1 r; ui1 a;};
		struct{ui1 w; ui1 z; ui1 y; ui1 x;};
		ui4 core;
	};

	XD_BT4() {}
	XD_BT4(ui4 _ini) : core(_ini) {}
};

}
//============================================================================//

