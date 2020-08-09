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
void CharacterCollision::Update() {

}
void CharacterCollision::CleanUp() {

}