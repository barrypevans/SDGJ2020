#pragma once
#include "component.h"
#include "entity.h"
#include "ISystem.h"
#include <glm/glm.hpp>
#include "game.h"
#include "ui.h"
#include "game-logic-core.h"
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

	struct posCoords {
		int x;
		int y;
		int key;
	};
	struct posCoords arr[10];
	int arrSize = 0;

	int npcPosCX;
	int npcPosCY;

	bool npcDestroyed = false;
	bool npcBDestroyed = false;
	bool npcCDestroyed = false;

	int enemyTypeA;
	int enemyTypeB;
	int enemyTypeC;

	// Put your implementations in the cpp file!
	bool isAdjecent(int pX, int pY, int nX, int nY);

	bool testCollision() {
		bool collide = false;
		if ((npcPositionX == playerPosX) && (npcPositionY == playerPosY)) {
			collide = true;
		}
		if (GameLogic::g_pGameLogic->IsHypeBarFull() && isAdjecent(playerPosX,playerPosY,npcPositionX,npcPositionY)) {
			this->npcDestroyed = true;
		}
		if (GameLogic::g_pGameLogic->IsHypeBarFull() && isAdjecent(playerPosX, playerPosY, npcPosBX, npcPosBY)) {
			this->npcBDestroyed = true;
		}
		if (GameLogic::g_pGameLogic->IsHypeBarFull() && isAdjecent(playerPosX, playerPosY, npcPosCX, npcPosCY)) {
			this->npcCDestroyed = true;
		}

		return collide;
	}

	void addNPC(int x, int y, int key);
	bool setNPCCoords(int key, int x, int y);
	bool calculateNext();
	bool compareStruct(posCoords a);
	void flush();
	

	static CharacterCollision* g_pChracterCollision;

private:

	Game* m_pGame;
};