#ifndef _ES_WDGT_H_INCLUDED
#define _ES_WDGT_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: win impl widget.
//============================================================================//
#include <windows.h>

#include "math/xd_i2.h"
#include "base/xd_string.h"

namespace nXD{
//============================================================================//
struct WDGT
{
	XD_STRING m_wdgt_class;
	HWND m_core;
	HINSTANCE m_hinstance;
	si4 m_mode;
	nXD::I2 m_size;

public:
	HWND		fGetHwnd() const;
	void		fSetHwnd(HWND hWnd);
	si4			fGetMode();
	void		fSetMode(int mode);
	nXD::I2&	fSizeA() { return m_size; }

	WDGT();
	~WDGT();
};
//============================================================================//
}//ns

#endif // _ES_WDGT_H_INCLUDED
