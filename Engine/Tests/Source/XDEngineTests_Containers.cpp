#include "Graphics/XD_Graphics_Minimal.h"
#include "Common/Container/XD_Array.h"
#include "XD_Test_Minimal.h"

namespace XD
{
    u8 globalCounter = 0;

    struct Nums
    {
    public:
        Nums() : 
        Nums(0, 0)
        {}

        Nums(u8 _x, u8 _y) : 
        X(_x),
        Y(_y)
        {
            ++globalCounter;
        }

        Nums(const Nums& _other) :
        X(_other.X),
        Y(_other.Y)
        {
            ++globalCounter;
        }

        ~Nums()
        {
            --globalCounter;
        }

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
            Arr.fAdd(Nums{22, 23});
            mXD_IS_TRUE(Arr.fGetSize() == 1, "Arr size with 1 elem is not 1");
            mXD_IS_TRUE(Arr.fGetCapacity() == 1, "Arr capacity with 1 elem is not " << Arr.fGetCapacity());
            mXD_IS_TRUE(Arr[0].X == 22, "Arr 0 elem X not equals 22");
            mXD_IS_TRUE(Arr[0].Y == 23, "Arr 0 elem Y not equals 23");
            Arr.fClear();
            mXD_IS_TRUE(Arr.fGetSize() == 0, "Arr size with 0 elem is not 0");
            mXD_IS_TRUE(Arr.fGetCapacity() == 1, "Arr capacity with 0 elem is not " << Arr.fGetCapacity());
            Arr.fAdd(Nums{22, 23});
            mXD_IS_TRUE(Arr.fGetCapacity() == 1, "Arr capacity with 1 elem is not " << Arr.fGetCapacity());
            Arr.fAdd(Nums{22, 23});
            mXD_IS_TRUE(Arr.fGetCapacity() == 3, "Arr capacity with 3 elem is not " << Arr.fGetCapacity());
            Arr.fAdd(Nums{22, 23});
            Arr.fAdd(Nums{20, 40});
            Arr.fAdd(Nums{22, 23});
            mXD_IS_TRUE(Arr.fGetCapacity() == 7, "Arr capacity with 7 elem is not " << Arr.fGetCapacity());
            Arr.fRemoveLast();
            mXD_IS_TRUE(Arr.fLast()->X == 20, "Arr last elem X not equals 20");
            mXD_IS_TRUE(Arr.fLast()->Y == 40, "Arr last elem Y not equals 40");
            mXD_IS_TRUE(Arr.fGetSize() == 4, "Arr size with 4 elem is not 4");
            Arr.fResize(2);
            mXD_IS_TRUE(Arr.fGetSize() == 2, "Arr size with 2 elem is not 2");
            Arr.fReserve(5);
            mXD_IS_TRUE(Arr.fGetCapacity() == 7, "Arr capacity with 7 elem is not " << Arr.fGetCapacity());
            Arr.fReserve(10);
            mXD_IS_TRUE(Arr.fGetCapacity() == 15, "Arr capacity with 15 elem is not " << Arr.fGetCapacity());
        }

        {
            XD_Array<Nums> Arr1{mallocWrapper.get()};
            Arr1.fAdd(Nums{22, 23});
            Arr1.fAdd(Nums{22, 23});
            XD_Array<Nums> Arr2{mallocWrapper.get()};
            Arr2.fAdd(Nums{6, 8});
            Arr2.fAdd(Nums{6, 8});
            Arr2.fAdd(Nums{6, 8});
            Arr2 = Arr1;
            mXD_IS_TRUE(Arr2.fGetSize() == 2, "Arr size with 2 elem is " << Arr2.fGetSize());
            mXD_IS_TRUE(Arr2[0].X == 22, "Arr elem 0 wasn't copied. It is " << Arr2[0].X);
            mXD_IS_TRUE(Arr2[1].X == 22, "Arr elem 1 wasn't copied. It is " << Arr2[1].X);
        }

        mXD_IS_TRUE(globalCounter == 0, "Global counter not 0. It is " << globalCounter);

        return A_A;
    }
}

int
main(int argc, const char** argv)
{
    X_Call(XD::Test_Array(), "XD Array test failed");
    return 0;
}
