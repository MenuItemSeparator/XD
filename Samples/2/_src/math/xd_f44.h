#ifndef _XD_F44_H_INCLUDED
#define _XD_F44_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: matrix 4x4 base.
//============================================================================//
#include <string.h> // memset

#include "base/xd_type.h"
#include "base/xd_code.h"

#include "xd_f4.h"
#include "xd_f2.h"

namespace nXD{
struct F44
{
	union{
		fl4 data[ 4 * 4 ];
		struct {
			fl4 c11, c12, c13, c14,
				c21, c22, c23, c24,
				c31, c32, c33, c34,
				c41, c42, c43, c44;
		};
		struct {
			fl4 m00, m01, m02, m03;
			fl4 m10, m11, m12, m13;
			fl4 m20, m21, m22, m23;
			fl4 m30, m31, m32, m33;
		};
	};

	F44() {}

	F44(fl4 _s)
	{
		fInit(_s);
	}

	void
	fSet(fl4 _data[]){
		memcpy(data, _data, sizeof(F44));
	}

	void
	fClear(){
		memset(data, 0, sizeof(fl4)*4*4);
	}

	F44&
	fInit(fl4 _s)
	{
		fClear();
		m00 = m11 = m22 = m33 = _s;
		return *this;
	}

	fl4
	fGet(szt _num)
	{
		return data[_num];
	}

	fl4
	fGet(szt _row, szt _col)
	{
		return data[_col * 4 + _row];
	}

	fl4* fDataP() { return data; }

public xd_func_block("Matrix"):
	F44& fPerspectiveA(fl4 _fov, fl4 _aspect, fl4 _near, fl4 _far);
	F44  fPerspectiveEX(fl4 fovy, fl4 aspect, fl4 znear, fl4 zfar, fl4 handedness);
	F44& fOrthoA(const nXD::F4& _border, const nXD::F2& _plane);
	F44& fTranslateA(const nXD::F4& _val);
	F44& fScaleA(const nXD::F4& _val);
	F44& fRotateA(const nXD::F4& _val);

public xd_functional:
	F44& operator *= (const nXD::F44& _val);
	F44 operator * (const nXD::F44& _val) const;
	void operator = (const F44& _val);

public xd_interface:
	static szt
	iSizeInF4(){
		return sizeof(F44)/sizeof(fl4);
	}
};
}//nXD
#endif // _XD_F44_H_INCLUDED
