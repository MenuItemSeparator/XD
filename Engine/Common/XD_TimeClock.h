#pragma once
#include "XD_Engine_Minimal.h"

namespace XD 
{
	class XD_ENGINE_API XD_TimeClock final
	{
	public:
		XD_TimeClock();
		double Restart();
	private:
		using Clock = std::chrono::high_resolution_clock;
		using Duration = std::chrono::duration<double, std::micro>;

		Clock::time_point m_lastTime;
	};
}