#include "XD_LibraryWindows_Implementation.h"

namespace XD
{

    XD_Library::XD_Library_Impl::XD_Library_Impl() :
        m_libraryName(),
        m_libraryHandle(0),
        m_moduleInterface(nullptr),
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

        tCreateModule creatingModuleProc = (tCreateModule)GetProcAddress(m_libraryHandle, "CreateModule");
        if(!creatingModuleProc)
        {
            mLOG("Loaded library " << _libraryName << " is not XD library");
            fUnloadXDLibrary();
            return;
        }

        m_moduleInterface = creatingModuleProc();

        if(!m_moduleInterface)
        {
            mLOG("Can't create " << _libraryName << " module");
            fUnloadXDLibrary();
            return;
        }

        m_moduleInterface->InitializeModule();

        m_libraryName = _libraryName;
        m_isLibraryLoaded = true;
    }

    void XD_Library::XD_Library_Impl::fUnloadXDLibrary()
    {
        if(m_moduleInterface)
        {
            m_moduleInterface->DeinitializeModule();
            delete m_moduleInterface;
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

    XD_Module_Interface *XD_Library::XD_Library_Impl::fGetLibraryModule()
    {
        return m_moduleInterface;
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

    XD_Module_Interface *XD_Library::fGetLibraryModule()
    {
        return m_libraryImplementation->fGetLibraryModule();
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
