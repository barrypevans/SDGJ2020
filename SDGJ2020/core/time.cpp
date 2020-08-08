#include "time.h"
#include <chrono>

Time* Time::g_pTime;

static long long TimeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Time::Init()
{
	m_lastTime = TimeSinceEpochMillisec();
	m_curTime = TimeSinceEpochMillisec();
}

void Time::CleanUp()
{
}

void Time::Update()
{
	m_lastTime = m_curTime;
	m_curTime = TimeSinceEpochMillisec();
	long long deltaTimeMillisecs = m_curTime - m_lastTime;
	m_deltaTime = static_cast<float>(deltaTimeMillisecs) * .001f;
}

float Time::GetDeltaTime()
{
	return m_deltaTime;
}

