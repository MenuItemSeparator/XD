#pragma once

#include "Type.h"
#include "Debug.h"
#include "Helpers.h"

namespace XD
{
class X
{
    s32 Var_Value = 0;
    bln Var_Handle = false;

    inline void fnHandle() { Var_Handle = true; }
public:
    X() = default;
    X(s32 _val): Var_Value(_val) {}
    ~X() { Var_Handle? nothing() : breakpoint(); }

    inline s32 operator()() { fnHandle(); return Var_Value; }
    inline bln operator > (s32 _val) { fnHandle(); return Var_Value > _val; }
    inline bln operator < (s32 _val) { fnHandle(); return Var_Value < _val; }
    inline bln operator == (s32 _val) { fnHandle(); return Var_Value == _val; }
};

class X_Test
{
    s32 Var_TestResult = 0;
public:
    X_Test()
    {
        Var_TestResult = -1;
    }

    bln fnIsSuccess() { return Var_TestResult > 0; }
};

}
