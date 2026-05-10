#pragma once
#include "Interface_Tests.h"
namespace wtf
{

    class Xml: public test::I_Test
    {
    public:
        Result fnProcessFile(const std::string& _path);

    public:
        Result fnTest() override;
    };

}
