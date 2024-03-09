#ifndef _XD_ATL_FRM_H_INCLUDED
#define _XD_ATL_FRM_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Author: UCKUHT
// Date: 2014-05-11
// Desc: atlass frame.
//============================================================================//
#include "xd.h"
#include "xd_f4.h"

#include "GFX/XD_GFX.h"

struct XD_ATL_FRM
{
	const nXD::GFX::TEXTURE*	texture;
	XD_F4						frame;

	XD_ATL_FRM()
	{
		fSet(0x0, XD_F4(0,0,1,1));
	}

	XD_ATL_FRM(const nXD::GFX::TEXTURE* _texture)
	{
		fSet(_texture, XD_F4(0,0,1,1));
	}

	XD_ATL_FRM(const nXD::GFX::TEXTURE* _texture, XD_F4& _frame_bounds)
	{
		fSet(_texture, _frame_bounds);
	}

	fl4
	fSizeX() const
	{
		return frame.data[2] - frame.data[0];
	}

	fl4
	fSizeY() const
	{
		return frame.data[3] - frame.data[1];
	}

	void
	fSet(const nXD::GFX::TEXTURE* _texture, const XD_F4& _frame)
	{
		texture = _texture;
		frame = _frame;
	}

	bool
	fIsEmpty()
	{
		return 0x0 == texture;
	}

	XD_F4&
	fFrameA()
	{
		return frame;
	}

	const XD_I2&
	fTextureSize() const
	{
		return texture->size;
	}
};

#endif // XD_ATL_FRM_H_INCLUDED
