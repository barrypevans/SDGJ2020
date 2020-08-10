#include "Entity_Controller.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"
#include "time.h"
#include "CharacterCollision.h"

Entity_Controller* Entity_Controller::g_pEntity_Controller;
enum Type { King, Knight, Bishop };
void Entity_Controller::Init()
{
	Entity* entity = (Entity*)m_entity;
	key = entity->UID;

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
	CharacterCollision::g_pChracterCollision->addNPC(entityPosX, entityPosY, key);
	
	
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
		entity = (Entity*)m_entity;
		// put movement code here
		//get input
		
		//printf("\n\nType %d\n\n", enemyType);
		if (Metronome::g_pMetronome->Beat) {
			beatCount++;
			if (enemyType == King) {
				if (beatCount > 3) {
					
					switch (rand() % 4) {
					case 0:
						if (entityPosX != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveRight(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY); }
						break;
					case 1:
						if (entityPosX != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveLeft(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY); }
						break;
					case 2:
						if (entityPosY != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY + 1)) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveUp(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY-1); }
						break;
					case 3:
						if (entityPosY != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY - 1)) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveDown(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY+1); }
						break;
					}
					beatCount = 0;
				}
			}
			else if (enemyType == Knight) {
				if (knightQueue) {
					if (knightQueueDirection) {
						//printf("Setting Key %d", key);
						switch (rand() % 2) {
						case 0:
							if (entityPosY != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY + 1)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveUp(entity); }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY - 1); }
							break;
						case 1:
							if (entityPosY != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY - 1)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveDown(entity); }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY + 1); }
							break;
						}
						knightQueueEnd++;
					}
					else {
						//printf("Setting Key %d", key);
						switch (rand() % 2) {
						case 0:
							if (entityPosX != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveRight(entity); }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY); }
							break;
						case 1:
							if (entityPosX != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveLeft(entity); }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX+1, entityPosY); }
							break;
						}
						knightQueueEnd++;
					}
					if (knightQueueEnd > 1) {
						knightQueue = false;
						knightQueueEnd = 0;
					}
				}
				else if (beatCount > 1) {
					//printf("Setting Key %d", key);
					switch (rand() % 4) {
						case 0:
							if (entityPosX != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveRight(entity); knightQueueDirection = false; }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX-1, entityPosY); }
							break;
						case 1:
							if (entityPosX != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveLeft(entity); knightQueueDirection = false; }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX +1, entityPosY); }
							break;
						case 2:
							if (entityPosY != 9 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY + 1)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveUp(entity); knightQueueDirection = true; }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY - 1); }
							break;
						case 3:
							if (entityPosY != 0 && (CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY - 1)) && (CharacterCollision::g_pChracterCollision->calculateNext())) { moveDown(entity); knightQueueDirection = true; }
							else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY + 1); }
							break;
						}
					beatCount = 0;
				}
			}
			else if (enemyType == Bishop) {
				if (beatCount > 2) {
					//printf("Setting Key %d", key);
					switch (rand() % 4) {
					case 0:
						if (entityPosX != 9 && entityPosY != 9 && CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY + 1) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveRight(entity); moveUp(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX -1, entityPosY - 1); }
						break;
					case 1:
						if (entityPosX != 0 && entityPosY != 0 && CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY - 1) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveLeft(entity); moveDown(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX+1, entityPosY + 1); }
						break;
					case 2:
						if (entityPosY != 9 && entityPosX != 0 && CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX - 1, entityPosY + 1) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveLeft(entity); moveUp(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX+1, entityPosY - 1); }
						break;
					case 3:
						if (entityPosY != 0 && entityPosX != 9 && CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX + 1, entityPosY - 1) && CharacterCollision::g_pChracterCollision->calculateNext()) { moveRight(entity); moveDown(entity); }
						else { CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX-1, entityPosY + 1); }
						break;
					}
					beatCount = 0;
				}
			}
		}
		
			entity->m_position = glm::mix(entity->m_position, targetPos, 10.0f * Time::g_pTime->GetDeltaTime());
			CharacterCollision::g_pChracterCollision->setNPCCoords(key, entityPosX, entityPosY);
			entity->GetComponent<Renderable>()->m_layerOrder = entityPosX - entityPosY + 16;
			//printf("\n\nEnemy %d at position X: %d Y: %d\n\n", key, entityPosX, entityPosY);
		
		
	}
	// move player
	
}

void Entity_Controller::CleanUp()
{

}