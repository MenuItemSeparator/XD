#pragma once
#include <Windows.h>
#include "XD_Engine_Minimal.h"
#include "Common/XD_Thread.h"

namespace XD
{
    class XD_ENGINE_API XD_Thread : public XD_ThreadBase
    {
        friend class ThreadInternalStarter;
    public:
        XD_Thread() = default;

        X fLaunchX(ThreadFn _fn, void* _userData, const char* _name);
        X fWaitX();
        X fTerminateX();
    private:
        ThreadFn m_entryFunction;
        void* m_userData;

        HANDLE m_threadHandle;
        u4 m_threadId;

    };
}