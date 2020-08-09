#include "Entity_Controller.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"
#include "time.h"
#include "CharacterCollision.h"
//
#include <iostream>
using namespace std;
//
Entity_Controller* Entity_Controller::g_pEntity_Controller;

void Entity_Controller::Init()
{
	Entity* entity = (Entity*)m_entity;
	entity->m_position.y = entity->m_position.y - .1;
	//entity->m_position.x = entity->m_position.x + .5;
	entityPosX = 6;
	entityPosY = 3;
	beatCount = 0;
	targetPos.x = entity->m_position.x;
	targetPos.y = entity->m_position.y;
}
void Entity_Controller::Update()
{
	Entity* entity = (Entity*)m_entity;
	// put movement code here
	//get input

	
	if (Metronome::g_pMetronome->Beat) {
		beatCount++;
		if (beatCount > 3) {
			switch (rand() % 4) {
			case 0:
				if (entityPosX != 9) moveRight(entity); break;
			case 1:
				if (entityPosX != 0) moveLeft(entity); break;
			case 2:
				if (entityPosY != 9) moveUp(entity); break;
			case 3:
				if (entityPosY != 0) moveDown(entity); break;
			}
			beatCount = 0;
		}
	}
	entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
	CharacterCollision::g_pChracterCollision->npcPositionX = entityPosX;
	CharacterCollision::g_pChracterCollision->npcPositionY = entityPosY;

	// move player
}
void Entity_Controller::CleanUp()
{

}