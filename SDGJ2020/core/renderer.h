#pragma once
#include "ISystem.h"
#include <sdl/SDL.h>
#include "renderable.h"
#include <glm/glm.hpp>


class Renderer : public ISystem
{
public:

	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	void JoinRenderQueue(Renderable* renderable);
	void ClearRenderQueue();
	void RenderAllInQueue();

private:
	std::vector<Renderable*> renderables;

	const glm::vec3 vertices[4] =
	{
		glm::vec3(-0.5,-0.5,0),
		glm::vec3(0.5,-0.5,0),
		glm::vec3(0.5,-0.5,0),
		glm::vec3(0.5,0.5,0)
	};

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
};

