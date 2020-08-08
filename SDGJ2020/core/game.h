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

	Entity* CreateEntity();
	void DestroyEntity(Entity*& entity);

private:
	void InitSystems();
	void InitCoreEntities();

	bool m_isRunning;
	std::vector<Entity*> m_entityList;
};

static Game* g_pGame;