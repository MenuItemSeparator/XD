#pragma once
#include "XD_Engine_Definitions.h"
#include "XD_Engine_PlatformSelector.h"
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

#ifdef dXD_DEBUG
    #define mXD_CreateMemberFunctionChecker(FNNAME) \
        template<typename T> \
        struct has_member_##FNNAME; \
        template<typename R, typename C> \
        class has_member_##FNNAME<R C::*> \
        { \
        private: \
            template<R C::*> \
            struct helper; \
            template<typename T> \
            static char check(helper<&T::FNNAME>*); \
            template<typename T> \
            static char (& check(...))[2]; \
        public: \
            static const bl value = (sizeof(check<C>(0)) == sizeof(char)); \
        }

    #define mXD_CheckMemberFunction(FNNAME, FNPROTOTYPE) \
        { \
            mXD_ASSERT(has_member_##FNNAME<FNPROTOTYPE>::value); \
        }
#else
    #define mXD_CreateMemberFunctionChecker(FNNAME);
    #define mXD_CheckMemberFunction(FNNAME, FNPROTOTYPE);
#endif

