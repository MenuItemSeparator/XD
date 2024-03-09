#pragma once

#include <ostream>

namespace XDN{

class Log final
{
private:
	static void fNoteInternal(std::ostream _stream) {std::cout<<stream;}
public:
	static void fLog(std::ostream _stream);
	static void fError(std::ostream _stream);
};

}// XDN
