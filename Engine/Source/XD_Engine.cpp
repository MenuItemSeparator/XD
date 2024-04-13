#include "XD_Engine.h"

namespace XD
{

    XD_Engine::XD_Engine() :
        m_libraries()
    {}
    
    X
    XD_Engine::fInitializeX()
    {
        m_libraries.push_back(std::make_shared<XD_Library>());
        X_Call(m_libraries.back()->fLoadLibraryX("SAMPLE_MATH.dll"), "Can't load sample math lib");
        return X::fSuccess();
    }
}
