#pragma once
#include <cmath>
#include "XD_Math_Common.h"
#include "XD_Vector4.h"

namespace XD
{

    template<typename T>
    class XD_ENGINE_API XD_Matrix4
    {
        using tColumnType = Vector4<T>;
        using tRowType = Vector4<T>;

    public:
        XD_Matrix4();
        XD_Matrix4(T _diagonalValue);
        XD_Matrix4(T const& _x0, T const& _y0, T const& _z0, T const& _w0,
                   T const& _x1, T const& _y1, T const& _z1, T const& _w1,
                   T const& _x2, T const& _y2, T const& _z2, T const& _w2,
                   T const& _x3, T const& _y3, T const& _z3, T const& _w3);
        XD_Matrix4(tRowType const& _v0, tRowType const& _v1, tRowType const& _v2, tRowType const& _v3);
        XD_Matrix4(const XD_Matrix4& _mat);
        XD_Matrix4<T>& operator=(const XD_Matrix4& _mat);
        XD_Matrix4<T>::tRowType& operator[](u4 i) { mXD_ASSERT(i >= 0 && i < 4); return this->m_value[i]; }

    private:
        tColumnType m_value[4];
    };

    template<typename T>
    XD_Matrix4<T>::XD_Matrix4() :
        XD_Matrix4<T>(1.0f)
    {}

    template<typename T>
    XD_Matrix4<T>::XD_Matrix4(T _diagonalValue) :
        XD::XD_Matrix4<T>
        (
            { _diagonalValue, 0.0f, 0.0f, 0.0f },
            { 0.0f, _diagonalValue, 0.0f, 0.0f },
            { 0.0f, 0.0f, _diagonalValue, 0.0f },
            { 0.0f, 0.0f, 0.0f, _diagonalValue }
        )
    {}

    template<typename T>
    XD_Matrix4<T>::XD_Matrix4(const T& _x0,
                              const T& _y0,
                              const T& _z0,
                              const T& _w0,
                              const T& _x1,
                              const T& _y1,
                              const T& _z1,
                              const T& _w1,
                              const T& _x2,
                              const T& _y2,
                              const T& _z2,
                              const T& _w2,
                              const T& _x3,
                              const T& _y3,
                              const T& _z3,
                              const T& _w3) :
        XD::XD_Matrix4<T>
        (
            {_x0, _y0, _z0, _w0},
            {_x1, _y1, _z1, _w1},
            {_x2, _y2, _z2, _w2},
            {_x3, _y3, _z3, _w3}
        )
    {

    }

    template<typename T>
    XD_Matrix4<T>::XD_Matrix4(const tRowType& _v0,
                              const tRowType& _v1,
                              const tRowType& _v2,
                              const tRowType& _v3) :
        m_value{_v0, _v1, _v2, _v3}
    {}

    template<typename T>
    XD_Matrix4<T>::XD_Matrix4(const XD_Matrix4& _mat) :
        m_value
        {
            _mat.m_value[0],
            _mat.m_value[1],
            _mat.m_value[2],
            _mat.m_value[3]
        }
    {}

    template<typename T>
    XD_Matrix4<T>&
    XD_Matrix4<T>::operator=(const XD_Matrix4& _mat)
    {
        if(this == &_mat) return *this;

        m_value[0] = _mat.m_value[0];
        m_value[1] = _mat.m_value[1];
        m_value[2] = _mat.m_value[2];
        m_value[3] = _mat.m_value[3];
        return *this;
    }

    template<typename T>
    XD_Matrix4<T>&
    operator*(const XD_Matrix4<T>& _lmat, const XD_Matrix4<T>& _rmat)
    {
        mXD_NOT_IMPLEMENTED();
    }

    template<typename T>
    bl
    operator==(const XD_Matrix4<T>& _lmat, const XD_Matrix4<T>& _rmat)
    {
        return (_lmat[0] == _rmat[0]) && (_lmat[1] == _rmat[1]) && (_lmat[2] == _rmat[2]) && (_lmat[3] == _rmat[3]);
    }

    template<typename T>
    bl
    operator!=(const XD_Matrix4<T>& _lmat, const XD_Matrix4<T>& _rmat)
    {
        return (_lmat[0] != _rmat[0]) || (_lmat[1] != _rmat[1]) || (_lmat[2] != _rmat[2]) || (_lmat[3] != _rmat[3]);
    }

    using Matrix4f = XD_Matrix4<f4>;
    using Matrix4d = XD_Matrix4<f8>;
}
