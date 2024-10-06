#pragma once
#include "XD_Allocator.h"

namespace XD
{
    class XD_ENGINE_API XD_LinearAllocator : public XD_Allocator
    {
    public:
        XD_LinearAllocator(sz _size);
        ~XD_LinearAllocator();

        virtual void* fAllocate(sz _size, sz _alignment = 0) override;
        virtual void fFree(void* _ptr) override;

    private:
        void* m_start;
        sz m_allocationRequests;

        void fReset();
    };
}