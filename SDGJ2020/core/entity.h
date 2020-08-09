#pragma once
#include <vector>
class Component;
#include "component.h"
#include <glm/glm.hpp>

class Entity
{
public:
	Entity();

	template<class T>
	T* AddComponent()
	{
		T* comp = new T();
		dynamic_cast<Component*>(comp)->m_entity = this;
		m_components.push_back(comp);
		dynamic_cast<Component*>(comp)->Init();
		return comp;
	}

	template<class T>
	T* GetComponent()
	{
		for (int i = 0; i < m_components.size(); ++i)
			if (dynamic_cast<T*>(m_components[i]) != nullptr)
				return (T*)m_components[i];
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

	glm::vec2 m_position;
	glm::vec2 m_scale;
	float m_rotation;

private:
	std::vector<Component*> m_components;
};

