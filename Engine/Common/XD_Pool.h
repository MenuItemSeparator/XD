#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    template<typename T>
    class XD_ENGINE_API XD_Pool final
    {
    public:
        XD_Pool();
        ~XD_Pool();
        XD_Pool(const XD_Pool&) = delete;
        XD_Pool& operator=(const XD_Pool&) = delete;
        
    };
    
    template <typename T>
    inline XD_Pool<T>::XD_Pool()
    {
    }

    template <typename T>
    inline XD_Pool<T>::~XD_Pool()
    {
    }
}