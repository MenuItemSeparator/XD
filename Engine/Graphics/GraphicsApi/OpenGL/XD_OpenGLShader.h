#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLShader
    {
    public:
        XD_OpenGLShader();

        X fUseX();
        X fSetFloatX(const char* _name, f4 _value);
        X fSetIntegerX(const char* _name, i8 _value);
        X fSetVector2fX(const char* _name, const Vector2f& _value);
        X fSetVector3fX(const char* _name, const Vector3f& _value);
        X fSetVector4fX(const char* _name, const Vector4f& _value);
        X fSetMatrix4fX(const char* _name, const Matrix4f& _matrix);
    };
}

