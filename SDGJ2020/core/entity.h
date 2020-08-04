#pragma once
#include <glm/glm.hpp>

class Entity
{
public:
	virtual void Update();
	virtual void Intialize();
	virtual void CleanUp();

	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

};