#include "game.h"
#include "stdio.h"
#include "Assert.h"
#include "glm/glm.hpp"
#include "level-test.h"

void Game::Init()
{
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");
	m_pLoadedLevel = new TestLevel();
	
}

void Game::CleanUp()
{
	if (m_pWindow)
	{
		m_pWindow->CleanUp();
		delete m_pWindow;
	}
}

void Game::Update()
{
	if (m_pWindow)
	{
		m_pWindow->PollEvents();
		m_pWindow->Update();
	}
}

bool Game::IsRunning()
{
	return m_isRunning;
}

void Game::RequestShutDown()
{
	m_isRunning = false;
}

void Game::InitSystems()
{
	m_pWindow = new Window(this);
	m_pWindow->Init();
}
