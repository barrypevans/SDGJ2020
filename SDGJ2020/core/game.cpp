#include "game.h"
#include "stdio.h"
#include "Assert.h"
#include "glm/glm.hpp"

#include "asset-manager.h"
#include "window.h"
#include "audio.h"

void Game::Init()
{
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");

	g_pAudio->Play(Audio::GameClip::kTest, .5f, 10);
}

void Game::CleanUp()
{
	if (g_pWindow)
	{
		g_pWindow->CleanUp();
		delete g_pWindow;
	}
}

void Game::Update()
{

	if (g_pWindow)
	{
		g_pWindow->PollEvents();
		g_pWindow->Update();
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
	g_pAssetManager = new AssetManager();
	g_pWindow = new Window(this);
	g_pAudio = new Audio();

	g_pAssetManager->Init();
	g_pWindow->Init();
	g_pAudio->Init();
}
