#pragma once
#include "ISystem.h"
#include <glm/glm.hpp>

class Camera : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;
	glm::mat4x4 GetOrthographicProjection();
	glm::mat4x4 GetCameraTransformation();
	
	void DoShake(float shake = .06f);

	float GetWidth();
	float GetHeight();

	glm::vec2 m_position;
	glm::vec2 m_targetPosition;
	glm::vec3 m_rotation;
	float m_width;

	float m_shakeIntensity = 0;

	static Camera* g_pCamera;
};