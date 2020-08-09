#pragma once
#include "component.h"
#include "entity.h"
#include "ISystem.h"
#include <glm/glm.hpp>
#include "game.h"

class CharacterCollision : public ISystem
{
public:

	CharacterCollision();

	CharacterCollision(Game* pGame) : m_pGame(pGame) {}

	// Inherited via ISystem
	virtual void Init() override {};
	virtual void CleanUp() override;
	virtual void Update() override;
	
	int playerPosX;
	int playerPosY;
	int npcPositionX;
	int npcPositionY;

	bool testCollision() {
		bool collide = false;
		if ((npcPositionX == playerPosX) && (npcPositionY == playerPosY)) {
			collide = true;
		}
		return collide;
	}

	static CharacterCollision* g_pChracterCollision;

private:

	Game* m_pGame;
};