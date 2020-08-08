#pragma once
#include "ISystem.h"

class Time : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;
	float GetDeltaTime();

	static Time* g_pTime;

private:
	long long m_curTime;
	long long m_lastTime;
	float m_deltaTime;
};

