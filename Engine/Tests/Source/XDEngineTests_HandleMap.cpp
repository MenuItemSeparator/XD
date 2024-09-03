#include "Graphics/XD_Graphics_Minimal.h"
#include "Graphics/XD_HandleMap.h"
#include "XD_Test_Minimal.h"

namespace XD
{
    X
    Test_CreateAndDestroyHandle()
    {
        XD_HandleMap<u8, 1024> m_testHandleMap{};
        u8 handle = m_testHandleMap.fCreateHandle();
        mXD_IS_TRUE(m_testHandleMap.fIsValid(handle), "Just created handle is not valid");
        X_Call(m_testHandleMap.fFreeHandleX(handle), "Can't free handle");
        mXD_IS_FALSE(m_testHandleMap.fIsValid(handle), "Just deleted handle is still valid");
        u8 newHandle = m_testHandleMap.fCreateHandle();
        mXD_IS_TRUE(handle == newHandle, "Handle map doesn't use cached handles");

        return A_A;
    }
}

int
main(int argc, const char** argv)
{
    X_Call(XD::Test_CreateAndDestroyHandle(), "Creation or destroying handle test was failed");
    return 0;
}
