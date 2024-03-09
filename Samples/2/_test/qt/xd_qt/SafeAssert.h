#pragma once
#include <iostream>
#include <cassert>

#define m_pass (void)0

#ifdef USE_CUSTOM_ASSERTIONS
#define m_assert(_expr) \
    if(!(_expr)){std::cout<<"Assertion failed! "<<#_expr<<" at "<<__LINE__<< " in " << __FILE__; std::_Exit(1); } m_pass
#else
    #define m_assert(_expr) assert(_expr)
#endif
