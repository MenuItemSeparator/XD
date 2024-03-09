#ifndef _XD_SPELL_H_INCLUDED
#define _XD_SPELL_H_INCLUDED

#include <string.h>

#include "base/xd.h"

struct XD_SPELL
{
	static const size_t s_buf_size = 8;
	union
	{
		char spell[s_buf_size];
		ui8  value;
	};
private:
	char eol;
	XD_SPELL* next;

public:
	XD_SPELL() : value(0), eol(0), next(0x0)
	{}

	XD_SPELL(const char* _spell) : eol(0), next(0x0)
	{
		fSet(_spell);
	}

	bool
	fEql(const XD_SPELL& _spell) const
	{
		return value == _spell.value;
	}

	bool
	fEql(const char* _spell) const // Misstake.
	{
		XD_SPELL l_spell(_spell);
		return fEql(l_spell);
	}

	bool
	fIsEmpty()
	{
		return 0 == value;
	}

	void
	fSet(const char* _spell)
	{
		if(0x0 == _spell)
			return;

		value = 0;
		szt len = (strlen(_spell) > s_buf_size)? s_buf_size : strlen(_spell);
		memcpy(spell, _spell, len);
	}

	const char* fGetP() const // Misstake.
	{
		return spell;
	}

	bool
	operator == (const XD_SPELL& _spell) const
	{
		return fEql(_spell);
	}

	bool
	operator == (const char* _spell)
	{
		return fEql(_spell);
	}

	ui8
	fAsNumber() const
	{
		return RCAST(ui8, value);
	}

	bool operator < (const XD_SPELL& _right) const
	{
		return 0 > strncmp(fGetP(), _right.fGetP(), s_buf_size);
	}

	XD_SPELL* fNextP()
	{
		return next;
	}

};

#endif // XD_SPELL_H_INCLUDED
