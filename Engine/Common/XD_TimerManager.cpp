#include "XD_TimerManager.h"

namespace XD
{
    XD_TimerInstance::XD_TimerInstance() :
        m_handle(),
        m_timePassed(0.0),
        m_targetTime(0.0),
        m_callback()
    {
        m_handle.m_handle = XD_INVALID_HANDLE;
    }

    X 
    XD_TimerInstance::fResetX()
    {
        m_handle.m_handle = XD_INVALID_HANDLE;
        m_timePassed = 0.0;
        m_targetTime = 0.0;
        m_callback.fClear();
        return A_A;
    }

    XD_TimerManager::XD_TimerManager() :
        m_timerHandles(),
        m_timers(TIMER_MAX_COUNT)
    {
    }

    X 
    XD_TimerManager::fStopTimerX(TimerHandle _timerHandle)
    {
        mXD_WARN(m_timerHandles.fIsValid(_timerHandle), "Timer handle is already invalidated");
        X_Call(m_timers[_timerHandle].fResetX(), "Error while stopping timer instance");
        X_Call(m_timerHandles.fFreeHandleX(_timerHandle), "Can't free handle");
        return A_A;
    }

    X
    XD_TimerManager::fUpdateX(double _deltaTime)
    {
        size_t timersSize = m_timers.size();
        for (size_t i = 0; i < timersSize; ++i)
        {
            XD_TimerInstance& instance = m_timers[i];

            if(!m_timerHandles.fIsValid(instance.m_handle)) continue;

            instance.m_timePassed += _deltaTime;
            if(instance.m_timePassed >= instance.m_targetTime)
            {
                instance.m_callback.fInvoke();
                X_Call(fStopTimerX(instance.m_handle), "Can't stop timer in update cycle");
            }
        }

        return A_A;
    }
}