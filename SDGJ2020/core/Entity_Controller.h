#pragma once
#include "component.h"
#include "entity.h"
class Entity_Controller : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;

	Entity* entity;

	int entityPosX;
	int entityPosY;
	int beatCount;
	bool destroyedA;
	bool destroyedB;
	bool destroyedC;
	int enemyType;
	bool knightQueue;
	bool knightQueueDirection;
	int knightQueueEnd;
	int key;
	

	glm::vec2 targetPos = glm::vec2(0, 0);

public:
	void moveRight(Entity* entity) {
		targetPos.y = targetPos.y - .25;
		targetPos.x = targetPos.x + .5;
		entityPosX++;
	}
	void moveLeft(Entity* entity) {
		targetPos.y = targetPos.y + .25;
		targetPos.x = targetPos.x - .5;
		entityPosX--;
	}
	void moveUp(Entity* entity) {
		targetPos.y = targetPos.y + .25;
		targetPos.x = targetPos.x + .50;
		entityPosY++;
	}
	void moveDown(Entity* entity) {
		targetPos.y = targetPos.y - .25;
		targetPos.x = targetPos.x - .50;
		entityPosY--;
	}
	int getEntityPosX() {
		return entityPosX;
	}
	int getEntityPosY() {
		return entityPosY;
	}
	void setType(int type) {
		this->enemyType=type;
	}
	void setEntityPos(int posX, int posY) {
		((Entity*)m_entity)->m_position.x = (posX + posY) / 2;
		((Entity*)m_entity)->m_position.y = (posY / 2) - (posX / 2);
	};
	void setEntityPosX(int posX);
	static Entity_Controller* g_pEntity_Controller;
};

