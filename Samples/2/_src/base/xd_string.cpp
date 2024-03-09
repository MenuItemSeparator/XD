#include <string.h>

#include "xd_string.h"
#include "base/xd_lang.h"
#include "base/xd_cast.h"

using namespace nXD;

//============================================================================//
XD_STRING::XD_STRING()
{
	fDrop();
}
//============================================================================//
XD_STRING::XD_STRING(szt s_z)
{
	fDrop();
	fAllocate(s_z);
}
//============================================================================//
XD_STRING::XD_STRING(str s_g, szt _size, MEM_STRAT _allocate)
{
	fDrop();
	szt size = _size? _size : strlen(s_g);
	if(AUTO == _allocate)
		fSet(s_g, size);
	else
		fSetLocal(s_g, size);
}
//============================================================================//
XD_STRING::XD_STRING(const XD_STRING& c_p)
{
	fDrop();
	fSet(c_p.fGet());
}
//============================================================================//
XD_STRING::~XD_STRING()
{
	fClear();
}
//============================================================================//
void
XD_STRING::fDrop()
{
	data = nullptr;
	length = 0;
	alloc_size = 0;
}
//============================================================================//
void
XD_STRING::fClear()
{
	if(alloc_size)
	{
		alloc_size = 0;
		sFreeBuffer(data);
	}
	fDrop();
}
//============================================================================//
void
XD_STRING::fAllocate(szt s_z, bln _forced)
{
	if(alloc_size > s_z && !_forced)
		return;

	fClear();

	data = sAllocateBuffer(s_z);// Opportunity to allocate empty string.
	data[0] = '\0';
	alloc_size = s_z;
}
//============================================================================//
si4
XD_STRING::fSet(const char* s_g)
{
	szt str_size = strlen(s_g);
	return fSet(s_g, str_size);
}
//============================================================================//
si4
XD_STRING::fSet(str _str, szt _size)
{
	si4 result = O_O;
	if(_size > length)
	{
		fAllocate(_size);
		result = A_A;
	}
	strncpy(SCAST(char* ,data), _str, _size);
	length = _size;
	return result;
}
//============================================================================//
str
XD_STRING::fGet() const
{
	if(data)
		return data;
	return "";
}
//============================================================================//
bool
XD_STRING::operator<(const XD_STRING& o_o)
{
	return fLesser(o_o);
}
//============================================================================//
bool
operator<(const XD_STRING& l_o, const XD_STRING& r_o)
{
	return l_o.fLesser(r_o);
}
//============================================================================//
bool
XD_STRING::operator == (const XD_STRING& o_o)
{
	return fCompare(o_o.fGet());
}
//============================================================================//
bool
XD_STRING::fLesser(const XD_STRING& o_o) const
{
	return strcmp(fGet(), o_o.fGet()) < 0;
}
//============================================================================//
void
XD_STRING::fSetLocal(str s_g, szt s_z)
{
	fClear();
	data = CCAST(char*, s_g);
	if(!s_z)
	{//1
		length = strlen(s_g);
	}//1
	else
	{
		length = s_z;
	}
}
//============================================================================//
XD_STRING&
XD_STRING::fSetLocalA(str _string, szt _size)
{
	fSetLocal(_string, _size);
	return *this;
}
//============================================================================//
bool
XD_STRING::fCompare(const char* s_g) const
{
	return 0 == strcmp(data,s_g);
}
//============================================================================//
szt
XD_STRING::fSize() const
{
	return length;
}
//============================================================================//
szt
XD_STRING::iStrSize(str _data)
{
	return strlen(_data);
}
//============================================================================//
char*
XD_STRING::fDataA()
{
	return data;
}
//============================================================================//
void
XD_STRING::fAdd(str _data)
{
	if(_data == nullptr)
		return;

	szt len = strlen(_data);
	if(len == 0){
		return;
	}

	char* buffer = this->data;
	szt req_buffer_size = this->length + len;
	if(req_buffer_size > this->alloc_size)
	{
		this->data = nullptr;
		fAllocate(req_buffer_size);
		strcpy(data, buffer);
		sFreeBuffer(buffer);
	}
	strcat(data, _data);
	this->length = iStrSize(data);
}
//============================================================================//
XD_STRING&
XD_STRING::operator << (str _data)
{
	fAdd(_data);
	return *this;
}
//============================================================================//
char*
XD_STRING::sAllocateBuffer(szt _size)
{
	char* result = new char[_size + 1];
	result[_size] = '\0';
	return result;
}
//============================================================================//
void
XD_STRING::sFreeBuffer(char* _buffer)
{
	delete[] _buffer;
}
//============================================================================//

