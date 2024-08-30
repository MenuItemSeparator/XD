#pragma once
#include <libloaderapi.h>
#include <Windows.h>
#include <wingdi.h>
#include "XD_Engine_Minimal.h"
#include "../../XD_Library.h"

//Windows implementation
namespace XD
{
    class XD_ENGINE_API XD_Library : public XD_Library_Base
    {
    public:
        XD_Library();
        ~XD_Library();

        X fLoadLibraryX(const std::string& _libraryName);
        virtual XD_FuncProc fvGetProcAddress(const char* _procName);
        X fUnloadLibraryX();
        bl fIsLoaded() const;

    protected:
        std::string m_libraryName;
        HMODULE m_libraryHandle;
        bl m_isLibraryLoaded;
    };

    class XD_ENGINE_API XD_WGL_Library : public XD_Library
    {
    public:
        virtual XD_FuncProc fvGetProcAddress(const char* _procName) override;
    };

}
