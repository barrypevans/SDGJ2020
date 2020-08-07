#pragma once 
#include "ISystem.h"
#include <GL/glew.h>
#include <sdl/SDL.h>
#undef main

class Game;
#include "game.h"

class Window : public ISystem
{
public:
	Window(Game* pGame) : m_pGame(pGame) {}

	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	void PollEvents();

private:

	SDL_Window* m_pSdlWindow;
	Game* m_pGame;
	SDL_GLContext m_glContext;
};
static Window* g_pWindow;