#pragma once
#include "XD_Graphics_Minimal.h"

namespace XD
{

    class XD_ENGINE_API XD_Shader
    {
    public:
        virtual X fvUseX() = 0;
        virtual X fvSetFloatX(const char* _name, f4 _value) = 0;
        virtual X fvSetIntegerX(const char* _name, i8 _value) = 0;
        virtual X fvSetVector2fX(const char* _name, const Vector2f& _value) = 0;
        virtual X fvSetVector3fX(const char* _name, const Vector3f& _value) = 0;
        virtual X fvSetVector4fX(const char* _name, const Vector4f& _value) = 0;
        virtual X fvSetMatrix4fX(const char* _name, const Matrix4f& _matrix) = 0;

        XD_Shader() = default;
        XD_Shader(const XD_Shader&) = delete;
        XD_Shader& operator=(const XD_Shader&) = delete;
        virtual ~XD_Shader() = default;
    };
}
