#pragma once
#include <vector>
#include <utility>
#include "XD_Types.h"
#include "XD_Callable.h"

namespace XD
{
    template<typename T>
    class XD_Delegate;
    template <typename T>
    class XD_MulticastDelegate;

    template<typename Ret, typename... Args>
    class XD_Delegate<Ret(Args...)>
    {
        friend XD_MulticastDelegate<Ret(Args...)>;

        template<typename T>
        using tFnPtr = Ret(T::*)(Args...);

        template<typename T>
        using tConstFnPtr = Ret(T::*)(Args...) const;
    public:
        XD_Delegate() = default;
        XD_Delegate(const XD_Delegate&) = delete;
        XD_Delegate& operator=(const XD_Delegate&) = delete;
        XD_Delegate(XD_Delegate&& d) noexcept : m_callable(nullptr) { m_callable.swap(d.m_callable); }
        XD_Delegate& operator=(XD_Delegate&& d) noexcept
        {
            if (&d == this) return *this;
            m_callable.swap(d.m_callable);
            return *this;
        }
        ~XD_Delegate() = default;

        template<typename T>
        void fBind(T& instance, tFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_MemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
        }

        template<typename T>
        void fBind(T& instance, tConstFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_ConstMemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
        }

        bool fIsValid() const { return m_callable != nullptr; }
        Ret operator()(Args... args) { return m_callable->fInvoke(std::forward<Args>(args)...); }
        Ret fInvoke(Args... args) { return m_callable->fInvoke(std::forward<Args>(args)...); }

    private:
        UPtr<XD_Callable<Ret(Args...)>> m_callable;
    };
}
