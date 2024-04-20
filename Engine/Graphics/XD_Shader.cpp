#include "XD_Shader.h"

namespace XD
{
    X
    XD_Shader::fUseX()
    {
        mXD_ASSERT(m_useProcPtr);
        X_Call(m_useProcPtr(this), "Invalid shader use proc");
        return A_A;
    }

    X
    XD_Shader::fSetFloatX(const char *_name, f4 _value)
    {
        mXD_ASSERT(m_setFloatProcPtr);
        X_Call(m_setFloatProcPtr(this, _name, _value), "Invalid shader set float proc");
        return A_A;
    }

    X
    XD_Shader::fSetIntegerX(const char *_name, i8 _value)
    {
        mXD_ASSERT(m_setIntegerProcPtr);
        X_Call(m_setIntegerProcPtr(this, _name, _value), "Invalid shader set int proc");
        return A_A;
    }

    X
    XD_Shader::fSetVector2fX(const char *_name, const Vector2f &_value)
    {
        mXD_ASSERT(m_setVector2ProcPtr);
        X_Call(m_setVector2ProcPtr(this, _name, _value), "Invalid shader set vec2 proc");
        return A_A;
    }

    X
    XD_Shader::fSetVector3fX(const char *_name, const Vector3f &_value)
    {
        mXD_ASSERT(m_setVector3ProcPtr);
        X_Call(m_setVector3ProcPtr(this, _name, _value), "Invalid shader set vec3 proc");
        return A_A;
    }

    X
    XD_Shader::fSetVector4fX(const char *_name, const Vector4f &_value)
    {
        mXD_ASSERT(m_setVector4ProcPtr);
        X_Call(m_setVector4ProcPtr(this, _name, _value), "Invalid shader set vec4 proc");
        return A_A;
    }

    X
    XD_Shader::fSetMatrix4fX(const char *_name, const Matrix4f &_value)
    {
        mXD_ASSERT(m_setMatrix4ProcPtr);
        X_Call(m_setMatrix4ProcPtr(this, _name, _value), "Invalid shader set mat4 proc");
        return A_A;
    }
}
