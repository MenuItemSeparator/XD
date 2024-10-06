#include "XD_Allocator.h"

namespace XD
{
    XD_Allocator* gGlobalAllocator;

    sz 
    XD_Allocator::fCalculatePadding(sz _baseAddress, sz _alignment)
    {
        if(_alignment == 0)
        {
            return _baseAddress;
        }

        if(_baseAddress % _alignment == 0)
        {
            return _baseAddress;
        }

		const sz multiplier = (_baseAddress / _alignment) + 1;
		const sz alignedAddress = _alignment * multiplier;
		return alignedAddress - _baseAddress;
    }
}