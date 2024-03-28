#include "XD_LibraryWindows_Implementation.h"

namespace XD
{

    XD_Library::XD_Library_Impl::XD_Library_Impl() :
        m_libraryName(),
        m_libraryHandle(0),
        m_isLibraryLoaded(false)
    {
    }

    void XD_Library::XD_Library_Impl::LoadXDLibrary(const std::string &_libraryName)
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

        m_libraryName = _libraryName;
        m_isLibraryLoaded = true;
    }

    void XD_Library::XD_Library_Impl::UnloadXDLibrary()
    {
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

    //===Impl end===

    XD_Library::XD_Library() :
        m_libraryImplementation(std::make_unique<XD_Library_Impl>())
    {

    }

    XD_Library::~XD_Library()
    {

    }

    void XD_Library::LoadXDLibrary(const std::string& _libraryName)
    {
        m_libraryImplementation->LoadXDLibrary(_libraryName);
    }

    void XD_Library::UnloadXDLibrary()
    {
        m_libraryImplementation->UnloadXDLibrary();
    }

}
