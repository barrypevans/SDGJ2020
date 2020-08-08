#include "player-controller.h"
#include "Input.h"
#include "entity.h"

//VVVThis was debug code. Remove 
#include <iostream>
using namespace std;
//^^^^^^^ Remove

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
	if (Input::g_pInput->getRightKeyPress() && playerPosX!=9) {
		entity->m_position.y = entity->m_position.y - .25;
		entity->m_position.x = entity->m_position.x + .5;
		coordX[0][0] = entity->m_position.x;
		double a = coordX[0][0];
		cout << a;
		playerPosX++;
	}
	if (Input::g_pInput->getLeftKeyPress() && playerPosX!=0) {
		entity->m_position.y = entity->m_position.y + .25;
		entity->m_position.x = entity->m_position.x - .5;
		playerPosX--;
	}
	if (Input::g_pInput->getUpKeyPress() && playerPosY!=9) {
		entity->m_position.y = entity->m_position.y + .23;
		entity->m_position.x = entity->m_position.x + .50;
		playerPosY++;
	}
	if (Input::g_pInput->getDownKeyPress() && playerPosY!=0) {
		entity->m_position.y = entity->m_position.y - .23;
		entity->m_position.x = entity->m_position.x - .50;
		playerPosY--;
	}
	
	
	// move player
	
}

void PlayerController::CleanUp()
{

}
