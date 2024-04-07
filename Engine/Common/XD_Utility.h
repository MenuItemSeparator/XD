#pragma once
#include "XDEngine.h"
#include "XD_Log.h"

#ifdef dXD_DEBUG
    #define X_Call(func, error_msg) \
        if (!func.fCheck()) \
        { \
            mLOG(error_msg << " " << __func__ << " " << __LINE__); \
            return XD::X::fFail(); \
        }

    #define X_Call_Void(func, error_msg) \
        if (!func.fCheck()) \
        { \
            mLOG(error_msg << " " << __func__ << " " << __LINE__); \
            return; \
        }
#else
    #define X_Call(func, error_msg) func
    #define X_Call_Void(func, error_msg) func
#endif

