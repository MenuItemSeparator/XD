#pragma once

#include "base/xd.h"
#include "base/xd_lang.h"
#include "base/xd_log.h"

#include "math/xd_point2.h"

namespace nXD{

struct BITMAP
{
	// Raw
	void*           data;
	szt             data_size;
	// Pixels
	ui1*            bmp;
	szt             bmp_size;
	XDE_PIXEL       format;
	XD_POINT2       size;
public:
	BITMAP(void* _data, szt _data_size)
		: data(_data), data_size(_data_size),
		  bmp(nullptr), bmp_size(0), format(XDE_PIXEL_NONE)
	{}

	~BITMAP()
	{
		if(bmp)
			delete[] bmp;
	}

	BITMAP& fSetA(void* _data, szt _data_size){
		data = _data; data_size = _data_size;
		return *this;
	}

	bool fEmpty()
	{
		return bmp_size == 0;
	}

	void fFree()
	{
		mTODO();
	}
};

}// nXD
