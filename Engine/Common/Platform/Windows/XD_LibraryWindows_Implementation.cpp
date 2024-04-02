#include "XD_LibraryWindows_Implementation.h"

namespace XD
{

    XD_Library::XD_Library_Impl::XD_Library_Impl() :
        m_libraryName(),
        m_libraryHandle(0),
        m_isLibraryLoaded(false)
    {}

    XD_Library::XD_Library_Impl::~XD_Library_Impl()
    {
        if(m_isLibraryLoaded)
        {
            fUnloadXDLibrary();
        }
    }

    void XD_Library::XD_Library_Impl::fLoadXDLibrary(const std::string &_libraryName)
    {
        if(m_isLibraryLoaded)
        {
            mLOG("Library with name " << _libraryName << " is already loaded.");
            return;
        }

        m_libraryHandle = LoadLibrary(_libraryName.c_str());

        if(m_libraryHandle == NULL)
        {
            mLOG("Error when loading library " << _libraryName);
            return;
        }

        OnAfterModuleLoadedFunc onLoadFunc = (OnAfterModuleLoadedFunc)GetProcAddress(m_libraryHandle, "OnAfterModuleLoaded");
        if(!onLoadFunc)
        {
            mLOG("Loaded library " << _libraryName << " is not XD library");
            fUnloadXDLibrary();
            return;
        }

        onLoadFunc();
        m_libraryName = _libraryName;
        m_isLibraryLoaded = true;
    }

    void XD_Library::XD_Library_Impl::fUnloadXDLibrary()
    {
        OnBeforeModuleUnloadedFunc onUnloadFunc = (OnBeforeModuleUnloadedFunc)GetProcAddress(m_libraryHandle, "OnBeforeModuleUnloaded");
        if(onUnloadFunc)
        {
            onUnloadFunc();
        }
        else
        {
            mLOG("The library you are trying to unload " << m_libraryName << " is not XD library");
        }

        if(!m_isLibraryLoaded)
        {
            mLOG("Library wasn't loaded.");
            return;
        }

        if(!FreeLibrary(m_libraryHandle))
        {
            mLOG("Error when unloading library " << m_libraryHandle);
            return;
        }

        m_isLibraryLoaded = false;
    }

    bool XD_Library::XD_Library_Impl::fIsLoaded() const
    {
        return m_isLibraryLoaded;
    }

    //===Impl end===

    XD_Library::XD_Library() :
        m_libraryImplementation(std::make_unique<XD_Library_Impl>())
    {}

    XD_Library::XD_Library(const std::string &_libraryName) : XD_Library()
    {
        fLoadXDLibrary(_libraryName);
    }

    XD_Library::~XD_Library()
    {
    }

    void XD_Library::fLoadXDLibrary(const std::string& _libraryName)
    {
        m_libraryImplementation->fLoadXDLibrary(_libraryName);
    }

    void XD_Library::fUnloadXDLibrary()
    {
        m_libraryImplementation->fUnloadXDLibrary();
    }

    bool XD_Library::fIsLoaded() const
    {
        return m_libraryImplementation->fIsLoaded();
    }
}
