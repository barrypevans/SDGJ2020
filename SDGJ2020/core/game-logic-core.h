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

	void SpawnEnemy(int enemyType);
	void DealDamage();
	void CorrectMove();
	void TriggerHype();
	bool IsHypeBarFull();
	void ClearMoveCount();
	void FailedMove();
	Entity* pCharacterEntity;

	std::vector <Entity*> m_activeEnemies;
	int m_maxEnemies;
	int m_beat;
	unsigned int m_score;

	int m_hypeCount;
	int m_maxHypeCount = 7;

	static GameLogic* g_pGameLogic;
};