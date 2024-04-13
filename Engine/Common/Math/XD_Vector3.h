#pragma once
#include <cmath>
#include "../XD_Types.h"

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

        float fDot(const Vector3<T>& _vector) const;
        float fMagnitude() const;
        Vector3<T> fGetNormalized() const;
    };

    template<typename T>
    inline float Vector3<T>::fDot(const Vector3<T>& vector) const
    {
        return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
    }

    template<typename T>
    inline float Vector3<T>::fMagnitude() const
    {
        const float x = static_cast<f4>(m_x);
        const float y = static_cast<f4>(m_y);
        const float z = static_cast<f4>(m_z);
        return std::sqrt(x * x + y * y + z * z);
    }

    template<typename T>
    Vector3<T> Vector3<T>::fGetNormalized() const
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
    Vector3<T> operator+(const Vector3<T>& _lVector, const Vector3<T>& _rVector)
    {
        return Vector3<T>{_lVector.m_x + _rVector.m_x, _lVector.m_y + _rVector.m_y, _lVector.m_z + _rVector.m_z};
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& _vector, const f4 _scalar)
    {
        return Vector3<T>{_vector.m_x * _scalar, _vector.m_y * _scalar, _vector.m_z * _scalar};
    }

    template<typename T>
    Vector3<T> operator/(const Vector3<T>& _vector, const f4 _scalar)
    {
        return Vector3<T>{_vector.m_x / _scalar, _vector.m_y / _scalar, _vector.m_z / _scalar};
    }

    template<typename T>
    Vector3<T> operator-(const Vector3<T>& _lVector, const Vector3<T>& _rVector)
    {
        return Vector3<T>{_lVector.m_x - _rVector.m_x, _lVector.m_y - _rVector.m_y, _lVector.m_z - _rVector.m_z};
    }

    template<typename T>
    bool operator==(const Vector3<T>& _lvector, const Vector3<T>& _rvector)
    {
        return fIsNearlyEqual(_lvector.m_x, _rvector.m_x) &&
               fIsNearlyEqual(_lvector.m_y, _rvector.m_y) &&
               fIsNearlyEqual(_lvector.m_z, _rvector.m_z);
    }

    template<typename T>
    bool operator!=(const Vector3<T>& _lvector, const Vector3<T>& _rvector)
    {
        return !(_lvector == _rvector);
    }

    using Vector3f = Vector3<f4>;
    using Vector3i = Vector3<i8>;
    using Vector3u = Vector3<u8>;
}
