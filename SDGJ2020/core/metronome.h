#pragma once
#include "ISystem.h"
#include <list>
#include <chrono>
#include "audio.h"

typedef unsigned long long uint64;

class Metronome : public ISystem
{

public:
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	void Start(float bpm);
	void Stop();

	static const int kBeatThreshold = 100;
	bool Beat;

	/// <summary>
	/// Milliseconds to the closest beat
	/// </summary>
	uint64 ActiveBeatOffset();
	static Metronome* g_pMetronome;

private:
	uint64 TimeSinceEpochMillisec();

	int m_currentBeat = 1;
	uint64 m_start;
	double m_activeOffset;

};