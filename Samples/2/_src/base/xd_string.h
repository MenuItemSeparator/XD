#ifndef _ES_STRING_H_INCLUDED
#define _ES_STRING_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: my own bicycle. I like it.
//============================================================================//
#include <cstring>

#include "base/xd.h"
#include "base/xd_code.h"

struct XD_STRING
{
public xd_data:
	char*	data;
	szt		alloc_size;// Size of allocated array.
	szt		length;

public xd_types:
	/// String strategy.
	enum MEM_STRAT
	{
		AUTO, // Memory is handled by obgect.
		MANUAL, // Memory management is delegated to user.
		MEM_STRAT_
	};

	enum
	{
		autosize = 0,
	};

public xd_functional:
	XD_STRING();
	explicit XD_STRING(szt s_z);
	XD_STRING(str _s) :XD_STRING(_s, 0, AUTO) {}
	XD_STRING(const char* s_g, szt _size, MEM_STRAT _allocate = AUTO);
	XD_STRING(const XD_STRING& cS_p);
	~XD_STRING();

public xd_functional:
	/// Drops all parameters at zero, without relesing memory.
	void	fDrop();
	/// Clears allocated data.
	void	fClear();
	/// Allocate/reallocate data.
	void	fAllocate(szt _s, bln _forced = true);
	/// Copy string into data.
	si4		fSet(const char* _s);
	si4		fSet(str _str, szt _size);
	/// Just getting data from.
	str		fGet() const;
	/// Setting local data. Just wrap and do not delete.
	void	fSetLocal(const char* s_g, szt s_z = 0); xd_heap_free xd_low_perf
	XD_STRING& fSetLocalA(str _srting, szt _size = 0); xd_heap_free xd_low_perf
	/// Compare with str.
	bool	fCompare(str s_g) const;
	/// Returns length of internal string.
	szt		fSize() const;
	/// Returns result of std compare operation.
	bool	fLesser(const XD_STRING& r_o) const;
	/// Add lines.
	void	fAdd(str _data);

public xd_functional:
	/// Sorting operator less
	bool	operator < (const XD_STRING& o_o);
	/// Compare operator
	bool	operator == (const XD_STRING& o_o);

	XD_STRING& operator << (const XD_STRING&) {return *this;}
	XD_STRING& operator << (str);
	XD_STRING& operator << (si4) {return *this;}
	XD_STRING& operator << (fl4) {return *this;}

	XD_STRING& operator + (const XD_STRING&) {return *this;}
	XD_STRING& operator + (str) {return *this;}
	XD_STRING& operator + (si4) {return *this;}
	XD_STRING& operator + (fl4) {return *this;}
	XD_STRING& operator = (XD_STRING& _val) {fSet(_val.fGet(),_val.fSize()); return *this;}

	operator str() const { return fGet(); }

public xd_interface:
	static	szt		iStrSize(str _data);

public xd_accessors:
	char*	fDataA();

private xd_functional:
	char*	sAllocateBuffer(szt);
	void	sFreeBuffer(char*);
};

bool
operator < (const XD_STRING& l_o, const XD_STRING& r_o);

#endif // ES_STRING_H_INCLUDED
