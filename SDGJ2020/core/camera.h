#pragma once
#include "ISystem.h"
#include <glm/glm.hpp>

class Camera : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	glm::mat4x4 GetOrthographicProjection();
	glm::mat4x4 GetCameraTransformation();
	
	glm::vec2 m_position;
	glm::vec3 m_rotation;
	float m_width;

	static Camera* g_pCamera;
};