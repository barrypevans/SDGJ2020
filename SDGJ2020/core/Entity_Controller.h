#pragma once
#include "component.h"
#include "entity.h"
class Entity_Controller : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;

	int entityPosX;
	int entityPosY;
	int beatCount;
	

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
		targetPos.y = targetPos.y + .23;
		targetPos.x = targetPos.x + .50;
		entityPosY++;
	}
	void moveDown(Entity* entity) {
		targetPos.y = targetPos.y - .23;
		targetPos.x = targetPos.x - .50;
		entityPosY--;
	}
	int getEntityPosX() {
		return this->entityPosX;
	}
	int getEntityPosY() {
		return this->entityPosY;
	}
	static Entity_Controller* g_pEntity_Controller;
};

