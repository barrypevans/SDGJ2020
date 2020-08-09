#include "camera.h"
#include "window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "time.h"
Camera* Camera::g_pCamera;

void Camera::Init()
{
	m_width = 12;
	m_position = glm::vec3(0,0,0);
	m_targetPosition = m_position;
}

void Camera::CleanUp()
{
}

void Camera::Update()
{
	m_shakeIntensity -= Time::g_pTime->GetDeltaTime()*.5;
	m_shakeIntensity = m_shakeIntensity >= 0 ? m_shakeIntensity : 0;
	glm::vec2 randPos = glm::vec2((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	m_position = glm::mix(m_targetPosition, randPos, m_shakeIntensity);
}

glm::mat4x4 Camera::GetOrthographicProjection()
{
	float aspect = Window::g_pWindow->GetAspect();
	glm::vec2 dims = Window::g_pWindow->GetDimensions();
	float height = aspect * m_width;

	float f = 100.0f;
	float n = -100.0f;

	return glm::ortho(-m_width * 0.5f, m_width * 0.5f, -height*0.5f, height *0.5f, n, f);
}

glm::mat4x4 Camera::GetCameraTransformation()
{
	return glm::translate(glm::mat4(1.0f),-glm::vec3(m_position.x, m_position.y, 0.0f));
}

void Camera::DoShake(float shake)
{
	m_shakeIntensity += shake;
}
