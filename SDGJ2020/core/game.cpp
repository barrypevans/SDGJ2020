#include "game.h"
#include "stdio.h"
#include "Assert.h"
#include "glm/glm.hpp"

#include "asset-manager.h"
#include "window.h"
#include "audio.h"
#include "renderable.h"
#include "renderer.h"
#include "camera.h"
#include "metronome.h"
#include "time.h"

Game* Game::g_pGame;

void Game::Init()
{
	g_pGame = this;
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");
	
	Metronome::g_pMetronome->Start(120);
	//Audio::g_pAudio->Play(Audio::GameClip::kMetReference, .5f, 10);
	InitCoreEntities();
}

void Game::CleanUp()
{
	Audio::g_pAudio->CleanUp();
	Window::g_pWindow->CleanUp();
	AssetManager::g_pAssetManager->CleanUp();
	Camera::g_pCamera->CleanUp();
	Metronome::g_pMetronome->CleanUp();
	Time::g_pTime->CleanUp();

	delete Camera::g_pCamera;
	delete  Audio::g_pAudio;
	delete  Window::g_pWindow;
	delete  AssetManager::g_pAssetManager;
}

void Game::Update()
{
	Time::g_pTime->Update();

	if (Window::g_pWindow)
	{
		Window::g_pWindow->PollEvents();
		Window::g_pWindow->Update();
	}

	Renderer::g_pRenderer->ClearRenderQueue();

	// update all entities
	for (int i = 0; i < m_entityList.size(); ++i)
		if (m_entityList[i])
			m_entityList[i]->Update();



	pBerryEntity->m_rotation += 0.1;
	pBerryEntity->m_scale += glm::vec2(0.01, 0.01) * Time::g_pTime->GetDeltaTime();



	Renderer::g_pRenderer->RenderAllInQueue();
	
	Window::g_pWindow->SwapBuffers();
	Metronome::g_pMetronome->Update();
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
	Window::g_pWindow = new Window(this);
	AssetManager::g_pAssetManager = new AssetManager();
	Audio::g_pAudio = new Audio();
	Renderer::g_pRenderer = new Renderer();
	Camera::g_pCamera = new Camera();
	Metronome::g_pMetronome = new Metronome();
	Time::g_pTime = new Time();

	Window::g_pWindow->Init();
	AssetManager::g_pAssetManager->Init();
	Audio::g_pAudio->Init();
	Renderer::g_pRenderer->Init();
	Camera::g_pCamera->Init();
	Metronome::g_pMetronome->Init();
	Time::g_pTime->Init();
}

void Game::InitCoreEntities()
{
	Entity* pDanceFloorEntity = CreateEntity();
	auto danceRenderable = pDanceFloorEntity->AddComponent<Renderable>();
	danceRenderable->SetTexture("art/dance-floor.png");
	pDanceFloorEntity->m_scale *= 15;

	pCharacterEntity = CreateEntity();
	auto charRenderable = pCharacterEntity->AddComponent<Renderable>();
	charRenderable->SetTexture("art/sprite_01.png");

	pBerryEntity = CreateEntity();
	auto berryRenderable = pBerryEntity->AddComponent<Renderable>();
	berryRenderable->SetTexture("art/berry.png");
	pBerryEntity->m_position = glm::vec2(2, 1);
	pBerryEntity->m_scale *= 2;

}
