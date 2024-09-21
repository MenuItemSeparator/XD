#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    template<typename T, size_t MAX_SIZE>
    class XD_ENGINE_API XD_HandleMap
    {
    public:
        XD_HandleMap();
        T fCreateHandle();
        X fFreeHandleX(T _handle);
        bl fIsValid(T _handle);
        X fClearX();
    private:
        std::unordered_set<XD::u8> m_activeHandles;
        std::vector<XD::u8> m_freeHandles;
        u8 m_handlePointer;
    };

    template <typename T, size_t MAX_SIZE>
    inline XD_HandleMap<T, MAX_SIZE>::XD_HandleMap() :
        m_activeHandles(),
        m_freeHandles(),
        m_handlePointer(0)
    {
        m_activeHandles.reserve(MAX_SIZE);
        m_freeHandles.reserve(MAX_SIZE / 2);
    }

    template <typename T, size_t MAX_SIZE>
    inline T 
    XD_HandleMap<T, MAX_SIZE>::fCreateHandle()
    {
        u8 newHandle;

        mXD_ASSERTM(m_handlePointer + 1 != MAX_SIZE, "Reached max capacity of handles");

        if(m_freeHandles.size())
        {
            newHandle = m_freeHandles.back();
            m_freeHandles.pop_back();
        }
        else
        {
            newHandle = m_handlePointer++;
        }

        m_activeHandles.insert(newHandle);

        return T{newHandle};
    }

    template <typename T, size_t MAX_SIZE>
    inline X 
    XD_HandleMap<T, MAX_SIZE>::fFreeHandleX(T _handle)
    {
        mXD_ASSERTM(fIsValid(_handle), "Trying to free invalid handle");

        m_activeHandles.erase(_handle.m_handle);
        m_freeHandles.push_back(_handle.m_handle);

        return A_A;
    }

    template <typename T, size_t MAX_SIZE>
    inline bl 
    XD_HandleMap<T, MAX_SIZE>::fIsValid(T _handle)
    {
        return m_activeHandles.find(_handle.m_handle) != m_activeHandles.end();
    }
    
    template <typename T, size_t MAX_SIZE>
    inline X XD_HandleMap<T, MAX_SIZE>::fClearX()
    {
        m_activeHandles.clear();
        m_freeHandles.clear();
        m_handlePointer = 0;
        return A_A;
    }
}