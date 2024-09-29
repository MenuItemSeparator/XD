#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    enum class eRendererType
    {
        None,
        OpenGL
    };

    struct XD_ENGINE_API XD_GraphicsConfig
    {
        eRendererType m_rendererType;
        void* m_hwnd;

        XD_GraphicsConfig() = default;
    };

    struct XD_ENGINE_API XD_Color
    {
    public:
        XD_Color() = default;
        XD_Color(f4 _r, f4 _g, f4 _b, f4 _a) : 
            m_r(_r), m_g(_g), m_b(_b), m_a(_a) {}

        f4 m_r{1.0f};
        f4 m_g{1.0f};
        f4 m_b{1.0f};
        f4 m_a{1.0f};
    };

    inline std::ostream& operator<<(std::ostream & _out, const XD_Color& _color) 
    {
        return _out << "Color: { " << _color.m_r << ", " << _color.m_g << ", " << _color.m_b << ", " << _color.m_a << " }";
    }
}
