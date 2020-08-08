#include "game.h"
#include "stdio.h"
#include "Assert.h"
#include "glm/glm.hpp"

#include "asset-manager.h"
#include "window.h"
#include "audio.h"
#include "renderable.h"

void Game::Init()
{
	g_pGame = this;
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");

	g_pAudio->Play(Audio::GameClip::kTest, .5f, 10);
	Entity* entity = CreateEntity();
	entity->AddComponent<Renderable>();
}

void Game::CleanUp()
{
	g_pAudio->CleanUp();
	g_pWindow->CleanUp();
	g_pAssetManager->CleanUp();

	delete g_pAudio;
	delete g_pWindow;
	delete g_pAssetManager;
}

void Game::Update()
{
	// update all entities
	for (int i = 0; i < m_entityList.size(); ++i)
		if (m_entityList[i])
			m_entityList[i]->Update();

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

Entity* Game::CreateEntity()
{
	Entity* entity = new Entity();
	m_entityList.push_back(entity);
	return entity;
}
void Game::DestroyEntity(Entity*& entity)
{
	delete entity;
	entity = nullptr;
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
