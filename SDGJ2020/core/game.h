#pragma once
#include "ISystem.h"

class Window;
#include "window.h"

class Game : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	bool IsRunning();
	void RequestShutDown();

	// Define All game systems here
	Window* m_pWindow;

private:
	void InitSystems();

	bool m_isRunning;
};
