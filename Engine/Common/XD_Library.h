#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_FuncProc_Base
    {
    public:
        template <typename T, typename = std::enable_if_t<std::is_function_v<T>>>
        operator T *() const
        {
            mXD_NOT_IMPLEMENTED();
            return nullptr;
        }
    protected:
        XD_FuncProc_Base() = default;
    };

    class XD_ENGINE_API XD_Library_Base
    {
    public:
        XD_Library_Base(const XD_Library_Base&) = delete;
        XD_Library_Base& operator=(const XD_Library_Base&) = delete;

        X fLoadLibraryX(const std::string& _libraryName) { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
        X fUnloadLibraryX() { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
        bl fIsLoaded() const { mXD_NOT_IMPLEMENTED(); return false; }

    protected:
        XD_Library_Base() = default;
    };
}
