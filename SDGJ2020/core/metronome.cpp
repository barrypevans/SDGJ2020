#include "metronome.h"

Metronome* Metronome::g_pMetronome;

void Metronome::Init() 
{
	m_start = TimeSinceEpochMillisec();
	m_activeOffset = 0;
	Beat = false;
}
void Metronome::Update() 
{
	if (m_activeOffset != (uint64_t)0)
	{
		uint64_t currentFrame = TimeSinceEpochMillisec();

		if (currentFrame-m_start >= (m_currentBeat*m_activeOffset))
		{
			//Tick
			Beat = true;
			m_currentBeat++;

			//printf("Tick ");
			//Audio::g_pAudio->Play(Audio::GameClip::kMetDown, .5, 0);
		}
		else
			Beat = false;

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
	m_currentBeat = 1;
}

void Metronome::Stop()
{
	m_activeOffset = 0;
}

uint64 Metronome::ActiveBeatOffset()
{
	if(m_activeOffset == 0)
		return 0;
	float difference = (m_currentBeat * m_activeOffset) - (TimeSinceEpochMillisec() - m_start);
	if (difference < (m_activeOffset / 2))
		return (uint64)difference;
	return (uint64)(m_activeOffset - difference);
}

uint64 Metronome::TimeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}