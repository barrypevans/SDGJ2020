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
	bool m_isPaused;
	Entity* CreateEntity();
	void DestroyEntity(Entity* entity);
	void StartGame();
	void ResetGame();

	template<class T>
	void ResetSystem(T* system)
	{
		if (system)
		{
			system->CleanUp();
			delete system;
		}
		system = new T();
		system->Init();
	}

	void ResetSystems();
	static Game* g_pGame;

private:

	void ResetGame_Internal();
	void InitSystems();
	void InitCoreEntities();
	void DestroyMarkedEntities();
	bool m_isRunning;
	std::vector<Entity*> m_entityList;
	bool m_doReset;
	Entity* pBerryEntity;
	Entity* pBerryBarryEntity;

	friend class Renderer;
};

