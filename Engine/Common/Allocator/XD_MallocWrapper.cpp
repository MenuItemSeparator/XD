#include "XD_MallocWrapper.h"

namespace XD
{
    XD_MallocWrapper::~XD_MallocWrapper()
    {
        mXD_ASSERTM(m_allocationsCounter == 0, "Alloc counter is not 0. It is " << m_allocationsCounter);
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
        mXD_ASSERT(m_allocationsCounter > 0);
        
        --m_allocationsCounter;
        ::free(_ptr);
    }
}