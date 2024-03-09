/*
#ifndef _TYPES_H_INCLUDED
#define _TYPES_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: basic datatypes.
//============================================================================//
#include <inttypes.h>
#include <cstddef>

typedef  bool			bln;
typedef  void*			ptr;
typedef  uint8_t		ui1;
typedef  uint16_t		ui2;
typedef  uint32_t		ui4;
typedef  uint64_t		ui8;

typedef  int8_t			si1;
typedef  int16_t		si2;
typedef  int32_t		si4;
typedef  int64_t		si8;
typedef  size_t			szt;
typedef	 size_t			num; // Numbered from 1, not from 0;
static szt ToInt(num _value) { return _value - 1;}
static num ToNum(si4 _value) { return _value + 1;}

typedef  float			fl4;
typedef  double			fl8;

typedef  intptr_t		sip;
typedef	 const char*	str;

const    szt			ptr_sz = sizeof(sip);

typedef si4				x_result;

#endif // _TYPES_H_INCLUDED
*/
