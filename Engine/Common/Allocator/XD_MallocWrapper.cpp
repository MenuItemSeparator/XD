#include "XD_MallocWrapper.h"

namespace XD
{
    XD_MallocWrapper::~XD_MallocWrapper()
    {
        mXD_ASSERT(m_allocationsCounter == 0);
    }

    void*
    XD_MallocWrapper::fAllocate(sz _size, sz _alignment)
    {
        ++m_allocationsCounter;
        return ::malloc(_size);
    }

    void 
    XD_MallocWrapper::fFree(void *_ptr)
    {
        --m_allocationsCounter;
        ::free(_ptr);
    }
}