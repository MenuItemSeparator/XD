#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_Allocator
    {
    public:
        XD_Allocator(sz _size) :
            m_totalSize(_size),
            m_used(0),
            m_peak(0)
        {}

        virtual ~XD_Allocator() 
        {
            m_totalSize = 0;
        }

        virtual void* fAllocate(sz _size, sz _alignment = 0) = 0;
        virtual void fFree(void* _ptr) = 0;
    protected:
        sz m_totalSize;
        sz m_used;
        sz m_peak;

        static sz fCalculatePadding(sz _baseAddress, sz _alignment);
    };

    class XD_ENGINE_API XD_LinearAllocator : public XD_Allocator
    {
    public:
        XD_LinearAllocator(sz _size);
        ~XD_LinearAllocator();

        virtual void* fAllocate(sz _size, sz _alignment = 0) override;
        virtual void fFree(void* _ptr) override;

    private:
        void* m_start;
        sz m_offset;
    };

    template<typename T, typename ...Args>
    T* fAlloc(XD_Allocator* _allocator, sz _alignment, Args... _args)
    {
        void* allocatedMemory = _allocator->fAllocate(sizeof(T), _alignment);
        return ::new(allocatedMemory)(std::forward<Args>(args)...)

    }

    template<typename T, typename ...Args>
    T* fAlloc(XD_Allocator* _allocator, Args... _args)
    {
        return _allocator->fAllocate<T>(sizeof(T), alignof(T), std::forward<Args>(args)...);
    }

    template<typename T>
    void fFree(XD_Allocator* _allocator, T* _ptr)
    {
        if(!_ptr) return;

        _ptr->~T();
        _allocator->fFree(_ptr);
    }
}