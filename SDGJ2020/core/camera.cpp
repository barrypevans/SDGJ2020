#include "camera.h"
#include "window.h"
#include <glm/gtc/matrix_transform.hpp>
Camera* Camera::g_pCamera;

void Camera::Init()
{
	m_width = 10;
	m_position = glm::vec3(0,1,0);
}

void Camera::CleanUp()
{
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
