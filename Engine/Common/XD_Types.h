#pragma once

#include <memory>

namespace XD
{
    using i4 = int32_t;
    using u4 = uint32_t;
    using f4 = float;

    const i4 XD_RESULT_SUCCESS = 1;
    const i4 XD_RESULT_FAIL = 0;

    template<typename T>
    using UPtr = std::unique_ptr<T>;
    template<typename T>
    using SPtr = std::shared_ptr<T>;

    class XD_Result
    {
    public:
        XD_Result() = delete;
        XD_Result(int _r) : Result(_r) {}

        static XD_Result Success() { return XD_Result{XD_RESULT_SUCCESS}; }
        static XD_Result Fail() { return XD_Result{XD_RESULT_FAIL}; }

        operator bool() const { return Result == XD_RESULT_SUCCESS; }
    private:
        i4 Result;
    };

}
