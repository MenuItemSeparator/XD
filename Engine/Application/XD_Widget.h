#pragma once
#include "XDApplication_Minimal.h"

namespace XD
{

    class XD_ENGINE_API XD_Widget_Interface
    {
    public:
        XD_Widget_Interface() = default;
        virtual ~XD_Widget_Interface() = default;
    };

    class XD_ENGINE_API XD_Widget : public XD_Widget_Interface
    {

    };

}
