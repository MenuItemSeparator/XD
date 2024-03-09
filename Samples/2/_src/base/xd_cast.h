/*
#ifndef _CAST_TYPES_H_INCLUDED
#define _CAST_TYPES_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: easy casting way, lesser letters - beter reading. ++ style using only
// in debug version. In release rtti better be switched off, and run time casts
// lose relevance. Other cast methods generaly unnessesary in production.
//============================================================================//

// Static.
#define SCAST(to, from) static_cast<to>(from)
// Reinterpret.
#define RCAST(to, from) reinterpret_cast<to>(from)
// Const.
#define CCAST(to, from) const_cast<to>(from)
// Dynamic.
#define DCAST(to, from) dynamic_cast<to>(from)
// Native c style.
#define NCAST(to, from) (to)from

#endif // _CAST_TYPES_H_INCLUDED
*/
