#include "Input.h"
#include "CharacterCollision.h"
#include "entity.h"
#include "metronome.h"
#include <iostream>
#include "time.h"
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
		printf("Error: Array Capacity Reached");
	}
	else {
		arr[arrSize].x = x;
		arr[arrSize].y = y;
		arr[arrSize].key = key;
		arrSize++;
		printf("\nAdded to Array index %d, key: %d, X: %d Y: %d\n", arrSize, key, x, y);
	}
}
bool CharacterCollision::setNPCCoords(int key, int x, int y) {
	bool notFound = true;
	int index = 0;
	for (int index = 0; index < arrSize; index++) {
		printf("\nchecking for Array index: %d key: arrKey: %d, %d, X: %d Y: %d\n", index, arr[index].key, key, x, y);
		if (arr[index].key == key) {
			notFound = false;
			break;
		}
	}
	if (notFound) {
		printf("Error: Entity Not Found in Array");
	}
	else {
		arr[index].x = x;
		arr[index].y = y;
	}
	return true;
}
bool CharacterCollision::compareStruct(posCoords a, posCoords b) {
	bool equal = false;
	printf("\nKeyA: %d, Key2: %d, Ax: %d, BX: %d, AY: %d, BY: %d\n", a.key, b.key, a.x, b.x, a.y, b.y);
	if (a.x == b.x && a.y == b.y) {
		equal = true;
	}
	return equal;
}
bool CharacterCollision::calculateNext() {
	bool noCollision = true;
	/*if (arrSize == 1) {
		return true;
	}
	if (arrSize == 2 && compareStruct(arr[0], arr[1])) {
		return true;
	}
	for (int index = 0; index < arrSize; index++) {
		for (int index2 = 0; index2 < arrSize; index2++) {
			if (index!=index2 && compareStruct(arr[index], arr[index2])) {
				noCollision = false;
				printf("Collsion!!");
				break;
			}
		}
	}*/
	return noCollision;
}


void CharacterCollision::Update() {

}
void CharacterCollision::CleanUp() {

}