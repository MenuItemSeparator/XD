#pragma once
#include <memory>
#include "XD_Engine_Definitions.h"

namespace XD
{
    using i4 = int32_t;
    using i8 = int64_t;
    using u4 = uint32_t;
    using u8 = uint64_t;
    using f4 = float;
    using f8 = double;
    using bl = bool;

    template<typename T>
    using tUptr = std::unique_ptr<T>;
    template<typename T>
    using tSptr = std::shared_ptr<T>;
    template<typename T>
    using tWptr = std::weak_ptr<T>;

    const i4 XD_RESULT_SUCCESS = 0x0;
    const i4 XD_RESULT_FAIL = -1;
    const i4 XD_RESULT_DISABLED = INT_MAX;
    const u8 XD_INVALID_HANDLE = UINT64_MAX;

    enum eEmote
    {
        A_A = XD_RESULT_SUCCESS,
        X_X = XD_RESULT_FAIL
    };

    class XD_ENGINE_API X
    {
    public:
        X() = delete;

        X(i8 _r) : m_result(_r) {}

        static X fSuccess() { return X{A_A}; }
        static X fFail() { return X{X_X}; }

        ~X()
        {
#ifdef dXD_DEBUG
            if(m_result != XD_RESULT_DISABLED)
            {
                mXD_ASSERTM(false, "Unhandled X result");
            }
#endif
        }

        bl fCheck()
        {
#ifdef dXD_DEBUG
            i8 tmp = m_result;
            m_result = XD_RESULT_DISABLED;
            return tmp >= 0;
#else
            return m_result >= 0;
#endif
        }
        operator i8() const { return m_result; }
    private:
        i8 m_result;
    };

    struct Memory
    {
    public:
        void* m_data;
        u8 m_byteSize;
    };

} // ns

