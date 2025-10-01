#include <iostream>
#include "xcall/XCallTests.h"

int
main()
{
    wtf::tests::Result_Tests tests;
    wtf::Result res = tests.fnTests();
    if(res < 0)
    {
        std::cout<<"Tests failed! "<<std::endl;
        return wtf::Codes::critical_failure;
    }

    std::cout<<"All tests completed successfully! "<<std::endl;
    return wtf::Codes::critical_success;
}
