#include "XD_WindowsLibrary.h"

namespace XD
{
    XD_Library::XD_Library() :
        XD_Library_Base(),
        m_libraryName(),
        m_libraryHandle(0),
        m_isLibraryLoaded(false)
    {}

    XD_Library::~XD_Library()
    {
        if(m_isLibraryLoaded)
        {
           fUnloadLibraryX().fCheck();
        }
    }

    X
    XD_Library::fLoadLibraryX(const std::string& _libraryName)
    {
        if(m_isLibraryLoaded)
        {
            mLOG("Library with name " << _libraryName << " is already loaded.");
            return X::fFail();
        }

        m_libraryHandle = LoadLibraryA(_libraryName.c_str());

        if(m_libraryHandle == NULL)
        {
            mLOG("Error when loading library " << _libraryName);
            return X::fFail();
        }

        m_libraryName = _libraryName;
        m_isLibraryLoaded = true;
        return X::fSuccess();
    }

    XD_FuncProc 
    XD_Library::fvGetProcAddress(const char* _procName)
    {
        mXD_ASSERT(m_isLibraryLoaded);
        FARPROC procPtr = GetProcAddress(m_libraryHandle, _procName);
        mXD_ASSERT(procPtr != nullptr);

        return XD_FuncProc{ reinterpret_cast<void*>(procPtr) };
    }

    X
    XD_Library::fUnloadLibraryX()
    {
        if(!m_isLibraryLoaded)
        {
            mLOG("Library wasn't loaded.");
            return X::fFail();
        }

        if(!FreeLibrary(m_libraryHandle))
        {
            mLOG("Error when unloading library " << m_libraryHandle);
            return X::fFail();
        }

        m_isLibraryLoaded = false;
        return X::fSuccess();
    }

    bl
    XD_Library::fIsLoaded() const
    {
        return m_isLibraryLoaded;
    }

    XD_FuncProc 
    XD_WGL_Library::fvGetProcAddress(const char *_procName)
    {
        mXD_ASSERT(m_isLibraryLoaded);
        FARPROC procPtr = wglGetProcAddress(_procName);
        mXD_ASSERT(procPtr != nullptr);

        return XD_FuncProc{ reinterpret_cast<void*>(procPtr) };
    }

}
