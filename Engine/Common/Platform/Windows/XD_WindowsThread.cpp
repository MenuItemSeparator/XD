#include "XD_WindowsThread.h"

namespace XD
{
    class ThreadInternalStarter
    {
    public:
        static u4 __stdcall fEntryPoint_Internal(void* _threadPtr)
        {
            XD_Thread* thread = reinterpret_cast<XD_Thread*>(_threadPtr);
            u4 exitCode = thread->m_entryFunction(thread->m_userData);
            mLOG("Thread " << thread->m_threadId << " ended");
            _endthreadex(0);
            return 0;
        }
    };

    X 
    XD_Thread::fLaunchX(ThreadFn _fn, void *_userData, const char *_name)
    {
        m_entryFunction = _fn;
        m_userData = _userData;

        m_threadHandle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &ThreadInternalStarter::fEntryPoint_Internal, this, 0, &m_threadId));

        mLOG("Current thread id " << GetCurrentThreadId());
        mLOG("New thread id " << m_threadId);

        if(!m_threadHandle)
        {
            mLOG("Can't launch thread with name " << _name);
            return X_X;
        }

        return A_A;
    }

    X 
    XD_Thread::fWaitX()
    {
        if (m_threadHandle)
        {
            if(m_threadId == GetCurrentThreadId())
            {
                mLOG("A thread cannot wait for itself! Current: " << m_threadId);
                return X_X;
            }

            WaitForSingleObject(m_threadHandle, INFINITE);
        }

        mLOG("Waited");
        return A_A;
    }

    X 
    XD_Thread::fTerminateX()
    {
        if (m_threadHandle)
        {
            TerminateThread(m_threadHandle, 0);
        }

        return A_A;
    }

}