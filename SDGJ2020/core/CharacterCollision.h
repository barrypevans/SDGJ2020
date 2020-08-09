#pragma once
#include "component.h"
#include "entity.h"
#include "ISystem.h"
#include <glm/glm.hpp>
#include "game.h"
#include "ui.h"

class CharacterCollision : public ISystem
{
public:


	CharacterCollision(Game* pGame) : m_pGame(pGame) {}

	// Inherited via ISystem
	virtual void Init() override {};
	virtual void CleanUp() override;
	CharacterCollision();
	virtual void Update() override;
	
	int playerPosX;
	int playerPosY;
	int npcPositionX;
	int npcPositionY;

	int npcPosBX;
	int npcPosBY;

	int npcPosCX;
	int npcPosCY;

	bool npcDestroyed = false;
	bool npcBDestroyed = false;
	bool npcCDestroyed = false;

	int enemyTypeA;
	int enemyTypeB;
	int enemyTypeC;

	bool isAdjecent(int pX, int pY, int nX, int nY) {
		bool adjacent = false;
		if ((pX + 1 == nX) && (pY == nY)) {
			adjacent = true;
		}
		if ((pX == nX) && (pY+1 == nY)) {
			adjacent = true;
		}
		if ((pX - 1 == nX) && (pY == nY)) {
			adjacent = true;
		}
		if ((pX == nX) && (pY-1 == nY)) {
			adjacent = true;
		}
		return adjacent;
	}

	bool testCollision() {
		bool collide = false;
		if ((npcPositionX == playerPosX) && (npcPositionY == playerPosY)) {
			collide = true;
		}
		if (UI::g_pUI->IsHypeBarFull() && isAdjecent(playerPosX,playerPosY,npcPositionX,npcPositionY)) {
			this->npcDestroyed = true;
		}
		if (UI::g_pUI->IsHypeBarFull() && isAdjecent(playerPosX, playerPosY, npcPosBX, npcPosBY)) {
			this->npcBDestroyed = true;
		}
		if (UI::g_pUI->IsHypeBarFull() && isAdjecent(playerPosX, playerPosY, npcPosCX, npcPosCY)) {
			this->npcCDestroyed = true;
		}

		return collide;
	}

	static CharacterCollision* g_pChracterCollision;

private:

	Game* m_pGame;
};