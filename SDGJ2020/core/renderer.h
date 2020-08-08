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

	void SetupQuad();
	void DrawRenderable(Renderable* renderable);

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uv;
	};

	const Vertex vertices[6] =
	{
		{glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)},
		{glm::vec3(0.5,0.5,0), glm::vec2(1,1)},
		{glm::vec3(0.5,-0.5,0), glm::vec2(1,0)},

		{glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)},
		{glm::vec3(-0.5,0.5,0), glm::vec2(0,1)},
		{glm::vec3(0.5,0.5,0), glm::vec2(1,1)},
	};

	unsigned int VBO; //Vertex Buffer's ID
	unsigned int vertexShader; //Vertex Shader's ID
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int VAO;
};

