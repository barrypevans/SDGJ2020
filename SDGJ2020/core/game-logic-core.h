#pragma once
#include "ISystem.h"
#include "entity.h"
class GameLogic : ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	Entity* pCharacterEntity;
	static GameLogic* g_pGameLogic;
};