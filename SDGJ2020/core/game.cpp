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
#include "Input.h"
#include "CharacterCollision.h"
#include "ui.h"
#include "player-controller.h"
#include "animatable.h"
#include "Entity_Controller.h"
#include "beatCounter.h"
#include "../game/dance-floor-visual-controller.h"
#include <time.h>
#include "game-logic-core.h"
Game* Game::g_pGame;

void Game::Init()
{
	//seed random numbers
	srand((unsigned)time(NULL));

	g_pGame = this;
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");

	Audio::g_pAudio->Play(Audio::GameClip::kFunkTheme, .1f, 10);
	Metronome::g_pMetronome->Start(120);
	InitCoreEntities();
}

void Game::CleanUp()
{
	Audio::g_pAudio->CleanUp();
	Window::g_pWindow->CleanUp();
	AssetManager::g_pAssetManager->CleanUp();
	Camera::g_pCamera->CleanUp();
	GameLogic::g_pGameLogic->CleanUp();
	Metronome::g_pMetronome->CleanUp();
	Time::g_pTime->CleanUp();
	UI::g_pUI->CleanUp();

	delete Camera::g_pCamera;
	delete  Audio::g_pAudio;
	delete  Window::g_pWindow;
	delete  AssetManager::g_pAssetManager;
}

void Game::Update()
{
	// delete entities that are marked for delete
	DestroyMarkedEntities();

	Time::g_pTime->Update();
	UI::g_pUI->Update();
	Camera::g_pCamera->Update();

	if (Window::g_pWindow)
	{
		Window::g_pWindow->PollEvents();
		Window::g_pWindow->Update();
	}

	Renderer::g_pRenderer->ClearRenderQueue();
	GameLogic::g_pGameLogic->Update();

	// update all entities
	for (int i = 0; i < m_entityList.size(); ++i)
		if (m_entityList[i])
			m_entityList[i]->Update();

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
void Game::DestroyEntity(Entity* entity)
{
	entity->m_markedForDestroy = true;
}


void Game::InitSystems()
{
	Window::g_pWindow = new Window(this);
	AssetManager::g_pAssetManager = new AssetManager();
	Audio::g_pAudio = new Audio();
	Renderer::g_pRenderer = new Renderer();
	Camera::g_pCamera = new Camera();
	GameLogic::g_pGameLogic = new GameLogic();
	Metronome::g_pMetronome = new Metronome();
	Time::g_pTime = new Time();
	Input::g_pInput = new Input();
	UI::g_pUI = new UI();
	CharacterCollision::g_pChracterCollision = new CharacterCollision();




	Window::g_pWindow->Init();
	AssetManager::g_pAssetManager->Init();
	Audio::g_pAudio->Init();
	Renderer::g_pRenderer->Init();
	Camera::g_pCamera->Init();
	Metronome::g_pMetronome->Init();
	Time::g_pTime->Init();
	Input::g_pInput->Init();
	UI::g_pUI->Init();
	GameLogic::g_pGameLogic->Init();
	CharacterCollision::g_pChracterCollision->Init();
}

void Game::InitCoreEntities()
{
	Entity* pBackDrop = CreateEntity();
	auto pBackDropRenderable = pBackDrop->AddComponent<Renderable>();
	pBackDropRenderable->SetTexture("art/backdrop.png");
	pBackDrop->m_scale *= 11;
	pBackDrop->m_position = glm::vec2(0, .5);
	pBackDropRenderable->m_layerOrder = -10;

	Entity* pDanceFloorEntity = CreateEntity();
	auto danceRenderable = pDanceFloorEntity->AddComponent<Renderable>();
	danceRenderable->SetTexture("art/dance-floor.png");
	danceRenderable->OverrideShader("shaders/board.fs");
	danceRenderable->m_layerOrder = -9;
	pDanceFloorEntity->AddComponent<DanceFloorVisualController>();
	pDanceFloorEntity->m_scale *= 10;


	Entity* pBeatCounter_B = CreateEntity();
	auto beatRenderable_B = pBeatCounter_B->AddComponent<Renderable>();
	beatRenderable_B->isUI = true;
	beatRenderable_B->SetTexture("art/BeatCounet_B.png");
	pBeatCounter_B->m_scale *= 3;
	pBeatCounter_B->m_position = glm::vec2(4, -3);

	/*
	Entity* pBeatCounter_C = CreateEntity();
	auto beatRenderable_C = pBeatCounter_C->AddComponent<Renderable>();
	beatRenderable_C->isUI = true;
	beatRenderable_C->SetTexture("art/BeatCounter_C.png");
	pBeatCounter_C->m_scale *= 3;
	pBeatCounter_C->m_position = glm::vec2(5, -3.8);
	*/

	Entity* pBeatCounter_A = CreateEntity();
	auto beatRenderable = pBeatCounter_A->AddComponent<Renderable>();
	beatRenderable->isUI = true;
	beatRenderable->SetTexture("art/BeatCounter_A.png");
	beatCounter* beatCountController = pBeatCounter_A->AddComponent<beatCounter>();
	pBeatCounter_A->m_scale *= .75;
	pBeatCounter_A->m_position = glm::vec2(2.93, -2.97);

	pBerryEntity = CreateEntity();
	auto berryRenderable = pBerryEntity->AddComponent<Renderable>();
	berryRenderable->isUI = true;
	berryRenderable->SetTexture("art/berry.png");
	berryRenderable->m_layerOrder = 3;
	pBerryEntity->m_position = glm::vec2(5.4, 1.6);
	pBerryEntity->m_scale *= 0.9;

	pBerryBarryEntity = CreateEntity();
	auto pBerryBarryRenderable = pBerryBarryEntity->AddComponent<Renderable>();
	pBerryBarryRenderable->isUI = true;
	pBerryBarryRenderable->SetTexture("art/BerryBarry.png");
	pBerryBarryRenderable->m_layerOrder = 2;
	pBerryBarryEntity->m_position = glm::vec2(5, 2.3);
	pBerryBarryEntity->m_scale *= 1.3;

}

void Game::DestroyMarkedEntities()
{
	// delete entities that are marked for delete
	for (int i = 0; i < m_entityList.size(); ++i)
	{
		if (!m_entityList[i] ||
			(m_entityList[i] && m_entityList[i]->m_markedForDestroy))
		{
			if (m_entityList[i])
				delete m_entityList[i];

			m_entityList.erase(m_entityList.begin() + i, m_entityList.begin() + i);
			i--;
		}
	}
}
