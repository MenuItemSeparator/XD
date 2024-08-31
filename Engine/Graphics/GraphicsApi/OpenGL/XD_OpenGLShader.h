#pragma once
#include "XD_Engine_Minimal.h"
#include "../../XD_Shader.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLShader : public XD_Shader
    {
    public:
        XD_OpenGLShader();

        virtual X fvUseX() override;
        virtual X fvSetFloatX(const char* _name, f4 _value) override;
        virtual X fvSetIntegerX(const char* _name, i8 _value) override;
        virtual X fvSetVector2fX(const char* _name, const Vector2f& _value) override;
        virtual X fvSetVector3fX(const char* _name, const Vector3f& _value) override;
        virtual X fvSetVector4fX(const char* _name, const Vector4f& _value) override;
        virtual X fvSetMatrix4fX(const char* _name, const Matrix4f& _matrix) override;
    };
}

