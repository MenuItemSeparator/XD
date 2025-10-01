#include "XCallTests.h"

namespace wtf { namespace tests {

Result
Result_Tests::fnTests()
{
    xcall(fnTest_1());
    xcall(fnTest_2());
    return Result(1);
}

Result
Result_Tests::fnTest_1()
{
    return Result(1);
}

Result
Result_Tests::fnTest_2()
{
    return Result(1);
}

}}
