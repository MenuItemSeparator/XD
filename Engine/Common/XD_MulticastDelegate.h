#pragma once
#include <utility>
#include "XD_Callable.h"
#include "XD_Delegate.h"

namespace XD
{
    template <typename T>
    class XD_Delegate;
    template <typename T>
    class XD_Callable;

    class XD_Connection
    {
    public:
        template <typename Ret, typename... Args>
        XD_Connection(XD_MulticastDelegate<Ret(Args...)>* delegate, XD_Callable<Ret(Args...)>* callable) :
            m_delegate(delegate),
            m_callable(callable),
            m_disconnectFunction(&fDisconnectFunction<Ret, Args...>) {}
        void fDisconnect() { m_disconnectFunction(m_delegate, m_callable); }
    private:
        void (*m_disconnectFunction)(void*, void*);
        void* m_delegate;
        void* m_callable;

        template <typename Ret, typename... Args>
        static void fDisconnectFunction(void* delegate, void* callable)
        {
            static_cast<XD_MulticastDelegate<Ret(Args...)>*>(delegate)->fUnbind(static_cast<XD_Callable<Ret(Args...)>*>(callable));
        }
    };

    template<typename Ret, typename... Args>
    class XD_MulticastDelegate<Ret(Args...)>
    {
        friend XD_Connection;

        template<typename T>
        using tFnPtr = Ret(T::*)(Args...);

        template<typename T>
        using tConstFnPtr = Ret(T::*)(Args...) const;

    public:
        XD_MulticastDelegate() = default;

        template<typename T>
        XD_Connection fBind(T& instance, tFnPtr<T> fnPtr)
        {
            XD_Delegate<Ret(Args...)> delegate{};
            m_delegates.push_back(std::move(delegate));
            m_delegates.back().fBind(instance, fnPtr);
            return XD_Connection{this, m_delegates.back().m_callable.get()};
        }

        template<typename T>
        XD_Connection fBind(T& instance, tConstFnPtr<T> fnPtr)
        {
            XD_Delegate<Ret(Args...)> delegate{};
            m_delegates.push_back(std::move(delegate));
            m_delegates.back().fBind(instance, fnPtr);
            return XD_Connection{this, m_delegates.back().m_callable.get()};
        }

        void operator()(Args... args)
        {
            for (XD_Delegate<Ret(Args...)>& delegate : m_delegates)
            {
                delegate.fInvoke(std::forward<Args>(args)...);
            }
        }

        void fInvoke(Args... args)
        {
            for (XD_Delegate<Ret(Args...)>& delegate : m_delegates)
            {
                delegate.fInvoke(std::forward<Args>(args)...);
            }
        }

        bool fIsValid() const { return !m_delegates.empty(); }

    private:
        using tDelegate = XD_Delegate<Ret(Args...)>;

        std::vector<tDelegate> m_delegates;

        void fUnbind(XD_Callable<Ret(Args...)>* callable)
        {
            auto end = m_delegates.end();
            for (auto it = m_delegates.begin(); it != end; ++it)
            {
                if (it->m_callable.get() == callable)
                {
                    m_delegates.erase(it);
                    return;
                }
            }
        }
    };
}
