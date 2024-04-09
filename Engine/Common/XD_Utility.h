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
#else
    #define X_Call(func, error_msg) func
#endif

