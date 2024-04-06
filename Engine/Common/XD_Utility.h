#pragma once
#include "XD_Log.h"

#define X_Call(func, error_msg) \
    if (!func.fCheck()) \
    { \
        mLOG(error_msg << " " << __func__ << " " << __LINE__); \
        return XD::X::Fail(); \
    }

#define X_Call_Void(func, error_msg) \
    if (!func.fCheck()) \
    { \
        mLOG(error_msg << " " << __func__ << " " << __LINE__); \
    }


