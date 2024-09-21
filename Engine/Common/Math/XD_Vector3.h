#pragma once
#include <cmath>
#include "XD_Math_Common.h"

namespace XD
{
    template<typename T>
    struct Vector3
    {
        static_assert(std::is_arithmetic<T>::value);
    public:
        T m_x;
        T m_y;
        T m_z;

        Vector3() = default;
        Vector3(T _x, T _y, T _z) : m_x(_x), m_y(_y), m_z(_z) {}

        f4 fDot(const Vector3<T>& _vector) const;
        f4 fMagnitude() const;
        Vector3<T> fGetNormalized() const;
    };

    template<typename T>
    dFORCEINLINE
    f4
    Vector3<T>::fDot(const Vector3<T>& vector) const
    {
        return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
    }

    template<typename T>
    f4
    Vector3<T>::fMagnitude() const
    {
        const f4 x = static_cast<f4>(m_x);
        const f4 y = static_cast<f4>(m_y);
        const f4 z = static_cast<f4>(m_z);
        return std::sqrt(x * x + y * y + z * z);
    }

    template<typename T>
    Vector3<T>
    Vector3<T>::fGetNormalized() const
    {
        const float length = fMagnitude();

        if (length <= 0.0f)
        {
            return Vector3<T>{};
        }

        const T x = static_cast<T>(m_x / length);
        const T y = static_cast<T>(m_y / length);
        const T z = static_cast<T>(m_z / length);
        return Vector3<T>{x, y, z};
    }

    template<typename T>
    dFORCEINLINE Vector3<T>
    operator+(const Vector3<T>& _lVector, const Vector3<T>& _rVector)
    {
        return Vector3<T>{_lVector.m_x + _rVector.m_x, _lVector.m_y + _rVector.m_y, _lVector.m_z + _rVector.m_z};
    }

    template<typename T>
    dFORCEINLINE Vector3<T>
    operator*(const Vector3<T>& _vector, const f4 _scalar)
    {
        return Vector3<T>{_vector.m_x * _scalar, _vector.m_y * _scalar, _vector.m_z * _scalar};
    }

    template<typename T>
    dFORCEINLINE Vector3<T>
    operator/(const Vector3<T>& _vector, const f4 _scalar)
    {
        return Vector3<T>{_vector.m_x / _scalar, _vector.m_y / _scalar, _vector.m_z / _scalar};
    }

    template<typename T>
    dFORCEINLINE Vector3<T>
    operator-(const Vector3<T>& _lVector, const Vector3<T>& _rVector)
    {
        return Vector3<T>{_lVector.m_x - _rVector.m_x, _lVector.m_y - _rVector.m_y, _lVector.m_z - _rVector.m_z};
    }

    template<typename T>
    dFORCEINLINE bl
    operator==(const Vector3<T>& _lvector, const Vector3<T>& _rvector)
    {
        return fIsNearlyEqual(_lvector.m_x, _rvector.m_x) &&
               fIsNearlyEqual(_lvector.m_y, _rvector.m_y) &&
               fIsNearlyEqual(_lvector.m_z, _rvector.m_z);
    }

    template<typename T>
    dFORCEINLINE bl
    operator!=(const Vector3<T>& _lvector, const Vector3<T>& _rvector)
    {
        return !(_lvector == _rvector);
    }

    using Vector3f = Vector3<f4>;
    using Vector3i = Vector3<i8>;
    using Vector3u = Vector3<u8>;
}
