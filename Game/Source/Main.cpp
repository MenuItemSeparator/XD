#include "Application/XD_Application.h"
#include <Common/XD_Library.h>

int main()
{
    XD::XD_ApplicationConfig applicationConfig{};
    applicationConfig.m_displayName = "XD";

    XD::XD_Library library{};
    library.fLoadXDLibrary("SAMPLE_MATH.dll");

    XD::XD_Application application{applicationConfig};
    if(!application.fInitialize())
    {
        mLOG("Invalid application initialization");
        return 1;
    }

    mLOG("Main loop started");
    XD::XD_ApplicationTerminationReason_Enum terminationReason = application.fLoop();

    switch (terminationReason)
    {
    case XD::XD_ApplicationTerminationReason_Enum::ClosedByUser:
        mLOG(applicationConfig.m_displayName << " was closed by user");
        return 0;
    default:
        mLOG(applicationConfig.m_displayName << " has unknown reason of termination");
        return 1;
    }
}
