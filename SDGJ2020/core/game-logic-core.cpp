#include "game-logic-core.h"
#include "game.h"
#include "player-controller.h"
#include "animatable.h"
#include "CharacterCollision.h"
#include "Entity_Controller.h"
#include "metronome.h"
#include "camera.h"
#include "../game/player-anim-controller.h"
#include "effects.h"
#include <fstream>
GameLogic* GameLogic::g_pGameLogic;

void GameLogic::Init()
{
	pCharacterEntity = Game::g_pGame->CreateEntity();
	pCharacterEntity->m_position = glm::vec2(0, 0);
	pCharacterEntity->AddComponent<PlayerAnimController>();
	auto charRenderable = pCharacterEntity->AddComponent<Animatable>();
	charRenderable->AddAnimation("idle", new Animation("art/player_idle_02.png", 20));
	charRenderable->AddAnimation("pose_1", new Animation("art/pose_01.png", 1));
	charRenderable->AddAnimation("pose_2", new Animation("art/pose_02.png", 1));
	charRenderable->AddAnimation("pose_3", new Animation("art/pose_03.png", 1));
	charRenderable->AddAnimation("pose_4", new Animation("art/pose_04.png", 1));
	charRenderable->SetActiveAnimation("idle");

	PlayerController* playerController = pCharacterEntity->AddComponent<PlayerController>();
	// make the character's width half of the tile size
	pCharacterEntity->m_scale = glm::vec2(.8f, .8f);
	pCharacterEntity->m_dontDestroyOnReset = true;
	m_maxEnemies = 1000;
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
		if (m_beat % 8 == 0)
		{
			if (m_activeEnemies.size() < m_maxEnemies)
				SpawnEnemy(0);
		}
	}
}

void GameLogic::Reset()
{
	PlayerController* playerController = pCharacterEntity->GetComponent<PlayerController>();
	playerController->playerPosX = 6;
	playerController->playerPosY = 3;
	playerController->targetPos = glm::vec2(0, 0);
	pCharacterEntity->m_position = glm::vec2(0,0);
	playerController->hasInit = true;
	m_score = 0;
	m_activeEnemies.clear();
}

void GameLogic::SpawnEnemy(int enemyType)
{
	Entity* pNPCEntity = Game::g_pGame->CreateEntity();
	auto NPCRenderable = pNPCEntity->AddComponent<Renderable>();
	NPCRenderable->SetTexture("art/Badguy_Flat.png");
	Entity_Controller* entityController = pNPCEntity->AddComponent<Entity_Controller>();
	entityController->setEntityPos(-3, 0);
	pNPCEntity->m_scale *= .5f;
	m_activeEnemies.push_back(pNPCEntity);
	entityController->setType(rand() % 3);
}

static bool IsAdjecent(int pX, int pY, int nX, int nY) {

	return (abs(pX - nX) <= 1) && (abs(pY - nY) <= 1);
}

void GameLogic::DealDamage()
{
	Effects::g_pEffects->GlowTilesAt(CharacterCollision::g_pChracterCollision->playerPosX, CharacterCollision::g_pChracterCollision->playerPosY);

	for (int i = 0; i < m_activeEnemies.size(); ++i)
	{
		Entity* enemy = m_activeEnemies[i];
		Entity_Controller* enemyController = enemy->GetComponent<Entity_Controller>();
		PlayerController* playerController = pCharacterEntity->GetComponent<PlayerController>();

		if (IsAdjecent(enemyController->getEntityPosX(), enemyController->getEntityPosY(),
			playerController->getPlayerPosX(), playerController->getPlayerPosY()))
		{
			// remove enemy from active list
			m_activeEnemies.erase(m_activeEnemies.begin() + i, m_activeEnemies.begin() + 1 + i);
			--i;
			// destroy enemy
			Game::g_pGame->DestroyEntity(enemy);
			m_score += 5000;
		}
	}
}

void GameLogic::CorrectMove()
{
	m_score += kCorrectMoveScore;
	Camera::g_pCamera->DoShake();
	if (m_hypeCount >= m_maxHypeCount)
	{
		TriggerHype();
	}
	else
	{
		m_hypeCount++;
		UI::g_pUI->CorrectMove();
	}
}

void GameLogic::TriggerHype()
{
	pCharacterEntity->GetComponent<PlayerAnimController>()->Pose();
	m_score += kHypeMoveScore;
	Audio::g_pAudio->Play((Audio::GameClip)(rand() % 15 + 3), .1f); // Hype
	m_hypeCount = 0;
	Camera::g_pCamera->DoShake();
	DealDamage();
}


bool GameLogic::IsHypeBarFull()
{
	return (m_hypeCount == m_maxHypeCount);
}

void GameLogic::ClearMoveCount()
{
	m_hypeCount = 0;
	UI::g_pUI->targetHypeBarPercent = 0;
}

void GameLogic::FailedMove()
{
	Audio::g_pAudio->Play((Audio::GameClip)(rand() % 7 + 27), .1f); // Scratch
	ClearMoveCount();
	Camera::g_pCamera->DoShake(.3f);
}

void GameLogic::LoadHighScore()
{

}

void GameLogic::WriteHighScore()
{
	/*printf(GetHighScoreLocation().c_str());
	char scoreString[20];
	sprintf_s(scoreString, "%d", m_score);
	std::ofstream myfile;
	myfile.open(GetHighScoreLocation());
	myfile << scoreString;
	myfile.close();
	m_highScore = m_score;*/
}

std::string GameLogic::GetHighScoreLocation()
{
	char* buf = nullptr;
	size_t sz = 0;
	_dupenv_s(&buf, &sz, "APPDATA");
	return std::string(buf)+"/HYPE/highscore.txt";
}
