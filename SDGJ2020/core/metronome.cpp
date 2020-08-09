#include "metronome.h"

Metronome* Metronome::g_pMetronome;

void Metronome::Init() 
{
	m_start = TimeSinceEpochMillisec();
	m_tick = 0;
	m_activeOffset = 0;
	Beat = false;
}
void Metronome::Update() 
{
	if (m_activeOffset != (uint64_t)0)
	{
		uint64_t currentFrame = TimeSinceEpochMillisec();
		uint64_t frameDelta = currentFrame - m_lastFrame;

		m_tick += frameDelta;
		if (m_tick >= m_activeOffset)
		{
			m_tick -= m_activeOffset;
			m_tick %= m_activeOffset;
			//Tick
			Beat = true;
			printf("Tick ");
			//Audio::g_pAudio->Play(Audio::GameClip::kMetDown, .5, 0);
		}
		else
			Beat = false;

		m_lastFrame = currentFrame;
	}
}
void Metronome::CleanUp() 
{
	Stop();
}

void Metronome::Start(float bpm)
{
	m_start = TimeSinceEpochMillisec();
	m_activeOffset = 60000.0f / bpm;
	m_lastFrame = TimeSinceEpochMillisec();
}

void Metronome::Stop()
{
	m_activeOffset = 0;
}

uint64 Metronome::ActiveBeatOffset()
{
	if(m_activeOffset == (uint64)0)
		return 0;
	uint64_t difference = (TimeSinceEpochMillisec() - m_start) % m_activeOffset;
	if (difference < (m_activeOffset / 2))
		return difference;
	return m_activeOffset - difference;
}

uint64 Metronome::TimeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}