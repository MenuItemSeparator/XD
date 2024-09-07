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
    private:
        std::unordered_set<T> m_activeHandles;
        std::vector<T> m_freeHandles;
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
        T newHandle;

        mXD_ASSERTM(m_handlePointer + 1 != MAX_SIZE, "Reached max capacity of handles");

        if(m_freeHandles.size())
        {
            newHandle = m_freeHandles.back();
            m_freeHandles.pop_back();
        }
        else
        {
            newHandle = T{m_handlePointer++};
        }

        return newHandle;
    }

    template <typename T, size_t MAX_SIZE>
    inline X 
    XD_HandleMap<T, MAX_SIZE>::fFreeHandleX(T _handle)
    {
        mXD_ASSERTM(fIsValid(_handle), "Trying to free invalid handle");

        m_activeHandles.erase(_handle);
        m_freeHandles.push_back(_handle);

        return A_A;
    }

    template <typename T, size_t MAX_SIZE>
    inline bl 
    XD_HandleMap<T, MAX_SIZE>::fIsValid(T _handle)
    {
        return m_activeHandles.find(_handle) != m_activeHandles.end();
    }
}