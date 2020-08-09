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
enum Type { King, Knight, Bishop };
void Entity_Controller::Init()
{
	Entity* entity = (Entity*)m_entity;
	if (CharacterCollision::g_pChracterCollision->enemyTypeA != -1) {
		enemyType = CharacterCollision::g_pChracterCollision->enemyTypeA;
		CharacterCollision::g_pChracterCollision->enemyTypeA = -1;
	}
	else if (CharacterCollision::g_pChracterCollision->enemyTypeB != -1) {
		enemyType = CharacterCollision::g_pChracterCollision->enemyTypeB;
		CharacterCollision::g_pChracterCollision->enemyTypeB = -1;
	}
	else if (CharacterCollision::g_pChracterCollision->enemyTypeC != -1) {
		enemyType = CharacterCollision::g_pChracterCollision->enemyTypeC;
		CharacterCollision::g_pChracterCollision->enemyTypeC = -1;
	}
	else {
		enemyType = 1;
	}
	switch (enemyType) {
	case 0:
		entity->m_position.y = entity->m_position.y - .1 + .69;
		entity->m_position.x = entity->m_position.x + 1.5;
		break;
	case 1:
		entity->m_position.y = entity->m_position.y - .1 + .94;
		entity->m_position.x = entity->m_position.x + 1;
		break;
	case 2:
		entity->m_position.y = entity->m_position.y - .1 + .44;
		entity->m_position.x = entity->m_position.x + 2;
		break;
	}
	entityPosX = 6;
	entityPosY = 3;
	beatCount = 0;
	targetPos.x = entity->m_position.x;
	targetPos.y = entity->m_position.y;
	destroyedA = false;
	destroyedB = false;
	destroyedC = false;
	knightQueue = false;
	knightQueueDirection = false;
	knightQueueEnd = 0;
	
	
}
void Entity_Controller::Update()
{
	if (CharacterCollision::g_pChracterCollision->npcDestroyed && (enemyType==0)) {
		if (!destroyedA) {
			Entity* entity = (Entity*)m_entity;
			entity->m_position.x = 10;
			entity->m_position.y = 10;
			destroyedA = true;
		}
	}
	else if(CharacterCollision::g_pChracterCollision->npcBDestroyed && (enemyType == 1)) {
		if (!destroyedB) {
			Entity* entity = (Entity*)m_entity;
			entity->m_position.x = 10;
			entity->m_position.y = 10;
			destroyedB= true;
		}
	}
	else if (CharacterCollision::g_pChracterCollision->npcCDestroyed && (enemyType == 2)) {
		if (!destroyedC) {
			Entity* entity = (Entity*)m_entity;
			entity->m_position.x = 10;
			entity->m_position.y = 10;
			destroyedC = true;
		}
	}
	else {
		Entity* entity = (Entity*)m_entity;
		// put movement code here
		//get input
		

		if (Metronome::g_pMetronome->Beat) {
			beatCount++;
			if (enemyType == King) {
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
			else if (enemyType == Knight) {
				if (knightQueue) {
					if (knightQueueDirection) {
						switch (rand() % 2) {
						case 0:
							if (entityPosY != 9) moveUp(entity); break;
						case 1:
							if (entityPosY != 0) moveDown(entity); break;
						}
						knightQueueEnd++;
					}
					else {
						switch (rand() % 2) {
						case 0:
							if (entityPosX != 9) moveRight(entity); break;
						case 1:
							if (entityPosX != 0) moveLeft(entity); break;
						}
						knightQueueEnd++;
					}
					if (knightQueueEnd > 1) {
						knightQueue = false;
						knightQueueEnd = 0;
					}
				}
				else if (beatCount > 1) {
					switch (rand() % 4) {
						case 0:
							if (entityPosX != 9) moveRight(entity); knightQueueDirection = false; break;
						case 1:
							if (entityPosX != 0) moveLeft(entity); knightQueueDirection = false; break;
						case 2:
							if (entityPosY != 9) moveUp(entity); knightQueueDirection = true; break;
						case 3:
							if (entityPosY != 0) moveDown(entity); knightQueueDirection = true; break;
						}
					beatCount = 0;
				}
			}
			else if (enemyType == Bishop) {
				if (beatCount > 2) {
					switch (rand() % 4) {
					case 0:
						if (entityPosX != 9 && entityPosY !=9) moveRight(entity); moveUp(entity); break;
					case 1:
						if (entityPosX != 0 && entityPosY!=0) moveLeft(entity); moveDown(entity); break;
					case 2:
						if (entityPosY != 9 && entityPosX !=0) moveLeft(entity); moveUp(entity); break;
					case 3:
						if (entityPosY != 0 && entityPosX!=9) moveRight(entity); moveDown(entity); break;
					}
					beatCount = 0;
				}
			}
		}
		switch (enemyType) {
		case 0:
			entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
			CharacterCollision::g_pChracterCollision->npcPositionX = entityPosX;
			CharacterCollision::g_pChracterCollision->npcPositionY = entityPosY;
			break;
		case 1:
			entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
			CharacterCollision::g_pChracterCollision->npcPosBX = entityPosX;
			CharacterCollision::g_pChracterCollision->npcPosBY = entityPosY;
			break;
		case 2:
			entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
			CharacterCollision::g_pChracterCollision->npcPosBX = entityPosX;
			CharacterCollision::g_pChracterCollision->npcPosBY = entityPosY;
			break;
		}
		
	}
	// move player
	
}
void Entity_Controller::CleanUp()
{

}