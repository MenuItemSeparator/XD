#pragma once
#include <libloaderapi.h>
#include "XDEngine_Minimal.h"
#include "../../XD_Library.h"

namespace XD
{
    class XD_ENGINE_API XD_FuncProc : public XD_FuncProc_Base
    {
    public:
        XD_FuncProc(void* _procPtr);

        template <typename T, typename = std::enable_if_t<std::is_function_v<T>>>
        operator T *() const
        {
            return reinterpret_cast<T *>(m_procPtr);
        }
    private:
        FARPROC m_procPtr;
    };

    class XD_ENGINE_API XD_Library : public XD_Library_Base
    {
    public:
        XD_Library();
        ~XD_Library();

        X fLoadLibraryX(const std::string& _libraryName);
        X fUnloadLibraryX();
        bl fIsLoaded() const;

    private:
        std::string m_libraryName;
        HMODULE m_libraryHandle;
        bl m_isLibraryLoaded;
    };

}
