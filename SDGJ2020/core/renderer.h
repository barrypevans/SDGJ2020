#pragma once
#include "ISystem.h"
#include <sdl/SDL.h>
#include "renderable.h"
#include <glm/glm.hpp>
#include <vector>

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

	static Renderer* g_pRenderer;
private:
	std::vector<Renderable*> renderables;

	const glm::vec3 vertices[3] =
	{
		glm::vec3(-0.5,-0.5,0),
		glm::vec3(0,0.5,0),
		glm::vec3(0.5,-0.5,0)
	};

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	unsigned int VBO; //Vertex Buffer's ID
	unsigned int vertexShader; //Vertex Shader's ID
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int VAO;



};

