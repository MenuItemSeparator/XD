#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "xd_math3d.h"


const float  PI_F = 3.14159265358979f;


namespace nXD{

void
mat4_set_zero( F44& _self )
{
	memset( &_self, 0, sizeof( F44 ));
}

void
mat4_set_identity( F44& _self )
{
	mat4_set_zero(_self);

	_self.m00 = 1.0;
	_self.m11 = 1.0;
	_self.m22 = 1.0;
	_self.m33 = 1.0;
}

void
mat4_multiply( F44& xd_out _self, const F44& _other )
{
	F44 m;
	size_t i;

	for( i=0; i<4; ++i )
	{
		m.data[i*4+0] =
			(_self.data[i*4+0] * _other.data[0*4+0]) +
			(_self.data[i*4+1] * _other.data[1*4+0]) +
			(_self.data[i*4+2] * _other.data[2*4+0]) +
			(_self.data[i*4+3] * _other.data[3*4+0]) ;

		m.data[i*4+1] =
			(_self.data[i*4+0] * _other.data[0*4+1]) +
			(_self.data[i*4+1] * _other.data[1*4+1]) +
			(_self.data[i*4+2] * _other.data[2*4+1]) +
			(_self.data[i*4+3] * _other.data[3*4+1]) ;

		m.data[i*4+2] =
			(_self.data[i*4+0] * _other.data[0*4+2]) +
			(_self.data[i*4+1] * _other.data[1*4+2]) +
			(_self.data[i*4+2] * _other.data[2*4+2]) +
			(_self.data[i*4+3] * _other.data[3*4+2]) ;

		m.data[i*4+3] =
			(_self.data[i*4+0] * _other.data[0*4+3]) +
			(_self.data[i*4+1] * _other.data[1*4+3]) +
			(_self.data[i*4+2] * _other.data[2*4+3]) +
			(_self.data[i*4+3] * _other.data[3*4+3]) ;
	}
	memcpy( &_self, &m, sizeof( F44 ) );

}


void
mat4_set_orthographic(	F44&	_self,
						float	_left,		float	_right,
						float	_bottom,	float	_top,
						float	_znear,		float	_zfar )
{
	mASSERT( _right > _left, "Wrong parameters");
	mASSERT( _bottom > _top, "Wrong parameters");
	mASSERT( _znear < _zfar, "Wrong parameters");

	mat4_set_zero(_self );

	_self.m00 = +2.f/(_right-_left);
	_self.m30 = -(_right+_left)/(_right-_left);
	_self.m11 = +2.f/(_top-_bottom);
	_self.m31 = -(_top+_bottom)/(_top-_bottom);
	_self.m22 = -2.f/(_zfar-_znear);
	_self.m32 = -(_zfar+_znear)/(_zfar-_znear);
	_self.m33 = 1.0;
}

void
mat4_set_perspective(	F44& xd_out _self,
						float fovy,  float aspect,
						float znear, float zfar)
{
	float h, w;

	assert( znear < zfar );

	h = tan(fovy / 360.f * PI_F) * znear;
	w = h * aspect;

	mat4_set_frustum( _self, -w, w, -h, h, znear, zfar );
}

void
mat4_set_frustum( 	F44& _self,
					float left,   float right,
					float bottom, float top,
					float znear,  float zfar )
{

	assert( right  > left );
	assert( bottom < top  );
	assert( znear  < zfar );

	mat4_set_zero( _self );

	_self.m00 = +2.f*znear/(right-left);
	_self.m20 = (right+left)/(right-left);

	_self.m11 = +2.f*znear/(top-bottom);
	_self.m31 = (top+bottom)/(top-bottom);

	_self.m22 = -(zfar+znear)/(zfar-znear);
	_self.m32 = -2.f*znear/(zfar-znear);

	_self.m23 = -1.f;
}

void
mat4_set_rotation(	F44& _self,
					float angle,
					float x, float y, float z)
{
	float c, s, norm;

	c = cos( PI_F*angle/180.f );
	s = sin( PI_F*angle/180.f );
	norm = sqrt(x*x+y*y+z*z);

	x /= norm; y /= norm; z /= norm;

	mat4_set_identity( _self );

	_self.m00 = x*x*(1-c)+c;
	_self.m10 = y*x*(1-c)-z*s;
	_self.m20 = z*x*(1-c)+y*s;

	_self.m01 =  x*y*(1-c)+z*s;
	_self.m11 =  y*y*(1-c)+c;
	_self.m21 =  z*y*(1-c)-x*s;

	_self.m02 = x*z*(1-c)-y*s;
	_self.m12 = y*z*(1-c)+x*s;
	_self.m22 = z*z*(1-c)+c;
}


void
mat4_set_rotation_rad(	F44& _self,
						float angle,
						float x, float y, float z)
{
	float c, s, norm;


	c = cos( angle );
	s = sin( angle );
	norm = sqrt(x*x+y*y+z*z);

	x /= norm; y /= norm; z /= norm;

	mat4_set_identity( _self );

	_self.m00 = x*x*(1-c)+c;
	_self.m10 = y*x*(1-c)-z*s;
	_self.m20 = z*x*(1-c)+y*s;

	_self.m01 =  x*y*(1-c)+z*s;
	_self.m11 =  y*y*(1-c)+c;
	_self.m21 =  z*y*(1-c)-x*s;

	_self.m02 = x*z*(1-c)-y*s;
	_self.m12 = y*z*(1-c)+x*s;
	_self.m22 = z*z*(1-c)+c;
}

void
mat4_set_translation(	F44& _self,
						float x, float y, float z)
{

	mat4_set_identity( _self );
	_self.m30 = x;
	_self.m31 = y;
	_self.m32 = z;
}

void
mat4_set_scaling(	F44& _self,
					float x, float y, float z)
{
	mat4_set_identity( _self );
	_self.m00 = x;
	_self.m11 = y;
	_self.m22 = z;
}

void
mat4_rotate(	F44& _self,
				float angle,
				float x, float y, float z)
{
	F44 m;
	mat4_set_rotation( m, angle, x, y, z);
	mat4_multiply( _self, m );
}

void
mat4_rotate_rad( F44& _self,
				 float angle,
				 float x, float y, float z)
{
	F44 m;
	mat4_set_rotation_rad( m, angle, x, y, z);
	mat4_multiply( _self, m );
}

void
mat4_translate( F44& _self,
				float x, float y, float z)
{
	F44 m;

	mat4_set_translation( m, x, y, z);
	mat4_multiply( _self, m );
}

void
mat4_scale( F44& _self,
			float x, float y, float z)
{
	F44 m;

	mat4_set_scaling( m, x, y, z);
	mat4_multiply( _self, m );
}
}//nXD
