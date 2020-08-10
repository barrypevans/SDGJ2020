#include "player-controller.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"
#include "time.h"
#include "CharacterCollision.h"
#include "game-logic-core.h"

PlayerController* PlayerController :: g_pPlayerController;
int npcPositionX;
int npcPositionY;
int playerPosX;
int playerPosY;
#include "ui.h"
#include "camera.h"


void PlayerController::Init()
{
	Entity* entity = (Entity*)m_entity;
	entity->m_position.y = entity->m_position.y - .1;
	//entity->m_position.x = entity->m_position.x + .5;
	playerPosX = 6;
	playerPosY = 3;
	beatCount = 0;
	targetPos.x = entity->m_position.x;
	targetPos.y = entity->m_position.y;
	oneButtonMode = false;
	hasInit = false;
}

void PlayerController::Update()
{
	Entity* entity = (Entity*)m_entity;
	bool correctMovement = true;
	// put movement code here
	//get input
	if (hasInit) {
		entity->m_position.y = entity->m_position.y - .1;
		playerPosX = 6;
		playerPosY = 3;
		targetPos.x = entity->m_position.x;
		targetPos.y = entity->m_position.y;
		hasInit = false;
	}

	if (oneButtonMode) {
		if (Metronome::g_pMetronome->Beat) {
			beatCount++;
		}
		if (beatCount > 3) {
				beatCount = 0;
		}
		if (Input::g_pInput->getAnyPress() && beatCount==0 && playerPosY != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold) {
				moveDown(entity);
				CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
				CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
				UI::g_pUI->CorrectMove();
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 1 && playerPosX != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold) {
				moveLeft(entity);
				CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
				CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
				UI::g_pUI->CorrectMove();
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 2 && playerPosY != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold) {
				moveUp(entity);
				CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
				CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
				UI::g_pUI->CorrectMove();
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 3 && playerPosX != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold) {
				moveRight(entity);
				CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
				CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
				UI::g_pUI->CorrectMove();
		}
		
	}
	else {

			if (Input::g_pInput->getRightKeyPress()) {
				if (playerPosX != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold)
				{
					//CharacterCollision::g_pChracterCollision->testCollision();
					moveRight(entity);
					CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
					CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
					GameLogic::g_pGameLogic->CorrectMove();
				}
				else
				{
					GameLogic::g_pGameLogic->FailedMove();
				}
			}
			if (Input::g_pInput->getLeftKeyPress()) {
				if (playerPosX != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold)
				{
					//CharacterCollision::g_pChracterCollision->testCollision();
					moveLeft(entity);
					CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
					CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
					GameLogic::g_pGameLogic->CorrectMove();
				}
				else
				{
					GameLogic::g_pGameLogic->FailedMove();
				}
			}
			if (Input::g_pInput->getUpKeyPress()) {
				if (playerPosY != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold)
				{
					//CharacterCollision::g_pChracterCollision->testCollision();
					moveUp(entity);
					CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
					CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
					GameLogic::g_pGameLogic->CorrectMove();
				}
				else
				{
					GameLogic::g_pGameLogic->FailedMove();
				}
			}
			if (Input::g_pInput->getDownKeyPress()) {
				if (playerPosY != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold)
				{
					//CharacterCollision::g_pChracterCollision->testCollision();
					moveDown(entity);
					CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
					CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
					GameLogic::g_pGameLogic->CorrectMove();
				}
				else
				{
					GameLogic::g_pGameLogic->FailedMove();
				}
			}

			entity->GetComponent<Renderable>()->m_layerOrder = playerPosX - playerPosY + 16;
	}
		entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
		CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
		CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;
		CharacterCollision::g_pChracterCollision->calculateNext();
		//printf("\n\nEnemy at position X: %d Y: %d\n\n",  playerPosX, playerPosY);


		// move player
	
	
}

