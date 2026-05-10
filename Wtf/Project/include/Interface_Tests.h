#pragma once
#include "xcall/XCall.h"


namespace wtf{ namespace test {

class I_Test
{
public:
    virtual wtf::Result fnTest() { return wtf::Result(1); }
};

}}
