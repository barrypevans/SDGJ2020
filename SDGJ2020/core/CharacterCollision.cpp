#include "Input.h"
#include "CharacterCollision.h"
#include "entity.h"
#include "metronome.h"
#include <iostream>
#include "time.h"
CharacterCollision* CharacterCollision::g_pChracterCollision;

CharacterCollision::CharacterCollision() {
	playerPosX=0;
	playerPosY=0;
	npcPositionX=0;
	npcPositionY=0;
	Entity* pNPCEntity = NULL;
	Entity* pCharacterEntity = NULL;
}
bool isAdjecent(int pX, int pY, int nX, int nY) {
	bool adjacent = false;
	if ((pX + 1 == nX) && (pY == nY)) {
		adjacent = true;
	}
	if ((pX == nX) && (pY + 1 == nY)) {
		adjacent = true;
	}
	if ((pX - 1 == nX) && (pY == nY)) {
		adjacent = true;
	}
	if ((pX == nX) && (pY - 1 == nY)) {
		adjacent = true;
	}
	return adjacent;
}

void CharacterCollision::Update() {

}
void CharacterCollision::CleanUp() {

}