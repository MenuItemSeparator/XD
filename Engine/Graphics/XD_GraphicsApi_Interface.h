#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_GraphicsApi_Interface
    {
        using tInitializeProcPtr = X(*)(void*);
        using tShutdownProcPtr = X(*)(void*);

        mXD_CreateMemberFunctionChecker(fInitializeX);
        mXD_CreateMemberFunctionChecker(fShutdownX);
    public:

        X fInitializeX();
        X fShutdownX();

        XD_GraphicsApi_Interface() = default;
        XD_GraphicsApi_Interface(const XD_GraphicsApi_Interface&) = delete;
        XD_GraphicsApi_Interface& operator=(const XD_GraphicsApi_Interface&) = delete;
        virtual ~XD_GraphicsApi_Interface() = default;
    protected:
        template<typename T>
        void fBindFunctions_Internal();
    private:
        tInitializeProcPtr m_initializeProcPtr;
        tShutdownProcPtr m_shutdownProcPtr;

        template<typename T>
        static X fInitialize_Base(void* _objectPtr) { X_Call(static_cast<T*>(_objectPtr)->fInitializeX(), "Invalid graphics api initialize"); return A_A; }
        template<typename T>
        static X fShutdown_Base(void* _objectPtr) { X_Call(static_cast<T*>(_objectPtr)->fShutdownX(), "Invalid graphics api shutdown"); return A_A; }
    };

    template<typename T>
    void
    XD_GraphicsApi_Interface::fBindFunctions_Internal()
    {
        mXD_CheckMemberFunction(fInitializeX, X(T::*)());
        m_initializeProcPtr = &fInitialize_Base<T>;

        mXD_CheckMemberFunction(fShutdownX, X(T::*)());
        m_shutdownProcPtr = &fShutdown_Base<T>;
    }
}
