#pragma once

#include "XDApplication_Minimal.h"
#include "XD_Window_Widget.h"

namespace XD
{

    enum class XD_ApplicationTerminationReason_Enum
    {
        Unknown = 0,
        ClosedByUser,
        COUNT
    };

    class XD_ENGINE_API XD_ApplicationConfig final
    {
    public:
        std::string m_displayName;

        XD_ApplicationConfig();
    };

    class XD_ENGINE_API XD_Application_Interface
    {
    public:
        virtual XD_Result fInitialize() = 0;
        virtual void fForceTerminate() = 0;
        virtual XD_ApplicationTerminationReason_Enum fLoop() = 0;

        virtual ~XD_Application_Interface() = default;
    };

    class XD_ENGINE_API XD_Application : public XD_Application_Interface
    {
        class XD_ApplicationContext
        {
        public:
            bool m_requestedTermination : 1;
        };

    public:
        XD_Application();
        XD_Application(const XD_ApplicationConfig& _config);
        XD_Application(const XD_Application&) = delete;
        XD_Application& operator=(const XD_Application&) = delete;
        virtual ~XD_Application() = default;

        virtual XD_Result fInitialize() override;
        virtual void fForceTerminate() override;
        virtual XD_ApplicationTerminationReason_Enum fLoop() override;

    private:
        XD_ApplicationConfig m_config;
        XD_ApplicationContext m_context;
        SPtr<XD_Window_Widget> m_window;

        bool fWantsToTerminate() const;
        XD_Result fDeinitialize();
    };

}
