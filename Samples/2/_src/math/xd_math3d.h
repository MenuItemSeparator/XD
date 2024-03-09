#pragma once

#include "base/xd.h"
#include "base/xd_code.h"

#include "xd_math.h"
#include "xd_f44.h"

namespace nXD{

void
mat4_set_identity( F44& xd_out _self );

void
mat4_set_zero( F44& xd_out _self );

void
mat4_multiply( F44& xd_out _self, const F44& _other );

void
mat4_set_orthographic(	F44& xd_out _self,
						float left,   float right,
						float bottom, float top,
						float znear,  float zfar
						);

void
mat4_set_perspective(	F44& xd_out _self,
						float fovy,  float aspect,
						float zNear, float zFar
						);

void
mat4_set_frustum(	F44& xd_out _self,
					float left,   float right,
					float bottom, float top,
					float znear,  float zfar
					);

void
mat4_set_rotation(	F44& xd_out _self,
					float angle,
					float x, float y, float z
					);

void
mat4_set_rotation_rad(	F44& xd_out _self,
						float angle,
						float x, float y, float z
						);

void
mat4_set_translation(	F44& xd_out _self,
						float x, float y, float z
						);

void
mat4_set_scaling(	F44& xd_out _self,
					float x, float y, float z
					);

void
mat4_rotate(	F44& xd_out _self,
				float angle,
				float x, float y, float z
				);

void
mat4_rotate_rad( F44& xd_out _self,
				 float angle,
				 float x, float y, float z
				 );

void
mat4_translate( F44& xd_out _self,
				float x, float y, float z
				);

void
mat4_scale( F44& xd_out self,
			float x, float y, float z
			);
}// nXD
