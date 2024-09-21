#pragma once
#include <memory>
#include <utility>

namespace XD
{
    template<typename T>
    class XD_Callable;

    template<typename Ret, typename... Args>
    class XD_Callable<Ret(Args...)>
    {
    public:
        virtual ~XD_Callable() = default;
        virtual Ret fInvoke(Args... args) = 0;
    protected:
        XD_Callable() = default;
    };

    template<typename Ret, typename T>
    class XD_MemFunCallable;

    template<typename T, typename Ret, typename... Args>
    class XD_MemFunCallable<T, Ret(Args...)> final : public XD_Callable<Ret(Args...)>
    {
        using tPtrToFn = Ret(T::*)(Args...);
    public:
        T& m_instance;
        tPtrToFn m_ptrToFunction;

        XD_MemFunCallable(T& instance, tPtrToFn ptrToFunction) : m_instance(instance), m_ptrToFunction(ptrToFunction) {}
        virtual Ret fInvoke(Args... args) override { return (m_instance.*m_ptrToFunction)(std::forward<Args>(args)...); }
    };

    template<typename Ret, typename T>
    class XD_ConstMemFunCallable;

    template<typename T, typename Ret, typename... Args>
    class XD_ConstMemFunCallable<T, Ret(Args...)> final : public XD_Callable<Ret(Args...)>
    {
        using tConstPtrToFn = Ret(T::*)(Args...) const;
    public:
        XD_ConstMemFunCallable(T& instance, tConstPtrToFn ptrToFunctionConst) : m_instance(instance), m_ptrToFunctionConst(ptrToFunctionConst) {}
        virtual Ret fInvoke(Args... args) override { return (m_instance.*m_ptrToFunctionConst)(std::forward<Args>(args)...); }
    private:
        T& m_instance;
        tConstPtrToFn m_ptrToFunctionConst;
    };

}
