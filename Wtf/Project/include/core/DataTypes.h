#pragma once
#include <stdint.h>

namespace wtf{

    using s32 = int32_t;
    using s64 = int64_t;

    using bln = bool;
    using szt = size_t;

    using f32 = float;
    using f64 = double;

    using ptr = intptr_t;

    enum Codes : int
    {
        critical_success = 100500,
        critical_failure = -100500,
        _Codes,
    };
}
