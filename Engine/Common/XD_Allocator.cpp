#include "XD_Allocator.h"

namespace XD
{
    sz XD_Allocator::fCalculatePadding(sz _baseAddress, sz _alignment)
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
		const sz padding = alignedAddress - _baseAddress;
		return padding;
    }

    XD_LinearAllocator::XD_LinearAllocator(sz _size) : 
            XD_Allocator(_size),
            m_start(nullptr),
            m_offset(0)
    {
        m_start = ::malloc(m_totalSize);
    }

    XD_LinearAllocator::~XD_LinearAllocator()
    {
        ::free(m_start);
        m_start = nullptr;
    }

    void* XD_LinearAllocator::fAllocate(sz _size, sz _alignment)
    {
        const sz currentAddress = (sz)m_start + m_offset;
        const sz padding = fCalculatePadding(currentAddress, _alignment);

        if(m_offset + padding + _size > m_totalSize)
        {
            mLOG("Linear allocator overflow. Return nullptr.");
            return nullptr;
        }

        m_offset += padding + _size;
        const sz paddedAddress = currentAddress + padding;

        m_used = m_offset;
        m_peak = std::max(m_peak, m_used);

        return (void*)paddedAddress;
    }

    void XD_LinearAllocator::fFree(void *_ptr)
    {
        mXD_ASSERT(false);
    }

}