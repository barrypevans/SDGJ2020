#pragma once
#include "component.h"
#include "entity.h"

class PlayerController : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override {};

	int playerPosX;
	int playerPosY;
	bool oneButtonMode;
	int beatCount;
	int npcPositionX;
	int npcPositionY;

	glm::vec2 targetPos = glm::vec2(0,0);


public:
	void moveRight(Entity* entity) {
		targetPos.y = targetPos.y - .25;
		targetPos.x = targetPos.x + .5;
		playerPosX++;
	}
	void moveLeft(Entity* entity) {
		targetPos.y = targetPos.y + .25;
		targetPos.x = targetPos.x - .5;
		playerPosX--;
	}
	void moveUp(Entity* entity) {
		targetPos.y = targetPos.y + .23;
		targetPos.x = targetPos.x + .50;
		playerPosY++;
	}
	void moveDown(Entity* entity) {
		targetPos.y = targetPos.y - .23;
		targetPos.x = targetPos.x - .50;
		playerPosY--;
	}
	int getPlayerPosX() {
		return this->playerPosX;
	}
	int getPlayerPosY() {
		return this->playerPosY;
	}
	static PlayerController* g_pPlayerController;
};