#pragma once
#include <vector>
#include "entity.h"

class Level
{
public:
	template<class T = Entity>
	T CreateEntity()
	{
		Entity* entity = new T();
		m_entityList.push_back(entity);
	}

	template<class T = Entity>
	void DestroyEntity(T*& entity)
	{
		// remove entity from level entities.
		for (int i = 0; i < m_entityList.size(); ++i)
		{
			if (m_entityList[i] == entity)
			{
				m_entityList.erase(i);
				break;
			}
		}

		delete entity;
		entity = nullptr;
	}

private:
	std::vector<Entity*> m_entityList;
};