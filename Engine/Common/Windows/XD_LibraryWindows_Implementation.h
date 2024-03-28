#pragma once
#include <libloaderapi.h>

#include "XDEngine_Minimal.h"
#include "../XD_Library.h"

namespace XD
{

    class XD_Library::XD_Library_Impl
    {
    public:
        XD_Library_Impl();
        void LoadXDLibrary(const std::string& _libraryName);
        void UnloadXDLibrary();

    private:
        std::string m_libraryName;
        HMODULE m_libraryHandle;
        bool m_isLibraryLoaded;
    };

}
