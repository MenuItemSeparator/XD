#pragma once

#define dDLLEXPORT __declspec(dllexport)

namespace XD
{
    class XD_Module_Interface
    {
    public:
        virtual ~XD_Module_Interface() = default;

        virtual void InitializeModule() = 0;
        virtual void DeinitializeModule() = 0;
    };
}

#define dIMPLEMENT_MODULE( ModuleImplClass, ModuleName ) \
    extern "C" dDLLEXPORT XD::XD_Module_Interface* CreateModule() \
    { \
            return new ModuleImplClass(); \
    } \
