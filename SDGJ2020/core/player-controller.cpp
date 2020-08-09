#include "player-controller.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"
#include "time.h"
#include "CharacterCollision.h"

PlayerController* PlayerController :: g_pPlayerController;
int npcPositionX;
int npcPositionY;
int playerPosX;
int playerPosY;


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
}

void PlayerController::Update()
{
	Entity* entity = (Entity*)m_entity;
	// put movement code here
	//get input
	if (oneButtonMode) {
		if (Metronome::g_pMetronome->Beat) {
			beatCount++;
		}
		if (beatCount > 3) {
				beatCount = 0;
		}
		if (Input::g_pInput->getAnyPress() && beatCount==0 && playerPosY != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
				moveDown(entity);
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 1 && playerPosX != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
				moveLeft(entity);
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 2 && playerPosY != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
				moveUp(entity);
		}
		if (Input::g_pInput->getAnyPress() && beatCount == 3 && playerPosX != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
				moveRight(entity);
		}
		
	}
	else {
		if (Input::g_pInput->getRightKeyPress() && playerPosX != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100 && !CharacterCollision::g_pChracterCollision->testCollision()) {
			moveRight(entity);
		}
		if (Input::g_pInput->getLeftKeyPress() && playerPosX != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100 && !CharacterCollision::g_pChracterCollision->testCollision()) {
			moveLeft(entity);
		}
		if (Input::g_pInput->getUpKeyPress() && playerPosY != 9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100 && !CharacterCollision::g_pChracterCollision->testCollision()) {
			moveUp(entity);
		}
		if (Input::g_pInput->getDownKeyPress() && playerPosY != 0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100 && !CharacterCollision::g_pChracterCollision->testCollision()) {
			moveDown(entity);
		}
	}
	entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f*Time::g_pTime->GetDeltaTime());
	CharacterCollision::g_pChracterCollision->playerPosX = playerPosX;
	CharacterCollision::g_pChracterCollision->playerPosY = playerPosY;

	
	// move player
	
}

void PlayerController::CleanUp()
{

}
