#pragma once
#include <libloaderapi.h>

#include "XDEngine_Minimal.h"
#include "../../XD_Library.h"

namespace XD
{

    class XD_ENGINE_API XD_Library::XD_Library_Impl final
    {
    public:
        XD_Library_Impl();
        ~XD_Library_Impl();
        void fLoadXDLibrary(const std::string& _libraryName);
        void fUnloadXDLibrary();
        bool fIsLoaded() const;

    private:
        std::string m_libraryName;
        HMODULE m_libraryHandle;
        XD_Module_Interface* m_moduleInterface;
        bool m_isLibraryLoaded;
    };

}
