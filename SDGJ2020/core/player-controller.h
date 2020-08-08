#pragma once
#include "component.h"
#include "entity.h"

class PlayerController : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;

	int playerPosX;
	int playerPosY;
	bool oneButtonMode;

public:
	void moveRight(Entity* entity) {
		entity->m_position.y = entity->m_position.y - .25;
		entity->m_position.x = entity->m_position.x + .5;
		playerPosX++;
	}
	void moveLeft(Entity* entity) {
		entity->m_position.y = entity->m_position.y + .25;
		entity->m_position.x = entity->m_position.x - .5;
		playerPosX--;
	}
	void moveUp(Entity* entity) {
		entity->m_position.y = entity->m_position.y + .23;
		entity->m_position.x = entity->m_position.x + .50;
		playerPosY++;
	}
	void moveDown(Entity* entity) {
		entity->m_position.y = entity->m_position.y - .23;
		entity->m_position.x = entity->m_position.x - .50;
		playerPosY--;
	}
};