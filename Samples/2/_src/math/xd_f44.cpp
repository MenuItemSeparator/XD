#include "xd_f44.h"
#include "xd_f4.h"
#include "xd_math3d.h"
namespace nXD{

//============================================================================//
F44&
F44::operator *= (const F44& _val)
{
	nXD::mat4_multiply(*this, _val);
	return *this;
}
//============================================================================//
F44
F44::operator * (const F44& _val) const
{
	F44 result = _val;
	result *= _val;
	return result;
}
//============================================================================//
void
F44::operator = (const F44& _val)
{
	memcpy(this, &_val, sizeof(nXD::F44));
}
//============================================================================//
F44&
F44::fOrthoA(const nXD::F4& _border, const nXD::F2& _plane)
{
	nXD::mat4_set_orthographic(*this,
			mVAR("Left", _border.left),
			mVAR("Right", _border.right),
			mVAR("Top", _border.top),
			mVAR("Bottom", _border.bot),

			mVAR("Near", _plane.x),
			mVAR("Far", _plane.y)
			);

	return *this;
}
//============================================================================//
F44&
F44::fPerspectiveA(fl4 _fov, fl4 _aspect, fl4 _near, fl4 _far)
{
	nXD::mat4_set_perspective(*this, _fov, _aspect, _near, _far);
	return *this;
}
//============================================================================//
F44&
F44::fTranslateA(const F4& _val)
{
	nXD::mat4_translate(*this, _val.x, _val.y, _val.z);
	return *this;
}
//============================================================================//
F44&
F44::fScaleA(const F4& _val)
{
	nXD::mat4_scale(*this, _val.x, _val.y, _val.z);
	return *this;
}
//============================================================================//
F44&
F44::fRotateA(const F4& _val)
{
	nXD::mat4_rotate(*this, 1, _val.x, _val.y, _val.z);
	return *this;
}
//============================================================================//
F44
F44::fPerspectiveEX(fl4 fovy, fl4 aspect, fl4 znear, fl4 zfar, fl4 handedness) {
	const fl4 y = 1 / std::tan(fovy);
	const fl4 x = y / aspect;
	const fl4 z = (znear - zfar);
	const fl4 f = zfar / z;
	F44 result;
	mOPTIMFUNC("Array below may be set directly?");
	fl4 data[4*4]=	{	x, 0, 0, 0,
						0, y, 0, 0,
						0, 0, f * handedness, -1 * handedness,
						0, 0, 2.0f * znear * f, 0 };
	result.fSet(data);
	return result;
}
}//nXD
