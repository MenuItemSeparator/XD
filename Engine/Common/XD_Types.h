#pragma once

#include <memory>
#include "XDEngine.h"

namespace XD
{
    using i4 = int32_t;
    using i8 = int64_t;
    using u4 = uint32_t;
    using u8 = uint64_t;
    using f4 = float;
    using bl = bool;

    template<typename T>
    using UPtr = std::unique_ptr<T>;
    template<typename T>
    using SPtr = std::shared_ptr<T>;
    template<typename T>
    using WPtr = std::weak_ptr<T>;

    const i4 XD_RESULT_SUCCESS = 0x0;
    const i4 XD_RESULT_FAIL = -1;
    const i4 XD_RESULT_DISABLED = INT_MAX;

    enum Emote
    {
        A_A = XD_RESULT_SUCCESS,
        X_X = XD_RESULT_FAIL
    };

    class XD_ENGINE_API X
    {
    public:
        X() = delete;
        X(i8 _r) : m_result(_r) {}
        ~X()
        {
            if(m_result != XD_RESULT_DISABLED)
            {
                mXD_ASSERTM(false, "Unhandled X result");
            }
        }

        static X Success() { return X{A_A}; }
        static X Fail() { return X{X_X}; }

        bl fCheck() { i8 tmp = m_result; m_result = XD_RESULT_DISABLED; return tmp >= 0; }
        operator i8() const { return m_result; }
    private:
        i8 m_result;

    };
} // ns

class Z
{
public:
    static XD::i8 m_value;
};
