#pragma once
#include <Windows.h>
#include "XD_Engine_Minimal.h"
#include "Common/XD_Mutex.h"

namespace XD
{
    class XD_ENGINE_API XD_Mutex : public XD_MutexBase
    {
    public:
        XD_Mutex();
        ~XD_Mutex();

        void fLock();
        void fUnlock();

    private:
        CRITICAL_SECTION m_mutex;
    };

    class XD_ENGINE_API XD_LockScope
    {
    public:
        XD_LockScope(XD_Mutex& _mutex);
        ~XD_LockScope();
    private:
        XD_Mutex& m_mutex;
    };
}