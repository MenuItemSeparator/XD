#pragma once
#include "XDGraphics_Minimal.h"

namespace XD
{

    class XD_ENGINE_API XD_Shader
    {
        using tUseProcPtr = X(*)(void*);
        using tSetFloatProcPtr = X(*)(void*, const char*, f4);
        using tSetIntegerProcPtr = X(*)(void*, const char*, i8);
        using tSetVector2fProcPtr = X(*)(void*, const char*, const Vector2f&);
        using tSetVector3fProcPtr = X(*)(void*, const char*, const Vector3f&);
        using tSetVector4fProcPtr = X(*)(void*, const char*, const Vector4f&);
        using tSetMatrix4fProcPtr = X(*)(void*, const char*, const Matrix4f&);

        mXD_CreateMemberFunctionChecker(fUseX);
        mXD_CreateMemberFunctionChecker(fSetFloatX);
        mXD_CreateMemberFunctionChecker(fSetIntegerX);
        mXD_CreateMemberFunctionChecker(fSetVector2fX);
        mXD_CreateMemberFunctionChecker(fSetVector3fX);
        mXD_CreateMemberFunctionChecker(fSetVector4fX);
        mXD_CreateMemberFunctionChecker(fSetMatrix4fX);

    public:
        X fUseX();
        X fSetFloatX(const char* _name, f4 _value);
        X fSetIntegerX(const char* _name, i8 _value);
        X fSetVector2fX(const char* _name, const Vector2f& _value);
        X fSetVector3fX(const char* _name, const Vector3f& _value);
        X fSetVector4fX(const char* _name, const Vector4f& _value);
        X fSetMatrix4fX(const char* _name, const Matrix4f& _matrix);

        XD_Shader() = default;
        XD_Shader(const XD_Shader&) = delete;
        XD_Shader& operator=(const XD_Shader&) = delete;
        virtual ~XD_Shader() = default;
    protected:
        template<typename T>
        void fBindFunctions_Internal();

    private:
        tUseProcPtr m_useProcPtr;
        tSetFloatProcPtr m_setFloatProcPtr;
        tSetIntegerProcPtr m_setIntegerProcPtr;
        tSetVector2fProcPtr m_setVector2ProcPtr;
        tSetVector3fProcPtr m_setVector3ProcPtr;
        tSetVector4fProcPtr m_setVector4ProcPtr;
        tSetMatrix4fProcPtr m_setMatrix4ProcPtr;

        template<typename T>
        static X fUseX_Base(void* _objectPtr) { X_Call(static_cast<T*>(_objectPtr)->fUseX(), "Invalid shader use proc"); return A_A; }
        template<typename T>
        static X fSetFloatX_Base(void* _objectPtr, const char* _name, f4 _value) { X_Call(static_cast<T*>(_objectPtr)->fSetFloatX(_name, _value), "Invalid set float proc"); return A_A; }
        template<typename T>
        static X fSetIntegerX_Base(void* _objectPtr, const char* _name, i8 _value) { X_Call(static_cast<T*>(_objectPtr)->fSetIntegerX(_name, _value), "Invalid set integer proc"); return A_A; }
        template<typename T>
        static X fSetVector2fX_Base(void* _objectPtr, const char* _name, const Vector2f& _value) { X_Call(static_cast<T*>(_objectPtr)->fSetVector2fX(_name, _value), "Invalid set float2 proc"); return A_A; }
        template<typename T>
        static X fSetVector3fX_Base(void* _objectPtr, const char* _name, const Vector3f& _value) { X_Call(static_cast<T*>(_objectPtr)->fSetVector3fX(_name, _value), "Invalid set floa3 proc"); return A_A; }
        template<typename T>
        static X fSetVector4fX_Base(void* _objectPtr, const char* _name, const Vector4f& _value) { X_Call(static_cast<T*>(_objectPtr)->fSetVector4fX(_name, _value), "Invalid set floa4 proc"); return A_A; }
        template<typename T>
        static X fSetMatrix4fX_Base(void* _objectPtr, const char* _name, const Matrix4f& _value) { X_Call(static_cast<T*>(_objectPtr)->fSetMatrix4fX(_name, _value), "Invalid set mat4 proc"); return A_A; }
    };

    template<typename T>
    void
    XD_Shader::fBindFunctions_Internal()
    {
        mXD_CheckMemberFunction(fUseX, X(T::*)());
        m_useProcPtr = &fUseX_Base<T>;

        mXD_CheckMemberFunction(fSetFloatX, X(T::*)(const char*, f4));
        m_setFloatProcPtr = &fSetFloatX_Base<T>;

        mXD_CheckMemberFunction(fSetIntegerX, X(T::*)(const char*, i8));
        m_setIntegerProcPtr = &fSetIntegerX_Base<T>;

        mXD_CheckMemberFunction(fSetVector2fX, X(T::*)(const char*, const Vector2f&));
        m_setVector2ProcPtr = &fSetVector2fX_Base<T>;

        mXD_CheckMemberFunction(fSetVector3fX, X(T::*)(const char*, const Vector3f&));
        m_setVector3ProcPtr = &fSetVector3fX_Base<T>;

        mXD_CheckMemberFunction(fSetVector4fX, X(T::*)(const char*, const Vector4f&));
        m_setVector4ProcPtr = &fSetVector4fX_Base<T>;

        mXD_CheckMemberFunction(fSetMatrix4fX, X(T::*)(const char*, const Matrix4f&));
        m_setMatrix4ProcPtr = &fSetMatrix4fX_Base<T>;
    }

}
