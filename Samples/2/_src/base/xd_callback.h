#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: low level my own patern who-what-why. Simplest event runner and easiest
//       listener type.
//============================================================================//

#include "xd.h"
#include "xd_lang.h"
#include "xd_cast.h"

#define mXD_WWW_DECLARE(functionName, object, objectData) sip(*functionName)(object, objectData)

namespace nXD{

template<class _WHO, typename _WHY>
struct XD_WWW_T
{
	typedef uip(*www)(_WHO*, _WHY*);
public:
	_WHO*	who; // Object.
	www		what;// Func ptr for who and why.
	_WHY*	why; // Extra data.

public:
	XD_WWW_T()
		: who(0x0), what(0x0), why(0x0)
		{}

public:
	bool
	fIsEmpty()
	{
		return what == 0;
	}//
	uip
	fRunX()
	{
		return what( who, why);
	}//

	uip
	fRunX(_WHY* _data)
	{
		if(0x0 == what)
			return O_O;

		return what(who, _data);
	}

	uip
	fRunX(_WHO* _who, _WHY* _why)
	{
		return what(_who, _why);
	}

	XD_WWW_T&
	fSetA(_WHO* who_, www what_, _WHY* why_)
	{
		who = who_; what = what_; why = why_;
		return *this;
	}

	XD_WWW_T&
	fObjectSetA(_WHO* _owner)
	{
		who = _owner;
		return *this;
	}

	XD_WWW_T&
	fMethodSetA(www _method)
	{
		what = _method;
		return *this;
	}

	template<typename T>
	XD_WWW_T&
	fMethodSetA(T _method)
	{
		what = RCAST(www, _method);
		return *this;
	}

};

typedef XD_WWW_T<void, void> XD_WWW;

}//ns
