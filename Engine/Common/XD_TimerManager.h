#pragma once
#include "XD_Engine_Minimal.h"
#include "XD_HandleMap.h"

namespace XD
{
    mXD_MAKE_HANDLE_STRUCT(TimerHandle);
    const u8 TIMER_MAX_COUNT = 64;
    using tTimerHandleMap = XD_HandleMap<TimerHandle, TIMER_MAX_COUNT>;

    struct XD_ENGINE_API XD_TimerInstance
    {
    public:
        TimerHandle m_handle;
        f8 m_timePassed;
        f8 m_targetTime;
        XD_Delegate<void(void)> m_callback;

        XD_TimerInstance(); 
        X fResetX();
    };

    class XD_ENGINE_API XD_TimerManager
    {
    public:
        XD_TimerManager();
        XD_TimerManager(const XD_TimerManager&) = delete;
        XD_TimerManager& operator=(const XD_TimerManager&) = delete;

        template<typename T>
        X fStartTimerX(TimerHandle& _timerHandle, f8 _timeToWait, T& _instance, void(T::*_callback)(void));
        X fStopTimerX(TimerHandle _timerHandle);
        X fUpdateX(double _deltaTime);
    private:
        tTimerHandleMap m_timerHandles;
        std::vector<XD_TimerInstance> m_timers;
    };
    
    template <typename T>
    inline X 
    XD_TimerManager::fStartTimerX(TimerHandle &_timerHandle, f8 _timeToWait, T& _instance, void (T::*_callback)(void))
    {
        _timerHandle = m_timerHandles.fCreateHandle();
        XD_TimerInstance& instance = m_timers[_timerHandle];
        instance.m_handle = _timerHandle;
        instance.m_timePassed = 0.0;
        instance.m_targetTime = _timeToWait;
        instance.m_callback.fBind<T>(_instance, _callback);
        return A_A;
    }
}