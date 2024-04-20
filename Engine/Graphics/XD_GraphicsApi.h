#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
class XD_ENGINE_API XD_GraphicsApi
    {
        using tInitializeProcPtr = X(*)(void*);
        using tShutdownProcPtr = X(*)(void*);

        mXD_CreateMemberFunctionChecker(fInitializeX);
        mXD_CreateMemberFunctionChecker(fShutdownX);
    public:

        X fInitializeX();
        X fShutdownX();

        XD_GraphicsApi() = default;
        XD_GraphicsApi(const XD_GraphicsApi&) = delete;
        XD_GraphicsApi& operator=(const XD_GraphicsApi&) = delete;
        virtual ~XD_GraphicsApi() = default;
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
    XD_GraphicsApi::fBindFunctions_Internal()
    {
        mXD_CheckMemberFunction(fInitializeX, X(T::*)());
        m_initializeProcPtr = &fInitialize_Base<T>;

        mXD_CheckMemberFunction(fShutdownX, X(T::*)());
        m_shutdownProcPtr = &fShutdown_Base<T>;
    }
}
