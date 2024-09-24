#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    typedef u4 (*ThreadFn)(void* _userData);

    class XD_ENGINE_API XD_ThreadBase
    {
    public:
        XD_ThreadBase() = default;
        virtual ~XD_ThreadBase() = default;
        XD_ThreadBase(const XD_ThreadBase&) = delete;
        XD_ThreadBase& operator=(const XD_ThreadBase&) = delete;

        X fLaunchX(ThreadFn _fn, void* _userData, const char* _name) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fWaitX() { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fTerminateX() { mXD_NOT_IMPLEMENTED(); return X_X; }
    private:
        X fRunX() { mXD_NOT_IMPLEMENTED(); return X_X; }
    };
}