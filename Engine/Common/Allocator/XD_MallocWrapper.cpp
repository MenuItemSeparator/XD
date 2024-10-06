#include "XD_MallocWrapper.h"

namespace XD
{
    void*
    XD_MallocWrapper::fAllocate(sz _size, sz _alignment)
    {
        return ::malloc(_size);
    }

    void 
    XD_MallocWrapper::fFree(void *_ptr)
    {
        ::free(_ptr);
    }
}