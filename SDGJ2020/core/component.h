#pragma once

class Component
{
public:
	virtual void Init();
	virtual void Update();
	virtual void CleanUp();

	void* m_entity;
};

