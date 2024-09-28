#include "XD_WindowsMutex.h"

namespace XD
{
    XD_Mutex::XD_Mutex()
    {
        InitializeCriticalSection(&m_mutex);
    }
    
    XD_Mutex::~XD_Mutex()
    {
        DeleteCriticalSection(&m_mutex);
    }
    
    void
    XD_Mutex::fLock()
    {
        EnterCriticalSection(&m_mutex);
    }
    
    void 
    XD_Mutex::fUnlock()
    {
        LeaveCriticalSection(&m_mutex);
    }

    XD_LockScope::XD_LockScope(XD_Mutex &_mutex) :
        m_mutex(_mutex)
    {
        m_mutex.fLock();
    }

    XD_LockScope::~XD_LockScope()
    {
        m_mutex.fUnlock();
    }
}