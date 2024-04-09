#include "XD_Application.h"

namespace XD
{

    XD_ApplicationConfig::XD_ApplicationConfig() :
        m_displayName("Nameless application")
    {}

    XD_Application_Base::XD_Application_Base(const XD_ApplicationConfig &_config) :
        m_config(_config),
        m_context()
    {}

}
