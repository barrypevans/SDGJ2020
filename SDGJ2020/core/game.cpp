#include "game.h"
#include "stdio.h"
#include "Assert.h"
#include "glm/glm.hpp"

#include "asset-manager.h"
#include "window.h"
#include "audio.h"
#include "renderable.h"
#include "renderer.h"


void Game::Init()
{
	g_pGame = this;
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");

	Audio::g_pAudio->Play(Audio::GameClip::kTest, .5f, 10);
	Entity* entity = CreateEntity();
	entity->AddComponent<Renderable>();
}

void Game::CleanUp()
{
	Audio::g_pAudio->CleanUp();
	Window::g_pWindow->CleanUp();
	AssetManager::g_pAssetManager->CleanUp();

	delete  Audio::g_pAudio;
	delete  Window::g_pWindow;
	delete  AssetManager::g_pAssetManager;
}

void Game::Update()
{
	if (Window::g_pWindow)
	{
		Window::g_pWindow->PollEvents();
		Window::g_pWindow->Update();
	}

	Renderer::g_pRenderer->ClearRenderQueue();

	// update all entities
	for (int i = 0; i < m_entityList.size(); ++i)
		if (m_entityList[i])
			m_entityList[0]->Update();

	Renderer::g_pRenderer->RenderAllInQueue();
	
	Window::g_pWindow->SwapBuffers();
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
	AssetManager::g_pAssetManager = new AssetManager();
	Window::g_pWindow = new Window(this);
	Audio::g_pAudio = new Audio();
	Renderer::g_pRenderer = new Renderer();
	
	AssetManager::g_pAssetManager->Init();
	Window::g_pWindow->Init();
	Audio::g_pAudio->Init();
	Renderer::g_pRenderer->Init();
}
