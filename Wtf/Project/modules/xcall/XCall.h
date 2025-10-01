#pragma once
#include "core/DataTypes.h"

namespace wtf {

    class Result
    {
        s32 Var_Result = -1;
        bln Var_Handled = false;
    public:
        Result() = delete;

        Result(const Result& _r): Var_Result(_r.Var_Result), Var_Handled(_r.Var_Handled)
        {}

        explicit Result(s32 _v): Var_Result(_v), Var_Handled(false)
        {}

        int operator ()()
        { return Var_Result; }

        Result& operator = (const Result& _r)
        { Var_Result = _r.Var_Result; Var_Handled = true; return *this; }

        bln operator < (s32 _r)
        { return Var_Result < _r; }
    };

}

#define xcall(_fn) { Result _r = _fn; if(_r < 0){ return _r; } }
