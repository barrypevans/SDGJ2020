#include "player-controller.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"


void PlayerController::Init()
{
	Entity* entity = (Entity*)m_entity;
	entity->m_position.y = entity->m_position.y - .1;
	//entity->m_position.x = entity->m_position.x + .5;
	playerPosX = 6;
	playerPosY = 3;
}

void PlayerController::Update()
{
	Entity* entity = (Entity*)m_entity;
	// put movement code here
	//get input
	if (Input::g_pInput->getRightKeyPress() && playerPosX!=9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
		entity->m_position.y = entity->m_position.y - .25;
		entity->m_position.x = entity->m_position.x + .5;
		playerPosX++;
	}
	if (Input::g_pInput->getLeftKeyPress() && playerPosX!=0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
		entity->m_position.y = entity->m_position.y + .25;
		entity->m_position.x = entity->m_position.x - .5;
		playerPosX--;
	}
	if (Input::g_pInput->getUpKeyPress() && playerPosY!=9 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
		entity->m_position.y = entity->m_position.y + .23;
		entity->m_position.x = entity->m_position.x + .50;
		playerPosY++;
	}
	if (Input::g_pInput->getDownKeyPress() && playerPosY!=0 && (float)Metronome::g_pMetronome->ActiveBeatOffset() < 100) {
		entity->m_position.y = entity->m_position.y - .23;
		entity->m_position.x = entity->m_position.x - .50;
		playerPosY--;
	}
	
	
	// move player
	
}

void PlayerController::CleanUp()
{

}
