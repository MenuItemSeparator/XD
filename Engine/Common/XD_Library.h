#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_Library final
    {
        class XD_Library_Impl;
    public:
        XD_Library();
        XD_Library(const std::string& _libraryName);
        ~XD_Library();

        void fLoadXDLibrary(const std::string& _libraryName);
        void fUnloadXDLibrary();
        bool fIsLoaded() const;

    private:
        UPtr<XD_Library_Impl> m_libraryImplementation;
    };

    typedef XD::XD_Module_Interface*(*tCreateModule)();
}
