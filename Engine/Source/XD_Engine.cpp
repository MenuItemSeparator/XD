#include "XD_Engine.h"

namespace XD
{

    XD_Engine::XD_Engine() :
        m_libraries()
    {}

    XD_Result XD_Engine::Initialize()
    {
        m_libraries.push_back(std::make_shared<XD_Library>("SAMPLE_MATH.dll"));
        return XD_Result::Success();
    }
}
