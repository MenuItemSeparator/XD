#pragma once

#include "XDEngine_Minimal.h"

namespace XD
{

    class XD_ENGINE_API XD_Application_Interface
    {
    public:
        virtual ~XD_Application_Interface() = default;
        virtual void* fCreateWidget() { return nullptr; }
    };

    class XD_ENGINE_API XD_Application : public XD_Application_Interface
    {
    public:
        XD_Application () {}

        void fLoop()
        {
            mLOG("Loop is here!");
        }
    };

}
