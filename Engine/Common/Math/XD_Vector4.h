#pragma once
#include <cmath>
#include "XDMath_Common.h"

namespace XD
{
    template<typename T>
    struct Vector4
    {
        static_assert(std::is_arithmetic<T>::value);
    public:
        T m_x;
        T m_y;
        T m_z;
        T m_w;

        Vector4() = default;
        Vector4(T _x, T _y, T _z, T _w) : m_x(_x), m_y(_y), m_z(_z), m_w(_w) {}
    };

    template<typename T>
    dFORCEINLINE Vector4<T>
    operator+(const Vector4<T>& _lVector, const Vector4<T>& _rVector)
    {
        return Vector4<T>{_lVector.m_x + _rVector.m_x, _lVector.m_y + _rVector.m_y, _lVector.m_z + _rVector.m_z, _lVector.m_w + _rVector.m_w};
    }

    template<typename T>
    dFORCEINLINE Vector4<T>
    operator*(const Vector4<T>& _vector, const f4 _scalar)
    {
        return Vector4<T>{_vector.m_x * _scalar, _vector.m_y * _scalar, _vector.m_z * _scalar, _vector.m_w * _scalar};
    }

    template<typename T>
    dFORCEINLINE Vector4<T>
    operator/(const Vector4<T>& _vector, const f4 _scalar)
    {
        return Vector4<T>{_vector.m_x / _scalar, _vector.m_y / _scalar, _vector.m_z / _scalar, _vector.m_w / _scalar};
    }

    template<typename T>
    dFORCEINLINE Vector4<T>
    operator-(const Vector4<T>& _lVector, const Vector4<T>& _rVector)
    {
        return Vector4<T>{_lVector.m_x - _rVector.m_x, _lVector.m_y - _rVector.m_y, _lVector.m_z - _rVector.m_z, _lVector.m_w - _rVector.m_w};
    }

    template<typename T>
    dFORCEINLINE bl
    operator==(const Vector4<T>& _lvector, const Vector4<T>& _rvector)
    {
        return fIsNearlyEqual(_lvector.m_x, _rvector.m_x) &&
               fIsNearlyEqual(_lvector.m_y, _rvector.m_y) &&
               fIsNearlyEqual(_lvector.m_z, _rvector.m_z) &&
               fIsNearlyEqual(_lvector.m_w, _rvector.m_w);
    }

    template<typename T>
    dFORCEINLINE bl
    operator!=(const Vector4<T>& _lvector, const Vector4<T>& _rvector)
    {
        return !(_lvector == _rvector);
    }

    using Vector4f = Vector4<f4>;
    using Vector4i = Vector4<i8>;
    using Vector4u = Vector4<u8>;
}
