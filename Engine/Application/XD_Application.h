#pragma once

#include "XDApplication_Minimal.h"
#include "XD_Widget.h"

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
        virtual X fInitializeX() = 0;
        virtual X fForceTerminateX() = 0;
        virtual X fLoopX() = 0;

        virtual ~XD_Application_Interface() = default;
    };

    class XD_ENGINE_API XD_Application : public XD_Application_Interface
    {
        class XD_ApplicationContext
        {
        public:
            bl m_requestedTermination : 1;
        };

    public:
        XD_Application();
        XD_Application(const XD_ApplicationConfig& _config);
        XD_Application(const XD_Application&) = delete;
        XD_Application& operator=(const XD_Application&) = delete;
        virtual ~XD_Application() = default;

        virtual X fInitializeX() override;
        virtual X fForceTerminateX() override;
        virtual X fLoopX() override;

    private:
        XD_ApplicationConfig m_config;
        XD_ApplicationContext m_context;
        SPtr<XD_Widget> m_window;

        bl fWantsToTerminate() const;
        X fTerminateSubsystemsX();
        X fTerminateWidgetX(XD_Widget* _widget);
    };

}
