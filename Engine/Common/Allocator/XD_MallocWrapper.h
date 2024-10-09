#pragma once
#include "XD_Engine_Minimal.h"
#include "XD_Allocator.h"

namespace XD
{
    class XD_ENGINE_API XD_MallocWrapper : public XD_Allocator
    {
    public:
        XD_MallocWrapper() :
            XD_Allocator(0),
            m_allocationsCounter(0)
        {}
        ~XD_MallocWrapper();

        virtual void* fAllocate(sz _size, sz _alignment = 0) override;
        virtual void fFree(void* _ptr) override;
    private:
        std::atomic<u8> m_allocationsCounter;
    };
}