#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_MutexBase
    {
    public:
        XD_MutexBase() = default;
        ~XD_MutexBase() = default;

        XD_MutexBase(const XD_MutexBase&) = delete;
        XD_MutexBase& operator=(const XD_MutexBase&) = delete;

        void fLock() { mXD_NOT_IMPLEMENTED(); }
        void fUnlock() { mXD_NOT_IMPLEMENTED(); }
    };
}