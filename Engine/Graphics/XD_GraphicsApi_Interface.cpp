#include "XD_GraphicsApi_Interface.h"

namespace XD
{
    X
    XD_GraphicsApi_Interface::fInitializeX()
    {
        mXD_ASSERT(m_initializeProcPtr);
        X_Call(m_initializeProcPtr(this), "Invalid graphics api initialization proc");
        return A_A;
    }

    X XD_GraphicsApi_Interface::fShutdownX()
    {
        mXD_ASSERT(m_shutdownProcPtr);
        X_Call(m_shutdownProcPtr(this), "Invalid graphics api shutdown proc");
        return A_A;
    }
}
