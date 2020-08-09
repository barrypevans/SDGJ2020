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
#include "ui.h"
#include "player-controller.h"
#include "animatable.h"
#include "Entity_Controller.h"
#include "beatCounter.h"

Game* Game::g_pGame;

void Game::Init()
{
	g_pGame = this;
	m_isRunning = true;
	InitSystems();
	printf("Game Initialized!\n");

	Audio::g_pAudio->Play(Audio::GameClip::kMetReference, .1f, 10);
	Metronome::g_pMetronome->Start(120);
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
	UI::g_pUI->CleanUp();

	delete Camera::g_pCamera;
	delete  Audio::g_pAudio;
	delete  Window::g_pWindow;
	delete  AssetManager::g_pAssetManager;
}

void Game::Update()
{
	Time::g_pTime->Update();
	UI::g_pUI->Update();

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
	Input::g_pInput = new Input();
	UI::g_pUI = new UI();


	Window::g_pWindow->Init();
	AssetManager::g_pAssetManager->Init();
	Audio::g_pAudio->Init();
	Renderer::g_pRenderer->Init();
	Camera::g_pCamera->Init();
	Metronome::g_pMetronome->Init();
	Time::g_pTime->Init();
	Input::g_pInput->Init();
	UI::g_pUI->Init();
}

void Game::InitCoreEntities()
{
	Entity* pDanceFloorEntity = CreateEntity();
	auto danceRenderable = pDanceFloorEntity->AddComponent<Renderable>();
	danceRenderable->SetTexture("art/dance-floor.png");
	pDanceFloorEntity->m_scale *= 10;

	pCharacterEntity = CreateEntity();
	auto charRenderable = pCharacterEntity->AddComponent<Animatable>();
	charRenderable->AddAnimation("idle", new Animation("art/player_idle.png", 20));
	charRenderable->SetActiveAnimation("idle");
	PlayerController* playerController = pCharacterEntity->AddComponent<PlayerController>();
	// make the character's width half of the tile size
	pCharacterEntity->m_scale *= .5f;

	Entity* pNPCEntity = CreateEntity();
	auto NPCRenderable = pNPCEntity->AddComponent<Renderable>();
	NPCRenderable->SetTexture("art/sprite_01.png");
	Entity_Controller* entityController = pNPCEntity->AddComponent<Entity_Controller>();
	pNPCEntity->m_position = glm::vec2(2, 1);
	pNPCEntity->m_scale *= .5f;

	Entity* pBeatCounter_B = CreateEntity();
	auto beatRenderable_B = pBeatCounter_B->AddComponent<Renderable>();
	beatRenderable_B->isUI=true;
	beatRenderable_B->SetTexture("art/BeatCounet_B.png");
	pBeatCounter_B->m_scale *= 3;
	pBeatCounter_B->m_position = glm::vec2(5, -3);

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
	beatRenderable->isUI=true;
	beatRenderable->SetTexture("art/BeatCounter_A.png");
	beatCounter* beatCountController = pBeatCounter_A->AddComponent<beatCounter>();
	pBeatCounter_A->m_scale *= .75;
	pBeatCounter_A->m_position = glm::vec2(3.93, -2.97);

	pBerryEntity = CreateEntity();
	auto berryRenderable = pBerryEntity->AddComponent<Renderable>();
	berryRenderable->isUI = true;
	berryRenderable->SetTexture("art/berry.png");
	pBerryEntity->m_position = glm::vec2(2, 1);
	pBerryEntity->m_scale *= 2;

}
