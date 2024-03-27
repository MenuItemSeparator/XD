#pragma once

#include <stdint.h>

namespace XD
{

using i4 = int32_t;
using u4 = uint32_t;
using f4 = float;


class xd_result
{
public:
    i4 Result;

public:
    xd_result() = delete;
    xd_result(int _r) : Result(_r) {}
};

}
