#pragma once
#include "ISystem.h"

class Window;
class Audio;
#include "window.h"
#include "audio.h"

class Game : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	bool IsRunning();
	void RequestShutDown();

private:
	void InitSystems();

	bool m_isRunning;
};
