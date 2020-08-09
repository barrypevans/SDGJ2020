#include "game-logic-core.h"
#include "game.h"
#include "player-controller.h"
#include "animatable.h"
#include "CharacterCollision.h"
#include "Entity_Controller.h"
#include "metronome.h"
#include "camera.h"
GameLogic* GameLogic::g_pGameLogic;

void GameLogic::Init()
{
	pCharacterEntity = Game::g_pGame->CreateEntity();
	pCharacterEntity->m_position = glm::vec2(0, 0);
	auto charRenderable = pCharacterEntity->AddComponent<Animatable>();
	charRenderable->AddAnimation("idle", new Animation("art/player_idle.png", 20));
	charRenderable->SetActiveAnimation("idle");

	PlayerController* playerController = pCharacterEntity->AddComponent<PlayerController>();
	// make the character's width half of the tile size
	pCharacterEntity->m_scale = glm::vec2(.5f, .5f);

	m_maxEnemies = 4;
	int m_beat = 0;
	m_score = 0;
}

void GameLogic::CleanUp()
{

}

void GameLogic::Update()
{
	
	if (Metronome::g_pMetronome->Beat)
	{
		m_beat++;

		// spawn enemy every 4 bars
		if (m_beat > 15)
		{
			if (m_activeEnemies.size() < m_maxEnemies)
				SpawnEnemy(0);
			m_beat = 0;
		}
	}
}

void GameLogic::SpawnEnemy(int enemyType)
{
	CharacterCollision::g_pChracterCollision->enemyTypeA = enemyType;
	Entity* pNPCEntity = Game::g_pGame->CreateEntity();
	auto NPCRenderable = pNPCEntity->AddComponent<Renderable>();
	NPCRenderable->SetTexture("art/Badguy_Flat.png");
	Entity_Controller* entityController = pNPCEntity->AddComponent<Entity_Controller>();
	pNPCEntity->m_position = glm::vec2(2, 1);
	pNPCEntity->m_scale *= .5f;
	m_activeEnemies.push_back(pNPCEntity);
}

void GameLogic::TriggerHype()
{
	UI::g_pUI->CorrectMove();
	Camera::g_pCamera->DoShake();
}
