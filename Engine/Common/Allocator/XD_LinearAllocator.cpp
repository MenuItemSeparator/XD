#include "XD_LinearAllocator.h"

namespace XD
{
    XD_LinearAllocator::XD_LinearAllocator(sz _size) : 
        XD_Allocator(_size),
        m_start(nullptr)
    {
        m_start = ::malloc(m_totalSize);
    }

    XD_LinearAllocator::~XD_LinearAllocator()
    {
        mXD_ASSERT(m_allocationRequests == 0);
        mXD_ASSERT(m_used == 0);

        ::free(m_start);
        m_start = nullptr;
    }

    void* 
    XD_LinearAllocator::fAllocate(sz _size, sz _alignment)
    {
        const sz currentAddress = (sz)m_start + m_used;
        const sz padding = fCalculatePadding(currentAddress, _alignment);

        if(m_used + padding + _size > m_totalSize)
        {
            mLOG("Linear allocator overflow. Return nullptr.");
            return nullptr;
        }

        ++m_allocationRequests;

        m_used += padding + _size;
        const sz paddedAddress = currentAddress + padding;
        m_peak = std::max(m_peak, m_used);

        return (void*)paddedAddress;
    }

    void 
    XD_LinearAllocator::fFree(void *_ptr)
    {
        --m_allocationRequests;
        if(m_allocationRequests == 0)
        {
            fReset();
        }
    }

    void 
    XD_LinearAllocator::fReset()
    {
        m_used = 0;
    }
}