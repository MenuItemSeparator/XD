#include "XD_TimeClock.h"

namespace
{
	const double MICRO = 1'000'000.0;
}

namespace XD
{
	XD_TimeClock::XD_TimeClock()
	{
		m_lastTime = Clock::now();
	}

	double XD_TimeClock::Restart()
	{
		const Clock::time_point oldTime = m_lastTime;
		m_lastTime = Clock::now();
		Duration deltaTimeMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(m_lastTime - oldTime);
		double deltaTimeSeconds = deltaTimeMicroseconds.count() / MICRO;
		return deltaTimeSeconds;
	}
}