#pragma once
#include <vector>
#include "component.h"
class Entity
{
public:
	Entity() {}

	template<class T>
	T* AddComponent()
	{
		T* comp = new T();
		m_components.push_back(comp);
		dynamic_cast<Component*>(comp)->Init();
		return comp;
	}

	template<class T>
	T* GetComponent()
	{
		for (int i = 0; i < m_components.size(); ++i)
			if (typeid(m_components[i]) == typeid(T*))
				return m_components[i];
		return nullptr;
	}

	template<class T>
	void RemoveComponent(Component* comp)
	{
		int i = 0;
		for (; i < m_components.size(); ++i)
			if (typeid(m_components[i]) == typeid(T*))
				break;

		// no component found
		if (i >= m_components.size())
			return;

		m_components.erase(i, 1);
	}

	virtual void Update();

	~Entity();
private:
	std::vector<Component*> m_components;
};

