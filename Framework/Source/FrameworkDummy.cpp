#include "FrameworkDummy.h"
#include "Core/EngineDummy.h"

namespace XDFramework
{
    void FrameworkDummy::SayHello()
    {
        XDEngine::EngineDummy::SayHello();
    }
}

