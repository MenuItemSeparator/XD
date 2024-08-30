#pragma once
#include "XD_Application_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_ApplicationConfig final
    {
    public:
        std::string m_displayName;

        XD_ApplicationConfig();
    };

    class XD_ENGINE_API XD_Application_Interface
    {
    public:
        virtual X fvInitializeX() = 0;
        virtual X fvTerminateX() = 0;

        virtual ~XD_Application_Interface() = default;
    };

    class XD_ENGINE_API XD_ApplicationContext
    {
    public:
        bl m_requestedTermination : 1;
    };

    class XD_Application_Base : public XD_Application_Interface
    {
    public:
        XD_Application_Base(const XD_Application_Base&) = delete;
        XD_Application_Base& operator=(const XD_Application_Base&) = delete;

        X fLoopX() { mXD_NOT_IMPLEMENTED(); return X::fFail(); }

    protected:
        XD_ApplicationConfig m_config;
        XD_ApplicationContext m_context;

        XD_Application_Base(const XD_ApplicationConfig& _config);

        bl fWantsToTerminate() const { mXD_NOT_IMPLEMENTED(); return false; }
        X fTerminateSubsystemsX() { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
        X fTerminateWidgetX(class XD_Window* _window) { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
    };

}
