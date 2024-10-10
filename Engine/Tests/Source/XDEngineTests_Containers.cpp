#include "Graphics/XD_Graphics_Minimal.h"
#include "Common/Container/XD_Array.h"
#include "XD_Test_Minimal.h"

namespace XD
{
    struct Nums
    {
    public:
        u8 X;
        u8 Y;
    };

    X
    Test_Array()
    {
        tUptr<XD_MallocWrapper> mallocWrapper = std::make_unique<XD_MallocWrapper>();

        {
            XD_Array<Nums> Arr{mallocWrapper.get()};
            mXD_IS_TRUE(Arr.fGetSize() == 0, "Empty arr size not 0");
            mXD_IS_TRUE(Arr.fGetCapacity() == 0, "Empty arr capacity not 0");
            Arr.fAdd(Nums{.X = 22, .Y = 23});
            mXD_IS_TRUE(Arr.fGetSize() == 1, "Arr size with 1 elem is not 1");
            mXD_IS_TRUE(Arr.fGetCapacity() == 1, "Arr capacity with 1 elem is not " << Arr.fGetCapacity());
            Arr.fClear();
            mXD_IS_TRUE(Arr.fGetSize() == 0, "Arr size with 0 elem is not 0");
            mXD_IS_TRUE(Arr.fGetCapacity() == 1, "Arr capacity with 0 elem is not " << Arr.fGetCapacity());
        }

        return A_A;
    }
}

int
main(int argc, const char** argv)
{
    X_Call(XD::Test_Array(), "XD Array test failed");
    return 0;
}
