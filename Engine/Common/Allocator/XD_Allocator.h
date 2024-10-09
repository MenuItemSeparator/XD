#pragma once
#include "STDIncludes.h"
#include "XD_Engine_Definitions.h"
#include "XD_Engine_PlatformSelector.h"
#include "Common/XD_Log.h"
#include "Common/XD_Utility.h"
#include "Common/XD_Types.h"

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

    XD_ENGINE_API extern XD_Allocator* gGlobalAllocator;    
    XD_ENGINE_API XD_Allocator* fGetGlobalAllocator();

    class XD_ENGINE_API XD_MemoryUtils 
    {
    public:
        static XD_Allocator* fGetGlobalAllocator();
        static void fSetGlobalAllocator(XD_Allocator* _globalAllocator);

        template<typename T, typename ...Args> 
        static T* 
        fAlloc(XD_Allocator* _allocator, sz _alignment, Args... _args)
        {
            void* allocatedMemory = _allocator->fAllocate(sizeof(T), _alignment);
            return ::new(allocatedMemory)T(std::forward<Args>(_args)...);
        }

        template<typename T, typename ...Args>
        static T* 
        fAlloc(XD_Allocator* _allocator, Args... _args)
        {
            return fAlloc<T>( _allocator, alignof(T), std::forward<Args>(_args)...);
        }

        template<typename T>
        static void 
        fFree(XD_Allocator* _allocator, T* _ptr)
        {
            if(!_ptr) return;

            _ptr->~T();
            _allocator->fFree(_ptr);
        }

        template<typename T, typename ...Args>
        static tSptr<T> 
        fMakeShared(XD_Allocator* _allocator, Args... _args)
        {
            const auto customDeleter = [_allocator](T* _ptr) mutable
            {
                fFree<T>(_allocator, _ptr);
            };

            T* ptr = fAlloc<T>(_allocator, std::forward<Args>(_args)...);
            return std::shared_ptr<T>{ ptr, customDeleter };
        }

        template<typename T, typename ...Args>
        static tUptr<T> 
        fMakeUnique(XD_Allocator* _allocator, Args... _args)
        {
            const auto customDeleter = [_allocator](T* _ptr) mutable
            {
                fFree<T>(_allocator, _ptr);
            };

            T* ptr = fAlloc<T>(_allocator, std::forward<Args>(_args)...);
            return std::unique_ptr<T>{ ptr, customDeleter };
        }
    };








}