#include "Main.h"
#include "Application/Platform/XDApplication_PlatformSelector.h"
#include "Common/Platform/XDCommon_PlatformSelector.h"
#include "Common/XD_Utility.h"
#include "glad.h"

int
main(int argc, char** argv)
{
    if(!gladLoadGLLoader()

    XD::XD_ApplicationConfig applicationConfig{};
    applicationConfig.m_displayName = "XD";

    XD::XD_Application application{applicationConfig};
    X_Call(application.fvInitializeX(), "Application initialization error");

    mLOG("Main loop started");
    X_Call(application.fLoopX(), "Application loop error");

    return 0;
}
