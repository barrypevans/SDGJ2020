#pragma once
#include "ISystem.h"
#include "entity.h"
#include <vector>
class Game : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	bool IsRunning();
	void RequestShutDown();
	int entityId;

	Entity* CreateEntity();
	void DestroyEntity(Entity* entity);

	static Game* g_pGame;

private:
	void InitSystems();
	void InitCoreEntities();
	void DestroyMarkedEntities();
	bool m_isRunning;
	std::vector<Entity*> m_entityList;

	Entity* pBerryEntity;
	Entity* pBerryBarryEntity;
	
};

