#include "entity.h"

void Entity::Update()
{
	for (int i = 0; i < m_components.size(); ++i)
	{
		if(m_components[i])
			m_components[i]->Update();
	}
}

Entity::~Entity()
{
	for (int i = 0; i < m_components.size(); ++i)
	{
		m_components[i]->CleanUp();
		delete m_components[i];
	}
}
