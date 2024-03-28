#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{
    class XD_Library final
    {
        class XD_Library_Impl;
    public:
        XD_Library();
        ~XD_Library();

        void LoadXDLibrary(const std::string& _libraryName);
        void UnloadXDLibrary();

    private:
        UPtr<XD_Library_Impl> m_libraryImplementation;
    };



}
