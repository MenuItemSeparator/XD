#pragma once
#include "Common/XD_Log.h"

namespace XD
{
    #define mXD_IS_TRUE(cond, fail_message) \
        if(!(cond)) \
        { \
            mLOG(">> [TEST FAIL]: " << __func__ << " " << #cond << " " << fail_message); \
            return X_X; \
        }

    #define mXD_IS_FALSE(cond, fail_message) \
        if((cond)) \
        { \
            mLOG(">> [TEST FAIL]: " << __func__ << " " << #cond << " " << fail_message); \
            return X_X; \
        }
}
