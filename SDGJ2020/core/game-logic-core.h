#pragma once
#include "ISystem.h"
#include "entity.h"
#include <vector>
class GameLogic : ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	virtual void SpawnEnemy(int enemyType);

	virtual void TriggerHype();

	Entity* pCharacterEntity;

	std::vector <Entity*> m_activeEnemies;
	int m_maxEnemies;
	int m_beat;
	unsigned int m_score;
	static GameLogic* g_pGameLogic;
};