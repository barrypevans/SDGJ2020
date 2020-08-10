#include "Input.h"
#include "CharacterCollision.h"
#include "entity.h"
#include "metronome.h"
#include <iostream>
#include "time.h"
#include "game.h"

CharacterCollision* CharacterCollision::g_pChracterCollision;

struct posCoords {
	int x;
	int y;
	int key;
};


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
void CharacterCollision::addNPC(int x, int y, int key) {
	if (arrSize > 9) {
		//printf("Error: Array Capacity Reached");
	}
	else {
		arr[arrSize].x = x;
		arr[arrSize].y = y;
		arr[arrSize].key = key;
		arrSize++;
		//printf("\nAdded to Array index %d, key: %d, X: %d Y: %d\n", arrSize, key, x, y);
	}
}
bool CharacterCollision::setNPCCoords(int key, int x, int y) {
	bool notFound = true;
	int index = 0;
	for (int index = 0; index < arrSize; index++) {
		if (arr[index].key == key) {
			notFound = false;
			break;
		}
	}
	if (notFound) {
		//printf("Error: Entity Not Found in Array");
	}
	else {
		arr[index].x = x;
		arr[index].y = y;
	}
	return true;
}
bool CharacterCollision::compareStruct(posCoords a) {
	bool equal = false;
	//printf("\nKeyA: %d, Key2: %d, Ax: %d, BX: %d, AY: %d, BY: %d\n", a.key, b.key, a.x, b.x, a.y, b.y);

	if (a.x == playerPosX && a.y == playerPosY) {
		if (a.x != 6 && a.y != 4) {
			equal = true;
		}
	}
	return equal;
}
void CharacterCollision::flush() {
	for (int index = 0; index < arrSize; index++) {
		arr[index].x = 0;
		arr[index].y = 0;
		arr[index].key = 0;
	}
	arrSize = 0;
}
bool CharacterCollision::calculateNext() {
	bool noCollision = true;
	for (int index = 0; index < arrSize; index++) {
		//printf("\n\nEnemy %d at position X: %d Y: %d\n\n", arr[index].key, arr[index].x, arr[index].y);
		if (compareStruct(arr[index])) {
			noCollision = false;
			Game::g_pGame->ResetGame();
			Audio::g_pAudio->Play((Audio::GameClip)(rand()%5 +19), .1f); // Lose
			//Audio::g_pAudio->Play((Audio::GameClip)(rand() % 7 + 30), .1f); // Scratch
			printf("\n\n\nDEATH!!!\n\n\n");
			printf("\n\n\nDEATH!!!\n\n\n");
			printf("\n\n\nDEATH!!!\n\n\n");
			break;
		}
		
	}
	return noCollision;
}


void CharacterCollision::Update() {

}
void CharacterCollision::Reset()
{
	playerPosX = 0;
	playerPosY = 0;
	npcPositionX = 0;
	npcPositionY = 0;
	flush();
}
void CharacterCollision::CleanUp() {

}