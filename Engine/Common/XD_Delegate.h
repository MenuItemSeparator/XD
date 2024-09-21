#pragma once
#include <vector>
#include <utility>
#include "XD_Utility.h"
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
        void
        fBind(T& instance, tFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_MemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
        }

        template<typename T>
        void
        fBind(T& instance, tConstFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_ConstMemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
        }

        bl fIsValid() const { return m_callable != nullptr; }
        Ret operator()(Args... args) { return m_callable->fInvoke(std::forward<Args>(args)...); }
        Ret fInvoke(Args... args) { return m_callable->fInvoke(std::forward<Args>(args)...); }

    private:
        tUptr<XD_Callable<Ret(Args...)>> m_callable;
    };

    template<typename... Args>
    class XD_Delegate<XD::X(Args...)>
    {
        friend XD_MulticastDelegate<XD::X(Args...)>;

        template<typename T>
        using tFnPtr = XD::X(T::*)(Args...);

        template<typename T>
        using tConstFnPtr = XD::X(T::*)(Args...) const;

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
        void
        fBind(T& instance, tFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_MemFunCallable<T, XD::X(Args...)>>(instance, ptrToFn);
        }

        template<typename T>
        void
        fBind(T& instance, tConstFnPtr<T> ptrToFn)
        {
            m_callable = std::make_unique<XD_ConstMemFunCallable<T, XD::X(Args...)>>(instance, ptrToFn);
        }

        bl fIsValid() const { return m_callable != nullptr; }
        XD::X operator()(Args... args) { X_Call(m_callable->fInvoke(std::forward<Args>(args)...), "Unknown delegate error"); return X::fSuccess(); }
        XD::X fInvoke(Args... args) { mXD_ASSERT(fIsValid()); X_Call(m_callable->fInvoke(std::forward<Args>(args)...), "Unknown delegate error"); return X::fSuccess(); }

    private:
        tUptr<XD_Callable<XD::X(Args...)>> m_callable;
    };
}
