#include "Graphics/XD_Graphics_Minimal.h"
#include "Graphics/XD_CommandBuffer.h"
#include "XD_Test_Minimal.h"

namespace XD
{
    struct TestStruct
    {
    public:
        int X = 2;
        float Y = 4;
        const char* Z = "Hello";
    };

    X
    Test_StartAndFinishCalls()
    {
        int dataInt = 4;
        TestStruct dataStruct{3,5,"World"};

        XD_CommandBuffer commandBuffer{};
        commandBuffer.fStartWrite_Internal();
        X_Call(commandBuffer.fWriteX<int>(dataInt), "Can't write int to command buffer in tests");
        X_Call(commandBuffer.fWriteX<TestStruct>(dataStruct), "Can't write struct to command buffer in tests");
        commandBuffer.fFinishWrite_Internal();

        int checkInt = 0;
        TestStruct checkStruct{};

        X_Call(commandBuffer.fReadX<int>(checkInt), "Can't read int from command buffer in tests");
        mXD_ASSERT(checkInt == dataInt);
        X_Call(commandBuffer.fReadX<TestStruct>(checkStruct), "Can't read struct from command buffer in tests");
        mXD_ASSERT(checkStruct.X == dataStruct.X);
        mXD_ASSERT(checkStruct.Y == dataStruct.Y);
        mXD_ASSERT(checkStruct.Z == dataStruct.Z);

        return A_A;
    }
}

int
main(int argc, const char** argv)
{
    X_Call(XD::Test_StartAndFinishCalls(), "Start/Finish calls causing errors");
    return 0;
}
