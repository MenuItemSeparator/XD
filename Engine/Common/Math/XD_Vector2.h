#pragma once
#include <cmath>
#include "XD_Types.h"

namespace XD
{
    template<typename T>
    struct Vector2
    {
        static_assert(std::is_arithmetic<T>::value);

    public:
        T m_x;
        T m_y;

        Vector2() = default;
        Vector2(T _x, T _y) noexcept : m_x(_x), m_y(_y) {}

        f4 fDot(const Vector2<T>& vector) const;
        f4 fMagnitude() const;
        Vector2<T> fGetNormalized() const;
    };

    template<typename T>
    inline float Vector2<T>::fDot(const Vector2<T>& _vector) const
    {
        return m_x * _vector.m_x + m_y * _vector.m_y;
    }

    template<typename T>
    inline float Vector2<T>::fMagnitude() const
    {
        const float x = static_cast<f4>(m_x);
        const float y = static_cast<f4>(m_y);
        return std::sqrt(x * x + y * y);
    }

    template<typename T>
    Vector2<T> Vector2<T>::fGetNormalized() const
    {
        const float length = fMagnitude();
        if (length <= 0.0f)
        {
            return Vector2<T>{};
        }

        const T x = static_cast<T>(m_x / length);
        const T y = static_cast<T>(m_y / length);
        return Vector2<T>{x, y};
    }

    template<typename T>
    Vector2<T> operator+(const Vector2<T>& _lVector, const Vector2<T>& _rVector)
    {
        return Vector2<T>{_lVector.m_x + _rVector.m_x, _lVector.m_y + _rVector.m_y};
    }

    template<typename T>
    Vector2<T> operator-(const Vector2<T>& _lVector, const Vector2<T>& _rVector)
    {
        return Vector2<T>{_lVector.m_x - _rVector.m_x, _lVector.m_y - _rVector.m_y};
    }

    using Vector2f = Vector2<f4>;
    using Vector2i = Vector2<i8>;
    using Vector2u = Vector2<u8>;
}
