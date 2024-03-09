#pragma once

#include <inttypes.h>
#include <cstddef>

typedef	bool				bln;
typedef	void*				ptr;
typedef	uint8_t				ui1;
typedef	uint16_t			ui2;
typedef	uint32_t			ui4;
typedef	uint64_t			ui8;

typedef	int8_t				si1;
typedef	int16_t				si2;
typedef	int32_t				si4;
typedef	int64_t				si8;
typedef	size_t				szt;
typedef	float				fl4;
typedef	double				fl8;

typedef	uintptr_t			uip;
typedef	const char*			str;
typedef	si4					x_result;

// Language helpers.
#define xd_none
#define xd_pass				0x0
// Class fields.
#define xd_data				xd_none
#define xd_types			xd_none
#define xd_functional		xd_none
#define xd_func_block(text) xd_none
#define xd_accessors		xd_none
#define xd_interface		xd_none
// Functions fields.
#define xd_out				xd_none
#define xd_as				xd_none

// Static.
#define SCAST(to, from)		static_cast<to>(from)
// Reinterpret.
#define RCAST(to, from)		reinterpret_cast<to>(from)
// Const.
#define CCAST(to, from)		const_cast<to>(from)
// Dynamic.
#define DCAST(to, from)		dynamic_cast<to>(from)
// Native c style.
#define NCAST(to, from)		(to)from

// This define needed to avoid warnings with ";"
#define mPASS				(void)0
// This macro avoid warning with unused variables.
#define mIGNOREP(text)		if(text){} mPASS

// Formaters.
#define mXD_DEBUG_STOP()	asm("int3")

#ifdef XD_BREAK_ERRORS
#define mBREAK_ERR()		mXD_DEBUG_STOP
#else
#define mBREAK_ERR()
#endif

namespace nXD{
	si4 fgIncrement(si4 _in);
}
