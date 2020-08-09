#include "game-logic-core.h"
#include "game.h"
#include "player-controller.h"
#include "animatable.h"

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
}

void GameLogic::CleanUp()
{

}
