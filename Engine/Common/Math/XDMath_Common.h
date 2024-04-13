#pragma once
#include "XDEngine.h"
#include "XDEngine_PlatformSelector.h"
#include "Common/XD_Types.h"
#include <type_traits>
#include <cmath>

namespace XD
{
    #define dXD_SMALL_NUMBER (0.0001f)
    #define dXD_DOUBLE_SMALL_NUMBER	(0.0001)

    template<typename T>
    constexpr dFORCEINLINE T
    fAbs(const T _value) { return (_value < (T)0) ? -_value : _value; }

    template< class T >
    static constexpr dFORCEINLINE T
    fMax( const T _a, const T _b ) { return (_b < _a) ? _a : _b; }

    static constexpr dFORCEINLINE bl
    fIsNearlyEqual(f4 _a, f4 _b, f4 _errorTolerance = dXD_SMALL_NUMBER)
    {
        return fAbs<f4>(_a - _b) <= _errorTolerance;
    }

    static constexpr dFORCEINLINE bl
    fIsNearlyEqual(f8 _a, f8 _b, f8 _errorTolerance = dXD_DOUBLE_SMALL_NUMBER)
    {
        return fAbs<f8>(_a - _b) <= _errorTolerance;
    }

    static constexpr dFORCEINLINE bl
    fIsNearlyZero(f4 _a, f4 _errorTolerance = dXD_SMALL_NUMBER)
    {
        return fAbs<f4>(_a) <= _errorTolerance;
    }

    static constexpr dFORCEINLINE bl
    fIsNearlyZero(f8 _a, f8 _errorTolerance = dXD_DOUBLE_SMALL_NUMBER)
    {
        return fAbs<f8>(_a) <= _errorTolerance;
    }
}
