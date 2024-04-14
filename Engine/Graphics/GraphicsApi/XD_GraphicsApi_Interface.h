#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_GraphicsApi_Interface
    {
        using tHelloWorldProcPtr = i4(*)(void*, i4);

        mXD_CreateMemberFunctionChecker(fHelloWorld);
    public:

        i4 fHelloWorld(i4 _value);

        XD_GraphicsApi_Interface() = default;
        virtual ~XD_GraphicsApi_Interface() = default;
    protected:
        template<typename T>
        void fInitialize();
    private:
        tHelloWorldProcPtr m_helloWorldProcPtr;

        template<typename T>
        static i4 fHelloWorld_Base(void* _objectPtr, i4 _value) { return static_cast<T*>(_objectPtr)->fHelloWorld(_value); }
    };

    template<typename T>
    void
    XD_GraphicsApi_Interface::fInitialize()
    {
        mXD_CheckMemberFunction(fHelloWorld, i4(T::*)(i4));
        m_helloWorldProcPtr = &fHelloWorld_Base<T>;
    }

    i4
    XD_GraphicsApi_Interface::fHelloWorld(i4 _value)
    {
        mXD_ASSERT(m_helloWorldProcPtr);
        return m_helloWorldProcPtr(this, _value);
    }

    class XD_ENGINE_API XD_OpenGLGraphicsApi : public XD_GraphicsApi_Interface
    {
        friend class XD_GraphicsApi_Interface;
    public:
        XD_OpenGLGraphicsApi() { XD_GraphicsApi_Interface::fInitialize<XD_OpenGLGraphicsApi>(); }
        i4 fHelloWorld(i4 _value) { return _value + 23; }
    };
}
